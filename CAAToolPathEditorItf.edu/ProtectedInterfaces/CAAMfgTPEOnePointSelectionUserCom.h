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
#ifndef CAAMfgTPEOnePointSelectionUserCom_H
#define CAAMfgTPEOnePointSelectionUserCom_H

#include "CATStateCommand.h"
#include "CATDialogAgent.h"
#include "CATSelector.h"
#include "CATMathPoint.h"
#include "CAT3DPointRep.h"
#include "CAAMfgTPEAddCmdInCutAreaToolBar.h"

class CAT3DViewer;
class CATIMfgTPECutAreasEditor;

class ExportedByCAAMfgTPEAddCmdInCutAreaToolBar CAAMfgTPEOnePointSelectionUserCom : public CATStateCommand
{

public:
		DeclareResource (CAAMfgTPEOnePointSelectionUserCom,CATStateCommand)

		CAAMfgTPEOnePointSelectionUserCom (void* ipCutAreasEditor);
		virtual ~CAAMfgTPEOnePointSelectionUserCom ();
 
		void BuildGraph();
		CATStatusChangeRC Activate (CATCommand*, CATNotification*);
		CATStatusChangeRC Cancel (CATCommand*, CATNotification*);
		CATStatusChangeRC Desactivate (CATCommand*, CATNotification*);

		void PreActivate (CATCommand* c1, CATNotification* c2, CATCommandClientData c3);
		void Move (CATCommand* c1, CATNotification* c2, CATCommandClientData c3);
		void EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData);

		CATBoolean SelectPoint (void*);
		CATBoolean HasPoint (void*);

		//---- Pour ODT
		void Valuate ( const CATMathPoint& point);

private:

	CATIMfgTPECutAreasEditor* _pCutAreasEditor;

	CATDialogAgent*         _PointAgent;

	CATSelector*   _Selector;

	CATMathPoint   _CurrentPoint;
	CAT3DViewer*	_Viewer;

	CATCallback    _PreactivateCB; 
	CATCallback    _MoveCB; 
	CATCallback    _EndPreactivateCB; 

	CATBoolean _HasPoint;
};
#endif 

