---
title: "Opening and Displaying an Image File"
category: "use-case case"
module: "CAAPrtUseCases"
tags: "["CAAPrtApplication", "CAAPrtWheatField", "CAAPrtDialog", "CAAPrint"]"
source_file: "Doc/online/CAAPrtUseCases/CAAPrtSampleOpenAndDisplay.htm"
converted: "2026-05-11T17:17:56.117863"
---
# 3D PLM Enterprise Architecture

|
## 3D Visualization - Print

|
### Opening and Displaying an Image File

_Reading a TIFF file to display it in a viewer_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAPrtApplication use case. This use case explains how to open an image file and display it in a viewer.

  * **What You Will Learn With This Use Case**
  * **The CAAPrtApplication Use Case**
    * What Does CAAPrtApplication Do
    * How to Launch CAAPrtApplication
    * Where to Find the CAAPrtApplication Code
  * **Step-by-Step**
  * **In Short**
  * **References**

****
---

* * *
### What You Will Learn With This Use Case

This use case is intended to open an image file read from the disk and to display it in a viewer. To do this, you'll learn how to create a print file image from the image file, print parameters, a 2D print representation from the print file image, and how to display this representation in a viewer.

[Top]
### The CAAPrtApplication Use Case

CAAPrtApplication is a set of use cases of the CAAPrint.edu framework that illustrates Print framework capabilities.

[Top]
#### What Does CAAPrtApplication Do

CAAPrtApplication is a set of use cases of the CAAPrint.edu framework that illustrates Print framework capabilities.
This use case shows several capabilities of the Print framework. Each command of CAAPrtApplication is described below.

File | Open | Opening a TIFF file

This use case shows several capabilities of the Print framework. Each command of CAAPrtApplication is described below.
File | Open | Opening a TIFF file
Print | Printing the image displayed in the viewer
Capture | Making a screen shot of the image displayed in the viewer
Album | Managing the image album
Printer Setup | Managing printer setup parameters
Printable Objects | Display a test image | Displaying a supplied sample TIFF file
Print a test image | Printing a supplied sample JPEG file
Print a label | Typing a text in a window and printing it with a frame

This article describes what happens when the application is launched with the pathname of a TIFF file as parameter, which is equivalent to File Open. It displays a file selection box to select the TIFF file, and selecting the file displays it in the application viewer.

_Figure 1: The CAAPrtWheatField.tif File_ ![](images/CAASampleTIFFImage.gif)

---

[Top]
#### How to Launch CAAPrtApplication

To launch CAAPrtApplication, you will need to set up the build time environment, then compile CAAPrtApplication along with its prerequisites, set up the run time environment, and then execute the use case [1].

You can launch CAAPrtApplication using a TIFF file as argument.

  * With Windows

        E:>CAAPrtApplication InstallRootDirectory/CAAPrint.edu/CNext/resources/graphic/images/CAAPrtWheatField.tif

---
  * With UNIX

        $ CAAPrtApplication InstallRootDirectory/CAAPrint.edu/CNext/resources/graphic/images/CAAPrtWheatField.tif

---

where:

  * `InstallRootDirectory` is the directory into which the CAA CD-ROM were unloaded
  * `CAAPrtWheatField.tif` is the sample TIFF file supplied and shown in Figure 1. You can use other TIFF files you may have at hand.

[Top]
#### Where to Find the CAAPrtApplication Code

The CAAPrtApplication use case is made of an application class and of a window class whose header and source files are located in the CAAPrtApplication.m module of the CAAPrint.edu framework:

Windows | `InstallRootDirectory/CAAPrint.edu/CAAPrtApplication.m`

The CAAPrtApplication use case is made of an application class and of a window class whose header and source files are located in the CAAPrtApplication.m module of the CAAPrint.edu framework:
Windows | `InstallRootDirectory/CAAPrint.edu/CAAPrtApplication.m`
Unix | `InstallRootDirectory/CAAPrint.edu/CAAPrtApplication.m`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

CAAPrtApplication includes the following files:

**LocalInterfaces directory**
---
CAAPrtApplication includes the following files:
CAAPrtApplication.h | Header file for the interactive application
CAAPrtDialog.h | Header file for the dialog window that hosts the viewer

**src directory**
CAAPrtApplication.h | Header file for the interactive application
CAAPrtDialog.h | Header file for the dialog window that hosts the viewer
CAAPrtApplication.cpp | Source file for the interactive application
CAAPrtDialog.cpp | Source file for the dialog window that hosts the viewer

This article explains the `DisplayImage` method located in the CAAPrtDialog.cpp file.

[Top]
### Step-by-Step

This article explains the `DisplayImage` method located in the CAAPrtDialog.cpp file.
To display a TIFF image file in a 2D viewer, there are four main steps:

  1. Creating a Print File Image from the Selected File
  2. Defining Print Parameters
  3. Creating a 2D Representation from the Image
  4. Displaying the Created 2D Representation

The preliminary tasks that consist in either retrieving the input file name passed as the command argument or creating and displaying the file selection box, retrieving the input file name from the file selected, and checking that its a TIFF file not described. The input file name is passed to the `DisplayImage` method in the `IPath` argument, such as TestFile.tif. The viewer is accessed as a data member of the dialog window class using the `_pViewer` pointer, and the representation created is kept in the `_pRep` data member.

The `DisplayImage` method reads the TIFF file, creates a 2D representation, and displays this representation in the 2D viewer of the application.

[Top]
#### Creating a Print File Image from the Input File

    void CAAPrtDialog::DisplayImage(const char* iPath)
    {
      CATPrintFileImage *pImage = new **CATPrintFileImage**(iPath, "TIFF");
      ...

---

This print file image is an instance of the _CATPrintFileImage_ class instantiated from the input file. The input file format is passed as the second argument, here TIFF. The print file image created holds the input file in memory and the TIFF interpreter to enable the file interpretation as soon as this will be asked.

[Top]
#### Defining Print Parameters

A print parameter object should be defined to be associated with the print file image.

      ...
      **CATPrintParameters** Parameters;
      ...

---

The print parameters are taken into account to create the printed output. No specific value is reset, so all the print parameters take their default values.

[Top]
#### Creating a 2D Representation from the Image

The file conversion to a 2D representation can now take place.

      ...
The file conversion to a 2D representation can now take place.
      CAT2DRep * pRep = NULL;
```cpp
      pRep = new **CATPrint2DRep**(pImage, Parameters);

```

      pImage->**Release**(#);

      ...

---

The _CATPrint2DRep_ is a specific 2D representation built from a print file image and a set of print parameters. The print file image is now useless and can be released.

[Top]
#### Displaying the Created 2D Representation

      ...
      if (pRep)
      {
```vbscript
if (pRep)
```vbscript
        if (_pRep)                    _// If there is a previous representation displayed_
```

```

        {
```vbscript
if (pRep)
```vbscript
if (_pRep)                    _// If there is a previous representation displayed_
```

          _pViewer->**RemoveRep**(_pRep); _// Removes it from the viewer_
          _pRep->**Destroy**(#);           _// Releases it_
```

        }

_pViewer->**RemoveRep**(_pRep); _// Removes it from the viewer_
_pRep->**Destroy**(#);           _// Releases it_
        _pViewer->**AddRep**(pRep);       _// Adds the representation to the viewer_
        _pViewer->**Reframe**(#);          _// Redraws the viewer contents_

```vbscript
        _pRep = pRep;      _// Keeps the new representation for future use (printing, etc.)_

```

      }
    }

---

```vbscript
If the 2D representation is successfully created, it can be displayed. The possible displayed representation is first removed from the viewer and released, and the new created representtaion is added to the viewer that is then asked to redraw itself. This representation is kept as a data member for a future use, such as printing, or capturing it in the album.

```

[Top]

* * *
### In Short

This use case shows the objects involved when displaying an image file, here encoded using TIFF, in a 2D viewer. These objects are the print file image, the set of print parameters, the 2D representation into which the image is converted, and the 2D viewer that displays it.

First, a _CATPrintFileImage_ instance is created using the input file, and a _CATPrintParameters_ instance is created. Then a _CATPrint2DRep_ instance is created using print file image and the print parameters. Finally, this representation is passed to the 2D viewer for display.

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
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
