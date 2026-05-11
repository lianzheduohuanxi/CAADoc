/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999  
//=============================================================================
// 
//
//========================================================================
// October 2002 Creation                                       C.RIMBAUD
//========================================================================
//
#ifndef CAAMfgTPEPolylineSelectionUserCom_H
#define CAAMfgTPEPolylineSelectionUserCom_H

#include "CATStateCommand.h"
#include "CATPathElementAgent.h"
#include "CATDialogAgent.h"

#include "CATIMfgCompoundTraject.h"

#include "CATBooleanDef.h"

#include "CATLISTV_CATMathPoint.h"
#include "CATLISTP_CATMathPoint2D.h"

#include "CATIMfgTPECutAreasEditor.h"
#include "CAAMfgTPEAddCmdInCutAreaToolBar.h"

class CAT3DViewer;
class CATSelector;

class ExportedByCAAMfgTPEAddCmdInCutAreaToolBar CAAMfgTPEPolylineSelectionUserCom : public CATStateCommand
{

public:
	DeclareResource (CAAMfgTPEPolylineSelectionUserCom, CATStateCommand)

	CAAMfgTPEPolylineSelectionUserCom (void* ipCutAreasEditor);
	virtual ~CAAMfgTPEPolylineSelectionUserCom ();
 
	void BuildGraph();
	CATBoolean LineSelection(void* Data);
	CATBoolean End(void  *Data);

	CATStatusChangeRC Cancel (CATCommand*, CATNotification*);
	CATStatusChangeRC Desactivate (CATCommand*, CATNotification*);
	CATStatusChangeRC Activate (CATCommand*, CATNotification*);

	void Valuate (int iSwitch);

private:


	CATIMfgTPECutAreasEditor* _piCutEditor;
	CATSelector*   _Selector;

	CAT3DViewer* _Viewer;

	CATPathElementAgent*	_EndAgent;
	CATDialogAgent*      _PointAgent;

	int _NumPolyline;
};
#endif 

