---
title: "Adding Business Rules to an Interactive Command"
category: "use case"
module: "CAADkpUseCases"
tags: "["CATIAVPMVDALock", "CAAVPMDesktopProduct", "CAADkpCustomCommand", "CATIAVPMVDACommand", "CATIAVPMVDACommandFactory_var", "CATIVpmFactoryObject"]"
source_file: "Doc/online/CAADkpUseCases/CAADkpCustomCommand.htm"
converted: "2026-05-11T17:33:46.012499"
---
tags: ["CATIAVPMVDALock", "CAAVPMDesktopProduct", "CAADkpCustomCommand", "CATIAVPMVDACommand", "CATIAVPMVDACommandFactory_var", "CATIVpmFactoryObject"]
source_file: "Doc/online/CAADkpUseCases/CAADkpCustomCommand.htmmd"
converted: "2026-05-11T17:33:46.012499"
Lifecycle Applications |  EBOM Part & Assembly Detailing |  Adding Business Rules to an Interactive Command _Customizing an interactive command with a pre- and a post-process_

converted: "2026-05-11T17:33:46.012499"
Lifecycle Applications |  EBOM Part & Assembly Detailing |  Adding Business Rules to an Interactive Command _Customizing an interactive command with a pre- and a post-process_
Use Case

* * *

Abstract This article shows how to implement the ENOVICustomCommand interface, to add business rules when a panel containing a list of attributes to fill is shown for creating or updating objects.

  * **What You Will Learn With This Use Case**
  * **The CAADkpCustomCommand Use Case**
    * What Does CAADkpCustomCommand Do
    * How to Launch CAADkpCustomCommand
    * Where to Find the CAADkpCustomCommand Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *

What You Will Learn With This Use Case This use case is intended to show you how to implement ENOVICustomCommand and what it does. Let's take an example : when creating an object interactively, a panel shows up with a list of attributes to fill. This user exit is called during this scenario, several times.
When the panel is constructed, the user exit is called through BeforeInit and AfterInit methods (there is no difference between them) in order to change the list of attributes : attributes can be added, removed, hidden, filled with calculated default values... An attribute can be made sensitive.
When filling the panel and when a sensitive attribute looses the focus, the user exit is called through BeforeCheck and AfterCheck methods (there is no difference between them) in order to perform some checks on the filled values, and compute other values.
When the user clics on the OK button, the user exit is called through BeforeExecute method with every attributes and their values. At this time the user exit can still send an error code to prevent the creation of the object.
The creation occurs, and when the server has done with it, the user exit is called a last time through AfterExecute method.   [Top] The CAADkpCustomCommand Use Case CAADkpCustomCommand is a use case of the CAAVPMDesktopProduct.edu framework that illustrates VPMDesktopProduct framework capabilities. [Top] What Does CAADkpCustomCommand Do CAADkpCustomCommand is showing how to hide an attribute, how to give a default value to another one, how to make sensitive another attribute, how to compute an attribute value from what has been filled, how to check the value of an attribute and send an error code if the value is not good, how to retrieve the created object and lock it.   [Top] How to Launch CAADkpCustomCommand To launch CAADkpCustomCommand , you will need to set up the build time environment, then compile CAADkpCustomCommand along with its prerequisites, set up the run time environment, and then execute the use case [1]. [Top] Where to Find the CAADkpCustomCommand Code The CAADkpCustomCommand use case is made of several classes/a single file located in the CAADkpCustomCommand.m module of the CAAVPMDesktopProduct.edu framework: | Windows | `InstallRootDirectory/CAAVPMDesktopProduct.edu/CAADkpCustomCommand.m/`

When the panel is constructed, the user exit is called through BeforeInit and AfterInit methods (there is no difference between them) in order to change the list of attributes : attributes can be added, removed, hidden, filled with calculated default values... An attribute can be made sensitive.
When filling the panel and when a sensitive attribute looses the focus, the user exit is called through BeforeCheck and AfterCheck methods (there is no difference between them) in order to perform some checks on the filled values, and compute other values.
When the user clics on the OK button, the user exit is called through BeforeExecute method with every attributes and their values. At this time the user exit can still send an error code to prevent the creation of the object.
The creation occurs, and when the server has done with it, the user exit is called a last time through AfterExecute method.   [Top] The CAADkpCustomCommand Use Case CAADkpCustomCommand is a use case of the CAAVPMDesktopProduct.edu framework that illustrates VPMDesktopProduct framework capabilities. [Top] What Does CAADkpCustomCommand Do CAADkpCustomCommand is showing how to hide an attribute, how to give a default value to another one, how to make sensitive another attribute, how to compute an attribute value from what has been filled, how to check the value of an attribute and send an error code if the value is not good, how to retrieve the created object and lock it.   [Top] How to Launch CAADkpCustomCommand To launch CAADkpCustomCommand , you will need to set up the build time environment, then compile CAADkpCustomCommand along with its prerequisites, set up the run time environment, and then execute the use case [1]. [Top] Where to Find the CAADkpCustomCommand Code The CAADkpCustomCommand use case is made of several classes/a single file located in the CAADkpCustomCommand.m module of the CAAVPMDesktopProduct.edu framework: | Windows | `InstallRootDirectory/CAAVPMDesktopProduct.edu/CAADkpCustomCommand.m/`
Unix | `InstallRootDirectory/CAAVPMDesktopProduct.edu/CAADkpCustomCommand.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There are five logical steps in CAADkpCustomCommand:

  1. Creating the CAADkpCustomCommand class
  2. Implementing the BeforeInit method
  3. Implementing the BeforeCheck method
  4. Implementing the BeforeExecute method
  5. Implementing the AfterExecute method
  6. Updating the dictionary

[Top] Creating the CAADkpCustomCommand class We have first to create two files, one for the definition of the class, the header file, and one for the implementation of the class.
4. Implementing the BeforeExecute method
5. Implementing the AfterExecute method
6. Updating the dictionary
The header file is the following :

    /** Class to implement custom rules when creating a Part Reference.
      * The purpose of this implementation is to assist the creation of Part Reference by showing or
      * hiding attributes, defining default values, manipulating objects.

      * The name of the object to extend is defined by Java implementation : we want to customize the
      * creation of a Part Reference, so the name is given by the concatenation of the name of the
      * object (PartMaster) and the name of the command (CATVpmVDACreate).
     */

    class ExportedByCAADkpCustomCommand ENOVECreateExtension : public CATBaseUnknown
    {
class ExportedByCAADkpCustomCommand ENOVECreateExtension : public CATBaseUnknown
        CATDeclareClass;

        public:

            /** Default Constructor.
             */

            ENOVECreateExtension(#);

            /** Destructor.
             */

            virtual ~ENOVECreateExtension(#);

            /** Called before showing the panel.
              * Most of the time a panel shows up with a list of attributes to fill. This method is
              * called when building this panel. It is then the place to hide some attributes, put
              * some default values, make some mandatory or sensitive.
             */

            HRESULT BeforeInit(#);

            /** Called before showing the panel.
              * This method is called just after @href #BeforeInit and has the same use as this one.
              * So, you can implement just one of them and leave the other empty.
             */

            HRESULT AfterInit(#);

            /** Called when a sensitive attribute looses the focus.
              * When filling the attributes on the screen, if a sensitive attribute looses the focus,
              * or if its value changes in case of a combobox, then this method is called. The value
              * entered for this attribute can be retrieved to compute other values of attributes.
             */

            HRESULT BeforeCheck(#);

            /** Called when a sensitive attribute looses the focus.
              * This method is called just after @href #BeforeCheck and has the same use as this one.
              * So, you can implement just one of them and leave the other empty.
             */

            HRESULT AfterCheck(#);

            /** Called when validating the panel.
              * When the OK button is clicked at the end of the filling process, this method is
              * called before the actual command is executed. To prevent the command from being
              * executed, this method can return an error code.
             */

            HRESULT BeforeExecute(#);

            /** Called at the very end of the process.
              * This method is called after the actual command is executed. Nothing can be done here to
              * prevent the command from being executed.
             */

            HRESULT AfterExecute(#);

```vbscript
        private :

```

            /** Copy constructor.
             */

            ENOVECreateExtension( const ENOVECreateExtension & Extension );
    };

---
In the header file of the class, make it derive from CATBaseUnknown, and use the CATDeclareClass macro to define some methods used by QueryInterface. The implementation file is the following (empty so far):

    /** Class to implement custom rules when creating a Part Reference.
      * The purpose of this implementation is to assist the creation of Part Reference by showing or
      * hiding attributes, defining default values, manipulating objects.

      * The name of the object to extend is defined by Java implementation : we want to customize the
      * creation of a Part Reference, so the name is given by the concatenation of the name of the
      * object (PartMaster) and the name of the command (CATVpmVDACreate).
     */

    CATImplementClass( ENOVECreateExtension, DataExtension, CATBaseUnknown, PartMasterCATVpmVDACreate );

    #include "TIE_ENOVICustomCommand.h"
    TIE_ENOVICustomCommand( ENOVECreateExtension );

    /** Default Constructor.
     */

    ENOVECreateExtension::ENOVECreateExtension(#)
    {}

    /** Destructor.
     */

    ENOVECreateExtension::~ENOVECreateExtension(#)
    {}

    /** Called before showing the panel.
      * Most of the time a panel shows up with a list of attributes to fill. This method is
      * called when building this panel. It is then the place to hide some attributes, put
      * some default values, make some mandatory or sensitive.
     */

    HRESULT ENOVECreateExtension::BeforeInit(#)
    {
HRESULT ENOVECreateExtension::BeforeInit(#)
        HRESULT RC = S_OK;
        return RC;

    };

    /** Called before showing the panel.
      * This method is called just after @href #BeforeInit and has the same use as this one.
      * So, you can implement just one of them and leave the other empty.
     */

    HRESULT ENOVECreateExtension::AfterInit(#)
    {
HRESULT ENOVECreateExtension::AfterInit(#)
        HRESULT RC = S_OK;
        return RC;

    };

    /** Called when a sensitive attribute looses the focus.
      * When filling the attributes on the screen, if a sensitive attribute looses the focus,
      * or if its value changes in case of a combobox, then this method is called. The value
      * entered for this attribute can be retrieved to compute other values of attributes.
     */

    HRESULT ENOVECreateExtension::BeforeCheck(#)
    {
HRESULT ENOVECreateExtension::BeforeCheck(#)
        HRESULT RC = S_OK;
        return RC;

    };

    /** Called when a sensitive attribute looses the focus.
      * This method is called just after @href #BeforeCheck and has the same use as this one.
      * So, you can implement just one of them and leave the other empty.
     */

    HRESULT ENOVECreateExtension::AfterCheck(#)
    {
HRESULT ENOVECreateExtension::AfterCheck(#)
        HRESULT RC = S_OK;
        return RC;

    };

    /** Called when validating the panel.
      * When the OK button is clicked at the end of the filling process, this method is
      * called before the actual command is executed. To prevent the command from being
      * executed, this method can return an error code.
     */

    HRESULT ENOVECreateExtension::BeforeExecute(#)
    {
HRESULT ENOVECreateExtension::BeforeExecute(#)
        HRESULT RC = S_OK;
        return RC;

    };

    /** Called at the very end of the process.
      * This method is called after the actual command is executed. Nothing can be done here to
      * prevent the command from being executed.
     */

    HRESULT ENOVECreateExtension::AfterExecute(#)
    {
HRESULT ENOVECreateExtension::AfterExecute(#)
        HRESULT RC = S_OK;
        return RC;

    };

---
return RC;
In the implementation file, we have to put some code to help the QueryInterface giving the correct interfaces and implementations. This file is an implementation of ENOVICustomCommand, and is an extension of the Part Master Create command. To specify this :
Use the CATImplementClass macro.
ENOVECreateExtension is the name of the class implementing the interface ENOVICustomCommand.
DataExtension is the keyword to tell that this class is an extension.
CATBaseUnknown is the class from which this class derives.
PartMasterCATVpmVDACreate is the name of the extended class.
Include the TIE header file for the definition of methods, the macro TIE_ENOVICustomCommand will implement them.   [Top] Implementing the BeforeInit method

        // Get a reference to the server object to have access to the attributes.
PartMasterCATVpmVDACreate is the name of the extended class.
Include the TIE header file for the definition of methods, the macro TIE_ENOVICustomCommand will implement them.   [Top] Implementing the BeforeInit method
        ENOVIUEDesktopCommand_var spUECommand( this );

        // 1. Put a default value in the V_ID attribute.
        // Do not allocate VPMIQAttribute, the method does it.

ENOVIUEDesktopCommand_var spUECommand( this );
        VPMIQAttribute * pIDAttribute = NULL;
```vbscript
        RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_ID", pIDAttribute );

        if ( SUCCEEDED( RC ) && pIDAttribute )

```

        {
    	// Give a default value.
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_ID", pIDAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pIDAttribute )
```

    	pIDAttribute->SetDefaultValue( "Default Value for V_ID" );

    	// Inform the server object that the definition of the attribute has changed.
    	spUECommand->set_Parameter( "ENOVIA_VPMPartMaster", "V_ID", * pIDAttribute );
        }

        // 2. Hide the V_Description attribute.
        // Do not allocate VPMIQAttribute, the method does it.

        VPMIQAttribute * pDescAttribute = NULL;
```vbscript
        RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_description", pDescAttribute );

        if ( SUCCEEDED( RC ) && pDescAttribute )

```

        {
    	// Hide the attribute on the panel.
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_description", pDescAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pDescAttribute )
```

    	pDescAttribute->SetVisibility( 0 );

    	// Inform the server object that the definition of the attribute has changed.
    	spUECommand->set_Parameter( "ENOVIA_VPMPartMaster", "V_description", * pDescAttribute );
        }

        // 3. Make the V_Name attribute sensitive.
```vbscript
        // 4. Set the additional icon to be displayed on the UI for this attribute
        // Do not allocate VPMIQAttribute, the method does it.
```

        VPMIQAttribute * pNameAttribute = NULL;
```vbscript
        RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_name", pNameAttribute );

        if ( SUCCEEDED( RC ) && pNameAttribute )

```

        {
    	// Make the attribute sensitive.
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_name", pNameAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pNameAttribute )
```

    	pNameAttribute->SetSensible( 1 );

```vbscript
    	//Set the additional icon to be displayed
    	//The number set using SetIconsFacet(#) API will be mapped to an icon according to the entries present in
```
    	//docs/java/VPMAttributeIconList.properties file on the Client side
pNameAttribute->SetSensible( 1 );
    	CATListOfInt iconNum;
    	iconNum.Append(1);
    	pNameAttribute->SetIconsFacet( iconNum );

    	// Inform the server object that the definition of the attribute has changed.
CATListOfInt iconNum;
iconNum.Append(1);
pNameAttribute->SetIconsFacet( iconNum );
    	spUECommand->set_Parameter( "ENOVIA_VPMPartMaster", "V_name", * pNameAttribute );

        }

---
[Top] Implementing the BeforeCheck method

        // In this example, V_Name is sensitive and V_Description has been hidden. Suppose
        // then that the value of V_Description will be computed from the value of V_Name.

        // Get a reference to the server object to have access to the attributes.
        ENOVIUEDesktopCommand_var spUECommand( this );

        // 1. Retrieve V_Name definition.
ENOVIUEDesktopCommand_var spUECommand( this );
        VPMIQAttribute * pNameAttribute = NULL;
```vbscript
        RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_name", pNameAttribute );

        if ( SUCCEEDED( RC ) && pNameAttribute )

```

        {
    	// 2. Retrieve V_Description definition.
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_name", pNameAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pNameAttribute )
```

    	VPMIQAttribute * pDescAttribute = NULL;
```vbscript
    	RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_description", pDescAttribute );

    	if ( SUCCEEDED( RC ) && pDescAttribute )

```

    	{
    	    // 3. Retrieve V_Name Value.
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_description", pDescAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pDescAttribute )
```

    	    CORBAAny NameValue = pNameAttribute->GetValue(#);

    	    CATUnicodeString StringNameValue;
    	    NameValue >> StringNameValue;

    	    // 4. Construct a description and assign it.
CATUnicodeString StringNameValue;
NameValue >> StringNameValue;
    	    CATUnicodeString StringDescValue( "Description of the Part " );
    	    StringDescValue.Append( StringNameValue );

    	    CORBAAny DescValue( StringDescValue );
    	    pDescAttribute->SetValue( DescValue );

    	    spUECommand->set_Parameter( "ENOVIA_VPMPartMaster", "V_description", * pDescAttribute );

    	}
        }

---
[Top] Implementing the BeforeExecute method

        // Get a reference to the server object to have access to the attributes.
        ENOVIUEDesktopCommand_var spUECommand( this );

        // 1. Get the definition of V_ID.
ENOVIUEDesktopCommand_var spUECommand( this );
        VPMIQAttribute * pIDAttribute = NULL;
```vbscript
        RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_ID", pIDAttribute );

        if ( SUCCEEDED( RC ) && pIDAttribute )

```

        {
    	// 2. Get the value of V_ID
RC = spUECommand->get_Parameter( "ENOVIA_VPMPartMaster", "V_ID", pIDAttribute );
```vbscript
if ( SUCCEEDED( RC ) && pIDAttribute )
```

    	CORBAAny IDValue = pIDAttribute->GetValue(#);
    	CATUnicodeString StringIDValue;
    	IDValue >> StringIDValue;

    	// 3. If the value is a forbidden one, return an error.
CORBAAny IDValue = pIDAttribute->GetValue(#);
CATUnicodeString StringIDValue;
IDValue >> StringIDValue;
    	if ( StringIDValue == "ForbiddenValue" )
    	    return E_FAIL;

        }

---
[Top] Implementing the AfterExecute method

        // Get a reference to the server object to have access to the attributes.
        ENOVIUEDesktopCommand_var spUECommand( this );

        // The object is now created, we can get it.
ENOVIUEDesktopCommand_var spUECommand( this );
        CATIVpmFactoryObject * piCreatedObject = NULL;

        RC = spUECommand->get_Source( piCreatedObject );
```vbscript
```vbscript
        if ( SUCCEEDED( RC ) && piCreatedObject )

```

```

        {
    	// In this example the created object will be locked.
RC = spUECommand->get_Source( piCreatedObject );
```vbscript
if ( SUCCEEDED( RC ) && piCreatedObject )
```

    	ENOVIABusinessObject * piCreatedBO = NULL;
    	RC = piCreatedObject->QueryInterface( IID_ENOVIABusinessObject, (void **) & piCreatedBO );
```vbscript
```vbscript
    	if ( SUCCEEDED( RC ) && piCreatedBO )

```

```

    	{
    	    // Get the command factory.
ENOVIABusinessObject * piCreatedBO = NULL;
RC = piCreatedObject->QueryInterface( IID_ENOVIABusinessObject, (void **) & piCreatedBO );
```vbscript
if ( SUCCEEDED( RC ) && piCreatedBO )
```

    	    CATIAVPMVDACommandFactory_var spCommandFactory = GetCommandFactory(#);
    	    CATIAVPMVDACommand * piCommand = NULL;

    	    CATUnicodeString LockString( "Lock" );

    	    // Construct and get a Lock Command.
CATIAVPMVDACommand * piCommand = NULL;
CATUnicodeString LockString( "Lock" );
```vbscript
    	    RC = spCommandFactory->Create( LockString, piCommand );

```

    	    // Retrieves the interface of the Lock Command.
RC = spCommandFactory->Create( LockString, piCommand );
    	    CATIAVPMVDALock * piLockCommand = NULL;
```cpp
    	    RC = piCommand->QueryInterface( IID_CATIAVPMVDALock, (void **) & piLockCommand );

```

    	    // Execute the Lock Command on the object.
CATIAVPMVDALock * piLockCommand = NULL;
RC = piCommand->QueryInterface( IID_CATIAVPMVDALock, (void **) & piLockCommand );
    	    piLockCommand->put_BObject( piCreatedBO );
    	    piLockCommand->put_referenceAlso( 0==0 );
    	    RC = piLockCommand->Exec(#);
                piCreatedBO->Release(#);

    	}
        }

---
[Top] Updating the dictionary

    PartMasterCATVpmVDACreate   ENOVICustomCommand   libCAADkpCustomCommand

---
PartMasterCATVpmVDACreate   ENOVICustomCommand   libCAADkpCustomCommand
Update the dictionary giving QueryInterface the information needed (which type implements which interface in which library). In this case : PartMasterCATVpmVDACreate is the type (the fourth parameter of the CATImplementClass macro).
ENOVICustomCommand is the interface implemented by the extension class.
libCAADkpCustomCommand is the name of the library where the code is (lib followed by the name of the module).
The dictionary is located in the directory CNext/code/dictionary of the local framework.   [Top]

* * *

libCAADkpCustomCommand is the name of the library where the code is (lib followed by the name of the module).
The dictionary is located in the directory CNext/code/dictionary of the local framework.   [Top]
In Short ENOVICustomCommand is an interface designed for implementing business rules when filling attributes in a panel, during creation, update, copy, paste of objects. There are four main events that trigger the call of this interface, when the panel is built, when a sensitive attribute looses the focus, when the user clics on the OK button to terminate the process, and when the process is ended. This interface requires six methods to be implemented, two of them being useless because of duplication.   [Top]

* * *

References [1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *

History Version: **1** [May 2001] | Version: **2** [October 2003] | Document created
---|---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
