// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEMmrCombineCurveReplace.h"

// System Framework
#include "CATErrorMacros.h"               // To manage Try/Catch
#include "CATLISTP_IID.h"

// Visualization Framework
#include "CATVisPropertiesValues.h"
#include "CATIVisProperties.h"            // To manage Hide/Show of a Feature
#include "CATPathElement.h"               // To handle Selection path

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"              // To handle the Redraw in the Tree Representation
#include "CATIDescendants.h"  
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"               // To handle feature, update it
#include "CATISpecAttribute.h"            // To handle Attributes of Features
#include "CATISpecAttrAccess.h"           // To retrieve the inverse feature
#include "CATLISTV_CATISpecAttribute.h"   // To handle a List of Attributes pointing to a Feature
#include "CATIAttrBehavior.h"             // To handle expected behavior of attribute

// InteractiveInterfaces Framework 
#include "CATIOrientationFlag.h"          // To handle inversion state of a Feature

// MechanicalModeler Framework
#include "CATIFeaturize.h"                // On the fly featurization of Selection Objects 
#include "CATIMfBRep.h"  
#include "CATIMfMonoDimResult.h"          // To put the CATIMfMonoDimResult IID int the CATBehaviorSpecs

// GeometricObjects Framework
#include "CATLine.h"                // To put the CATLine IID in the CATBehaviorSpecs 

// GSMInterfaces Framework
#include "CATIGSMFactory.h"               // To create Inversion Feature 
#include "CATIGSMInverse.h"               // To handle Inversion Feature 

#include <iostream.h>

//-----------------------------------------------------------------------------
CATImplementClass(CAAEMmrCombineCurveReplace, DataExtension, CATIReplace, CombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIReplace, CAAEMmrCombineCurveReplace);

// 
// To declare that CombineCurve implements CATIReplace ,  
// insert the following line in the interface dictionary:
//
//    CombinedCurve        CATIReplace    libCAAMmrCombinedCurveReplace
//
//-----------------------------------------------------------------------------

CAAEMmrCombineCurveReplace::CAAEMmrCombineCurveReplace() :CATSpecReplaceExt()
{
   cout << "CAAEMmrCombineCurveReplace::CAAEMmrCombineCurveReplace" << endl;
}

//-----------------------------------------------------------------------------

CAAEMmrCombineCurveReplace::~CAAEMmrCombineCurveReplace()
{
   cout << "CAAEMmrCombineCurveReplace::~CAAEMmrCombineCurveReplace" << endl;
}

//-----------------------------------------------------------------------------

HRESULT
CAAEMmrCombineCurveReplace::IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
   const CATBaseUnknown_var& iElement,
   CATUnicodeString& oMessage,
   int& oElementValidity,
   const CATBaseUnknown_var& iOldValue)
{
   cout << "CAAEMmrCombineCurveReplace::IsElementValidForReplace" << endl;

   HRESULT exit = S_OK;

   oElementValidity = 0;

   // The default implementation calls the CATIAttrBehavior interface
   exit = CATSpecReplaceExt::IsElementValidForReplace(iNameOfRole, iElement, oMessage, oElementValidity, iOldValue);

   return exit;
}


//------------------------------------------------------------------------
HRESULT
CAAEMmrCombineCurveReplace::Replace(const CATUnicodeString& iNameOfRole,
   CATBaseUnknown_var& ispNewElement,
   const CATBaseUnknown_var& ispOldValue)
{
   HRESULT rc = E_FAIL;

   cout << "CAAEMmrCombineCurveReplace::Replace" << endl;

   CATISpecObject_var spCurrent = this;
   CATISpecObject_var spNewSpec = ispNewElement;
   CATBaseUnknown_var spForReplace = ispNewElement;

   // Tests to enhance performance in case of replacing an element by itself
   // We want to avoid the Replace of a Feature by itself, but we have 
   // to be cautious with the orientation associated with the input element.
   if ((NULL_var != ispNewElement) && (ispNewElement == ispOldValue))
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
   if ((NULL_var != spForReplace) && (spForReplace == spCurrent))
   {
      return E_FAIL;
   }

   //Featurization on the fly
   //-------------------------------------
   if (NULL_var == spNewSpec)
   {
      CATISpecObject_var spElem = ExtractFeature(ispNewElement);
      spForReplace = spElem;
   }

   //Inversion of the Feature if no inversion still exists
   //-----------------------------------------------------
   spForReplace = InvertFeature(ispNewElement, spForReplace);

   // If the Replace feature is a Brep feature, it should be
   // aggregated by the combined curve
   CATIMfBRep *pIMfBRep = NULL;
   rc = spForReplace->QueryInterface(IID_CATIMfBRep, (void**)& pIMfBRep);
   if (SUCCEEDED(rc))
   {
      CATISpecObject_var spSpecObjectOnReplace = spForReplace;
      if (NULL_var != spSpecObjectOnReplace)
      {
         CATISpecObject * pFather = spSpecObjectOnReplace->GetFather();
         if (NULL == pFather)
         {
            CATIDescendants * pIDescendantsOnCC = NULL;
            rc = QueryInterface(IID_CATIDescendants, (void**)&pIDescendantsOnCC);

            if (SUCCEEDED(rc))
            {
               pIDescendantsOnCC->Append(spForReplace);

               pIDescendantsOnCC->Release();
               pIDescendantsOnCC = NULL;
            }
         }
         else
         {
            pFather->Release();
            pFather = NULL;
            rc = E_FAIL;
         }
      }
      else rc = E_FAIL;

      pIMfBRep->Release();
      pIMfBRep = NULL;

   }
   else rc = S_OK;

   // Replace operation
   if (SUCCEEDED(rc))
   {
      //Standard Replace Call
      //---------------------
      rc = CATSpecReplaceExt::Replace(iNameOfRole, spForReplace, ispOldValue);

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

HRESULT CAAEMmrCombineCurveReplace::GetRequestedBehavior(const CATUnicodeString & iAttributeName,
   CATListPtrIID ** oBehaviorArray, int * oBehaviorSize)
{
   if (!oBehaviorArray || !oBehaviorSize)
      return E_INVALIDARG;
   cout << "CAAEMmrCombineCurveReplace::GetRequestedBehavior" << endl;
   HRESULT rc = S_OK;

   //Check input
   int InputType = 0;
   if (2 == iAttributeName.Compare("Curve1") || 2 == iAttributeName.Compare("Curve2"))
      InputType = 1;
   else if (2 == iAttributeName.Compare("Direction1") || 2 == iAttributeName.Compare("Direction2"))
      InputType = 2;
   else
   {
      //call adapter for inherited attributes
      rc = CATSpecReplaceExt::GetRequestedBehavior(iAttributeName, oBehaviorArray, oBehaviorSize);
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
   else if (InputType == 2)
      SubList->Append(&IID_CATLine);

   (*oBehaviorArray)->Append(*SubList);
   delete SubList;

   return rc;
}

//------------------------------------------------------------------------
CATISpecObject_var
CAAEMmrCombineCurveReplace::ExtractFeature(const CATBaseUnknown_var& ispSelectedObject)
{
   cout << "CAAEMmrCombineCurveReplace::ExtractFeature" << endl;

   CATISpecObject_var spNewValue = ispSelectedObject;

   if (NULL_var == spNewValue)
   {
      // Selected Object conversion into an equivalent feature
      CATIFeaturize_var spToFeaturize = ispSelectedObject;
      if (NULL_var != spToFeaturize)
      {
         // We create a Feature that will have the representation (Result) of the 
         // selected object that will be a Relimited one. The selected object is a non-
         // persistent object, with this conversion we make it persistent and associative.
         // This feature will be aggregated in the Replace method, we just have to update it
         // before calling this method.
         spNewValue = spToFeaturize->FeaturizeR(MfPermanentBody |
            MfLastFeatureSupport |
            MfRelimitedFeaturization);
         //Update of the New Feature
         CATTry
         {
            spNewValue->Update();
         }
            CATCatch(CATError, error)
         {
            ::Flush(error);
         }
         CATEndTry
      }
   }

   return spNewValue;
}

//------------------------------------------------------------------------
CATISpecObject_var CAAEMmrCombineCurveReplace::InvertFeature(const CATBaseUnknown_var& ispSelectedObject, const CATISpecObject_var& ispCurrentSpec)
{
   cout << "CAAEMmrCombineCurveReplace::InvertFeature" << endl;

   CATISpecObject_var spToReturn = ispCurrentSpec;

   //We check that the feature is not inversed
   CATIOrientationFlag_var spInvertFlag = ispSelectedObject;
   if (NULL_var != spInvertFlag && spInvertFlag->IsInversed())
   {
      //We check first if the feature is an inversion
      CATIGSMInverse_var spInverse = ispCurrentSpec;
      if (NULL_var != spInverse)
      {
         //We retrieve inversion Parent
         spToReturn = spInverse->GetElem();
      }
      else
      {
         //Inversion Creation
         //------------------
         CATISpecObject_var spSpec(this);
         CATISpecObject_var spInverse = NULL_var;
         CATIContainer_var  spFeatCont = spSpec->GetFeatContainer();

         //We check that no inversion still exist on this feature
         //We First get the pointing attributes, owned by a GSMInverse feature  
         /*
         CATListValCATISpecAttribute_var * aListAtt = ispCurrentSpec->InverseAttrLink("CATIGSMInverse");
         */
         CATISpecAttrAccess_var spAttrAccessOnCurrentSpec = ispCurrentSpec;
         CATListValCATBaseUnknown_var * pListPointingObject = spAttrAccessOnCurrentSpec->ListPointingObjects(IID_CATIGSMInverse);
         if (NULL != pListPointingObject)
         {
            int size = pListPointingObject->Size();
            for (int i = 1; i <= size; i++)
            {
               CATISpecObject_var spOwner = (*pListPointingObject)[i];
               if (NULL_var != spOwner)
               {
                  // if the feature is created in the same Container of Feature
                  // then we store the Inverse feature and exit the loop.
                  CATIContainer_var spFeatContForOwner = spOwner->GetFeatContainer();
                  if (spFeatContForOwner == spFeatCont)
                  {
                     // We have found a valid Inverse Feature, we step out of this loop
                     // and we won't need an inversion creation. 
                     spInverse = spOwner;
                     break;
                  }
               }
            }
            delete pListPointingObject;
            pListPointingObject = NULL;
         }

         // Finally we create the inversion
         // If no inversion was found above.
         if (NULL_var == spInverse)
         {
            CATIGSMFactory * pIFactoryOnFeatCont = NULL;
            HRESULT rc = spFeatCont->QueryInterface(IID_CATIGSMFactory, (void**)&pIFactoryOnFeatCont);
            if (SUCCEEDED(rc))
            {
               spInverse = pIFactoryOnFeatCont->CreateInverse(ispCurrentSpec);
               if (NULL_var != spInverse)
               {
                  //Hide the inversion
                  CATIVisProperties *pVisuSpec = NULL;
                  rc = spInverse->QueryInterface(IID_CATIVisProperties, (void**)&pVisuSpec);
                  if (SUCCEEDED(rc))
                  {
                     CATVisPropertiesValues MyProp;
                     MyProp.SetShowAttr(CATNoShowAttr);
                     pVisuSpec->SetPropertiesAtt(MyProp, CATVPShow, CATVPGlobalType);
                     pVisuSpec->Release();
                     pVisuSpec = NULL;
                  }

                  // Aggregation of the inversion to me
                  CATIDescendants_var spDesc = spSpec;
                  if (NULL_var != spDesc)
                  {
                     spDesc->Append(spInverse);
                  }

                  //Update the inversion
                  CATISpecObject_var spObject = spInverse;
                  if (NULL_var != spObject)
                  {
                     CATTry
                     {
                        spObject->Update();
                     }
                        CATCatch(CATError, error)
                     {
                        Flush(error);
                     }
                     CATEndTry
                  }
               }

               pIFactoryOnFeatCont->Release();
               pIFactoryOnFeatCont = NULL;
            }
         }
         spToReturn = spInverse;
      }
   }
   return spToReturn;
}
