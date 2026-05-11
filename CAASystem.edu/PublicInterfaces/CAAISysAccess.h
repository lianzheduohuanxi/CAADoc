#ifndef CAAISysAccess_H
#define CAAISysAccess_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which associates a container with its objects the CAAGeometry
//  document.
//  Every container's object implements this interface to know its
//  container. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Methods:
//  ------------
//
//  SetContainer: Sets the container
//  GetContainer: Retrieve the container
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysAccess;

class ExportedByCAASysGeoModelInf CAAISysAccess : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

    virtual  HRESULT     SetContainer(CATBaseUnknown * iContainer)  =0 ;
    virtual  HRESULT     GetContainer(CATBaseUnknown ** oContainer) =0 ;

};

#endif
