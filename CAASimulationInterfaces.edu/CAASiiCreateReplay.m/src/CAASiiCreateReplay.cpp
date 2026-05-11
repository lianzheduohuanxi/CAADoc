/**
 * @fullreview ABB LJE 01:07:12
 *
 * @quickreview LJE 01:09:11
 * @quickreview awn 04:02:03
 * @quickreview awn 04:04:07
 * @quickreview awn 04:04:15
 * @quickreview awn 05:11:16
 */
 // COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which creates a motion of a product in a new replay to be created in a *.CATProduct document
//
//  Illustrates :
//     Document loading in session
//     Create a replay within document
//     Create the motion within a replay
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAASiiCreateReplay inputDirectory inputFile.CATProduct outputDirectory
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
//     3 : Simulation error
//     4 : Problem in storing the file
//
//============================================================================================

// Header
#include "CAASiiCreateReplay.h"

// Standard C++ library
#include <iostream.h>

// System Frameworks
#include "CATBaseUnknown.h"
#include "CATString.h"

// Access to documents Frameworks
#include "CATLib.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATSession.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIDocRoots.h"

// Product Structure Frameworks
#include "CATIProduct.h"

// Simulation Frameworks
#include "CATIReplayFactory.h"
#include "CATIReplay.h"
#include "CATIReplayChannelProductMoveFactory.h"
#include "CATIReplayChannelProductMove.h"

int main (int argc, char * argv[] )
{ 
  int iError = 1;

  cout << "################################################" << endl;
  cout << "#                                              #" << endl;
  cout << "#             Creation of a replay             #" << endl;
  cout << "#                                              #" << endl;
  cout << "################################################" << endl << endl;
  
  if(4 != argc) 
  {
    cout << "Usage: CAASiiCreateReplay inputDirectory inputFile.CATProduct outputDirectory"<< endl;
    return (iError);
  }
  CATString inputName(argv[2]);
  CATString suffix = inputName.SubString(inputName.GetLengthInChar()-11,11);
  if (0 != suffix.compare(".CATProduct")) 
  {
    cout << "inputFile is not a CATProduct"<< endl;
    return (iError);
  }

  char inputPath[CATMaxPathSize];
  CATMakePath (argv[1], argv[2], inputPath);
  CATUnicodeString FilePath(inputPath);

  char outputPath[CATMaxPathSize]; 
  CATMakePath (argv[3], argv[2], outputPath);
  CATUnicodeString OutputPath(outputPath);

  CAASiiCreateReplay MyClass;

  iError = MyClass.CreateReplay(FilePath,OutputPath);

  return (iError);
}


//============================================================================================
// Constructor
//============================================================================================
CAASiiCreateReplay::CAASiiCreateReplay()
{}

//============================================================================================
// Destructor
//============================================================================================
CAASiiCreateReplay::~CAASiiCreateReplay()
{}


//============================================================================================
// 1 - Create a V5 session in memory
// 2 - Load input *.CATProduct and make it ready
// 3 - Simulate the parsing
// 4 - Create a replay in the document
// 5 - Create a channel for each product and fill it
// 6 - save the document
//============================================================================================

int CAASiiCreateReplay::CreateReplay( const CATUnicodeString& iProduct,
                                      const CATUnicodeString& iOutput)
{
  int iError = 2;// can not load the file

  //==========================================================================================
  // 1 - Create a V5 session in memory
  //==========================================================================================
  HRESULT HR = E_FAIL;
  CATSession* pSession = NULL;
  HR = Create_Session("CAASiiCreateReplaySession", pSession);
  if (FAILED(HR) || (NULL == pSession))
  {
    cout << "Session could not be created"<< endl;
    return(iError);
  }

  //==========================================================================================
  // 2 - Load input *.CATProduct and make it ready
  //==========================================================================================
  CATDocument* pDocument = NULL;
  HR = CATDocumentServices::OpenDocument(iProduct, pDocument);
  if (FAILED(HR) || (NULL == pDocument)) 
  {
    cout << iProduct.ConvertToChar() << " could not be loaded"<< endl;
    return(iError);
  }

  //==========================================================================================
  // 3 - Simulate the parsing
  //==========================================================================================
  const int numberOfProducts = 1;
  CATIProduct* piProductOnProduct[numberOfProducts] = {NULL};
  int numberOfSamples[numberOfProducts] = {4};
  double inputTime[numberOfProducts][4] = { 1., 2., 3., 7.};
  double inputProductMove[numberOfProducts][4][12] = {1.,0.,0.,0.,1.,0.,0.,0.,1,10.,0.,0.,
                                                      1.,0.,0.,0.,1.,0.,0.,0.,1,20.,0.,0.,
                                                      1.,0.,0.,0.,1.,0.,0.,0.,1,50.,0.,0.,
                                                      1.,0.,0.,0.,1.,0.,0.,0.,1,99.,0.,0.};

  // Initialize the product
  CATIDocRoots* piDocRootsOnDocument = NULL;
  HR = pDocument->QueryInterface(IID_CATIDocRoots,(void**)&piDocRootsOnDocument);
  if (SUCCEEDED(HR))
  {
    // Search the root product
    CATIProduct* piProductOnRootProduct = NULL;
    CATListValCATBaseUnknown_var* pRootList = piDocRootsOnDocument->GiveDocRoots();
    if (NULL != pRootList) 
    {
      int nRoots = pRootList->Size();
      CATBaseUnknown* pBUTmp = NULL;
      for (int j = 1; j <= nRoots && NULL == piProductOnRootProduct; j++)
      {
        pBUTmp = (*pRootList)[j];
        if(pBUTmp)
        {
          HR = pBUTmp->QueryInterface(IID_CATIProduct,(void**)&piProductOnRootProduct);
        }
      }
      // Search the first product
      if (NULL != piProductOnRootProduct)
      {
        CATListValCATBaseUnknown_var* pProductList = piProductOnRootProduct->GetChildren("CATIProduct");
        if (NULL != pProductList) 
        {
          int nProducts = pProductList->Size();
          if (nProducts >= numberOfProducts)
          {
            CATBaseUnknown* pBUProduct = NULL;
            for (int i = 1; i <= numberOfProducts; i++)
            {
              pBUProduct = (*pProductList)[i];
              if(pBUProduct)
              {
                HR = pBUProduct->QueryInterface(IID_CATIProduct,(void**)&piProductOnProduct[i-1]);
              }
              if (FAILED(HR)) piProductOnProduct[i-1] = NULL;
            }
          }
          delete pProductList;
          pProductList = NULL;
        }

        piProductOnRootProduct->Release();
        piProductOnRootProduct = NULL;
      }
      delete pRootList;
      pRootList = NULL;
    }
    piDocRootsOnDocument->Release();
    piDocRootsOnDocument = NULL;
  }

  //==========================================================================================
  // 4 - Create a replay in the document
  //==========================================================================================
  // Search for the factory of replays

  CATIReplayFactory* piReplayFactory = NULL;
  HR = pDocument->QueryInterface(IID_CATIReplayFactory,(void**)&piReplayFactory);
  if (SUCCEEDED(HR)) 
  {
    // Create the replay
    CATIReplay* piReplay = NULL;
    HR = piReplayFactory->CreateInstance (&piReplay);
    if (SUCCEEDED(HR)) 
    {
      // Search for the factory of channels
      CATIReplayChannelProductMoveFactory* piReplayChannelProductMoveFactory = NULL;
      HR = piReplay->QueryInterface(IID_CATIReplayChannelProductMoveFactory,(void**)&piReplayChannelProductMoveFactory);
      if (SUCCEEDED(HR)) 
      {
        for (int j = 0; j < numberOfProducts; j++)
        {

          //====================================================================================
          // 5 - Create a channel for each product and fill it
          //====================================================================================
          CATIReplayChannelProductMove* piReplayChannelProductMove = NULL;
          HR = piReplayChannelProductMoveFactory->CreateInstance ((CATBaseUnknown**)&piProductOnProduct[j],&piReplayChannelProductMove);
          if (SUCCEEDED(HR)) 
          {
            // Create the samples
            for (int i = 0; i < numberOfSamples[j] && SUCCEEDED(HR); i++)
            {

              HR = piReplayChannelProductMove->AddSample (inputTime[j][i], inputProductMove[j][i]);
            }
            // Release the reference to the channel
            piReplayChannelProductMove->Release();
            piReplayChannelProductMove = NULL;
          }
          // Release the reference to the product
          piProductOnProduct[j]->Release();
          piProductOnProduct[j] = NULL;
        }
        // Release the reference to the factory
        piReplayChannelProductMoveFactory->Release();
        piReplayChannelProductMoveFactory = NULL;
      }
      // Release the reference to the replay
      piReplay->Release();
      piReplay = NULL;
    }
    piReplayFactory->Release();
    piReplayFactory = NULL;
  }

  //==========================================================================================
  // 6 - save the document
  //==========================================================================================
  HR = CATDocumentServices::SaveAs(*pDocument, iOutput);
  if (FAILED(HR))
  {
    cout << iOutput.ConvertToChar() << " could not be stored"<< endl;
    return(iError);
  }
 
  
  HR = CATDocumentServices::Remove(*pDocument);
  // End session
  Delete_Session("CAASiiCreateReplaySession");
  if (SUCCEEDED(HR))
  {
    iError = 0;
  }
  else
  {
    iError = 3;
  }
  return(iError);
}
