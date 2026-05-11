#ifndef CAAEPstINFVisPropertiesLine_H
#define CAAEPstINFVisPropertiesLine_H

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFLine component, implementing the 
//  CATIVisProperties interface to enable its graphic properties
//  modification.
//
//===========================================================================
#include "CATExtIVisProperties.h"    // Need to derive from

class CAAEPstINFVisPropertiesLine : public CATExtIVisProperties
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEPstINFVisPropertiesLine();
    virtual ~CAAEPstINFVisPropertiesLine();

    // CATIVisProperties interface
    HRESULT IsGeomTypeDefined(CATVisGeomType & iGeomType) ;

    HRESULT GetSubTypeFromPath(CATPathElement     & iPathElement,
                               CATVisPropertyType   iPropertyType,
                               CATVisGeomType     & oGeomType,
                               unsigned int       & oPropertyNumber ) ;

  private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesLine(const CAAEPstINFVisPropertiesLine &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEPstINFVisPropertiesLine & operator = (const CAAEPstINFVisPropertiesLine &iObjectToCopy);

};
#endif
