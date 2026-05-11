//============================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Aerospace Sheet Metal Design
// Mission         : 
//
//                   - Open an input Part     ( including at least the Sheet Metal Parameters )
//                   - Create a Web Feature   ( or retrieve the Web if it exists in the input Part )
//                   - Set the Web parameters ( specified in an input ".txt" file )
//                   - Update the Web 
//                   - Save the result in an output Part 
//
// Type		         : Batch program
//
// Inputs	         : Path to a ".txt" file describing input data
//
// Outputs         : Return code is 0 if program worked ok, > 0 otherwise
//	 
// Illustrates     :  
//                   o How to Open a Part Document
//                   o How to use the CAA Aerospace Sheet Metal factory to create a Web
//                   o How to use the CAA Aerospace Sheet Metal Web Interface to set the Web parameters
//                   o How to Save a Part Document  
//
// To run the sample :
//  
//     CAAStmWeb InputDataPath
//
//                  where InputDataPath is a path to a ".txt" file with the following format
//
//                  # Comment
//
//                  KEYWORD:
//                  data
//                  KEYWORD:
//                  data
//                  data
//                  ...
//
//                  Available KEYWORD values :
//
//                  INPUT:            (mandatory                   : a path to a ".CATPart" file)
//                  OUTPUT:           (mandatory except if DISPLAY : a path to a ".CATPart" file)
//                  LENGTHUNIT:       (mandatory                   : "mm" (millimeter) or "in" (inch)
//                  DISPLAY:          (optional                    : a Web must exist in the input Part )
//                  SUPPORT:          (mandatory if creation : i.e. : Plane.1 ... )
//                  BOUNDARY:         (optional              : i.e. : Fill.1 ...  )
//                                    (                        !!! if no BOUNDARY : Support must be a closed Sketch)
//                  MATERIALORIENT:   (optional              : + (default), -)
//    
// i.e. :
// 
//   CAAStmWeb E:\tmp\CAATestCreateWeb.txt
//
//   ====> File CAATestCreateWeb.txt ( delivered in : Data.d )
//
//         #
//         # Create Web : general case : Support + Boundary.
//         #
//
//         INPUT:
//         E:\tmp\CAATestBasicGeometry.CATPart
//         OUTPUT:
//         E:\tmp\CAAResultCreateWeb.CATPart
//         LENGTHUNIT:
//         mm
//         SUPPORT:
//         Plane.1
//         BOUNDARY:
//         Extrude.1
//         Fill.1
//         Sketch.4
//         Sketch.3
//         MATERIALORIENT:
//         +
//
//   CAAStmWeb E:\tmp\CAATestDisplayWeb.txt
//
//   ====> File CAATestDisplayWeb.txt ( delivered in : Data.d )
//
//         #
//         # Shows the Web current entries.
//         #
//
//         INPUT:
//         E:\tmp\CAATestBasicGeometry.CATPart
//         LENGTHUNIT:
//         mm
//         DISPLAY:
//
//  Return code:
//  
//                  0 : successful execution
//                  1 : bad number of arguments
//                  2 : Document creation problem
//                  3 : Document deletion problem
//                  4 : Part Save problem
//                  5 : Web creation problem
//
//============================================================================================
#include "iostream.h"

#include "CAAStmServices.h"
#include "CAAStmInputData.h"

#include "CATSession.h" 
#include "CATDocument.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"

#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATTopDefine.h"

#include "CATInit.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

#include "CATIAerospaceSheetMetalFactory.h"
#include "CATIStmWeb.h"

// -----------------------------------------------------------------------------
// Main 
// Test : Create a Web
// -----------------------------------------------------------------------------

int main(int iArgc, char * iArgv[])
	{
	int RetCode = 0;
	HRESULT rc  = S_OK;
	
  CAAStmServices  CAASmaTools;
  CAAStmInputData CAAWebInput;

  cout << endl;    
  cout << "================================================================================" << endl;
  cout << "=========        Batch : Start Web creation or modification            =========" << endl;
  cout << "================================================================================" << endl;
  cout << endl;

  // ----------------------------------------------------------------------------
  // USE CASE 
  // ----------------------------------------------------------------------------
	
  // Find and analyse Input Data :  
  CATUnicodeString InputDataFilePath = iArgv[1];

  cout << endl;
	cout << "(CAAStmWeb) InputDataFile : "<< InputDataFilePath.ConvertToChar() << endl;
  cout << endl;
  
  rc = CAASmaTools.AnalyseWebInputData (InputDataFilePath, CAAWebInput);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(CAAStmWeb) ERROR : bad input arguments." << endl;
    cout << endl;
    RetCode  = 1 ;
    }
   
  // create a session
  char *       pSessionName = "CAAStmWeb";
  CATSession * pSession     = NULL; 
    
  rc = Create_Session (pSessionName, pSession); 
    
  if(FAILED(rc))
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmWeb) ERROR : Create Session has FAILED" << endl;
    cout << endl;
    exit(RetCode);
    }
    
  // Load the input Document
  CATDocument * pDocument = NULL; 
    
  rc = CATDocumentServices::OpenDocument(CAAWebInput.GetInputPartPath().ConvertToChar(), pDocument);
    
  if(NULL == pDocument)
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmWeb) ERROR : Open Document has FAILED." << endl;
    cout << endl;
    exit(RetCode);
    }
    
  cout <<" (CAAStmWeb) The Input Document " << CAAWebInput.GetInputPartPath().ConvertToChar() << " is opened." << endl;

  // Interfaces to manage Aerospace Sheet Metal Features :

  CATIAerospaceSheetMetalFactory *  piAslFactory  = NULL;  // ASM Factory
  CATISpecObject_var                 spPrtPartSpec;         // Part Feature
  CATISpecObject *                   piWebSpec     = NULL;  // Web Feature
  CATIStmWeb *                       piStmWeb      = NULL;  // Web public interface

  // Retrieve the Part Feature and the Aerospace Sheet Metal Factory :
  CATInit * piInit = NULL;
  
  rc = pDocument -> QueryInterface(IID_CATInit , (void**)& piInit);

  if(SUCCEEDED(rc))
    {
    CATIPrtContainer * piPrtCont = (CATIPrtContainer *) piInit -> GetRootContainer("CATIPrtContainer");
    
    if(NULL != piPrtCont)
      { 
      spPrtPartSpec = piPrtCont -> GetPart(); 
    
      if(NULL_var != spPrtPartSpec)
        {
        cout << endl;
        cout <<" (CAAStmWeb) Part Feature is OK." << endl;
        cout << endl;

        rc = piPrtCont -> QueryInterface(IID_CATIAerospaceSheetMetalFactory, (void **)& piAslFactory);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmWeb) Aerospace Sheet Metal Factory retrieved in the Input Part." << endl;
          cout << endl;
          } 
        else
          {
          cout << endl;
          cout <<" (CAAStmWeb) ERROR : Aerospace Sheet Metal Factory NOT found." << endl;
          cout << endl;
          } 
        }
      else
        {
        cout << endl;
        cout <<" (CAAStmWeb) ERROR :  Part Feature NOT found in the Input Part." << endl;
        cout << endl;
        rc = E_FAIL;
        }

      piPrtCont -> Release();
      piPrtCont = NULL;
      }
    else
      {
      cout << endl;
      cout <<" (CAAStmWeb) ERROR : Feature Container NOT found in the Input Part." << endl;
      cout << endl;
      rc = E_FAIL;
      }
    
    piInit -> Release();
    piInit = NULL;
    }
  else
    {
    cout << endl;
    cout <<" (CAAStmWeb) ERROR : Init interface NOT found in the Input Part." << endl;
    cout << endl;
    rc = E_FAIL;
    }

  if(SUCCEEDED(rc) && (NULL != piAslFactory))  
    {     
    // Try to retrieve the Web Feature :
    rc = CAASmaTools.FindWeb (spPrtPartSpec, &piWebSpec);

    if(SUCCEEDED(rc))
      {
      cout << endl;
      cout <<" (CAAStmWeb) Web Feature retrieved in the Input Part." << endl;
      cout << endl;
      }
    else
      {
      if(CAAWebInput.GetDisplay())
        {
        RetCode = 2;
        cout << endl;
        cout <<" (CAAStmWeb) ERROR : NO Web to display." << endl;
        cout << endl;
        }
      else
        {
        // No Web found : creation of a new one
        rc = piAslFactory -> CreateWeb ((CATISpecObject *) spPrtPartSpec, &piWebSpec);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmWeb) NEW Web Feature creation is OK." << endl;
          cout << endl;
          }
        else
          {
          RetCode = 2;
          cout << endl;
          cout <<" (CAAStmWeb) ERROR : NEW Web Feature creation has failed." << endl;
          cout << endl;
          }
        }
      }
    }
  
  if(SUCCEEDED(rc) && (NULL != piWebSpec))  
    {
    // =================================
    //  Display the Web current entries
    // =================================
    if(CAAWebInput.GetDisplay())
      {
      rc = CAASmaTools.Display (piWebSpec);

      if(FAILED(rc))
        {
        RetCode = 2;
        cout << endl;
        cout <<" (CAAStmWeb) ERROR : Display the current Web entries has failed." << endl;
        cout << endl;
        }
      }
    else
      {
      cout << endl;
      cout << endl;
      cout << "    =========================== " << endl;
      cout << "    Set of the Web Parameters : " << endl;
      cout << "    =========================== " << endl;
      cout << endl;
      cout << endl;

      // retrieve a pointer on the Web public interface :
      
      rc = piWebSpec -> QueryInterface(IID_CATIStmWeb, (void **)& piStmWeb);
      }

    if(SUCCEEDED(rc) && (NULL != piStmWeb))  
      {
      // Support :
      // ---------
      if(SUCCEEDED(rc) && (CAAWebInput.GetSupportGeomToSet()))
        {
        // Search the Web Support input specification :
        CATISpecObject * pSupportSpec = NULL;

        rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAWebInput.GetSupportGeomName(), &pSupportSpec);

        if(SUCCEEDED(rc) && (NULL != pSupportSpec))  
          {
          // Set the Web Support :
          rc = piStmWeb -> SetSupport(pSupportSpec);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmWeb) Support is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmWeb) ERROR : set of the Support has FAILED." << endl;
            cout << endl;
            }
            
          pSupportSpec -> Release();
          pSupportSpec = NULL;
          }
        }
        
      // Boundary :
      // ----------        
      if(SUCCEEDED(rc) && (CAAWebInput.GetBoundaryToSet()))
        { 
        CATLISTP(CATISpecObject) LimitsSpecList;
        CATListOfInt ViewTypeList;
            
        // Search the Web Boundary input specifications :
        CATListOfCATUnicodeString LimitsGeomNameList;
        LimitsGeomNameList = CAAWebInput.GetLimitsGeomNameList();
        int NbLimits = LimitsGeomNameList.Size();

        if(NbLimits > 0)
          {
          rc = CAASmaTools.FindFeaturesInSpecTree (spPrtPartSpec, LimitsGeomNameList, LimitsSpecList);
        
          if(SUCCEEDED(rc))  
            {
            int NbLimitsSpecSpecs = LimitsSpecList.Size();               
            int iLimSpec = 1;
            for(; iLimSpec <= NbLimitsSpecSpecs; iLimSpec++)
              {
              ViewTypeList.Append(1);     // Folded View
              }

            // Set the Web Boundary :
            rc = piStmWeb -> SetBoundaryElements (LimitsSpecList, ViewTypeList);

            if(SUCCEEDED(rc))
              {
              cout << endl;
              cout << " (CAAStmWeb) Boundary is set." << endl;
              cout << endl;
              }
            else 
              {
              RetCode = 5; 
              cout << endl;
              cout << " (CAAStmWeb) ERROR : Set of the boundary specs has FAILED." << endl;
              cout << endl;
              }
                            
            CATISpecObject * pCurrentLimitSpec = NULL;
            for(iLimSpec = 1; iLimSpec <= NbLimitsSpecSpecs; iLimSpec++)
              {
              pCurrentLimitSpec = LimitsSpecList[iLimSpec];
              if(NULL != pCurrentLimitSpec)
                {
                pCurrentLimitSpec -> Release();
                pCurrentLimitSpec = NULL;
                }
              }
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmWeb) ERROR : Retrieve the geometric Boundary specs has FAILED." << endl;
            cout << endl;
            }
          }
        else
          {
          // Spec of Boundary not specified : Boundary is set with the Support :
          CATISpecObject * pSupportSpec = NULL;

          rc = piStmWeb -> GetSupport(&pSupportSpec);

          if(SUCCEEDED(rc) && (NULL != pSupportSpec))
            {
            LimitsSpecList.Append(pSupportSpec);
            ViewTypeList.Append(1);

            // Set the Web Boundary :            
            rc = piStmWeb -> SetBoundaryElements (LimitsSpecList, ViewTypeList);

            if(SUCCEEDED(rc))
              {
              cout << endl;
              cout << " (CAAStmWeb) Boundary is set." << endl;
              cout << endl;
              }
            else 
              {
              RetCode = 5; 
              cout << endl;
              cout << " (CAAStmWeb) ERROR : Set of the boundary specs has FAILED." << endl;
              cout << endl;
              }

            pSupportSpec -> Release();
            pSupportSpec = NULL;
            }
          }
        }
        
      // Support Material orientation :
      // ------------------------------         
      if(SUCCEEDED(rc) && (CAAWebInput.GetMaterialOrientToSet()))
        {
        rc = piStmWeb -> SetMaterialOrient(CAAWebInput.GetMaterialOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmWeb) Support Material orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmWeb) ERROR : Set of the Support Material orientation has FAILED." << endl;
          cout << endl;
          } 
        }
      }
    }
  else
    RetCode = 2;

  if(SUCCEEDED(rc) && (FALSE == CAAWebInput.GetDisplay()))  
    {
    // Update the Part : to force all internal impacted Specs by the Web to re-build

    rc = CAASmaTools.Update ((CATISpecObject *) spPrtPartSpec);
    
    if(SUCCEEDED(rc))
      {
      cout << endl;
      cout << " (CAAStmWeb) Update of the Web Feature is OK." << endl;
      cout << endl;
          
      // Save the Document 
      rc = CATDocumentServices::SaveAs (*pDocument, CAAWebInput.GetOutputPartPath().ConvertToChar());
            
      if(SUCCEEDED(rc))  
        {
        cout << endl; 
        cout <<" (CAAStmWeb) The Output Document " << CAAWebInput.GetOutputPartPath().ConvertToChar() << " is saved." << endl;
        cout << endl; 
        }
      else 
        {
        RetCode = 4; 
        cout << endl;
        cout << " (CAAStmWeb) ERROR : Save Document has FAILED." << endl;
        cout << endl;
        }
      }
    else
      {
      RetCode = 5; 
      cout << endl;
      cout << " (CAAStmWeb) ERROR : Update of the Web has FAILED." << endl;
      cout << endl;
      }
    }   
  
  // Releases on Interfaces :
  if(NULL != piAslFactory)
    {
    piAslFactory -> Release();
    piAslFactory = NULL;
    }
  if(NULL != piStmWeb)
    {
    piStmWeb -> Release();
    piStmWeb = NULL;
    }
  if(NULL != piWebSpec)
    {
    piWebSpec -> Release();
    piWebSpec = NULL;
    }

  // Close the document
  rc = CATDocumentServices::Remove (*pDocument);
    
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmWeb) ERROR : Remove Document has FAILED." << endl;
    cout << endl;
    }

  // End session
  rc = Delete_Session (pSessionName);
      
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmWeb) ERROR : Delete Session has FAILED." << endl;
    cout << endl;
    }

  cout << endl;
  cout << "================================================================================" << endl;
  cout << "=========        Batch : End Web creation or modification              =========" << endl;
  cout << "================================================================================" << endl;
  cout << endl;

  return RetCode ;
  }






