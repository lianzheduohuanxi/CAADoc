// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAALifAddLibrary.cpp
//
// Provides implementation to interface CATIAddTypeLibrary in order to
// create 2 new user types and 1 new user function.
//
//===================================================================

#ifndef CAALifAddLibrary_H
#define CAALifAddLibrary_H

#include "CATBaseUnknown.h"


class CAALifAddLibrary: public CATBaseUnknown
{
  CATDeclareClass;

  public:

	CAALifAddLibrary ();
	virtual ~CAALifAddLibrary ();

	void Add();

  private:
  CAALifAddLibrary (CAALifAddLibrary &);
  CAALifAddLibrary& operator=(CAALifAddLibrary&);

};


#endif
