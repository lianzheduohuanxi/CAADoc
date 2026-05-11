// COPYRIGHT DASSAULT SYSTEMES 2004
#ifndef CAAMaiCreateUserSetupCom_H
#define CAAMaiCreateUserSetupCom_H
//=============================================================================
//
// Class CAAMaiCreateUserSetupCom:
// Manufacturing Generic Setup Commands
//
//=============================================================================

#include "CATStateCommand.h"
#include "CAAMaiSetupEnv.h"

class CATPathElementAgent;
class CATDialogState;

class ExportedByCAAMaiSetupEnv CAAMaiCreateUserSetupCom : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMaiCreateUserSetupCom,CATStateCommand)
    
      CAAMaiCreateUserSetupCom (CATString* argument);
      virtual ~CAAMaiCreateUserSetupCom();
      void BuildGraph();

   private:

	   // Create the setup
      boolean ManageChildActivityAndSequence(void *);

      CATPathElementAgent*     _ActAcq;
      CATUnicodeString         _TypeToCreate;
      CATDialogState*          _InitState;
};
#endif
