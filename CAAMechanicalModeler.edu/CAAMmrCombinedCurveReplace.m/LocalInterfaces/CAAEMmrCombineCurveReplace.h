// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef CAAEMmrCombineCurveReplace_H
#define CAAEMmrCombineCurveReplace_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplace interface
//  which  manages the replacement of a Feature by another one for a given Role.   
//
//                   
//  This extension extends the CombineCurve Feature.
//
//===========================================================================

// ObjectSpecsModeler Framework 
#include "CATSpecReplaceExt.h"   // The adapter class for the Replace Capability  

class CATISpecObject_var;        // To handle features

class CAAEMmrCombineCurveReplace : public CATSpecReplaceExt
{
   CATDeclareClass;
      
 public :

   CAAEMmrCombineCurveReplace();
   virtual ~CAAEMmrCombineCurveReplace();

      
   HRESULT IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                   const CATBaseUnknown_var& ispElement,
                                   CATUnicodeString& oMessage, 
                                   int& oElementValidity,
                                   const CATBaseUnknown_var& ispOldValue=NULL_var);

   HRESULT Replace(const CATUnicodeString& iNameOfRole,
                   CATBaseUnknown_var& ispNewElement,
                   const CATBaseUnknown_var& ispOldValue=NULL_var);


	 HRESULT GetRequestedBehavior(const CATUnicodeString & iAttributeName, 
		                            CATListPtrIID ** oBehaviorArray, 
																int * oBehaviorSize);

 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveReplace(const CAAEMmrCombineCurveReplace &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveReplace & operator = (const CAAEMmrCombineCurveReplace &iObjectToCopy);

   // On the fly featurization for selection objects
   CATISpecObject_var ExtractFeature(const CATBaseUnknown_var& ispSelectedObject);

 
   CATISpecObject_var InvertFeature(const CATBaseUnknown_var& ispSelectedObject,
                                    const CATISpecObject_var& ispCurrentSpec);


};

#endif
