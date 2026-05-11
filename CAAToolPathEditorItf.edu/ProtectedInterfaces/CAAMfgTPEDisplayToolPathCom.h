/* -*-cCAAMfgTPEDisplayToolPathComCAAMfgTPEDisplayToolPathCom-*- */
#ifndef CAAMfgTPEDisplayToolPathCom_H
#define CAAMfgTPEDisplayToolPathCom_H
//
//=============================================================================
//
// Class CAAMfgTPEDisplayToolPathCom:
//
//=============================================================================
// Usage Notes:
//

#include "CATStateCommand.h"
#include "CAAMfgTPEDisplayToolPathCommand.h"

class CATPathElementAgent;
class CAT3DViewer;
class CATDialogAgent;
class CATPathElement;
class CATVisManager;
class CATIContainer_var;
class CATIMfgToolPath_var;

class ExportedByCAAMfgTPEDisplayToolPathCommand CAAMfgTPEDisplayToolPathCom : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMfgTPEDisplayToolPathCom,CATStateCommand)
    
      CAAMfgTPEDisplayToolPathCom (CATString* argument);
      virtual ~CAAMfgTPEDisplayToolPathCom();
      void BuildGraph();
		void Valuate (const CATBaseUnknown_var& iValue);  

	private :

		// to Create the rep of the tool path
		void CreateController();
		// Delete the rep of the tool path
		void DeleteController();
		// To update the rep of the tool path
		void DispatchInfo();

		//  To Get the factory of tool pathes.
		HRESULT GetToolPathFactory (CATIContainer_var& oContainer);

		// To get the tool path
		boolean GetSelection (void* data);
		// To Terminate the command
		boolean End (void* data);

		CATIMfgToolPath_var _ToolPath;

		CAT3DViewer*		 _Viewer;
		CATPathElementAgent* _TPSelectionAgent;
		CATDialogAgent*	_TPEndAgent ;

		CATPathElement* _ToolPahVisu;
		IID*            _iid;
		CATVisManager*  _VisuManager;
      
};
#endif
