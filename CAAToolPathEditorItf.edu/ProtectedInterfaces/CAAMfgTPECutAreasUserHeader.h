//===================================================================
// COPYRIGHT Dassault Systemes 2002
//===================================================================
//
// CAAMfgTPECutAreasUserHeader.h
// Provide implementation to interface CATIMfgTPECutAreasUserHeader
//
//===================================================================
// October 2002 Creation                                       C.RIMBAUD
//========================================================================
//
#ifndef CAAMfgTPECutAreasUserHeader_H
#define CAAMfgTPECutAreasUserHeader_H

#include "CATBaseUnknown.h"
#include "CATListOfCATString.h"

//-----------------------------------------------------------------------

class CAAMfgTPECutAreasUserHeader: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAMfgTPECutAreasUserHeader ();
     virtual ~CAAMfgTPECutAreasUserHeader ();

    /**
     * Implements a function from an interface.
     * @see ToolPathEditorInterfaces.CATIMfgTPECutAreasUserHeader#GetHeaders
     */
     HRESULT GetHeaders (CATListValCATString & ioHeadersList ) ;


  private:

  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAMfgTPECutAreasUserHeader (CAAMfgTPECutAreasUserHeader &);
  CAAMfgTPECutAreasUserHeader& operator=(CAAMfgTPECutAreasUserHeader&);

};

//-----------------------------------------------------------------------

#endif
