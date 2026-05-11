// COPYRIGHT Dassault Systemes 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
// 
// CAAEGSMFeaturesSplInputDescription
// Provide implementation to interface
//    CATIInputDescription 
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local Framework

#include "CAAEGSMFeaturesSplInputDescription.h"

// System
#include "CATIMfBRep.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBoolean.h"
// InteractiveInterfaces
#include "CATIInputDescription.h"
#include "CATIMf3DBehavior.h"
#include "CATIMf3DBehavior2.h"


#include "CAAIGSMCircleSweepTg.h"

//#define DEBUG_INPUTDESCRIPTION 
#ifdef DEBUG_INPUTDESCRIPTION 
#include "iostream.h"
#endif 

// ---------------------------------------------------------------------------------------------
int Get3DBehavior(CATISpecObject_var spSpec )
{
    int iBehave  = 0; 
    CATIMf3DBehavior_var sp3DBeh(spSpec);
    if (sp3DBeh -> IsAShape () ) {
        CATIMf3DBehavior2_var sp3DBeh2(spSpec);
        if (sp3DBeh2 -> IsAVolume  () ){
            iBehave = 3 ; 
        }
        else {
            iBehave = 1 ;
        }
    }
    else if (sp3DBeh -> IsASolid () ) {
        iBehave = 2 ;
    }
    return iBehave ;
}

// ---------------------------------------------------------------------------------------------

CATBeginImplementClass(CAAEGSMFeaturesSplInputDescription,DataExtension,CATIniInputDescriptionAdaptor,CAASewSkinBasic);
CATAddExtendedImplementation(CAACircleSweepTg);
CATEndImplementClass(CAAEGSMFeaturesSplInputDescription);

//CATImplementClass ( CAAEGSMFeaturesSplInputDescription ,
//                   DataExtension       ,    
//                   CATIInputDescription      ,
//                   CAACircleSweepTg        );

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIInputDescription, CAAEGSMFeaturesSplInputDescription);

//-------------------------------------------------------------------------------------
// Constructor 
//-------------------------------------------------------------------------------------
CAAEGSMFeaturesSplInputDescription::CAAEGSMFeaturesSplInputDescription():CATIniInputDescriptionAdaptor()
{
#ifdef DEBUG_INPUTDESCRIPTION 
    cout <<" CAAEGSMFeaturesSplInputDescription::CAAEGSMFeaturesSplInputDescription" << endl;
#endif 
}

//-------------------------------------------------------------------------------------
// Destructor 
//-------------------------------------------------------------------------------------
CAAEGSMFeaturesSplInputDescription::~CAAEGSMFeaturesSplInputDescription()
{
#ifdef DEBUG_INPUTDESCRIPTION 
    cout <<" CAAEGSMFeaturesSplInputDescription::~CAAEGSMFeaturesSplInputDescription" << endl;
#endif 
}

//---------------------------------------------------------------------
//      Interface CATIInputDescription
//---------------------------------------------------------------------
//Input description general rules
/*====================================================================================
 |    GetFeatureType    |    GetMainInput      |     GetListOfModifiedFeatures      |
 |                      | Returns   oMainInput | Returns   ioListOfModifiedFeatures |
 ====================================================================================
 |      Creation        |  E_FAIL       Nul    |  E_FAIL           {}               |
 ====================================================================================
 |  ContextualCreation  |   S_OK       Input   |  E_FAIL           {}               |
 ====================================================================================
 |    Modification      |   S_OK       Input1  |   S_OK    {Input1[, Input2, ...]}  |
 ====================================================================================*/

/*
////////////////////////////////////////////////////////////////////////////////////
//USE OF CATGuiInputDescription::GetInputDescription

    For each spec type (tested with 'spec->IsSubTypeOf') :
        - set oFeature_type as Feature_type
        - set oElem as MainInput
        - set oListOfModifiedFeatures (Rq: oElem is automatically added to oListOfModifiedFeatures)

-- Methods behaviors / Implement rules --

    - For each new feature, don't forget to add a new CATAddExtendedImplementation  and a new reference in Dictionary.

    - For Creation Feature Add Specific code in GSMModel\CATGmoIntegration\CATGmoInputDescriptionCreation

    - this method return E_FAIL only if an attribute access method has failed or Spec not implemented
      (missing IsSubTypeOf)

    - Valuation of oElem or oListOfModifiedFeatures must not depends on oFeature_type value

    - You don't need to append MainInput into ListOfModifiedFeatures : it's automatically done

    - MainInput and ListOfModifiedFeatures must have the same type as CurrentSpec (Shape / Volume / Solid) see Trim/Split
      and must not be Brep feature.
      If it is the case : feature will be automatically set as creation feature.

      If you have the choice between several main input (exemple Corner full trim)
      take the input that is not a Brep And that have the same type as CurrentSpec. 
      (Example 1: Fillet Full trim between 
        - Surf.1 and Surf.2 -> MainInput=Surf.1
        - Brep.1 and Surf.2 -> MainInput=Surf.2
        - Brep.1 and Brep.2 -> Creation Feature (MainInput=NULL)
       Example 2 : Trim between 
        - Surf.1 and Surf.2 -> MainInput=Surf.1
        - Vol.1 and Surf.2  -> MainInput=Surf.2
        - Brep.1 and Vol.2  -> Creation Feature (MainInput=NULL))

    - Beware : 'Contextual feature' can be 'Modification feature' in NoKeep Mode
      consequently, you must create specific code for oListOfModifiedFeatures 
      if a contextual feat modify more than his MainInput (ex : Combine)

    - For perfo reason, flag ModifiedFeature detection code with iNeedListOfModifiedFeatures

    - Modification of MainInput must be versionned
*/

// List of features that will not be computed for the visualization.
//---------------------------------------------------------------------
HRESULT CAAEGSMFeaturesSplInputDescription::GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures)
{
    CATIInputDescription::FeatureType oFeature_type;
    CATISpecObject_var oMainInput;
    
    HRESULT hr=GetInputDescription(oFeature_type,oMainInput,oListOfModifiedFeatures);
    if(CATIInputDescription::FeatureType_Creation==oFeature_type ||
        CATIInputDescription::FeatureType_ContextualCreation==oFeature_type)
        return E_FAIL;
    else
        return hr;
}

//-------------------------------------------------------------------------------------
//---------------------------------------------------------------------
//  Gets Main input of the feature.
//---------------------------------------------------------------------
//  Method used in feature build methods in case of deactivation
//---------------------------------------------------------------------
HRESULT CAAEGSMFeaturesSplInputDescription::GetMainInput(CATBaseUnknown_var& oMainInput)
{
    CATIInputDescription::FeatureType oFeature_type;
    CATListValCATBaseUnknown_var oListOfModifiedFeatures;
    CATISpecObject_var MainInput;

    HRESULT hr=GetInputDescription(oFeature_type,MainInput,oListOfModifiedFeatures,0);
    
    oMainInput=MainInput;  //QI CATBaseUnknown

    if(CATIInputDescription::FeatureType_Creation==oFeature_type || NULL_var==oMainInput)
        return E_FAIL;
    else
        return hr;
}


//---------------------------------------------------------------------
// Gets the type of the feature.
//---------------------------------------------------------------------
HRESULT CAAEGSMFeaturesSplInputDescription::GetFeatureType(CATIInputDescription::FeatureType& oFeature_type)
{   
    CATISpecObject_var oMainInput;
    CATListValCATBaseUnknown_var oListOfModifiedFeatures; 
    HRESULT hr=GetInputDescription(oFeature_type,oMainInput,oListOfModifiedFeatures,0);
    
    return hr;
}

//---------------------------------------------------------------------
// PRIVATE METHODS 
//---------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////*/
HRESULT CAAEGSMFeaturesSplInputDescription::GetInputDescription(CATIInputDescription::FeatureType& oFeature_type,
                                                    CATISpecObject_var & oMainInput,
                                                    CATListValCATBaseUnknown_var& oListOfModifiedFeatures,
                                                    int iNeedListOfModifiedFeatures)
{
    CATISpecObject_var spec(this);
    HRESULT hr = S_OK;
    
    //Default values : Creation Feature
    oFeature_type = CATIInputDescription::FeatureType_Creation;
    oMainInput = NULL_var;
    oListOfModifiedFeatures.RemoveAll();
    
    if (!spec) return E_FAIL;
    
    /////////////////////////////////////////////////////////////////////////////////////
    //USE
    //For each spec type (tested with 'spec->IsSubTypeOf') :
    // set oFeature_type as Feature_type
    // set oMainInput as MainInput
    // set oListOfModifiedFeatures (Rq: oMainInput is automatically added to oListOfModifiedFeatures)
    /////////////////////////////////////////////////////////////////////////////////////
    
    //BEGIN PURE MODIFICATION
    
    if (spec->IsSubTypeOf("CAASewSkinBasic") ) { 
            oFeature_type = CATIInputDescription::FeatureType_Creation;
    
    }    
    if (spec->IsSubTypeOf("CAACircleSweepTg"))    {
        CAAIGSMCircleSweepTg_var spCircleSweepTg(this);
        if (spCircleSweepTg!= NULL_var)
        {
            int TrimMode = 0 ;
            hr = spCircleSweepTg ->GetTrimMode (TrimMode) ;
            if (TrimMode == 0 ){
                oFeature_type = CATIInputDescription::FeatureType_Creation;
            }
            else if ( TrimMode == 1 ){
                oFeature_type = CATIInputDescription::FeatureType_Modification;
            }
            
            if (oFeature_type == CATIInputDescription::FeatureType_Modification)
            {
                // Main Input = Support file 
                CATISpecObject_var spSupport; 
                hr = spCircleSweepTg ->GetSurfaceSupport  (spSupport) ;
                if (NULL_var != spSupport ) { 
                    oMainInput = spSupport ; 
                }
                
                // List of Modified feature , = Propagation 
                if(iNeedListOfModifiedFeatures){
                    oListOfModifiedFeatures.Append(spSupport);
                    
                }
            }  
        }
    }
    
    else
    {
        //Feature not implemented : method must fails
        oFeature_type = CATIInputDescription::FeatureType_Creation;
        hr=E_FAIL;
    }
    
    ////////////////////////////////////////////////////////////////////
    // Additionnal behaviors : type modification
    ////////////////////////////////////////////////////////////////////
    
/*    // 1. Mode Keep / No Keep
    CATIGSMFeatureType_var spFeatType(this);
    if(!!spFeatType)
    {
        int keepmode;
        //0 : Automatic
        //1 : Keep
        //2 : No Keep
        spFeatType->GetKeepMode(keepmode);
        //Keep Mode
        if(keepmode == 1)
        {
            oFeature_type = CATIInputDescription::FeatureType_Creation;
        }
        //No Keep Mode
        else if(keepmode == 2)
        {
            if (oFeature_type == CATIInputDescription::FeatureType_ContextualCreation)
            {
                oFeature_type = CATIInputDescription::FeatureType_Modification;
            }
        }
    }
  */  
    


  
    /////////////////////////////////////////////////////////////////////////
    // Check For Main input is not a BRep 
	////////////////////////////////////////////////////////////////////////

	// 3 .type modification in case of Brep main input or NULL main input

	//if MainInput=Brep -> Creation
	if(CATIInputDescription::FeatureType_Creation != oFeature_type)
	{
		CATIMfBRep_var Brep(oMainInput);
		if (!oMainInput || !!Brep)
		{
			oFeature_type = CATIInputDescription::FeatureType_Creation;
		}
	}

    /////////////////////////////////////////////////////////////////////////
    // Check Main Input consistency within the Current feature 
	////////////////////////////////////////////////////////////////////////

	// 4. Warning : Main input must have the same type as current spec (2DShape, Volume, Solid)
	//Otherwise MainInput=NULL -> FeatureType_Creation

	if(CATIInputDescription::FeatureType_Creation != oFeature_type)
	{
		int Spec3DBehav=Get3DBehavior(spec);
		int MainInput3DBehav=Get3DBehavior(oMainInput);

		//si un des types est inconnu 
		//(cela peut arrive pour des vieux feat non agg en cours de delete)
		//on choisit de ne pas modifier le type..
		if(Spec3DBehav!=MainInput3DBehav && Spec3DBehav!=0 && MainInput3DBehav!=0)
		{
			oFeature_type = CATIInputDescription::FeatureType_Creation;
		}
	}

  
    /////////////////////////////////////////////////////////////////////////
    //Final coherency check (do not add code after)
    ////////////////////////////////////////////////////////////////////////
    
    // Creation 
    if(CATIInputDescription::FeatureType_Creation==oFeature_type)
    {
        oListOfModifiedFeatures.RemoveAll();
        oMainInput = NULL_var;
    }

    // Modification 
    else if(CATIInputDescription::FeatureType_Modification==oFeature_type)
    {          
        if(iNeedListOfModifiedFeatures)
        {
            if(!!oMainInput)
            {
                //we append oMainInput to modification list if needed (at first position)
                int ind=oListOfModifiedFeatures.Locate(oMainInput);
                if(ind)
                {
                    if(ind!=1){oListOfModifiedFeatures.Swap(1,ind);}                  
                }
                else
                {oListOfModifiedFeatures.InsertAt(1,oMainInput);}
            }
            //Remove duplicates
            oListOfModifiedFeatures.RemoveDuplicates();
            
            // remove Brep and other type features
            int size          =oListOfModifiedFeatures.Size();
            int Spec3DBehav   = Get3DBehavior(spec);
            
            for(int i=1;i<=size;i++) //beware of list size !
            {
                if(NULL_var!=oListOfModifiedFeatures[i])
                {
                    int ModifInput3DBehav = Get3DBehavior(oListOfModifiedFeatures[i]);
                    CATIMfBRep_var Brep=oListOfModifiedFeatures[i];
                    if((Spec3DBehav!=ModifInput3DBehav && Spec3DBehav!=0 && ModifInput3DBehav!=0)
                        || !!Brep)
                    {
                        oListOfModifiedFeatures.RemovePosition(i);
                        size--;
                    }
                    
                }
                else
                {
                    oListOfModifiedFeatures.RemovePosition(i);
                    size--;
                }
            }              
        }
    }
    return hr;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
HRESULT CAAEGSMFeaturesSplInputDescription::ComputeDescription(CATIInputDescription::FeatureType& oFeature_type,
                                                                 CATBaseUnknown_var& oMainInput,
                                                                 CATListValCATBaseUnknown_var & oListOfModifiedFeatures)
{
#ifdef DEBUG_INPUTDESCRIPTION 
    static int cpt=0;
    cout << "ComputeDescription :" << cpt << endl;
    cpt++;
#endif 

    CATISpecObject_var MainInput;
    HRESULT hr=GetInputDescription(oFeature_type,MainInput,oListOfModifiedFeatures);
    oMainInput=MainInput;
    
    return hr;
}





