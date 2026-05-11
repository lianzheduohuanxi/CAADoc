---
title: "Using the "Tools Palette" Toolbar for a Workbench"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrGeoCreationWkb_Palette", "CAAAfrGeoCreationWkb", "CATIAfrPaletteOptions", "CAAEAfrPaletteOptions", "CAAAfrPaletteOptions", "CAAGeometry", "CAAAfrEltCountHeader", "CAAAfrEltCountHdr", "CATIAfrCmdPaletteOptions", "CAAApplicationFrame"]
source_file: "Doc\online\CAAAfrUseCases\CAAAfrSamplePaletteWkb.htm"
converted: "2026-05-11T17:17:55.792002"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### Using the "Tools Palette" Toolbar for a Workbench

_How to implement CATIAfrPaletteOptions_  
---|---|---  
Use Case  
  
* * *

### Abstract

This use case is intended to show you how to implement _CATIAfrPaletteOptions_ to provide "options" which are available as soon as a specific workbench is active. 

  * **What You Will Learn With This Use Case**
  * **The CAAAfrPaletteOptions Use Case**
    * What Does CAAAfrPaletteOptions Do
    * How to Launch CAAAfrPaletteOptions
    * Where to Find the CAAAfrPaletteOptions Code
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

### What You Will Learn With This Use Case

The Tools Palette is a special toolbar which updates dynamically when:

  * Entering a workbench - The workbench implements the _CATIAfrPaletteOptions_ interface. 



> Command headers are added in the Palette once the workbench is activated, and they are removed from the toolbar after the workbench deactivation.

  * Executing a shared/exclusive command - The command implements the _CATIAfrCmdPaletteOptions_ interface. 



> Command headers may be added when the command is activated and they are removed when the command is canceled. For a state command, there is also the possibility to add command headers for a specific state, they are removed when the state is left. When the command is deactivated, the command headers become unavailable. [1]

This use case is intended to show you how to implement _CATIAfrPaletteOptions.   _ [Top]

### The CAAAfrPaletteOptions Use Case

CAAAfrPaletteOptions is a use case of the CAAApplicationFrame.edu framework that illustrates ApplicationFrame framework capabilities. [Top]

#### What Does CAAAfrPaletteOptions Do

CAAAfrPaletteOptions is the implementation of the _CATIAfrPaletteOptions_ on a workbench of the CAAGeometry document [2]. It enables us to display a specific toolbar, the "Tools Palette" toolbar. This toolbar contains, like the other toolbars defined in workbench or Add-in [3], command header instances. In the use case, there is a command header displaying the count of points and lines created in the CAAGeometry document. Fig.1 Tools Palette | ![](images/CAAAfrSamplePaletteWkb.jpg)  
---  
  
This header is a customized command header. Its graphic representation is not a check button with an icon, but two _CATDlgEditor_ class instances. Refer to the CAAAfrEltCountHeader use case [4] for complete details about this specific header. 

Now, if you launch the Cuboid command from the Solids Toolbar, you can see on the above picture, [Fig.2], that new options are added. This command also uses  Tools Palette options for its scenario [1].

Fig.2 Cuboid Command ![](images/CAAAfrSamplePaletteWkbWithCmd.jpg)  
---  
  
Once the Cuboid command is completed, the Tools Palette is restored, and contains the two editors again.

[Top]

#### How to Launch CAAAfrPaletteOptions

See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)" use case for a detailed description of how this use case should be launched. 

Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:

  * On the **Start** menu, point to **Infrastructure** , and then click **CAA V5: Geometrical Creation**
  * click **Point** and create some points
  * click **Line** and create some points
  * click **Cuboid**  
    * Select a point 
    * click ![](images/CAACreateBoxSwitchAgentCuboidWidthDepth.jpg)
    * Select a second point 
    * click ![](images/CAACreateBoxSwitchOrigin.jpg) (the icon is not highlighted any more) 
    * indicate a point to define the depth (= height)



[Top]

#### Where to Find the CAAAfrPaletteOptions Code

The CAAAfrPaletteOptions use case is made of a single class,_CAAEAfrPaletteOptions_ , located in the CAAAfrPaletteOptions.m module of the CAAApplicationFrame.edu framework:

Windows | `InstallRootDirectory\CAAApplicationFrame.edu\CAAAfrPaletteOptions.m\`  
---|---  
Unix | `InstallRootDirectory/CAAApplicationFrame.edu/CAAAfrPaletteOptions.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

There are two logical steps in CAAAfrPaletteOptions:

  1. Creating the Header File
  2. Creating the Source File



[Top]

#### Creating the Header File

Here is the CAAEAfrPaletteOptions.h file
    
    
    #include "CATBaseUnknown.h"    
    #include "CATListOfCATCommandHeader.h"       
    
    class CAAEAfrPaletteOptions: public CATBaseUnknown
    {
      CATDeclareClass;
    
      public:
    
        CAAEAfrPaletteOptions();
        virtual ~CAAEAfrPaletteOptions();
     
        CATLISTP(CATCommandHeader) **GetPaletteOptions**();
    
    
      private:
        CAAEAfrPaletteOptions(const CAAEAfrPaletteOptions &iObjectToCopy);
        CAAEAfrPaletteOptions & operator = (const CAAEAfrPaletteOptions &iObjectToCopy);
         
    };  
  
---  
  
The _CAAEAfrPaletteOptions_ class derives from _CATBaseUnkown_. The `GetPaletteOptions` method is the only one method of the _CATIAfrPaletteOptions_ interface. The `CATDeclareClass` macro declares that the _CAAEAfrPaletteOptions_ class belongs to a component. Note that the copy constructor and the assignment operator are set as private, and are not implemented in the source file. This prevents the compiler from creating them as public without you know.

[Top]

#### Creating the Source File

Here is the CAAEAfrPaletteOptions.cpp file
    
    
    ...
    #include <TIE_CATIAfrPaletteOptions.h>
    TIE_CATIAfrPaletteOptions(CAAEAfrPaletteOptions);
    
    CATImplementClass(CAAEAfrPaletteOptions, 
                      **DataExtension** , 
                      CATBaseUnknown, 
                      **CAAAfrGeoCreationWkb_Palette**);
    
    CAAEAfrPaletteOptions::CAAEAfrPaletteOptions():CATBaseUnknown(){}
    
    CAAEAfrPaletteOptions::~CAAEAfrPaletteOptions(){}
    ...  
  
---  
  
The _CAAEAfrPaletteOptions_ class states that it implements the _CATIAfrPaletteOptions_ interface thanks to the `TIE_CATIAfrPaletteOptions` macro. The `CATImplementClass` macro declares that the _CAAEAfrPaletteOptions_ class is a data extension, thanks to the `DataExtension` keyword, that extends `CAAAfrGeoCreationWkb_Palette`. The third argument must always be set as _CATBaseUnknown_ or _CATNull_ for any kind of extension. 

`CAAAfrGeoCreationWkb_Palette`: is the concatenation of the internal name of the workbench + "_`Palette"`. This interface can be only implemented on your workbench. You cannot implement it on a Dassault System workbench. The internal name of the workbench is the third argument of the `NewAccess` macro when the first argument is `CATCmdWorkbench` [5].
    
    
    ...
    NewAccess(**CATCmdWorkbench** ,pCAAAfrGeoCreationWkb,CAAAfrGeoCreationWkb);  
  
---  
  
Now, lets us see the `GetPaletteOptions` implementation.
    
    
    ...
    CATLISTP(CATCommandHeader) CAAEAfrPaletteOptions::GetPaletteOptions()
    {
        CATLISTP(CATCommandHeader) TheListToReturn ;
    
        CATCommandHeader *pMyCommand = NULL ;
        HRESULT rc= ::**CATAfrGetCommandHeader**("CAAAfrEltCountHdr",pMyCommand);
    
        if ( FAILED(rc) || ( NULL ==pMyCommand) )
        {
            pMyCommand = new **CAAAfrEltCountHeader**("CAAAfrEltCountHdr");
        } 
    
        if ( NULL != pMyCommand)
        {
           TheListToReturn.**Append**(pMyCommand);
        }
    
        return TheListToReturn ;
    }
    ...  
  
---  
  
The goal of this method is to append command header instances into the returned list. The most important thing, is to take care of the instantiation. This method is called each time one enters in the concerned workbench. So before instantiating the command header class, check that the instantiation does not already exist. Refer to the "Command Header Management" section of the technical article about the command header [6] to understand the life cycle of a command header instance. 

To do the check, use _CATAfrGetCommandHeader_ , the global function which returns an instance associated with the current editor. (The _CATFrmEditor_ class instance associated with the document). If no instance, i.e  `pMyCommand` the second argument of the global function is NULL, then you can create the command header instance.

[Top]

* * *

### In Short

This use case has explained how to implement the _CATIAfrPaletteOptions_ interface to add options in the Tools Palette for your workbench. 

[Top]

* * *

### References

[1] | [Creating a Command with Options in the "Tools Palette" Toolbar](CAAAfrCmdPalette.htm)  
---|---  
[2] | [The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.htm)  
[3] | [Application Frame Overview](../CAAAfrTechArticles/CAAAfrOverview.htm)  
[4] | [Creating Editors in Toolbar](CAAAfrSampleEditorHdr.htm)  
[5] | [Creating a Workbench](CAAAfrSampleWorkbench.htm)  
[6] | [The Command Headers](../CAAAfrTechArticles/CAAAfrCommandHeaders.htm)  
[Top]  
  
* * *

### History

Version: **1** [Feb 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
