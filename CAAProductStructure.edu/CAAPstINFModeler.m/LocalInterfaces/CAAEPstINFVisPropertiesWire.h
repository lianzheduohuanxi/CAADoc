#ifndef CAAEPstINFVisPropertiesWire_H
#define CAAEPstINFVisPropertiesWire_H

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFWire component, implementing the 
//  CATIVisProperties interface to enable its graphic properties
//  modification.
//
//===========================================================================
#include "CATExtIVisProperties.h"    // Need to derive from

class CAAEPstINFVisPropertiesWire : public CATExtIVisProperties
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEPstINFVisPropertiesWire();
    virtual ~CAAEPstINFVisPropertiesWire();

    // CATIVisProperties interface
    HRESULT IsGeomTypeDefined(CATVisGeomType & iGeomType) ;

    HRESULT GetSubTypeFromPath(CATPathElement     & iPathElement,
                               CATVisPropertyType   iPropertyType,
                               CATVisGeomType     & oGeomType,
                               unsigned int       & oPropertyNumber ) ;

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesWire(const CAAEPstINFVisPropertiesWire &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesWire & operator = (const CAAEPstINFVisPropertiesWire &iObjectToCopy);

};
#endif
