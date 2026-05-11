#ifndef CAAISysName_H
#define CAAISysName_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which manages the name of the CAAGeometry's object.
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
//  SetName: Sets the name of the component
//  Getname: Retrieves the name of the component
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown
class CATUnicodeString  ;  

// Local framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysName;

class ExportedByCAASysGeoModelInf CAAISysName : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

    virtual  HRESULT     SetName(const CATUnicodeString & iName)  =0 ;
    virtual  HRESULT     GetName(CATUnicodeString & ioName) =0 ;

};

#endif
