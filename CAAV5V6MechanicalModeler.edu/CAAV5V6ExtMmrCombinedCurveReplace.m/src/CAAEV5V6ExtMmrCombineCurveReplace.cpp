// COPYRIGHT DASSAULT SYSTEMES 2012
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplace interface
//  which  manages the replacement of a Feature by another one for a given Role.   
//
//  This extension extends the V5V6ExtCombinedCurve Feature.
//
// Note : CAAEV5V6ExtMmrCombinedCurveReplace is the same use case as CAAEMmrCombinedCurveReplace. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//===========================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAEV5V6ExtMmrCombineCurveReplace.h"

// VisualizationInterfaces Framework for V6
// Visualization Framework for V5
#include "CATIVisProperties.h"            // To manage Hide/Show of a Feature
#include "CATVisPropertiesValues.h"

// ObjectModelerNavigator Framework
#include "CATIRedrawEvent.h"              // To handle the Redraw in the Tree Representation
  
// CATMecModUseItf Framework 
#include "CATIMmiUseFeaturize.h"                // On the fly featurization of Selection Objects 
#include "CATIMmiUseMfBRep.h"
#include "CATIMmiUseBasicInsertion.h"

// CATMecModUseItf Framework for V6
// InteractiveInterfaces Framework for V5
#include "CATIOrientationFlag.h"          // To handle inversion state of a Feature

// CATMecModUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIMfMonoDimResult.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"

// CATGSMUseItf Framework
#include "CATIGSMUseInverse.h"             // To handle Inversion Feature 
#include "CATIGSMUseFactory.h"             // To create Inversion Feature 

// GeometricObjects Framework
#include "CATLine.h"   

// FeatureModelerExt 
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmPointingFeatureIterator.h"
#include "CATFmContainerFacade.h"

// System Framework
#include "CATBaseUnknown.h"


//DataCommonProtocolUse Framework for V6
// ObjectSpecsModeler Framework for V5
#include "CATLISTP_IID.h"


#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

//DataCommonProtocolUse Framework
#include "CATLISTP_IID.h"
#include "CATIUseEntity.h"
#include "DataCommonProtocolServices.h"

#else
//============================================== 
// V5 only
//============================================== 

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// System Framework
#include "CATErrorMacros.h"               // To manage Try/Catch

#endif

// C++ Standard library
#include <iostream.h> // for cout traces

//-----------------------------------------------------------------------------
CATImplementClass(CAAEV5V6ExtMmrCombineCurveReplace, DataExtension, CATIReplace, V5V6ExtCombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIReplace, CAAEV5V6ExtMmrCombineCurveReplace);

// 
// To declare that CombineCurve implements CATIReplace ,  
// insert the following line in the interface dictionary:
//
//    V5V6ExtCombinedCurve    CATIReplace    libCAAV5V6ExtMmrCombinedCurveReplace
//
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrCombineCurveReplace::CAAEV5V6ExtMmrCombineCurveReplace():CATMmrReplaceAdapter()
{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplace::CAAEV5V6ExtMmrCombineCurveReplace" << endl;
}

//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrCombineCurveReplace::~CAAEV5V6ExtMmrCombineCurveReplace ()
{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplace::~CAAEV5V6ExtMmrCombineCurveReplace" << endl;
}

//-----------------------------------------------------------------------------

HRESULT
CAAEV5V6ExtMmrCombineCurveReplace::IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                                     const CATBaseUnknown_var& iElement,
                                                     CATUnicodeString& oMessage, 
                                                     int& oElementValidity, 
                                                     const CATBaseUnknown_var& iOldValue)
{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplace::IsElementValidForReplace" << endl;
  
   HRESULT rc = S_OK;

   oElementValidity=0;

   // Default implementation 
   rc = CATMmrReplaceAdapter::IsElementValidForReplace(iNameOfRole,iElement,oMessage,oElementValidity,iOldValue);
   
   return rc;
}



//------------------------------------------------------------------------
HRESULT
CAAEV5V6ExtMmrCombineCurveReplace::Replace(const CATUnicodeString& iNameOfRole,
                            CATBaseUnknown_var& ispNewElement,
                            const CATBaseUnknown_var& ispOldValue)
{
   HRESULT rc = E_FAIL;
   CATIMmiMechanicalFeature_var spCurrent = this;
   cout <<"CAAEV5V6ExtMmrCombineCurveReplace::Replace" << endl;

   //Check inputs
   if (ispNewElement == NULL_var || ispOldValue == NULL_var)
     return E_INVALIDARG;

   // Tests to enhance performance in case of replacing an element by itself
   // We want to avoid the Replace of a Feature by itself, but we have 
   // to be cautious with the orientation associated with the input element.
   if (ispNewElement->IsEqual(ispOldValue))
   {
      // Get the Inversion Management interface
      CATIOrientationFlag_var spInvertFlag = ispNewElement;

      // If the NewElement is not inversed and that the Old one is 
      // equal to the new one, we don't do the Replace
      if (NULL_var != spInvertFlag && !spInvertFlag->IsInversed())
        return S_OK;

      // If the new element doesn't support inversion flag management,
      // the orientation doesn't matter for this element, so the Replace
      // is not necessary, we don't do the Replace
      if (NULL_var == spInvertFlag)
         return S_OK;
   }

   // Tests that input Element is different from this, if it is the 
   // case we are trying to Replace an input of this by this, this is 
   // a basic test to avoid cycle in between Feature. 
   //CATIMmiMechanicalFeature_var spCurrent = this; 
   CATIMmiMechanicalFeature_var spForReplace = ispNewElement;

   if (spCurrent == NULL_var)
     return E_FAIL;

   if (spForReplace != NULL_var && spCurrent->IsEqual(spForReplace))
   {
      return E_FAIL;
   }
   
   //Featurization on the fly
   //------------------------
   if (spForReplace == NULL_var)
   {
     CATIMmiUseMfBRep_var spElem=NULL_var;
     rc = ExtractFeature(ispNewElement, spElem);
     if (SUCCEEDED(rc) && spElem!= NULL_var)
     {
       spForReplace = spElem;
       if (spForReplace == NULL_var)
         return E_FAIL;
     }
   }

   //Inversion of the Feature if no inversion still exists
   //-----------------------------------------------------
   rc = InvertFeature(ispNewElement, spForReplace);
   if (FAILED(rc))
     return rc;

   // If the Replace feature is a Brep feature, it should be
   // aggregated by the combined curve
   CATIMmiUseMfBRep_var spMfBRep = spForReplace;
   if (spMfBRep != NULL_var)
   {
     CATIMmiMechanicalFeature_var spFather = NULL_var;
     rc = spForReplace->GetMechanicalFather(spFather);
         
     if (NULL_var == spFather)
     {
       CATIMmiUseBasicInsertion_var hInsertedObject = spForReplace;
       if (hInsertedObject != NULL_var)
         rc = hInsertedObject->InsertInside(spCurrent);
     }
     else
     {
       //It should not be aggregated by someone else
       rc = E_FAIL;
     }
   }
  
   // Replace operation
   if (SUCCEEDED(rc))
   {
      //Standard Replace
      //----------------
      rc = CATMmrReplaceAdapter::Replace(iNameOfRole,spForReplace,ispOldValue);

      //Update Representation
      //----------------------
      CATIRedrawEvent_var spEvent(spCurrent);
      if (NULL_var != spEvent)
      {
         spEvent->Redraw();
      }

   }

   return rc;
}


HRESULT CAAEV5V6ExtMmrCombineCurveReplace::GetRequestedBehavior(const  CATUnicodeString  &  iAttributeName,  
                                CATListPtrIID  **  oBehaviorArray,  
                                int  *  oBehaviorSize)

{
  cout <<"CAAEV5V6ExtMmrCombineCurveReplace::ExtractFeature" << endl;
  HRESULT rc = S_OK;

  //Check input
  int InputType=0;
  if (2 == iAttributeName.Compare("V5V6Curve1") || 2 == iAttributeName.Compare("V5V6Curve2"))
    InputType=1;
  else if (2 == iAttributeName.Compare("V5V6Dir1") || 2 == iAttributeName.Compare("V5V6Dir2"))
    InputType=2;
  else
  {
    //call adapter for inherited attributes
    rc = CATMmrReplaceAdapter::GetRequestedBehavior(iAttributeName, oBehaviorArray, oBehaviorSize);
    return rc;
  }

  // Initialialize list of lists
  // 1 list in the list of lists
  (*oBehaviorSize) = 1;
  (*oBehaviorArray) = new CATListPtrIID[1];

  
  //Only 1 interface in the sublist 
  CATListPtrIID* SubList = new CATListPtrIID;
  
  if (InputType == 1)
    SubList->Append(&IID_CATIMfMonoDimResult);
  else if(InputType == 2)
    SubList->Append(&IID_CATLine);

  (*oBehaviorArray)->Append(*SubList);
  delete SubList;

  return rc;
}

//------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCombineCurveReplace::ExtractFeature(const CATBaseUnknown_var& ispSelectedObject,
                                                   CATIMmiUseMfBRep_var& ospBRepFeature)

{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplace::ExtractFeature" << endl;

   HRESULT rc = S_OK;

   // Selected Object conversion into an equivalent feature
   CATIMmiUseFeaturize_var spToFeaturize = ispSelectedObject;
   
   if (NULL_var != spToFeaturize)
   {
     // We create a Feature that will have the representation (Result) of the 
     // selected object that will be a Relimited one. The selected object is a non-
     // persistent object, with this conversion we make it persistent and associative.
     // This feature will be aggregated in the Replace method, we just have to update it
     // before calling this method. 

     HRESULT rc = spToFeaturize->Featurize(ospBRepFeature, 
                                           MfPermanentBody | MfLastFeatureSupport | MfRelimitedFeaturization,
                                           CATMmrRelimited);
	  //Update the new feature   
     if (SUCCEEDED(rc) && ospBRepFeature != NULL_var)
     {

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
        CATIUseEntity * piPartEntity = NULL;
	    rc = ospBRepFeature->QueryInterface(IID_CATIUseEntity , (void**) &piPartEntity);
        if (SUCCEEDED(rc))
        {
   	       rc = DataCommonProtocolServices::Update(piPartEntity);
	       piPartEntity->Release(); 
	       piPartEntity = NULL;
         }
#else
//============================================== 
// V5 only
//==============================================

		 CATISpecObject_var spNewValue = ospBRepFeature;
		 if (spNewValue != NULL_var)
		 {
           CATTry
           {
              spNewValue->Update();
           }
           CATCatch(CATError,error)
           {
             ::Flush(error);
           }
		   CATEndTry 
		 }   
#endif
     } 
   }

   return rc; 
}




HRESULT CAAEV5V6ExtMmrCombineCurveReplace::InvertFeature(const CATBaseUnknown_var& ispSelectedObject,
                                                  CATIMmiMechanicalFeature_var& iospFeature)

{
  cout <<"CAAEV5V6ExtMmrCombineCurveReplace::InvertFeature" << endl;

  HRESULT rc = S_OK;

  CATIMmiMechanicalFeature_var spToReturn = iospFeature;
  CATIMmiMechanicalFeature_var spThis = this;

  //We check that the feature is not inversed
  CATIOrientationFlag_var spInvertFlag = ispSelectedObject;
  if (NULL_var != spInvertFlag && spInvertFlag->IsInversed())
  {
    //We check first if the feature is an inversion
    CATIGSMUseInverse_var spInverse = iospFeature;
    if (NULL_var != spInverse)
    {
      //We retrieve inversion Parent
      spToReturn = spInverse->GetElem();
    }
    else
    {
      //Inversion Creation
      //------------------    
      CATIGSMUseInverse_var spInverse = NULL_var;

      CATUnicodeString ClientId("SAMPLES");
      CATUnicodeString PartnerId = "CAAMmrExtMechanicalModeler";
      CATUnicodeString CatalogName("CAAV5V6ExtMmrCombinedCurveCatalog");
      CATFmCredentials CredentialForCC;
      CredentialForCC.RegisterAsApplicationBasedOn(CATFmFeatureModelerID,PartnerId); 
      CredentialForCC.RegisterAsCatalogOwner(CatalogName,ClientId);
      
      CATFmFeatureFacade FeatFacadeOnInverseFeat(CredentialForCC, iospFeature);      
      CATFmFeatureFacade FeatFacadeOnThis(CredentialForCC, this);

      CATFmContainerFacade FeatCont;
      rc = FeatFacadeOnThis.GetContainerFacade(FeatCont);

      if (FAILED(rc))
        return rc;

      CATFmFeatureFacade FeatFacadeOnPointedFeat(CredentialForCC);
      CATFmPointingFeatureIterator PointingFeatsIterator;
      rc =  FeatFacadeOnInverseFeat.ScanPointingFeatures(PointingFeatsIterator);

      if (SUCCEEDED(rc))
      {
        while (SUCCEEDED(PointingFeatsIterator.Next(FeatFacadeOnPointedFeat))) 
        {
          CATIGSMUseInverse * piPointingFeat = NULL;
          rc = FeatFacadeOnPointedFeat.QueryInterfaceOnFeature(IID_CATIGSMUseInverse, (void**)&piPointingFeat);
          if (SUCCEEDED(rc) && piPointingFeat)
          {
            //Get feature container
            CATFmContainerFacade PointingFeatCont;
            rc = FeatFacadeOnPointedFeat.GetContainerFacade(PointingFeatCont);
          
            if (SUCCEEDED(rc))
            {
              // if the feature is created in the same Container of Feature
              // then we store the Inverse feature and exit the loop.
              int compare=PointingFeatCont.CompareContainerWith(FeatCont);
              if (compare)
              {
                spInverse = piPointingFeat;
                piPointingFeat->Release();
                piPointingFeat=NULL;
                break;
              }
            }

            piPointingFeat->Release();
            piPointingFeat=NULL;
          }
        }
      }

      // Finally we create the inversion
      // If no inversion was found above.
      if (NULL_var == spInverse)
      {
        CATIGSMUseFactory * piFactoryOnFeatCont = NULL ;   
        HRESULT rc = FeatCont.QueryInterfaceOnContainer(IID_CATIGSMUseFactory,(void**)&piFactoryOnFeatCont);
        if (SUCCEEDED(rc) && piFactoryOnFeatCont)
        {
          spInverse = piFactoryOnFeatCont->CreateInverse(iospFeature);
          if (NULL_var != spInverse)
          {
            //Hide the inversion
            CATIVisProperties *pVisuSpec = NULL;
            rc = spInverse->QueryInterface(IID_CATIVisProperties,(void**)&pVisuSpec);
            if (SUCCEEDED(rc))
            {
              CATVisPropertiesValues MyProp;
              MyProp.SetShowAttr(CATNoShowAttr);
              pVisuSpec->SetPropertiesAtt(MyProp,CATVPShow,CATVPGlobalType);
              pVisuSpec->Release();
              pVisuSpec = NULL;
            }

            // Aggregation of the inversion to me
            CATIMmiUseBasicInsertion_var hBasicInsertion = spInverse;
            if (hBasicInsertion != NULL_var)
              rc = hBasicInsertion->InsertInside(spThis);

            //Update the inversion
            CATFmFeatureFacade FeatFacadeOnInverse(CredentialForCC, spInverse);
            rc = FeatFacadeOnInverse.Update();    
          }

          piFactoryOnFeatCont->Release();
          piFactoryOnFeatCont = NULL;
        }
      }
      spToReturn = spInverse;
    }
  }

  iospFeature = spToReturn;

  return rc;
}
