// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef CAAEMmrCatalogPrdAdn_H
#define CAAEMmrCatalogPrdAdn_H

// System Framework
#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

class CATCmdContainer;       // Needed by CreateToolbars

/** Class representing an addin of the Product Structure Workbench.
 *  It implements the CATIPrsConfigurationAddin interface which
 *  is specified by the workbench as the interface to implement in its addins. 
 */
class CAAEMmrCatalogPrdAdn : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public:
     CAAEMmrCatalogPrdAdn();
     virtual ~CAAEMmrCatalogPrdAdn();

     /**
      * Instantiates the command headers for the commands.
      */
     void CreateCommands();

     /**
     * Creates toolbars and arranges the commands inside.
     */
     CATCmdContainer * CreateToolbars();

  private : 
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCatalogPrdAdn(const CAAEMmrCatalogPrdAdn &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCatalogPrdAdn & operator = (const CAAEMmrCatalogPrdAdn &iObjectToCopy);
};
#endif

