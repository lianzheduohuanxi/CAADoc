#ifndef CAALifWindow2_h
#define CAALifWindow2_h

// COPYRIGHT DASSAULT SYSTEMES 1999 - 2000

//=============================================================================
//  Abstract
//  --------
//  This window contains a parameter editor as well 
//  as the parameter associated manipulator
//  The parameter to be edited is a length type parameter
//  constrained by a formula.
//  The formula is initially deactivated for the purpose of the use case.
//  A spinner is added to the editor.
//  Using the spinner to modify the parameter value within the range and bounds
//  specified for the manipulator displays a information box.        
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATDlgDocument (Dialog Framework)
//             CATDlgWindow (Dialog Framework)
//               CATDialog (Dialog Framework)
//                 CATCommand (System Framework)
//                   CATEventSubscriber (System Framework)
//                     CATBaseUnknown (System Framework)
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h" 
#include "CATICkeParm.h"


// System framework, Events and Callbacks management.
#include "CATNotification.h"

class CATInteractiveApplication; 
class CATICkeParm; 


class CAALifWindow2 : public CATDlgDocument
{
  // Declare the CAALifWindow2.CATNls file as the dialog message catalog
  DeclareResource(CAALifWindow2, CATDlgDocument)

  public:
	/*
	 * Constructor. No initialization is actually done in it.
	 * The real initialization is done in the Build method.
	 */
    CAALifWindow2(CATInteractiveApplication * iParentCommand);

    virtual ~CAALifWindow2();

	//
	// Build
    // -----
    // This method constructs:
    //  
    //   - The Menubar and all Dialog's object for the this interactive object
    //      --> see CreateMenuBar()
	//   - A CATPart document 
	//   - Knowledgeware objects(two parameters, a formula and a manipulator) 
    //   
    void     Build();

  private:

    // Callback on the exit button item of the menubar
    void OnExit  (CATCommand* iMyCommand, 
										   CATNotification* paramNotification,
										   CATCommandClientData myData);

    
    // CreateMenuBar
    // -------------
    // Creates the Menubar which is reduced to a File/Exit option
    //
    void CreateMenuBar();
	

    // DisplayMessage
    // --------------
	// Callback on the change value notification of a parameter.
    // Displays an information box with the new parameter value
    // when the parameter value is modified
	//
	void OnDisplayMessage(CATCallbackEvent parmEvent, 
										   void* publisherObject,
										   CATNotification* paramNotification,
										   CATSubscriberData myData,
										   CATCallback callBackId);
    
    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public
	//
    CAALifWindow2 ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAALifWindow2(const CAALifWindow2 &iObjectToCopy);

  private:


	/* The parent widget (a CATInteractiveApplication instance) */
    CATInteractiveApplication * _pApplication;
	/* The parameter to be edited */
	CATICkeParm_var _spParam1 ;

	CAALifServices* _services;

    };
#endif
