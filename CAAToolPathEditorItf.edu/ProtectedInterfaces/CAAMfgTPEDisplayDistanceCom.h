//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// Class CAAMfgTPEDisplayDistanceCom
//
//===================================================================
//
#ifndef CAAMfgTPEDisplayDistanceCom_H
#define CAAMfgTPEDisplayDistanceCom_H

#include "CATStateCommand.h"
#include "CAAMfgTPEAddToolBar.h"

#include "CATIMfgToolPath.h"
#include "CATMathPoint.h"
#include "CATNotification.h"

class CATPathElementAgent;
class CAT3DViewer;

class CATDialogAgent;
class CATPathElement;
class CATVisManager;
class CATRep;
class CAT3DPointRep;
class CAT3DCustomRep;
class CATSelector;

class ExportedByCAAMfgTPEAddToolBar CAAMfgTPEDisplayDistanceCom : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMfgTPEDisplayDistanceCom,CATStateCommand)
    
      CAAMfgTPEDisplayDistanceCom (CATString* argument);
      virtual ~CAAMfgTPEDisplayDistanceCom();

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
		CATBoolean GetSelection (void* data);
		// To Terminate the command
		CATBoolean End (void* data);

		// To display the distance between two points.
		void DisplayDistance();

		// To create the selector of points
		void SetSelector();

		// Processing of events.
		void PreActivate (CATCommand*, CATNotification*, CATCommandClientData);
		void Move (CATCommand*, CATNotification*, CATCommandClientData);
		void EndPreActivate (CATCommand*, CATNotification*, CATCommandClientData);
		// To process the selection of a point.
		void ActivateSelector (CATCommand*, CATNotification*, CATCommandClientData);

		// To remove the rep of the distance.
		void RemoveDistanceRep();
		//  To remove the rep of the point.
		void RemovePointRep();

		// To convert a length in the current unit.
		void ConvertLengthInUnit(double iLength, CATUnicodeString& ioLengthinUnit);

		CATIMfgToolPath_var _ToolPath;

		CAT3DViewer*		   _Viewer;
		CATPathElementAgent* _TPSelectionAgent;
		CATDialogAgent*	   _TPEndAgent ;
		CAT3DCustomRep*      _DistanceRep;

		CATMathPoint _FirstPoint, _SecondPoint;

		CATPathElement* _ToolPahVisu;
		IID*            _iid;
		CATVisManager*  _VisuManager;

		CAT3DPointRep*     _CurrentPointRep;
		CATSelector*      _Selector;    
		
		double _Distance ;
	   boolean _hasFirstPoint, _hasSecondPoint;
      
};
#endif
