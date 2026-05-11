//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#ifndef CAAPmiUserPrismaticOperationToolActivity_H
#define CAAPmiUserPrismaticOperationToolActivity_H

#include "CATBaseUnknown.h"

#include "CATListOfCATUnicodeString.h"

/**
 * Class Class extending the object "UserDrilling".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.CATIMfgToolActivity
 *  </ol>
 */
class CAAPmiUserPrismaticOperationToolActivity: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     CAAPmiUserPrismaticOperationToolActivity ();
     virtual ~CAAPmiUserPrismaticOperationToolActivity ();

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgToolActivity#GetAuthorizedToolTypeList
     */
     HRESULT GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList ) ;

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgToolActivity#CreateDefaultTool
     */
     HRESULT CreateDefaultTool (CATBaseUnknown_var & oTool ) ;

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgToolActivity#GetFirstToolCompensation
     */
     HRESULT GetFirstToolCompensation (int & oFirstNumber ) ;

    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgToolActivity#GetSecondToolCompensation
     */
     HRESULT GetSecondToolCompensation (int & oSecondNumber ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAAPmiUserPrismaticOperationToolActivity (CAAPmiUserPrismaticOperationToolActivity &);
  CAAPmiUserPrismaticOperationToolActivity& operator=(CAAPmiUserPrismaticOperationToolActivity&);

};

#endif
