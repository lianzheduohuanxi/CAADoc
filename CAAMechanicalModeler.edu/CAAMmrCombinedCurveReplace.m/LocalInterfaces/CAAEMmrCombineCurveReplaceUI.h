// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef CAAEMmrCombineCurveReplaceUI_H
#define CAAEMmrCombineCurveReplaceUI_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplaceUI interface
//  which manages the depth of a given Selection Path.

//  This extension extends the CombineCurve Feature.
//
//===========================================================================

// ObjectSpecsModeler Framework 
#include "CATBaseUnknown.h"   

// System Framework
class CATUnicodeString ;

// Visualization Framework
class CATPathElement;            // To handle Object Selection  

class CAAEMmrCombineCurveReplaceUI : public CATBaseUnknown
{
   CATDeclareClass;
      
 public :

   CAAEMmrCombineCurveReplaceUI();
   virtual ~CAAEMmrCombineCurveReplaceUI();


   HRESULT FindValidElementForReplace(const CATUnicodeString& iRole,
                                      const CATPathElement* ipSelection,
                                      const CATBaseUnknown* ipOldValue, 
                                      CATBaseUnknown*& opFoundElement);
 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveReplaceUI(const CAAEMmrCombineCurveReplaceUI &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveReplaceUI & operator = (const CAAEMmrCombineCurveReplaceUI &iObjectToCopy);



};

#endif
