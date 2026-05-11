// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEMmrCombineCurveReplaceUI.h"

// Visualization Framework
#include "CATPathElement.h"               // To handle Selection path

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"               // To handle feature, update it
#include "CATIReplace.h"   // To handle a List of Attributes pointing to a Feature

//System Framework
#include "CATUnicodeString.h"

#include <iostream.h>

CATImplementClass(CAAEMmrCombineCurveReplaceUI, DataExtension, CATBaseUnknown, CombinedCurve);


#include "TIE_CATIReplaceUI.h"
TIE_CATIReplaceUI(CAAEMmrCombineCurveReplaceUI);

// 
// To declare that CombineCurve implements  CATIReplaceUI,  
// insert thisfollowing line in the interface dictionary:
//
//    CombinedCurve        CATIReplaceUI  libCAAMmrCombinedCurvereplace
//
//-----------------------------------------------------------------------------


CAAEMmrCombineCurveReplaceUI::CAAEMmrCombineCurveReplaceUI():CATBaseUnknown()
{
   cout <<"CAAEMmrCombineCurveReplaceUI::CAAEMmrCombineCurveReplaceUI" << endl;
}

//-----------------------------------------------------------------------------

CAAEMmrCombineCurveReplaceUI::~CAAEMmrCombineCurveReplaceUI ()
{
   cout <<"CAAEMmrCombineCurveReplaceUI::~CAAEMmrCombineCurveReplaceUI" << endl;
}

//-----------------------------------------------------------------------------

HRESULT CAAEMmrCombineCurveReplaceUI::FindValidElementForReplace(const CATUnicodeString& iRole,
                                                               const CATPathElement* ipSelection,
                                                               const CATBaseUnknown* ipOldValue, 
                                                               CATBaseUnknown*& opFoundElement)
{
   cout <<"CAAEMmrCombineCurveReplaceUI::FindValidElementForReplace" << endl;

   // Init of the pointer to return 
   opFoundElement=NULL;
 
   // used for searching path recursively
   CATBaseUnknown* pNextParent = NULL;
   // used to separate features from other objects during the loops
   CATISpecObject_var spFeatParent = NULL_var;
   // Return code init
   HRESULT hr = S_OK;
   CATUnicodeString message;
   // Integer used to know if an object is Valid or not to replace another one
   int ElementValidity=0;
   // Get the CATIReplace interface on this to call IsElementValidForReplace
   // for each object in the CATPathElement
   CATIReplace_var spReplace = this;

   // Get a non-const CATPathElement pointer to be able to call non-const method
   // on this CATPathElement
   CATPathElement* pTmp = (CATPathElement*)ipSelection;

   // Get a CATBaseUnknwon SmartPointer on ipOldValue Object to test via
   // IsElementValidForReplace if an Element is OK to replace spOldValue 
   CATBaseUnknown * pOldValue = (CATBaseUnknown*)ipOldValue;
   CATBaseUnknown_var spOldValue = pOldValue;
   // If the input CATPathElement is valuated, we make two loops
   // to get the first candidate object that can replace ipOldValue in the 
   // iRole Attribute from this.
   if (NULL != pTmp)
   {
      //We do a First loop to retrieve a candidate that is a feature
      pTmp->InitToLeafElement();
      // Begin the Loop, we point on the last element of the CATPathElement
      pNextParent = pTmp->NextFatherElement(); 
      // We are going to stop when there is no more Parent for pNextParent 
      while (NULL != pNextParent) 
      {
         // Get a CATISpecObject Smart Pointer on the current object of the CATPathElement 
         spFeatParent = pNextParent;
         // We want to find a Feature 
         if (NULL_var != spFeatParent)
         {
            // Test if the spFeatParent can replace spOldValue
            hr = spReplace -> IsElementValidForReplace(iRole,spFeatParent,message,ElementValidity,spOldValue);
            
            if (SUCCEEDED(hr) && 1 == ElementValidity)
            {
               // The element is Ok for Replace, we step out of this loop
               opFoundElement = pNextParent;
               opFoundElement->AddRef();
               break;
            }
         }
         // get the next parent object in the CATPathElement 
         pNextParent = pTmp->NextFatherElement();
      }

      // We do another loop to enable Selection of BRep Features 
      // If we have found nothing during the last loop, we do another 
      // loop searching object that are not features
      if (NULL == opFoundElement)
      {
         pTmp->InitToLeafElement();
         pNextParent = pTmp->NextFatherElement();
         // We are going to stop again, when there is no more Parent for pNextParent
         while (NULL != pNextParent) 
         {
            spFeatParent = pNextParent;
            // We want to find everything except a Feature
            if (NULL_var == spFeatParent)
            {
               // Test if the pNextParent can replace spOldValue
               hr = spReplace->IsElementValidForReplace(iRole,pNextParent,message,ElementValidity,spOldValue);
               
               if (SUCCEEDED(hr) && 1 == ElementValidity)
               {
                  // The element is Ok for Replace, we step out of this loop
                  opFoundElement = pNextParent;
                  opFoundElement -> AddRef();
                  break;
               }
            }
            pNextParent = pTmp->NextFatherElement();
         }
      }
   }
   return S_OK;
}


