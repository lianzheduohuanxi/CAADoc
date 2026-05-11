#ifndef CAAPriEditSketchCmd_h
#define CAAPriEditSketchCmd_h
// COPYRIGHT Dassault Systemes 2002
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This command is a state command which enables the end user to
//     - Select a Pad 
//     - Edit its profile 
// 
//  This use case illustrates how to use the CATEditAgent class
//     .
//===========================================================================

// DialogEngine framework
#include "CATStateCommand.h" // To derive from
class CATDialogAgent ;
class CATEditAgent   ;
class CATFeatureImportAgent ;

// Visualization framework
class CATPathElement ;

// SpecObjectModeler framework
class CATISpecObject ;

// Local framework
class CAAPriEditSketchDlg ;      // Dialog box associated with the state command

class CAAPriEditSketchCmd: public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAPriEditSketchCmd.CATNls 
  //    
  //
  CmdDeclareResource( CAAPriEditSketchCmd, CATStateCommand )

  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;

  public:

    // Constructor 
    // 
    CAAPriEditSketchCmd();

    virtual ~CAAPriEditSketchCmd();

  private:

    // BuildGraph
    // ----------
    // Constructs the agents, the states and the transitions. 
    //
    virtual void    	BuildGraph(); 

    // Action methods
    // --------------
    
    // SelectPad : called when a Pad has been selected
    CATBoolean SelectPad(void * iUsefuldata);
    CATBoolean UndoSelectPad(void * iUsefuldata);
    CATBoolean RedoSelectPad(void * iUsefuldata);

     // TriggerEditSketch: called when the end user has clicked on the Sketch button
    CATBoolean TriggerEditSketch(void *iUsefuldata) ;

    // EditSketch: called when the end user leaves the stacked workbench (the sketcher)
    CATBoolean EditSketch(void *iUsefuldata) ;


    // Filter method
    // ----------------
    // Filter to test that the Pad has a sketch has profile
    //
    CATBoolean   TestProfile( CATDialogAgent * iAgent, void *iUsefulData);

    // FindProfile
    // -----------
    // This method retrieves the profile from the selected Pad
    //
    HRESULT FindProfile(CATBaseUnknown  * iSelectedPad , 
                        CATISpecObject ** oSpecObjectOnProfile) ;

    // ProvideProfileToEdit
    // -----------------
    // This method returns the path of the object to edit. This method is
    // called by the CATEditAgent instance during its activation. 
    // The path element destruction is done by the CATEditAgent instance
    // 
    CATPathElement * ProvideProfileToEdit(CATClassId iDummy) ;

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchCmd(const CAAPriEditSketchCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPriEditSketchCmd & operator = (const CAAPriEditSketchCmd &iObjectToCopy);
  
  private:

    // The dialog box associated with the command
    CAAPriEditSketchDlg      * _pDialogBox;

    // Agent to enter the Pad
    CATFeatureImportAgent    * _pFeatureAgent ;
 
    // Agent to ask the profile edition 
    CATDialogAgent           * _pTriggerAgent ;

    // Agent to execute the workbench's stack.
    CATEditAgent             * _pEditAgent ;

};

//----------------------------------------------------------------------

#endif

