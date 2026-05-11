
// COPYRIGHT DASSAULT SYSTEMES 2007
// All right reserved

//==========================================================================
//	Sample code for : Functional Modeling Interfaces
//	Mission	        : Build a basic feature structure
//	
//	Type            : Batch program
//	Inputs          : One path to record the created feature structure
//	Outputs	        : Return code is 0 if program worked ok, >0 otherwise
//	 
//	Illustrates     : Main Functional Set and Functional Set creation
//
// 
//==========================================================================

//==========================================================================
// How to execute :
// 
//   CAAFmoCreateBasicFeatureStructureMain Part1 
//
//   with : Part1 path to the saved part
//         
//
// Example :
//   CAAFmoCreateBasicFeatureStructureMain E:\CAA2WS\tmp\UserFuncMod1.CATPart    
//
//
//
// Return code :
//   0 successful execution
//   1 number of arguments incorrect
//   2 problem during session's creation
//   3 problem during Main Functional Set's creation
//   4 problem during Functional Sets' creation
//   5 problem during the basic feature structure's recording
//   6 problem during session's closing
// 
//==========================================================================


// Functional Modeling Framework
#include "CATIFmoBody.h"            // needed to create Main Functional Set
#include "CATIFmoFunctionalSet.h"   // needed to create Functional Sets


// ObjectModelerBase Framework
#include "CATSession.h"	            // needed to manage session
#include "CATDocument.h"            // needed to manage the CATPart document
#include "CATDocumentServices.h"    // needed to create the document
#include "CATSessionServices.h"     // needed to create the session
#include "CATInit.h"                // needed to access Mechanical design container
#include "CATIAlias.h"              // needed to rename features


// MecModInterfaces Framework
#include "CATIPrtContainer.h"       // needed to manage Mechanical Design features


// ObjectSpecsModeler Framework
#include "CATISpecObject.h"         // needed to query interface

// System Framework
#include "CATBoolean.h"


//================================================================================
// Main Method 
// 
// Creates a basic feature structure
//
// Steps:
//  1. Opens a session
//  2. Creates a Main Functional Set
//  3. Creates four Functional Sets, with convenient change of name
//  4. Saves the Basic Feature Structure
//  5. Closes the session
//================================================================================
int main (int iArgc,         // Number of arguments (2)
		      char *iArgv[])     // Path for the created part
{
  int rc = 0;

  // Step 1 - Opens a session

  // Checks arguments
  if (2 != iArgc) 
  {
    return 1;
  }

  // Opens a session
  CATSession * pSampleSession = NULL;
  Create_Session ("SampleSession", pSampleSession);

  CATDocument * pDoc = NULL;
  CATDocumentServices::New ("CATPart", pDoc);

  if (NULL == pDoc)
  {
    return 2;
  }

  CATInit_var hInitOnDoc (pDoc);
  if (NULL_var == hInitOnDoc)
  {
    return 2; 
  }

  CATIPrtContainer * piPrtCont  = (CATIPrtContainer*) hInitOnDoc -> GetRootContainer ("CATIPrtContainer");	
  CATISpecObject_var hMechPart;
  if (piPrtCont)
  {
    // retrieves the MechanicalPart
    hMechPart = piPrtCont -> GetPart();

    piPrtCont -> Release();
    piPrtCont = NULL;
  }

  if (NULL_var == hMechPart)
  {
    return 3;
  }

  // Step 2 - Creates a Main Functional Set

  CATIFmoBody * piFmoBody = NULL;
  CATIFmoFunctionalSet * piFmoFunctionalSet = NULL;
  if (SUCCEEDED (hMechPart -> QueryInterface (IID_CATIFmoBody, (void**) &piFmoBody)))
  {
    CATBoolean iForceCreation = TRUE,
               oIsCreated     = FALSE;

    // Forces the creation of the Main Functional Set
    piFmoBody -> CreateOrRetrieveMainFunctionalSet (&piFmoFunctionalSet, iForceCreation, oIsCreated);
    if (!oIsCreated)
    {
      return 4;
    }

    piFmoBody -> Release();
    piFmoBody = NULL;
  }

  if (NULL == piFmoFunctionalSet)
  {
    return 4;
  }

  // Step 3 - Creates four Functional Sets, with convenient change of name

  CATIFmoFunctionalSet * piShellableFunctionalSet = NULL,
                       * piInternalFunctionalSet  = NULL,
                       * piExternalFunctionalSet  = NULL,
                       * piProtectedFunctionalSet = NULL;
 
  piFmoFunctionalSet -> CreateFunctionalSet (&piShellableFunctionalSet);
  if (piShellableFunctionalSet)
  {
    CATIAlias * piFunSetAlias = NULL;
    if (SUCCEEDED (piShellableFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
    {
       piFunSetAlias -> SetAlias ("FunctionalSet_Shellable");

       piFunSetAlias -> Release();
       piFunSetAlias = NULL;
    }

     piShellableFunctionalSet -> Release();
     piShellableFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }

  piFmoFunctionalSet -> CreateFunctionalSet (&piInternalFunctionalSet);
   if (piInternalFunctionalSet)
  {
    CATIAlias * piFunSetAlias = NULL;
    if (SUCCEEDED (piInternalFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
    {
       piFunSetAlias -> SetAlias ("FunctionalSet_Internal");

       piFunSetAlias -> Release();
       piFunSetAlias = NULL;
    }

     piInternalFunctionalSet -> Release();
     piInternalFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }

  piFmoFunctionalSet -> CreateFunctionalSet (&piExternalFunctionalSet);
  if (piExternalFunctionalSet)
  {
    CATIAlias * piFunSetAlias = NULL;
    if (SUCCEEDED (piExternalFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
    {
       piFunSetAlias -> SetAlias ("FunctionalSet_External");

       piFunSetAlias -> Release();
       piFunSetAlias = NULL;
    }

     piExternalFunctionalSet -> Release();
     piExternalFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }

  piFmoFunctionalSet -> CreateFunctionalSet (&piProtectedFunctionalSet);
  if (piProtectedFunctionalSet)
  {
    CATIAlias * piFunSetAlias = NULL;
    if (SUCCEEDED (piProtectedFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
    {
       piFunSetAlias -> SetAlias ("FunctionalSet_Protected");

       piFunSetAlias -> Release();
       piFunSetAlias = NULL;
    }

     piProtectedFunctionalSet -> Release();
     piProtectedFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }

  if (piFmoFunctionalSet)
  {
     piFmoFunctionalSet -> Release();
     piFmoFunctionalSet = NULL;
  }

  // Step 4 - Saves this Basic Feature Structure

  // Saves in the input path
  HRESULT boolSave = E_FAIL;
  char * nomPart1 = iArgv[1];
  boolSave = CATDocumentServices::SaveAs (*pDoc, nomPart1);
  if (!SUCCEEDED (boolSave))
  {
    return 5;
  }

  // Step 5 - Closes the cession

  // Closes the documents
  boolSave = CATDocumentServices::Remove (*pDoc);
  if (!SUCCEEDED (boolSave))
  {
    return 6;
  }

  // Closes the session   
  boolSave = ::Delete_Session ("SampleSession"); 
  if (!SUCCEEDED (boolSave))
  {
    rc = 6;
  }
  else
  {
    rc = 0;
  }
  return rc;
}
