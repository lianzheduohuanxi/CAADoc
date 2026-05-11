// COPYRIGHT Dassault Systemes 2005
//===================================================================
// CAAAniSelectNodeCmd.h
// Header definition of CAAAniSelectNodeCmd
//===================================================================
#ifndef CAAAniSelectNodeCmd_H
#define CAAAniSelectNodeCmd_H

#include "CATStateCommand.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"
class CATPathElementAgent;
class CAT3DCustomRep;
class CATDlgDialog;

//-----------------------------------------------------------------------

class CAAAniSelectNodeCmd: public CATStateCommand
{
	CATDeclareClass;
	CmdDeclareResourceFile(AniCommandHeader, CAAAniSelectNodeCmd, CATStateCommand)

  public:
	 CAAAniSelectNodeCmd (const CATUnicodeString *iEntityType = NULL,
                        const CATString &iName = "CAAAniSelectNodeCmd",
                        CATCommandMode iStatus = CATCommandModeExclusive);

	  static HRESULT HighlightCustoNode( CAT3DCustomRep * , CATBaseUnknown * , void * );


    void BuildGraph();

  // Standard constructors and destructors
  // -------------------------------------
     CAAAniSelectNodeCmd ();
     virtual ~CAAAniSelectNodeCmd ();

     CATBoolean SelectNode(void *data) ;
 
  private:

    CATPathElementAgent*   _FeatSelectionAgent;
	  CATDialogAgent*				 _Agent, *_AgentCancel;
	  CATDlgDialog*				   _Panel;


};

//-----------------------------------------------------------------------

#endif
