---
title: "Displaying cgr Files"
category: "use-case case"
module: "CAAVisUseCases"
tags: "["CAAVisBaseView", "CAAVisBaseCGRDocument", "CAAVisBaseDocument", "CAAVisBasics", "CAAVisBaseApplication", "CAAVisualization"]"
source_file: "Doc/online/CAAVisUseCases/CAAVisSampleDisplayCgr.htm"
converted: "2026-05-11T17:31:52.093625"
---
# 3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Displaying cgr Files

_Opening a cgr file and displaying it in a viewer_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAVisBasics use case. This use case explains how to open a cgr file and to display it in a viewer.

  * **What You Will Learn With This Use Case**
  * **The CAAVisBasics Use Case**
    * What Does CAAVisBasics Do
    * How to Launch CAAVisBasics
    * Where to Find the CAAVisBasics Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to open a cgr file read from the disk and to display it in a 3D navigation viewer.

[Top]
### The CAAVisBasics Use Case

CAAVisBasics is a set of use cases of the CAAVisualization.edu framework that illustrates Vizualization framework capabilities.

[Top]
#### What Does CAAVisBasics Do

CAAVisBasics is a set of use cases of the CAAVisualization.edu framework that illustrates Vizualization framework capabilities.
CAAVisBasics is an MDI interactive application that displays viewers in its document windows. One of these viewers is dedicated to display a cgr file selected using the File Open command in the file selection box. This article focuses on the way this cgr file is displayed.

The cubes.cgr file is selected and read from disk and displayed in a 3D navigation viewer.

![](images/CAAVisSampleCGRFile.jpg)

[Top]
#### How to Launch CAAVisBasics

To launch CAAVisBasics, you will need to set up the build time environment, then compile CAAVisBasics along with its prerequisites, set up the run time environment, and then execute the sample [1]. When you have launched CAAVisBasics, the following is displayed.

![](images/CAAVisSampleCGRFile1.jpg)

Then point **File** , and click **Open**. In the **Select a CGR File** dialog box, select the resources/cgr directory in the run time view, and click the **CUBES.cgr** file that displays the cgr file with the cubes.

[Top]
#### Where to Find the CAAVisBasics Code

Then point **File** , and click **Open**. In the **Select a CGR File** dialog box, select the resources/cgr directory in the run time view, and click the **CUBES.cgr** file that displays the cgr file with the cubes.
CAAVisBasics code is located in the CAAVisBasics.m use case module of the CAAVisualization.edu framework:

Windows | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m`

CAAVisBasics code is located in the CAAVisBasics.m use case module of the CAAVisualization.edu framework:
Windows | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m`
Unix | `InstallRootDirectory/CAAVisualization.edu/CAAVisBasics.m`

where `InstallRootDirectory` is the root directory of your CAA V5 installation.

CAAVisBasics includes the following files:

**LocalInterfaces directory**
---
CAAVisBasics includes the following files:
CAAVisBaseApplication.h | Header file for the interactive application that hosts the viewer
CAAVisBaseCGRDocument.h | Header file for the document that displays a cgr file
CAAVisBaseDocument.h | Header file for the document base class
CAAVisBaseView.h | Header file for the document window containing a viewer to display the document

**src directory**
CAAVisBaseApplication.h | Header file for the interactive application that hosts the viewer
CAAVisBaseCGRDocument.h | Header file for the document that displays a cgr file
CAAVisBaseDocument.h | Header file for the document base class
CAAVisBaseView.h | Header file for the document window containing a viewer to display the document
CAAVisBaseApplication.cpp | Source file for the interactive application that hosts the viewer
CAAVisBaseCGRDocument.cpp | Source file for the document that displays a cgr file
CAAVisBaseDocument.cpp | Source file for the document base class
CAAVisBaseView.cpp | Source file for the document window containing a viewer to display the document

[Top]
### Step-by-Step

To open and display a cgr file in a 3D viewer, there are three main steps:
# | Step | Where
---|---|---
To open and display a cgr file in a 3D viewer, there are three main steps:
1 | Create a 3D navigation viewer instance | `CAAVisBaseView::CreateViewer` method
2 | Create a 3D representation bag from the selected cgr file | `CAAVisBaseCGRDocument::CreateModel` method
3 | Display the representation in the viewer | `CAAVisBaseDocument::AddRepToViewer` method

The preliminary tasks that consist in creating the application and its main window with menus and commands, displaying the file selection box, retrieving the input file name from the file selected, and checking that its a cgr file, are not described. The input file name is a data member of _CAAVisBaseCGRDocument_ class.

[Top]
#### Creating a 3D Navigation Viewer Instance

The 3D navigation viewer is an instance of the _CATNavigation3DViewer_ class. It is created in the `CreateViewer` method of the _CAAVisBaseView_ class that is called when the application is launched.

    void CAAVisBaseView::CreateViewer(#)

    {
The 3D navigation viewer is an instance of the _CATNavigation3DViewer_ class. It is created in the `CreateViewer` method of the _CAAVisBaseView_ class that is called when the application is launched.
void CAAVisBaseView::CreateViewer(#)
      _pViewer = new CATNavigation3DViewer(this, "3DViewer",
                                          CATDlgFraNoTitle | CATDlgFraNoFrame,
                                          500, 500);
      Attach4Sides(_pViewer);

    }

---

The `_pViewer` pointer to the 3D navigation viewer is kept as a data member of the _CAAVisBaseView_ class. Its parameter are:

`this` | The viewer parent in the dialog containment tree structure and in the command tree structure [2]
---|---
`3DViewer` | The viewer identifier
`CATDlgFraNoTitle` | The viewer has no title [3]
`CATDlgFraNoFrame` | The viewer frame is not displayed [3]
`500, 500` | The viewer width and height expressed in pixels

The `Attach4Sides` method attaches the four sides of the viewer to those of the window. This makes the viewer occupy the whole window space.

[Top]
#### Creating a 3D Representation Bag from the Selected cgr File

The _CAAVisBaseCGRDocument_ constructor stores the cgr file name as a data member, and calls methods to create the representation and to display it in the viewer.

    CAAVisBaseCGRDocument::CAAVisBaseCGRDocument(const char * fileName,
                                                 CATCommand * iParent,
                                                 CATDialog  * iDialogParent,
                                                 CATString  * iDocumentName)

                         : CAAVisBaseDocument(iParent, iDialogParent, iDocumentName)
    {
CATCommand * iParent,
CATDialog  * iDialogParent,
CATString  * iDocumentName)
      _pFileToOpen = (char *)malloc((strlen(fileName)+1)*sizeof(char));
```vbscript
      memset(_pFileToOpen, 0, strlen(fileName)+1);
      strcpy(_pFileToOpen, fileName);

      CreateModel(#);

      AddRepToViewer(#);

```

    }

---

The representation bag is created thanks to the `CreateModel` method.

    void CAAVisBaseCGRDocument::CreateModel(#)

    {
The representation bag is created thanks to the `CreateModel` method.
void CAAVisBaseCGRDocument::CreateModel(#)
      _pRootContainer = new CAT3DBagRep;

      //Reading of the CGR file. The rep issued from this reading
      //is added as a children of _pRootContainer
void CAAVisBaseCGRDocument::CreateModel(#)
_pRootContainer = new CAT3DBagRep;
      CAT3DBagRep * cgr = (CAT3DBagRep *)::**CATReadCgr**((char *) _pFileToOpen,
                                                      USE_LODS_TEXTURE_EDGE);
      if(cgr)

      {
CAT3DBagRep * cgr = (CAT3DBagRep *)::**CATReadCgr**((char *) _pFileToOpen,
USE_LODS_TEXTURE_EDGE);
if(cgr)
        _pRootContainer->AddChild(*cgr);

      }
    }

---

This representation is created as a _CAT3DBagRep_ , since the cgr file may need several representations to accomodate its data. The global function `CATReadCgr` takes the name of the cgr file as parameter. The second parameter is useless, and must always be set to `USE_LODS_TEXTURE_EDGE`.

[Top]
#### Displaying the Representation in the Viewer

The `AddRepToViewer` method displays the created representation.

    void CAAVisBaseDocument::AddRepToViewer(#)

    {
The `AddRepToViewer` method displays the created representation.
void CAAVisBaseDocument::AddRepToViewer(#)
      _pView->Add3DRep(_pRootContainer);

    }

---

`_pView` is a pointer to the 3D navigation viewer. The representation is assigned to this viewer thanks to the `Add3DRep` method.

[Top]

* * *
### In Short

This use case shows the objects involved when displaying a cgr file, namely the 3D navigation viewer that displays the cgr file and the 3D representation bag into which the cgr file is put to be passed to the viewer.

[Top]

* * *
### References

[1] | [Building and Launching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Creating Dialog Objects](../CAADlgTechArticles/CAADlgCreatingDialogs.md)
[3] | [Frame](../CAADlgQuickRefs/CAADlgCATDlgFrame.md)
[Top]

* * *
### History

Version: **1** [Feb 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
