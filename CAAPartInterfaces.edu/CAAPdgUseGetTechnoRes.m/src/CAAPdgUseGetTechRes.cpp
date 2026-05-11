/**
 * @quickReview TZH 13:07:12
 */
// COPYRIGHT DASSAULT SYSTEMES 2013

//==========================================================================
//  Sample code for : Part Interfaces
//  Mission					: - Get Technological result informations 
//										- Dump attributes
//	
//  Type						: Batch program
//  Inputs					:   CATPart
//  Outputs					:	Return code is 0 if program worked ok, >0 otherwise
//	 
//
//==========================================================================

//==========================================================================
//  How to execute :
//  
//  CAAPdgUseGetTechnoRes InputPart
//    
//    
//========================================================================== 



//ObjectModelerBase Framework
#include "CATSession.h"          // needed to manage session
#include "CATDocument.h"				 // needed to manage documents
#include "CATDocumentServices.h" // needed to create/save documents
#include "CATSessionServices.h"  // needed to create/delete session
#include "CATInit.h"             // needed to retrieve root container from document


// MecModInterfaces Framework
#include "CATIPrtContainer.h"    // needed to retrieve factories
#include "CATIPrtPart.h"         // needed to access reference planes


#include "CATIPdgUseTechResTool.h" 
#include "CATIPdgUseTechnoRes.h" 
#include "CATListOfCATIPdgUseTechnoRes.h"
#include "CATListValCATICkeParm.h"
#include "CATIDescendants.h"
#include "CATICkeParm.h"
#include "CATLib.h"
#include "CATGetEnvValue.h"
#include "CATLISTV_CATISpecObject.h" 
#include "CATFace.h"
#include "ListPOfCATFace.h"
#include "CATISpecObject.h"


FILE* OpenStream (CATUnicodeString & oFileName);

int main(int iArgc, 			// Number of arguments (2)
         char *iArgv[])   
{


  int rc=0;

  // Checks arguments
 
  //if(1 != iArgc) return 1;
  char*  FilePath  =  iArgv[1]; 

  // Opens a session
  CATSession * pSampleSession = NULL;
  Create_Session("SampleSession",pSampleSession);

  // Opens a CATPart document and initializes the data
  CATDocument * pDoc= NULL;

    rc = CATDocumentServices::Open(FilePath, pDoc) ;


  CATInit_var spInitOnDoc(pDoc);
  if(NULL_var == spInitOnDoc) return 2;

  // Retrieves the root container
  CATIPrtContainer * piPrtCont = 
    (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");	
	
	
  CATIPrtPart_var spPart;
  if(piPrtCont)
  {
    spPart = piPrtCont->GetPart();



  			CATIDescendants *pPartAsDescendant = NULL;        
			if(SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant)))
			{
				CATUnicodeString FileName;
				FILE * pStream = OpenStream(FileName);
				if (pStream)
				{

				//TrBody
				CATLISTV(CATISpecObject_var) ListTRBodies;
				pPartAsDescendant->GetAllChildren("CATIMechanicalTool", ListTRBodies);
				if (ListTRBodies.Size())
				{

					for(int k=1; k<=ListTRBodies.Size(); k++)
					{
						fprintf(pStream,"************************************************\n");
						fprintf(pStream,"***********New Body********\n");
						fprintf(pStream,"************************************************\n");

						CATISpecObject_var hSpecTRBody;
						hSpecTRBody = ListTRBodies[k];

								CATIPdgUseTechResTool *pTerBody = NULL;
								if(SUCCEEDED(hSpecTRBody->QueryInterface(IID_CATIPdgUseTechResTool,(void**)&pTerBody))&&pTerBody)
								{
							
									CATLISTP(CATIPdgUseTechnoRes) pListTR = NULL;
									rc = pTerBody->GetAllTechResFromTool(pListTR);
									if(SUCCEEDED(rc))
									{
										if(SUCCEEDED(rc) && pListTR.Size())
										{

											for(int i=1; i<pListTR.Size(); i++)
											{
												fprintf(pStream,"************************************************\n");
												CATIPdgUseTechnoRes *piCurrentTR = pListTR[i];
												if(piCurrentTR)
												{
													CATListValCATICkeParm_var TechResList;
													piCurrentTR->GetTechResAttributes (TechResList);
													if (TechResList.Size())
													{
														for(int j=1; j<=TechResList.Size(); j++)
														{
															CATICkeParm_var spParm=TechResList[j];
															CATUnicodeString  ParamToDisplay="";
															CATUnicodeString  Param=spParm->Name();
															ParamToDisplay.Append(Param);
															ParamToDisplay.Append("      =         ");
															CATUnicodeString  ParamValue=spParm->Show();
															ParamToDisplay.Append(ParamValue);
															ParamToDisplay.Append("\n");
															fprintf(pStream,ParamToDisplay);

														}

													}
												/*	ListPOfCATFace TechResFaceList;
													piCurrentTR->GetTechResfaces (TechResFaceList);
													if (TechResFaceList.Size())
													{
														fprintf(pStream,"*********Tags**********\n");
														for(int k=1; k<=TechResFaceList.Size(); k++)
														{
															CATFace *pCurFace = TechResFaceList[k];
															if(pCurFace)
															{
																int FaceTag1=0;
																FaceTag1= pCurFace->GetPersistentTag();
																CATUnicodeString str;
																str.BuildFromNum(FaceTag1);

																fprintf(pStream,str);

															}

														}
													}*/


													
													piCurrentTR->Release(); piCurrentTR = NULL;
												}
											}
											
										}
									}
									pTerBody->Release();
									pTerBody = NULL;

								}
							
					}
				}
				fclose(pStream);
			}
				pPartAsDescendant->Release();
				pPartAsDescendant = NULL;
			}

			piPrtCont->Release();
			piPrtCont = NULL;
  }







  // Closes the session   
  ::Delete_Session("SampleSession"); 

  return rc;
};


FILE* OpenStream (CATUnicodeString & oFileName)
{
	static int _sUsageCountInSession = 0;
	FILE * opStream = NULL;

	_sUsageCountInSession ++; // Increment usage counter

	char FullName [CATMaxPathSize];

	// Get stream directory
	const char* pStreamDir = CATGetEnv("ADL_ODT_OUT");
	if( !pStreamDir )
	{
		pStreamDir = CATGetEnv("TMP");
	}

	const char* pOdtName = CATGetEnv("ODT_LOG_NAME");
	if( !pOdtName )
	{
		pOdtName = "DumpResult";
	}

	CATMakePath(pStreamDir, pOdtName, FullName);
	oFileName = FullName;

	opStream = fopen(FullName, "w+");


	return (opStream);
}
