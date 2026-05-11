#ifndef CAAESysName_H
#define CAAESysName_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CAAISysName interface 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  //Needed to derive from CATBaseUnknown
#include "CATUnicodeString.h"

class CAAESysName : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysName();
    virtual ~CAAESysName();

    // Sets the name
    virtual  HRESULT  SetName(const CATUnicodeString & iName) ;

    // Retrieves the name
    virtual  HRESULT  GetName(CATUnicodeString & ioName) ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysName(const CAAESysName &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysName & operator = (const CAAESysName &iObjectToCopy);

  private:

    CATUnicodeString      _Name ;

};
#endif
