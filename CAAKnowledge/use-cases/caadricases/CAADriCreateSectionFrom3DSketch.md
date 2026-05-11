---
```vbscript
title: "Creating a Section View from a 3D Sketch"
category: "use case"
module: "CAADriUseCases"
tags: ["CATIDftStandardManager", "CATIPrtContainer", "CATIDftDrawing", "CATIDftDocumentServices", "CATIContainer_var", "CATIA", "CATI2DLine_var", "CATI2DWFGeometry_var", "CATIStringList", "CATIDftView", "CATIPrtPart_var", "CATIAlias", "CATInit_var", "CATI2DWFGeometry", "CATISpecObject_var", "CATISpecObject", "CATIDescendants", "CAADrwCreateSectionFrom3DSketch", "CAADrwCreatViewFrom3D", "CATIProduct"]
source_file: "Doc/online/CAADriUseCases/CAADriCreateSectionFrom3DSketch.htm"
converted: "2026-05-11T17:31:50.970014"
```

---
# Mechanical Design

|
## Drafting

|
### Creating a Section View from a 3D Sketch

_How to create a section view with the cutting profile associative to a 3D Sketch_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAADrwCreateSectionFrom3DSketch use case. This use case explains how to create a generative section view defined by a cutting profile associative to a 3D Sketch. Thus, if the 3D Sketch is modified, the section view will modified after update.

  * **What You Will Learn With This Use Case**
  * **The CAADrwCreateSectionFrom3DSketch Use Case**
    * What Does CAADrwCreateSectionFrom3DSketch Do
    * How to Launch  CAADrwCreateSectionFrom3DSketch
    * Where to Find the  AADrwCreateViewFrom3D Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to create a Drawing generative section view from a 3D Sketch.

_Fig 1: The part document containing the sketch "SketchForSection"_
---
![](images/CAADriCreateSectionFrom3DSketch1.jpg)

The SketchForSection sketch allows you to manage the cutting profile of the Drawing Section View from the 3D document.

[Top]
### The CAADrwCreateSectionFrom3DSketch Use Case

CAADrwCreateSectionFrom3DSketch is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCreateSectionFrom3DSketch Do?

  _Fig. 2: Drawing Document with the new Section view_
---
![](images/CAADriCreateSectionFrom3DSketch2.jpg)

[Top]
#### How to Launch CAADrwCreateSectionFrom3DSketch

To launch CAADrwCreateSectionFrom3DSketch, you will need to set up the build time environment, then compile CAADrwCreateSectionFrom3DSketch along with its prerequisites, set up the run time environment, and then execute the use case [1].

When you launch the use case, pass the full pathname of the Drawing file as argument. A Part file is delivery in the following path: CAADraftingInterfaces.edu\CNext\resources\graphic\PartWithPlaneAndSketchForSectionView.CATPart.

  * With Windows

When you launch the use case, pass the full pathname of the Drawing file as argument. A Part file is delivery in the following path: CAADraftingInterfaces.edu\CNext\resources\graphic\PartWithPlaneAndSketchForSectionView.CATPart.
        e:> mkrun -c cmd
        CAADrwCreateSectionFrom3DSketch c/.../PartWithPlaneAndSketchForSectionView.CATPart c/DrawingTestOutput.CATDrawing

---
  * With UNIX

        $ mkrun -c cmd
        CAADrwCreateSectionFrom3DSketch /u/users/.../PartWithPlaneAndSketchForSectionView.CATPart /u/users/DrawingTestOutput.CATDrawing

---

[Top]
#### Where to Find the CAADrwCreateSectionFrom3DSketch Code

The CAADrwCreateSectionFrom3DSketch use case is made of a single source file named CAADrwCreateSectionFrom3DSketch.cpp located in the CAADrwCreateSectionFrom3DSketch.m module of the CAADraftingInterfaces.edu framework:

The CAADrwCreateSectionFrom3DSketch use case is made of a single source file named CAADrwCreateSectionFrom3DSketch.cpp located in the CAADrwCreateSectionFrom3DSketch.m module of the CAADraftingInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateSectionFrom3DSketch.m\`

The CAADrwCreateSectionFrom3DSketch use case is made of a single source file named CAADrwCreateSectionFrom3DSketch.cpp located in the CAADrwCreateSectionFrom3DSketch.m module of the CAADraftingInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateSectionFrom3DSketch.m\`
Unix | ` InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCreateSectionFrom3DSketch.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are six steps in CAADrwCreatViewFrom3D:

  1. Creating and Initializing the Document
  2. Creating the Drawing in the Document
  3. Retrieving the Part document and the "SketchForSection" Sketch
  4. Creating the Section View from the "SketchForSection" Sketch
  5. Saving the Document and Exiting

[Top]
#### Creating and Initializing the Document

    int main(int iArgc, // Number of arguments (2)
    char** iArgv) // Path to the new *.CATDrawing document
    {
    // Check arguments
int main(int iArgc, // Number of arguments (2)
char** iArgv) // Path to the new *.CATDrawing document
    if(3 != iArgc) return 1;
    const char *pfileNamePart = iArgv[1];
    const char *pfileNameOut = iArgv[2];
    int code_err = 1;

    // CREATE THE SESSION
    // ==================
int code_err = 1;
    CATSession *pSampleSession = NULL;
    HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
```vbscript
    if (FAILED(hr)) return 1;

```

    ...

---

This section represents the usual sequence for loading a CATIA document [2].

[Top]
#### Creating the Drawing in the Document

    ...
       // DRAWING DOCUMENT CREATION
       // ===============================
       CATDocument* pNewDoc = NULL;
       CATDocumentServices::New("CATDrawing", pNewDoc);
    ...

---

The other steps to fully initialize the Drawing document are included in the specific sub program, `CreateViewFrom3DInDrawingDoc`.

[Top]
#### Retrieving the Part Document and the "SketchForSection" Sketch

    ...
     // READ THE PART DOCUMENT AND GET THE APPROPRIATE SKETCH
     // =====================================================
     CATDocument *pDocPart = NULL;
CATDocument *pDocPart = NULL;
     if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) && pDocPart)

     {
CATDocument *pDocPart = NULL;
if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) && pDocPart)
       CATInit_var spInitOnDoc(pDocPart);
       if(NULL_var != spInitOnDoc)

       {
         // Retrieves the root container
CATInit_var spInitOnDoc(pDocPart);
if(NULL_var != spInitOnDoc)
         CATIPrtContainer * piPrtCont = (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");
```vbscript
         if (piPrtCont)

```

         {
           // Get the part feature of the container.
CATIPrtContainer * piPrtCont = (CATIPrtContainer*) spInitOnDoc->GetRootContainer("CATIPrtContainer");
if (piPrtCont)
           CATIPrtPart_var spPart = piPrtCont->GetPart();

           // Get the appropriate sketch
CATIPrtPart_var spPart = piPrtCont->GetPart();
           CATIDescendants *piDescPart=NULL;
```vbscript
           if (SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants,(void**)&piDescPart)))

```

           {
CATIDescendants *piDescPart=NULL;
if (SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants,(void**)&piDescPart)))
             CATListValCATISpecObject_var listFeatures;

             piDescPart->GetAllChildren ("CATISketch",listFeatures) ;

             int nbChilds = listFeatures.Size();
             CATISketch* piSketch = NULL;
             CATISpecObject_var spFeat;
```vbscript
             for (int i = 1; i <= nbChilds; i++)

```

             {
int nbChilds = listFeatures.Size();
CATISketch* piSketch = NULL;
CATISpecObject_var spFeat;
for (int i = 1; i <= nbChilds; i++)
               spFeat = listFeatures[i];
```vbscript
               if (NULL_var != spFeat)

```

               {
```vbscript
for (int i = 1; i <= nbChilds; i++)
spFeat = listFeatures[i];
if (NULL_var != spFeat)
```vbscript
                 if (SUCCEEDED(spFeat->QueryInterface(IID_CATISketch, (void**)&piSketch)))
```

```

                 {
spFeat = listFeatures[i];
if (NULL_var != spFeat)
```vbscript
if (SUCCEEDED(spFeat->QueryInterface(IID_CATISketch, (void**)&piSketch)))
```

                   CATIAlias *piSketchAlias = NULL;
```vbscript
                   if (SUCCEEDED(piSketch->QueryInterface(IID_CATIAlias, (void**)&piSketchAlias)))

```

                   {
```vbscript
if (SUCCEEDED(spFeat->QueryInterface(IID_CATISketch, (void**)&piSketch)))
CATIAlias *piSketchAlias = NULL;
if (SUCCEEDED(piSketch->QueryInterface(IID_CATIAlias, (void**)&piSketchAlias)))
                     CATUnicodeString SketchName = piSketchAlias->GetAlias();
    		 const CATUnicodeString SketchSection_UC = "SketchForSection";
    		 if (SketchName == SketchSection_UC)
```vbscript
```vbscript
    		 hr = CreateSectionViewFromSketchInDrawingDoc(pNewDoc, piSketch);

```

```

```

    ...

---

All the sketches in the Part document are retrieved by using the ` GetAllChildren` method of the _CATIDescendants_ interface. The appropriate sketch is extracted from the list thanks to the `GetAlias` method of the _CATIAlias_ interface.

[Top]
#### Creating the Section View from the "SketchForSection" Sketch

    ...

    // ---------------------------------------------------------------
    // Sub program to create a Drawing Generative View from a 3D Sketch.
    // ---------------------------------------------------------------
    HRESULT CreateSectionViewFromSketchInDrawingDoc(CATDocument *ipNewDoc, CATISketch *ipi3DSketch)
    {
HRESULT CreateSectionViewFromSketchInDrawingDoc(CATDocument *ipNewDoc, CATISketch *ipi3DSketch)
      HRESULT hr = E_FAIL;

```vbscript
      if (ipNewDoc && ipi3DSketch)

```

      {
        // DRAWING STANDARD CREATION
        // ===============================

        // Gets the drawing feature using the CATIDftDocumentServices interface
        CATIDftDrawing *piDftDrawing = NULL;
        CATIDftDocumentServices *piDftDocServices = NULL;
        CATIContainer_var spDrwCont;
```vbscript
        if (SUCCEEDED(ipNewDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))

```

        {
CATIDftDrawing *piDftDrawing = NULL;
CATIDftDocumentServices *piDftDocServices = NULL;
CATIContainer_var spDrwCont;
if (SUCCEEDED(ipNewDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
          piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
          piDftDocServices->Release();
          piDftDocServices = NULL;
```vbscript
          if (piDftDrawing)

```

          {
piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
piDftDocServices->Release();
piDftDocServices = NULL;
if (piDftDrawing)
            CATISpecObject *piDrawingSO=NULL;
```vbscript
            if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))

```

            {
```vbscript
if (piDftDrawing)
CATISpecObject *piDrawingSO=NULL;
if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))
```vbscript
```vbscript
              spDrwCont = piDrawingSO->GetFeatContainer();
              if (NULL_var != spDrwCont)
```

```

```

              {
```vbscript
if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))
```vbscript
```vbscript
spDrwCont = piDrawingSO->GetFeatContainer();
if (NULL_var != spDrwCont)
```

```

                CATIDftStandardManager *piStdmgr = NULL;
                hr = spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
```vbscript
                if (SUCCEEDED(hr))
```

```

                {
                  // Find a standard in the list of allowed standards (ie. the list of .CATDrwSTD files in the reffiles directory)
CATIDftStandardManager *piStdmgr = NULL;
hr = spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
```vbscript
if (SUCCEEDED(hr))
```

                  CATIStringList *piListstd = NULL;
```vbscript
                  if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) && piListstd )

```

                  {
CATIStringList *piListstd = NULL;
if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) && piListstd )
                    unsigned int nbrstd = 0;
                    piListstd->Count(&nbrstd);
```vbscript
                    for (unsigned int indice = 0; indice < nbrstd; indice ++)

```

                    {
unsigned int nbrstd = 0;
piListstd->Count(&nbrstd);
for (unsigned int indice = 0; indice < nbrstd; indice ++)
                      wchar_t *wstd = NULL;
```vbscript
                      if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) && wstd )

```

                      {

wchar_t *wstd = NULL;
if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) && wstd )
    		    CATUnicodeString stdname;
    		    const CATUnicodeString ISO_UncS = "ISO";
    		    stdname.BuildFromWChar(wstd);
```vbscript
    		    if ( stdname == ISO_UncS )

```

    		    {
                          // Import the ISO standard in the document
const CATUnicodeString ISO_UncS = "ISO";
stdname.BuildFromWChar(wstd);
if ( stdname == ISO_UncS )
                          piStdmgr->ImportStandard (wstd);
                          break;

                        }
piStdmgr->ImportStandard (wstd);
break;
                        delete[] wstd; wstd = NULL;

                      }
                    }
break;
delete[] wstd; wstd = NULL;
                    piListstd->Release(); piListstd=NULL;

                  }
delete[] wstd; wstd = NULL;
piListstd->Release(); piListstd=NULL;
                  piStdmgr->Release (); piStdmgr=NULL;

                }
              }

              // Creation of new generative section view from a 3D Sketch in the active sheet of the Drawing Document
piStdmgr->Release (); piStdmgr=NULL;
              CATIDftView *piDftSectionViewFrom3D = NULL;
              CATIDftSheet *piDftSheet = NULL;
              piDftDrawing->GetActiveSheet(&piDftSheet);

              // View anchor point definition
CATIDftView *piDftSectionViewFrom3D = NULL;
CATIDftSheet *piDftSheet = NULL;
piDftDrawing->GetActiveSheet(&piDftSheet);
              double ptOrigin[2] = {150.0,150.0};
               CATMathVector normalSketch;
              CATI2DLine_var spFirstLine;
              double pOrthoDirection[2];

              CATIDftGenViewFactory *piDftGenViewFact = NULL;
```vbscript
              if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact)))

```

              {
                // vecPro argument compute:
                // VecPro must be a direction perpandicular to the first line in the sketch defining the section profile.
                // The Vecpro orientation informs the system which part will be drawn in the section view.
```vbscript
if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact)))
```vbscript
                CATLISTV (CATI2DWFGeometry_var ) GeomList;
                if (SUCCEEDED(ipi3DSketch->GetComponents(CATI2DWFGeometry::ClassName(),GeomList)))
```

```

                {
CATLISTV (CATI2DWFGeometry_var ) GeomList;
```vbscript
```vbscript
if (SUCCEEDED(ipi3DSketch->GetComponents(CATI2DWFGeometry::ClassName(),GeomList)))
                  if (GeomList.Size() > 1)

```

```

                  {
CATLISTV (CATI2DWFGeometry_var ) GeomList;
```vbscript
```vbscript
if (SUCCEEDED(ipi3DSketch->GetComponents(CATI2DWFGeometry::ClassName(),GeomList)))
if (GeomList.Size() > 1)
```

```

                    int indice=1;
```vbscript
                    while (indice < GeomList.Size())

```

                    {
```vbscript
if (GeomList.Size() > 1)
int indice=1;
while (indice < GeomList.Size())
                      spFirstLine = GeomList[indice];
                      if (NULL_var != spFirstLine)
```

                      {
while (indice < GeomList.Size())
spFirstLine = GeomList[indice];
if (NULL_var != spFirstLine)
                        double pOrigin[2],pDirection[2];
                        spFirstLine->GetLineData(pOrigin, pDirection);
                        pOrthoDirection[0] = pDirection[1];
                        pOrthoDirection[1] = -pDirection[0];
                        break;

                      }
spFirstLine->GetLineData(pOrigin, pDirection);
pOrthoDirection[0] = pDirection[1];
pOrthoDirection[1] = -pDirection[0];
break;
                      indice++;

                    }
                  }
                }
indice++;
                CATISpecObject_var spPlanarSupport;
```vbscript
                if (SUCCEEDED(ipi3DSketch->GetPlanarSupport(spPlanarSupport )))

```

                {
CATISpecObject_var spPlanarSupport;
if (SUCCEEDED(ipi3DSketch->GetPlanarSupport(spPlanarSupport )))
                  CATPlane_var spPlane= spPlanarSupport;
                  if(NULL_var != spPlane)

                  {
```vbscript
if (SUCCEEDED(ipi3DSketch->GetPlanarSupport(spPlanarSupport )))
CATPlane_var spPlane= spPlanarSupport;
if(NULL_var != spPlane)
                    CATMathPlane mathPlaneSk;
                    spPlane->GetAxis(mathPlaneSk);
                    CATMathPoint ThePoint;
                    mathPlaneSk.EvalPoint(pOrthoDirection[0],pOrthoDirection[1],ThePoint);
                    double XCoord = ThePoint.GetX();
                    double YCoord = ThePoint.GetY();
                    double ZCoord = ThePoint.GetZ();

                    CATMathDirection vecPro;
                    vecPro.SetCoord(XCoord,YCoord,ZCoord);

```

                    // Offset Profile
CATMathDirection vecPro;
vecPro.SetCoord(XCoord,YCoord,ZCoord);
                    int viewProfile = 0;

                    // Section View defined by a Sketch
int viewProfile = 0;
                    CATCell *piPlaneElem = NULL;
                    CATBody *piBody= NULL;
                    CATMathPoint iLimitPoints[2];

                    // Sketch defined in Part Document
CATCell *piPlaneElem = NULL;
CATBody *piBody= NULL;
CATMathPoint iLimitPoints[2];
                    CATIProduct *piProduct= NULL;

                    // Creation of the section view associative to a 3D Sketch
CATIProduct *piProduct= NULL;
```vbscript
                    hr = piDftGenViewFact->CreateStandAloneSectionView(ptOrigin, DftSectionView, vecPro, viewProfile, ipi3DSketch,piPlaneElem,piBody,iLimitPoints,piProduct,

```

                    &piDftSectionViewFrom3D);
CATIProduct *piProduct= NULL;
hr = piDftGenViewFact->CreateStandAloneSectionView(ptOrigin, DftSectionView, vecPro, viewProfile, ipi3DSketch,piPlaneElem,piBody,iLimitPoints,piProduct,
                    piDftGenViewFact->Release();piDftGenViewFact=NULL;

                  }
                }
              }
piDftGenViewFact->Release();piDftGenViewFact=NULL;
              piDrawingSO->Release();
              piDrawingSO=NULL;

            }
piDrawingSO->Release();
piDrawingSO=NULL;
           piDftDrawing->Release();
           piDftDrawing = NULL;

         }
       }
      }
piDftDrawing->Release();
piDftDrawing = NULL;
      return hr;

    }
    ...

---

The sub program `CreateSectionViewFromSketchInDrawingDoc` create a Section View from a 3D Sketch by using the method ` CreateStandAloneSectionView` of the _CATIDftGenViewFactory_ interface. This interface is implemented by the Sheet. The Drawing Standard has to be initialized before the Drawing View creation

Main arguments to initialize are:

  * `ptOrigin`: Anchor point of the section view
  * `DftSectionView`: Type of the Section
  * `VecPro`: must be a direction perpandicular to **the first line** in the sketch defining the section profile and included in this sketch.
The `Vecpro` orientation informs the system which part will be drawn in the section view.
  * `ipi3DSketch`: 3D Sketch.

The other arguments are of no use in this sample.

[Top]
#### Saving the Document and Exiting

    ...
    // SAVE THE RESULT
    // =================
    if (pNewDoc)
    {
```vbscript
if (pNewDoc)
      CATDocumentServices::SaveAs(*pNewDoc, (char *)pfileNameOut);
      CATDocumentServices::Remove (*pNewDoc);
```

    }

    //ENDS SESSION AND DROPS DOCUMENT
    //=====================================
CATDocumentServices::Remove (*pNewDoc);
    if (pDocPart)
      CATDocumentServices::Remove (*pDocPart);

    ::Delete_Session("SampleSession");

---

This section represents the usual sequence for saving a newly created CATIA document.

[Top]

* * *
### In Short

This use case shows the way to:

This use case shows the way to:
  1. Open a Part document
  2. Retrieve the appropriate sketch in the Part document.
  3. Create a Drawing document, and initialize the sStandard
  4. Create a section view from a 3D Sketch by using ` CreateStandAloneSectionView` method defined in the _CATIDftGenViewFactory_ interface
  5. Save the Drawing document

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [ Loading a Document](../CAAOmbUseCases/CAAOmbLoadDoc.md)
[Top]

* * *
### History

Version: **1** [Jan 2005] | Document created
---|---
[Top]

* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
