// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAALifAddLibraryExt.cpp
// Provide implementation to interface CATICreateInstance
//
//===================================================================

#ifndef CAALifAddLibraryExt_H
#define CAALifAddLibraryExt_H

#include "CATBaseUnknown.h"


class CAALifAddLibraryExt: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAALifAddLibraryExt ();
     virtual ~CAALifAddLibraryExt ();

    /**
     * Implements a function from an interface.
     * @see System.CATICreateInstance#CreateInstance
     */
     HRESULT __stdcall CreateInstance (void ** ppv) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAALifAddLibraryExt (CAALifAddLibraryExt &);
  CAALifAddLibraryExt& operator=(CAALifAddLibraryExt&);

};


#endif
