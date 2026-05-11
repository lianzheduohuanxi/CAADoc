---
title: "Creating a State Dialog Command"
category: "use-case"
module: "CAADegTechArticles"
tags: ["CAACommandCmd", "CATIndicationAgent"]
source_file: "Doc/online/CAADegTechArticles/CAADegCreatingCommand.md"
converted: "2026-05-11T17:33:49.764355"
---

3D PLM Enterprise Architecture |  User Interface - Commands |  Creating a State Dialog Command _How to create the dialog command class_  
---|---|---  
Technical Article  
  
* * *

Abstract This article is the state dialog command programmer's guide. Organized as a step-by-step, it deals with all you can do to program your state dialog command. 
    * **Creating the State Dialog Class Header**
    * **In Short**.  
---  
  
* * *

Creating the State Dialog Command Class Header This shows how to create the class header file. Assume your class is named CAACommandCmd. The main to do is: 
    * **Subclassing** : A state dialog command must derive from the CATStateCommand class, or from one of its subclasses you may have already created. 
          
          class CAACommandCmd : public CATStateCommand  
  
---  
    * **Resources** : they are located in the CAACommandCmd.CATNls file you will store in your framework's CNext\resources\msgcatalog directory. Resources of a dialog state command are the prompts you can associate with each state, and the undo prompts. Declare the file using the `CmdDeclareResource` macro. The base class must be set as the second parameter. 
          
          CmdDeclareResource(CAACommandCmd, CATStateCommand);  
  
---  
    * **Lifecycle** : the command lifecycle is managed using the command's constructor and destructor, and using the methods `Activate`, `Desactivate`, and `Cancel`. `Activate` is called when your command takes the focus, `Desactivate` is called when a shared command takes the focus, and thus leaves your command on the command stack in its current state, and `Cancel` is called when your command completes, or when an exclusive command takes the focus and requests your command to be deleted. 
          
          CATStatusChangeRC Activate   (CATCommand * iCmd, CATNotification * iNotif);
          CATStatusChangeRC Desactivate(CATCommand * iCmd, CATNotification * iNotif);
          CATStatusChangeRC Cancel     (CATCommand * iCmd, CATNotification * iNotif);  
  
---  
    * **Statechart** : the statechart is implemented by overriding the `BuildGraph` method. States, transitions, and dialog agents are created in this method, and guard conditions and action methods are declared as state and transition parameters. 
          
          virtual void BuildGraph();  
  
---  
    * **Dialog agents** : Dialog agents translate end user intents into end user input. They are instances of the classes CATDialogAgent, an unspecialized dialog agent that you can use, for example, to monitor end user input through a dialog box. More specialized dialog agents exist: the CATIndicationAgent to retrieve a 2D point when the end user left clicks in either a 2D or a 3D viewer, and the CATPathElementAgent to retrieve the object the end user has selected. A dialog agent should be declared as a data member to be created and used in the `BuildGraph` method, and used in condition and actions methods. Create as many dialog agents as you need. 
          
          CATDialogAgent      * _daAgent;
          CATIndicationAgent  * _daIndicationAgent;
          CATPathElementAgent * _daSelectionAgent;  
  
---  
    * **Guard conditions** : they are provided as methods of the CAACommandCmd class. They take a single argument to get data passed, if needed, by the state dialog command, and must return a CATBoolean. 
          
          CATBoolean  GuardConditionMethod1(void * iUsefulData);
          CATBoolean  GuardConditionMethod2(void * iUsefulData);  
  
---  
    * **Actions** : they are also provided as methods of the CAACommandCmd class. They also take a single argument to get data passed, if needed, by the state dialog command, and must return a CATBoolean. 
          
          CATBoolean  ActionMethod1(void * iUsefulData);
          CATBoolean  ActionMethod2(void * iUsefulData);  
  
---  
Once you have completed this step, the header file of your state dialog command class should look like this:
    #include "CATStateCommand.h"
    
    class CAACommandCmd : public CATStateCommand
    {
      CmdDeclareResource(CAACommandCmd, CATStateCommand);
      public :
        CAACommandCmd();
        virtual ~CAACommandCmd();
        CATStatusChangeRC Activate   (CATCommand * iCmd, CATNotification * iNotif);
        CATStatusChangeRC Desactivate(CATCommand * iCmd, CATNotification * iNotif);
        CATStatusChangeRC Cancel     (CATCommand * iCmd, CATNotification * iNotif);
    
        virtual void BuildGraph();
        CATBoolean  GuardConditionMethod1(void * iUsefulData);
        CATBoolean  GuardConditionMethod2(void * iUsefulData); 
        CATBoolean  ActionMethod1(void * iUsefulData);
        CATBoolean  ActionMethod2(void * iUsefulData);
    
      private :
        CATDialogAgent      * _daAgent;
        CATIndicationAgent  * _daIndicationAgent;
        CATPathElementAgent * _daSelectionAgent;
    };  
  
---  
It can include additional methods and data members, for example, to access the document objects your command can work on. [Top]

* * *

In Short A dialog state command is a dialog command designed as a state machine, each state enabling end user input, that enables the end user to pass from state to state using transitions between these states triggered when requested events happen and when requested guard conditions are satisfied, and that execute the declared actions. It is modeled using a class deriving from the CATStateCommand class. The statechart diagram is implemented using the `BuildGraph` method, and the command life cycle is managed by the `Activate`, `Desactivate`, and `Cancel` methods in addition to the command class constructor and destructor. [Top]

* * *

History Version: **1** [Jan 2000] |  Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
