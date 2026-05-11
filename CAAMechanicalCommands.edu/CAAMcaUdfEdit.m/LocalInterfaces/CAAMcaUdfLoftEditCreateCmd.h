#ifndef CAAMcaUdfLoftEditCreateCmd_h
#define CAAMcaUdfLoftEditCreateCmd_h
// COPYRIGHT Dassault Systemes 2002
//
//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  It is a command to edit and create a type of user feature.
//  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//  This command enables to edit and create an user feature which comes from
//  the CAAUserFeatureSample user feature reference with the CAAUdfLoft type.
//  
//  This type of user feature has two inputs: two points. The end user selects 
//  a point feature and the name of the feature is displayed in a dialog box. 
//  To help the end user, the current point to select is indicated by the 
//  highlight of the linked editor. It can also pre-visualize the result in
//  the 3D viewer. 
//  
//  This use case illustrates:
//     - how to use the CATPrtPanelStateCmd class
//     - how to instantiate a user feature in an interactive command 
//     
//=========================================================================== 
//  How to launch ?
//  -------------
//  Edit mode:
//
//  In the InstallRootDirectory/CAAMechanicalCommands.edu/InputData you find the 
//  CAAUdfModelWithTypeInst.CATPart document which contains one instance of the
//  CAAUserFeatureSample user feature reference with the CAAUdfLoft type
//    
//    - in Cnext, open this file and double click on the CAAUserFeatureSampleToEdit 
//      feature: the current command is launched
//
//  Create mode:
//    
//    - Select the Generative Shape Design workbench in the Start menu
//    - In the toolbar, User Feature Creation, click on the first icon: the
//      current command is launched. (see CAAMcaUdfAddin.m/LocalInterfaces/CAAMcaUdfAdn.h)
//    
//  where InstallRootDirectory is the directory where the CAA CD-ROM is installed.
//===========================================================================

// MechanicalModelerUI framework
#include "CATPrtPanelStateCmd.h" // To derive from

class CAAMcaUdfLoftDlg ;         // Dialog box to edit the user feature
class CATFeatureImportAgent ;    // To select features
class CATIUdfInstantiate ;       // Interface to instantiate a user feature 
class CATDocument ;              // Used by the RetrieveTheUFRef method
class CATDlgNotify ;             // Dialog box to display the error message
class CATPathElement ;           // input selected

class CAAMcaUdfLoftEditCreateCmd: public CATPrtPanelStateCmd
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAMcaUdfLoftEditCreateCmd.CATNls 
  //    
  //
  CmdDeclareResource( CAAMcaUdfLoftEditCreateCmd, CATPrtPanelStateCmd )

  public:

    // Constructors
    // ------------
    // Two constructors:
    //   * Edit mode  : The forth argument of the CATPrtPanelStateCmd constructor is 0
    //   * Create mode: The forth argument of the CATPrtPanelStateCmd constructor is 1
    //   The mode is retrieved thanks to the GetMode method of the CATMMUIPanelStateCmd 
    //   class, parent class of the CATPrtPanelStateCmd class.
    // The command is exclusive since it modifies data model
    // The command is one shot: It is the recommended style. The end user can replay
    // the command is double clicking on the icon. 


    // Constructor in edition mode
    // 
    CAAMcaUdfLoftEditCreateCmd(CATISpecObject *iObjectToEdit);

    // Constructor in creation mode
    // 
    CAAMcaUdfLoftEditCreateCmd();

    virtual ~CAAMcaUdfLoftEditCreateCmd();

  private:

    // BuildGraph
    // ----------
    // Constructs the agents, the states and the transitions. 
    // In creation mode, the user feature instance is created in this 
    // method, and not in the constructor to have the undo model in case
    // of Cancel exit
    //
    virtual void    	BuildGraph(); 

    // GiveMyPanel
    // -----------
    // Method of the CATMMUIPanelStateCmd class, parent class of the 
    // CATPrtPanelStateCmd class, which returns the edit dialog box (panel) created 
    // in this state command.
    // It is mandatory to override this method, especially if you use the 
    // GetInitialPanelState and the AddPanelState methods of this same 
    // grandparent class. In these two methods a state is created. This state is linked 
    // to agents, conditions and outgoing transitions which depend on the Ok, 
    // Cancel, Preview buttons of the dialog box. Then the dialog box is associated with
    // the state thanks to the CATCommand::AddDialogAgent method. 
    // 
    virtual CATDlgDialog*		GiveMyPanel();

    // CheckInput
    // ----------
    // Method to test the selected object. If the test is OK, the 
    // SelectPoint method will be called.
    //
    virtual CATBoolean CheckInput(void * iUsefuldata); 

    //
    // OkAction
    // --------
    // Callback method called when the end user click on the Ok Button. 
    // In this method,the user feature inputs are modified with the 
    // selected features.
    // In is mandatory to call the CATPrtPanelStateCmd::OkAction at the end
    // of the method to benefit of the update and the error managment. 
    // 
    virtual CATBoolean		OkAction(void * iUsefuldata);  

    //
    // CancelAction
    // ------------
    // Callback method called when the end user click on the Cancel/Close Button. 
    // 
    // In is mandatory to call the CATPrtPanelStateCmd::CancelAction at the end
    // of the method to benefit of the update and the error managment. 
    // 

    virtual CATBoolean		CancelAction(void * iUsefuldata);  

    // PreviewAction
    // -------------
    // Callback method called when the end user click on the Preview Button.
    // In this method,the user feature inputs are modified with the 
    // selected features.
    // In is mandatory to call the CATPrtPanelStateCmd::PreviewAction at the end
    // of the method to benefit of the update and the error managment. 
    //
    virtual CATBoolean		PreviewAction(void * iUsefuldata); 

    // SelectPoint
    // -------------
    // Callback method when the end user select a feature to valuate one input.
    // This method is an action method of the unique loop transition.
    // _spFirstPoint or _spSecondPoint are valuated, it depends on the current editor.
    // This information comes from the CAAMcaUdfLoftDlg dialog box. 
    // As soon as the two points are valuated the OK and the Preview Button are
    // enable.
    // 
    virtual CATBoolean		SelectPoint(void * iUsefuldata);

    // CloseErrorDialogBox
    // -------------------
    // This method unsets the repeat mode if the end user
    // double click on the icon to launch this command. It prevent
    // a loop.
    // 
    virtual CATBoolean		CloseErrorDialogBox(void * iUsefuldata);


    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMcaUdfLoftEditCreateCmd(const CAAMcaUdfLoftEditCreateCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAMcaUdfLoftEditCreateCmd & operator = (const CAAMcaUdfLoftEditCreateCmd &iObjectToCopy);
  
    // Method called in the two constructor to create the edit dialog box
    HRESULT InitCommand();

    // CreateFeature
    // -------------
    // Method to create an instance of the user feature reference CAAUserFeatureSample
    // contained in a Part document given by the CAAMcaUdfLoftFile environment variable.
    // CAAUserFeatureSample must have the CAAUdfLoft type.
    // This instance is created without explicit inputs. 
    // 
    HRESULT CreateFeature();

    // RetrieveTheUFRef
    // ----------------
    // In the document iDocument, we look for the list of user feature references
    // and in this list we look for the CAAUserFeatureSample feature. 
    // This feature implements CATIUdfInstantiate to do the
    // instantiation. 
    //
    HRESULT RetrieveTheUFRef(CATDocument *iDocument, CATIUdfInstantiate ** opIUdf) ;
    
    // InstantiateTheUFRef
    // -------------------
    // One instantiation without explicit inputs is created in the current document. 
    //
    HRESULT InstantiateTheUFRef(CATIUdfInstantiate * pIUdf) ;

    // CheckUserFeatureType
    // --------------------
    // Check that the type of the user feature is an CAAUdfLoft
    //
    HRESULT CheckUserFeatureType(CATISpecObject * iUserFeature);


    // Activate
    // --------------------
    // Creates the UF if first time and in case of creation
    // and manages the current feature in case of OGS aggregation
    //
    CATStatusChangeRC Activate   (CATCommand * iCmd,CATNotification * iNotif);


    // Deactivate
    // --------------------
    // Restores the previous current feature, if the UF is inside an OGS
    //
    CATStatusChangeRC Deactivate (CATCommand * iCmd,CATNotification * iNotif);

    // InitAction
    // ----------
    // Override the CATPartPanelStateCmd 
    //
    CATBoolean InitAction(void * iUseful);

    // BeforeBuildGraph
    // ----------
    // Create the UF in creation mode
    // Keep the current feature to restore
    //
    CATBoolean BeforeBuildGraph();


    // IsUFInsideOGS
    // -------------------
    // Returns TRUE if the UF is inside an OGS
    // otherwise FALSE 
    // 
    HRESULT IsUFInsideOrderedBody(CATBoolean & oIsInsideOrderedBody ) ;

  private:
    
    // 1- To manage error 

    // In the contructors or in the CreateFeature method an error
    // can be detected. We keep the kind of error in a string.
    // This string is a keyword in the NLS file associated with
    // this state command (CAAMcaUdfLoftEditCreateCmd.CATNls).
    // It enables to display a NLS message depending on the error
    //
    CATString              _ErrorKey ;
    
    // The dialog box to display the NLS error message
    CATDlgNotify          * _pErrorDialogBox;

    // If an error occurs in the constructors
    // or in the CreateFeature method the command is stopped
    // just after the apparition of a dialog box which displays
    // the error message. This agent enables to detect the OK
    // notification and to trigger the trabsition towards the
    // Null state.
    CATDialogAgent        * _pAgentErrorDialogBox ; 


    // 2- To manage the edition

    // The edit dialog box to display the inputs (names and roles)
    CAAMcaUdfLoftDlg      * _pInputDialogBox;

    // Agent to select a feature
    CATFeatureImportAgent * _pFeatureAgent ;

    // Features for the inputs
    CATPathElement        * _pFirstPoint ;
    CATPathElement        * _pSecondPoint ;
    CATPathElement        * _pSelectedPath ;

    // The current feature to restore at the end of the command
    // if necessary ( the UF is inside an OGS, and if the creation
    // is canceled or in edition mode )
    //
    CATISpecObject_var      _spSpecObjOnPreviousCurrentFeat ;


};

//----------------------------------------------------------------------

#endif

