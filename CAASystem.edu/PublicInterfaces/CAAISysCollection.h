#ifndef CAAISysCollection_h
#define CAAISysCollection_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which enables to manages the list of objects of the container
//  in the CAAGeometry Document. 
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetNumberOfObjects
//  GetObject
//  AddObject
//  RemoveObject
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"              // Needed to derive from CATBaseUnknown

// local Framework
#include "CAASysGeoModelInf.h"           // Needed to export the IID  

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysCollection;

class ExportedByCAASysGeoModelInf CAAISysCollection : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:
   
    virtual HRESULT GetNumberOfObjects(int * oCount) = 0;
    virtual HRESULT GetObject    (int iRank,
                                  CATBaseUnknown ** oObject) = 0;
    virtual HRESULT AddObject    (CATBaseUnknown * iObject) = 0;
    virtual HRESULT RemoveObject (CATBaseUnknown * iObject) = 0;
    virtual HRESULT Empty  () =0 ;
};

#endif
