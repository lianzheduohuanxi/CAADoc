// COPYRIGHT DASSAULT SYSTEMES 2004
#ifndef CAAMaiCreateUserSetupAddin_H
#define CAAMaiCreateUserSetupAddin_H
//=============================================================================
//
// Class CAAMaiCreateUserSetupAddin
// Manufacturing Generic Setup Commands
//
//=============================================================================
#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

class CATCmdContainer;       // Needed by CreateToolbars
class CAAMaiCreateUserSetupAddin : public CATBaseUnknown
{
   CATDeclareClass;

public:

   CAAMaiCreateUserSetupAddin();
   virtual ~CAAMaiCreateUserSetupAddin();
   
   void CreateCommands();
   CATCmdContainer * CreateToolbars();

};
#endif
