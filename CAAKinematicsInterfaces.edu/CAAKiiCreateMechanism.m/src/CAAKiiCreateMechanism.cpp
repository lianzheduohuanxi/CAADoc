/**
 * @quickReview SVV 03:01:16
 * @quickReview SVV 03:10:28
 * @quickReview SVV 04:01:07
 * @quickReview SVV 04:06:14
 * @quickReview SVV 04:08:17
 * @quickReview RKN 04:10:25
 */
/**
 * @fullreview JCS RKN EER 01:12:04
 * @error UDOO Y err_1 (.h) =/constructeur en private
 * @error MISC Y err_2 argc doit initialise a 0
 * @error UNP Y err_3 pDocument est rendu par une methode sure ?
 * @error MISC Y err_4 sortir le ->Size de la boucle
 * @error UNP Y err_5 tester (*pRootList)[j]
 * @error UNP Y err_6 Tester pProductList != NULL
 * @error UNP Y err_7 Tester memberList[k] != NULL
 * @error MISC Y err_8 spConnectorOnLine est deja un CATBaseUnknown
 * @error BCMM Y err_9 release des memberList[i] a faire
 * @error UDOO Y err_10 Mise a NULL de piDocumentAsMechanismFactory
*/
// --------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batc\h program which creates a mechanism in a *.CATProduct.
//
//  Illustrates :
//     Document loading in session
//     Creation of a mechanism within document
//     Creation of a commanded joint within the mechanism
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAAKiiCreateMechanism inputDirectory inputFile.CATProduct outputDirectory
//
//  Inputs      :
//     inputDirectory        : directory containing the file
//     inputFile.CATProduct  : name of the file
//     outputDirectory       : directory which will contain the file after modifications
//
//  Return Code :
//     0 : OK
//     1 : Bad input (argument number or file)
//     2 : Problem in loading the file
//     3 : Kinematics error
//
// If required, uncomment traces before building this sample
//============================================================================================
//  History:
//  --------
//  07/01/2004 : RKN : CATDocumentServices::Open method is deprecated, 
//               and replaced with CATDocumentServices::OpenDocument.
//  14/06/2004 : RKN : ListMembers is deprecated, the new method is ListMembersHere
//  17/08/2004 : EER : corrected MaxTime : modification in SaveAs Arguments
//  25/10/2004 : SVV : Switch from CATInteractiveApplication to Main() base batch.
//  
//============================================================================================

// Standard C++ library
#include <iostream.h>
#include <fstream.h>

// System Frameworks
#include "CATBaseUnknown.h"
#include "CATString.h"

// Access to documents Frameworks
#include "CATLib.h" 
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATIDocRoots.h"
#include "LifeCycleObject.h"

// Product Structure Frameworks
#include "CATIProduct.h"

// Kinematics Frameworks
#include "CATIKinMechanismFactory.h"
#include "CATIKinMechanism.h"
#include "CATIKinJoint.h"
#include "CATIKinCmd.h"
#include "CATKinDefs.h"

#include "CATLine.h"
#include "CATIContainerOfDocument.h"
// to create connector
#include "CATAsmConnectorServices.h"

#include "iostream.h"

//============================================================================================
// 1 - Check arguments
// 2 - Load the CATProduct and make it ready
// 3 - Search the geometries and associated connectors
// 4 - Create the mechanism
// 5 - Create the joint
// 6 - Create the length command
// 7 - Create the fixed product
// 8 - save the document
//============================================================================================

int main(int argc, char ** argv)
{
//==========================================================================================
// 1 - Check arguments
//==========================================================================================
  
  int returnCode = 0;
  
  if(4 != argc)
  {
    /*    cout << "Usage: CAAKiiCreateMechanism inputDirectory inputFile.CATProduct outputDirectory"<< endl; */
    returnCode = 1;
    return returnCode;
  }
  
  CATString inputName(argv[2]);
  CATString suffix = inputName.SubString(inputName.GetLengthInChar()-11,11);
  if (0 != suffix.compare(".CATProduct"))
  {
    /*    cout << "inputFile is not a CATProduct"<< endl; */
    returnCode = 1;
    return returnCode;
  }
  
//==========================================================================================
// 2 - Load the CATProduct and make it ready
//==========================================================================================
  char inputPath[CATMaxPathSize];
  CATMakePath (argv[1], argv[2], inputPath);
  
  HRESULT HR = E_FAIL;
  CATSession* pSession = NULL;
  HR = Create_Session("CAAKiiCreateMechanismSession", pSession);
  if (!SUCCEEDED(HR))
  {
    /*    cout << "Session could not be created"<< endl; */
    returnCode = 2;
    return returnCode;
  }
  CATDocument* pDocument = NULL;
  HR = CATDocumentServices::OpenDocument(inputPath, pDocument);
  if (!SUCCEEDED(HR))
  {
    /*    cout << inputPath << " could not be loaded"<< endl; */
    returnCode = 2;
    return returnCode;
  }
 
//==========================================================================================
// 3 - Search the geometries and associated connectors
//==========================================================================================
  // Search all the roots of the document
  CATIDocRoots* piDocRootsOnDocument = NULL;
  if (pDocument && SUCCEEDED(pDocument->QueryInterface(IID_CATIDocRoots, (void**)&piDocRootsOnDocument)))
  {
    CATListValCATBaseUnknown_var* pRootList = piDocRootsOnDocument->GiveDocRoots();
    if (NULL != pRootList)
    {
      // Search the root product
      CATIProduct* piProductOnRootProduct = NULL;
      CATBaseUnknown_var spProd_i_bu;
      int ListSize = pRootList->Size();
      for (int j = 1; j <= ListSize; j++)
      {
        spProd_i_bu = (*pRootList)[j];
        if (spProd_i_bu != NULL_var && 
            SUCCEEDED(spProd_i_bu->QueryInterface(IID_CATIProduct,(void**)&piProductOnRootProduct)))
        {
          break;
        }
      }
      delete pRootList;
      pRootList = NULL;
      
      // Get all the products of the root product
      int numberOfProducts = 0;
      int numberOfConnector = 0;
      const int maximumNumberOfConnector = 2;
      CATLISTP(CATBaseUnknown) iConnectorList;
      CATIProduct* piFixedProduct = NULL;
      if (piProductOnRootProduct)
      {
        CATListValCATBaseUnknown_var* pProductList = piProductOnRootProduct->GetAllChildren();
        if (pProductList)
        {
          numberOfProducts = pProductList->Size();
          
          // Search two valid lines in the products
          
          for (int i = 1; numberOfConnector < maximumNumberOfConnector && i <= numberOfProducts; i++)
          {
            // Search the product
            CATIProduct* piProductOnProduct = NULL;
            CATBaseUnknown_var spProduct_bu;
            spProduct_bu = (*pProductList)[i];
            if (spProduct_bu != NULL_var &&
              SUCCEEDED(spProduct_bu->QueryInterface(IID_CATIProduct,(void**)&piProductOnProduct)))
            {
              // retain first product to be set as fixed at the end
              if (i==1) 
              {
                piFixedProduct = piProductOnProduct;
                piFixedProduct->AddRef();
              }
              
              // Search the link to the shape representation associated with the product
              CATILinkableObject_var spLinkableOnShapeRep = NULL_var;
              if (SUCCEEDED(piProductOnProduct->GetShapeRep(spLinkableOnShapeRep)))
              {
                // Use the link the find the document containing the shape representation
                CATDocument* pShapeDocument = spLinkableOnShapeRep->GetDocument();
                if (NULL != pShapeDocument)
                {
                  // Find the container of the document
                  CATIContainerOfDocument* piContainerOfDocumentOnShapeDocument = NULL;
                  if (SUCCEEDED(pShapeDocument->QueryInterface(IID_CATIContainerOfDocument, (void**)&piContainerOfDocumentOnShapeDocument)))  {
                    // Find the container of the geometry
                    CATIContainer* piContainer = NULL;
                    piContainerOfDocumentOnShapeDocument->GetSpecContainer(piContainer);
                    piContainerOfDocumentOnShapeDocument->Release();
                    piContainerOfDocumentOnShapeDocument = NULL;
                    if (NULL != piContainer)
                    {
                      // List all geometrical entities and search the first line in the document
                      SEQUENCE(CATBaseUnknown_ptr) memberList;
                      // @CSC-Filter VIOI  mkCheckSource error filtered
                      piContainer->ListMembersHere(CATLine::ClassName (),memberList);
//                      SEQUENCE(CATBaseUnknown_ptr) memberList= piContainer->ListMembers(CATLine::ClassName ());
                      CATBaseUnknown* papiUnknownOnLineConnector = NULL;
                      CATBaseUnknown * pLine_bu = NULL;
                      int MembersSize = memberList.length();
                      int k = 0;
                      for (; NULL == papiUnknownOnLineConnector && k < MembersSize; k++)
                      {
                        // Filter the line
                        CATLine* piLine = NULL;
                        pLine_bu = memberList[k];
                        if (pLine_bu && 
                          SUCCEEDED(pLine_bu->QueryInterface(IID_CATLine,(void**)&piLine)))
                        {
                          CATILinkableObject_var spLinkableOnLine (memberList[k]);
                          if (NULL_var != spLinkableOnLine)
                          {
                            // Get the connector associated to the line
                            CATIConnector* spConnectorOnLine = NULL;
                            int xCreation = 0;
                            
                            HR = GetProductConnector(spLinkableOnLine, piProductOnProduct, piProductOnRootProduct, 0, spConnectorOnLine, xCreation);
                            //old: GetProductConnector(spLinkableOnLine,(*pProductList)[i],spRootProduct);//
                            if (spConnectorOnLine)
                            {
                              // Store the connector as a CATBaseUnknown
                              HR = spConnectorOnLine->QueryInterface(IID_CATBaseUnknown, (void**)&papiUnknownOnLineConnector);
                            }
                          }
                          piLine->Release();
                          piLine = NULL;
                        }
                      }
                      
                      for (k = 0; k < MembersSize; k++)
                      {
                        pLine_bu = memberList[k];
                        if (pLine_bu)
                        {
                          pLine_bu->Release();
                          pLine_bu = NULL;
                        }
                      }
                      
                      // Store the connector and the product corresponding to the line
                      if (NULL != papiUnknownOnLineConnector)  
                      {
                        iConnectorList.Append(papiUnknownOnLineConnector);
                        numberOfConnector++;
                        papiUnknownOnLineConnector->Release();
                        papiUnknownOnLineConnector = NULL;
                      }
                      piContainer->Release();
                      piContainer = NULL;
                    }
                  }
                }
              }
              piProductOnProduct->Release();
              piProductOnProduct = NULL;
            }
          }
          delete pProductList;
          pProductList = NULL;
        }
        piProductOnRootProduct->Release();
        piProductOnRootProduct = NULL;
      }
//======================================================================================
// 4 - Create the mechanism
//======================================================================================
      CATIKinMechanism* piMechanism = NULL;
      CATIKinMechanismFactory* piDocumentAsMechanismFactory = NULL;
      if (SUCCEEDED(pDocument->QueryInterface(IID_CATIKinMechanismFactory, (void**)&piDocumentAsMechanismFactory)))
      {
        if (SUCCEEDED(piDocumentAsMechanismFactory->CreateInstance(&piMechanism)))
        {
//====================================================================================
// 5 - Create the joint
//====================================================================================
          if (numberOfConnector == maximumNumberOfConnector)
          {
            // Cylindrical joint from connectors
            CATIKinJoint* piJoint = NULL;
            const char* jointType = CATKinCylindricalJoint;
            boolean iCreateConstraintsForJoint = 1;
            if (SUCCEEDED(piMechanism->AddJoint(jointType,&iConnectorList, iCreateConstraintsForJoint, &piJoint)))
            {
//============================================================================
// 6 - Create the length command
//============================================================================
              CATIKinCmd* piCmd = NULL;
              const char* cmdType = CATKinLengthCmd;
              if (SUCCEEDED(piMechanism->AddCommand(piJoint, cmdType, &piCmd)))
              {
                piCmd->Release();
                piCmd = NULL;
              }
              piJoint->Release();
              piJoint = NULL;
            }
          }
          
//====================================================================================
// 7 - Create the fixed product
//====================================================================================
          boolean iCreateConstraintsForFixed = 1;
          HR = piMechanism->SetFixedProduct(piFixedProduct,iCreateConstraintsForFixed);
          piFixedProduct->Release();
          piFixedProduct = NULL;
          piMechanism->Release();
          piMechanism = NULL;
        }
        piDocumentAsMechanismFactory->Release();
        piDocumentAsMechanismFactory = NULL;
      }
    }
    piDocRootsOnDocument->Release();
    piDocRootsOnDocument = NULL;
  }
  
//==========================================================================================
// 8 - save the document
//==========================================================================================
  char outputPath[CATMaxPathSize];
  CATMakePath (argv[3], argv[2], outputPath);
  HR = CATDocumentServices::SaveAs(*pDocument, outputPath,"",FALSE);
  if (!SUCCEEDED(HR))
  {
    /*    cout << outputPath << " could not be stored"<< endl; */
    returnCode = 4;
    return returnCode;
  }
  
  // Close the document
  LifeCycleObject *piLifeCycleOfDocument = NULL;
  HR = pDocument->QueryInterface(IID_LifeCycleObject,(void**)&piLifeCycleOfDocument);
  if (SUCCEEDED(HR))
  {
    piLifeCycleOfDocument->remove();
    piLifeCycleOfDocument->Release();
    piLifeCycleOfDocument = NULL;
  }
  
  // End session
  Delete_Session("CAAKiiCreateMechanismSession");
  
  if (SUCCEEDED(HR)) returnCode = 0;
  else returnCode = 3;

  return returnCode;
}
