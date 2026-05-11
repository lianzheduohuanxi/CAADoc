#ifndef CAAEAfrPaletteOptions_H
#define CAAEAfrPaletteOptions_H

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  It is an implementation  of the CATIAfrPaletteOptions interface on
//  the CAAAfrGeoCreationWkb workbench. 
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// ApplicationFrame framework
#include "CATListOfCATCommandHeader.h"       

class CAAEAfrPaletteOptions: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrPaletteOptions();
    virtual ~CAAEAfrPaletteOptions();
 
    CATLISTP(CATCommandHeader) GetPaletteOptions();


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrPaletteOptions(const CAAEAfrPaletteOptions &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrPaletteOptions & operator = (const CAAEAfrPaletteOptions &iObjectToCopy);
     
};
#endif
