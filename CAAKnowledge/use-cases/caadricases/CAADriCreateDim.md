---
```vbscript
title: "Creating a Distance Dimension on Interactive Geometry"
category: "use case"
module: "CAADriUseCases"
tags: ["CATIDftStandardManager", "CATIDrwAnnotationFactory_var", "CATISheet_var", "CATIDrwAnnotationFactory", "CATIDftDocumentServices", "CATIDrwDimDimension", "CATIContainer_var", "CATIA", "CATIDrawing", "CATIStringList", "CATIView_var", "CAADrwCreateDimCmd", "CATIUnknownList", "CATISpecObject_var", "CAADrwCreateDim", "CATIUnknownListImpl", "CATI2DWFFactory_var", "CAADraftingInterfaces", "CAADRWCreateDim"]
source_file: "Doc/online/CAADriUseCases/CAADriCreateDim.htm"
converted: "2026-05-11T17:31:50.950000"
```

---
# Mechanical Design

|
## Drafting

|
### Creating a Distance Dimension on Interactive Geometry

_How to create a distance dimension between two 2D lines_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAADrwCreateDim.cpp use case. This use case explains how to edit a dimension dress-up.

  * **What You Will Learn With This Use Case**
  * **The CAADrwCreateDim Use Case**
    * What Does CAADrwCreateDim Do
    * How to Launch CAADrwCreateDimCmd
    * Where to Find the CAADrwCreateDim Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

In this use case you will learn how to create an associative dimension on two 2D lines.

[Top]
### The CAADrwCreateDim Use Case

CAADrwCreateDim is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCreateDim Do

CAADrwCreateDim is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.
This sample creates a dimension on two 2D lines in batch mode:

Fig. 2: The Model created by CAADrwCreateDim batch ![](images/CAADrwCreateDim1.jpg)

---

[Top]
#### How to Launch CAADrwCreateDim

To launch CAADrwCreateDim, you will need to set up the build time environment, then compile CAADrwCreateDim along with its prerequisites, set up the run time environment, and then execute the use case [1].

When you launch the use case, pass the full pathname of the file into which you you want to store the created document as argument: for example Result.CATDrawing.

  * With Windows  `e:> CAADrwCreateDim Result.CATDrawing`
---
  * With UNIX  `$ CAADrwCreateDim /u/users/Result.CATDrawing`
---

[Top]
#### Where to Find the CAADrwCreateDim Code

The CAADrwCreateDim use case is made of one source file named CAADrwCreateDim.cpp located in the CAADrwCreateDim.m module of the CAADraftingInterfaces.edu framework:

The CAADrwCreateDim use case is made of one source file named CAADrwCreateDim.cpp located in the CAADrwCreateDim.m module of the CAADraftingInterfaces.edu framework:
Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateDim.m\`

The CAADrwCreateDim use case is made of one source file named CAADrwCreateDim.cpp located in the CAADrwCreateDim.m module of the CAADraftingInterfaces.edu framework:
Windows | `InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateDim.m\`
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCreateDim.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are six steps in CAADRWCreateDim:

  1. Creating and Initializing the Document
  2. Accessing the Drawing in the Document
  3. Creating the Drawing Standard for Annotations
  4. Creating a Geometric Elements in the Main View
  5. Creating the distance dimension
  6. Saving the Document and Exiting

[Top]
#### Creating and Initializing the Document

    int main(int    iArgc,   // Number of arguments (1)
             char** iArgv)   // Path to the new *.CATDrawing document
    {
       // Check arguments
int main(int    iArgc,   // Number of arguments (1)
char** iArgv)   // Path to the new *.CATDrawing document
       if(2 != iArgc) return 1;
       const char *pfileNameOut = iArgv[1];

       // CREATE THE SESSION
       // ==================

       CATSession *pSampleSession = NULL;
       HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
```vbscript
       if (FAILED(hr)) return 1;

```

       // DRAWING DOCUMENT CREATION
       // =========================

       CATDocument* pDoc = NULL;
       hr = CATDocumentServices::New("CATDrawing", pDoc);
```vbscript
```vbscript
       if (FAILED(hr))

```

```

       {
          // Ends session
          ::Delete_Session("SampleSession");
hr = CATDocumentServices::New("CATDrawing", pDoc);
```vbscript
if (FAILED(hr))
```

          return 2;

       }
    ...

---

This section represents the usual sequence for creating a CATIA document.

[Top]
#### Accessing the Drawing in the Document

    ...
      // Gets the drawing feature using the CATIDftDocumentServices interface
       CATIDrawing *piDrawing = NULL;
       CATIDftDocumentServices *piDftDocServices = NULL;
       CATIContainer_var spDrwcont = NULL_var;
       CATISpecObject_var spSpecObj = NULL_var;
```vbscript
       if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))

```

       {
CATIDftDocumentServices *piDftDocServices = NULL;
CATIContainer_var spDrwcont = NULL_var;
CATISpecObject_var spSpecObj = NULL_var;
if (SUCCEEDED(pDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
          piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
          piDftDocServices->Release();
          spSpecObj=piDrawing;
```vbscript
          spDrwcont = spSpecObj->GetFeatContainer();

```

       }
piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
piDftDocServices->Release();
spSpecObj=piDrawing;
spDrwcont = spSpecObj->GetFeatContainer();
       else return 3;

    ...

---

The root feature of a drawing document is the Drawing that is the feature that implements the CATIDrawing interface. We can get a pointer to CATIDrawing using the CATIDftDocumentServices interface, which is implemented by the document. The GetDrawing method first argument is the interface you want to get on the drawing.

[Top]
#### Creating the Drawing Standard for Annotations

    ...
      if (!!spDrwcont)
       {
```vbscript
if (!!spDrwcont)
          CATIDftStandardManager *piStdmgr = NULL;
          HRESULT rc = spDrwcont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
          if (SUCCEEDED(rc))
```

          {
             //  Find a standard in the list of allowed standards (ie. the list of .CATDrwSTD files in the reffiles directory)
CATIDftStandardManager *piStdmgr = NULL;
HRESULT rc = spDrwcont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
if (SUCCEEDED(rc))
             CATIStringList *piListstd = NULL;
```vbscript
             if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) )

```

             {
CATIStringList *piListstd = NULL;
if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) )
                wchar_t  *wstd = NULL;
                unsigned int  nbrstd;
                piListstd->Count(&nbrstd);
                CATUnicodeString stdname;
                const CATUnicodeString ANSI_UncS = "ANSI";

```vbscript
                for (unsigned int indice = 0; indice < nbrstd; indice ++)

```

                {
const CATUnicodeString ANSI_UncS = "ANSI";
for (unsigned int indice = 0; indice < nbrstd; indice ++)
```vbscript
```vbscript
                   if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) )

```

```

                   {
```vbscript
for (unsigned int indice = 0; indice < nbrstd; indice ++)
```vbscript
if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) )
```

                      stdname.BuildFromWChar(wstd);

     		  if ( stdname == ANSI_UncS )
```

    		  {
                         // Import the ANSI standard in the document
```vbscript
if ( stdname == ANSI_UncS )
                         piStdmgr->ImportStandard (wstd);
                         break;
```

                      }
                   }
                }
piStdmgr->ImportStandard (wstd);
break;
                piListstd->Release();
                piListstd=NULL;

             }

piListstd->Release();
piListstd=NULL;
             piStdmgr->Release ();
             piStdmgr=NULL;

          }
       }
    ...

---

The reffiles directory is  accessible in runtime view.

[Top]
#### Creating the Geometric Elements in the Main View

    ...
     // We are working in main view of the current sheet
       CATISheet_var spSheet = piDrawing->GetCurrentSheet();
       piDrawing->Release();
       CATIView_var spMainView = spSheet->GetMainView();

       // GEOMETRY CREATION
       // =================
       // We now can create geometries in the main view after :
       //   - Setting the view as the current one
       //   - Getting the view geometry factory interface
       spSheet->SetCurrentView(spMainView);
spSheet->SetCurrentView(spMainView);
       CATI2DWFFactory_var spGeomFactory = spMainView;

       double X[2] = { 100.0, 200.0};
       double Z[2] ={ 50.0, 130.0};
       double startPoint[2], endPoint[2];

       // Creation of lines
double X[2] = { 100.0, 200.0};
double Z[2] ={ 50.0, 130.0};
double startPoint[2], endPoint[2];
       startPoint[0] = X[0];
       startPoint[1] = Z[0];
       endPoint[0] = X[1];
       endPoint[1] = Z[0];
       CATISpecObject_var spLine1 = spGeomFactory->CreateLine(startPoint, endPoint);

       startPoint[0] = X[0];
       startPoint[1] = Z[1];
       endPoint[0] = X[1];
       endPoint[1] = Z[1];
       CATISpecObject_var spLine2 = spGeomFactory->CreateLine(startPoint, endPoint);

    ...

---

To create geometric elements in a view, the view has to be current.

[Top]
#### Creating the Distance Dimension

    ...
       // Gets the view annotation factory
       CATIDrwAnnotationFactory_var spAnnFactory = spMainView;

       // Vertical distance dimension creation between Line1 and Line2
CATIDrwAnnotationFactory_var spAnnFactory = spMainView;
       CATDrwDimType dimType = DrwDimDistance;
       CATDimDefinition dimDef;
       CATIUnknownList * piSelectionsList =NULL;
       CATIUnknownListImpl * piListsel = new CATIUnknownListImpl();
       piListsel->QueryInterface(IID_CATIUnknownList, (void **) &piSelectionsList);
       piListsel->Release();
       piListsel=NULL;
       IUnknown * piLine1 = NULL;
       IUnknown * piLine2 = NULL;
       spLine1->QueryInterface(IID_IUnknown, (void **)&piLine1);
       spLine2->QueryInterface(IID_IUnknown, (void **)&piLine2);
       piSelectionsList->Add(0, piLine1);
       piSelectionsList->Add(1, piLine2);

       CATIDrwDimDimension * piDimHoriz = NULL;
       double pt1[2] = {10.0, 15.0};
       double  * pts[2];
       pts[0] = pt1;
       pts[1] = pt1+1;
       dimDef.Orientation = DrwDimAuto;
```vbscript
```vbscript
       hr = spAnnFactory->CreateDimension(piSelectionsList,pts,dimType,&dimDef,&piDimHoriz);

       if (piLine1) piLine1->Release();
       if (piLine2) piLine2->Release();
       if (piDimHoriz) piDimHoriz->Release();
       if (piSelectionsList) piSelectionsList->Release();

```

```

    ...

---

[Top]
#### Saving the Document and Exiting

    ...
      // Save the result
      CATDocumentServices::SaveAs(*pDoc, (char *)pfileNameOut);
       CATDocumentServices::Remove (*pDoc);
       //Ends session and drops document
       ::Delete_Session("SampleSession");

CATDocumentServices::SaveAs(*pDoc, (char *)pfileNameOut);
CATDocumentServices::Remove (*pDoc);
       return 0;

    }

---

This section represents the usual sequence for saving a newly created CATIA document.

[Top]

* * *
### In Short

This use case shows the objects and interfaces used when creating a dimension in a main view of a CATDrawing document. The Dimension is created using the _CATIDrwAnnotationFactory_ interface.

[Top]

* * *
### References

[1] | [Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] | [Creating a New Document](../CAAOmbUseCases/CAAOmbNewDoc.md)
[Top]

History

Version: **1** [Jan 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
