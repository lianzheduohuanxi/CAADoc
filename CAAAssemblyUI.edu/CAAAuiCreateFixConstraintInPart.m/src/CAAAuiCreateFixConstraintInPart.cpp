/**
 * @quickReview DVE 05:04:25
 * @quickReview BPF 05:07:21
 * @quickReview BPF 05:04:19
 */


//============================================================================================
// Sample code for : Assembly
// Mission         : Create,remove and list a fix constraint on a CATPart.
//
// Type            : Batch program
// Inputs          : Part file
// Outputs         : Return code is 0 if program worked Ok, >0 otherwise
// Step by step	   :
//					 1. Opening a session  
//					 2. Opening a document
//					 3. Get the root (spec) container of given CATPart.
//					 4. Get the mechanicalPart feature which is contained in the specification container of a Part document.
//					 5. Retrieve all (non order) GeometricalSet type children of a Part.
//					 6. Get the (line) child by its (3rd) position of GeometricalSet.  
//					 7. Create a constraint : Type - Fix constraint, Element to be constrained - Line,  
//					 8. Get the list of constraints under a given Part 
//					 9. Remove constraints
//					10. closing document
//					11. closing session
//
//============================================================================================





#include <iostream.h>

//System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATGetEnvValue.h"

// ObjectModelerBase Framework
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATDocument.h"
#include "CATInit.h" 

//MecModInterfaces 
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIMmiNonOrderedGeometricalSet.h"

//object specs moderler
#include "CATISpecObject.h"
#include "CATIDescendants.h"
#include "CATLISTV_CATISpecObject.h"

//ConstraintModeler 
#include "CATICst.h"
#include "CATConstraintServices.h"


// --- Correction to IR 0504177 ---
#ifdef _WINDOWS_SOURCE
   #define SLASH     "\\"
#else
   #define SLASH     "/"
#endif



// Return code 

#define RET_OK						0

#define RET_ERR						1
#define ERR_USAGE					2
#define ERR_ENV_SLASH				3

#define ERR_SESSIONOPEN				11
#define ERR_SESSIONCLOSE			12

#define ERR_DOCOPEN					21
#define ERR_DOCLCOSE				22

#define ERR_CREATECST				31
#define ERR_LISTCST					32
#define ERR_REMOVECST				33



int main(int iargc, char *iargv[])
{
	HRESULT rc = E_FAIL;
	int RetCode =  RET_OK;
	
	cout << "\nUse Case : Create, remove and list a fix constraint on CATPart." << endl << endl;

	if(iargc!=3)
	{
		cout << "USAGE : " << iargv[0] << " <InputPartFile Path>  <OutputPartFile Path>" << endl << endl;
		return ERR_USAGE;
	}

	CATUnicodeString inputFile ="";
	CATUnicodeString outputFile =""; 

    CATUnicodeString slash(SLASH);
	inputFile = iargv[1]+slash+"Line_FixCst.CATPart";
	outputFile = iargv[2]+slash+"Line_FixCst_output.CATPart";


	cout << "Starting Use Case                                                               ... [ OK ]" << endl;

	cout << "\n InputFile = " << inputFile.CastToCharPtr();
	cout << "\n OutputFile = " << outputFile.CastToCharPtr() << "\n";

	// Opening a session  
	CATSession* pSession = NULL;
	rc = Create_Session("Session_ASM_FixCST",pSession);
	if ( FAILED(rc) )
	{
		cout << "Creating Session                                                      ... [ ERROR ]" << endl;
	    return ERR_SESSIONOPEN;
	}
	cout << "Creating Session                                                                ... [ OK ]" << endl;

	// Opening a document
	CATDocument * pDocument = NULL;
	rc = CATDocumentServices::OpenDocument(inputFile,pDocument);
	if ( SUCCEEDED(rc) )
	{
		cout << "Opening document                                                                ... [ OK ]" << endl;

		CATInit *pDocAsInit = NULL;
		if( SUCCEEDED(pDocument->QueryInterface(IID_CATInit, (void**)&pDocAsInit)) )
		{
			CATBaseUnknown *piBaseRoot = NULL;
			CATIPrtContainer *piSpecContainer = NULL;
			
			// Get the root (spec) container of given CATPart.
			piBaseRoot = pDocAsInit->GetRootContainer("CATIPrtContainer");
			pDocAsInit->Release();
			pDocAsInit = NULL;

			if(NULL != piBaseRoot)
			{
				rc = piBaseRoot->QueryInterface(IID_CATIPrtContainer, (void**) &piSpecContainer);
				piBaseRoot->Release();
				piBaseRoot = NULL;

				if(SUCCEEDED(rc) && NULL != piSpecContainer)
				{
					//Get the mechanicalPart feature which is contained in the specification container of a Part document.
					CATIPrtPart_var spPart( piSpecContainer->GetPart() );
					piSpecContainer->Release();
					piSpecContainer = NULL;

					if(NULL_var != spPart)
					{
						CATIDescendants *piPartAsDescendants = NULL;
						rc = spPart->QueryInterface(IID_CATIDescendants, (void**)&piPartAsDescendants) ;
						if ( SUCCEEDED(rc) && NULL != piPartAsDescendants)
						{
							cout << "Searching descendents of Part                                                   ... [ OK ]" << endl;
				
							// Retrieve all (non order) GeometricalSet type children of a Part.
							CATLISTV(CATISpecObject_var) GSList;  
							piPartAsDescendants->GetAllChildren("CATIMmiNonOrderedGeometricalSet",GSList);
							
							piPartAsDescendants->Release();
							piPartAsDescendants = NULL;

							CATIMmiNonOrderedGeometricalSet_var spGS=NULL_var;
							if( 0 != GSList.Size())
							{
								spGS=GSList[1];
								if(NULL_var != spGS)
								{
									CATIDescendants *pDescendants = NULL;
									rc = spGS->QueryInterface(IID_CATIDescendants, (void**)&pDescendants) ;
									if ( SUCCEEDED(rc) )
									{
										cout << "Searching descendents of GS                                                     ... [ OK ]" << endl;
										cout << "*** GS  : children count  = " << pDescendants->GetNumberOfChildren() << endl;

										// Get the (line) child by its (3rd) position of GeometricalSet.  
										CATISpecObject_var spSpecLine = NULL_var;
										spSpecLine=pDescendants->GetChildAtPosition(3);
										if (NULL_var != spSpecLine)
										{
											cout << "Searching GS child : Line                                                       ... [ OK ]" << endl;


											CATLISTV(CATBaseUnknown_var) ElemList; 
											ElemList.Append(spSpecLine);

											CATICst_var spCst = NULL_var;

											// Create a constraint : Type - Fix constraint, Element to be constrained - Line,  
											rc = CATConstraintServices::CreateConstraintIn(	spPart, 
																							CstType_Reference,
																							ElemList,
																							0.0,
																							CATCstVal_Mode_Constrained,
																							spCst);

											if ( SUCCEEDED(rc) )
											{
												cout << "***** Creating constraint *****                                                 ... [ OK ]" << endl;
												// saving document with constraints
												CATDocumentServices::SaveAs(*pDocument,outputFile);

												// Get the list of constraints under a given Part 
												CATLISTV(CATICst_var) CstList;
												rc=CATConstraintServices::ListConstraints(spPart, CstList);
												if(SUCCEEDED(rc))
												{
													cout << "***** Listing constraints *****                                                 ... [ OK ]" << endl;
													cout << "*** Total Cst = " << CstList.Size() << endl;
												}
												else
												{
													cout << "Listing constraints                                                   ... [ ERROR ]" << endl;
													RetCode=ERR_LISTCST;
												}


												// Remove constraints
												rc = CATConstraintServices::RemoveConstraint(CstList[1]);
												if ( SUCCEEDED(rc) )
												{
													cout << "***** Removing constraint *****                                                 ... [ OK ]" << endl;
												}
												else
												{
													cout << "Removing constraints                                                  ... [ ERROR ]" << endl;
													RetCode=ERR_REMOVECST;
												}

											}
											else
											{
												cout << "Creating constraint                                                   ... [ ERROR ]" << endl;
												RetCode=ERR_CREATECST;
											}

										}
										else //(NULL_var != spSpecLine)
										{
											cout << "Searching GS child : Line                                             ... [ ERROR ]" << endl;
											RetCode = RET_ERR;
										}

										pDescendants->Release();
										pDescendants = NULL;
									} // if( spGS)
									else
										RetCode = RET_ERR;
								}
								else 
								{
									cout << "Descendents searching                                                 ... [ ERROR ]" << endl;
									RetCode = RET_ERR;
								}
							}
							else //if( 0 != GSList.Size() )
							{
								cout << "Part does not contains Geomtrical Set                                 ... [ ERROR ]" << endl;
								RetCode = RET_ERR;
							}
						}
						else // spPart->QueryInterface(CATIDescendants)
						{
							cout << "Descendents searching                                                 ... [ ERROR ]" << endl;
							RetCode = RET_ERR;
						}
					} // if(NULL_var != spPart) 
					else
						RetCode = RET_ERR;
				}// QI(IID_CATIPrtContainer)
				else
					RetCode = RET_ERR;
			} // if(NULL != piBaseRoot)
			else
				RetCode = RET_ERR;
		} // pDocument->QueryInterface(CATInit)
		else
		{
			cout << "Initializing                                                          ... [ ERROR ]" << endl;
			RetCode = RET_ERR;
		}

		// closing document
		CATDocumentServices::Remove(*pDocument);
		cout << "Closing document                                                                ... [ OK ]" << endl;
	}
	else // CATDocumentServices::OpenDocument()
	{
		cout << "Opening document                                                      ... [ ERROR ]" << endl;
	    RetCode = ERR_DOCOPEN;
	}

	// closing session
	rc=Delete_Session("Session_ASM_FixCST");
	if ( FAILED(rc) )
	{
		cout << "Closing Session                                                       ... [ ERROR ]" << endl;
	    return ERR_SESSIONCLOSE;
	}
	cout << "Closing Session                                                                 ... [ OK ]" << endl;
	
	cout << "Finishing Use Case                                                              ... [ OK ]" << endl;

	return RetCode;
}



/*
 ----------------------------------------------------------------------------------------------------------
          ***                 End of Use case : CAAAuiCreateFixConstraintInPart        ***                 
 ----------------------------------------------------------------------------------------------------------
*/
