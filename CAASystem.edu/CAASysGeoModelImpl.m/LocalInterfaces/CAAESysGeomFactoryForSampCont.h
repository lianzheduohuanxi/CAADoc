#ifndef CAAESysGeomFactoryForSampCont_H
#define CAAESysGeomFactoryForSampCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999
  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of CAASysSampCont to implement the CAAISysGeomFactory 
//  interface which enables to create the objects.
//
//
//===========================================================================
//  Main Methods:
//  ------------
//
//  Create   -> Constructs a new CATObject 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

// Local Framework
#include "CAAISysGeomFactory.h" // to have Object type

class CAAESysGeomFactoryForSampCont: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
    CAAESysGeomFactoryForSampCont();
    virtual ~CAAESysGeomFactoryForSampCont();

    // Create
    // ------
    // iObjectType is point, root, line ......
    // 
    // oCreateObj  is a pointer on the request interface 
    // 
    virtual HRESULT Create (const CAAISysGeomFactory::GeomObject iObjectType,
                            const IID             & iRequestInterfaceIID,  
			    CATBaseUnknown       ** oCreatedObj) const;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysGeomFactoryForSampCont(const CAAESysGeomFactoryForSampCont &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysGeomFactoryForSampCont & operator = (const CAAESysGeomFactoryForSampCont &iObjectToCopy);
  
};
#endif
