//============================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//============================================================================================
// Sample code for : Aerospace Sheet Metal Design
// Mission         : 
//                   
//                   - Open an input Part                         ( including at least a Web )
//                   - Create or modify a Surfacic Flange Feature
//                   - Set the Surfacic Flange parameters         ( specified in an input ".txt" file )
//                   - Update the Surfacic Flange 
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
//                   o How to use the CAA Aerospace Sheet Metal factory to create a Surfacic Flange
//                   o How to use the CAA Surfacic Flange public Interface to set the Surfacic Flange parameters
//                   o How to Save a Part Document  
//
// To run the sample :
//  
//     CAAStmSurfacicFlange InputDataPath
//
//                  where InputDataPath is a path to a ".txt" file with the following format
//
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
//                  Available KEYWORD : 
//
//                  INPUT:                (mandatory  : a path to a ".CATPart" file)
//                  OUTPUT:               (mandatory  : a path to a ".CATPart" file)
//                  LENGTHUNIT:           (mandatory  : "mm" (millimeter) or "in" (inch)
//                  MODIFNAME:            (optional   : i.e : Surfacic Flange.2)
//                  DISPLAY:              (optional   : the Surfacic Flange must exist in the input Part)
//                   
//                  BASEFEATURE:          (mandatory  : i.e.    : Web.1)        
//                  BASERADIUSTYPE:       (optional   : Constant (default))
//                  BASERADIUS:           (optional   : default : valuated by the Sheet Metal Parameters)
//    
//                  SUPPTYPE:             (optional   : Exact (default), Angle, Approximation)
//                  SUPPGEOM:             (optional   : i.e.    : Fill.1, Plane.1 ....) 
//                  SUPPLENGTH:           (optional   : Support Length value)
//                  SUPPAPPROX:           (optional   : Support Approximation Length value)
//    
//                  EOPTYPE:              (optional   : Length From OML (default), Element FD, Element FP)
//                  EOPGEOM:              (optional   : i.e     : Line.2)
//                  EOPLENGTH:            (optional   : Length value)
//    
//                  BASEFEATUREORIENT:    (optional   : + (default), -)
//                  FLANGESURFORIENT:     (optional   : + (default), -)
//                  MATERIALORIENT:       (optional   : + (default), -)
//    
//                  SIDE1TYPE:            (optional   : Standard (default), Element FD, Element FP, None)
//                  SIDE1GEOM:            (optional   : i.e     : Plane.2)
//                  CORNER1TYPE:"         (optional   : None (default), Corner)
//                  CORNER1RADIUS:"       (optional   : Radius value)
//    
//                  SIDE2TYPE:            (optional   : Standard (default), Element FD, Element FP, None)
//                  SIDE2GEOM:            (optional   : i.e     : Plane.2)
//                  CORNER2TYPE:"         (optional   : None (default), Corner)
//                  CORNER2RADIUS:"       (optional   : default : 10.mm)
//    
//                  PROCESSTYPE:          (optional   : Hydropressed (default), BreakFormed)
//                  K_FACTOR:             (optional   : default : valuated by the Sheet Metal Parameters) 
//    
//                  COMPENSJOGGLE:        (optional   : None (default) , Apply)
//                  COMPENSSIDE1TYPE:     (optional   : None (default) , Automatic, Angle, Length)
//                  COMPENSSIDE1VALUE:    (optional   : Angle value or Length value)
//                  COMPENSSIDE2TYPE:     (optional   : None (default) , Automatic, Angle, Length)
//                  COMPENSSIDE2VALUE:    (optional   : Angle value or Length value)
//    
// i.e. :
// 
//   CAAStmSurfacicFlange E:\tmp\CAATestCreateFlangeSurf.txt
//
//   ====> File CAATestCreateFlangeSurf.txt : ( delivered in : Data.d )
//
//         #
//         # Create a Surfacic Flange : Base Feature + Support Exact + EOP Length 
//         #
//
//         INPUT:
//         E:\tmp\CAATestCreateFlangeSurf.CATPart
//         OUTPUT:
//         E:\tmp\CAAResultCreateFlangeSurf.CATPart
//         BASEFEATURE:
//         Web.1 
//         SUPPGEOM:
//         Extrude.1
//         EOPLENGTH:
//         25.
//
//   CAAStmSurfacicFlange E:\tmp\CAATestDisplayFlangeSurf.txt
//
//   ====> File CAATestDisplayFlangeSurf.txt ( delivered in : Data.d )
//
//         #
//         # Shows Surfacic Flange current entries.
//         #
//
//         INPUT:
//         E:\tmp\CAATestModifyFlangeSurf.CATPart
//         MODIFNAME:
//         Surfacic Flange.1
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
//                  5 : SurfacicFlange creation problem
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
#include "CATIStmFlangeSurf.h"

// -----------------------------------------------------------------------------
// Main 
// Test : Create a SurfacicFlange
// -----------------------------------------------------------------------------

int main(int iArgc, char * iArgv[])
	{
	int RetCode = 0;
	HRESULT rc  = S_OK;
	
  CAAStmServices   CAASmaTools;
  CAAStmInputData  CAAFlangeInput;

  cout << endl;    
  cout << "============================================================================================" << endl;
  cout << "=========        Batch : Start Surfacic Flange creation or modification            =========" << endl;
  cout << "============================================================================================" << endl;
  cout << endl;

  // ----------------------------------------------------------------------------
  // USE CASE 
  // ----------------------------------------------------------------------------
	
  // Find and analyse Input Data :  
  CATUnicodeString InputDataFilePath = iArgv[1];

  cout << endl;
	cout << "(CAAStmSurfacicFlange) InputDataFile : "<< InputDataFilePath.ConvertToChar() << endl;
  cout << endl;

  rc = CAASmaTools.AnalyseSurfacicFlangeInputData (InputDataFilePath, CAAFlangeInput);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(CAAStmSurfacicFlange) ERROR : bad input arguments." << endl;
    cout << endl;
    RetCode  = 1 ;
    }
   
  // create a session
  char *       pSessionName = "CAAStmSurfacicFlange";
  CATSession * pSession     = NULL; 
    
  rc = Create_Session (pSessionName, pSession); 
    
  if(FAILED(rc))
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmSurfacicFlange) ERROR : Create Session has FAILED" << endl;
    cout << endl;
    exit(RetCode);
    }
    
  // Load the input Document
  CATDocument * pDocument = NULL; 
    
  rc = CATDocumentServices::OpenDocument(CAAFlangeInput.GetInputPartPath().ConvertToChar(), pDocument);
    
  if(NULL == pDocument)
    {
    RetCode = 2;
    cout << endl;
    cout << " (CAAStmSurfacicFlange) ERROR : Open Document has FAILED." << endl;
    cout << endl;
    exit(RetCode);
    }
    
  cout <<" (CAAStmSurfacicFlange) The Input Document " << CAAFlangeInput.GetInputPartPath().ConvertToChar() << " is opened." << endl;

  // Interfaces to manage Aerospace Sheet Metal Features :

  CATIAerospaceSheetMetalFactory *  piAslFactory     = NULL;  // ASM Factory
  CATISpecObject_var                spPrtPartSpec;            // Part Feature
  CATISpecObject *                  piFlangeSurfSpec = NULL;  // Surfacic Flange Feature
  CATIStmFlangeSurf *               piStmFlangeSurf  = NULL;  // Surfacic Flange public interface

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
        cout <<" (CAAStmSurfacicFlange) Part Feature is OK." << endl;
        cout << endl;

        rc = piPrtCont -> QueryInterface(IID_CATIAerospaceSheetMetalFactory, (void **)& piAslFactory);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmSurfacicFlange) Aerospace Sheet Metal Factory retrieved in the Input Part." << endl;
          cout << endl;
          } 
        else
          {
          cout << endl;
          cout <<" (CAAStmSurfacicFlange) ERROR : Aerospace Sheet Metal Factory NOT found." << endl;
          cout << endl;
          } 
        }
      else
        {
        cout << endl;
        cout <<" (CAAStmSurfacicFlange) ERROR :  Part Feature NOT found in the Input Part." << endl;
        cout << endl;
        rc = E_FAIL;
        }
      
      piPrtCont -> Release();
      piPrtCont = NULL;
      }
    else
      {
      cout << endl;
      cout <<" (CAAStmSurfacicFlange) ERROR : Feature Container NOT found in the Input Part." << endl;
      cout << endl;
      rc = E_FAIL;
      }
    
    piInit -> Release();
    piInit = NULL;
    }
  else
    {
    cout << endl;
    cout <<" (CAAStmSurfacicFlange) ERROR : Init interface NOT found in the Input Part." << endl;
    cout << endl;
    rc = E_FAIL;
    }
    
  if(SUCCEEDED(rc) && (NULL != piAslFactory))  
    {     
    if(CAAFlangeInput.GetModifFlange())
      {
      // Try to retrieve the SurfacicFlange Feature :
      rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetModifFlangeName(), &piFlangeSurfSpec);

      if(SUCCEEDED(rc))
        {
        cout << endl;
        cout <<" (CAAStmSurfacicFlange) Surfacic Flange Feature retrieved in the Input Part." << endl;
        cout << endl;
        }
      else
        {
        cout << endl;
        cout <<" (CAAStmSurfacicFlange) ERROR : Surfacic Flange Feature " << CAAFlangeInput.GetModifFlangeName().ConvertToChar() <<" NOT found." << endl;
        cout << endl;
        }
      }
    else
      {
      if(CAAFlangeInput.GetDisplay())
        {
        RetCode = 2;
        cout << endl;
        cout <<" (CAAStmWeb) ERROR : Surfacic Flange to display NOT found." << endl;
        cout << endl;
        }
      else
        {
        // creation of a new SurfacicFlange
        rc = piAslFactory -> CreateSurfacicFlange ((CATISpecObject *) spPrtPartSpec, &piFlangeSurfSpec);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout <<" (CAAStmSurfacicFlange) NEW Surfacic Flange Feature creation is OK." << endl;
          cout << endl;
          }
        else
          {
          cout << endl;
          cout <<" (CAAStmSurfacicFlange) ERROR : NEW Surfacic Flange Feature creation has failed." << endl;
          cout << endl;
          }
        }
      }
    }
  
  if(SUCCEEDED(rc) && (NULL != piFlangeSurfSpec))  
    {
    if(CAAFlangeInput.GetDisplay())
      {
      rc = CAASmaTools.Display (piFlangeSurfSpec);

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
      cout << "    ======================================= " << endl;
      cout << "    Set of the Surfacic Flange Parameters : " << endl;
      cout << "    ======================================= " << endl;
      cout << endl;
      cout << endl; 

      // retrieve a pointer on the SurfacicFlange public interface :
      
      rc = piFlangeSurfSpec -> QueryInterface(IID_CATIStmFlangeSurf, (void **)& piStmFlangeSurf);
      }
    
    if(SUCCEEDED(rc) && (NULL != piStmFlangeSurf))  
      {
      // Base Feature :
      // --------------
      if(CAAFlangeInput.GetBaseFeatureToSet())
        {
        // Search the Base Feature input specification :
        CATISpecObject * pBaseFeatureSpec = NULL;

        rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetBaseFeatureName(), &pBaseFeatureSpec);

        if(SUCCEEDED(rc) && (NULL != pBaseFeatureSpec))  
          {
          // Set the Base Feature :
          rc = piStmFlangeSurf -> SetBaseFeature (pBaseFeatureSpec);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Base Feature is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Base Feature has FAILED." << endl;
            cout << endl;
            }
            
          pBaseFeatureSpec -> Release();
          pBaseFeatureSpec = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : Specification of the Base Feature NOT found." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
 
      // Bend Radius Type :
      // ------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetBaseRadiusTypeToSet())) 
        {
        rc = piStmFlangeSurf -> SetBendRadiusType (CAAFlangeInput.GetBaseRadiusTypeName());

        if(FAILED(rc))
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Bend Radius Type has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // Bend Radius Value :
      // ------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetBaseRadiusValueToSet()))
        { 
        CATICkeParm * piBendRadiusValueParam = NULL;

        rc = piStmFlangeSurf -> GetBendRadiusValue (&piBendRadiusValueParam);

        if(SUCCEEDED(rc) && (NULL != piBendRadiusValueParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                          CAAFlangeInput.GetBaseRadiusValue());  // MKS Units

          piBendRadiusValueParam -> Valuate(MKSVal);
          
          // Inactivate the Formula if any :
          CATICkeRelation_var spRelation = piBendRadiusValueParam -> Relation();
          if(NULL_var != spRelation) 
            {
            if(spRelation -> IsActivated()) spRelation -> Desactivate();
            }          
        
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Bend Radius Value is set." << endl;
          cout << endl;

          piBendRadiusValueParam -> Release();
          piBendRadiusValueParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Bend Radius Value has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 

      // Support Type :
      // --------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSupportTypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSupportType (CAAFlangeInput.GetSupportTypeName());

        if(FAILED(rc))
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Support Type has FAILED." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 

      // Support Geometry :
      // ------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSupportGeomToSet()))
        {
        // Search the Support input specification :
        CATISpecObject * pSupportSpec = NULL;

        rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetSupportGeomName(), &pSupportSpec);

        if(SUCCEEDED(rc) && (NULL != pSupportSpec))  
          {
          // Set the Support Geometry :
          rc = piStmFlangeSurf -> SetSupport (pSupportSpec);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Support is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Support has FAILED." << endl;
            cout << endl;
            rc = E_FAIL;
            }
            
          pSupportSpec -> Release();
          pSupportSpec = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : Specification of the Support NOT found." << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 
    
      // Support Length :
      // ----------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSupportLengthToSet()))
        {
        CATICkeParm * piSupportLengthParam = NULL;

        rc = piStmFlangeSurf -> GetSupportLength (&piSupportLengthParam);
      
        if(SUCCEEDED(rc) && (NULL != piSupportLengthParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                          CAAFlangeInput.GetSupportLengthValue());  // MKS Units

          piSupportLengthParam -> Valuate(MKSVal);
            
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Support Length Value is set." << endl;
          cout << endl;
    
          piSupportLengthParam -> Release();
          piSupportLengthParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Support Length Value has FAILED." << endl;
          cout << endl;
          }
        } 
    
      // Support Approximation Length :
      // ------------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSupportApproxToSet()))
        {
        CATICkeParm * piSupportApproxLengthParam = NULL;

        rc = piStmFlangeSurf -> GetSupportApproxLength (&piSupportApproxLengthParam);
      
        if(SUCCEEDED(rc) && (NULL != piSupportApproxLengthParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                          CAAFlangeInput.GetSupportApproxValue());  // MKS Units

          piSupportApproxLengthParam -> Valuate(MKSVal);
            
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Support Approximation Length Value is set." << endl;
          cout << endl;
    
          piSupportApproxLengthParam -> Release();
          piSupportApproxLengthParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Support Approximation Length Value has FAILED." << endl;
          cout << endl;
          }
        }

      // EOP Type :
      // ----------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetEOPTypeToSet()))
        {
        rc = piStmFlangeSurf -> SetEOPType (CAAFlangeInput.GetEOPTypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) EOP Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("Length From OML");
        
          rc = piStmFlangeSurf -> SetEOPType (Type);
          
          CAAFlangeInput.SetEOPTypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("Length From OML");
        
        rc = piStmFlangeSurf -> SetEOPType (Type);
          
        CAAFlangeInput.SetEOPTypeName(Type);
        }

      // EOP Geometry :
      // --------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetEOPGeomToSet()))
        {
        if(((CAAFlangeInput.GetEOPTypeName()) == "Element FD") || ((CAAFlangeInput.GetEOPTypeName()) == "Element FP"))
          {
          // Search the EOP input specification :
          CATISpecObject * pEOPSpec = NULL;

          rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetEOPGeomName(), &pEOPSpec);

          if(SUCCEEDED(rc) && (NULL != pEOPSpec))  
            {
            // Set the EOP Geometry :
            CATLISTP(CATISpecObject) ListEOPElements;
            ListEOPElements.Append(pEOPSpec);

            rc = piStmFlangeSurf -> SetEOPElements (ListEOPElements);

            if(SUCCEEDED(rc))
              {
              cout << endl;
              cout << " (CAAStmSurfacicFlange) EOP Geometry is set." << endl;
              cout << endl;
              }
            else
              {
              RetCode = 5; 
              cout << endl;
              cout << " (CAAStmSurfacicFlange) ERROR : set of the EOP Geometry has FAILED." << endl;
              cout << endl;
              rc = E_FAIL;
              }
            
            pEOPSpec -> Release();
            pEOPSpec = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : Specification of the EOP Geometry NOT found." << endl;
            cout << endl;
            rc = E_FAIL;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the EOP Geometry INVALID with the EOP Type : " << CAAFlangeInput.GetEOPTypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
    
      // EOP Length :
      // ------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetEOPLengthToSet()))
        {
        if((CAAFlangeInput.GetEOPTypeName()) == "Length From OML")
          {
          CATICkeParm * piEOPLengthParam = NULL;

          rc = piStmFlangeSurf -> GetEOPLength (&piEOPLengthParam);
      
          if(SUCCEEDED(rc) && (NULL != piEOPLengthParam))
            {
            // Valuate the Literal ::
            double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                            CAAFlangeInput.GetEOPLengthValue());  // MKS Units

            piEOPLengthParam -> Valuate(MKSVal);
            
            cout << endl;
            cout << " (CAAStmSurfacicFlange) EOP Length Value is set." << endl;
            cout << endl;
    
            piEOPLengthParam -> Release();
            piEOPLengthParam = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the EOP Length Value has FAILED." << endl;
            cout << endl;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the EOP Length INVALID with the EOP Type : " << CAAFlangeInput.GetEOPTypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // Base Feature Orientation :
      // --------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetBaseFeatureOrientToSet()))
        { 
        rc = piStmFlangeSurf -> SetBaseFeatureOrient (CAAFlangeInput.GetBaseFeatureOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Base Feature orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : Set of the Base Feature orientation has FAILED." << endl;
          cout << endl;
          } 
        } 
    
      // FlangeSurf Orientation :
      // ------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetFlangeSurfOrientToSet()))
        {
        rc = piStmFlangeSurf -> SetFlangeOrient (CAAFlangeInput.GetFlangeSurfOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) FlangeSurf orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : Set of the FlangeSurf orientation has FAILED." << endl;
          cout << endl;
          } 
        } 
    
      // Material Orientation :
      // ----------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetMaterialOrientToSet()))
        {
        rc = piStmFlangeSurf -> SetMaterialOrient (CAAFlangeInput.GetMaterialOrient());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Material orientation is set." << endl;
          cout << endl;
          } 
        else 
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : Set of the Material orientation has FAILED." << endl;
          cout << endl;
          } 
        } 

      // Side 1 : Type :
      // ---------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSide1TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide1Type (CAAFlangeInput.GetSide1TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Side 1 Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("Standard");
        
          rc = piStmFlangeSurf -> SetSide1Type (Type);

          CAAFlangeInput.SetSide1TypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("Standard");
        
        rc = piStmFlangeSurf -> SetSide1Type (Type);

        CAAFlangeInput.SetSide1TypeName(Type);
        }

      // Side 1 : Geometry :
      // -------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSide1GeomToSet()))
        {
        if(((CAAFlangeInput.GetSide1TypeName()) == "Element FD") || ((CAAFlangeInput.GetSide1TypeName()) == "Element FP"))
          {
          // Search the Side 1 input specification :
          CATISpecObject * pSide1Spec = NULL;

          rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetSide1GeomName(), &pSide1Spec);

          if(SUCCEEDED(rc) && (NULL != pSide1Spec))  
            {
            // Set the Side 1 Geometry :
            CATLISTP(CATISpecObject) ListSide1Elements;
            ListSide1Elements.Append(pSide1Spec);

            rc = piStmFlangeSurf -> SetSide1Elements (ListSide1Elements);

            if(SUCCEEDED(rc))
              {
              cout << endl;
              cout << " (CAAStmSurfacicFlange) Side 1 Geometry is set." << endl;
              cout << endl;
              }
            else
              {
              RetCode = 5; 
              cout << endl;
              cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 1 Geometry has FAILED." << endl;
              cout << endl;
              rc = E_FAIL;
              }
            
            pSide1Spec -> Release();
            pSide1Spec = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : Specification of the Side 1 Geometry NOT found." << endl;
            cout << endl;
            rc = E_FAIL;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 1 Geometry INVALID with the EOP Type : " << CAAFlangeInput.GetSide1TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // Side 1 : Corner Type :
      // ----------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCorner1TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide1DressUpType (CAAFlangeInput.GetCorner1TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Corner 1 Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("None");
        
          rc = piStmFlangeSurf -> SetSide1DressUpType (Type);

          CAAFlangeInput.SetCorner1TypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("None");
        
        rc = piStmFlangeSurf -> SetSide1DressUpType (Type);

        CAAFlangeInput.SetCorner1TypeName(Type);
        }

      // Side 1 : Corner Radius :
      // ------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCorner1RadiusToSet()))
        {
        if((CAAFlangeInput.GetCorner1TypeName()) == "Corner")
          {
          CATICkeParm * piCorner1RadiusParam = NULL;

          rc = piStmFlangeSurf -> GetSide1CornerRadius (&piCorner1RadiusParam);
      
          if(SUCCEEDED(rc) && (NULL != piCorner1RadiusParam))
            {
            // Valuate the Literal ::
            double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                            CAAFlangeInput.GetCorner1RadiusValue());  // MKS Units

            piCorner1RadiusParam -> Valuate(MKSVal);
            
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Corner 1 Radius Value is set." << endl;
            cout << endl;
    
            piCorner1RadiusParam -> Release();
            piCorner1RadiusParam = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Corner 1 Radius Value has FAILED." << endl;
            cout << endl;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Corner 1 Radius Value INVALID with the Type : " << CAAFlangeInput.GetCorner1TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 
 
      // Side 2 : Type :
      // ---------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSide2TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide2Type (CAAFlangeInput.GetSide2TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Side 2 Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("Standard");
        
          rc = piStmFlangeSurf -> SetSide2Type (Type);

          CAAFlangeInput.SetSide2TypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("Standard");
        
        rc = piStmFlangeSurf -> SetSide2Type (Type);

        CAAFlangeInput.SetSide2TypeName(Type);
        }

      // Side 2 : Geometry :
      // -------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetSide2GeomToSet()))
        {
        if(((CAAFlangeInput.GetSide2TypeName()) == "Element FD") || ((CAAFlangeInput.GetSide2TypeName()) == "Element FP"))
          {
          // Search the Side 2 input specification :
          CATISpecObject * pSide2Spec = NULL;

          rc = CAASmaTools.FindFeatureInSpecTree (spPrtPartSpec, CAAFlangeInput.GetSide2GeomName(), &pSide2Spec);

          if(SUCCEEDED(rc) && (NULL != pSide2Spec))  
            {
            // Set the Side 2 Geometry :
            CATLISTP(CATISpecObject) ListSide2Elements;
            ListSide2Elements.Append(pSide2Spec);

            rc = piStmFlangeSurf -> SetSide2Elements (ListSide2Elements);

            if(SUCCEEDED(rc))
              {
              cout << endl;
              cout << " (CAAStmSurfacicFlange) Side 2 Geometry is set." << endl;
              cout << endl;
              }
            else
              {
              RetCode = 5; 
              cout << endl;
              cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 2 Geometry has FAILED." << endl;
              cout << endl;
              rc = E_FAIL;
              }
            
            pSide2Spec -> Release();
            pSide2Spec = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : Specification of the Side 2 Geometry NOT found." << endl;
            cout << endl;
            rc = E_FAIL;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 2 Geometry INVALID with the EOP Type : " << CAAFlangeInput.GetSide2TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
      
      // Side 2 : Corner Type :
      // ----------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCorner2TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide2DressUpType (CAAFlangeInput.GetCorner2TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Corner 2 Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("None");
        
          rc = piStmFlangeSurf -> SetSide2DressUpType (Type);

          CAAFlangeInput.SetCorner2TypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("None");
        
        rc = piStmFlangeSurf -> SetSide2DressUpType (Type);

        CAAFlangeInput.SetCorner2TypeName(Type);
        }

      // Side 2 : Corner Radius :
      // ------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCorner2RadiusToSet()))
        {
        if((CAAFlangeInput.GetCorner2TypeName()) == "Corner")
          {
          CATICkeParm * piCorner2RadiusParam = NULL;

          rc = piStmFlangeSurf -> GetSide2CornerRadius (&piCorner2RadiusParam);
      
          if(SUCCEEDED(rc) && (NULL != piCorner2RadiusParam))
            {
            // Valuate the Literal ::
            double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                            CAAFlangeInput.GetCorner2RadiusValue());  // MKS Units

            piCorner2RadiusParam -> Valuate(MKSVal);
            
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Corner 2 Radius Value is set." << endl;
            cout << endl;
    
            piCorner2RadiusParam -> Release();
            piCorner2RadiusParam = NULL;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Corner 2 Radius Value has FAILED." << endl;
            cout << endl;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Corner 2 Radius Value INVALID with the Type : " << CAAFlangeInput.GetCorner2TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        } 

      // Manufacturing Process Type :
      // ----------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetProcessTypeToSet()))
        {
        rc = piStmFlangeSurf -> SetManufacturingProcessType (CAAFlangeInput.GetProcessTypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Manufacturing Process Type is set." << endl;
          cout << endl;
          }
        else
          {
          CATUnicodeString Type("Hydropressed");
        
          rc = piStmFlangeSurf -> SetManufacturingProcessType (Type);

          CAAFlangeInput.SetProcessTypeName(Type);
          }
        }
      else
        {
        CATUnicodeString Type("Hydropressed");
        
        rc = piStmFlangeSurf -> SetManufacturingProcessType (Type);

        CAAFlangeInput.SetProcessTypeName(Type);
        }

      // K_Factor :
      // ----------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetK_FactorToSet()))
        {
        CATICkeParm * piKFactorParam = NULL;

        rc = piStmFlangeSurf -> GetKFactor (&piKFactorParam);
      
        if(SUCCEEDED(rc) && (NULL != piKFactorParam))
          {
          // Valuate the Literal ::
          double MKSVal = CAASmaTools.ConvertLengthToMKS (CAAFlangeInput.GetLengthUnit(),
                                                          CAAFlangeInput.GetK_FactorValue());  // MKS Units

          piKFactorParam -> Valuate(MKSVal);
          
          // Inactivate the Formula if any :
          CATICkeRelation_var spRelation = piKFactorParam -> Relation();
          if(NULL_var != spRelation) 
            {
            if(spRelation -> IsActivated()) spRelation -> Desactivate();
            }          
     
          cout << endl;
          cout << " (CAAStmSurfacicFlange) K_Factor Value is set." << endl;
          cout << endl;
    
          piKFactorParam -> Release();
          piKFactorParam = NULL;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the K_Factor Value has FAILED." << endl;
          cout << endl;
          }
        } 

      // Compensation : Joggle(s) :
      // --------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCompensJoggleTypeToSet()))
        {
        rc = piStmFlangeSurf -> SetJoggleCompensation ((CATISpecObject *) spPrtPartSpec, CAAFlangeInput.GetCompensJoggleTypeName());
          
        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Joggle Compensation is set." << endl;
          cout << endl;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Joggle Compensation has FAILED." << endl;
          cout << endl;
          }
        } 
    
      // Compensation : Side 1 : Type :
      // ------------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCompensSide1TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide1CompensationType (CAAFlangeInput.GetCompensSide1TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Side 1 Compensation Type is set." << endl;
          cout << endl;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 1 Compensation Type has FAILED." << endl;
          cout << endl;
          }
        }

      // Compensation : Side 1 : Value :
      // -------------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCompensSide1ValueToSet()))
        {
        if(((CAAFlangeInput.GetCompensSide1TypeName()) == "Length") || ((CAAFlangeInput.GetCompensSide1TypeName()) == "Angle"))
          {
          rc = piStmFlangeSurf -> SetSide1CompensationValue (CAAFlangeInput.GetCompensSide1Value());
        
          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Side 1 Compensation Value is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 1 Compensation Value INVALID has failed." << endl;
            cout << endl;
            rc = E_FAIL;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 1 Compensation Value INVALID with the Type : " << CAAFlangeInput.GetCompensSide1TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }

      // Compensation : Side 2 : Type :
      // ------------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCompensSide2TypeToSet()))
        {
        rc = piStmFlangeSurf -> SetSide2CompensationType (CAAFlangeInput.GetCompensSide2TypeName());

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " (CAAStmSurfacicFlange) Side 2 Compensation Type is set." << endl;
          cout << endl;
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 2 Compensation Type has FAILED." << endl;
          cout << endl;
          }
        }

      // Compensation : Side 2 : Value :
      // -------------------------------
      if(SUCCEEDED(rc) && (CAAFlangeInput.GetCompensSide2ValueToSet()))
        {
        if(((CAAFlangeInput.GetCompensSide2TypeName()) == "Length") || ((CAAFlangeInput.GetCompensSide2TypeName()) == "Angle"))
          {
          rc = piStmFlangeSurf -> SetSide2CompensationValue (CAAFlangeInput.GetCompensSide2Value());
        
          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " (CAAStmSurfacicFlange) Side 2 Compensation Value is set." << endl;
            cout << endl;
            }
          else
            {
            RetCode = 5; 
            cout << endl;
            cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 2 Compensation Value INVALID has failed." << endl;
            cout << endl;
            rc = E_FAIL;
            }
          }
        else
          {
          RetCode = 5; 
          cout << endl;
          cout << " (CAAStmSurfacicFlange) ERROR : set of the Side 2 Compensation Value INVALID with the Type : " << CAAFlangeInput.GetCompensSide2TypeName().ConvertToChar() << endl;
          cout << endl;
          rc = E_FAIL;
          }
        }
      }
    }
  else
    {
    rc      = E_FAIL;
    RetCode = 2;
    }

  if(SUCCEEDED(rc) && (FALSE == CAAFlangeInput.GetDisplay()))  
    {
    // Update the Part : to ensure all internal Surfacic Flange links to re-build

    rc = CAASmaTools.Update ((CATISpecObject *) spPrtPartSpec);
    
    if(SUCCEEDED(rc))
      {
      cout << endl;
      cout << " (CAAStmSurfacicFlange) Update of the Surfacic Flange Feature is OK." << endl;
      cout << endl;

      // Save the Document 
      rc = CATDocumentServices::SaveAs (*pDocument, CAAFlangeInput.GetOutputPartPath().ConvertToChar());
            
      if(SUCCEEDED(rc))  
        {
        cout << endl; 
        cout <<" (CAAStmSurfacicFlange) The Output Document " << CAAFlangeInput.GetOutputPartPath().ConvertToChar() << " is saved." << endl;
        cout << endl; 
        }
      else 
        {
        RetCode = 4; 
        cout << endl;
        cout << " (CAAStmSurfacicFlange) ERROR : Save Document has FAILED." << endl;
        cout << endl;
        }
      }
    else
      {
      RetCode = 5; 
      cout << endl;
      cout << " (CAAStmSurfacicFlange) ERROR : Update of the Surfacic Flange has FAILED." << endl;
      cout << endl;
      }
    }   
  
  // Releases on Interfaces :
  if(NULL != piAslFactory)
    {
    piAslFactory -> Release();
    piAslFactory = NULL;
    }
  if(NULL != piStmFlangeSurf)
    {
    piStmFlangeSurf -> Release();
    piStmFlangeSurf = NULL;
    }
  if(NULL != piFlangeSurfSpec)
    {
    piFlangeSurfSpec -> Release();
    piFlangeSurfSpec = NULL;
    }

  // Close the document
  rc = CATDocumentServices::Remove (*pDocument);
    
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmSurfacicFlange) ERROR : Remove Document has FAILED." << endl;
    cout << endl;
    }

  // End session
  rc = Delete_Session (pSessionName);
      
  if(FAILED(rc))
    {
    RetCode = 3; 
    cout << endl;
    cout << " (CAAStmSurfacicFlange) ERROR : Delete Session has FAILED." << endl;
    cout << endl;
    }

  cout << endl;
  cout << "============================================================================================" << endl;
  cout << "=========        Batch : End Surfacic Flange creation or modification              =========" << endl;
  cout << "============================================================================================" << endl;
  cout << endl;

  return RetCode ;
  }






