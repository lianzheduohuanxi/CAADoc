// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombineCurveReplaceUI
//    Implementation of interface CATIReplaceUI for V5V6ExtCombinedCurve 
//
// Note : CAAEV5V6ExtMmrCombinedCurveReplace is the same use case as CAAEMmrCombinedCurveReplace. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//====================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu framework 
#include "CAAEV5V6ExtMmrCombineCurveReplaceUI.h"

// VisualizationInterfaces framework for V6
// VisualizationBase framework for V5
#include "CATPathElement.h"               // To handle Selection path

// CATMecModLiveUseItf framework
#include "CATIMmiMechanicalFeature.h"     // To handle mechanical feature, update it

// DataCommonProtocolUse framework in V6
// ObjectSpecsModeler framework in V5
#include "CATIReplace.h"   // To handle a List of Attributes pointing to a Feature

// C++ Standard library
#include <iostream.h>

CATImplementClass(CAAEV5V6ExtMmrCombineCurveReplaceUI, DataExtension, CATBaseUnknown, V5V6ExtCombinedCurve);


#include "TIE_CATIReplaceUI.h"
TIE_CATIReplaceUI(CAAEV5V6ExtMmrCombineCurveReplaceUI);

// 
// To declare that CombineCurve implements  CATIReplaceUI,  
// insert thisfollowing line in the interface dictionary:
//
// V5V6ExtCombinedCurve	        CATIReplaceUI	   libCAAV5V6ExtMmrCombinedCurveReplace
//
//-----------------------------------------------------------------------------


CAAEV5V6ExtMmrCombineCurveReplaceUI::CAAEV5V6ExtMmrCombineCurveReplaceUI():CATBaseUnknown()
{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplaceUI::CAAEV5V6ExtMmrCombineCurveReplaceUI" << endl;
}

//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrCombineCurveReplaceUI::~CAAEV5V6ExtMmrCombineCurveReplaceUI ()
{
   cout <<"CAAEV5V6ExtMmrCombineCurveReplaceUI::~CAAEV5V6ExtMmrCombineCurveReplaceUI" << endl;
}

//-----------------------------------------------------------------------------

HRESULT CAAEV5V6ExtMmrCombineCurveReplaceUI::FindValidElementForReplace(const CATUnicodeString& iRole,
                                                                 const CATPathElement* ipSelection,
                                                                 const CATBaseUnknown* ipOldValue, 
                                                                 CATBaseUnknown*& opFoundElement)
{
  cout <<"CAAEV5V6ExtMmrCombineCurveReplaceUI::FindValidElementForReplace" << endl;

  HRESULT hr = S_OK;

  // Init of the pointer to return 
  opFoundElement=NULL;
 
  // Get the CATIReplace interface on this, to call IsElementValidForReplace
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
  // used for searching path recursively

  CATBaseUnknown* pNextParent = NULL;
  if (NULL != pTmp)
  {
    //We do a First loop to retrieve a candidate that is a feature
    pTmp->InitToLeafElement();

    // Begin the Loop, we point on the last element of the CATPathElement
    pNextParent = pTmp->NextFatherElement(); 

    // We are going to stop when there is no more Parent for pNextParent 
    while (NULL != pNextParent) 
    {
      // Get a CATIMmiMechanicalFeature Smart Pointer on the current object of the CATPathElement 
      // used to separate mechanical features from other objects during the loops
      CATIMmiMechanicalFeature_var spFeatParent = pNextParent; 

      // We want to find a Feature 
      if (NULL_var != spFeatParent)
      {
        // Test if the spFeatParent can replace spOldValue
        int ElementValidity=0;
        CATUnicodeString message;
        hr = spReplace->IsElementValidForReplace(iRole,spFeatParent,message,ElementValidity,spOldValue);
            
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

      // We are going to stop when there is no more Parent for pNextParent
      while (NULL != pNextParent) 
      {
        CATIMmiMechanicalFeature_var spFeatParent = pNextParent; 

        // We want to find everything except a Feature
        if (NULL_var == spFeatParent)
        {
          // Test if the pNextParent can replace spOldValue
          CATUnicodeString message;
          int ElementValidity=0;
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


