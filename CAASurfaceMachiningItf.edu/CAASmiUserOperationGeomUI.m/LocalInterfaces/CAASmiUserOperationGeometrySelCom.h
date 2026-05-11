// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiUserOperationGeometrySelCom.h
//
//===================================================================
#ifndef CAASmiUserOperationGeometrySelCom_H
#define CAASmiUserOperationGeometrySelCom_H

#include "CATStateCommand.h"
class CATPathElementAgent;
class CATDlgDialog;

class CAASmiUserOperationGeometrySelCom: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  DeclareResource(CAASmiUserOperationGeometrySelCom, CATStateCommand )

  public:

     CAASmiUserOperationGeometrySelCom(CATCommand *iFather,const CATBaseUnknown_var &ispGuide);
     virtual ~CAASmiUserOperationGeometrySelCom();
	 
	 // Builds the command statechart.
	 virtual void BuildGraph();

     // Action associated to state transitions.
     CATBoolean SelCurve(void * data);


  private:

     // Dialog agents
	 CATPathElementAgent * _pSelectAgent; 
     CATDialogAgent *      _pPanelAgent;

     // Edition panel (Father)
	 CATDlgDialog * _pPanel;

     // Guide parameter of the CAA machining feature
	 CATBaseUnknown_var  _spGuide;

};

#endif
