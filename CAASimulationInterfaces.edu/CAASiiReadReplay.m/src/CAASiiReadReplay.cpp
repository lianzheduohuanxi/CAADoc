/**
 * @fullreview PVO LJE 01:07:17
 * @quickreview awn 04:02:03
 * @quickreview awn 04:04:07
 * @quickreview awn 04:04:15
 * @quickreview awn 06:03:08
 * @quickreview sha 17:09:20
 */
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which reads the motion of products in existing replays contained in a *.CATProduct
//  document and write the related data in a text file.
//
//  Illustrates :
//     Document loading in session
//     Access to a replay within document
//     Access to the motion within a replay
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAASiiReadReplay inputDirectory inputFile.CATProduct outputDirectory
//
//  Inputs      :
//     inputDirectory        : directory containing the file
//     inputFile.CATProduct  : name of the file
//     outputDirectory       : directory which will contain the output text file
//
//  Return Code :
//     0 : OK
//     1 : Bad input (argument number or file)
//     2 : Problem in loading the file
//     3 : Simulation error
//
//============================================================================================

// Header
#include "CAASiiReadReplay.h"

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
#include "CATSession.h"
#include "LifeCycleObject.h"

// Product Structure Frameworks
#include "CATIProduct.h"
#include "CATIAlias.h"

// Simulation Frameworks
#include "CATIReplayFactory.h"
#include "CATIReplayChannel.h"
#include "CATIReplayChannelProductMove.h"
#include "CATIReplay.h"
#include "CATIReplayList.h"



int main (int argc, char * argv[] )
{ 
  int iError = 1;

  cout << "################################################" << endl;
  cout << "#                                              #" << endl;
  cout << "#             Reading a replay                 #" << endl;
  cout << "#                                              #" << endl;
  cout << "################################################" << endl << endl;
  
  if(4 != argc) 
  {
    cout << "Usage: CAASiiReadReplay inputDirectory inputFile.CATProduct outputDirectory"<< endl;
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


  CATString name = inputName.SubString(0,inputName.GetLengthInChar()-11) + ".txt";
  char outputPath[CATMaxPathSize]; 
  CATMakePath (argv[3], name.ConvertToChar(), outputPath);
  CATUnicodeString Output(outputPath);

  CAASiiReadReplay MyClass;

  iError = MyClass.ReadReplay(FilePath,Output);

  return (iError);
}

//============================================================================================
// Constructor
//============================================================================================
CAASiiReadReplay::CAASiiReadReplay()
{}

//============================================================================================
// Destructor
//============================================================================================
CAASiiReadReplay::~CAASiiReadReplay()
{}

//============================================================================================
// 1 - Create a V5 session in memory
// 2 - Load input *.CATProduct and make it ready
// 3 - Open the output file
// 4 - Read all the replays of the document
// 5 - Read all the channels of the replay
// 6 - Filter the product motion channels
// 7 - Read product, time, position of all the samples of the channel and print the data
//============================================================================================

int CAASiiReadReplay::ReadReplay(const CATUnicodeString& iProduct,
                                 const CATUnicodeString& iOutput)
{
  int iError = 2;// can not load the file

  //==========================================================================================
  // 1 - Create a V5 session in memory
  //==========================================================================================
  HRESULT HR = E_FAIL;
  CATSession* pSession = NULL;
  HR = Create_Session("CAASiiReadReplaySession", pSession);
  if (FAILED(HR) || (NULL == pSession)) 
  {
    cout << "Session could not be created"<< endl;
    return(iError);
  }
  CATDocument* pDocument = NULL;
  HR = CATDocumentServices::OpenDocument(iProduct, pDocument);
  if (FAILED(HR) || (NULL == pDocument)) {
    cout << iProduct.ConvertToChar() << " could not be loaded"<< endl;
    return(iError);
  }


  
  //==========================================================================================
  // 3 - Open the output file
  //==========================================================================================
  char outputPath[CATMaxPathSize]; 
  strcpy(outputPath,iOutput.ConvertToChar());
  ofstream outputFile;
  outputFile.open (outputPath, ios::out);
  outputFile << "Product_motions_from " << iProduct.ConvertToChar() << endl << flush;

  //==========================================================================================
  // 4 - Read all the replays of the document
  //==========================================================================================
  // Search for the factory of replays
  CATIReplayFactory* piReplayFactory = NULL;
  HR = pDocument->QueryInterface(IID_CATIReplayFactory,(void**)&piReplayFactory);
  if (SUCCEEDED(HR)) {
    // List the replays
    CATIReplayList* piListOfReplays = new CATIReplayList();
    HR = piReplayFactory->ListReplays (piListOfReplays);
    if (SUCCEEDED(HR)) 
    {
      CATIReplay* piReplay = NULL;
      for (int i = 1; i <= piListOfReplays->Size(); i++) 
      {
        piReplay = (*piListOfReplays)[i];
        if (piReplay) 
        {
          //==================================================================================
          // 5 - Read all the channels of the replay
          //==================================================================================
          int numberOfChannel = 0;
          HR = piReplay->GetNumberOfChannel(&numberOfChannel);
          if (SUCCEEDED(HR)) 
          {
            // Print the name of the replay
            CATIAlias* piAliasOnReplay = NULL;
            if (SUCCEEDED(piReplay->QueryInterface(IID_CATIAlias,(void**)&piAliasOnReplay)) && (NULL != piAliasOnReplay)) {
              outputFile << "Replay " << piAliasOnReplay->GetAlias().ConvertToChar() <<endl << flush;
              piAliasOnReplay->Release();
              piAliasOnReplay = NULL;
            }
            // Loop on all channels
            for (int j = 1; j <= numberOfChannel; j++)
            {
              //==============================================================================
              // 6 - Filter the product motion channels
              //==============================================================================
              CATIReplayChannel* piChannel = NULL;
              HR = piReplay->GetChannel(j, &piChannel);
              if (SUCCEEDED(HR) && (NULL != piChannel))
              {
                CATIReplayChannelProductMove* piProductMoveChannel = NULL;
                HR = piChannel->QueryInterface(IID_CATIReplayChannelProductMove,(void**)&piProductMoveChannel);
                if (SUCCEEDED(HR))
                {
                  //==========================================================================
                  // 7 - Read product, time, position of all the samples of the channel and print the data
                  //==========================================================================
                  CATIProduct* piProduct = NULL;
                  HR = piProductMoveChannel->GetProduct((CATBaseUnknown**)&piProduct);
                  if (SUCCEEDED(HR)) 
                  {
                    CATIAlias* piAliasOnProduct = NULL;
                    HR = piProduct->QueryInterface(IID_CATIAlias,(void**)&piAliasOnProduct);
                    if (SUCCEEDED(HR)) 
                    {
                      // Print the name of the product
                      outputFile << "   Product " << piAliasOnProduct->GetAlias().ConvertToChar() <<endl << flush;
                      piAliasOnProduct->Release();
                      piAliasOnProduct = NULL;
                      // Loop on the samples 
                      int numberOfSample = 0;
                      HR = piProductMoveChannel->GetNumberOfSample(&numberOfSample);
                      for (int k = 1; k <= numberOfSample; k++) 
                      {
                        // Print sample information
                        double time;
                        HR = piProductMoveChannel->GetSampleTime(k, &time);
                        double productMove[12];
                        HR = piProductMoveChannel->GetSample(k, productMove);
                        outputFile << "      " << time << " = ";
                        for (int l = 0; l < 12; l++) outputFile << productMove[l] << "; ";
                        outputFile << endl << flush;
                      }
                      outputFile << "   EndProduct" <<endl << flush; 
                    }
                    // Release the reference to the product
                    piProduct->Release();
                    piProduct = NULL;
                  }
                  // Release the reference to the product move channel
                  piProductMoveChannel->Release();
                  piProductMoveChannel = NULL;
                }
                // Release the reference to the channel
                piChannel->Release();
                piChannel = NULL;
              }
            }
            outputFile << "EndReplay" <<endl << flush;
          }
          // Release the reference to the replay
          piReplay->Release();
          piReplay=NULL;
          (*piListOfReplays)[i] = NULL;
        }
      }
    }
    // Clean the list
    delete piListOfReplays;
    piListOfReplays = NULL;
    piReplayFactory->Release();
    piReplayFactory = NULL;
  }

  // Close the output file
  outputFile.close();


  HR = CATDocumentServices::Remove(*pDocument);
  // End session
  Delete_Session("CAASiiReadReplaySession");
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


