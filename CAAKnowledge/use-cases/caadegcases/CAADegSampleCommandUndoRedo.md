---
```vbscript
title: "Managing Command Undo/Redo"
category: "use case"
module: "CAADegUseCases"
tags: ["CAADegCreatePolylineCmd", "CATIUndoTransaction", "CAAISysPolyline", "CAADialogEngine", "CAAGeometry", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleCommandUndoRedo.htm"
converted: "2026-05-11T17:33:49.596686"
```

---
tags: ["CAADegCreatePolylineCmd", "CATIUndoTransaction", "CAAISysPolyline", "CAADialogEngine", "CAAGeometry", "CAADegGeoCommands"]
source_file: "Doc/online/CAADegUseCases/CAADegSampleCommandUndoRedo.htm"
converted: "2026-05-11T17:33:49.596686"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Command Undo/Redo _Enabling the end user to undo and redo the command result_  

converted: "2026-05-11T17:33:49.596686"
3D PLM Enterprise Architecture |  User Interface - Commands |  Managing Command Undo/Redo _Enabling the end user to undo and redo the command result_
Use Case  

* * *

Abstract This article shows how to add undo/redo capabilities to a command to enable the end user to undo and redo the command result when the command is completed. 
    * **What You Will Learn With This Use Case**
    * **The Polyline Command Use Case**
      * What Does the Polyline Command Do
      * How to Launch the Polyline Command
      * Where to Find the Polyline Command Code
    * **Step-by-Step**
    * **In Short**
    * **References**  
---  

* * *

What You Will Learn With This Use Case This use case is intended to show how to manage the command undo/redo, that is how to undo and redo the command effect after the command has completed. It deals with a non transactional document model, that is a document model that doesn't include document object undo/redo by means of the CATIUndoTransaction interface implementation. As a consequence, the document object undo/redo must be coded in the undo/redo methods. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline commmand creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. When the command is completed, and when other successive commands are also over, the command undo process can sequentially undo the command effects, starting from the last command and going up until the maximum number of undo is reached. Conversely, the polyline undone can be redone. [Top] How to Launch the Polyline Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following: 
    * Select File->New 
    * In the New box, select CAAGeometry and click OK 
    * Select Insert->Multi Lines->Polyline
    * Click to create the points that make up the polyline, and right click to end
What You Will Learn With This Use Case This use case is intended to show how to manage the command undo/redo, that is how to undo and redo the command effect after the command has completed. It deals with a non transactional document model, that is a document model that doesn't include document object undo/redo by means of the CATIUndoTransaction interface implementation. As a consequence, the document object undo/redo must be coded in the undo/redo methods. [Top] The Polyline Command Use Case The Polyline command is a use case of the CAADialogEngine.edu framework that illustrates the DialogEngine framework capabilities. [Top] What Does the Polyline Command Do The Polyline commmand creates a polyline by successively indicating or selecting points, or entering their coordinates using a dialog box. A right click stops the polyline creation and exits the command. When the command is completed, and when other successive commands are also over, the command undo process can sequentially undo the command effects, starting from the last command and going up until the maximum number of undo is reached. Conversely, the polyline undone can be redone. [Top] How to Launch the Polyline Command See the section entitled "How to Launch the CAAGeometry Use Case" in the "[The CAAGeometry Sample](../CAASysUseCases/CAASysCAAGeometryOverview.md)" use case for a detailed description of how this use case should be launched. Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready, do the following:
You can create several polylines. Then, clicking undo several times removes the polylines in their creation reverse order, and clicking redo restores them in their cration order. [Top] Where to Find the Polyline Command Code The Polyline command is made of a single class named _CAADegCreatePolylineCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`  

You can create several polylines. Then, clicking undo several times removes the polylines in their creation reverse order, and clicking redo restores them in their cration order. [Top] Where to Find the Polyline Command Code The Polyline command is made of a single class named _CAADegCreatePolylineCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the command undo/redo, there are four steps: # | Step | Where  

You can create several polylines. Then, clicking undo several times removes the polylines in their creation reverse order, and clicking redo restores them in their cration order. [Top] Where to Find the Polyline Command Code The Polyline command is made of a single class named _CAADegCreatePolylineCmd_ located in the CAADegGeoCommands.m module of the CAADialogEngine.edu framework: Windows | `InstallRootDirectory\CAADialogEngine.edu\CAADegGeoCommands.m\`
Unix | `InstallRootDirectory/CAADialogEngine.edu/CAADegGeoCommands.m/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step To create the command undo/redo, there are four steps: # | Step | Where
1 | Declare the command undo/redo methods | Header file  
2 | Create the command undo/redo object | Command member function  
3 | Provide the static undo and redo methods | Command member functions  
4 | Provide the static deallocation method | Command member function  

[Top] Declaring the Command Undo/Redo Methods The command undo/redo methods are declared in the command class header file.

    ...
3 | Provide the static undo and redo methods | Command member functions
4 | Provide the static deallocation method | Command member function
      CATCommandGlobalUndo * GetGlobalUndo();

      static void DeallocatePolyline(void * iUsefulData); 
      static void UndoCreatePolyline(void * iUsefulData);
      static void RedoCreatePolyline(void * iUsefulData); 

    ...	  

---  
static void UndoCreatePolyline(void * iUsefulData);
static void RedoCreatePolyline(void * iUsefulData);
These methods are as follows: 

    * `GetGlobalUndo` is a CATCommand redefined method that returns a CATCommandGlobalUndo object. This object contains pointers to the deallocation, undo, and redo methods to be accessed when the command itself is deleted. `GetGlobalUndo` is called just before the command completes
    * `DeallocatePolyline` is a command static method that is called to deallocate the polyline when the maximum number of undo steps is reached. At this moment, the polyline cannot be redone, and the polyline stored for redo must be deallocated
    * `UndoCreatePolyline` is a command static method that is called to undo the command result, that is the created polyline
    * `RedoCreatePolyline` is a command static method that is called to redo the command result.
These methods are as follows:
These last three methods are static because they should be accessible when the command has completed and is no more active. The class instance is deleted when the command undo process takes place. [Top] Creating the Command Undo/Redo Object The command undo/redo object is created using the `GetGlobalUndo` method.

    CATCommandGlobalUndo * CAADegCreatePolylineCmd::GetGlobalUndo()

    {
These last three methods are static because they should be accessible when the command has completed and is no more active. The class instance is deleted when the command undo process takes place. [Top] Creating the Command Undo/Redo Object The command undo/redo object is created using the `GetGlobalUndo` method.
CATCommandGlobalUndo * CAADegCreatePolylineCmd::GetGlobalUndo()
      CATCommandGlobalUndo * pCommandUndoRedo = NULL;

      if ( _EltPolyline )  _// The created polyline_

      {
CATCommandGlobalUndo * pCommandUndoRedo = NULL;
if ( _EltPolyline )  _// The created polyline_
        pCommandUndoRedo = new **CATCommandGlobalUndo**(
           (CATGlobalUndoMethod)& CAADegCreatePolylineCmd::UndoCreatePolyline,
           (CATGlobalUndoMethod)& CAADegCreatePolylineCmd::RedoCreatePolyline,
           (void *) _EltPolyline,
           (CATGlobalUndoMethod)& CAADegCreatePolylineCmd::DeallocatePolyline);

      }
(CATGlobalUndoMethod)& CAADegCreatePolylineCmd::UndoCreatePolyline,
(CATGlobalUndoMethod)& CAADegCreatePolylineCmd::RedoCreatePolyline,
(void *) _EltPolyline,
(CATGlobalUndoMethod)& CAADegCreatePolylineCmd::DeallocatePolyline);
      return pCommandUndoRedo;

    }  

---  
The CATCommandGlobalUndo instance returned by GetGlobalUndo contains pointers to 
    * The undo method
    * The redo method
    * The created polyline
    * The deallocation method.
[Top] Providing the Static Undo and Redo Methods The `UndoCreatePolyline` and `RedoCreatePolyline` methods have the following signatures.

    void CAADegCreatePolylineCmd::UndoCreatePolyline(void *iData)
    {
void CAADegCreatePolylineCmd::UndoCreatePolyline(void *iData)
      CAAISysPolyline * Elt  = (CAAISysPolyline *) iData;
      if ( Elt )

      {
        ... _// Provide undo code here_
      }
    }

    void  CAADegCreatePolylineCmd::RedoCreatePolyline(void *iData)
    {
void  CAADegCreatePolylineCmd::RedoCreatePolyline(void *iData)
      CAAISysPolyline * Elt  = (CAAISysPolyline *) iData;
      if ( Elt )

      {
        ... _// Provide redo code here_  }
    }  

---  
The pointer to the polyline is passed as a void *. Cast it to the appropriate interface pointer before using it to undo or redo the command result. [Top] Providing the Static Deallocation Method The `DeallocatePolyline` deallocates the created polyline when the maximum number of undo steps is reached.

The pointer to the polyline is passed as a void *. Cast it to the appropriate interface pointer before using it to undo or redo the command result. [Top] Providing the Static Deallocation Method The `DeallocatePolyline` deallocates the created polyline when the maximum number of undo steps is reached.
    void CAADegCreatePolylineCmd::DeallocatePolyline(void * iData)

    {
The pointer to the polyline is passed as a void *. Cast it to the appropriate interface pointer before using it to undo or redo the command result. [Top] Providing the Static Deallocation Method The `DeallocatePolyline` deallocates the created polyline when the maximum number of undo steps is reached.
void CAADegCreatePolylineCmd::DeallocatePolyline(void * iData)
      if (iData)

      {
void CAADegCreatePolylineCmd::DeallocatePolyline(void * iData)
if (iData)
        CAAISysPolyline * Elt  = (CAAISysPolyline *) iData;
        if (Elt) Elt->**Release**();

      }
    }  

---  
The pointer to the polyline is passed as a void *. Cast it to the appropriate interface pointer before releasing it. [Top]

* * *

In Short This use case shows how to add command undo/redo capabilities to a command using an undo/redo object that remains alive after the command is completed and that holds pointers to the created object, to command static undo and redo methods, and to a command static deallocation method of the created object. [Top]

* * *

References [Top]  
---  

* * *

History Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
