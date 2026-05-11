#ifndef CAAESysGeomFactoryForGeomCont_H
#define CAAESysGeomFactoryForGeomCont_H

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of CAASysGeomCont to implement the CAAISysGeomFactory 
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
#include "CAAISysGeomFactory.h" // Implemented interface

class CAAESysGeomFactoryForGeomCont: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:
    CAAESysGeomFactoryForGeomCont();
   virtual ~CAAESysGeomFactoryForGeomCont();


    // Create
    // ------
    // iObjectType is point, root, line ......
    // 
    // oCreateObj  is a pointer on the request interface 
    // 
    virtual HRESULT Create (const CAAISysGeomFactory::GeomObject iObjectType, 
                            const IID        & iRequestInterfaceIID,          
                            CATBaseUnknown  ** oCreatedObj) const;
  
  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysGeomFactoryForGeomCont(const CAAESysGeomFactoryForGeomCont &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysGeomFactoryForGeomCont & operator = (const CAAESysGeomFactoryForGeomCont &iObjectToCopy);

};
#endif
