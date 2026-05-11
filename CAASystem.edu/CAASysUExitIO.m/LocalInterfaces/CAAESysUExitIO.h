#ifndef CAAESysUExitIO
#define CAAESysCircle_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CATUExitIO component and implementing the 
//  CATIUExitIO interface.
//
//  The component CATUExitIO is defined in the System FW. 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"   //Needed to derive from CATBaseUnknown
#include "CATIUExitIO.h"
#include "CATBoolean.h"       //For the unic data member 

class CAAESysUExitIO : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysUExitIO();
    virtual ~CAAESysUExitIO();

    // Enables to perform some operations on the file to open
    // This method is called when a file is physically open
    //
    virtual HRESULT OnOpen (const CATUnicodeString *iFileName,
                            CATAccessRight iMode, 
                            HRESULT *oGranted, 
                             CATFileSystemError *oError);

    // This method is not implemented
    // 
    virtual HRESULT CreationMask (const CATUnicodeString *iFileName, 
                                  DWORD *oMode, 
                                  CATFileSystemError *oError);

    // Enables to perform some operations on the file to close
    // This method is called when a file is physically close
    //
    virtual HRESULT OnClose (const CATUnicodeString *iFileName,
			     CATFileSystemError *oError); 

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysUExitIO(const CAAESysUExitIO &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysUExitIO & operator = (const CAAESysUExitIO &iObjectToCopy);


};
#endif
