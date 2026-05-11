// COPYRIGHT DASSAULT SYSTEMES 2012
#ifndef CAAEV5V6ExtMmrCombineCurveReplaceUI_H
#define CAAEV5V6ExtMmrCombineCurveReplaceUI_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplaceUI interface
//  which manages the depth of a given Selection Path.

//  This extension extends the CombineCurve Feature.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" 
class CATUnicodeString ;

// VisualizationBase Framework in V5
// VisualizationInterfaces Framework in V6
class CATPathElement;            // To handle Object Selection  

class CAAEV5V6ExtMmrCombineCurveReplaceUI : public CATBaseUnknown
{
   CATDeclareClass;
      
 public :

   CAAEV5V6ExtMmrCombineCurveReplaceUI();
   virtual ~CAAEV5V6ExtMmrCombineCurveReplaceUI();


   HRESULT FindValidElementForReplace(const CATUnicodeString& iRole,
                                      const CATPathElement* ipSelection,
                                      const CATBaseUnknown* ipOldValue, 
                                      CATBaseUnknown*& opFoundElement);
 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombineCurveReplaceUI(const CAAEV5V6ExtMmrCombineCurveReplaceUI &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEV5V6ExtMmrCombineCurveReplaceUI & operator = (const CAAEV5V6ExtMmrCombineCurveReplaceUI &iObjectToCopy);



};

#endif
