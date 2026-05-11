
// COPYRIGHT DASSAULT SYSTEMES 2007
// All right reserved

//==========================================================================
//	Sample code for : Functional Modeling Interfaces
//	Mission	        : Import of FuncSpecs from a CATPArt to a basic feature structure
//	
//	Type            : Batch program
//	Inputs          : Two paths to record the modified part
//	Outputs	        : Return code is 0 if program worked ok, >0 otherwise
//	 
//	Illustrates     : Navigate into a Solid Functional Set and import of Func Specs
//
// 
//==========================================================================

//==========================================================================
// How to execute :
// 
//   CAAFmoImportFunctionalSpecsMain Part1 
//
//   with : Part1 path to the saved part
//         
//
// Example :
//   CAAFmoImportFunctionalSpecsMain E:\CAA2WS\tmp\UserFuncMod1.CATPart    
//
//
//
// Return code :
//   0 successful execution
//   1 number of arguments incorrect
//   2 problem during input document's openning
//   3 problem during PartBody's retrieving
//   4 problem during Main Functional Set's retrieving
//   5 problem during Functional Sets of initial part retrieving
//   6 problem during Functional Specifications import
//   7 problem during Functional Modifier retrieving
//   8 problem during the part with imports recording
//   9 problem during session's closing
//  10 problem during session's deletion
// 
//==========================================================================


// Functional Modeling Framework
#include "CATIFmoBody.h"                              // needed to get Main Functional Set
#include "CATIFmoFunctionalSet.h"                     // needed to get Functional Sets
#include "CATIListOfCATIFmoFunctionalSet.h"           // needed get Functional Sets
#include "CATIFmoFunctionalSpecification.h"           // needed to get Functional Specifications
#include "CATIListOfCATIFmoFunctionalSpecification.h" // needed to get Functional Specifications
#include "CATIFmoImportFactory.h"


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

// Visualizationbase Framework
#include "CATPathElement.h"         // needed to import Functional Specification
#include "CATIBuildPath.h"          // needed to import Functional Specification

// System Framework
#include "CATUnicodeString.h"       
#include "CATBoolean.h"


//================================================================================
// Main Method 
// 
// Creates a basic feature structure
//
// Steps:
//  1. Opens a session
//  2. Retrieves the part with input datas
//  3. Retrieves the Basic Feature Structure to add the Functional Imports
//  4. Retrieves four Functional Sets, with convenient name in InitialPart
//  5. Retrieves four Functional Sets, with convenient name in FinalPart
//  6. Import each Functional Shellable in the FunctionalSet_ShellableImports
//  7. Retrieve modifiers of a Functional Specification
//  8. Saves the FinalPart with the Functional imports
//  9. Closes the session
//================================================================================
int main (int iArgc,         // Number of arguments (4)
		      char *iArgv[])     // Path for the two input parts and the output part
{
  int rc = 0;

  // Step 1 - Opens a session

  // Checks arguments
  if (4 != iArgc) 
  {
    return 1;
  }

  // Opens a session
  CATSession * pSampleSession = NULL;
  Create_Session ("SampleSession", pSampleSession);

  // Step 2 - Retrieves the part with input datas
  CATDocument * pInitialDoc = NULL;
  char * nomInitialPart = iArgv[1];
  CATDocumentServices::OpenDocument (nomInitialPart, pInitialDoc);

  CATInit_var hInitOnInitialDoc (pInitialDoc);
  if (NULL_var == hInitOnInitialDoc)
  {
    return 2; 
  }

  // Step 3 - Retrieves the Basic Feature Structure to add the Functional Imports
  CATDocument * pFinalDoc = NULL;
  char * nomFinalPart = iArgv[2];
  CATDocumentServices::OpenDocument (nomFinalPart, pFinalDoc);

  CATInit_var hInitOnFinalDoc (pFinalDoc);
  if (NULL_var == hInitOnFinalDoc)
  {
    return 2; 
  }

  CATIPrtContainer * piPrtCont = (CATIPrtContainer*) hInitOnInitialDoc -> GetRootContainer ("CATIPrtContainer");	
  CATISpecObject_var hInitialMechPart;
  if (piPrtCont)
  {
    // retrieves the MechanicalPart
    hInitialMechPart = piPrtCont -> GetPart();

    piPrtCont -> Release();
    piPrtCont = NULL;
  }
  if (NULL_var == hInitialMechPart)
  {
    return 3;
  }

  CATISpecObject_var hFinalMechPart;
  piPrtCont = (CATIPrtContainer*) hInitOnFinalDoc -> GetRootContainer ("CATIPrtContainer");	
  if (piPrtCont)
  {
    // retrieves the MechanicalPart
    hFinalMechPart = piPrtCont -> GetPart();

    piPrtCont -> Release();
    piPrtCont = NULL;
  }
  if (NULL_var == hFinalMechPart)
  {
    return 3;
  }

  // Retrieves the Main Functional Set
  CATIFmoBody * piFmoBody = NULL;
  CATIFmoFunctionalSet * piFmoInitialFunctionalSet = NULL;
  if (SUCCEEDED (hInitialMechPart -> QueryInterface (IID_CATIFmoBody, (void**) &piFmoBody)))
  {
    CATBoolean iForceCreation = FALSE,
               oIsCreated     = FALSE;

    // Retrieves the existing Main Functional Set
    piFmoBody -> CreateOrRetrieveMainFunctionalSet (&piFmoInitialFunctionalSet, iForceCreation, oIsCreated);

    piFmoBody -> Release();
    piFmoBody = NULL;

    if (oIsCreated)
    {
      return 4;
    }
  }
  if (NULL == piFmoInitialFunctionalSet)
  {
    return 4;
  }

  CATIFmoFunctionalSet * piFmoFinalFunctionalSet = NULL;
  if (SUCCEEDED (hFinalMechPart -> QueryInterface (IID_CATIFmoBody, (void**) &piFmoBody)))
  {
    CATBoolean iForceCreation = FALSE,
               oIsCreated     = FALSE;

    // Retrieves the existing Main Functional Set
    piFmoBody -> CreateOrRetrieveMainFunctionalSet (&piFmoFinalFunctionalSet, iForceCreation, oIsCreated);

    piFmoBody -> Release();
    piFmoBody = NULL;

    if (oIsCreated)
    {
      return 4;
    }
  }
  if (NULL == piFmoFinalFunctionalSet)
  {
    return 4;
  }


  // Step 4 - Retrieves four Functional Sets, with convenient name in InitialPart

  CATIFmoFunctionalSet * piShellableFunctionalSet = NULL,
                       * piInternalFunctionalSet  = NULL,
                       * piExternalFunctionalSet  = NULL,
                       * piProtectedFunctionalSet = NULL;
 
  CATIListOfCATIFmoFunctionalSet * pListFunctionalSet = NULL;
  piFmoInitialFunctionalSet -> GetDirectFunctionalSet (&pListFunctionalSet);
  if (pListFunctionalSet)
  {
    unsigned int Size = 0;
    if (SUCCEEDED (pListFunctionalSet -> Count (&Size)))
    {
      for (unsigned int i = 0; i < Size; i++) 
      {
        CATIFmoFunctionalSet * pFunctionalSet = NULL;
        if (SUCCEEDED (pListFunctionalSet -> Item (i, &pFunctionalSet)) && pFunctionalSet)
        {
          CATIAlias * piFunSetAlias = NULL;
          if (SUCCEEDED (pFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
          {
             CATUnicodeString name = piFunSetAlias -> GetAlias ();
             if (name == "Functional Set_Shellable")
             {
               piShellableFunctionalSet = pFunctionalSet;
               if (piShellableFunctionalSet)
               {
                 piShellableFunctionalSet -> AddRef();
               }
             }
             else if (name == "Functional Set_Internal")
             {
               piInternalFunctionalSet = pFunctionalSet;
               if (piInternalFunctionalSet)
               {
                 piInternalFunctionalSet -> AddRef();
               }
             }
             else if (name == "Functional Set_External")
             {
               piExternalFunctionalSet = pFunctionalSet;
               if (piExternalFunctionalSet)
               {
                 piExternalFunctionalSet -> AddRef();
               }
            }
             else if (name == "Functional Set_Protected")
             {
               piProtectedFunctionalSet = pFunctionalSet;
               if (piProtectedFunctionalSet)
               {
                 piProtectedFunctionalSet -> AddRef();
               }
            }

             piFunSetAlias -> Release();
             piFunSetAlias = NULL;
          }

          pFunctionalSet -> Release(); 
          pFunctionalSet = NULL;
        }
      }
    }

    pListFunctionalSet -> Release();
    pListFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }
  if (NULL == piShellableFunctionalSet || NULL == piInternalFunctionalSet || NULL == piExternalFunctionalSet || NULL == piProtectedFunctionalSet)
  {
    return 5;
  }

  // Step 5 - Retrieves four Functional Sets, with convenient name in FinalPart

  CATIFmoFunctionalSet * piShellableFunctionalSetImport = NULL,
                       * piInternalFunctionalSetImport  = NULL,
                       * piExternalFunctionalSetImport  = NULL,
                       * piProtectedFunctionalSetImport = NULL;

  piFmoFinalFunctionalSet -> GetDirectFunctionalSet (&pListFunctionalSet);
  if (pListFunctionalSet)
  {
    unsigned int Size = 0;
    if (SUCCEEDED (pListFunctionalSet -> Count (&Size)))
    {
      for (unsigned int i = 0; i < Size; i++) 
      {
        CATIFmoFunctionalSet * pFunctionalSet = NULL;
        if (SUCCEEDED (pListFunctionalSet -> Item (i, &pFunctionalSet)) && pFunctionalSet)
        {
          CATIAlias * piFunSetAlias = NULL;
          if (SUCCEEDED (pFunctionalSet -> QueryInterface (IID_CATIAlias, (void**) &piFunSetAlias)))
          {
             CATUnicodeString name = piFunSetAlias -> GetAlias ();
             if (name == "FunctionalSet_ShellableImports")
             {
               piShellableFunctionalSetImport = pFunctionalSet;
               if (piShellableFunctionalSetImport)
               {
                 piShellableFunctionalSetImport -> AddRef();
               }
             }
             else if (name == "FunctionalSet_InternalImports")
             {
               piInternalFunctionalSetImport = pFunctionalSet;
               if (piInternalFunctionalSetImport)
               {
                 piInternalFunctionalSetImport -> AddRef();
               }
             }
             else if (name == "FunctionalSet_ExternalImports")
             {
               piExternalFunctionalSetImport = pFunctionalSet;
               if (piExternalFunctionalSetImport)
               {
                 piExternalFunctionalSetImport -> AddRef();
               }
            }
             else if (name == "FunctionalSet_ProtectedImports")
             {
               piProtectedFunctionalSetImport = pFunctionalSet;
               if (piProtectedFunctionalSetImport)
               {
                 piProtectedFunctionalSetImport -> AddRef();
               }
            }

             piFunSetAlias -> Release();
             piFunSetAlias = NULL;
          }

          pFunctionalSet -> Release(); 
          pFunctionalSet = NULL;
        }
      }
    }

    pListFunctionalSet -> Release();
    pListFunctionalSet = NULL;
  }
  else
  {
    return 5;
  }
  if (NULL == piShellableFunctionalSetImport || NULL == piInternalFunctionalSetImport || NULL == piExternalFunctionalSetImport || NULL == piProtectedFunctionalSetImport)
  {
    return 5;
  }


  // Step 6 : Import each Functional Shellable in the FunctionalSet_ShellableImports

  CATIListOfCATIFmoFunctionalSpecification * pListFunctionalSpec = NULL;
 
  piShellableFunctionalSet -> GetDirectFunctionalSpec (&pListFunctionalSpec);
  if (pListFunctionalSpec)
  {
    unsigned int Size = 0;
    if (SUCCEEDED (pListFunctionalSpec -> Count (&Size)))
    {
      CATIBuildPath * piTargetPathAccess = NULL;
      if (SUCCEEDED (piShellableFunctionalSetImport -> QueryInterface (IID_CATIBuildPath, (void**) &piTargetPathAccess)))
      {
        CATPathElement * pTargetPath = NULL;
        CATPathElement * pTargetContext = new CATPathElement();
        if (pTargetContext)
        {
          pTargetContext -> AddChildElement (hFinalMechPart);
          piTargetPathAccess -> ExtractPathElement (pTargetContext, &pTargetPath);

          pTargetContext -> Release();
          pTargetContext = NULL;
        }
        if (pTargetPath)
        {
          CATIFmoImportFactory * piFmoImportFactory = NULL;
          if (SUCCEEDED (piShellableFunctionalSetImport -> QueryInterface (IID_CATIFmoImportFactory, (void**) &piFmoImportFactory)))
          {
            for (unsigned int i = 0; i < Size; i++) 
            {
              CATIFmoFunctionalSpecification * pFunctionalSpec = NULL;
              if (SUCCEEDED (pListFunctionalSpec -> Item (i, &pFunctionalSpec)) && pFunctionalSpec)
              {
                CATIBuildPath * piInputPathAccess = NULL;
                if (SUCCEEDED (piShellableFunctionalSet -> QueryInterface (IID_CATIBuildPath, (void**) &piInputPathAccess)))
                {
                  CATPathElement * pInputPath = NULL;
                  CATPathElement * pInputContext = new CATPathElement();
                  if (pInputContext)
                  {
                    pInputContext -> AddChildElement (hInitialMechPart);
                    piInputPathAccess -> ExtractPathElement (pInputContext, &pInputPath);

                    pInputContext -> Release();
                    pInputContext = NULL;
                  }
                  if (pInputPath)
                  {
                    pInputPath -> AddChildElement (pFunctionalSpec);

                    CATIFmoFunctionalSpecification * pFunctionalImport = NULL;
                    piFmoImportFactory -> CreateFunctionalImport (pInputPath, pTargetPath, &pFunctionalImport);
                    if (pFunctionalImport)
                    {
                      pFunctionalImport -> Release();
                      pFunctionalImport = NULL;
                    }
                    else
                    {
                      return 6;
                    }

                    pInputPath -> Release();
                    pInputPath = NULL;
                  }

                  piInputPathAccess -> Release();
                  piInputPathAccess = NULL;
                }

                pFunctionalSpec -> Release(); 
                pFunctionalSpec = NULL;
              }
            }

            piFmoImportFactory -> Release(); 
            piFmoImportFactory = NULL;
          }

          pTargetPath -> Release();
          pTargetPath = NULL;
        }

        piTargetPathAccess -> Release(); 
        piTargetPathAccess = NULL;
      }
    }

    pListFunctionalSpec -> Release();
    pListFunctionalSpec = NULL;
  }
  else
  {
    return 6;
  }

  // Step 7 : Retrieve modifiers of a Functional Specification
  CATIListOfCATIFmoFunctionalSpecification * pListFunctionalProtected = NULL;
 
  piProtectedFunctionalSet -> GetDirectFunctionalSpec (&pListFunctionalProtected);
  if (pListFunctionalProtected)
  {
    unsigned int Size = 0;
    if (SUCCEEDED (pListFunctionalProtected -> Count (&Size)))
    {
      for (unsigned int i = 0; i < Size; i++) 
      {
        CATIFmoFunctionalSpecification * pFunctionalSpec = NULL;
        if (SUCCEEDED (pListFunctionalProtected -> Item (i, &pFunctionalSpec)) && pFunctionalSpec)
        {
          CATIListOfCATIFmoFunctionalSpecification * pListFunctionalModifier = NULL;
          if (SUCCEEDED (pFunctionalSpec -> GetLocalModifiers (&pListFunctionalModifier)))
          {
            if (pListFunctionalModifier)
            {
              pListFunctionalModifier -> Release();
              pListFunctionalModifier = NULL;
            }
          }
          else
          {
            return 7;
          }

          CATIListOfCATIFmoFunctionalSpecification * pListFunctionalModified = NULL;
          if (SUCCEEDED (pFunctionalSpec -> GetModifiedFeatures (&pListFunctionalModified)))
          {
            if (pListFunctionalModified)
            {
              pListFunctionalModified -> Release();
              pListFunctionalModified = NULL;
            }
          }
          else
          {
            return 7;
          }

          pFunctionalSpec -> Release(); 
          pFunctionalSpec = NULL;
        }
      }
    }
 
    pListFunctionalProtected -> Release();
    pListFunctionalProtected = NULL;
  }

  // Clean
  if (piShellableFunctionalSet)
  {
    piShellableFunctionalSet -> Release();
    piShellableFunctionalSet = NULL;
  }
  if (piInternalFunctionalSet)
  {
    piInternalFunctionalSet -> Release();
    piInternalFunctionalSet = NULL;
  }
  if (piExternalFunctionalSet)
  {
    piExternalFunctionalSet -> Release();
    piExternalFunctionalSet = NULL;
  }
  if (piProtectedFunctionalSet)
  {
    piProtectedFunctionalSet -> Release();
    piProtectedFunctionalSet = NULL;
  }
  if (piShellableFunctionalSetImport)
  {
    piShellableFunctionalSetImport -> Release();
    piShellableFunctionalSetImport = NULL;
  }
  if (piInternalFunctionalSetImport)
  {
    piInternalFunctionalSetImport -> Release();
    piInternalFunctionalSetImport = NULL;
  }
  if (piExternalFunctionalSetImport)
  {
    piExternalFunctionalSetImport -> Release();
    piExternalFunctionalSetImport = NULL;
  }
  if (piProtectedFunctionalSetImport)
  {
    piProtectedFunctionalSetImport -> Release();
    piProtectedFunctionalSetImport = NULL;
  }

  // Step 8 - Saves the FinalPart with the Functional imports

  // Saves in the input path
  HRESULT oRc = E_FAIL;
  char * nomPart = iArgv[3];
  oRc = CATDocumentServices::SaveAs (*pFinalDoc, nomPart);
  if (!SUCCEEDED (oRc))
  {
    return 8;
  }

  // Closes the documents
  oRc = CATDocumentServices::Remove (*pInitialDoc);
  if (!SUCCEEDED (oRc))
  {
    return 9;
  }
  oRc = CATDocumentServices::Remove (*pFinalDoc);
  if (!SUCCEEDED (oRc))
  {
    return 9;
  }
 
  // Step 9 - Closes the session   
  oRc = ::Delete_Session ("SampleSession"); 
  if (!SUCCEEDED (oRc))
  {
    rc = 10;
  }
  else
  {
    rc = 0;
  }
  return rc;
}
