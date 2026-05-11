---
title: "Creating an Add-in"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrFilletHdr", "CAAAfrGeoCreationWkbAddin", "CAAGeometry", "CAAAfrOperationToolsMnu", "CAAAfrUnionHdr", "CAAAfrTFilletStr", "CAAAfrGeoOperationAdnHeader", "CAAAfrSubstractHdr", "CATImplementClass", "CAAAfrGeoOperationAdn", "CAAAfrMFilletStr", "CAAAfrOperationMbr", "CAAAfrMSubstractStr", "CAAApplicationFrame", "CAAAfrTSubstractStr", "CAAAfrOperationTlb", "CAAAfrGeoOperationAddin", "CAAAfrOperationToolsSep", "CAAAfrTUnionStr", "CAAIAfrGeoCreationWkbAddin"]
source_file: "Doc\online\CAAAfrUseCases\CAAAfrSampleAddin.htm"
converted: "2026-05-11T17:17:55.625620"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### Creating an Add-in

_Customizing a workshop or a workbench_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to create an add-in. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrGeoOperationAdn Use Case**
    * What Does CAAAfrGeoOperationAdn Do
    * How to Launch CAAAfrGeoOperationAdn
    * Where to Find the CAAAfrGeoOperationAdn Code
  * **Step-by-Step**
  * **Troubleshooting**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

This use case is intended to show how to create an add-in to a given workbench. An add-in is an object that gathers commands to work on the document and arrange them in one or several toolbars and menu items. Command headers are used to make the link between the add-in and the commands.

[Top]

### The CAAAfrGeoOperationAdn Use Case

CAAAfrGeoOperationAdn is a use case of the CAAApplicationFrame.edu framework that illustrates the ApplicationFrame framework capabilities.

[Top]

#### What Does CAAAfrGeoOperationAdn Do

The CAAAfrGeoOperationAdn use case creates an add-in to the **CAA Geometrical Creation** workbench for the CAAGeometry document. Is is made up of:

  *  a single toolbar.
![CAAAfrGeomAddinToolbar.jpg \(2966 bytes\)](images/CAAAfrGeomAddinToolbar.jpg) | The **Operation** toolbar. It includes three commands: Union, Subtract, and Fillet.  
---|---  
  * menu items 
![CAAAfrGeomAddinToolbar.jpg \(2966 bytes\)](images/CAAAfrGeomAddinMenu.jpg) |  It includes three commands: Union, Subtract, and Fillet and a separator just after Conferencing.  
---|---  



[Top]

#### How to Launch CAAAfrGeoOperationAdn

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)" use case for a detailed description of how this use case should be launched.

Do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 

  * Select File->New
  * In the New box, select CAAGeometry and click OK
  * If the Operation toolbar is not displayed, right click on a toolbar and select it in the contextual menu to make it appear.
  * If you can't find it in the menu, select Start->Infrastructure->CAA V5 :Geometrical Creation  to reset the workbench.



[Top]

#### Where to Find the CAAAfrGeoOperationAdn Code

The CAAAfrGeoOperationAdn use case is made of a single class named _CAAAfrGeoOperationAdn_ located in the CAAAfrGeoCreationWkbAddin.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrGeoCreationWkbAddin.m\`  
---|---  
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeoCreationWkbAddin.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

To create the add-in, you should create the module directory to store the add-in code along with its two subdirectories LocalInterfaces and src. For this example, this directory is named CAAAfrGeoOperationAdn.m and can be found in the CAAApplicationFrame.edu framework. Then you will need to create the following files.

In the CAAAfrGeoOperationAdn.m\LocalInterfaces directory:  
---  
CAAAfrGeoOperationAdn.h | The header file of the add-in description class  
In the CAAAfrGeoOperationAdn.m\src directory:  
CAAAfrGeoOperationAdn.cpp | The header file of the add-in description class  
In the dictionary, that is the CNext\code\dictionary directory, referenced at run time using the CATDictionaryPath environment variable, create or update:  
CAAApplicationFrame.edu.dico | The interface dictionary  
In the CNext\resources\msgcatalog directory, referenced at run time using the CATMsgCatalogPath environment variable:  
CAAAfrGeoOperationAdn.CATNls | The add-in message file  
CAAAfrGeoOperationAdnHeader.CATNls and  
CAAAfrGeoOperationAdnHeader.CATRsc | The command header resource files  
  
To create the CAA Geometrical Creation workbench, there are four steps:

# | Step | Where  
---|---|---  
1 | Create the add-in description class | LocalInterfaces and src  
2 | Create the command headers | `CreateCommands` method  
3 | Create the add-in and arrange the commands | `CreateToolbars` method  
4 | Provide the resources | Resource files  
  
[Top]

#### Creating the Add-in Description Class

  1. Create the CAAAfrGeoOperationAdn.h file 
         
         #include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown
         
         class CATCmdContainer;       // Needed by CreateToolbars
         
         class CAAAfrGeoOperationAdn : public CATBaseUnknown
         {
           CATDeclareClass;
           public:
              CAAAfrGeoOperationAdn();
              virtual ~CAAAfrGeoOperationAdn();
         
              void CreateCommands();
              CATCmdContainer * CreateToolbars();
         };  
  
---  
  2. Create the CAAAfrGeoOperationAdn.cpp file 
         
         // Local Framework
         #include "CAAAfrGeoOperationAdn.h"
         
         // ApplicationFrame Framework 
         #include <CATCreateWorkshop.h>    // To use NewAccess - SetAccess - SetAccessChild ...
         
         // Declaration of a new Command Header Class 
         #include "CATCommandHeader.h"        // See Creating the Command Headers
         MacDeclareHeader(CAAAfrGeoOperationAdnHeader);  
         
         CATImplementClass(CAAAfrGeoOperationAdn, DataExtension,
                           CATBaseUnknown, CAAAfrGeoOperationAddin);
         
         #include <TIE_CAAIAfrGeoCreationWkbAddin.h>
         TIE_CAAIAfrGeoCreationWkbAddin(CAAAfrGeoOperationAdn);
         
         CAAAfrGeoOperationAdn::CAAAfrGeoOperationAdn()
         {}
         
         CAAAfrGeoOperationAdn::~CAAAfrGeoOperationAdn()
         {}
         
         void CAAAfrGeoOperationAdn::CreateCommands()
         {
           ... // See Creating the Command Headers
         }
         
         CATCmdContainer * CAAAfrGeoOperationAdn::CreateToolbars()
         {
           ... // See Creating the Toolbar and Arranging the Commands
         }
           
  
---  
  
The _CAAAfrGeoOperationAdn_ class states that it implements the _CAAIAfrGeoCreationWkbAddin_ interface thanks to the `TIE_CAAIAfrGeoCreationWkbAddin` macro. The `CATImplementClass` macro declares that the _CAAAfrGeoOperationAdn_ class is a data extension, thanks to the `DataExtension` keyword, that extends _CAAAfrGeoOperationAddin_. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. The name of the latetype, the fourth argument of the CATImplementClass macro, mustn't be the same as an existing C++ class name or an existing latetype name.

  3. Updating the Dictionary 

Update the interface dictionary, that is a file named, for example, CAAApplicationFrame.dico, whose directory's pathname is concatenated at run time in the CATDictionaryPath environment variable, and containing the following declaration to state that the _CAAAfrGeoOperationAddin_ component implements the _CAAIAfrGeoCreationWkbAddin_ interface, and whose code is located in the libCAAAfrGeoCreationWkbAddin shared library or DLL.
         
         CAAAfrGeoOperationAddin CAAIAfrGeoCreationWkbAddin libCAAAfrGeoCreationWkbAddin  
  
---  
  
Note that the component main class name is used to refer to the component in the interface dictionary, and never the extension class names. Note also that the shared library or DLL to associate with the component/interface pair is the one that contains the code created by the call to the TIE macro (This is generally the same library than the one that contains the interface implementation code, since the TIE macro is usually included in the extension class source file.) This is because when a client asks a component for an interface pointer, the TIE class is instantiated first, and it either retrieves the existing instance of the appropriate extension class, or otherwise instantiates it.




[Top]

#### Creating the Command Headers

This is done by the `CreateCommands` method. Each command available in your add-in must have a command header. A command header is an instance of a command header class, and different commands can share the same command header class to create their command header. Refer to The Command Headers for more details.

A command header class is created for the commands, named CAAAfrGeoOperationAdnHeader using the `MacDeclareHeader` macro. 

  1. Create the CAAAfrGeoOperationAdnHeader command header class. To do this, add the following in CAAAfrGeoOperationAddin.cpp: 
         
         #include "CATCommandHeader.h"
         MacDeclareHeader(CAAAfrGeoOperationAdnHeader);  
  
---  
  
The `MacDeclareHeader` macro creates the header file and the source file for the CAAAfrGeoOperationAdnHeader class, and associates with this class the resource files CAAAfrGeoOperationAdnHeader.CATNls and CAAAfrGeoOperationAdnHeader.CATRsc. See Providing the Resources.

  2. Create the command headers in the empty `CreateCommands` method. This method should contain one instantiation statement of the command header class per command header. Each statement has the following form, for example for the Union command. 
         
         void CAAAfrGeoOperationAdn::CreateCommands()
         {
           ...
           new CAAAfrGeoOperationAdnHeader("Union", "CommandLib",
                                           "UnionCmd", (void *)NULL):
           ...
         }    
  
---  
  
The command header constructor has the following arguments: 
     * `Union` is the identifier you need to assign to the command header. It will be used afterwards: 
       * To associate the command starters you will define to put the command in a menu and in toolbars with the command header. This is done for this add-in in Creating the Toolbar and Arranging the Commands.
       * To build the variables that define the command header resources, such as the help messages seen by the end user in his/her own language, or the icon to display in the toolbar. This is explained in Providing the Resources
     * `CommandLib` is the name of the shared library or DLL containing the Union command's code, without the prefix lib, and without the suffix depending on the operating system.
     * `UnionCmd` is the name of the Union command class
     * the last argument is the possible pointer to the object to pass to the command when executing it. It is often a character string that indicates the action to carry out when the same command can perform several actions depending on the active document and data, such as "update" or "update all", or "cut" or "copy".



[Top]

#### Creating the Toolbar and Arranging the Commands

Finally, we'll create the toolbar and arrange the commands. This is the job of the `CreateToolbars` method.

  * Creating the toolbar 
        
        CATCmdContainer * CAAAfrGeoOperationAdn::CreateToolbars()
        {
          NewAccess(CATCmdContainer,pCAAAfrOperationTlb,CAAAfrOperationTlb);
        
              NewAccess(CATCmdStarter,pCAAAfrTUnionStr,CAAAfrTUnionStr);
              SetAccessCommand(pCAAAfrTUnionStr,"CAAAfrUnionHdr");
              SetAccessChild(pCAAAfrOperationTlb,pCAAAfrTUnionStr);
        
              NewAccess(CATCmdStarter,pCAAAfrTSubstractStr,CAAAfrTSubstractStr);
              SetAccessCommand(pCAAAfrTSubstractStr,"CAAAfrSubstractHdr");
              SetAccessNext(pCAAAfrTUnionStr,pCAAAfrTSubstractStr);
        
              NewAccess(CATCmdStarter,pCAAAfrTFilletStr,CAAAfrTFilletStr);
              SetAccessCommand(pCAAAfrTFilletStr,"CAAAfrFilletHdr");
              SetAccessNext(pCAAAfrTSubstractStr,pCAAAfrTFilletStr);
        
          AddToolbarView(pCAAAfrOperationTlb,-1,Right); // Invisible toolbar
        		 
          ...
        }  
  
---  
  
Here is what's happen: 
    * The Operation toolbar is created as an instance of the CATCmdContainer class using the `NewAccess` macro. pCAAAfrOperationTlb is the variable used to handle the Operation toolbar command container instance pointer, and CAAAfrOperationTlb is the identifier used to refer to it in the add-in resource files. This identifier must be unique among all the toolbar identifiers that can be found within the application [1]. The Operation toolbar default location is defined using the `AddToolbarView` macro, where `-1` means that the toolbar is invisible by default (`1` means visible), and `Right` means that the toolbar is docked at the right side of the application window.
    * Three macros are required for each command. For example, the Union command is processed as follows: 
      1. First, the command starter is created as a CATCmdStarter instance using the `NewAccess` macro. pCAAAfrTUnionStr is the variable used to handle a pointer to that instance, and CAAAfrTUnionStr is its identifier.
      2. Then the Union command header is associated with this command starter using the `SetAccessCommand` macro. The second parameter is the Union command header identifier defined as the first parameter of the command header constructor. Refer to Creating the Command Headers
      3. Finally the Union command starter is set as the child of the Boolean Operations toolbar.

Proceed in the same way for the other commands, except that they are set as next of one another using the `SetAccessNext` macro.

  * Creating the menu items 
        
        CATCmdContainer * CAAAfrGeoOperationAdn::CreateToolbars()
        {
          ...
          **NewAccess**(CATCmdContainer,pCAAAfrOperationMbr,CAAAfrOperationMbr);
        
               NewAccess(CATCmdContainer,pCAAAfrOperationToolsMnu,**CATAfrToolsMnu**);
               SetAccessChild(pCAAAfrOperationMbr,pCAAAfrOperationToolsMnu);
        
                 NewAccess(**CATCmdSeparator** ,pCAAAfrOperationToolsSep,CAAAfrOperationToolsSep);
                 SetAccessChild(pCAAAfrOperationToolsMnu,pCAAAfrOperationToolsSep);
        
                 NewAccess(**CATCmdStarter** ,pCAAAfrMUnionStr,CAAAfrMUnionStr);
                 SetAccessCommand(pCAAAfrMUnionStr,"CAAAfrUnionHdr");
                 SetAccessNext(pCAAAfrOperationToolsSep,pCAAAfrMUnionStr);
        
                 NewAccess(CATCmdStarter,pCAAAfrMSubstractStr,CAAAfrMSubstractStr);
                 SetAccessCommand(pCAAAfrMSubstractStr,"CAAAfrSubstractHdr");
                 SetAccessNext(pCAAAfrMUnionStr,pCAAAfrMSubstractStr);
        
                 NewAccess(CATCmdStarter,pCAAAfrMFilletStr,pCAAAfrMFilletStr);
                 SetAccessCommand(pCAAAfrMFilletStr,"CAAAfrFilletHdr");
                 SetAccessNext(pCAAAfrMSubstractStr,pCAAAfrMFilletStr);
        
            **SetAddinMenu**(pCAAAfrOperationTlb,pCAAAfrOperationMbr);
          ...
        }  
  
---  
  
Here is what's happen: 
    * A container is created to receive all the menus: `pCAAAfrOperationMbr`
    * To modify the Tools menu, identified the `CATAfrToolsMnu` name, a container with the same name is created.
    * The separator is created by the `NewAccess` macro in using the `CATCmdSeparator` keyword.
    * Three macros are required for each command. For example, the Union command is processed as follows: 
      1. First, the command starter is created as a CATCmdStarter instance using the `NewAccess` macro. pCAAAfrMUnionStr is the variable used to handle a pointer to that instance, and CAAAfrMUnionStr is its identifier.
      2. Then the Union command header is associated with this command starter using the `SetAccessCommand` macro. The second parameter is the Union command header identifier defined as the first parameter of the command header constructor. Refer to Creating the Command Headers
      3. Finally the Union command starter is set as the child of the Boolean Operations toolbar.

Proceed in the same way for the other commands, except that they are set as next of one another using the `SetAccessNext` macro.

    * The container, `pCAAAfrOperationMbr`, declared as menu thanks to the `SetAddinMenu` method. The first argument of this method, `pCAAAfrOperationTlb`, is the first chained toolbar, those returned by the method-see the next section. The second argument is the container itself `pCAAAfrOperationMbr`. 

  * Returning the toolbar 
        
        CATCmdContainer * CAAAfrGeoOperationAdn::CreateToolbars()
        {
          ...
        		 
          return pCAAAfrOperationTlb ;
        }  
  
---  
  
The first chained toolbar, `pCAAAfrOperationTlb`,  is returned by this method.




[Top]

#### Providing the Resources

You should provide the resources for the toolbar, the menu and for all its commands. They are classified into the following: 

  * The toolbar's title. The Creating Resources for Workshops and Workbenches article details all the resources [2].
  * The command header resources in the command header resource files: titles, messages, icons, and the accelerators associated with the commands. This is described in Creating Resources for Command Headers [3]



More about Internationalization and resources can be found in Internationalizing Your Client Application.

[Top]

* * *

### Troubleshooting

####  My addin is not available or a system failure occured

![symptom.gif \(111 bytes\)](../CAAIcons/images/symptom.gif) | I create a workbench addin but it's not available, or a system failure occurs.  
---|---  
![solution.gif \(218 bytes\)](../CAAIcons/images/solution.gif) | Check your latetype name in the CATImplementClass macro. The latetype name mustn't be an existing C++ class name or an existing latetype name.  
  
#### A Command Doesn't Display in the Menu Bar or Toolbar

![symptom.gif \(111 bytes\)](../CAAIcons/images/symptom.gif) | I create a command starter for a command, and I arrange it in the menu bar or in a toolbar, but the command doesn't display in the menu bar or toolbar where I place it.  
---|---  
![diagnos.gif \(130 bytes\)](../CAAIcons/images/diagnos.gif) | The command starter is not associated with a command header, and is thus not displayed, since the command cannot be launched without command header.  
![solution.gif \(218 bytes\)](../CAAIcons/images/solution.gif) | Check your `CreateToolbars` method. The command starter must be associated with a command header for the command you want to display thanks to the `SetAccessCommand` macro.  
  
[Top]

* * *

### In Short

An add-in gathers commands to customize a workshop or a workbench without you need to modify the workshop or workbench's code. You simply need to implement the interface that the workshop or workbench exposes for add-ins.

[Top]

* * *

### References

[1] | [Checklist for CAA V5 C++ Naming Rules](../CAADocQuickRefs/CAADocCppNamingRulesChecklist.htm)  
---|---  
[2] | [ Creating Resources for Workshops and Workbenches ](../CAAAfrTechArticles/CAAAfrI18NWorkshop.htm)  
[3] | [ Creating Resources for Command Headers ](../CAAAfrTechArticles/CAAAfrI18NHeader.htm)  
[Top]  
  
* * *

### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Sep 2002] | Menu item addition  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
