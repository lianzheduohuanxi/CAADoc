/* -*-c++-*- */
#ifndef CAAMfgTPESplitToolPathCom_H
#define CAAMfgTPESplitToolPathCom_H
//
//=============================================================================
//
// Class CAAMfgTPESplitToolPathCom:
// Manufacturing Generic Activity Commands
//
//=============================================================================
// Usage Notes:
//

#include "CATStateCommand.h"
#include "CAAMfgTPESplitToolPathCommand.h"


#include "CATIMfgToolPath.h"
#include "CATIMfgTPMultipleMotion.h"
#include "CATIMfgActivity.h"
#include "CATMathPoint.h"
#include "CATNotification.h"

class CATIContainer_var;

class CATPathElementAgent;
class CAT3DViewer;

class CATDialogAgent;
class CATPathElement;
class CATVisManager;
class CATRep;
class CAT3DPointRep;
class CATSelector;

class ExportedByCAAMfgTPESplitToolPathCommand CAAMfgTPESplitToolPathCom : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMfgTPESplitToolPathCom,CATStateCommand)
    
      CAAMfgTPESplitToolPathCom (CATString* argument);
      virtual ~CAAMfgTPESplitToolPathCom();
      void BuildGraph();
		void Valuate (const CATBaseUnknown_var& iValue);  

	private :

		// to Create the rep of the tool path
		void CreateController();
		// Delete the rep of the tool path
		void DeleteController();
		// To update the rep of the tool path
		void DispatchInfo();

		// To get the tool path
		boolean GetSelection (void* data);
		// To Terminate the command
		boolean End (void* data);

		// To split the tool path.
		boolean SplitToolPath();

		// To create the selector of points
		void SetSelector();

		// Processing of events.
		void PreActivate (CATCommand*, CATNotification*, CATCommandClientData);
		void Move (CATCommand*, CATNotification*, CATCommandClientData);
		void EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData);
		// To process the selection of a point.
		void ActivateSelector (CATCommand*, CATNotification*, CATCommandClientData);

		// to search the index of the selected point
	   void SetPreActivatedPoint (CATMathPoint &Point);

		//  To remove the rep of the point.
		void RemovePointRep();

		//  To Get the factory of tool pathes.
		HRESULT GetToolPathFactory (CATIContainer_var& oContainer);

		CATIMfgActivity_var _Activity;
		CATIMfgToolPath_var _ToolPath;
		CATIMfgTPMultipleMotion_var _TPMultipleMotion;

		CAT3DViewer*		 _Viewer;
		CATPathElementAgent* _TPSelectionAgent;
		CATDialogAgent*	_TPEndAgent ;

		int 	_PointNumber;

		CATPathElement* _ToolPahVisu;
		IID*            _iid;
		CATVisManager*  _VisuManager;

		CATRep*            _TPRep;          
		CAT3DPointRep*     _CurrentPointRep;
		CATSelector*      _Selector;        
      
};
#endif
