---
title: "Creating Annotations on View Components"
category: "use case"
module: "CAADriUseCases"
tags: ["CATIDrwAnnotationFactory_var", "CATISheet_var", "CATIDftTextProperties", "CATIDftText", "CATIDrwAnnotationFactory", "CATIDftDocumentServices", "CAADrwCoordinates", "CATIA", "CATI2DPoint_var", "CATIDrawing", "CATI2DPoint", "CATIView_var", "CAADRWCoordinates", "CATIDescendants_var", "CATIView", "CATIDrwSubString", "CATIDescendants", "CAADraftingInterfaces", "CATIDrwTextProperties", "CATISheet"]
source_file: "Doc/online/CAADriUseCases/CAADriCoordinates.htm"
converted: "2026-05-11T17:31:50.944012"
---
# Mechanical Design

| 
## Drafting

| 
### Creating Annotations on View Components

_How to retrieve view components_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAADrwCoordinates use case. This use case explains how to retrieve the view components.

  * **What You Will Learn With This Use Case**
  * **The CAADrwCoordinates Use Case**
    * What Does CAADrwCoordinates Do
    * How to Launch CAADrwCoordinates
    * Where to Find the CAADrwCoordinates Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
### What You Will Learn With This Use Case

This use case is intended to retrieve the view components. These components can be :

  * Geometry
  * Annotations
  * Generative results.

[Top]
### The CAADrwCoordinates Use Case

CAADrwCoordinates is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCoordinates Do

Fig. 1 The Document Before Running CAADrwCoordinates ![](images/CAADrwCoordinates1.jpg)  
---  
  
Fig. 1 represents a CATDrawing document containing 2D points.

Fig. 2 The Document After Running CAADrwCoordinates ![](images/CAADrwCoordinates2.jpg)  
---  
  
Fig. 2 represents the previous CATDrawing after CAADrwCoordinates processing.  
A text has been created near each point. This text is formatted like follows :

_Point _point index_  
_X = _the x point coordinate  
_Y = _the y point coordinate_

[Top]
#### How to Launch CAADrwCoordinates

To launch CAADrwCoordinates, you will need to set up the build time environment, then compile CAADrwCoordinates along with its prerequisites, set up the run time environment, and then execute the use case [1].

The CATDrawing document Fig. 1 is saved in the Framework CAADraftingInterfaces.edu/Cnext/Resources/graphic/CAADrwCoordinates.CATDrawing. 

When you launch the use case, pass the full pathname of the file into which you you want to store the created document as argument: for example Result.CATDrawing. 

  * With Windows 
        
        e:> CAADrwCoordinates CAADrwCoordinates.CATDrawing Result.CATDrawing  
  
---  
  * With UNIX 
        
        $ CAADrwCoordinates /u/users/CAADrwCoordinates.CATDrawing Result.CATDrawing  
  
---  

[Top]
#### Where to Find the CAADrwCoordinates Code

The CAADrwCoordinates use case is made of a single source file named CAADrwCoordinates.cpp located in the CAADrwCoordinates.m module of the CAADraftingInterfaces.edu framework:

Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCoordinates.m\`  
---|---  
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCoordinates.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are six steps in CAADRWCoordinates:

  1. Reading the Document
  2. Accessing the Drawing in the Document
  3. Navigating through the Drawing and Sheet to Get the Active View
  4. Getting the View Points
  5. Scanning Points and Creating Texts
  6. Saving the Document and Exiting

[Top]
#### Reading the Document
    
    
    int main(int    iArgc,   // Number of arguments (1) 
             char** iArgv)   // Path to the *.CATDrawing document
    {
       // Check arguments
       if(2 != iArgc) return 1;
       const char *fileName = iArgv[1];
       
    
       // READ THE DRAWING DOCUMENT
       // =========================
    
       // creates a session
       **CATSession** *pSampleSession = NULL;
       HRESULT hr = **::Create_Session**("SampleSession",pSampleSession);
       if (FAILED(hr)) return 1;
    
       // read the document
       **CATDocument** * pDoc = NULL;
       if (!SUCCEEDED(**CATDocumentServices::OpenDocument**(fileName, pDoc)))
       {
          // Ends session
          ::Delete_Session("SampleSession");
          return 2;
       }
    ...  
  
---  
  
This section represents the usual sequence for reading a CATIA document [2].

[Top]
#### Accessing the Drawing in the Document
    
    
    ...
       // Gets the drawing feature using the CATIDftDocumentServices interface
       **CATIDrawing** *piDrawing = NULL;
       **CATIDftDocumentServices** *piDftDocServices = NULL;
       if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
       {
          piDftDocServices->**GetDrawing**(IID_CATIDrawing, (void **)&piDrawing);
          piDftDocServices->Release();
       }
    
       if (NULL == piDrawing)
          return 3;
    ...  
  
---  
  
The root feature of a drawing document is the Drawing, that is, the feature that implements the _CATIDrawing_ interface. We can get a pointer to _CATIDrawing_ using the _CATIDftDocumentServices_ interface, which is implemented by the document. The `GetDrawing` method first argument is the _CATIDrawing_ interface IID.

[Top]
#### Navigating through the Drawing and Sheet to Get the Active View
    
    
    ...
       // We can get the current sheet
       **CATISheet** _var spSheet = piDrawing->**GetCurrentSheet**();
       // And the sheet current view
       **CATIView** _var spCurrentView = spSheet->**GetCurrentView**();
    
       // Memory cleaning
       piDrawing->Release();
    ...  
  
---  
  
A drawing may contain several sheets, but only one is the current one. The current sheet is the sheet containing the active view, that is the view currently edited. The methods of the _CATISheet_ and _CATIView_ interfaces do return handlers, so we do not need to care about releasing them. The drawing variable is a pointer to _CATIDrawing_ , so we have to release it when it is no longer used.

[Top]
#### Getting the View Points
    
    
    ...
       // Now we do seek all the points in the view
       **CATIDescendants** _var spDesc = spCurrentView;
       CATListValCATISpecObject_var pointList;
       spDesc->**GetDirectChildren** ("CATI2DPoint",pointList);
    ...  
  
---  
  
The view geometry can be retrieved using the _CATIDescendants_ interface. The first argument of the _GetDirectChildren_ method is a scan filter. In this example, we only get points.

[Top]
#### Scanning Points and Creating Texts
    
    
    ...
     // loop on points
     for (int ii=1; ii<=pointList.Size(); ii++)
     {
       // Gets the coordinates
       CATI2DPoint_var spPoint = pointList[ii];
       double coord[2];
       spPoint->GetPointData(coord);
       // Compute the string
       CATUnicodeString textString("Point ");
       CATUnicodeString index;
       index.BuildFromNum(ii);
       textString += index;
       int titleLength = textString.GetLengthInChar();
       textString.Append("\n");
       textString.Append("X = ");
       CATUnicodeString coordText[2];
       coordText[0].BuildFromNum(coord[0]);
       textString.Append(coordText[0]);
       textString.Append("\n");
       textString.Append("Y = ");
       coordText[1].BuildFromNum(coord[1]);
       textString.Append(coordText[1]);
    
       // Creates the Text
       CATIDrwAnnotationFactory_var spAnnFactory = spCurrentView;
       CATIDftText *piDftText = NULL;
       const double txtpos[2] = {coord[0]+10.0,coord[1]+10.0};
       if (SUCCEEDED(spAnnFactory->CreateDftText(txtpos, &piDftText)))
       {
         wchar_t *ptxtChar = new wchar_t[textString.GetLengthInChar()+1];
         textString.ConvertToWChar(ptxtChar);
         piDftText->SetString(ptxtChar);
         delete [] ptxtChar;
         ptxtChar = NULL; 
         CATIDrwSubString *piDrwSubString = NULL;
         if (SUCCEEDED(piDftText->QueryInterface(IID_CATIDrwSubString,(void **)&piDrwSubString)))
         {
           // Select the sub string to modifiable.
           piDrwSubString->SetSelection(1,8);
    
           // Modify the properties
           CATIDftTextProperties *piTextProp = NULL;
           if (SUCCEEDED(piDftText->GetTextProperties(&piTextProp)))
           {
             piTextProp->SetBold(TRUE);
             piTextProp->SetUnderline(TRUE);
             piTextProp->Release();piTextProp=NULL;
           }
           piDrwSubString->Release();piDrwSubString=NULL;
         }
         piDftText->Release();piDftText=NULL;
       }
      }
    
    ...  
  
---  
  
We loop on the points and get the coordinates using _CATI2DPoint::GetPointData_. The text string is computed using _CATUnicodeString_ operators.  
The _CATIDrwAnnotationFactory_ annotation factory is implemented by the view and so the coordinates passed in `CreateDrwText` are view coordinates. The _CATIDrwTextProperties_ interface allows text property modifications, such as setting the text with a bold typeface using the `SetBold` method.

[Top]
#### Saving the Document and Exiting
    
    
    ...
       // Save the result
       hr = CATDocumentServices::SaveAs(*pDoc, (char *)fileNameOut);
       if (FAILED(hr)) return 4;
    
    
       // Ends session and drops document	
       CATDocumentServices::Remove (*pDoc);
       ::Delete_Session("SampleSession");
    
    
       return 0;
    }  
  
---  
  
This section represents the usual sequence for saving a CATIA document [2].

[Top]

* * *
### In Short

This use case shows how to get the view components. The view implements the _CATIDescendants_ interface and the components can be retrieved by using the _GetDirectChildren_ method.

This use case shows also how to open a CATDrawing document, get the root feature which implements the _CATIDrawing_ interface. A pointer to this interface is the key to enter and navigate inside the drawing structure, and can be retrieved using the `GetDrawing` method of the _CATIDftDocumentServices_ interface implemented by the document. Retrieving the active view is performed first by retrieving the current sheet thanks to the `GetCurrentSheet` method of the _CATIDrawing_ interface, and then asking the current sheet for the current view using the `GetCurrentView` of _CATISheet_. This current view is scanned using the _GetDirectChildren_ method of _CATIDescendants_.  
The view also implements the _CATIDrwAnnotationFactory_ interface and the texts are created using its `CreateDrwText` method, and set with a bold typeface using the `SetBold` method.

[Top]

* * *
### References

[1] | [Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Creating a New Document](../CAAOmbUseCases/CAAOmbNewDoc.md)  
[Top]  
  
* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
