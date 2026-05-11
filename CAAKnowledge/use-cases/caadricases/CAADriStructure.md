---
title: "Creating Sheets and Views in a CATDrawing Document"
category: "use case"
module: "CAADriUseCases"
tags: ["CATIDftStandardManager", "CATIDftDrawing", "CATIDftDrawingFormat", "CATIDftDocumentServices", "CATIContainer_var", "CATIA", "CATIDftViewMakeUp", "CAADrwStructure", "CATIDrawing", "CATIStringList", "CATIDftView", "CATIDftSheetFormat", "CATIDrwFactory", "CATIUnknownList", "CATISpecObject_var", "CATIView", "CATISpecObject", "CATI2DWFFactory_var", "CATIDftFormat_var", "CAADraftingInterfaces"]
source_file: "Doc\online\CAADriUseCases\CAADriStructure.htm"
converted: "2026-05-11T17:31:51.020431"
---

# Mechanical Design

| 

## Drafting

| 

### Creating Sheets and Views in a CATDrawing Document

_How to structure a CATDrawing document_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article discusses the CAADrwStructure use case. This use case explains how to create sheets and interactive views in a drawing document.

  * **What You Will Learn With This Use Case**
  * **The CAADrwStructure Use Case**
    * What Does CAADrwStructure Do
    * How to Launch CAADrwStructure
    * Where to Find the CAADrwStructure Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *

### What You Will Learn With This Use Case

In this use case you will learn how to deal with the structure of a drawing document. Thus you will be able to create sheets and interactive views.

[Top]

### The CAADrwStructure Use Case

CAADrwStructure is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]

#### What Does CAADrwStructure Do

  Fig. 1: The Document Created by the Use Case   
---  
![](images/CAADrwStructure1.jpg)  
  
This picture represents a CATDrawing document created by the use case program. The program first creates a basic drafting structure composed of a drawing, a sheet and two views (these views are not displayed in the graph). Then the second sheet is created with an additional view.

**Remark** : A sheet always contains: 

  * A main view which contains the elements directly created in the sheet
  * A background view, which is dedicated to the frames and title blocks.



These two views are created by the sheet factory. They are part of the sheet and so they cannot be deleted and they are not showed in the graph.

[Top]

#### How to Launch CAADrwStructure

To launch CAADrwStructure, you will need to set up the build time environment, then compile CAADrwStructure along with its prerequisites, set up the run time environment, and then execute the use case [1].

When you launch the use case, pass the full pathname of the file into which you you want to store the created document as argument. 

  * With Windows 
        
        e:> CAADrwStructure DrawingTest.CATDrawing  
  
---  
  * With UNIX 
        
        $ CAADrwStructure /u/users/DrawingTest.CATDrawing  
  
---  



[Top]

#### Where to Find the CAADrwStructure Code

The CAADrwStructure use case is made of a single source file named CAADrwStructure.cpp located in the CAADrwStructure.m module of the CAADraftingInterfaces.edu framework:

Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwStructure.m\`  
---|---  
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwStructure.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

There are five steps in CAADrwStructure:

  1. Creating and Initializing the document
  2. Accessing the drawing feature and drawing container  in the document 
  3. Creating standard in the drawing document 
  4. Appending format to the current sheet in the drawing document 
  5. Creating an Additional Sheet and Adding it to the drawing feature
  6. Creating a view and adding it to the just created sheet
  7. Creating a geometric element in this view
  8. Saving the document and exiting



[Top]

#### Creating and Initializing the Document
    
    
    int main(int    iArgc,   // Number of arguments (1) 
             char** iArgv)   // Path to the new *.CATDrawing document
    {
      // Check arguments
      if(2 != iArgc) return 1;
      const char *fileName = iArgv[1];
    
      // DRAWING DOCUMENT CREATION
      // =========================
    
      // creates a session
      CATSession *pSampleSession = NULL;
      HRESULT hr = **::Create_Session**("SampleSession",pSampleSession);
      if (FAILED(hr)) return 1;
    
      CATDocument* pDoc = NULL;
      hr = **CATDocumentServices::New**("CATDrawing", pDoc);
      if (FAILED(hr)) return 2;
    ...  
  
---  
  
This section represents the usual sequence for creating a CATIA document.

[Top]

#### Accessing the drawing feature and drawing container in the document
    
    
     ...
    
    
    // Gets the drawing feature.
    CATIDftDrawing *piDftDrawing = NULL;
    CATIDftDocumentServices *piDftDocServices = NULL;
    CATIContainer_var spDrwCont;
    if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
    {
      if (SUCCEEDED(piDftDocServices->**GetDrawing**(IID_CATIDftDrawing, (void **)&piDftDrawing)))
      {
        if (piDftDrawing)
        {
          // Gets the drawing container.
          CATISpecObject *piSpecObj=NULL;
          if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piSpecObj)))
          {
            spDrwCont = piSpecObj->**GetFeatContainer**();
            piSpecObj->Release();
            piSpecObj=NULL;
          }
        }
      }
      piDftDocServices->Release();
      piDftDocServices=NULL;
    }
    ...
    
    
       
  
---  
  
The root feature of a drawing document is the Drawing that is the feature that implements the CATIDrawing interface. We can get a pointer to CATIDrawing using the CATIDftDocumentServices interface, which is implemented by the document. The GetDrawing method first argument is the interface you want to get on the drawing.

[Top]

####  

#### Creating drawing standard in the drawing document
    
    
    ...   
    // Gets standard manager from the drawing container.
    CATIDftStandardManager *piStdmgr = NULL;
    
    if (SUCCEEDED(spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr)))
    {
      // Find a standard in the list of allowed standards (ie. the list of xml files in the resources/standard/drafting directory)  
      CATIStringList *piListstd = NULL;
      if ( SUCCEEDED(piStdmgr->**GetAvailableStandards**(&piListstd)) && piListstd )
      {
        unsigned int nbrstd = 0;
        piListstd->Count(&nbrstd);
        for (unsigned int indice = 0; indice < nbrstd; indice ++)
        {
          wchar_t *wstd = NULL;
          if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) && wstd )
          {
     	const CATUnicodeString ANSI_UncS = "ANSI";
    	CATUnicodeString stdname;
    	stdname.BuildFromWChar(wstd);
    	if ( stdname == ANSI_UncS ) 
    	{
    	  // Import the ANSI standard in the document
              piStdmgr->**ImportStandard** (wstd);
              break;
            }
            delete[] wstd; wstd = NULL;
          }
        }
        piListstd->Release(); piListstd=NULL; 
      }
      piStdmgr->Release (); piStdmgr=NULL;
    }
    ...
         
    ---  
    
     
     
    
    CATIDftStandardManager interface is implemented on applicative container of 
     drawing application. GetAvailableStandards method returns the list of available 
     standards. ImportStandard method allows to apply a standard on the drawing 
     document. 
    
    
     
    
    [Top]
    
    
     
    
    #### Appending format to the current sheet in the drawing 
     drawing document
    
    
     
       
         
         
    
    
    ...   
     // Get available formats from drawing
    CATIDftDrawingFormats *piDftFormats = NULL;
    CATUnicodeString myFormatName;
    if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATIDftDrawingFormats,(void **)&piDftFormats)))
    {
      CATLISTV(CATISpecObject_var) spListFormat;
      if (SUCCEEDED(piDftFormats->**GetAvailableFormats**(spListFormat)))
      {
        int nbformats= spListFormat.Size();
        // Gets the first format in the list.
        if (nbformats >= 1)
        {
          CATIDftFormat_var spFormat = spListFormat[1];
          if (FAILED(spFormat->**GetFormatName**(myFormatName)))
          {
            // Memory clean.
            piDftFormats->Release();
            piDftFormats=NULL;
            piDftDrawing->Release();
            piDftDrawing=NULL;
            CATDocumentServices::Remove (*pDoc);
            ::Delete_Session("SampleSession");
            return 4;
          }
        }
      }
      piDftFormats->Release();
      piDftFormats=NULL;
    }
    
    // Adds the format to the current sheet.
    CATIUnknownList *piListOfSheet=NULL;
    CATIDftSheetFormat *piDftSheetFormat=NULL;
    if (SUCCEEDED(piDftDrawing->**GetSheets**(&piListOfSheet)))
    {
      IUnknown * item = NULL;
      unsigned int nbSheet = 0;
      piListOfSheet->Count(&nbSheet);
    
      // Loop on all Generated Geometry of the view.
      for(unsigned int i=0 ; i<nbSheet ; i++)
      {
        if( SUCCEEDED( piListOfSheet->Item(i, &item) ) )
        {
          if (item)
          {
            if (SUCCEEDED(item->QueryInterface (IID_CATIDftSheetFormat,(void **)&piDftSheetFormat)))
            {
              if (FAILED(piDftSheetFormat->**SetSheetFormat**(myFormatName)))
              {
                // Memory clean.
                item->Release();
                item=NULL;
                piDftSheetFormat->Release();
                piDftSheetFormat=NULL;
                piDftDrawing->Release();
                piDftDrawing=NULL;
                CATDocumentServices::Remove (*pDoc);
                ::Delete_Session("SampleSession");
                return 5;
              }
              piDftSheetFormat->Release();
              piDftSheetFormat=NULL;
            }
            item->Release();
            item=NULL;
          }
        }
      }
    }
    ...  
  
---  
  
CATIDftDrawingFormat interface is implemented on drawing root. GetAvailableFormats method returns the list of available formats. SetSheetFormat method initializes the format on the sheet. 

[Top]

 

#### Creating an Additional Sheet and Adding it to the Drawing Feature
    
    
    ...   
    CATIDftSheet *piDftNewSheet = NULL;
    wchar_t *pSheetName= L"MyNewSheet";
    if (SUCCEEDED(piDftDrawing->**AddSheet**(&piDftNewSheet,pSheetName)))
    ...  
  
---  
  
AddSheet method on CATIDftDrawing interface creates the sheet and add it to the drawing root. If this method is called in interactive context, sheet tab page will be updated.

[Top]

#### Creating a View and Adding it to the Just Created Sheet
    
    
    ...   
    // The drawing factory is implemented on the drawing container
    CATIDrwFactory_var spDrwFact = spDrwCont;
    
    // Create a view with Make Up
    CATIDftViewMakeUp *piNewViewMU = NULL;
    if (NULL_var != spDrwFact && SUCCEEDED(spDrwFact -> **CreateViewWithMakeUp**(IID_CATIDftViewMakeUp, (void **)&piNewViewMU)))
    {
      if (piNewViewMU)
      {
        // Get the view from the MakeUp
        CATIView *piNewView = NULL; 
        if (SUCCEEDED(piNewViewMU->**GetView**(&piNewView)))
        {
          if (piNewView)
          {
            // The view has to be typed: FrontView for Interactive view. 
            piNewView->**SetViewType**(FrontView);
            piNewViewMU->**SetAxisData**(100.0,50.0);
    
           // At last, add the view to the sheet
           if (piDftNewSheet) piDftNewSheet->**AddView**(piNewViewMU);
    ...  
  
---  
  
The CATIDrwFactory is implemented by the drawing container. A MakeUp object is associated to the view. So we create the two objects by using CreateViewWithMakeUp method.The view has to be typed and added to the sheet.

[Top]

#### Creating a Geometric Element in this View
    
    
    ...   
    // Activate this new view in the new sheet
    CATIDftView *piDftNewView=NULL;
    if (SUCCEEDED(piNewView->QueryInterface(IID_CATIDftView,(void **)&piDftNewView)))
    {
      piDftNewSheet->**SetDefaultActiveView**(piDftNewView);
      piDftNewView->Release();
      piDftNewView=NULL;
    }
    
    // Get the Wire frame factory to create geometry.
    CATI2DWFFactory_var spGeomFactory(piNewView);
    
    // Creation of a circle:
    double center[2];
    center[0]=50.0;
    center[1]=60.0;
    double radius = 50.0;
    CATISpecObject_var spCercle;
    if (NULL_var != spGeomFactory) 
    {
      spCercle = spGeomFactory->**CreateCircle**(center,radius);
    ...  
  
---  
  
To create geometric elements in a view, the view has to be current. Wire frame factory is obtained from the current view.

 

[Top]

#### Saving the Document and Exiting
    
    
    ...   
      // Save the result
      hr = **CATDocumentServices::SaveAs**(*pDoc, (char *)fileName);
      if (FAILED(hr)) return 6;
    
      // Ends session and drops document	
      **CATDocumentServices::Remove** (*pDoc);
      **::Delete_Session**("SampleSession");
    
      return 0;
    }  
  
---  
  
This section represents the usual sequence for saving a newly created CATIA document.

[Top]

* * *

### In Short

This use case shows the objects and interfaces used when creating sheets and views in a CATDrawing document. Sheets are created by using AddSheet method defined in CATIDftDrawing interface, thus sheet tab page may be updated in interactive context. View features are created by using CreateViewWithMakeUp defined in CATIDrwFactory interface implemented by the drawing container.

[Top]

* * *

### References

[1] |  [ Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
[2] |  [ Creating a New Document](../CAAOmbUseCases/CAAOmbNewDoc.htm)  
[Top]  
  
* * *

### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
