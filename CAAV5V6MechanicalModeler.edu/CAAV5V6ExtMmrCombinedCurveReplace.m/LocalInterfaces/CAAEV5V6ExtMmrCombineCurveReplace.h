// COPYRIGHT DASSAULT SYSTEMES 2012
#ifndef CAAEV5V6ExtMmrCombineCurveReplace_H
#define CAAEV5V6ExtMmrCombineCurveReplace_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplace interface
//  which  manages the replacement of a Feature by another one for a given Role.   
//
//                   
//  This extension extends the V5V6ExtCombinedCurve Feature.
//
// Note : CAAEV5V6ExtMmrCombinedCurveReplace is the same use case as CAAEMmrCombinedCurveReplace. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//===========================================================================

// CATMecModExtendItf Framework 
#include "CATMmrReplaceAdapter.h" // The adapter class for the Replace Capability  


class CATListPtrIID;
class CATIMmiUseMfBRep_var;
class CATIMmiMechanicalFeature_var;

class CAAEV5V6ExtMmrCombineCurveReplace : public CATMmrReplaceAdapter
{
   CATDeclareClass;
      
 public :

   CAAEV5V6ExtMmrCombineCurveReplace();
   virtual ~CAAEV5V6ExtMmrCombineCurveReplace();
   
   HRESULT IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                   const CATBaseUnknown_var& ispElement,
                                   CATUnicodeString& oMessage, 
                                   int& oElementValidity,
                                   const CATBaseUnknown_var& ispOldValue=NULL_var);
   
   HRESULT Replace(const CATUnicodeString& iNameOfRole,
                   CATBaseUnknown_var& ispNewElement,
                   const CATBaseUnknown_var& ispOldValue=NULL_var);

  
    HRESULT GetRequestedBehavior(const  CATUnicodeString  &  iAttributeName,  
                                 CATListPtrIID  **  oBehaviorArray,  
                                  int  *  oBehaviorSize); 

 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombineCurveReplace(const CAAEV5V6ExtMmrCombineCurveReplace &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombineCurveReplace & operator = (const CAAEV5V6ExtMmrCombineCurveReplace &iObjectToCopy);

   // On the fly featurization for selection objects
   //CATISpecObject_var ExtractFeature(const CATBaseUnknown_var& ispSelectedObject);
   HRESULT ExtractFeature(const CATBaseUnknown_var& ispSelectedObject,
                                                   CATIMmiUseMfBRep_var& ospBRepFeature);

 
   //CATISpecObject_var InvertFeature(const CATBaseUnknown_var& ispSelectedObject,
   //                                 const CATISpecObject_var& ispCurrentSpec);
   HRESULT InvertFeature(const CATBaseUnknown_var& ispSelectedObject,
                           CATIMmiMechanicalFeature_var& iospFeature);

};

#endif
