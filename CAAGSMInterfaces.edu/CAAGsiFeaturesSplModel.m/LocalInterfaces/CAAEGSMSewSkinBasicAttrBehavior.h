#ifndef CAAEGSMSewSkinBasicAttrBehavior_H
#define CAAEGSMSewSkinBasicAttrBehavior_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMSewSkinBasicAttrBehavior.h
// Provide implementation to interface
//    CATIAttrBehavior
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIAttrBehavior
//===================================================================

// System Framework
#include "CATBaseUnknown.h"   // Base class for CAAEGSMSewSkinBasicAttrBehavior

// ObjectSpecsModeler Framework
#include "CATBehaviorSpecs.h" // To return the Behavior of an Attribute

// System Framework
class CATUnicodeString;       // To handle Attribute Names 

/**
 * Implement CATIAttrBehavior on CAASewSkinBasic LateType. 
 */
class CAAEGSMSewSkinBasicAttrBehavior : public CATBaseUnknown
{
 public :
   CATDeclareClass;
  
   CAAEGSMSewSkinBasicAttrBehavior();
   virtual ~CAAEGSMSewSkinBasicAttrBehavior();

   /**
     * Returns for a given attribute the expected behavior of its valuating objects
     * @param ipAttrName
     *        name of the concerned attribute.
     * @param oppBehavior
     *        list of lists of interfaces in the CATBehaviorSpecs format.This parameter
     *        has to be deleted by the caller.
     *        <br> this list is a combination of interfaces implemented by the object 
     *         valuating the attribute.
     */     
   HRESULT GetRequestedBehavior(const CATUnicodeString* ipAttrId, CATBehaviorSpecs** oppBehavior);

 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEGSMSewSkinBasicAttrBehavior(const CAAEGSMSewSkinBasicAttrBehavior &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEGSMSewSkinBasicAttrBehavior & operator = (const CAAEGSMSewSkinBasicAttrBehavior &iObjectToCopy);

};

#endif
