//============================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Aerospace Sheet Metal Design
// Mission         : 
//                   
//                   - Open an input Part        ( including a Surfacic Flange or a Web )
//                   - Create or modify a Joggle Feature
//                   - Set the Joggle parameters ( specified in an input ".txt" file )
//                   - Update the Joggle 
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
//                   o How to use the CAA Aerospace Sheet Metal factory to create a Joggle
//                   o How to use the CAA Aerospace Sheet Metal Joggle Interface to set the Joggle parameters
//                   o How to Save a Part Document  
//
// To run the sample :
//  
//     CAAStmJoggle InputDataPath
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
//                  INPUT:            (mandatory             : a path to a ".CATPart" file)
//                  OUTPUT:           (mandatory             : a path to a ".CATPart" file)
//                  LENGTHUNIT:       (mandatory             : "mm" (millimeter) or "in" (inch)
//                  MODIFNAME:        (optional              : i.e : Joggle.2 )
//                  DISPLAY:          (optional   : the Surfacic Flange must exist in the input Part)
//
//                  SUPPORT:          (mandatory if creation : a Surfacic Flange or the Web)
//                  PLANE:            (mandatory if creation : a CATPlane or a planar Face)
//                  CLEARANCE:        (optional              : Length value)
//                  DEPTH:            (optional              : Length value : default : Thickness)
//                  DEPTHORIENT:      (optional              : + (default), -)
//                  RUNOUT            (optional              : Length Value : 3. * Depth (default formula))
//                  RUNOUTORIENT      (optional              : + (default), -)
//                  STARTRADIUS       (optional              : Length Value : Depth (default))
//                  ENDRADIUS         (optional              : Length Value : Depth (default))
//    
// i.e. :
// 
//   CAAStmJoggle E:\tmp\CAATestCreateJoggle.txt
//
//   ====> File CAATestCreateJoggle.txt : ( delivered in : Data.d )
//
//         #
//         # Create a Joggle on a Surfacic Flange 
//         #
//
//         INPUT:
//         E:\tmp\CAATestCreateJoggle.CATPart
//         OUTPUT:
//         E:\tmp\CAAResultCreateJoggle.CATPart
//         UNIT:
//         mm
//         SUPPORT:
//         Surfacic Flange.1
//         PLANE:
//         Plane.4
//         DEPTH:
//         10.
//         DEPTHORIENT:
//         +
//         RUNOUT:
//         20.
//         RUNOUTORIENT:
//         -
//         CLEARANCE:
//         1.5
//         STARTRADIUS:
//         5.
//         ENDRADIUS:
//         3.
//
//   CAAStmJoggle E:\tmp\CAATestDisplayJoggle.txt
//
//   ====> File CAATestDisplayJoggle.txt ( delivered in : Data.d )
//
//         #
//         # Shows Joggle current entries.
//         #
//
//         INPUT:
//         E:\tmp\CAATestModifyJoggle.CATPart
//         MODIFNAME:
//         Joggle.1
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
//                  5 : Joggle creation problem
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

#include "CATICkeParm.h"
#include "CATICkeRelation.h"

#include "CATIAerospaceSheetMetalFactory.h"
#include "CATIStmJoggle.h"

// -----------------------------------------------------------------------------
// Main 
// Test : Create a Joggle
// -----------------------------------------------------------------------------

int main(int iArgc, char * iArgv[])
	{
	int RetCode = 0;
	HRESULT rc  = S_OK;
	
  CAAStmServices   CAASmaTools;
  CAAStmInputData  CAAJoggleInput;

  cout << endl;    
  cout << "===================================================================================" << endl;
  cout << "=========        Batch : Start Joggle creation or modification            =========" << endl;
  cout << "===================================================================================" << endl;
  cout << endl;

  // ----------------------------------------------------------------------------
  // USE CASE 
  // ----------------------------------------------------------------------------
	
  // Find and analyse Input Data :  
  CATUnicodeString InputDataFilePath = iArgv[1];

  cout << endl;
	cout << "(CAAStmJoggle) InputDataFile : "<< InputDataFilePath.ConvertToChar() << endl;
  cout << endl;

  rc = CAASmaTools.AnalyseJoggleInputData (InputDataFilePath, CAAJoggleInput);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(CAAStmJoggle) ERROR : bad input arguments." << endl;
    cout << endl;
    RetCode  = 1 ;
    }
   
  // create a session
  char *       pSessionName = "CAAStmJoggle";
  CATSession * pSession     = NULL; 
    
  rc = Create_Session (pSessionName, pSession); 
    
  if(FAILED(rc))
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmJoggle) ERROR : Create Session has FAILED" << endl;
    cout << endl;
    exit(RetCode);
    }
    
  // Load the input Document
  CATDocument * pDocument = NULL; 
    
  rc = CATDocumentServices::OpenDocument(CAAJoggleInput.GetInputPartPath().ConvertToChar(), pDocument);
    
  if(NULL == pDocument)
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmJoggle) ERROR : Open Document has FAILED." << endl;
    cout << endl;
    exit(RetCode);
    }
    
  cout <<" (CAAStmJoggle) The Input Document " << CAAJoggleInput.GetInputPartPath().ConvertToChar() << " is opened." << endl;

  // Interfaces to manage Aerospace Sheet Metal Features :

  CATIAerospaceSheetMetalFactory *   piAslFactory      = NULL;     // ASM Factory
  CATISpecObject_var                  spPrtPartSpec;                // Part Feature
  CATISpecObject *                    piJoggleSpec      = NULL;     // Joggle Feature
  CATISpecObject *                    piPrevSupportSpec = NULL;     // Joggle Support BEFORE any modification
  CATIStmJoggle *                     piStmJoggle       = NULL;     // Joggle public interface

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
        cout <<" (CAAStmJoggle) Part Feature is OK." << endl;
        cout << endl;

        rc = piPrtCont -> QueryInterface(IID_CATIAerospaceSheetMetalFactory, (void **)& piAslFactory);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmJoggle) Aerospace Sheet Metal Factory retrieved in the Input Part." << endl;
          cout << endl;
          } 
        else
          {
          cout << endl;
          cout <<" (CAAStmJoggle) ERROR : Aerospace Sheet Metal Factory NOT found." << endl;
          cout << endl;
          } 
        }
      else
        {
        cout << endl;
        cout <<" (CAAStmJoggle) ERROR :  Part Feature NOT found in the Input Part." << endl;
        cout << endl;
        rc = E_FAIL;
        }

      piPrtCont -> Release();
      piPrtCont = NULL;
      }
    else
      {
      cout << endl;
      cout <<" (CAAStmJoggle) ERROR : Feature Container NOT found in the Input Part." << endl;
      cout << endl;
      rc = E_FAIL;
      }
    
    piInit -> Release();
    piInit = NULL;
    }
  else
    {
    cout << endl;
    cout <<" (CAAStmJoggle) ERROR : Init interface NOT found in the Input Part." << endl;
    cout << endl;
    rc = E_FAIL;
    }

  if(SUCCEEDED(rc) && (NULL != piAslFactory))  
    {     
    if(CAAJoggleInput.GetModifJoggle())
      {
      // Try to retrieve the Joggle Feature :
      rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAJoggleInput.GetModifJoggleName(), &piJoggleSpec);

      if(SUCCEEDED(rc))
        {
        cout << endl;
        cout <<" (CAAStmJoggle) Joggle Feature retrieved in the Input Part." << endl;
        cout << endl;
        }
      else
        {
        cout << endl;
        cout <<" (CAAStmJoggle) ERROR : Joggle Feature " << CAAJoggleInput.GetModifJoggleName().ConvertToChar() <<" NOT found." << endl;
        cout << endl;
        }
      }
    else
      {
      if(CAAJoggleInput.GetDisplay())
        {
        RetCode = 2;
        cout << endl;
        cout <<" (CAAStmWeb) ERROR : Joggle to display NOT found." << endl;
        cout << endl;
        }
      else
        {
        // creation of a new Joggle
        rc = piAslFactory -> CreateJoggle ((CATISpecObject *) spPrtPartSpec, &piJoggleSpec);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmJoggle) NEW Joggle Feature creation is OK." << endl;
          cout << endl;
          }
        else
          {
          cout << endl;
          cout <<" (CAAStmJoggle) ERROR : NEW Joggle Feature creation has failed." << endl;
          cout << endl;
          }
        }
      }
    }
  
  if(SUCCEEDED(rc) && (NULL != piJoggleSpec))  
    {
    if(CAAJoggleInput.GetDisplay())
      {
      rc = CAASmaTools.Display (piJoggleSpec);

      if(FAILED(rc))
        {
        RetCode = 2;
        cout << endl;
        cout <<" (CAAStmWeb) ERROR : Display the current Joggle entries has failed." << endl;
        cout << endl;
        }
      }
    else
      {
      cout << endl;
      cout << endl;
      cout << "    ============================== " << endl;
      cout << "    Set of the Joggle Parameters : " << endl;
      cout << "    ============================== " << endl;
      cout << endl;
      cout << endl; 

      // Retrieve a pointer on the Joggle public interface :
      
      rc = piJoggleSpec -> QueryInterface(IID_CATIStmJoggle, (void **)& piStmJoggle);
      }
        
    if(SUCCEEDED(rc) && (NULL != piStmJoggle))  
      {
      // Retrieve the previous Joggle Support to manage other Joggles on Support ( see : ManageOnSupport )
      
      HRESULT rcPrev = piStmJoggle -> GetSupport (&piPrevSupportSpec);

      // ==================
      //  Joggle Parameters
      // ==================
      
      // Support :
      // ---------
      if(CAAJoggleInput.GetSupportGeomToSet())
        {
        // Search the Support Geom input specification :
        CATISpecObject * pSupportGeomSpec = NULL;

        rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAJoggleInput.GetSupportGeomName(), &pSupportGeomSpec);

        if(SUCCEEDED(rc) && (NULL != pSupportGeomSpec))  
          {
          // Set the Support :
          rc = piStmJoggle -> SetSupport (pSupportGeomSpec);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmJoggle) Support is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmJoggle) ERROR : set of the Support has FAILED." << endl;
            cout << endl;
            }
            
          pSupportGeomSpec -> Release();
          pSupportGeomSpec = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : Specification of the Support NOT found." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
     
      // Joggle Plane :
      // --------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetPlaneGeomToSet()))
        {
        // Search the Joggle Plane Geom input specification :
        CATISpecObject * pPlaneGeomSpec = NULL;
      
        rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAJoggleInput.GetPlaneGeomName(), &pPlaneGeomSpec);
      
        if(SUCCEEDED(rc) && (NULL != pPlaneGeomSpec))  
          {
          // Set the Joggle Plane :
          rc = piStmJoggle -> SetPlane (pPlaneGeomSpec);
        
          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmJoggle) Joggle Plane is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmJoggle) ERROR : set of the Joggle Plane has FAILED." << endl;
            cout << endl;
            } 
        
          pPlaneGeomSpec -> Release();
          pPlaneGeomSpec = NULL;
          } 
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : Specification of the Joggle Plane NOT found." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // Depth Value :
      // -------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetDepthValueToSet()))
        { 
        CATICkeParm * piDepthValueParam = NULL;

        rc = piStmJoggle -> GetDepth (&piDepthValueParam);

        if(SUCCEEDED(rc) && (NULL != piDepthValueParam))
          {
          // Valuate the Literal :
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAJoggleInput.GetLengthUnit(),
                                                          CAAJoggleInput.GetDepthValue());  // MKS Units
 
          piDepthValueParam -> Valuate(MKSVal);         
        
          cout << endl;
          cout << " (CAAStmJoggle) Depth Value is set." << endl;
          cout << endl;

          piDepthValueParam -> Release();
          piDepthValueParam = NULL;
          } 
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : set of the Depth Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          } 
        }  

      // Depth Orientation :
      // -------------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetDepthOrientToSet()))
        { 
        rc = piStmJoggle -> SetDepthOrient (CAAJoggleInput.GetDepthOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmJoggle) Depth orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : Set of the Depth orientation has FAILED." << endl;
          cout << endl;
          } 
        } 

      // Runout Value :
      // --------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetRunoutValueToSet()))
        { 
        CATICkeParm * piRunoutValueParam = NULL;

        rc = piStmJoggle -> GetRunout (&piRunoutValueParam);

        if(SUCCEEDED(rc) && (NULL != piRunoutValueParam))
          {
          // Valuate the Literal :
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAJoggleInput.GetLengthUnit(),
                                                          CAAJoggleInput.GetRunoutValue());  // MKS Units

          piRunoutValueParam -> Valuate(MKSVal);
         
          // Inactivate the Formula if any :
          CATICkeRelation_var spRelation = piRunoutValueParam -> Relation();
          if(NULL_var != spRelation) 
            {
            if(spRelation -> IsActivated()) spRelation -> Desactivate();
            }          
        
          cout << endl;
          cout << " (CAAStmJoggle) Runout Value is set." << endl;
          cout << endl;

          piRunoutValueParam -> Release();
          piRunoutValueParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : set of the Runout Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 
    
      // Runout Orientation :
      // --------------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetRunoutOrientToSet()))
        { 
        rc = piStmJoggle -> SetRunoutOrient (CAAJoggleInput.GetRunoutOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmJoggle) Runout orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : Set of the Runout orientation has FAILED." << endl;
          cout << endl;
          } 
        }

      // Clearance Value :
      // -----------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetClearanceValueToSet()))
        { 
        CATICkeParm * piClearanceValueParam = NULL;

        rc = piStmJoggle -> GetClearance (&piClearanceValueParam);

        if(SUCCEEDED(rc) && (NULL != piClearanceValueParam))
          {
          // Valuate the Literal :
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAJoggleInput.GetLengthUnit(),
                                                          CAAJoggleInput.GetClearanceValue());  // MKS Units

          piClearanceValueParam -> Valuate(MKSVal);
       
          cout << endl;
          cout << " (CAAStmJoggle) Clearance Value is set." << endl;
          cout << endl;

          piClearanceValueParam -> Release();
          piClearanceValueParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : set of the Clearance Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
    
      // Start Radius Value :
      // --------------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetStartRadiusValueToSet()))
        { 
        CATICkeParm * piStartRadiusValueParam = NULL;

        rc = piStmJoggle -> GetStartRadius (&piStartRadiusValueParam);

        if(SUCCEEDED(rc) && (NULL != piStartRadiusValueParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAJoggleInput.GetLengthUnit(),
                                                          CAAJoggleInput.GetStartRadiusValue());  // MKS Units

          piStartRadiusValueParam -> Valuate(MKSVal);         
        
          cout << endl;
          cout << " (CAAStmJoggle) Start Radius Value is set." << endl;
          cout << endl;

          piStartRadiusValueParam -> Release();
          piStartRadiusValueParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : set of the Start Radius Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // End Radius Value :
      // ------------------
      if(SUCCEEDED(rc) && (CAAJoggleInput.GetEndRadiusValueToSet()))
        { 
        CATICkeParm * piEndRadiusValueParam = NULL;

        rc = piStmJoggle -> GetEndRadius (&piEndRadiusValueParam);

        if(SUCCEEDED(rc) && (NULL != piEndRadiusValueParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAJoggleInput.GetLengthUnit(),
                                                          CAAJoggleInput.GetEndRadiusValue());  // MKS Units

          piEndRadiusValueParam -> Valuate(MKSVal);         
        
          cout << endl;
          cout << " (CAAStmJoggle) End Radius Value is set." << endl;
          cout << endl;

          piEndRadiusValueParam -> Release();
          piEndRadiusValueParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : set of the End Radius Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
       
      if(SUCCEEDED(rc) && (FALSE == CAAJoggleInput.GetDisplay())) 
        { 
        //   Manage the Joggle impacted Features.
        //   A call to this method is mandatory BEFORE updating the Joggle.
        //
        //    - if the Support has been modified : 
        //      the Joggle will be removed from its Previous Support (if any).
        //    - if the Joggle Plane has been modified : 
        //      the Joggle will be inserted on the Support according with other Joggles (if any).
        //    - a new OFFSET Surface of the Support will be created if necessary.

        rc = piStmJoggle -> ManageOnSupport ((CATISpecObject *) spPrtPartSpec, piPrevSupportSpec);

        if(FAILED(rc))
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmJoggle) ERROR : Manage the Joggle internal Features has FAILED." << endl;
          cout << endl;
          }
        }
      }
    }
  else
    {
    rc      = E_FAIL;
    RetCode = 2;
    }
    
  if(SUCCEEDED(rc) && (FALSE == CAAJoggleInput.GetDisplay()))   
    {
    // Update the Part : to force all internal impacted Specs by the Joggle to re-build

    rc = CAASmaTools.Update ((CATISpecObject *) spPrtPartSpec);

    if(SUCCEEDED(rc))
      {
      cout << endl;
      cout << " (CAAStmJoggle) Update of the Joggle Feature is OK." << endl;
      cout << endl;

      // Save the Document 
    
      rc = CATDocumentServices::SaveAs (*pDocument, CAAJoggleInput.GetOutputPartPath().ConvertToChar());
            
      if(SUCCEEDED(rc))  
        {
        cout << endl; 
        cout <<" (CAAStmJoggle) The Output Document " << CAAJoggleInput.GetOutputPartPath().ConvertToChar() << " is saved." << endl;
        cout << endl; 
        }
      else 
        {
        RetCode = 4; 
        cout << endl;
        cout << " (CAAStmJoggle) ERROR : Save Document has FAILED." << endl;
        cout << endl;
        }
      }
    else
      {
      RetCode = 5; 
      cout << endl;
      cout << " (CAAStmJoggle) ERROR : Update of the Joggle has FAILED." << endl;
      cout << endl;
      }
    }   
  
  // Releases on Interfaces :
  if(NULL != piAslFactory)
    {
    piAslFactory -> Release();
    piAslFactory = NULL;
    }
  if(NULL != piStmJoggle)
    {
    piStmJoggle -> Release();
    piStmJoggle = NULL;
    }
  if(NULL != piJoggleSpec)
    {
    piJoggleSpec -> Release();
    piJoggleSpec = NULL;
    }
  if(NULL != piPrevSupportSpec)
    {
    piPrevSupportSpec -> Release();
    piPrevSupportSpec = NULL;
    }

  // Close the document
  rc = CATDocumentServices::Remove (*pDocument);
    
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmJoggle) ERROR : Remove Document has FAILED." << endl;
    cout << endl;
    }

  // End session
  rc = Delete_Session (pSessionName);
      
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmJoggle) ERROR : Delete Session has FAILED." << endl;
    cout << endl;
    }

  cout << endl;
  cout << "===================================================================================" << endl;
  cout << "=========        Batch : End Joggle creation or modification              =========" << endl;
  cout << "===================================================================================" << endl;
  cout << endl;

  return RetCode ;
  }






