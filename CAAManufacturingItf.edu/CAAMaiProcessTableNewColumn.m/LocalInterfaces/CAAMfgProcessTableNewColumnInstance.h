// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAMfgProcessTableNewColumnInstance.h
// Provide implementation to interface
//    CATICreateInstance
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   EXTENSION: CAAMfgProcessTableNewColumn
//   TIE: CATICreateInstance
//End CAA2 Wizard Generation Report
//
//  Nov 2004  Creation
//===================================================================
#ifndef CAAMfgProcessTableNewColumnInstance_H
#define CAAMfgProcessTableNewColumnInstance_H

#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------

/**
 * Class Class extending the object "CAAMfgProcessTableNewColumn".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see System.CATICreateInstance
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAMfgProcessTableNewColumnInstance: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAMfgProcessTableNewColumnInstance ();
     virtual ~CAAMfgProcessTableNewColumnInstance ();

    /**
     * Implements a function from an interface.
     * @see System.CATICreateInstance#CreateInstance
     */
     HRESULT __stdcall CreateInstance (void ** oPPV ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAMfgProcessTableNewColumnInstance (const CAAMfgProcessTableNewColumnInstance &);
  CAAMfgProcessTableNewColumnInstance& operator=(const CAAMfgProcessTableNewColumnInstance&);

};

//-----------------------------------------------------------------------

#endif
