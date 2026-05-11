// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAASchDeletionMacro
//
// Usage:
// Use the macros in this header to release subclasses of 
// CATBaseUnknown and IUnknown
//
//=============================================================================
#ifndef CAASchDeletionMacro_H
#define CAASchDeletionMacro_H

//-----------------------------------------------------------------------------
// Delete CATUnknown 
//-----------------------------------------------------------------------------
#define CAASchDeleteUnknown(CATUnknownObject)  \
if (CATUnknownObject) \
{  \
  CATUnknownObject->Release(); \
  CATUnknownObject = NULL; \
}
//-----------------------------------------------------------------------------
// Delete C++ Array 
//-----------------------------------------------------------------------------
#define CAASchDeleteArray(pArray)  \
if (pArray) \
{  \
  delete[] pArray; \
  pArray = NULL; \
}
#endif  
