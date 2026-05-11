#ifndef CAAEGSMCircleSweepTgReplaceUI_H
#define CAAEGSMCircleSweepTgReplaceUI_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMCircleSweepTgReplaceUI.h
// Provide implementation to interface
//    CATIReplaceUI
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIReplaceUI
//
//===================================================================

// ObjectSpecsModeler Framework 
#include "CATBaseUnknown.h"   

// System Framework
class CATUnicodeString ;

// Visualization Framework
class CATPathElement;            // To handle Object Selection  

/**
 * Implement CATIReplaceUI on CAACircleSweepTg LateType. 
 */
class CAAEGSMCircleSweepTgReplaceUI : public CATBaseUnknown
{
   CATDeclareClass;
      
 public :

   CAAEGSMCircleSweepTgReplaceUI();
   virtual ~CAAEGSMCircleSweepTgReplaceUI();


   HRESULT FindValidElementForReplace(const CATUnicodeString& iRole,
                                      const CATPathElement* ipSelection,
                                      const CATBaseUnknown* ipOldValue, 
                                      CATBaseUnknown*& opFoundElement);
 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEGSMCircleSweepTgReplaceUI(const CAAEGSMCircleSweepTgReplaceUI &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEGSMCircleSweepTgReplaceUI & operator = (const CAAEGSMCircleSweepTgReplaceUI &iObjectToCopy);



};

#endif
