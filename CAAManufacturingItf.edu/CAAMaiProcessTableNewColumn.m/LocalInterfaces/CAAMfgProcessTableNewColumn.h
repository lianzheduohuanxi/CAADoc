// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAMfgProcessTableNewColumn.h
// Provide implementation to interface
//    CATIMfgTabularViewColumn
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   IMPLEMENTATION
//   TIE: CATIMfgTabularViewColumn
//End CAA2 Wizard Generation Report
//
//  Jul 2004  Creation
//===================================================================
#ifndef CAAMfgProcessTableNewColumn_H
#define CAAMfgProcessTableNewColumn_H

#include "CATIMfgTabularViewColumn.h"
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATListOfCATString.h"
#include "CATListOfCATUnicodeString.h"

//-----------------------------------------------------------------------

/**
 * Class Object modeler implementation class.
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgTabularViewColumn
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAMfgProcessTableNewColumn: public CATIMfgTabularViewColumn
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAMfgProcessTableNewColumn ();
     virtual ~CAAMfgProcessTableNewColumn ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgTabularViewColumn#GetListColumnId
     */
     HRESULT GetListColumnId (CATListOfCATString&  oListColumnId ) ;

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgTabularViewColumn#GetListTitleColumn
     */
     HRESULT GetListTitleColumn (CATListOfCATUnicodeString&  oListTitle ) ;

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgTabularViewColumn#GetParamCke
     */
     HRESULT GetParamCke (const CATBaseUnknown_var&  ispBUActivity  , const CATString&  iColumnId  , CATBaseUnknown_var&  ospBUCkeParm, int& MultiMod);

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgTabularViewColumn#GetValue
     */
     HRESULT GetValue (const CATBaseUnknown_var&  ispBUActivity  , const CATString&  iColumnId  , CATUnicodeString&  ostrValue ) ;

     /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgTabularViewColumn#ResetCache
     */
     HRESULT ResetCache (const int iCacheID ) ;

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAMfgProcessTableNewColumn (const CAAMfgProcessTableNewColumn &);
  CAAMfgProcessTableNewColumn& operator=(const CAAMfgProcessTableNewColumn&);
};

//-----------------------------------------------------------------------

#endif
