---
title: "Creating a Command with Options in the "Tools Palette" Toolbar"
category: "use-case case"
module: "CAAAfrUseCases"
tags: "["CAADegTwoPointsBoxUncheckHdr", "CAADegGeoCommands", "CAADegOriginBoxHdr", "CAADegTwoPointsBoxCheckHdr", "CAADialogEngine", "CATIAfrPaletteOptions", "CAAAfrViewerFeedbackHdr", "CAASysCuboid", "CAADegBoxCreationChoiceNotification", "CAADegFourPointsBoxHdr", "CAAGeometry", "CAADegBoxPaletteChoiceCmd", "CAADegCreateBoxPaletteHeader", "CAADegTwoPointsBoxHdr", "CAADegThreePointsBoxHdr", "CAADegCreateBoxCmd", "CATIAfrCmdPaletteOptions"]"
source_file: "Doc/online/CAAAfrUseCases/CAAAfrCmdPalette.htm"
converted: "2026-05-11T17:17:55.606549"
---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating a Command with Options in the "Tools Palette" Toolbar

How to implement CATIAfrCmdPaletteOptions and define options
---|---|---
Use Case

* * *
### Abstract

This article shows how a state command can add "options" in a special toolbar during the life of the command. This special toolbar is named the "Tools Palette" and "options" are command headers. The definition and the usage of options are also explained.

  * **What You Will Learn With This Use Case**
  * **The CAADegCreateBoxCmd Use Case**
    * What Does CAADegCreateBoxCmd Do
    * How to Launch CAADegCreateBoxCmd
    * Where to Find the CAADegCreateBoxCmd Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

The Tools Palette is a special toolbar which updates dynamically when:

  * Entering a workbench - The workbench implements the _CATIAfrPaletteOptions_ interface. [10]

> Command headers are added in the Palette once the workbench is activated, and they are removed from the toolbar after the workbench deactivation.

  * Executing a shared/exclusive command - The command implements the _CATIAfrCmdPaletteOptions_ interface.

> Command headers may be added when the command is activated and they are removed when the command is canceled. For a state command, there is also the possibility to add command headers for a specific state, they are removed when the state is left. When the command is deactivated, the command headers become unavailable.

This use case is intended to show you how to implement _CATIAfrCmdPaletteOptions_  and how to create options using the _CATAfrCheckHeaderAccessor_ class.

[Top]
### The CAADegCreateBoxCmd Use Case

CAADegCreateBoxCmd is a use case of the CAADialogEngine.edu framework that illustrates ApplicationFrame framework capabilities. [Top]
#### What Does CAADegCreateBoxCmd Do

CAADegCreateBoxCmd is a state command to create a box. This command is defined in the CAA V5: Geometrical Creation workbench of the CAAGeometry document [1].  A box is defined by three dimensions: the width (W), the depth (D), and the height (H). The CAADegCreateBoxCmd command gives to the end user the possibility to define three kinds of boxes:                Fig.1 - left                     Fig.1 - center                Fig.1 - right
---

  * P1, the first selected point, defines a point of reference.
  * P2 is the second selected point, it defines with P1 the width of the box.

```vbscript
If the end user finishes the command, the box is a cube.  Fig-1 left

```

  * By indicating a third point (P3), the distance between P2 and P3 defines the depth.

```vbscript
If the end user finishes the command, the box is a parallelepiped where the depth is equal to the height.  Fig-1 center

```

  * By indicating a forth point (P4), the distance between P3 and P4 defines the height .

```vbscript
If the end user finishes the command, the box is a parallelepiped where the depth is equal to the height.  Fig-1 center
The three dimensions of the box are different, it is a parallelepiped. Fig-1 right

The choice between these three kinds of boxes is possible thanks to options set in the Palette. This palette is the "Tools Palette" toolbar. The picture below shows this toolbar and icons added by the state command:

_Fig.2_ | The three icons, surrounded of a circle, enable the end user to create:

```

  * A cube: ![](images/CAACreateBoxSwitchAgentCube.jpg)
  * A parallelepiped where the depth is equal to the height : ![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg)
  * A real parallelepiped: ![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)

These three icons are not always in the palette, it depends on the current state:

  * The three icons are displayed once P1 is selected.
  * The first icon disappears from the Palette as soon as P2 is selected. The end user cannot any more create a cube, he/she can only create a parallelepiped. Only the two lasts are available
  * Once P3 is indicated, the three icons disappear. The end user will create a "real" parallelepiped.

![](images/CAACreateBoxPaletteWithCircle.jpg)
![](images/CAACreateBoxSwitchOrigin.jpg) is already present during the life of the command.

  * The icon is highlighted: The origin of the box is the origin of the model (0,0,0)
  * The icon is normal: The origin of the box is the first selected point

|

The CAADegCreateBoxCmd is a state dialog command that creates a box in the 3D space according to the following UML statechart diagram [2].

Fig.3 ![](images/CAACreateBoxUML.jpg)
---

[Top]
#### How to Launch CAADegCreateBoxCmd

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched.

Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

  * On the **File** menu, click **New**
  * **New** Dialog box click **CAAGeometry** and click **OK**
  * click **Point** and create some points
  * click **Cuboid**
    * Select a point
    * Select a second point
  * click **Cuboid**
    * click ![](images/CAACreateBoxSwitchOrigin.jpg) (the icon is highlighted)
    * Select a point
    * Select a second point
  * click **Cuboid**
    * Select a point
    * click ![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg)
    * Select a second point
    * click ![](images/CAACreateBoxSwitchOrigin.jpg) (the icon is not highlighted any more)
    * indicate a point to define the depth (= height)
  * click **Cuboid**
    * Select a point
    * Select a second point
    * click ![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)
    * indicate a point to define the depth
    * indicate a point to define the height

[Top]
#### Where to Find the CAADegCreateBoxCmd Code

The CAADegCreateBoxCmd use case is made of several classes located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework:

  * The _CAADegCreateBoxCmd_   class

It is the state command which implements the _CATIAfrCmdPaletteOptions_ interface and enables the end user to create a box.

  * The _CAADegBoxPaletteChoiceCmd_   class

The three icons (![](images/CAACreateBoxSwitchAgentCube.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)) are the representation of three check headers. A check header launches a command header for the check state and another one for the uncheck state. These two command headers start the _CAADegBoxPaletteChoiceCmd_ command.

  * The _CAADegBoxCreationChoiceNotification_   class

The three icons (![](images/CAACreateBoxSwitchAgentCube.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)) are the representation of three check headers. A check header launches a command header for the check state and another one for the uncheck state. These two command headers start the _CAADegBoxPaletteChoiceCmd_ command.
It is a notification sent by the previous _CATCommand_ to inform the _CAADegCreateBoxCmd_   class that a check button has been pushed. The notification contains the number of the selected check button.

Windows | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`

It is a notification sent by the previous _CATCommand_ to inform the _CAADegCreateBoxCmd_   class that a check button has been pushed. The notification contains the number of the selected check button.
Windows | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are four logical steps in CAADegCreateBoxCmd:

  1. Defining the CAADegCreateBoxCmd class
  2. Defining Options
  3. Implementing the CATIAfrCmdPaletteOptions Interface
  4. Using Options

[Top]
#### Defining the CAADegCreateBoxCmd class

4. Using Options
The CAADegCreateBoxCmd class is a state command.

  1. Defining the CAADegCreateBoxCmd.h
  2. Defining the CAADegCreateBoxCmd.cpp

  1. Defining the CAADegCreateBoxCmd.h

    // DialogEngine framework
    #include "CATStateCommand.h"
    ...
    class CAADegCreateBoxCmd : public **CATStateCommand**
    {
      **CmdDeclareResource**(CAADegCreateBoxCmd,CATStateCommand);

      **CATDeclareClass** ;

      public :
        CAADegCreateBoxCmd(#);
        virtual ~CAADegCreateBoxCmd(#);

        ...
public :
CAADegCreateBoxCmd(#);
virtual ~CAADegCreateBoxCmd(#);
        virtual CATLISTP(CATCommandHeader) **GetPaletteStateOptions**(#) ;
        virtual CATLISTP(CATCommandHeader) **GetPaletteOptions**(#) ;

```vbscript
      private :

```

        ...
virtual CATLISTP(CATCommandHeader) **GetPaletteStateOptions**(#) ;
virtual CATLISTP(CATCommandHeader) **GetPaletteOptions**(#) ;
private :
        virtual void **BuildGraph**(#) ;
        CATBoolean  **CheckChoice**(void * iChoice);
        CATBoolean  **CreateBox**(void * iDummy);

        ...
virtual void **BuildGraph**(#) ;
CATBoolean  **CheckChoice**(void * iChoice);
CATBoolean  **CreateBox**(void * iDummy);
        void **BoxCreationChoiceChange** (CATCommand        * iPublisher,
    		          CATNotification      * iNotification,
    		          CATCommandClientData   iUsefulData);

```vbscript
      private :

```

       ...
CATNotification      * iNotification,
CATCommandClientData   iUsefulData);
private :
        int                            _CurrentBoxCreationTypeChoice ;

        CATAfrCheckHeaderAccessor    * _pTwoPointsCmdHdr ;
        CATAfrCheckHeaderAccessor    * _pThreePointsCmdHdr ;
        CATAfrCheckHeaderAccessor    * _pFourPointsCmdHdr ;
        CATAfrCheckHeaderAccessor    * _pOriginCheckHdr ;

    };

---

CATAfrCheckHeaderAccessor    * _pOriginCheckHdr ;
This class deriving from the _CATStateCommand_ class contains:

the following macros:

     * `CmdDeclareResource`: This macro defines the resource file for the state command [3]
     * `CATDeclareClass`: As any class that makes up a component, its includes this macro.

the following (fully or partially explained) methods:

     * `GetPaletteStateOptions `and `GetPaletteOptions`: methods of the _CATIAfrCmdPaletteOptions_ interface
     * `BuildGraph`: it is the method which implements the state chart [4]
     * `CheckChoice`: it is the condition method to enable the sorting between the three possibilities to create a box. Refer to the Using Option - Define the way to create a box section
     * `CreateBox`: the action method which creates a box in the model. See the Using Option- Locate the newly box section.
     * `BoxCreationChoiceChange`: callback method enabling the command to update the icons when one among the three has been selected- See the Managing Exclusivity Between the Three Icons section

and the following data:

     * `_CurrentBoxCreationTypeChoice`: it is a value which keeps the index of the current activated check button. The value ranges from 1 to 3. (1= ![](images/CAACreateBoxSwitchAgentCube.jpg), 2=![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg),3=![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)).
     * `_pTwoPointsCmdHdr`, `_pThreePointsCmdHdr`, and `_pFourPointsCmdHdr`: three pointers to access to the headers representing options to define the way to define the box.
     * `_pOriginCheckHdr`:  the pointer to access to the check header representing the option to define the origin of the box.

The class contains other methods and data, refer to the code for more details.

  2. Defining the CAADegCreateBoxCmd.cpp

The beginning of the source file is such as:

    ...
    #include <CATCommandHeader.h>
    **MacDeclareHeader**(CAADegCreateBoxPaletteHeader) ;

    **CATImplementClass**(CAADegCreateBoxCmd, Implementation,CATStateCommand, CATNull);

    ...
    #include "CATCreateExternalObject.h"
    **CATCreateClass**(CAADegCreateBoxCmd);

    ...

---
     * The `MacDeclareHeader` macro creates the _CAADegCreateBoxPaletteHeader_ class. It is a _CATCommandHeader_ class explained in the Defining Options section.
     * The `CATImplementClass` macro declares that the _CAADegCreateBoxCmd_ class is a component main class thanks the `Implementation` keyword, and OM-derives [5] from _CATStateCommand_.
     * The `CATCreateClass` macro enables the _CATCommandHeader_ class to create an instance of the command by its name.

[Top]
#### Defining Options

Options are command header instances set in the Palette toolbar. In the constructor of the _CAADegCreateBoxCmd_  class the command headers are defined. Refer to the technical article entitled "The Command Headers"  [6] for details and warnings about command header creation.

This state command creates and uses two kinds of options

  * Option to define the way to create the box

This state command creates and uses two kinds of options
This option uses three command headers instances: `CAADegTwoPointsBoxHdr, CAADegThreePointsBoxHdr, and CAADegFourPointsBoxHdr`. Only the creation of the first one is described, since the two others are built on the same model.

In the Managing the exclusivity between the three icons section, you will find explanations how a radio button has been simulated with these three headers.

  * Option to locate the newly box

In the Managing the exclusivity between the three icons section, you will find explanations how a radio button has been simulated with these three headers.
This option uses only one check header instance: `CAADegOriginBoxHdr`

In these two cases, the command header is a check header  A check header being a non-exposed class, the _CATAfrCheckHeaderAccessor_ class encapsulates its creation and its access. The _CATAfrCheckHeaderAccessor_ class constructor creates a check header instance only if the instance does not already exist in the command header list associated with the current editor [6]. Consequently you can create as many _CATAfrCheckHeaderAccessor_ class instances as you want, the methods of this class are redirected on the unique check header instance of the current editor.

Note, that there is also the CAAAfrViewerFeedbackHdr use case [7] which describes the usage of the _CATAfrCheckHeaderAccessor_ class __ in an add-in context.

**Option to definethe way to create the box**

    ...
      CATCommandHeader * pCmd = NULL ;
      ::**CATAfrGetCommandHeader**("CAADegTwoPointsBoxHdr",pCmd);

CATCommandHeader * pCmd = NULL ;
```cpp
      _pTwoPointsCmdHdr = new **CATAfrCheckHeaderAccessor**("CAADegTwoPointsBoxHdr");

      if ( NULL == pCmd )

```

      {
_pTwoPointsCmdHdr = new **CATAfrCheckHeaderAccessor**("CAADegTwoPointsBoxHdr");
```vbscript
if ( NULL == pCmd )
```

         new **CAADegCreateBoxPaletteHeader**

                              ("**CAADegTwoPointsBoxCheckHdr** ",
                              "CAADegGeoCommands",
                              "CAADegBoxPaletteChoiceCmd", (void *) 1);

         new **CAADegCreateBoxPaletteHeader**
                              ("**CAADegTwoPointsBoxUncheckHdr** ",
                              "CAADegGeoCommands",
                              "CAADegBoxPaletteChoiceCmd", (void *) 1);

new **CAADegCreateBoxPaletteHeader**
         _pTwoPointsCmdHdr->**SetCheckCommand**("CAADegTwoPointsBoxCheckHdr");
         _pTwoPointsCmdHdr->**SetUncheckCommand**("CAADegTwoPointsBoxUncheckHdr");

         _pTwoPointsCmdHdr->**SetResourceFile**("CAADegCreateBoxPaletteHeader");

         _pTwoPointsCmdHdr->**SetCheck**(TRUE,FALSE);

      }
    ...

---

`_pTwoPointsCmdHdr` is a newly _CATAfrCheckHeaderAccessor_ class pointer. This pointer will be used in the state command to manage the exclusivity between the three icons. Refer to the Managing the exclusivity between the three icons sections.

But, before to create a _CATAfrCheckHeaderAccessor_ class instance, the _CATAfrGetCommandHeader_**** global function is used to retrieve a check header pointer. If the check header has never been created for the current editor, this method will return NULL. In this case, after the _CATAfrCheckHeaderAccessor_ class construction you should:

  * Create a command header instance for the check and uncheck states.

The _CAADegCreateBoxPaletteHeader_ class is a class automatically created by the `MacDeclareHeader` macro. Refer to the Defining the CAADegCreateBoxCmd.cpp section. The two instances, `CAADegTwoPointsBoxCheckHdr` and `CAADegTwoPointsBoxUncheckHdr`, will launch the _CAADegBoxPaletteChoiceCmd_ command located in the `CAADegGeoCommands` dll. The last argument, `1`, is the argument of the _CAADegBoxPaletteChoiceCmd_ command. This value is different for the two others check header. See the Managing the exclusivity between the three icons section.

`CAADegTwoPointsBoxCheckHdr` and `CAADegTwoPointsBoxUncheckHdr` are command header instances without representation since they are not displayed in menu bar, toolbar or contextual menu. Therefore there is no icon, no help, short help for these two instances [8].

  * Associate the `CAADegTwoPointsBoxCheckHdr` header with the check state thanks to the `SetCheckCommand` method

When the check header will be checked the `CAADegTwoPointsBoxCheckHdr` command header instance will be started.

  * Associate the `CAADegTwoPointsBoxUncheckHdr` header with the uncheck state thanks to the `SetUncheckCommand` method

When the check header will be unchecked the `CAADegTwoPointsBoxUncheckHdr` command header instance will be started.

  * Associate a resource file with the `CAADegTwoPointsBoxHdr` header.

In the CNext/resources/msgcatalog directory of the CAADialogEngine.edu framework you find the  `CAADegCreateBoxPaletteHeader.CATNls `and the `CAADegCreateBoxPaletteHeader.CATRsc` files. The first one contains the help, shorthelp,... and the second one contains the icon name [8].

  * Initialize the state of the `CAADegTwoPointsBoxHdr` check header with the `SetCheck` method

In the CNext/resources/msgcatalog directory of the CAADialogEngine.edu framework you find the  `CAADegCreateBoxPaletteHeader.CATNls `and the `CAADegCreateBoxPaletteHeader.CATRsc` files. The first one contains the help, shorthelp,... and the second one contains the icon name [8].
The first argument, `TRUE`, specify that the `CAADegTwoPointsBoxHdr` check header is with the check state. The second argument, `FALSE`, specify that no notification is sent to refresh the visualization. For the two others check header, the first argument is `FALSE`.

You can note that this initialization is done only for the first creation. When the command is re-launched, the check header already exists and it has kept the previous state.

**Option to locate the newly box**

    ...
      pCmd = NULL ;
      ::**CATAfrGetCommandHeader**("CAADegOriginBoxHdr",pCmd);

pCmd = NULL ;
```cpp
      _pOriginCheckHdr = new **CATAfrCheckHeaderAccessor**("CAADegOriginBoxHdr");

      if ( NULL == pCmd)

```

      {
_pOriginCheckHdr = new **CATAfrCheckHeaderAccessor**("CAADegOriginBoxHdr");
```vbscript
if ( NULL == pCmd)
```

          _pOriginCheckHdr->**SetResourceFile**("CAADegCreateBoxCmd");

      }
    ...

---

`_pOriginCheckHdr` is a newly _CATAfrCheckHeaderAccessor_ class pointer. This pointer will be used in the `CreateBox` method Refer to the Using Options section.

But, before to create a _CATAfrCheckHeaderAccessor_ class instance, the _CATAfrGetCommandHeader_**** global function is used to retrieve a check header pointer. If the check header has never been created for the current editor, this method will return NULL. In this case, after the _CATAfrCheckHeaderAccessor_ class construction you should only specify the resource file name. In the CNext/resources/msgcatalog directory of the CAADialogEngine.edu framework you find the `CAADegCreateBoxCmd.CATNls `and the `CAADegCreateBoxCmd.CATRsc` files. The first one contains the help, shorthelp,... and the second one contains the icon name [8].

This check header does not launch any command when the button is pushed. It is just a header which keeps a state.

**Managing Exclusivity Between the Three Icons**

When an icon (![](images/CAACreateBoxSwitchAgentCube.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg) ,![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)) is pushed, the _CAADegBoxPaletteChoiceCmd_ command is launched. This command sends a notification to inform the _CAADegCreateBoxCmd_ state command.

    ...
When an icon (![](images/CAACreateBoxSwitchAgentCube.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg) ,![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)) is pushed, the _CAADegBoxPaletteChoiceCmd_ command is launched. This command sends a notification to inform the _CAADegCreateBoxCmd_ state command.
    CAADegBoxPaletteChoiceCmd::CAADegBoxPaletteChoiceCmd(void *iArgument):
                       CATCommand(**NULL** ,"CAADegBoxPaletteChoiceCmd")

    {
CAADegBoxPaletteChoiceCmd::CAADegBoxPaletteChoiceCmd(void *iArgument):
CATCommand(**NULL** ,"CAADegBoxPaletteChoiceCmd")
       int value = ( int) iArgument ;

       CAADegBoxCreationChoiceNotification * pNotification = NULL ;
       pNotification = new **CAADegBoxCreationChoiceNotification**(#);
       pNotification->**SetChoice**(value);

       **SendNotification**(GetFather(#),pNotification);

pNotification = new **CAADegBoxCreationChoiceNotification**(#);
pNotification->**SetChoice**(value);
       pNotification = NULL ;

       **RequestDelayedDestruction**(#);
    }
    ...

---

  * `iArgument` is the argument of the _CATCommandHeader_ constructor. The notification keeps this value for the _CAADegCreateBoxCmd_ command. Refer to the Option to define the way to create the box section.
  * The notification is sent to the parent of the _CAADegBoxPaletteChoiceCmd_ command. This parent is NULL, in other words the current command selector [10]. The current command (_CAADegCreateBoxCmd_ ), which has the same parent, will receive this notification.
  * You can note that `pNotification` is not deleted after the sending. This notification has been created with the `CATNotificationDeleteOn` option. It means that the notification will be automatically deleted at the end of the next transaction, that is, as soon as the dialog between sending and receiving commands is completed.
  * The last method is `RequestDelayedDestruction`. The three mandatory rules to respect for such call in a command's constructor are :
    * The class will be never derived ,**AND**
    * Any method will be called after the class construction (avoid public methods to ensure this point), **AND  **
    * The `RequestDelayedDestruction` is the last instruction.

In the `BuildGraph` method of the _CAADegCreateBoxCmd_ command, a callback method has been declared to be inform when a `CAADegBoxCreationChoiceNotification` class notification is sent.

    ...
In the `BuildGraph` method of the _CAADegCreateBoxCmd_ command, a callback method has been declared to be inform when a `CAADegBoxCreationChoiceNotification` class notification is sent.
    AddAnalyseNotificationCB(NULL, "CAADegBoxCreationChoiceNotification",
                    (CATCommandMethod)&CAADegCreateBoxCmd::**BoxCreationChoiceChange** ,
                                NULL);

    ...

---

  * `NULL`:
  * `CAADegBoxCreationChoiceNotification`: The notification class name
  * `BoxCreationChoiceChange`: the callback method
  * `NULL`: no argument for the callback method

The `BoxCreationChoiceChange` method unchecks the two other check buttons.

    ...
The `BoxCreationChoiceChange` method unchecks the two other check buttons.
    void CAADegCreateBoxCmd::BoxCreationChoiceChange (CATCommand  * iPublisher ,
                                        CATNotification      * iNotification,
                                        CATCommandClientData   iUsefulData)

    {
     ...
void CAADegCreateBoxCmd::BoxCreationChoiceChange (CATCommand  * iPublisher ,
CATNotification      * iNotification,
CATCommandClientData   iUsefulData)
              CAADegBoxCreationChoiceNotification * pNotif = NULL ;
```vbscript
              pNotif = ( CAADegBoxCreationChoiceNotification *) iNotification ;

```

              int value = 0 ;
              HRESULT rc = pNotif->**GetChoice**(value);

              ...
              {
int value = 0 ;
HRESULT rc = pNotif->**GetChoice**(value);
```vbscript
                 if ( **value == 1** )

```

                 {
HRESULT rc = pNotif->**GetChoice**(value);
if ( **value == 1** )
                     _pThreePointsCmdHdr->SetCheck(**FALSE** ,FALSE);
                     _pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);

                 }
```vbscript
if ( **value == 1** )
_pThreePointsCmdHdr->SetCheck(**FALSE** ,FALSE);
_pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
                 if ( value == 2 )
```

                 {
_pThreePointsCmdHdr->SetCheck(**FALSE** ,FALSE);
_pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
if ( value == 2 )
                     _pTwoPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
                     _pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);

                 }
```vbscript
if ( value == 2 )
_pTwoPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
_pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
                 if ( value == 3 )
```

                 {
_pTwoPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
_pFourPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
if ( value == 3 )
                     _pTwoPointsCmdHdr->SetCheck(**FALSE** ,FALSE);
                     _pThreePointsCmdHdr->SetCheck(**FALSE** ,FALSE);

                 }
                 **_CurrentBoxCreationTypeChoice** = value ;
    ...

---

`GetChoice` retrieves the last activated check button.  `_CurrentBoxCreationTypeChoice,` a data member, keeps the current activated check button. See its usage in the Using Options- Define the way to create a box section.

[Top]
#### Implementing the CATIAfrCmdPaletteOptions Interface

The _CAADegCreateBoxCmd_ class states that it implements the _CATIAfrCmdPaletteOptions_ interface thanks to the `TIE_CATIAfrCmdPaletteOptions` macro.

    ...
    #include "TIE_CATIAfrCmdPaletteOptions.h"
    **TIE_CATIAfrCmdPaletteOptions**(CAADegCreateBoxCmd);
    ...

---

This interface has two methods:

  1. GetPaletteOptions
  2. GetPaletteStateOptions

  1. GetPaletteOptions

This method is called when the command is activated. It is the reason why the command must be an exclusive or shared command [9].

In the use case, the option to add in the Palette is the command header represented by this icon: ![](images/CAACreateBoxSwitchOrigin.jpg).

    ...
This method is called when the command is activated. It is the reason why the command must be an exclusive or shared command [9].
In the use case, the option to add in the Palette is the command header represented by this icon: ![](images/CAACreateBoxSwitchOrigin.jpg).
    CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteOptions(#)

    {
In the use case, the option to add in the Palette is the command header represented by this icon: ![](images/CAACreateBoxSwitchOrigin.jpg).
CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteOptions(#)
```cpp
       CATLISTP(CATCommandHeader) PaletteOptions;

```

       CATCommandHeader * pCmd = NULL ;

       ::**CATAfrGetCommandHeader**("CAADegOriginBoxHdr",pCmd);

```cpp
CATLISTP(CATCommandHeader) PaletteOptions;
CATCommandHeader * pCmd = NULL ;
       if ( NULL != pCmd )
```

       {
CATCommandHeader * pCmd = NULL ;
if ( NULL != pCmd )
           PaletteOptions.**Append**(pCmd);
           pCmd = NULL ;

       }
```vbscript
if ( NULL != pCmd )
PaletteOptions.**Append**(pCmd);
pCmd = NULL ;
       return PaletteOptions ;
```

    }
    ...

---

`PaletteOptions` is a list of command header instance pointers to return. The _CATAfrGetCommandHeader_ global function is the means to retrieve a command header instance pointer from its name. The name being the first argument of the function. This header is kept in the list associated with the current editor [6].

The `CAADegOriginBoxHdr` command header instance is a check header to specify if the newly box should be created at the origin of the model . Refer to the Defining Options section for details about the header creation.

  2. GetPaletteStateOptions

This method is called each time the state command enters in a state. In most cases, the goal of this method is to retrieve the name of the current state, and whether the state's name, add the specific command header instance pointers in the returned list.

    ...
2. GetPaletteStateOptions
This method is called each time the state command enters in a state. In most cases, the goal of this method is to retrieve the name of the current state, and whether the state's name, add the specific command header instance pointers in the returned list.
    CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteStateOptions(#)

    {
This method is called each time the state command enters in a state. In most cases, the goal of this method is to retrieve the name of the current state, and whether the state's name, add the specific command header instance pointers in the returned list.
CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteStateOptions(#)
```cpp
       CATLISTP(CATCommandHeader) PaletteStateOptions;

```

       CATDialogState * pCurrentState = **GetCurrentState**(#);
```vbscript
       if ( NULL != pCurrentState )

```

       {
```cpp
CATLISTP(CATCommandHeader) PaletteStateOptions;
CATDialogState * pCurrentState = **GetCurrentState**(#);
if ( NULL != pCurrentState )
          CATString StateName = pCurrentState->**GetResourceID**(#);

          if ( ! strcmp("**stWidthPointId** ",StateName) )
```

          {
CATString StateName = pCurrentState->**GetResourceID**(#);
```vbscript
if ( ! strcmp("**stWidthPointId** ",StateName) )
             Case stWidthPointId State

```

          }else if (  ! strcmp("**stDepthPointId** " ,StateName) )
          {
```vbscript
```vbscript
if ( ! strcmp("**stWidthPointId** ",StateName) )
Case stWidthPointId State
             Case stDepthPointId**** State - not detailed
```

```

          }
       }
       return PaletteStateOptions ;
    ...

---

return PaletteStateOptions ;
The `GetCurrentState` method retrieves a pointer to the current state. The `GetResourceID` method retrieves the resource identifier of the state. It is the unique argument of the `AddDialogState` or `GetInitialState` methods.

In the `BuildGraph` method, four states are created:

    ...
The `GetCurrentState` method retrieves a pointer to the current state. The `GetResourceID` method retrieves the resource identifier of the state. It is the unique argument of the `AddDialogState` or `GetInitialState` methods.
In the `BuildGraph` method, four states are created:
    CATDialogState *stCornerPoint = **GetInitialState**("stCornerPointId");

    CATDialogState *stWidthPoint = **AddDialogState**("**stWidthPointId** ");

    CATDialogState *stDepthPoint = AddDialogState("**stDepthPointId** ");

    CATDialogState *stHeightPoint = AddDialogState("stHeightPointId");

    ...

---

`stCornerPoint` is the state to select P1, `stWidthPoint` is the state to select P2, `stDepthPoint` is the state to indicate P3 and `stHeightPoint` is the state to indicate P4. Refer to Fig.1 for explanations about these four points and Fig.3 for the UML state chart. For the `stWidthPoint` state, the three icons (![](images/CAACreateBoxSwitchAgentCube.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg))  are added in the Palette, and for the `stDepthPoint` state only the two lasts (![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg),![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg)) are set.

Here is the code to process the state whose the identifier is `stWidthPoint`Id:

    ...
Here is the code to process the state whose the identifier is `stWidthPoint`Id:
              CATCommandHeader * pCmd = NULL ;

              ::**CATAfrGetCommandHeader**("**CAADegTwoPointsBoxHdr** ",pCmd);
Here is the code to process the state whose the identifier is `stWidthPoint`Id:
CATCommandHeader * pCmd = NULL ;
```vbscript
              if ( NULL != pCmd )

```

              {
CATCommandHeader * pCmd = NULL ;
if ( NULL != pCmd )
                 PaletteStateOptions.**Append**(pCmd);
                 pCmd = NULL ;

              }

              ::**CATAfrGetCommandHeader**("**CAADegThreePointsBoxHdr** ",pCmd);
PaletteStateOptions.**Append**(pCmd);
pCmd = NULL ;
```vbscript
              if ( NULL != pCmd )

```

              {
```vbscript
if ( NULL != pCmd )
                 PaletteStateOptions.Append(pCmd);
                 pCmd = NULL ;
```

              }

              ::**CATAfrGetCommandHeader**("**CAADegFourPointsBoxHdr** ",pCmd);
PaletteStateOptions.Append(pCmd);
pCmd = NULL ;
```vbscript
              if ( NULL != pCmd )

```

              {
```vbscript
if ( NULL != pCmd )
                 PaletteStateOptions.Append(pCmd);
                 pCmd = NULL ;
```

              }
    ...

---

`PaletteStateOptions`, defined just above,  is a list of command header instance pointers. The _CATAfrGetCommandHeader_ global function is the means to retrieve a command header instance pointer from its name. The name being the first argument of the function. This header is kept in the list associated with the current editor [8].

In this state, all the possibilities to create the box are valid. The `CAADegTwoPointsBoxHdr`, `CAADegThreePointsBoxHdr`, and` CAADegFourPointsBoxHdr` command header instances are check headers to specify if the newly box should be created with two, three or four points respectively. Refer to the Defining Options section for details about the header creations.

[Top]
#### Using Options

The state command has defined two options:

  * To locate the newly box,
  * To define the way to create a box.

These two options are used in different parts of the command.

  * **Locate the newly box **

The `CreateBox` method is the action method when the final state is reached. It creates a new `CAASysCuboid` [1] element in the current CAAGeometry document. Just after the box creation, not detailed here, it is necessary to specify the origin of this box.

    ...
The `CreateBox` method is the action method when the final state is reached. It creates a new `CAASysCuboid` [1] element in the current CAAGeometry document. Just after the box creation, not detailed here, it is necessary to specify the origin of this box.
          CATMathPoint CornerPoint ;
          CATMathPoint BoxOrigin ;

          **FindBoxCornerPoint**(CornerPoint);

CATMathPoint CornerPoint ;
CATMathPoint BoxOrigin ;
```vbscript
          if ( NULL == _pOriginCheckHdr )

```

          {
              BoxOrigin = CornerPoint ;
          } else if (  FALSE == _pOriginCheckHdr->**IsChecked**(#) )
          {
```vbscript
if ( NULL == _pOriginCheckHdr )
BoxOrigin = CornerPoint ;
```

          }
    ...

---

The `FindBoxCornerPoint` method is a local method which retrieves the coordinates of the first selected point (P1) Fig.1

`_pOriginCheckHdr` is a _CATAfrCheckHeaderAccessor_ class pointer on the "CAADegOriginBoxHdr" check header. See the Defining Options section. If the check header is checked (highlighted) the box is located at the first selected point location, otherwise in (0,0,0) the default _CATMathPoint_ value.

  * **Define the way to create a box  **

This option is used in the `CheckChoice` condition method. The asterisked transitions on the state chart - Fig 3 /- use this method to accept of not the transition.

Here are the transition using the `CheckChoice` condition method:

    ...
This option is used in the `CheckChoice` condition method. The asterisked transitions on the state chart - Fig 3 /- use this method to accept of not the transition.
Here are the transition using the `CheckChoice` condition method:
    CATDialogTransition * **pState2Transition1** = AddTransition

      (
Here are the transition using the `CheckChoice` condition method:
CATDialogTransition * **pState2Transition1** = AddTransition
         stWidthPoint,
         stDepthPoint,
         AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
```cpp
    	              Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**4**)),
         Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionWidth)

```

      ) ;

```vbscript
AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
```cpp
Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**4**)),
Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionWidth)
```

    CATDialogTransition * **pState2Transition3** = AddTransition
```

      (
```cpp
Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionWidth)
CATDialogTransition * **pState2Transition3** = AddTransition
         stWidthPoint,
         NULL,
         AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
```cpp
    	              Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**1**)),
         Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
```

```

      ) ;
NULL,
AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
```cpp
Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**1**)),
Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
```

    CATDialogTransition * **pState3Transition1** = AddTransition

      (
```cpp
Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**1**)),
```cpp
Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
```

CATDialogTransition * **pState3Transition1** = AddTransition
         stDepthPoint,
         stHeightPoint,
         AndCondition(IsOutputSetCondition(_daIndicationDepthPoint),
```cpp
    	              Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**3**)),
         Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionDepth)
```

```

      ) ;
stHeightPoint,
AndCondition(IsOutputSetCondition(_daIndicationDepthPoint),
```cpp
Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**3**)),
Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionDepth)
```

    CATDialogTransition * **pState3Transition3** = AddTransition

      (
```cpp
Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**3**)),
```cpp
Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionDepth)
```

CATDialogTransition * **pState3Transition3** = AddTransition
         stDepthPoint,
         NULL,
         AndCondition(IsOutputSetCondition(_daIndicationDepthPoint),
```cpp
    	              Condition((ConditionMethod) & CAADegCreateBoxCmd::**CheckChoice** ,(void*)**2**)),
         Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
```

```

      ) ;
    ...

---
    * `pState2Transition1` is triggered if P2 is selected- Refer Fig.1 /- and either ![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg)or ![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg) is highlighted
    * `pState2Transition3` is triggered if P2 is selected- Refer Fig.1 /- and ![](images/CAACreateBoxSwitchAgentCube.jpg) is highlighted.
    * `pState3Transition1` is triggered if P3 is indicated- Refer Fig.1 /- and ![](images/CAACreateBoxSwitchAgentCuboidWidthDepthHeight.jpg) is highlighted
    * `pState3Transition3` is triggered if  P3 is indicated- Refer Fig.1 /- and ![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg) is highlighted

The `CheckChoice` method takes into the current state account, it is the last argument of the `AddTransition` method, and the current activated check button.

    ...
The `CheckChoice` method takes into the current state account, it is the last argument of the `AddTransition` method, and the current activated check button.
    CATBoolean CAADegCreateBoxCmd::**CheckChoice**(void *iChoice)

    {
The `CheckChoice` method takes into the current state account, it is the last argument of the `AddTransition` method, and the current activated check button.
CATBoolean CAADegCreateBoxCmd::**CheckChoice**(void *iChoice)
        CATBoolean Test = FALSE ;
        int Choice = (int) iChoice ;

```vbscript
        if ( ( 4 == Choice  ) && ( _CurrentBoxCreationTypeChoice > 1 ) )

```

        {   Test = TRUE;
        }else if ( _CurrentBoxCreationTypeChoice == Choice )
        {
```vbscript
if ( ( 4 == Choice  ) && ( _CurrentBoxCreationTypeChoice > 1 ) )
           Test = TRUE;
```

        }
        return Test ;
    }
    ...

---

`_CurrentBoxCreationTypeChoice` is a data member which keeps the current activated check button. It is initialized in the constructor, and refreshed in the `BoxCreationChoiceChange` method.

The `CheckChoice` method returns `TRUE` when the condition is filled otherwise `FALSE`.

[Top]

* * *
### In Short

This use case has explained how to implement the _CATIAfrCmdPaletteOptions_ interface to add options in the Tools Palette toolbar.

[Top]

* * *
### References

[1] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)
---|---
[2] | [Describing State Dialog Commands Using UML](../CAADegTechArticles/CAADegUMLDescription.md)
[3] | [Assigning Resources to a State Dialog Command](../CAADegTechArticles/CAADegResources.md)
[4] | [Implementing the Command Statechart Diagram](../CAADegTechArticles/CAADegGraph.md)
[5] | [Object Modeler Inheritances](../CAASysTechArticles/CAASysOMInheritance.md)
[6] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)
[7] | [Creating a Check Button](CAAAfrCheckHeader.md)
[8] | [Creating Resources for Command Headers](../CAAAfrTechArticles/CAAAfrI18NHeader.md)
[9] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[10] | [Using the "Tools Palette" Toolbar for a Workbench](CAAAfrSamplePaletteWkb.md)
[Top]

* * *
### History

Version: **1** [Aug 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
