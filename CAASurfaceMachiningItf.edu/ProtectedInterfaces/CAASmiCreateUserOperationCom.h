// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiCreateUserOperationCom.h
//
//===================================================================
#ifndef CAASmiCreateUserOperationCom_H
#define CAASmiCreateUserOperationCom_H

#include "CAASmiUserOperationCmdEnv.h"

#include "CATStateCommand.h"
#include "CATBoolean.h"
class CATPathElementAgent;

class ExportedByCAASmiUserOperationCmdEnv CAASmiCreateUserOperationCom: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  DeclareResource( CAASmiCreateUserOperationCom, CATStateCommand )

  public:

	  CAASmiCreateUserOperationCom(CATString* argument);
	  virtual ~CAASmiCreateUserOperationCom();

	  // Builds the command statechart.
	  virtual void BuildGraph();

	  // Create the activity and make sequencing
      CATBoolean CreateActivity (void *);


	  // Find the program on which you want to create the activity
	  CATBaseUnknown_var FindActivityFather(CATBaseUnknown_var& ioRefActivity);

	  // To Initialize the activity
      HRESULT SetLinksAndDataOnActivity();
      HRESULT InitTool ();
      HRESULT SetCompatibleToolingFromDocument (const CATListOfCATUnicodeString &iToolTypeList,
		                                        CATBaseUnknown_var& oTool);

  private:

	  // Activity
      CATBaseUnknown_var _spCreatedActivity;
	  
      // Activity type
	  CATUnicodeString _TypeToCreate;

	  // Selection agent
      CATPathElementAgent * _pActAcq;
};

#endif
