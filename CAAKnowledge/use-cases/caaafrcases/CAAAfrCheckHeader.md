---
title: "Creating a Check Button"
category: "use-case case"
module: "CAAAfrUseCases"
tags: "["CAACafViewerFeedbackCmd", "CAACafViewerFeedback", "CAAAfrGeneralWksAddinHeader", "CAAAfrViewerFeedbackHdr", "CAAViewerFeedback", "CATIWorkbenchAddin", "CAACafViewerFeedbackManager", "CATIAfrGeneralWksAddin", "CAACafViewerFeedbackCheckHdr", "CAACafViewerFeedbackUncheckHdr", "CAACafViewerFeedbackCmdId", "CAACafCATIAApplicationFrm", "CAAAfrGeneralWksAddin", "CAAAfrGeneralWksAdn", "CATIAApplicationFrm", "CAACATIAApplicationFrm", "CAAApplicationFrame"]"
source_file: "Doc/online/CAAAfrUseCases/CAAAfrCheckHeader.htm"
converted: "2026-05-11T17:17:55.585103"
---
# 3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Creating a Check Button

_Using CATAfrCheckHeaderAccessor_
---|---|---
Use Case

* * *
### Abstract

This article shows how to integrate in a workbench a check button in order to launch a command when the button is "checked" and another one when the state of the button becomes "unchecked".

  * **What You Will Learn With This Use Case**
  * **The CAAAfrViewerFeedbackHdr Use Case**
    * What Does CAAAfrViewerFeedbackHdr Do
    * How to Launch CAAAfrViewerFeedbackHdr
    * Where to Find the CAAAfrViewerFeedbackHdr Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how integrate in a workbench a button which launches a command when the button is checked and another one when the button is unchecked. It is possible thanks to a command header [1] whose the representation is a check button. This specialized command header is a check header. This picture below explains the internal process:

  * When the button is "checked", a command header A is started which itself launches a command 1
  * When the button is "unchecked", a command header B is started which itself launches a command 2

This article explains how to:

  * Use the _CATAfrCheckHeaderAccessor_   class, the class which encapsulates the non exposed check header class,
  * Create the command headers for the "check" and "uncheck" states,
  * Create the command which contains the "check" and "uncheck" behaviors.

A check header can be also used without starting command headers. In this case, only the "checked" or "unchecked" state is interesting. This kind of usage is described in another use case [2] .

[Top]
### The CAAAfrViewerFeedbackHdr Use Case

CAAAfrViewerFeedbackHdr is a use case of the CAAApplicationFrame.edu framework that illustrates Application framework capabilities.

[Top]
#### What Does CAAAfrViewerFeedbackHdr Do

The CAAAfrViewerFeedbackHdr use case inserts in the General workshop [3] a check header whose the title is "Viewer Feedback demonstrator". The left picture shows the check header with the state "off", and the right picture with the state "On". In the two cases you have the representation of the header in the menu bar and the tool bar.

When the state is "checked", if there is a current viewer, some information, such as the mouse position, is displayed in the 2D viewpoint as the image shows it below. Refer to the "Viewer Feedback" use case for details about this rendering [4].

![](images/CAAAfrCheckHeaderMouseCoord.jpg)
---

[Top]
#### How to Launch CAAAfrViewerFeedbackHdr

To launch CAAAfrViewerFeedbackHdr, you will need to set up the build time environment, then compile CAAAfrViewerFeedbackHdr along with its prerequisites, set up the run time environment, and then execute the use case [5].

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`

But just before launching the execution, edit the CAAApplicationFrame.edu.dico interface dictionary file located in the dictionary directory of the CAAApplicationFrame.edu framework:
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`
UNIX | `InstallRootDirectory/CAAApplicationFrame.edu/CNext/code/dictionary/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

In this file, remove the "**#** " character before the two following lines:

    ...
    #CAAAfrGeneralWksAddin       CATIWorkbenchAddin          libCAAAfrGeneralWksAddin
    #CAAAfrGeneralWksAddin       CATIAfrGeneralWksAddin      libCAAAfrGeneralWksAddin
    ...

---

[Top]
#### Where to Find the CAAAfrViewerFeedbackHdr Code

The CAAAfrViewerFeedbackHdr use case is made of several classes located :

  * In the CAAAfrGeneralWksAddin.m module of the CAAApplicationFrame.edu framework

The CAAAfrViewerFeedbackHdr use case is made of several classes located :
Windows | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m/`

Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m/`

There is a single class, the _CAAAfrGeneralWksAdn_ class, which is an implementation of the _CATIAfrGeneralWksAddin_ interface [3]. If the "Making Your Document Independent Command Available in All Workbenches" use case explains the implementation of this interface, this article only details the check header instance creation and its integration in menu bar and tool bar.

  * In the CAACafViewerFeedback.m module of the CAACATIAApplicationFrm.edu framework

There is a single class, the _CAAAfrGeneralWksAdn_ class, which is an implementation of the _CATIAfrGeneralWksAddin_ interface [3]. If the "Making Your Document Independent Command Available in All Workbenches" use case explains the implementation of this interface, this article only details the check header instance creation and its integration in menu bar and tool bar.
Windows | `InstallRootDirectory/CAACafCATIAApplicationFrm.edu/CAACafViewerFeedback.m/`

Unix | `InstallRootDirectory/CAACafCATIAApplicationFrm.edu/CAACafViewerFeedback.m/`

There are the _CAACafViewerFeedbackCmd_ and the _CAACafViewerFeedbackManager_ classes. The first is a command which is described in this article. The second is an object to manage the viewer feedback which is only detailed in the Visualization use case [4].

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are four logical steps in the CAAAfrViewerFeedbackHdr use case:

  1. Creating the Check Header Instance in Add-in
  2. Creating the Check/Uncheck Command
  3. Retrieving the State of a Check Header
  4. Creating the Check Header Resources

[Top]
#### Creating the Check Header Instance in Add-in

The  _CAAAfrGeneralWksAdn_ class is an implementation of the _CATIAfrGeneralWksAddin_ interface which is an Add-in of the General workshop [3]. Like other Add-in implementations, there are two methods to consider:

  * `CreateCommands`, the method to create the command header instances,

  * `CreateToolbars`, the method to arrange the command header instances in menu bar and tool bar. Since this piece code is not in relationship with the topic of this article, refer to the CAAAfrGeneralWksAddin use case [3] for details.

Extract of the `CreateCommands` method

    ...
    void CAAAfrGeneralWksAdn::CreateCommands(#)
    {
      ...
void CAAAfrGeneralWksAdn::CreateCommands(#)
      CATAfrCheckHeaderAccessor **ViewerFeedbackHdrAccessor** ("CAAAfrViewerFeedbackHdr");
      ViewerFeedbackHdrAccessor.**SetResourceFile**("CAAAfrGeneralWksAddinHeader");

      ...
    }

---

The _CATAfrCheckHeaderAccessor_ class enables you to create an instance of a non-exposed check header class.  "`CAAAfrViewerFeedbackHdr`" will be the check header internal name. The `SetResourceFile` method allows you to specify in which filename, the Nls and Rsc resources will be set. See the Creating the Check Header Resources section.

Then, the behavior for the "check" and "uncheck" states are specified.

    ...

      CATCommandHeader * pHdr = (CATCommandHeader*) new
                             CAAAfrGeneralWksAddinHeader("**CAACafViewerFeedbackCheckHdr** ",
                                 "CAACafViewerFeedback",
                                 "CAACafViewerFeedbackCmd", (void *)1);
CATCommandHeader * pHdr = (CATCommandHeader*) new
CAAAfrGeneralWksAddinHeader("**CAACafViewerFeedbackCheckHdr** ",
      pHdr->**SetVisibility**(0);

      pHdr = (CATCommandHeader*) new
```vbscript
                            CAAAfrGeneralWksAddinHeader("**CAACafViewerFeedbackUncheckHdr** ",

```

                                 "CAACafViewerFeedback",
                                 "CAACafViewerFeedbackCmd", (void *)2);
pHdr = (CATCommandHeader*) new
```vbscript
CAAAfrGeneralWksAddinHeader("**CAACafViewerFeedbackUncheckHdr** ",
```

      pHdr->**SetVisibility**(0);

      ViewerFeedbackHdrAccessor.**SetCheckCommand**("CAACafViewerFeedbackCheckHdr");

      ViewerFeedbackHdrAccessor.**SetUncheckCommand**("CAACafViewerFeedbackUncheckHdr");

---

The _CAAAfrGeneralWksAddinHeader_   class has been automatically created with the `MacDeclareHeader` macro insert in the `CAAAfrGeneralWksAdn.cpp `file [3]. The arguments of the two instances are:

  * `CAACafViewerFeedbackCheckHdr/``CAACafViewerFeedbackUncheckHdr`: the internal name of the two command header instances.
  * `CAACafViewerFeedback`: name of the library exporting the `CAACafViewerFeedbackCmd` command
  * `CAACafViewerFeedbackCmd`: name of the command which set/unset the viewer feedback. This class is explained further, see the Creating the Check/Uncheck Command section.
  * `1/2`: arguments of the `CAACafViewerFeedbackCmd` command

The `SetVisibility` method of the _CATCommandHeader_ class prohibits that the two instances, `CAACafViewerFeedbackCheckHdr and CAACafViewerFeedbackUncheckHdr` appear in the Customize command. The end user which do not known the identifier of command header cannot launch them in the power input, or drag and drop the command in a toolbar. See the technical article for more information about this method [1].

Associating the `CAACafViewerFeedbackCheckHdr `header instance with the "Check" state, thanks to the `SetCheckCommand` method, the _CAACafViewerFeedbackCmd_ with` 1` as argument will be finally launched when the end use will check the check button.

Associating the `CAACafViewerFeedbackUncheckHdr `header instance with the "Uncheck" state, thanks to the `SetUncheckCommand` method, the _CAACafViewerFeedbackCmd_ with `2` as argument will be finally launched when the end use will uncheck the check button.

[Top]
#### Creating the Check/Uncheck Command

The aim of this section is to explain the command which is launched when the end user selects the "Viewer Feedback Demonstrator" check button. This command is a _CAACafViewerFeedbackCmd_ class:

  * _CAACafViewerFeedbackCmd_ header file
  * _CAACafViewerFeedbackCmd_ source file

_CAACafViewerFeedbackCmd_ header file

    #include "CATCommand.h"

_CAACafViewerFeedbackCmd_ header file
    class CAACafViewerFeedbackCmd : public **CATCommand**

    {
class CAACafViewerFeedbackCmd : public **CATCommand**
```vbscript
      public :

```

       CAACafViewerFeedbackCmd(void * iArgument);

       virtual ~CAACafViewerFeedbackCmd(#);

```vbscript
      private :

```

       CAACafViewerFeedbackCmd (#);
```vbscript
       CAACafViewerFeedbackCmd(const CAACafViewerFeedbackCmd &iObjectToCopy);
```

       CAACafViewerFeedbackCmd & operator = (const CAACafViewerFeedbackCmd &iObjectToCopy);

    };

---

The _CAACafViewerFeedbackCmd_ class is a _CATCommand_ class without methods. The default constructor, the copy constructor, and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.

_CAACafViewerFeedbackCmd_ source file

    ...
    #include "CATCreateExternalObject.h"
    **CATCreateClassArg**(CAACafViewerFeedbackCmd,void *);

    CAACafViewerFeedbackCmd::CAACafViewerFeedbackCmd(void *iArgument):
                           **CATCommand**(**NULL** ,"CAACafViewerFeedbackCmdId")
    {
CAACafViewerFeedbackCmd::CAACafViewerFeedbackCmd(void *iArgument):
      CAACafViewerFeedbackManager * pCAACafViewerFeedbackManager = NULL ;
      CAACafViewerFeedbackManager::GetManager(&pCAACafViewerFeedbackManager);
```vbscript
      if ( NULL != pCAACafViewerFeedbackManager )

```

      {
CAACafViewerFeedbackManager * pCAACafViewerFeedbackManager = NULL ;
CAACafViewerFeedbackManager::GetManager(&pCAACafViewerFeedbackManager);
if ( NULL != pCAACafViewerFeedbackManager )
         int state = (int) **iArgument** ;

```vbscript
         if ( 1 == state )

```

         {
int state = (int) **iArgument** ;
if ( 1 == state )
            pCAACafViewerFeedbackManager->SetViewerFeedbackOn(#);

         }else
         {
```vbscript
if ( 1 == state )
pCAACafViewerFeedbackManager->SetViewerFeedbackOn(#);
            pCAACafViewerFeedbackManager->SetViewerFeedbackOff(#);
```

         }
         ...
      }
      **RequestDelayedDestruction**(#);
    }

---

The `CATCreateClassArg`**** macro**** enables any command header (a _CATCommandHeader_ class) to instantiate a _CATCommand_ by its name and with an argument.

The first argument, `NULL`, given to the _CATCommand_ class means that the parent of the command is the current command selector [6]. The second argument ("`CAACafViewerFeedbackCmdId`") is the internal name of the command. This _CATCommand_ is undefined [6] (the default behavior of a _CATCommand)_ because this command should not disturb the current active command.

What it is necessary to retain in this class is the command's life cycle. The _CAACafViewerFeedbackCmd_ is instantiated by a command header but not deleted by this command header, therefore the _CAACafViewerFeedbackCmd_ should manage its deletion. But as the _CATCommand_ is undefined [6], it means that it is not seen by the focus manager and cannot be activated, deactivated or canceled as usual for commands launched from a command header. So a `RequestDelayedDestruction` instruction is done at the end of the constructor. The three mandatory rules to respect for such call in a command's constructor are :

  * The class will be never derived ,**AND**
  * Any method will be called after the class construction (avoid public methods to ensure this point), **AND  **
  * The `RequestDelayedDestruction` is the last instruction.

```vbscript
```vbscript
For details about the  _CAACafViewerFeedbackManager_ refer you to the Visualization use case [4].

```

```

[Top]
#### Retrieving the State of a Check Header

A method of the _CAACafViewerFeedbackManager_ class needs to know the state of the check header.

    ...
A method of the _CAACafViewerFeedbackManager_ class needs to know the state of the check header.
    void CAACafViewerFeedbackManager::WindowActivatedCB( CATCallbackEvent   event,
                                                  void             * client,
                                                  CATNotification  * notification,
                                                  CATSubscriberData  data,
                                                  CATCallback        callback)

    {
void             * client,
CATNotification  * notification,
CATSubscriberData  data,
CATCallback        callback)
        CATAfrCheckHeaderAccessor ViewerFeedbackHdrAcc("CAAAfrViewerFeedbackHdr") ;
        if( 1 == ViewerFeedbackHdrAcc.**IsChecked**(#) )

        {
          ...
        }
    }
    ...

---

The `WindowActivatedCB` is a callback method called when a window of the frame is activated. Before launching an action, you want to know the state of the check header in the window's context, in other words the state of the check header which has been created when the document displaying in the window has been opened. The _CATAfrCheckHeaderAccessor_ class constructor tests that the check header already exists in the list of command for the current editor, before to create it. In all cases, after the  _CATAfrCheckHeaderAccessor_ constructor class, you have an access to the check header contained in the list of command headers dedicated to the current editor. Refer you to the "Life Cycle management" section of the technical article about command headers [1] to understand the relationship between editor (_CATFrmEditor_   class) and command header (_CATCommandHeader_ class).

[Top]
#### Creating the Check Header Resources

The `WindowActivatedCB` is a callback method called when a window of the frame is activated. Before launching an action, you want to know the state of the check header in the window's context, in other words the state of the check header which has been created when the document displaying in the window has been opened. The _CATAfrCheckHeaderAccessor_ class constructor tests that the check header already exists in the list of command for the current editor, before to create it. In all cases, after the  _CATAfrCheckHeaderAccessor_ constructor class, you have an access to the check header contained in the list of command headers dedicated to the current editor. Refer you to the "Life Cycle management" section of the technical article about command headers [1] to understand the relationship between editor (_CATFrmEditor_   class) and command header (_CATCommandHeader_ class).
Previously in the "Creating the Check Header Instance in Add-in" section, just after the check header creation through the _CATAfrCheckHeaderAccessor_ class, the resource file name has been specified thanks to the `SetResourceFile` method. In this use case the prefix of the file name is "CAAAfrGeneralWksAddinHeader". You retrieve the  `CAAAfrGeneralWksAddinHeader.CATNls` and `CAAAfrGeneralWksAddinHeader.CATRsc` files in the CNext/resources/msgcatalog directory of the CAAApplicationFrame.edu framework.

The `CAAAfrGeneralWksAddinHeader.CATNls` file contains:

    ...
    **CAAAfrGeneralWksAddinHeader**.**CAAAfrViewerFeedbackHdr**.Category  = "View" ;
The `CAAAfrGeneralWksAddinHeader.CATNls` file contains:
    CAAAfrGeneralWksAddinHeader.CAAAfrViewerFeedbackHdr.Title     = "Viewer Feeback demonstrator" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrViewerFeedbackHdr.ShortHelp = "Viewer Feeback demonstrator" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrViewerFeedbackHdr.Help      = "Demonstrator of the Viewer CAA API" ;
    CAAAfrGeneralWksAddinHeader.CAAAfrViewerFeedbackHdr.LongHelp  = "Viewer Feeback demonstrator
    This command checks or uncheks the feedback of the cursor in the current viewer." ;

    ...

---

and the `CAAAfrGeneralWksAddinHeader.CATNls` file contains:

    ...
    CAAAfrGeneralWksAddinHeader.CAAAfrViewerFeedbackHdr.Icon.Normal = "I_CAAViewerFeedback" ;
    ...

---

where :

  * `CAAAfrGeneralWksAddinHeader`: is the file name
  * `CAAAfrViewerFeedbackHdr`**:** is the command header identifier.
  * `Category, Title, ShortHelp, Help, `I`con.Normal` `and LongHelp` : keywords for a command header [7]

[Top]

* * *
### In Short

This article explains how to use the _CATAfrCheckHeaderAccessor_ class to create or retrieve a check header.

[Top]

* * *
### References

[1] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.md)
---|---
[2] | [Creating a Command with Options in the "Tools Palette" Toolbar](CAAAfrCmdPalette.md)
[3] | [Making Your Document Independent Command Available in All Workbenches](CAAAfrSampleGeneralWksAddin.md)
[4] | [ Viewer Feedback](../CAAVisUseCases/CAAVisViewerFeedback.md)
[5] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
[6] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[7] | [Creating Resources for Command Headers](../CAAAfrTechArticles/CAAAfrI18NHeader.md)
[Top]

* * *
### History

Version: **1** [Aug 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
