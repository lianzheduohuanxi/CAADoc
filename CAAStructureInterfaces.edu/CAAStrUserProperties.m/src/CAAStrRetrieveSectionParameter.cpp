//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003+
//=============================================================================

//-------------------------------------------------------------
//               CAAStrRetrieveSectionParameter                    
//-------------------------------------------------------------

/*********************************************************************
 
  Get the value of the computed attribute that was added in use case 
  CAAStrDefineUserAttributes
     
  - 1. Opens an existing product
  - 2. Retrieves part container
  - 3. Retrieves all members
  - 4. Access member's section area attribute
  - 5. Close the open document and delete the session
     
 To run this sample, you can use the command:
    mkrun -c "CAAStrUserProperties input.CATPart"
 where input.CATPart is an existing document that contains the 
 structure plate and shape objects.

***********************************************************************/

//=============================================================================

#include <iostream.h> 

// System Framework
#include "CATLib.h"
#include "CATListOfCATUnicodeString.h"

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATILinkableObject.h"
#include "CATInit.h"
#include "CATIDocId.h"
#include "CATIAlias.h"

// StructureInterfaces Framework
#include "CATIAStrServices.h"
#include "CATIStructureMember.h"

// KnowledgeInterfaces Framework
#include "CATIValue.h"
#include "CATICkeParm.h"
#include "CATIInstance.h"
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATIDescendants.h"

// MecModInterfaces Framework
#include "CATIPrtContainer.h"

// ProductStructure Framework
#include "CATIProduct.h"

HRESULT AccessMemberSectionAttribute(CATISpecObject_var &ispMember);

// ------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
	HRESULT rc = 0;

	/* -------------------------------- */
	/*  0. Control of arguments number  */       
	/* -------------------------------- */
	 if ( 2 != argc )
	 {
		 cout << "ERROR : bad number of arguments " << argc << endl << flush;
		 return 1;  
	 }

	/* ---------------------------------------- */
	/* 1. Load an existing CATProduct document  */
	/* ---------------------------------------- */
	CATSession* pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                    pSession);
	if (SUCCEEDED(rc))
	  cout << endl << " ## CAAStrRetrieveSectionParameter ## " << endl
		     << endl << " Initialize CATIA Session Succeeded " << endl << flush;
		cout << endl << " Input document path " << argv[1] << endl << flush;

	CATDocument* pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1],pDoc);

	if ( FAILED(rc) || (NULL==pDoc)) return 2;
	cout << endl << " product document opened : " 
		   << argv[1] << endl << flush;
	
	/* ---------------------------- */
	/* 2. Retrieves Prt Container   */
	/* ---------------------------- */
  CATISpecObject_var spSpecObjectPart;
  if (pDoc)
  {
    CATInit *pInitOnDoc = NULL ;
    if (SUCCEEDED(pDoc->QueryInterface(IID_CATInit,(void **) &pInitOnDoc)) && pInitOnDoc)
    {
      CATIPrtContainer *pIPrtCont = NULL ;
      pIPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");
      if (pIPrtCont)
      {
        spSpecObjectPart = pIPrtCont->GetPart();
        pIPrtCont->Release(); pIPrtCont = NULL;
      }
      pInitOnDoc->Release(); pInitOnDoc = NULL;
    }
  }

  CATITypeDictionary_var spDico = CATGlobalFunctions::GetTypeDictionary();
  if(!!spDico )
  {
    spDico->LoadPackage( "StrFunctionalDesign" );
	  cout << endl << " Load StrFunctionalDesign Package  " << endl << flush;
  }

	/* --------------------------------------------------- */
	/* 3. Retrieves all the member object under the part   */
	/* --------------------------------------------------- */

  CATIDescendants_var spPartAsDesc = spSpecObjectPart;
  CATLISTV(CATISpecObject_var) ListMember;
  if (!! spPartAsDesc)
    spPartAsDesc->GetAllChildren("CATIStructureMember", ListMember);

  /* ------------------------------------------- */
  /* 4. Access member's section area attribute   */
  /* ------------------------------------------- */
  int numberOfChildren = ListMember.Size();
	cout << endl << " The number of Children for CATIStructureMember  " << numberOfChildren << endl << flush;
	for (int i = 1; i <= numberOfChildren; i++)
	{
		rc = AccessMemberSectionAttribute( (ListMember)[i]);

		if (!SUCCEEDED(rc)) return 5;
	}

  /* -------------------------------------------- */
	/*  5. Ends the session                         */
	/* -------------------------------------------- */
	// remove opened document
	rc = CATDocumentServices::Remove (*pDoc);
	if (!SUCCEEDED(rc)) return 6;
	
	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	
	rc = ::Delete_Session("CAA2_Sample_Session");
	if (SUCCEEDED(rc))
		cout << " Delete Session Succeeded " << endl << flush;
	
	return rc;
		
};

HRESULT AccessMemberSectionAttribute(CATISpecObject_var &ispMember)
{
  HRESULT rc = E_FAIL;
  CATTry 
  { 
    CATIValue* piVal = NULL;
    if ( NULL_var != ispMember )
    {
      CATIAlias_var spAlias(ispMember);
      if (!! spAlias)
        cout << "Member " << (spAlias->GetAlias()).ConvertToChar() << endl;
      CATIInstance *piInstance = NULL;
	    rc = ispMember->QueryInterface (IID_CATIInstance,(void **)&piInstance);	 
      if( SUCCEEDED(rc) &&  piInstance)
      {
        piVal = piInstance->GetValue("SectionArea");
        if( NULL != piVal )
        {
          CATUnicodeString uAttrVal = piVal->Show();
          cout << "SectionArea value is: " << uAttrVal.ConvertToChar() << endl;
        }
        piInstance->Release(); piInstance = NULL;
      }      
    }    
    if ( NULL != piVal ) { piVal->Release(); piVal = NULL; }
  } // end CATTry

  CATCatch (CATError, error)
  {        
    CATRethrow;
  }     
  CATEndTry;
  return rc;
}
