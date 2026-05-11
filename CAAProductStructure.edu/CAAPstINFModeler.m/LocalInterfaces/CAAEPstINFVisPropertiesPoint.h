#ifndef CAAEPstINFVisPropertiesPoint_H
#define CAAEPstINFVisPropertiesPoint_H

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint component, implementing the 
//  CATIVisProperties interface to enable its graphic properties
//  modification.
//
//===========================================================================

#include "CATExtIVisProperties.h"    // Need to derive from

class CAAEPstINFVisPropertiesPoint : public CATExtIVisProperties
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEPstINFVisPropertiesPoint();
    virtual ~CAAEPstINFVisPropertiesPoint();

    // CATIVisProperties interface
    HRESULT IsGeomTypeDefined(CATVisGeomType & iGeomType) ;

    HRESULT GetSubTypeFromPath(CATPathElement     & iPathElement,
                               CATVisPropertyType   iPropertyType,
                               CATVisGeomType     & oGeomType,
                               unsigned int       & oPropertyNumber) ;

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesPoint(const CAAEPstINFVisPropertiesPoint &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesPoint & operator = (const CAAEPstINFVisPropertiesPoint &iObjectToCopy);

};
#endif
