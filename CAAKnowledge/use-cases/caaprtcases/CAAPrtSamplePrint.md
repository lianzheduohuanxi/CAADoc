---
title: "Adding Print Standard Functions to Your Application"
category: "use case"
module: "CAAPrtUseCases"
tags: ["CATIA", "CAAPrtDialog", "CAAPrint", "CAAPrtApplication", "CAAPrtApplicationUse"]
source_file: "Doc/online/CAAPrtUseCases/CAAPrtSamplePrint.md"
converted: "2026-05-11T17:17:56.124848"
---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization - Print

| 
### Adding Print Standard Functions to Your Application

_Taking advantage of the Print, Capture, Album, and Printer Manager dialog boxes_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article shows how to print a given object on a printer. 

  * **What You Will Learn With This Use Case**
  * **The CAAPrtApplicationUse Case**
    * What Does CAAPrtApplication Do
    * How to Launch CAAPrtApplication
    * Where to Find the CAAPrtApplication Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to add the Print standard functions to your application.

[Top]
### The CAAPrtApplication Case

CAAPrtApplication is a set of use cases of the CAAPrint.edu framework that illustrates Print framework capabilities.

[Top]
#### What Does CAAPrtApplication Do

This use case shows the Print, Capture, Album, and  Printer Manager items of the CAAPrtApplication. For more details about the following dialog boxes, you can refer to the interactive documentation: CATIA Infrastructure > CATIA Infrastructure User Guide > Basic Tasks > Printing Document. Note that the shown pictures are Window snapshots, so dialog boxes can differ on Unix system.

**Print Item**

In the `File` menu, click `Print...` item.The following dialog box appears. It enables you to print the contents of the viewer.For more details about each widget of this dialog box, launch a CATIA session, open any document, and select the Print command in the File menu. Thanks to the ? icon you can get tool tip information.

![](images/CAAPrtSamplePrintPrintItem.jpg)  
---  
  
**Capture Item**

In the `Tools` menu, point to `Image` and click `Capture...` item. The following toolbar appears. For more details about each widget of this dialog box, launch a CATIA session, open any document, and select the Capture command in the Image sub-menu of the Tools menu. Thanks to the ? icon you can get tool tip information.

![](images/CAAPrtSamplePrintCaptureItem.jpg)  
---  
  
**Album Item**

In the `Tools` menu, point to `Image` and click `Album...` item. The following toolbar appears. For more details about each widget of this dialog box, launch a CATIA session, open any document, and select the Album command in the Image sub-menu of the Tools menu. Thanks to the ? icon you can have tool tip information.

![](images/CAAPrtSamplePrintAlbumItem.jpg)  
---  
  
**Printer Setup Item**

In the `File` menu, click `Printer Setup...` item. The Printers dialog box appears. It enables you to add/configure your printers. For more details about each widget of this dialog box, launch a CATIA session, open any document, and select the Printer Setup command in the File menu. Thanks to the ? icon you can have tool tip information.

![](images/CAAPrtSamplePrintManagerItem.jpg)  
---  
  
[Top]
#### How to Launch CAAPrtApplication

To launch CAAPrtApplication, you will need to set up the build time environment, then compile CAAPrtApplication along with its prerequisites, set up the run time environment, and then execute the use case [1].

[Top]
#### Where to Find the CAAPrtApplication Code

The CAAPrtApplication use case is made of an application class and of a window class whose header and source files are located in the CAAPrtApplication.m module of the CAAPrint.edu framework:

Windows | `InstallRootDirectory\CAAPrint.edu\CAAPrtApplication.m`  
---|---  
Unix | `InstallRootDirectory/CAAPrint.edu/CAAPrtApplication.m`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

CAAPrtApplication includes the following files:

**LocalInterfaces directory**  
---  
CAAPrtApplication.h | Header file for the interactive application  
CAAPrtDialog.h | Header file for the dialog window that hosts the viewer  
**src directory**  
CAAPrtApplication.cpp | Source file for the interactive application  
CAAPrtDialog.cpp | Source file for the dialog window that hosts the viewer  
  
This article explains the `CAAPrtDialog` class and its callbacks methods. 
#### Step-by-Step

To open and display a TIFF image file in a 2D viewer, there are four main steps:
# | Step | Where  
---|---|---  
1 | Adds the Print dialog box | PrintCB method  
2 | Adds the Capture toolbar | CaptureCB method  
3 | Adds the Album dialog box | AlbumCB method  
4 | Adds the Printer Manager dialog box | PrinterManagerCB method  
  
These capabilities are proposed to the end user as items of the File menu. A callback set for each of these items displays the appropriate dialog box. The control is then passed to the Print framework that manages the requested tasks. The four methods detailed below are callback methods. Their arguments are unused.

[Top]
#### Adding the Print Dialog Box
    
    
    void CAAPrtDialog::PrintCB(CATCommand           * iSendingCommand,
                                CATNotification      * iSentNotification,
                                CATCommandClientData   iUsefulData)
    {
      _appli->**SetBusyCursor**(); _// Set the cursor as an hourglass_
    
      _// Instantiates the Print dialog box_
      CATPrintDialog * print = new **CATPrintDialog**(this, "Print", _viewer);
    
      print->**SetVisibility**(CATDlgShow); _// Shows the Print dialog box_
    }  
  
---  
  
The cursor is set as busy and looks like an hour glass as long as the Print dialog box is not displayed. This is done using the `SetBusyCursor` method. The Print dialog box constructor has the following parameters: 

  * `this` is the dialog box parent set as the application window
  * `"Print"` is the dialog box identifier, unused here
  * `_viewer` is the application viewer. This object along with is contents will be printed.

The `SetVisibility` method displays the dialog box. The Print dialog box manages its deallocation itself.

[Top]
#### Adding the Capture Toolbar
    
    
    void CAAPrtDialog::CaptureCB(CATCommand           * iSendingCommand,
                                  CATNotification      * iSentNotification,
                                  CATCommandClientData   iUsefulData)
    {
      CATPrintCaptureDialog * capture = new **CATPrintCaptureDialog**(this, "Capture", _viewer);
      capture->**SetVisibility**(CATDlgShow);
    }  
  
---  
  
The Capture toolbar constructor has the following parameters: 

  * `this` is the toolbar parent set as the application window
  * `"Capture"` is the toolbar identifier, unused here
  * `_viewer` is the application viewer. This object along with is contents will be captured.

The `SetVisibility` method displays the dialog box. The Capture toolbar manages its deallocation itself.

[Top]
#### Adding the Album Dialog Box

The file conversion to a 2D representation can now take place.
    
    
    void CAAPrtDialog::AlbumCB(CATCommand           * iSendingCommand,
                                CATNotification      * iSentNotification,
                                CATCommandClientData   iUsefulData)
    {
      _// Instantiates the Album dialog box_
      CATPrintAlbumDialog *album = new **CATPrintAlbumDialog**(this, "Album");
    
      album->SetVisibility(CATDlgShow); _// Shows the Album dialog box_
    }  
  
---  
  
The Album dialog box constructor has the following parameters: 

  * `this` is the dialog box parent set as the application window
  * `"Album"` is the dialog box identifier, unused here.

The `SetVisibility` method displays the dialog box. The Album dialog box manages its deallocation itself.

[Top]
#### Adding the Printer Manager Dialog Box
    
    
    void CAAPrtDialog::PrinterManagerCB(CATCommandCATCommand * iSendingCommand,
                                         CATNotification      * iSentNotification,
                                         CATCommandClientData   iUsefulData)
    {
      _// Instantiates the Printer Manager dialog boxcommand_ 
      CATPrinterManagerDialog *printMan = new **CATPrinterManagerDialog**(this, 
                                                  "PrintMan", CATDlgWndModal);
    
      printMan->**SetVisibility**(CATDlgShow); _// Shows the Printer Manager dialog box_
    }  
  
---  
  
The Printer Manager dialog box constructor has the following parameters: 

  * `this` is the dialog box parent set as the application window
  * `"PrinMan"` is the dialog box identifier, unused here
  * `CATDlgWndModal` is the dialog box style. Modal means that no interaction outsisde the dialog box is possible as long as it is displayed.

The `SetVisibility` method displays the dialog box. The Printer Manager dialog box manages its deallocation itself.

[Top]

* * *
### In Short

This use case shows how to add the Print dialog boxes and toolbars to your application. They include the Print dialog box to print the contents of a viewer, the Capture toolbar to make a snapshot of a viewer in an image file stored in the album, the Album toolbar to manage the album, and the Printer Manager to set up the printer.

[Top]

* * *
### References

[1] | [Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
Version: **2** [Nov 2003] | Document updated  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
