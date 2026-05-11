#ifndef CAAEMaiUserOppositeHandMachiningOptions_H
#define CAAEMaiUserOppositeHandMachiningOptions_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserOppositeHandMachiningOptions.h
// Provides implementation to interface CATIMfgUserOppositeHandMachiningOptions
//=============================================================================

#include "CATIMfgUserOppositeHandMachiningOptions.h"
#include "CATUnicodeString.h"

/**
 * Object modeler implementation class.
 * <br>
 * It implements the interface :
 *  <ol>
 *  <li>@see ManufacturingInterfaces.GetNames
 *  </ol>
 */
class CAAEMaiUserOppositeHandMachiningOptions: public CATIMfgUserOppositeHandMachiningOptions
{
  CATDeclareClass;
  
  public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMaiUserOppositeHandMachiningOptions();
    virtual ~CAAEMaiUserOppositeHandMachiningOptions();
  
    /**
     * Implements a function from an interface.
     * @see ManufacturingInterfaces.CATIMfgUserOppositeHandMachiningOptions#GetNames
     */
    HRESULT GetNames(CATUnicodeString & oOperationName, CATUnicodeString & oSettingName, CATUnicodeString & oRepositoryName) ;
  
  private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMaiUserOppositeHandMachiningOptions(CAAEMaiUserOppositeHandMachiningOptions &);
    CAAEMaiUserOppositeHandMachiningOptions& operator=(CAAEMaiUserOppositeHandMachiningOptions&);
};
#endif
