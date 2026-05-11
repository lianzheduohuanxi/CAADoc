---
title: "Managing Variables and Operation States for Behavior Command"
category: "use case"
module: "CAABehUseCases"
tags: ["CAAOBMInterfaces", "CAAOBMInterfacesCommand", "CATIType_var", "CAAOBMInterfacesProduct", "CATIDocRoots", "CATICkeParm", "CATIValue", "CATIConnector_var", "CATIVariableManagement", "CATIBehOperationManagement_var", "CATICkeParm_var", "CATIBehOperationManagement", "CATICkeParmFactory_var", "CATIPrdObjectPublisher_var", "CATILinkableObject_var", "CAAOBMInterfacesDlg", "CATIVariableManagement_var", "CAAOBMInterfacesCmd", "CAAOBMInterfacesPart", "CATIProduct_var"]
source_file: "Doc\online\CAABehUseCases\CAABehOpAndVarMgt.htm"
converted: "2026-05-11T17:33:49.917165"
---

3D PLM Enterprise Architecture |  Business Process Knowledge Template |  Managing Variables and Operation States for Behavior Command _Managing Variables of BKT Objects and Operation States for a Behavior Command launching a CAA Command._  
---|---|---  
Use Case  
  
* * *

Abstract This Use Case shows how to code a CAA command launched by a behavior command and also how to manipulate the variables of BKT Objects (behaviors or types). 
    * **What You Will Learn With This Use Case**
    * **The CAAOBMInterfacesCmd Use Case**
      * What Does CAAOBMInterfacesCmd Do
      * How to Launch CAAOBMInterfacesCmd
      * Where to Find the CAAOBMInterfacesCmd Code
    * **Step-by-Step**
    * **In Short**
    * **References**  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to show how to control the execution of a behavior command. It is illustrated through a CAA command called by a behavior command. The control of the states of the behavior will guaranty the synchronicity of the behavior and the CAA command in order to avoid any side effects. It also demonstrates how to access to the variables (attributes) of a behavior or of a technological object and how to manage them.                                                                                                                                                                                                                                    [Top] The CAAOBMInterfacesCmd Use Case CAAOBMInterfacesCmd is a use case of the CAAOBMInterfaces.edu framework that illustrates the CATOBMInterfaces and the CATBehaviorInterfaces frameworks capabilities. [Top] What Does CAAOBMInterfacesCmd Do First, the CAAOBMInterfacesCmd Use Case is based on pre-existing data:     - a catalog (.CATfct) where is defined a BKT type (also called technological object) with its variables (attributes) and its behaviors. A behavior has also its own variables.                     ![](Images/CAABeh1.gif)     - a product containing a part with publications.                     ![](Images/CAABehProduct.jpg) First, you will have to type the product with the BKT type/technological object. The BKT type has a main behavior called "**SequentialCombination** " containing itself one behavior command called "**Command** " which is dedicated to launch a CAA Command. The CAAOBMInterfacesCmd use case implements this command which launches a simple dialog dedicated to valuate some variables of the BKT type and of its behavior. In the command code, you will see how to control the execution of the behavior once it has launched the CAA Command in order to synchronize both so that the behavior doesn't finish before the end of its command.  In the dialog code, you will see what kind of action you can have on the attributes of BKT Objects. [Top] Where to Find the CAAOBMInterfacesCmd Code The CAAOBMInterfacesCmd use case is made of classes and resources located in the CAAOBMInterfacesCmd.m module and in the CNext\resources\graphic directory of the CAAOBMInterfaces.edu framework: Windows | ` InstallRootDirectory\CAAOBMInterfaces.edu\CAAOBMInterfacesCmd.m\`  
---|---  
Unix | ` InstallRootDirectory/CAAOBMInterfaces.edu/CAAOBMInterfacesCmd.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. These classes and interfaces are: _CAAOBMInterfacesCommand_ | CAA Command description class  
---|---  
_CAAOBMInterfacesDlg_ | Dialog description class  
_CAAOBMInterfaces.CATfct_ | Catalog describing a BKT type with its attributes and behaviors  
_CAAOBMInterfacesProduct.CATProduct_ | Product to be typed  
_CAAOBMInterfacesPart.CATPart_ | Part contained in the Product  
[Top] How to Launch CAAOBMInterfacesCmd Open the catalog CAAOBMInterfaces.CAFct and create the associated workbench with the dedicated command in the BKT toolbar.         ![](Images/CAABehHammer.jpg)                     ![](Images/CAABehWkb.jpg) Open the CAAOBMInterfacesProduct.CATProduct. Select the product and click on this icon ![](Images/CAABehFinger.jpg) to initialize the BKT context. Select the product and click on this icon ![](Images/CAABehType.jpg) to type the product with the BKT type. As a result you can see : ![](Images/CAABehTypedProduct.jpg) The product is now typed by the technological object.   To launch the execution of the use case itself , executes the sequence of behaviors of the extended product. To do so, from its submenu, select the command Type->SequentialCombination ![](Images/CAABehExeSequence.jpg)   It opens the following dialog dedicated to manipulate variables:   ![](Images/CAABehDialog.jpg) [Top] Step-by-Step 1 | Create a CAA Command dedicated to be launched by a behavior command |    
---|---|---  
2 | Manage the states of the behavior command from the CAA command |    
3 | Manage the variables of BKT Objects |    
[Top] Create a CAA Command dedicated to be launched by a Behavior A BKT type may have behaviors of different types. One of them is the behavior Command which launches a CAA command. This one is a CATStateCommand and in argument of its constructor you must absolutely precise the behavior. This is to allow the communication between the behavior and its command in order to be synchronous during the execution of the command. Its header file CAAOBMInterfacesCommand.h is as follows  

    
    class CAAOBMInterfacesCommand: public CATStateCommand
    {
    
    DeclareResource( CAAOBMInterfacesCommand, CATStateCommand )
    
    public:
    CAAOBMInterfacesCommand();
    CAAOBMInterfacesCommand(CATBaseUnknown *iBehavior);
    virtual ~CAAOBMInterfacesCommand();
    
    
    ...
    
    }  
  
---  
[Top] Manage the States of the Command Behavior from the CAA Command Most of the time, the behaviors  of a technological object are executed sequentially. In this Use Case, one of the behaviors is a behavior command launching a CAA command. If we don't take the control of the execution of the behavior command during the execution of the CAA command, the behavior engine will continue to execute the sequence of behaviors. This can be problematic if one of the behavior following the behavior command is waiting as an input, an output of the CAA command. That's why we strongly advise you to control the operations thanks to the _CATIBehOperationManagement_ interface. First, the constructor of the CAA command has to look like this:
    
    CAAOBMInterfacesCommand::CAAOBMInterfacesCommand(CATBaseUnknown *iBehavior) :
    CATStateCommand ("CAAOBMInterfacesCommand", CATCommandMsgRequestSharedMode) 
    {
    _Behavior = iBehavior;
    
    CATIBehOperationManagement_var Manage = _Behavior;
    
    Manage->Start();
    
    ...
    
    Manage->Suspend();
    }  
  
---  
The behavior in argument must be stored in a data member of the command to be always accessible. From the behavior, get a handler on the _CATIBehOperationManagement_. With this api, you will be able to start, suspend, cancel or finish the behavior. In the constructor, start the behavior at the beginning and suspend it at the end. Do exactly the same in the BuildGraph, Activate and Desactivate methods and in any other methods you will create in your own command. The call to the Start and __ Suspend methods of the _CATIBehOperationManagement_ interface have to bracket the code of these methods. The BuildGraph method defines the state chart of the command and instanciates the dialog to manage the attributes of the BKT Objects. The behavior Command is passed in argument of the dialog constructor. The Cancel method of the command is called at the end, just before its destruction.
    
    CATStatusChangeRC CAAOBMInterfacesCommand::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
    {
    CATIBehOperationManagement_var Manage = _Behavior;
    ...
    Manage->Start();
    ...
    
    if(_OK->IsOutputSet())
    Manage->Done();
    
    if(_Cancel->IsOutputSet())
    Manage->Cancel();
    ...
    }  
  
---  
The command may have stopped of different manners. At the beginning of the Cancel method, we start the behavior. At the end, the state of the behavior depends on the interaction of the user to finish the command. If the user has clicked on the OK button, the behavior is stopped properly (status Done). If the user has cancelled the dialog, the behavior is cancelled. As a consequence, the behavior command is in an error state and the behavior sequence will be interrupted ** _OK **and ** _Cancel **are dialog agents associated to the OK and Cancel button of the dialog. You don't have to manage the state of the behavior in the destructor, because it has been done in the Cancel method. [Top] Manage the Variables of BKT Objects. The Dialog opened thanks to the CAA Command allows some actions on the variables of the extended product and of the behavior:                                         ![](Images/CAABehDialog.jpg)
    1. Valuation of the string variable "Beh_Out2" of the behavior command.
    2. Creation of a link between the variable "Beh_In1" of the behavior command and the variable "AttOnType" of the extended product. 
    3. Modification of the type of the attribute "P1" of the behavior command.
    4. Valuation of the attribute "P1" of the behavior with a publication.
The management of those variables is done with the _CATIVariableManagement_ api. 1. Valuation of a behavior variable. In the panel, modify the value "Default" of the variable Beh_Out2 and then click on the Apply button close to the field.  As a resut, if you put the mouse on the attribute Beh_Out2 in the specification tree, a tooltip appears containing the new value. The executed code is the following: 
    
    CATICkeParmFactory_var **CkeParmFactory** = CATCkeGlobalFunctions::GetVolatileFactory();  
  
---  
First, we get the volatile factory to create values from KnowledgeInterfaces.
    
    CATICkeParm_var hValueParmReal;
    
    hValueParmReal =**CkeParmFactory** ->CreateString("StringOnBeh",EdtValue);  
  
---  
Then, we create a string parameter with the value EdtValue entered in the edit field of the panel.
    
    CATIValue* **ValueParm** = NULL;
    
    HRESULT rc = hValueParmReal->QueryInterface(IID_CATIValue, (void**) &**ValueParm**);  
  
---  
From the parameter  hValueParmReal __ which is a _CATICkeParm_ , we query a _CATIValue_ , necessary for the _CATIVariableManagement_ api.
    
    CATIVariableManagement_var hVarMngt = _Behavior;
    CATUnicodeString VarName = "Beh_Out2";
    ...
    hVarMngt->**SetVariableValue**(&VarName,tio_OUT,**ValueParm**);  
  
---  
We get the CATIVariableManagement handler from the behavior (_Behavior was initialized during the dialog constructor), and we valuate its attribute "Beh_Out2" with the _CATIValue_ ValueParm created just before. 2. Creation of a Link between 2 variables. In the panel, click on the Apply button to link the AttonType and the Beh_In1 attributes. As a resut, if you put the mouse on the attribute Beh_In1 in the specification tree, a tooltip appears containing the name of the linked attribute AttonType. The executed code is the following: 
    
    CATFrmEditor * editor = CATFrmEditor::GetCurrentEditor();
    CATDocument * pDoc = editor->GetDocument();
    
    CATIDocRoots *piDocRootsOnDoc = NULL;
    ...
    HRESULT rc = pDoc -> QueryInterface(IID_CATIDocRoots,(void**)&piDocRootsOnDoc);
    
    CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc -> GiveDocRoots();
    ...
    
    CATIProduct_var **root_product** ;
    **root_product** = (*pRootProducts)[1];
    ...  
  
---  
First, we query the list of document roots and we retrieve its first item which is the root product.
    
    CATIVariableManagement_var ProdVarMngt = **root_product** ;
    CATIVariableManagement_var BehVarMngt = _Behavior;  
  
---  
Then, we get both CATIVariableManagement handler from the extended product and its behavior command (_Behavior was initialized during the dialog constructor).
    
    CATBaseUnknown* pAttOnType = NULL;
    CATUnicodeString VarNameType = "AttonType";
    
    HRESULT hr = ProdVarMngt->**GetVariable**(&VarNameType, tio_IN,&pAttOnType);  
  
---  
From the extended product, we get its attribute AttonType.
    
    CATUnicodeString VarNameBeh = "Beh_In1";
    
    hr = BehVarMngt->**LinkVariables**(&VarNameBeh,tio_IN,pAttOnType);  
  
---  
We link the variable Beh_In1 of the behavior with the variable AttonType of the extended product. 3. Modification of the type of a variable. In the panel, select in the combo box a new type for the variable P1 of the behavior command and click on the Apply button close to the combo. P1 is a variable of type pointer. A pointer variable can point on an object of any kind of knowledgeware type. In our example, the available types are **Part** , **Product** and **ObjectType**. ObjectType is a generic type for all kind of values and objects. As a resut, if you put the mouse on the attribute P1 in the specification tree, a tooltip appears containing the waited type for the object pointed by P1. The executed code is the following:  CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();   
---  
First, we get the dictionary of type. CATIType_var TheType = dico->FindType(SelectedType, **TheType**);   
---  
Then, we get the new type to associate to P1. TheType is the value selected in the combo box. CATIVariableManagement_var BehVarMngt = _Behavior;   
---  
We get the CATIVariableManagement interface from the behavior. CATUnicodeString VarName = "P1";  
  
HRESULT HR = BehVarMngt->**SetVariableType**(&VarName,tio_IN,**TheType**);  
---  
We change the type of the variable P1. 4. Valuation of a behavior variable with a publication. In the panel, enter the name of the publication which will be pointed by the variable P1 and click on the Apply button close to the text field. In this use case, the available publications are in the part _CAAOBMInterfacesPart.CATPart_ : **" My Face"** and **" Hole"**. The variable P1 has to have the type ObjectType to be able to point one of these publication. As a resut, if P1 is of the correct type, if you put the mouse on it in the specification tree, a tooltip appears containing the path of the document containing the publication. The executed code is the following:  CATIPrdObjectPublisher_var RootPrd_Publications = root_product;  
  
CATBaseUnknown* RetrievedPub = RootPrd_Publications->GetFinalObject(**PubName**);  
   
---  
First we get the root product as done before (root_product). And then we get the publications manager on the root product in order to search the publication PubName specified in the valuation field. CATIConnector_var Connector = RetrievedPub;   
CATILinkableObject_var **LinkObj** = Connector->GiveReferenceObject();  
---  
We get the object in the publication. CATICkeParmFactory_var CkeParmFactory = CATCkeGlobalFunctions::GetVolatileFactory();  
   
CATICkeParm_var PubRef = CkeParmFactory->CreateObjectReference(**LinkObj**);   
---  
We get the volatile factory to create a parameter feature reference from the published object.
    
    CATIValue* **ValuePub** = NULL;
    
    HRESULT rc = PubRef ->QueryInterface(IID_CATIValue, (void**) &**ValuePub**);  
  
---  
From the parameter PubRef which is a _CATICkeParm_ , we query a _CATIValue_ , necessary for the _CATIVariableManagement_ api.
    
    CATIVariableManagement_var hVarMngt = _Behavior;
    ...
    CATUnicodeString VarName = "P1";
    rc = hVarMngt->SetVariableValue(&VarName, tio_IN,ValuePub);  
  
---  
We get the CATIVariableManagement handler from the behavior (_Behavior was initialized during the dialog constructor), and we valuate its attribute "P1" with the _CATIValue_ ValuePub created just before.

* * *

In Short When using a behavior command launching a CAA command, don't forget to control the state of the behavior during the execution of the command thanks to the _CATIBehOperationManagement_ interface. With the _CATIVariableManagement_ interface, you are able to access and control the variables of behaviors and types. [Top]

* * *

References [1] |     
---|---  
[2] |     
[3] |    
[Top]  
  
* * *

History Version: **1** [Jul 2005] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
