/**
 * @fullreview ABB LJE 01:07:12
 * @quickReview KFE 04:04:07
 */
// --------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which computes the inertia of subassemblies of a product in a *.CATProduct document
//
//  Illustrates :
//     Document loading in session
//     Access to subassemblies within document
//     Computation of inertia data
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAASpaComputeInertia inputDirectory inputFile.CATProduct
//
//  Inputs      :
//     inputDirectory        : directory containing the file
//     inputFile.CATProduct  : name of the file
//
//  Return Code :
//     0 : OK
//     1 : Bad input (argument number or file)
//     2 : Problem in loading the file
//     3 : Computation error
//
//============================================================================================


#include <stdlib.h>
#include <stdio.h>

// Standard C++ library
#include <iostream.h>

// System Frameworks
#include "CATBaseUnknown.h"
#include "CATString.h"


// Access to documents Frameworks
#include "CATLib.h" 
#include "CATDocumentServices.h" 
#include "CATDocument.h"
#include "CATSessionServices.h"
#include "CATIDocRoots.h"
#include "LifeCycleObject.h"

// Product Structure Frameworks
#include "CATIProduct.h"
#include "CATIAlias.h"


// Space Analysis Frameworks
#include "CATIInertia.h"


#define CAA_SPA_INIT_ENV


#ifdef CAA_SPA_INIT_ENV  

#include "CATISpaEnvironment.h"

#endif


//============================================================================================
// 1 - Check arguments
// 2 - Load input *.CATProduct and make it ready
// 3 - Search the products
// 4 - Print the inertia data
//============================================================================================

int main(int iArgc, char ** iArgv)
{
  HRESULT HR_END = E_FAIL;


  int _returnCode = 3;
  //==========================================================================================
  // 1 - Check arguments
  //==========================================================================================
  if(3 != iArgc) 
  {
    cout << "Usage: CAASpaComputeInertia inputDirectory inputFile.CATProduct"<< endl;
    _returnCode = 1;
    return _returnCode;
  }

  CATString inputName(iArgv[2]);
  CATString suffix = inputName.SubString(inputName.GetLengthInChar()-11,11);
  if (0 != suffix.compare(".CATProduct")) 
  {
    cout << "inputFile is not a CATProduct"<< endl;
    _returnCode = 1;
    return _returnCode;
  }

  //==========================================================================================
  // 2 - Load input *.CATProduct and make it ready
  //==========================================================================================
  char inputPath[CATMaxPathSize]; 
  CATMakePath (iArgv[1], iArgv[2], inputPath);

  HRESULT HR = E_FAIL;
  CATSession* pSession = NULL;
  HR = Create_Session("CAASpaComputeInertiaSession", pSession);
  if (FAILED(HR)) 
  {
    cout << "Session could not be created"<< endl;
    _returnCode = 2;
    return _returnCode;
  }

  CATDocument* pDocument = NULL;
  HR = CATDocumentServices::OpenDocument(inputPath, pDocument);
  if (FAILED(HR)) 
  {
    cout << inputPath << " could not be loaded"<< endl;
    _returnCode = 2;
    return _returnCode;
  }


  HRESULT HR_Init = E_FAIL;

#ifdef CAA_SPA_INIT_ENV  

  HRESULT HR_Env = E_FAIL;

  CATISpaEnvironment * piSpaEnvironment = NULL;

  if (SUCCEEDED(HR))
  {
     HR_Env = pDocument->QueryInterface(IID_CATISpaEnvironment,(void**)&piSpaEnvironment);

     if (SUCCEEDED(HR_Env))
     {
        HR_Init = piSpaEnvironment->Init();
     }
  }
#endif
  //===============================================================================
  //===============================================================================

  if (SUCCEEDED(HR_Init))
  {
      //==========================================================================================
      // 3 - Search the products
      //==========================================================================================
      CATIProduct* piProduct = NULL;
      CATIDocRoots* piDocRootsOnDocument = NULL;
      
      HR = pDocument->QueryInterface(IID_CATIDocRoots,(void**)&piDocRootsOnDocument);
      if (SUCCEEDED(HR)) 
      {
          // Search the root product
          CATIProduct* piRootProduct = NULL;
          CATListValCATBaseUnknown_var* pRootList = piDocRootsOnDocument->GiveDocRoots();
          if (NULL != pRootList) 
          {
              int nRoots = pRootList->Size();
              for (int i = 1; i <= nRoots && NULL == piRootProduct; i++) 
              {
                  HR = (*pRootList)[i]->QueryInterface(IID_CATIProduct,(void**)&piRootProduct);
              }
              // Search all children of the root product
              if (NULL != piRootProduct) 
              {
                  CATListValCATBaseUnknown_var* pProductList = piRootProduct->GetChildren("CATIProduct");
                  
                  //======================================================================================
                  if (NULL != pProductList) 
                  {
                      int nProducts = pProductList->Size();
                      
                      for (int j = 1; j <= nProducts; j++) 
                      {
                          HR = (*pProductList)[j]->QueryInterface(IID_CATIProduct,(void**)&piProduct);
                          if (SUCCEEDED(HR) && (NULL != piProduct)) 
                          {
                              //==============================================================================
                              // 4 - Print the inertia data
                              //==============================================================================
                              CATIInertia* piInertiaOnProduct = NULL;
                              HR = piProduct->QueryInterface(IID_CATIInertia,(void**)&piInertiaOnProduct);
                              
                              if (SUCCEEDED(HR)) 
                              {
                                  double density       = 0.;
                                  double mass          = 0;
                                  double position[3]   = {0,0,0};
                                  double matrix[9]     = {0,0,0,0,0,0,0,0,0};
                                  double components[9] = {0,0,0,0,0,0,0,0,0};
                                  double values[3]     = {0,0,0};
                                  
                                  HR = piInertiaOnProduct->GetInertia (&density,&mass, position, matrix, components, values);
                                  if (SUCCEEDED(HR)) 
                                  {
                                      
                                      cout <<"CATIInertia->GetInertia = "<<endl;
                                      cout <<"density = "<<density<<endl;
                                      cout <<"mass = "<<mass<<endl;
                                      cout <<"position = "<<position[0]<<"=="<<position[1]<<"=="<<position[2]<<endl;
                                      cout <<"matrix = "<<matrix[0]<<"=="<<matrix[1]<<"=="<<matrix[2]<<endl;
                                      cout <<"matrix = "<<matrix[3]<<"=="<<matrix[4]<<"=="<<matrix[5]<<endl;
                                      cout <<"matrix = "<<matrix[6]<<"=="<<matrix[7]<<"=="<<matrix[8]<<endl;
                                      cout <<"components = "<<components[0]<<"=="<<components[1]<<"=="<<components[2]<<endl;
                                      cout <<"components = "<<components[3]<<"=="<<components[4]<<"=="<<components[5]<<endl;
                                      cout <<"components = "<<components[6]<<"=="<<components[7]<<"=="<<components[8]<<endl;
                                      cout <<"values = "<<values[0]<<"=="<<values[1]<<"=="<<values[2]<<endl;
                                      cout <<"CATIInertia->GetInertia ==> END"<<endl;
                                      HR_END = S_OK;
                                      
                                      CATIAlias* piAliasOnProduct = NULL;
                                      HR = piProduct->QueryInterface(IID_CATIAlias,(void**)&piAliasOnProduct);
                                      if (SUCCEEDED(HR)) 
                                      {
                                          cout << "Product " << piAliasOnProduct->GetAlias().ConvertToChar() << " : mass = " << mass;   
                                          piAliasOnProduct->Release();
                                          piAliasOnProduct = NULL;
                                          if (density <= 0.) 
                                          {
                                              cout <<" with non homogeneous density" <<endl;
                                          }
                                          else 
                                          {
                                              cout << " with density = " << density <<endl;
                                          }
                                      }
                                  }
                                  // Release the reference to the inertia
                                  piInertiaOnProduct->Release(); 
                                  piInertiaOnProduct = NULL;
                              }
                              // Release the reference to the product  
                              piProduct->Release();
                              piProduct = NULL;
                          }
                      }
                      // Clean the product list
                      delete pProductList;
                      pProductList = NULL;
                  }
                  //======================================================================================
                  
                  // Release the reference to the root product
                  piRootProduct->Release();
                  piRootProduct = NULL;
            }
            // Clean the root list
            delete pRootList;
            pRootList = NULL;
        }
        // Release the reference to the doc roots
        piDocRootsOnDocument->Release();
        piDocRootsOnDocument = NULL;
    }
  }
  
#ifdef CAA_SPA_INIT_ENV  

  if (SUCCEEDED(HR_Env))
  {
      piSpaEnvironment->Clean();

      piSpaEnvironment->Release();
      piSpaEnvironment = NULL;
  }

#endif

  
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
  Delete_Session("CAASpaComputeInertiaSession");

  if ((SUCCEEDED(HR)) && (SUCCEEDED(HR_END)))
  {
      _returnCode = 0;
  }
  else
  {
      _returnCode = 3;
  }


  return _returnCode;
}




