---
```vbscript
title: "Warm Start Incremental Backup"
category: "use-case"
module: "CAAAfrTechArticles"
tags: ["CATIContainer", "CATIdent", "CAAMyCommand", "CATInit"]
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrWarmstart.htm"
converted: "2026-05-11T17:17:55.951704"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface

|
### Warm Start Incremental Backup

_Principles and CAA Integration_
---|---|---
Technical Article

* * *
### Abstract

This article first presents principles and mechanisms for warm start incremental backup. Then it explains what you should do to make sure the workbench or command you create supports warm start.

  * **Incremental Warm Start Principles**
  * **Technical Description**
    * **Backup Data**
    * **Activation, Deactivation, Re-initialization Mechanisms**
    * **Transaction**
  * **CAA Workbench Integration**
  * **CAA Command Integration**
    * **What are Commands to Take Into Account?**
    * **Why and How to Deactivate the Warm Start?**
    * **Why and How to Activate or Re-initialize the Warm Start?**
    * **Why and How to Commit a Transaction?**
    * **Commands Creating Applicative Container**
    * **Commands Using Non V5 Documents**
  * **In Short**
  * **References**

---

* * *
### Incremental Warm Start Principles

Until now, warm start meant simply automatically saving all documents every xx minutes. Auto save operations on large amounts of data can take a long time, even lasting several minutes, and all interactions since the last auto save are lost. The auto save feature can also be deactivated by users who prefer to save their documents frequently and manually to avoid losing data.

To resolve these problems the incremental warm start has been created. Its objectives are:

  * No CPU over cost perceptible for the end user,
  * No loss of interactions.

To resolve these problems the incremental warm start has been created. Its objectives are:
All open documents are copied in a temporary directory, and all modifications since the document was opened are logged in a log file. These operations involve a minimum inconvenience for the end user when opening documents (direct copy without loading), and the logging of document modifications at each interaction is not perceptible.

Regarding the restore behavior:

  * after a crash, all documents are opened from the temporary directory
  * all modifications stored in the log are replayed
  * all necessary editors are opened
  * restoring data could take a long time:
    * all modifications made by users (including test/try, mistakes, etc.) are replayed
    * time is needed to replay necessary updates.

Most of the logged data correspond to operations done in commands. Some of them are not always replayable. When it is the case, the warm start mechanism is deactivated to avoid a bad restoration in case of crash.

A "warm start compliant" workbench means that for any commands defined inside the workbench:

  * either the command is warm start compliant, it means that the command does not execute operations preventing a complete restoration,
  * or the command deactivates the warm start.

The incremental warm start mechanism is available for all Dassault Systemes workbenches of the following document types [1]:

  * Part,
  * Product,
  * Drawing.

This incremental warm start is activated through the Options command.

Fig.1 Activation through Tools/Options ![](images/CAAAfrWarmStartTOEntoure.jpg)
---

[Top]
### Technical Description

The aim of this section is first to give an internal description of the data which allow us to support the incremental warm start, and then to explain how this data is used during a session.
#### Backup Data

The aim of this section is first to give an internal description of the data which allow us to support the incremental warm start, and then to explain how this data is used during a session.
Data to do an incremental backup is stored in the CNext02.roll directory located in the `CATTemp` environment variable which is by default:

Unix | : | $HOME/CATTemp

Data to do an incremental backup is stored in the CNext02.roll directory located in the `CATTemp` environment variable which is by default:
Unix | : | $HOME/CATTemp
Windows | : | DriveName/Documents and Settings\LogonName\Local Settings\Application Data\DassaultSystemes\CATTemp

CNext02.roll contains:

  * **Documents**

> These are copies of all opened documents in session, no matter if those are visible or not. A copy is done either from the original file location ( in file environment) , or from a database (in ENOVIA environment). The name of each copy is an internal name, without relationship with the document original name.

  * A **Autosave.log** file

This file contains all modifications on the documents since they were copied to CNext02.roll. Moreover, it contains opening and closure orders on documents.

This file contains all modifications on the documents since they were copied to CNext02.roll. Moreover, it contains opening and closure orders on documents.
Fig.2 shows how operations in this file are grouped in lots. Each lot is a "transaction" done on a document. The ith transaction can concern a document, and the i+1th another one.

It should be noted that this file can reach a great size if the end user works a long time without saving documents.

  * A **Undoredo.log  **file

It should be noted that this file can reach a great size if the end user works a long time without saving documents.
The Autosave.log file stores operations without taking into account the undo or redo commands that the end user can do. Take the following example: the end user creates a point, and then cancels the operation. The creation is stored in the Autosave.log file, but not the reverse operation. It is the role of the Undoredo.log file to keep the "track" of transactions.

The Undoredo.log file, smaller than the Autosave.log file, contains information on each transaction contained in the Autosave.log file. It also keeps track of the last closed (or validated) transaction. An opened transaction is a no validated transaction, and therefore not replayed at the restoration stage. It is detailed in the Transaction section.

Fig.2 Warm start Data Diagram ![](images/CAAAfrWarmStartDiagram.jpg)

---
#### Activation,  Deactivation,  Re-initialization Mechanisms

Fig.2 Warm start Data Diagram ![](images/CAAAfrWarmStartDiagram.jpg)
Now that backup data is described, we can explained how it is used according to end user interactions.

  1. **The session is opened in "Incremental backup"** **mode** \- Fig.1

The CNext02.roll directory is created.

  2. **A first warm start compliant document is opened  ** (Part, Drawing ou Product)

A copy of the document is done from its original location to the CNext02.roll directory.

  3. **Operations  are done on the opened document**

The Autosave.log and Undoredo.log files are modified.

  4. **The document is saved**

As all opened documents are saved, the warm start can be re-initialized: the Autosave.log and Undoredo.log files are emptied, and the copy of the document is redone.

  5. **Another warm start compliant document is opened  **

Now, two documents are in the CNext02.roll directory. (If the Autosave.log and Undoredo.log files were present, they are not deleted.)

  6. **One document is saved**

The Autosave.log and Undoredo.log files cannot be deleted, since there is one dirty file left in memory. As long as there remains dirty documents in memory, a unique save is not sufficient to re-initialize (*) the warm start.

(*) A re-initialization includes the destruction of the Autosave.log and Undoredo.log files and a copy from their original location of all loaded documents.

The Autosave.log and Undoredo.log files cannot be deleted, since there is one dirty file left in memory. As long as there remains dirty documents in memory, a unique save is not sufficient to re-initialize (*) the warm start.
  7. **Save All**

In this case, the re-initialization is possible. The Autosave.log and Undoredo.log files are deleted and the document copies are brought up to date.

  8. **Modification on documents are done, and then a command which is not warm start compliant is executed** \- See the detailed list

All data contained in the CNext02.roll directory are deleted. The end user is informed by the following message that the incremental warm start is deactivated:

Fig.3 Warm Start Deactivation Message From a Command. ![](images/CAAAfrWarmStartCommandKO.jpg)

---

All data contained in the CNext02.roll directory are deleted. The end user is informed by the following message that the incremental warm start is deactivated:
Fig.3 Warm Start Deactivation Message From a Command. ![](images/CAAAfrWarmStartCommandKO.jpg)
```vbscript
If the end user saves all the opened documents (Save All command) and leaves the no warm start compliant command, the warm start will be reactivated. As long as it is not done, the CNext02.roll directory stays empty.

```

  9. Save All has been done, modifications are done, and **a document which is not warm start compliant is opened** (A Process document for example)

The incremental warm start is deactivated, and the CNext02.roll directory is emptied The end user is informed by the following message:

Fig.4 Warm start Deactivation Message From a Workbench. ![](images/CAAAfrWarmStartWBKO.jpg)

---

Fig.4 Warm start Deactivation Message From a Workbench. ![](images/CAAAfrWarmStartWBKO.jpg)
  10. **A warm start compliant workbench is activated**

Since the documents in memory are not saved, the following message appears:

![](images/CAAAfrWarmStartWBOK.jpg)
---

Since the documents in memory are not saved, the following message appears:
Once all the documents are saved, the warm start is re-activated.

However, if all documents are saved before the warm start compliant workbench activation, the following message appears:

![](images/CAAAfrWarmStartWBOK1.jpg)
---

  11. **Closing a document** when the warm start is still active

A copy of the document exists in the backup directory. There are two cases to consider:

     * If all other documents are saved, the warm start will be re-initialized,
     * Otherwise, i.e. at least one document is still dirty, the copy of the closed document is not deleted, and the operations are recorded in the Autosave.log and Undoredo.log files.

#### Transaction

We have previously seen that the Autosave.log file contains the operations recorded during the session, and that they are grouped together in transactions Fig.2. A transaction is a lot which corresponds to a logical set of operations. When operations are replayed, only full lots are redone. It also means that if the last lot is not "closed", it will be not replayed.

To understand at which moment a transaction is closed, the type of the executed command [2] must be distinguished:

**Command Class Type** | **Transaction Closure Time**
---|---
To understand at which moment a transaction is closed, the type of the executed command [2] must be distinguished:
CATStateCommand   | When the command is ended
CATDlgDialog or CATCommand  | When the next command will open a new transaction (*)

(*) For CAA commands, it can be only a state command since the transactional mechanism is not opened, and only the state commands open natively a transaction when they are activated.
##### Here is the particular case of the Copy and Cut Command.

CATDlgDialog or CATCommand  | When the next command will open a new transaction (*)
  1. ##### Clipboard not kept

Suppose that the end user launches the Cut or the Copy command, if the application crashes before or during the paste command, after the warm start, the Paste command will be not possible. The reason is that the Cut and Copy commands copy the selected object in the clipboard which cannot be restored by the warm start feature.

  2. ##### The Cut command is not executed if it is the last validated operation

No data is lost.

[Top]
### CAA Workbench Integration

You are making a new workbench [3], you should considerer its warm start integration. There are two cases to consider:

  * It is a workbench of a non warm start compliant document ( Analysis, Process, ...)

You have nothing to do. By default, a workbench is not warm start compliant, so warm start will be not activated in this new workbench.

  * It is a workbench of a warm start compliant document (Part, Product, Drawing)

> You should declare that the new CAA workbench is warm start compliant. It is done by adding the following line in the CATRsc resource file of the workbench [4]:
>
>
>     AllowWarmStart="YES" ;
>
> ---
>
> You find this file in the CNext/resource/msgcatalog directory of the framework defining the workbench.
>
> The warm start compatibility will be checked on each command such as described in the next section.

[Top]
### CAA Command Integration

Once you have created a command [5], you should check its integration in the warm start mechanism. This section explains you which commands are concerned, and if any, how you can use the _CATOmbWarmStartServices_ class to activate, deactivate the warm start, or validate a transaction. Commands which create applicative container, or use non V5 documents, end this section.
#### **What are Commands to Take Into Account?**

Once you have created a command [5], you should check its integration in the warm start mechanism. This section explains you which commands are concerned, and if any, how you can use the _CATOmbWarmStartServices_ class to activate, deactivate the warm start, or validate a transaction. Commands which create applicative container, or use non V5 documents, end this section.
Any command which modifies a V5 document, launched from a command header [6] or not, is concerned by the warm start. However, these two following cases can be excluded:

  1. Undefined command

```vbscript
```vbscript
For recall, an undefined command is a command which is not seen by the focus manager [2]. It means that such command are never activated, deactivated or killed by this object. An example is the Search command [7]. These commands should not be concerned by the warm start, because they should not contain operations on document. Two commands should not work on the same object at the same time.

```

```

```vbscript
For recall, an undefined command is a command which is not seen by the focus manager [2]. It means that such command are never activated, deactivated or killed by this object. An example is the Search command [7]. These commands should not be concerned by the warm start, because they should not contain operations on document. Two commands should not work on the same object at the same time.
  2. Command launched from a no warm start document

```

Please note that if today the document does not support warm start, one day it could do it. If now, you can exclude the command, it is only because the warm start will be first deactivated by the workbench of the document.

#### Why and How to Deactivate the Warm Start?

It is necessary to make sure that the command will not corrupt the backup restoration. For that it is necessary to analyze the operations which are made on the document.

  * **W****arm start compliant operation list**

All the following operations are re-playable:

    * Document: Open , New, Save
    * Container: Creation inside a state command
    * Selection Set
    * Feature:
      * Creation, Copy, Paste, Delete, Update
      * Attribute addition
      * Attribute modification such as graphical property modification (except some Drafting elements)
      * Activation and deactivation.

It is available on any features: Dassault Systemes and CAA features

  * **List of operations which are not w****arm start compliant  **

```vbscript
If one of the operations which follow is carried out in the command, the warm start will have to be deactivated.

```

    * Applicative attribute addition on sub-elements,
    * CGM attribute addition outside Build implementation,
    * Applicative container creation outside a state command,
    * Graphical property modification on some Drafting elements
    * Document creation by the `NewFrom` method of the _CATDocumentServices_ class

To deactivate the warm start, you should use the `Deactivate` method of the _CATOmbWarmStartServices_ class _._ This call must be done in the command activation. Here is an code example:

    class CAAMyCommand : public CATCommand
    {
          ...
             CATStatusChangeRC **Activate**( CATCommand *iCmd,CATNotification *iNotif);
          ...
    }

---

_CAAMyCommand_ derives from CATCommand, but it can be _CATStateCommand_ or _CATDlgDialog._ The unique common point is that the command is shared or exclusive. The `Activate` method is called by the focus manager once the command is activated or reactivated after a deactivation by a shared command. In the two cases the deactivated state is tested, because the command which has interrupted the _CAAMyCommand_ command might have reactivated the warm start.

_CAAMyCommand_ derives from CATCommand, but it can be _CATStateCommand_ or _CATDlgDialog._ The unique common point is that the command is shared or exclusive. The `Activate` method is called by the focus manager once the command is activated or reactivated after a deactivation by a shared command. In the two cases the deactivated state is tested, because the command which has interrupted the _CAAMyCommand_ command might have reactivated the warm start.
    CATStatusChangeRC CAAMyCommand::Activate( CATCommand *iCmd,CATNotification *iNotif)

    {
_CAAMyCommand_ derives from CATCommand, but it can be _CATStateCommand_ or _CATDlgDialog._ The unique common point is that the command is shared or exclusive. The `Activate` method is called by the focus manager once the command is activated or reactivated after a deactivation by a shared command. In the two cases the deactivated state is tested, because the command which has interrupted the _CAAMyCommand_ command might have reactivated the warm start.
CATStatusChangeRC CAAMyCommand::Activate( CATCommand *iCmd,CATNotification *iNotif)
       CATBoolean WarmStartActivationState = FALSE ;
       HRESULT rc = CATOmbWarmStartServices::**IsActive**(WarmStartActivationState );
```vbscript
       if ( SUCCEEDED(rc) && (TRUE == WarmStartActivationState) )

```

       {
CATBoolean WarmStartActivationState = FALSE ;
HRESULT rc = CATOmbWarmStartServices::**IsActive**(WarmStartActivationState );
if ( SUCCEEDED(rc) && (TRUE == WarmStartActivationState) )
          CATUnicodeString WarningMessageToDisplay ;
          rc = **CATOmbWarmStartServices** ::**Deactivate**(WarningMessageToDisplay);
```vbscript
```vbscript
          if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )

```

```

          {
CATUnicodeString WarningMessageToDisplay ;
rc = **CATOmbWarmStartServices** ::**Deactivate**(WarningMessageToDisplay);
```vbscript
if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )
```

             CATApplicationFrame *pFrame = CATApplicationFrame::**GetFrame**();
```vbscript
             if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))

```

             {
```vbscript
if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )
CATApplicationFrame *pFrame = CATApplicationFrame::**GetFrame**();
if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))
                CATDlgNotify * pNotify = new **CATDlgNotify**(
                                            pFrame->GetMainWindow(),
```

                                            "AutoSaveId",
```vbscript
if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))
CATDlgNotify * pNotify = new **CATDlgNotify**(
pFrame->GetMainWindow(),
                                      CATDlgNfyInformation|CATDlgNfyOK|CATDlgWndModal) ;

                CATUnicodeString NotifyWindowTitle= "....";
                pNotify->**DisplayBlocked**(WarningMessageToDisplay,NotifyWindowTitle);

                pNotify->**RequestDelayedDestruction();**
                pNotify = NULL ;
```

             }
          }
       }
    }

---

Before deactivating the warm start, you can test that it is not already deactivated. The `Deactivate` method returns a message that you should display to inform the end user. This message, Fig.4, is displayed through a _[CATDlgNotify](../CAADlgQuickRefs/CAADlgCATDlgNotify.md)_ class instance:

  * The dialog parent of the _CATDlgNotify_ class instance is the object returned by the `GetMainWindow` method of the _CATApplicationFrame_ class. Refer to the technical article entitled "Understanding the Application Frame Layout " for complete details about the dialog parent of a dialog box. [8]
  * `AutoSaveId` is the identifier of the dialog box
  * `CATDlgNfyInformation,CATDlgNfyOK `and `CATDlgWndModal` are the information style

The `DisplayBlocked` method usage avoids setting a callback to close the window. The `RequestDelayedDestruction` call will be executed after the closure of the window by the end user.  The first argument of the `DisplayBlocked` method is the message to display, and the second one is the title of the window.

```vbscript
```vbscript
For the title of the window, you can set for example the command's NLS name. If the command is activated from a command header [6], this NLS name is the title of the command header instance [9].

```

```

    ...
          CATUnicodeString NotifyWindowTitle= "CommandClassName";
          CATString CatalogName="xxx";
          CATString MessageKey = "xxx.yyy.**Title** ";
          CATMsgCatalog::**BuildMessage**(CatalogName,MessageKey,NULL,0,NotifyWindowTitle);

    ...

---

where

  * `CommandClassName` is the name of the command class.
  * `xxx` is the command header resource file name.
  * `yyy` is the command header instance (which the command class is associated with).

#### Why and How to Activate or Re-initialize the Warm Start?

```vbscript
If the command saves or closes one or several documents, it can try to activate or re-initialize the warm start. The activation will succeed if the following conditions are met:

```

```vbscript
If the command saves or closes one or several documents, it can try to activate or re-initialize the warm start. The activation will succeed if the following conditions are met:
  1. Warm Start option is activated, Fig.1
  2. Command is launched from a workbench which authorizes the warm start,
  3. All documents in session are saved, or not dirty. If you close or save all the loaded documents, this last condition is of course always true.

The `Activate` method of the _CATOmbWarmStartServices_ class enables you to try to reactivate the warm start. This call must be done just after the last closure or saving. Here is a piece of code:

          CATUnicodeString WarningMessageToDisplay ;
          rc = **CATOmbWarmStartServices** ::**Activate**(WarningMessageToDisplay);
```vbscript
          if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )
```

```

          {
CATUnicodeString WarningMessageToDisplay ;
rc = **CATOmbWarmStartServices** ::**Activate**(WarningMessageToDisplay);
```vbscript
if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )
```

             CATApplicationFrame *pFrame = CATApplicationFrame::**GetFrame**();
```vbscript
             if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))

```

             {
```vbscript
if (SUCCEEDED(rc) && (0 != WarningMessageToDisplay.GetLengthInChar()) )
CATApplicationFrame *pFrame = CATApplicationFrame::**GetFrame**();
if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))
                CATDlgNotify * pNotify = new **CATDlgNotify**(
                                            pFrame->GetMainWindow(),
```

                                            "AutoSaveId",
```vbscript
if ( (NULL != pFrame ) && ( NULL != pFrame->**GetMainWindow**() ))
CATDlgNotify * pNotify = new **CATDlgNotify**(
pFrame->GetMainWindow(),
                                            CATDlgNfyInformation|CATDlgNfyOK|CATDlgWndModal) ;

                CATUnicodeString NotifyWindowTitle= "....";
                pNotify->**DisplayBlocked**(WarningMessageToDisplay,NotifyWindowTitle);

                pNotify->**RequestDelayedDestruction();**
                pNotify = NULL ;
```

             }
          }
       }
    }

---

Refer to the previous section for details.
#### Why and How to Commit a Transaction?

Refer to the previous section for details.
Normally the operations inside a command are validated at the end of the command for a state command, or at the activation of the next state command for the others type of commands. That means that as long as the validation is not made, if the V5 session is broken, the last operations will be not replayed at the backup. However, you can force this validation during a command if it is necessary.

The `CommitTransaction` method of the _CATOmbWarmStartServices_ class enables you to do so. This call must be done just after the last validated operation.

#### Commands Creating Applicative Container

Normally the operations inside a command are validated at the end of the command for a state command, or at the activation of the next state command for the others type of commands. That means that as long as the validation is not made, if the V5 session is broken, the last operations will be not replayed at the backup. However, you can force this validation during a command if it is necessary.
The `CommitTransaction` method of the _CATOmbWarmStartServices_ class enables you to do so. This call must be done just after the last validated operation.
The method to create an applicative container is the _CATCreateApplicativeContainer_ global function [10]. Once the applicative container is created you have in this order to:

  1. Call its initialization through the `Init` method of the _CATInit_ interface [11]

You call it only if the container implements the _CATInit_ interface. Inside this implementation you find the provider declarations, and sometime feature creations.

  2. Call the _CATOmbPerformAfterContainerCreation_ global function

This call enables the application to initialize the undo/redo and the transactional mechanism on the container. This call must always be called **after** the container initialization. If you do it before the operations done in the `Init` method will be stored in the backup data. So when the document will be reloaded, the operations in the `Init` method will be executed twice: first by the warm start restoration and a second time, by the automatically call to the `Init` method.

Here is an extract of code to create an applicative container inside a command:

    ...
Here is an extract of code to create an applicative container inside a command:
    CATBaseUnknown * pAppliContainer = NULL;
    CATDocument *pDocument = ... ;
    CATIdent AppliContainerType = "....";
    CATIdent AppliContainerSuperType = "....";
    CATUnicodeString AppliContainerIdentifier = "...";

    HRESULT rc = ::**CATCreateApplicativeContainer**(&pAppliContainer,
                           pDocument ,
                           AppliContainerType,
                           IID_CATIContainer,
                           AppliContainerSuperType,
                           AppliContainerIdentifier);

```vbscript
    if ( SUCCEEDED(rc) && (NULL !=pAppliContainer) )

```

    {
AppliContainerSuperType,
AppliContainerIdentifier);
if ( SUCCEEDED(rc) && (NULL !=pAppliContainer) )
       CATIContainer * pIContainer =  (CATIContainer *) pAppliContainer ;

       **CATInit** * pInitOnApplicativeContainer = NULL ;
```vbscript
if ( SUCCEEDED(rc) && (NULL !=pAppliContainer) )
CATIContainer * pIContainer =  (CATIContainer *) pAppliContainer ;
       rc = pIContainer->QueryInterface(IID_CATInit, (void**) & pInitOnApplicativeContainer);
```vbscript
       if ( SUCCEEDED(rc) )
```

```

       {
rc = pIContainer->QueryInterface(IID_CATInit, (void**) & pInitOnApplicativeContainer);
```vbscript
if ( SUCCEEDED(rc) )
```

          pInitOnApplicativeContainer->**Init**(FALSE);
          pInitOnApplicativeContainer->Release();
          pInitOnApplicativeContainer = NULL ;

       }
pInitOnApplicativeContainer->**Init**(FALSE);
pInitOnApplicativeContainer->Release();
pInitOnApplicativeContainer = NULL ;
       rc ::**CATOmbPerformAfterContainerCreation**(pIContainer);

    }
    ...

---
#### **Commands Using Non V5 Documents**

The warm start architecture is not able to manage modifications in non-V5 documents. This kind of command needs to be checked individually.

[Top]

* * *
### In Short

The incremental backup is a mean to distribute the "automatic save" time along the session. The principle is to keep a copy of the loaded documents and to store the modifications done on these documents. In case of crash, it is possible to restore the model such as it was before the interruption of the session, except the last non validated transaction.

However, some operations on data are not re-playable. If the warm start is not stopped before executing them, the restoration will be corrupted. This article explains why and how the warm start should be deactivated for a single command or for the whole workbench.

[Top]

* * *
### References

[1] | Document Overview
---|---
[2] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
[3] | [Creating a Workbench](../CAAAfrUseCases/CAAAfrSampleWorkbench.md)
[4] | [Creating Resources for Workbenches](CAAAfrI18NWorkshop.md)
[5] | [Getting Started with State Dialog Commands](../CAADegTechArticles/CAADegGettingStarted.md)
[6] | [The Command Headers](CAAAfrCommandHeaders.md)
[7] | [Search Overview](../CAACafTechArticles/CAACafSearch.md)
[8] | [Understanding the Application Frame Layout ](CAAAfrLayoutV5.md)
[9] | [Creating Resources for Command Headers](CAAAfrI18NHeader.md)
[10] | Creating Features in Applicative Container
[11] | Creating New Features "From Scratch" in a Product Document
[Top]

* * *
### History

Version: **1** [Sep 2003] | Document created
---|---
[Top]

* * *

_Copyright 2003, Dassault Systmes. All rights reserved._
