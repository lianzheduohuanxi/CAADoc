// Copyright Dassault Systemes 2000
#ifndef CAAEGSMCircleSweepTgAttrBehavior_H
#define CAAEGSMCircleSweepTgAttrBehavior_H
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// CAAEGSMCircleSweepTgAttrBehavior.h
// Provide implementation to interface
//   CATIAttrBehavior
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
#include "CATBaseUnknown.h"   // Base class for CAAEGSMCircleSweepTgAttrBehavior

// ObjectSpecsModeler Framework
#include "CATBehaviorSpecs.h" // To return the Behavior of an Attribute

// System Framework
class CATUnicodeString;       // To handle Attribute Names 

/**
 * Implement CATIAttrBehavior on CAACircleSweepTg LateType. 
 */
class CAAEGSMCircleSweepTgAttrBehavior : public CATBaseUnknown
{
 public :
   CATDeclareClass;
  
   CAAEGSMCircleSweepTgAttrBehavior();
   virtual ~CAAEGSMCircleSweepTgAttrBehavior();

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
    CAAEGSMCircleSweepTgAttrBehavior(const CAAEGSMCircleSweepTgAttrBehavior &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEGSMCircleSweepTgAttrBehavior & operator = (const CAAEGSMCircleSweepTgAttrBehavior &iObjectToCopy);

};

#endif
