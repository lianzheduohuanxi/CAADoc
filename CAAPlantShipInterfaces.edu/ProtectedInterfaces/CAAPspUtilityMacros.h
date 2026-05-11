//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2008
//=============================================================================
//
//-----------------------------------------------------------------------------
//  Utility macros
//-----------------------------------------------------------------------------

#ifndef CAAPspUtilityMacros_H
#define CAAPspUtilityMacros_H

#include "CATErrorDef.h"
#include "CATUnicodeString.h"
#include "IUnknown.h"
#include "CATBaseUnknown.h"
#include "CATIAlias.h"
#include "CATISpecObject.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATError.h"

// Use c++ stream trace base classes

/** @c++ansi mcf 2004-10-04.15:11:35 [Replace forward declaration of standard streams with iosfwd.h] **/
#ifdef _CAT_ANSI_STREAMS
#include "iosfwd.h"
#else //_CAT_ANSI_STREAMS
class ofstream;
class ostream;
#endif //_CAT_ANSI_STREAMS

//-----------------------------------------------------------------------------

// Release a model object.
#define ReleaseIUnknown(piObject) \
{\
  if (piObject)\
  {\
    (piObject)->Release();\
    piObject = NULL;\
  }\
}

// Delete a c++ object.
#define DeleteObject(pObject) \
{\
  if (pObject)\
  {\
    delete pObject;\
    pObject = NULL;\
  }\
}

//  Get object name
inline CATUnicodeString GetObjectName(const IUnknown *piObject)
{
  CATUnicodeString uObjectName;
  if (piObject)
  {
    CATIAlias *piAlias = NULL;
    if (SUCCEEDED(((IUnknown*)piObject)->QueryInterface (IID_CATIAlias, (void **)&piAlias)) &&
        piAlias)
    {
      uObjectName = piAlias->GetAlias();
      piAlias->Release();
    } // End if valid alias
    else
    {
      CATISpecObject *piSpec = NULL;
      if (SUCCEEDED(((IUnknown*)piObject)->QueryInterface (IID_CATISpecObject, (void **)&piSpec)) &&
          piSpec)
      {
        uObjectName = piSpec->GetName();
        piSpec->Release();
      }
    } // End if valid spec
  } // End if valid object
  return uObjectName;
}

//  Get object name
inline CATUnicodeString GetObjectName(const CATBaseUnknown_var& ispObject)
{
  CATUnicodeString uObjectName;
  if (ispObject)
    uObjectName = GetObjectName(ispObject->GetImpl());
  return uObjectName;
}

inline ostream & operator << (ostream & ct, const CATUnicodeString& Uni)
{
  ct << "\"" << Uni.ConvertToChar() << "\"";
  return ct;
}

// Output CATError information
inline ostream & operator << (ostream & ct, const CATError *pError)
{
  if (!pError)
  {
    ct << "NULL CATError" << endl;
  }
  else
  {
		CATUnicodeString ucNLSMessage = ((CATError*)pError)->GetNLSMessage();
    const char * pNLSMessage = ucNLSMessage.CastToCharPtr();
    ct << "ID: " << ((CATError*)pError)->GetId() << ", Name: " << ((CATError*)pError)->GetName() << endl
       << "  Message: " << pNLSMessage << endl;
    char* pSourceFileName;
    int sourceLineNumber;
    ((CATError*)pError)->GetSourceFileName(&pSourceFileName);
    ((CATError*)pError)->GetSourceLineNumber(&sourceLineNumber);
    ct << "  Source: " << pSourceFileName << ":" << sourceLineNumber << endl;
  }
  return ct;
}

inline ostream & operator << (ostream & ct, const IUnknown *piUnk)
{
  if (!piUnk)
    ct << "Invalid IUnknown handle";
  else
  {
    // Print pointer value
    ct << (void *)piUnk << ":" << GetObjectName(piUnk);
  } // End if valid piAlias
  return ct;
}

inline ostream & operator << (ostream & ct, const CATBaseUnknown_var& spUnk)
{
  if (!spUnk)
    ct << "Invalid CATBaseUnknown handle";
  else
    ct << spUnk->GetImpl();
  return ct;
}

// Output math point
inline ostream & operator << (ostream & ct, const CATMathPoint& m)
{
  ct << "<" << m.GetX() << "," << m.GetY() << "," << m.GetZ() << ">";
  return ct;
}

// Output math vector
inline ostream & operator << (ostream & ct, const CATMathVector& m)
{
  ct << "<" << m.GetX() << "," << m.GetY() << "," << m.GetZ() << ">";
  return ct;
}

//-----------------------------------------------------------------------------

#endif
