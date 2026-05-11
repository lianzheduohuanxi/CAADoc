// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
// CAACV5EV5IntegrationToolbar.h
// Creation : BZQ - 08.29.2007
//
//===================================================================

#ifndef CAACV5EV5IntegrationToolbar_H
#define CAACV5EV5IntegrationToolbar_H

#include "CATBaseUnknown.h"
class CATCmdContainer;
class CATDialogAgent;

class CAACV5EV5IntegrationToolbar : public CATBaseUnknown
{
  CATDeclareClass;

public:

  // Standard Constructors & Destructors
  CAACV5EV5IntegrationToolbar();
  ~CAACV5EV5IntegrationToolbar();

  // Load the Command Headers included with the Addin Toolbar
  void CreateCommands();

  // Arrange the Command Headers inside the Addin Toolbar
  CATCmdContainer * CreateToolbars();

private:

  // Copy Constructor & Equal Operator
  CAACV5EV5IntegrationToolbar(CAACV5EV5IntegrationToolbar &);
  CAACV5EV5IntegrationToolbar & operator=(CAACV5EV5IntegrationToolbar &);

};

#endif

