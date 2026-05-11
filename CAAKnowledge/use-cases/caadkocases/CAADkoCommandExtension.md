---
title: "Adding Business Rules to a Command"
category: "use case"
module: "CAADkoUseCases"
tags: ["CATIAVPMVDAAddChild", "CAADkoCommandExtenstion", "CAAVPMDesktopObjects", "CATIAVPMAddChild", "CATIAVPMVDACommandExtension", "CATImplementClass", "CATIAVPMVDACommand", "CATIAVPMVDAAddChild_var", "CAADkoCommandExtension", "CATIAVPMVDACommandFactory_var", "CATIAVPMVDACopy", "CATIAVPMVDAExists"]
source_file: "Doc\online\CAADkoUseCases\CAADkoCommandExtension.htm"
converted: "2026-05-11T17:33:45.967445"
---

Lifecycle Applications |  EBOM Part & Assembly Detailing |  Adding Business Rules to a Command _Customizing a command with a pre- and post-process_  
---|---|---  
Use Case  
  
* * *

Abstract This article shows how to extend a server command to perform some checks before executing this command and to perform some works after executing this same command. 

  * **What You Will Learn With This Use Case**
  * **The CAADkoCommandExtension Use Case**
    * What Does CAADkoCommandExtension Do
    * How to Launch CAADkoCommandExtension
    * Where to Find the CAADkoCommandExtension Code
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

What You Will Learn With This Use Case This use case is intended to show you how to implement a single interface to plug in rules before executing a command and after its execution. A command has input parameters, is executed, and can have output parameters. A command is also designed to call some additional code to check specific rules or execute specific actions depending on each customer.  
This additional code is made available to the command by implementing the Prepare and Cleanup methods of the CATIAVPMVDACommandExtension interface in an extension class of the command.  
Before executing, the command will call the Prepare method. At this point, Prepare can have access to all the input parameters of the command. If those parameters, or if other conditions are not satisfactory, Prepare can return an error code to prevent the command from beeing executed.  
If Prepare returns successfully, and the command is executed, it then calls the Cleanup method. At this point, Cleanup can have access to all input and output parameters. But returning an error code here will have no effect on the command execution, since this execution is completed. [Top] The CAADkoCommandExtenstion Use Case CAADkoCommandExtenstion is a use case of the CAAVPMDesktopObjects.edu framework that illustrates VPMDesktopObjects framework capabilities. [Top] What Does CAADkoCommandExtension Do CAADkoCommandExtension is a data extension of the CATIAVPMAddChild command. The way to extend other server commands is exactly the same, so we just extend one of them. CATIAVPMAddChild is used to create a business object and attach it to a parent business object, for example when creating a Part Instance and attaching it to a Product Root Class.

  1. In this use case, we implement two simple rules before and after executing the command: Before the execution, we check that a Context object (of type ENOVIA_VPMContext) already exists, and that its identifier is composed of the name of the object to create to which the string " for context" is appended. If this context object does not exist, we send back an error code to prevent the command from creating the object. 
  2. After the execution, the business object is created, we retrieve it and copy it in the clipboard. 

[Top] How to Launch CAADkoCommandExtension To launch CAADkoCommandExtension , you will need to set up the build time environment, then compile CAADkoCommandExtension along with its prerequisites, set up the run time environment, and then execute the use case [1]. [Top] Where to Find the CAADkoCommandExtension Code The CAADkoCommandExtension use case is made of a single file located in the CAADkoCommandExtension.m module of the CAAVPMDesktopObjects.edu framework: | Windows | `InstallRootDirectory\CAAVPMDesktopObjects.edu\CAADkoCommandExtension.m\`  
---|---  
Unix | `InstallRootDirectory/CAAVPMDesktopObjects.edu/CAADkoCommandExtension.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There are three logical steps in CAADkoCommandExtension:

  1. Creating the CAADkoCommandExtension class
  2. Implementing the Prepare method
  3. Implementing the Cleanup method
  4. Updating the dictionary

[Top] Creating the CAADkoCommandExtension We first create two files, one for the definition of the extension class, the header file, and one for the implementation of the class.  
The header file is the following : 
    
    
    class ExportedByCAADkoCommandExtension CAADkoCommandExtension : public CATBaseUnknown
    {
        CATDeclareClass;
    
        public :
    
            /** Default Constructor.
             */
    
            CAADkoCommandExtension();
    
    
            /** Destructor.
             */
    
            virtual ~CAADkoCommandExtension();
    
    
            /** Called just before the execution of the command.
              * The execution of a command is made of three steps : preparation with parameters,
              * execution, cleanup and retrieval of the results. This method is called just before
              * the execution, so that every parameter is accessible and the execution of the command
              * can be cancelled if this method returns an error code.
             */
    
            HRESULT Prepare();
    
    
            /** Called just after the execution of the command.
              * This method is called just after the execution, so that further work can be done
              * on the results of the command.
             */
    
            HRESULT Cleanup();
    
    
        private :
    
            /** Copy constructor.
             */
    
            CAADkoCommandExtension( const CAADkoCommandExtension & Extension );
    };
            
  
---  
In the header file of the class, make it derive from CATBaseUnknown, and use the CATDeclareClass macro to define some methods used by QueryInterface. The implementation file is the following (empty so far) : 
    
    
    /** Class to implement custom rules when using the AddChild command (example).
      * The purpose of this implementation is to code custom rules before and after executing a
      * server command.  
    
      * The name of the object to extend is defined by the name of the command to extend. In this
      * case it is CATVpmVDAAddChild.
     */
    
    CATImplementClass( CAADkoCommandExtension, DataExtension, CATBaseUnknown, CATVpmVDAAddChild );
    
    
    #include "TIE_CATIAVPMVDACommandExtension.h"
    TIE_CATIAVPMVDACommandExtension( CAADkoCommandExtension );
    
    
    /** Constructor.
     */
    
    CAADkoCommandExtension::CAADkoCommandExtension()
    {}
    
    
    /** Destructor.
     */
    
    CAADkoCommandExtension::~CAADkoCommandExtension()
    {}
    
    
    /** Called just before the execution of the command.
      * The execution of a command is made of three steps : preparation with parameters,
      * execution, cleanup and retrieval of the results. This method is called just before
      * the execution, so that every parameter is accessible and the execution of the command
      * can be cancelled if this method returns an error code.
     */
    
    HRESULT CAADkoCommandExtension::Prepare()
    {
        HRESULT RC = S_OK;
        return RC;
    }
    
    
    /** Called just after the execution of the command.
      * This method is called just after the execution, so that further work can be done
      * on the results of the command.
     */
    
    HRESULT CAADkoCommandExtension::Cleanup()
    {
        HRESULT RC = S_OK;
        return RC;
    }
            
  
---  
In the implementation file, we have to put some code to help the QueryInterface giving the correct interfaces and implementations. This file is an implementation of CATIAVPMVDACommandExtension, and is an extension of the AddChild command. To specify this :  
Use the CATImplementClass macro.  
CAADkoCommandExtension is the name of the class implementing the interface CATIAVPMVDACommandExtension.  
DataExtension is the keyword to tell that this class is an extension.  
CATBaseUnknown is the class from which this class derives.  
CATVpmVDAAddChild is the name of the extended class (CATVpmVDA followed by the name of the command).  
Include the TIE header file for the definition of methods, the macro TIE_CATIAVPMVDACommandExtension will implement them. [Top] Implementing the Prepare method
    
    
        CATIAVPMVDAAddChild_var spAddChild( this );
            
  
---  
We first get the CATIAVPMVDAAddChild interface in order to retrieve the input parameters of the command.
    
    
        spAddChild->get_ChildData( pChildtype, pIdentifier, pName, pDescription, piChildReference );
            
  
---  
Those parameters are the type of the business object to create, its identifier, its name, its description, and the reference of the object if needed (when creating a Part Instance, the command needs the Part Reference to instanciate).
    
    
    	// Construct and get an Exists Command, to search for objects.
    	CATIAVPMVDACommandFactory_var spCommandFactory = GetCommandFactory();
    	CATIAVPMVDACommand * piCommand = NULL;
    
    	CATUnicodeString ExistsString( "Exists" );
    
    	// Create the Exists command.
    	RC = spCommandFactory->Create( ExistsString, piCommand );
            
  
---  
We get the factory of command by calling the global function GetCommandFactory() located in VPMCommandServices. We can then create a command dedicated for searching objects, called Exists command. We have a generic pointer on this command, a CATIAVPMVDACommand pointer. To use it properly, we must get the CATIAVPMVDAExists interface.
    
    
    	// Retrieve the interface of this Exists command.
    	CATIAVPMVDAExists * piExistsCommand = NULL;
    	RC = piCommand->QueryInterface( IID_CATIAVPMVDAExists, (void **) & piExistsCommand );
            
  
---  
This is achieved by doing a QueryInterface. We have now the proper interface to search for objects.
    
    
    	// Constructs parameters for the command.
    	CATUnicodeString ObjectType( "ENOVIA_VPMContext" );
    
    	// Execute the Exists Command.
    	piExistsCommand->put_Type( ObjectType );
    	piExistsCommand->put_ID( ContextName );
    	piExistsCommand->Exec();
            
  
---  
We prepare the parameters for the search, the type of objects to search for, ENOVIA_VPMContext, and the identifier of the object. We pass those parameters to the Exists command and execute it.
    
    
    	// Get the result object, if any.
    	ENOVIABusinessObject * piObjectResult = NULL;
    	piExistsCommand->get_BObject( piObjectResult );
    	
    	if ( piObjectResult != NULL )
    	{
    	    // The Context object exists, the check is good.
    	    piObjectResult->Release();
    	    piObjectResult = NULL;
    	}
    	else
    	{
    	    // The Context object does not exists, we suppose then that it is
    	    // an error, send an error code to bypass the execution.
    	    RC = E_FAIL;
        	}
            
  
---  
Once the Exists command has been executed, we get the result of the query, if there is one. If so, the pointer is not null and the check is OK, corresponding to the rule we chose at the beginning. If not, the object does not exist and we send back an error code to prevent the AddChild command from being executed. [Top] Implementing the Cleanup method
    
    
        CATIAVPMVDAAddChild_var spAddChild( this );
            
  
---  
We first get the CATIAVPMVDAAddChild interface in order to retrieve the output parameters of the command.
    
    
    	// Retrieves the created object.
    	ENOVIABusinessObject * piCreatedObject = NULL;
    	RC = spAddChild->get_ChildBObject( piCreatedObject );
            
  
---  
The AddChild command has been executed, so we can retrieve the created object which is an output parameter of this command.
    
    
    	    // Construct and get a Copy Command.
    	    CATIAVPMVDACommandFactory_var spCommandFactory = GetCommandFactory();
    	    CATIAVPMVDACommand * piCommand = NULL;
    
    	    CATUnicodeString CopyString( "Copy" );
    
    	    // Create a Copy Command.
    	    RC = spCommandFactory->Create( CopyString, piCommand );
    
    	    // Retrieves the interface of the Copy Command.
    	    CATIAVPMVDACopy * piCopyCommand = NULL;
    	    RC = piCommand->QueryInterface( IID_CATIAVPMVDACopy, (void **) & piCopyCommand );
            
  
---  
We want to copy the new created object, so we have to create a CATIAVPMVDACopy command. For this, we get the command factory by calling the global function, we ask for the creation of a Copy command and we perform a QueryInterface to get the CATIAVPMVDACopy interface to use it properly.
    
    
    	    // Execute the Copy Command.
    	    piCopyCommand->put_BObject( piCreatedObject );
    	    piCopyCommand->Exec();
            
  
---  
The only task remaining there is to put the new created object as the input parameter of the Copy command, and execute it. This object is now in the clipboard for a later use. [Top] Updating the dictionary
    
    
    CATVpmVDAAddChild   CATIAVPMVDACommandExtension   libCAADkoCommandExtension
            
  
---  
Update the dictionary giving QueryInterface the information needed (which type implements which interface in which library). In this case : CATVpmVDAAddChild is the type (the fourth parameter of the CATImplementClass macro).  
CATIAVPMVDACommandExtension is the interface implemented by the extension class.  
libCAADkoCommandExtension is the name of the library where the code is (lib followed by the name of the module).  
The dictionary is located in the directory CNext/code/dictionary of the local framework. [Top]

* * *

In Short Extending a server command consists in implementing an interface, CATIAVPMVDACommandExtension, implementing two methods, Prepare which is called before the execution of the command, and Cleanup which is called after. [Top]

* * *

References [1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[Top]  
  
* * *

History Version: **1** [May 2001] | Version: **2** [October 2003] | Document created  
---|---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
