---
title: "Editing Callout in Generative Views"
category: "use-case case"
module: "CAADriUseCases"
tags: "["CATIDftDocumentServices", "CATIGenerSpec", "CATIDrwSimpleText", "CATIDrwAnnotationComponent", "CATIDftView", "CATIDftDrawing", "CATIDrwSubText_var", "CAADraftingInterfaces", "CATIA", "CATIDftText", "CAADrwCallout", "CATIUnknownList", "CATIDrwCalloutAccess"]"
source_file: "Doc/online/CAADriUseCases/CAADriCallout.htm"
converted: "2026-05-11T17:31:50.931544"
---
# Mechanical Design

|
## Drafting

|
### Editing Callout in Generative Views

_How to access and modify callouts in generative view_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAADrwCallout use case. This use case explains how to retrieve these elements in a generative view.

  * **What You Will Learn With This Use Case**
  * **The CAADrwCallout Use Case**
    * What Does CAADrwCallout Do
    * How to Launch CAADrwCallout
    * Where to Find the CAADrwCallout Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to access callouts in generative views.

[Top]
### The CAADrwCallout Use Case

CAADrwCallout is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCallout Do?

Fig. 1: Initial Document
---
![](images/CAADrwCallout1.jpg)
Fig. 1 represents a Drawing document containing generative views created from a Part document.

Fig. 2 The Document modified by the Use Case
---
![](images/CAADrwCallout2.jpg)
Fig. 2 represents the Drawing document modified by the use case program.  All Callouts have been modified by ApplyStyle internal method defined in this Use Case, thus, arrows of callout have been changed.

[Top]
#### How to Launch CAADrwCallout

To launch CAADrwCallout, you will need to set up the build time environment, then compile CAADrwCallout along with its prerequisites, set up the run time environment, and then execute the use case [1].

When you launch the use case, pass the full pathname of the Drawing file as argument. A Drawing file is delivery in the following path: CAADraftingInterfaces.edu/CNext/resources/graphic/DrawingForCalloutUseCase.CATDrawing.

  * With Windows

When you launch the use case, pass the full pathname of the Drawing file as argument. A Drawing file is delivery in the following path: CAADraftingInterfaces.edu/CNext/resources/graphic/DrawingForCalloutUseCase.CATDrawing.
        e:> mkrun -c cmd
        CAADrwCallout c/.../DrawingForCalloutUseCase.CATDrawing c/DrawingTestOutput.CATDrawing

---
  * With UNIX

        $ mkrun -c cmd
        CAADrwCallout /u/users/.../DrawingForCalloutUseCase.CATDrawing  /u/users/DrawingTestOutput.CATDrawing

---

[Top]
#### Where to Find the CAADrwCallout Code

The CAADrwCallout use case is made of a single source file named CAADrwCallout.cpp located in the CAADrwCallout.m module of the CAADraftingInterfaces.edu framework:

Windows | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCallout.m/`

The CAADrwCallout use case is made of a single source file named CAADrwCallout.cpp located in the CAADrwCallout.m module of the CAADraftingInterfaces.edu framework:
Windows | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCallout.m/`
Unix | `InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCallout.m/`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are seven steps in CAADrwCallout:

  1. Opening a Drawing Document
  2. Accessing the Drawing Root in the Document
  3. Accessing all Callouts in all Views
  4. Getting the View from Callout
  5. Getting Geometric Informations of Profile Associated with a Generative View
  6. Modifying Callout Representation
  7. Saving the Document and Exiting

[Top]
#### Opening a Drawing Document

    int main(int iArgc, // Number of arguments (3)
    char** iArgv) // Path to the existing file *.CATDrawing document
    {
    // Check arguments
int main(int iArgc, // Number of arguments (3)
char** iArgv) // Path to the existing file *.CATDrawing document
    if(3 != iArgc) return 1;
    const char *pfileNameDrawing = iArgv[1];
    const char *pfileNameOut = iArgv[2];

    // return code error
```vbscript
if(3 != iArgc) return 1;
const char *pfileNameDrawing = iArgv[1];
const char *pfileNameOut = iArgv[2];
    int rc =0;

```

    // CREATE THE SESSION
    // =====================

int rc =0;
    CATSession *pSampleSession = NULL;
    HRESULT hr = ::Create_Session("SampleSession",pSampleSession);
```vbscript
    if (FAILED(hr)) return 1;

```

    CATIDftDrawing *piDrawing = NULL;
    CATIDftDocumentServices *piDftDocServices = NULL;
    CATDocument* pDocDrawing = NULL;

```cpp
    if (FAILED(CATDocumentServices::OpenDocument(pfileNameDrawing, pDocDrawing)))

```

    {
    // Ends session
    ::Delete_Session("SampleSession");
    return 2;
    }
    ...

---

This section represents the usual sequence for loading a CATIA document [2].

[Top]
#### Accessing the Drawing Root in the Document

    ...
    CATIDftDrawing *piDrawing = NULL;
    CATIDftDocumentServices *piDftDocServices = NULL;
```cpp
    if (SUCCEEDED(pDocDrawing->QueryInterface(IID_CATIDftDocumentServices,(void **)&piDftDocServices)))

```

    {
CATIDftDrawing *piDrawing = NULL;
CATIDftDocumentServices *piDftDocServices = NULL;
if (SUCCEEDED(pDocDrawing->QueryInterface(IID_CATIDftDocumentServices,(void **)&piDftDocServices)))
```vbscript
```cpp
      if (SUCCEEDED(piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDrawing)))

```

```

      {
CATIDftDocumentServices *piDftDocServices = NULL;
if (SUCCEEDED(pDocDrawing->QueryInterface(IID_CATIDftDocumentServices,(void **)&piDftDocServices)))
```cpp
if (SUCCEEDED(piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDrawing)))
```

        piDftDocServices->Release(#);
        piDftDocServices=NULL;

      }
    ...

---

The root feature of a Drawing document is the Drawing itself, that is, the feature that implements the _CATIDftDrawing_ interface. We can get a pointer to _CATIDftDrawing_ using the _CATIDftDocumentServices_ interface, which is implemented by the document. The `GetDrawing` method first argument is the _CATIDftDrawing_ interface IID.

[Top]
#### Accessing all Callout in the Drawing Document

    ...
    // LOOP ON ALL VIEWS IN DRAWING
    // ================================
    CATIUnknownList * piListOfView = NULL;
```vbscript
    if (SUCCEEDED(piDrawing->GetViews(&piListOfView)))

```

    {
CATIUnknownList * piListOfView = NULL;
if (SUCCEEDED(piDrawing->GetViews(&piListOfView)))
      unsigned int piViewListSize = 0;
      piListOfView->Count(&piViewListSize);

      IUnknown * itemView = NULL;
      CATIDftView *piCurrentView = NULL;

      // Loop on all callouts of the processed view
      // -----------------------------------------------
IUnknown * itemView = NULL;
CATIDftView *piCurrentView = NULL;
      for(unsigned int numview=0 ; numview<piViewListSize ; numview++)

      {
```vbscript
for(unsigned int numview=0 ; numview<piViewListSize ; numview++)
```vbscript
        if( SUCCEEDED( piListOfView->Item(numview, &itemView) ) )
```

```

        {
```vbscript
for(unsigned int numview=0 ; numview<piViewListSize ; numview++)
```vbscript
if( SUCCEEDED( piListOfView->Item(numview, &itemView) ) )
          if (itemView)
```

```

          {
```vbscript
if( SUCCEEDED( piListOfView->Item(numview, &itemView) ) )
```vbscript
```cpp
if (itemView)
            if (SUCCEEDED(itemView->QueryInterface(IID_CATIDftView,(void **)&piCurrentView)))
```

```

```

            {
```vbscript
if (itemView)
```cpp
if (SUCCEEDED(itemView->QueryInterface(IID_CATIDftView,(void **)&piCurrentView)))
```

              CATIUnknownList * piListOfCallout = NULL;

```

              // Get list of callouts of the view processed
              // ----------------------------------------------
CATIUnknownList * piListOfCallout = NULL;
              if( SUCCEEDED( piCurrentView->GetComponents(IID_CATIDrwCalloutAccess, &piListOfCallout) ) )

              {
```cpp
if( SUCCEEDED( piCurrentView->GetComponents(IID_CATIDrwCalloutAccess, &piListOfCallout) ) )
```vbscript
                if (piListOfCallout)
```

```

                {
```cpp
if( SUCCEEDED( piCurrentView->GetComponents(IID_CATIDrwCalloutAccess, &piListOfCallout) ) )
```vbscript
if (piListOfCallout)
```

                  unsigned int piListSize = 0;
                  piListOfCallout->Count(&piListSize);

                  CATIDrwCalloutAccess* piCallout = NULL;
                  IUnknown * item = NULL;

```

                  // Loop on all callouts of the view processed
                  // ----------------------------------------------
CATIDrwCalloutAccess* piCallout = NULL;
IUnknown * item = NULL;
                  for(unsigned int i=0 ; i<piListSize ; i++)

                  {
```vbscript
for(unsigned int i=0 ; i<piListSize ; i++)
```vbscript
                    if( SUCCEEDED( piListOfCallout->Item(i, &item) ) )
```

```

                    {
```vbscript
for(unsigned int i=0 ; i<piListSize ; i++)
```cpp
if( SUCCEEDED( piListOfCallout->Item(i, &item) ) )
                      if(SUCCEEDED( item->QueryInterface(IID_CATIDrwCalloutAccess, (void**) & piCallout) ) )
```

```

                      {

    ...

---

The GetViews method returns the list of all views in Drawing document. The GetComponents method of CATIDftView interface is a generic method to return elements identified by his IID.

[Top]
#### Getting the View from Associated Callout

    ...
    // Get the view associated with the callout
    // -------------------------------------------
    CATIDftView *piDefView=NULL;

```vbscript
    if (SUCCEEDED(piCallout->GetAssociatedView(&piDefView)))

```

    {
CATIDftView *piDefView=NULL;
if (SUCCEEDED(piCallout->GetAssociatedView(&piDefView)))
      piDefView->GetViewName(&pViewName);
      ViewName.BuildFromWChar(pViewName);
      cerr << " View name associated to the processed callout: " << ViewName.CastToCharPtr(#) << endl;

    ...

---

GetAssociatedView method defined in CATIDrwCalloutAccess interface returns the View from which Callout is defined. In case of Broken View, Callout are created in the same View, So GetAssociatedView is useless.

[Top]
#### Getting Geometric Information of a Profile Associated to a Generative View

    ...

    CATIGenerSpec *piGenerSpec=NULL;
    if (SUCCEEDED(piDefView->GetGenerSpec(&piGenerSpec)))
    {

      // Get callout type
      // -------------------
      CATIDrwCalloutAccess::CATDrwCalloutType calloutType;
      piCallout->GetCalloutType(calloutType);

```cpp
      if (calloutType == CATIDrwCalloutAccess::SectionCallout)

```

      {
CATIDrwCalloutAccess::CATDrwCalloutType calloutType;
piCallout->GetCalloutType(calloutType);
if (calloutType == CATIDrwCalloutAccess::SectionCallout)
        CATListPtrCATMathPoint2D ListOfPoints;
        int depli=0;
        CATMathDirection vecpro;

        // Get geometric informations about section profile
        // ---------------------------------------------------------
int depli=0;
CATMathDirection vecpro;
```vbscript
        if (SUCCEEDED(piGenerSpec->GetSectionProfile(ListOfPoints,depli,vecpro)))

```

        {
```vbscript
if (SUCCEEDED(piGenerSpec->GetSectionProfile(ListOfPoints,depli,vecpro)))
          int NbPt = ListOfPoints.Size(#);
          for (int numpt=1 ; numpt<=NbPt ; numpt++)
```

          {
```cpp
if (SUCCEEDED(piGenerSpec->GetSectionProfile(ListOfPoints,depli,vecpro)))
int NbPt = ListOfPoints.Size(#);
for (int numpt=1 ; numpt<=NbPt ; numpt++)
            CATMathPoint2D *tmpt = ListOfPoints[numpt];
            cerr << " Number point = " << numpt << ", X= "<< tmpt->GetX(#) << "Y = " << tmpt->GetY(#) << endl;

```

            // Memory clean
CATMathPoint2D *tmpt = ListOfPoints[numpt];
cerr << " Number point = " << numpt << ", X= "<< tmpt->GetX(#) << "Y = " << tmpt->GetY(#) << endl;
```vbscript
            if (tmpt) delete tmpt , tmpt=NULL;

```

          }
        }
      }

    ...

---

From the Associated view to the Callout, It is possible to retrieve the definition of the View. For example for a Section View, the Cutting Profile may be obtained by GetSectionProfile method defined in CATIGenerSpec Interface.

Note: depli and vecpro arguments are dedicated to give information about the type of the profile (Aligned Section View or Offset Section View)

#### Modifying the Callout Representation.

    ...
    int NbTexts;
    rc = piCallout->GetNumberOfTexts(NbTexts);
```vbscript
```vbscript
    if (SUCCEEDED(rc))

```

```

    {
int NbTexts;
rc = piCallout->GetNumberOfTexts(NbTexts);
```vbscript
```vbscript
if (SUCCEEDED(rc))
      for (int iNumText = 1; iNumText <= NbTexts ; iNumText++)

```

```

      {
rc = piCallout->GetNumberOfTexts(NbTexts);
```vbscript
```vbscript
if (SUCCEEDED(rc))
for (int iNumText = 1; iNumText <= NbTexts ; iNumText++)
```

```

        CATIDrwAnnotationComponent *piAnnot=NULL;
        rc = piCallout->GetCalloutText(iNumText,&piAnnot);
```vbscript
```vbscript
        if (SUCCEEDED(rc))

```

```

        {
CATIDrwAnnotationComponent *piAnnot=NULL;
rc = piCallout->GetCalloutText(iNumText,&piAnnot);
```vbscript
if (SUCCEEDED(rc))
```

          CATIDrwSimpleText *piText=NULL;
          CATIDftText *piDftText = NULL;

          // Callout texts may be based on simple text instance until V5R13 CATIA level.
CATIDrwSimpleText *piText=NULL;
CATIDftText *piDftText = NULL;
```cpp
          if (SUCCEEDED(piAnnot->QueryInterface(IID_CATIDrwSimpleText,(void **)&piText)))

```

          {
```cpp
if (SUCCEEDED(piAnnot->QueryInterface(IID_CATIDrwSimpleText,(void **)&piText)))
            CATIDrwSubText_var spSubText;
            spSubText = piText->GetSubText(1);
            CATUnicodeString textName = spSubText->GetText(#);
            cerr << " texte name = " << textName.CastToCharPtr(#) << endl;

            piText->Release(#); piText=NULL;
```

          }
CATUnicodeString textName = spSubText->GetText(#);
cerr << " texte name = " << textName.CastToCharPtr(#) << endl;
piText->Release(#); piText=NULL;
          else if(SUCCEEDED(piAnnot->QueryInterface(IID_CATIDftText,(void **)&piDftText)))

          {
piText->Release(#); piText=NULL;
else if(SUCCEEDED(piAnnot->QueryInterface(IID_CATIDftText,(void **)&piDftText)))
            wchar_t *ptextName=NULL;
```vbscript
            if (SUCCEEDED(piDftText->GetString(&ptextName)))

```

            {
else if(SUCCEEDED(piAnnot->QueryInterface(IID_CATIDftText,(void **)&piDftText)))
wchar_t *ptextName=NULL;
if (SUCCEEDED(piDftText->GetString(&ptextName)))
              CATUnicodeString strTextName;
              strTextName.BuildFromWChar(ptextName);
              cerr << " texte name = " <<strTextName.CastToCharPtr(#) << endl;
```vbscript
              if (ptextName) delete[] ptextName; ptextName = NULL;

```

            }
CATUnicodeString strTextName;
strTextName.BuildFromWChar(ptextName);
cerr << " texte name = " <<strTextName.CastToCharPtr(#) << endl;
if (ptextName) delete[] ptextName; ptextName = NULL;
            piDftText->Release(#);piDftText=NULL;

          }
cerr << " texte name = " <<strTextName.CastToCharPtr(#) << endl;
if (ptextName) delete[] ptextName; ptextName = NULL;
piDftText->Release(#);piDftText=NULL;
          piAnnot->Release(#);piAnnot=NULL;

        }
      }

      // Modification of the callout Representation

      int thickness = 2;
int thickness = 2;
```vbscript
      rc = piCallout->SetProfileThickness(thickness);

```

      int linetype = 3;
```vbscript
      rc = piCallout->SetProfileLineType(linetype);

```

      int NbArrows;
      rc =piCallout->GetNumberOfArrow(NbArrows);
```vbscript
```vbscript
      if (SUCCEEDED(rc))

```

```

      {
int NbArrows;
rc =piCallout->GetNumberOfArrow(NbArrows);
```vbscript
```vbscript
if (SUCCEEDED(rc))
        for (int iNumArrow = 1; iNumArrow <= NbArrows ; iNumArrow++)

```

```

        {
rc =piCallout->GetNumberOfArrow(NbArrows);
```vbscript
```vbscript
if (SUCCEEDED(rc))
for (int iNumArrow = 1; iNumArrow <= NbArrows ; iNumArrow++)
```

```

          double ArrowLength,ArrowLengthSymb,ArrowAngleSymb,ArrowOrientation;
          CATSymbolType ArrowTypeSymb;
          ArrowLength=35.0;
          ArrowTypeSymb=FILLED_ARROW;
          ArrowLengthSymb=6.0;
          ArrowAngleSymb=45.0;

```vbscript
          rc = piCallout->SetInfoOfArrow(iNumArrow,ArrowLength,ArrowTypeSymb,ArrowLengthSymb,ArrowAngleSymb);

```

        }

```vbscript
ArrowAngleSymb=45.0;
rc = piCallout->SetInfoOfArrow(iNumArrow,ArrowLength,ArrowTypeSymb,ArrowLengthSymb,ArrowAngleSymb);
```vbscript
        if (NbArrows != 0)
```

```

        {
rc = piCallout->SetInfoOfArrow(iNumArrow,ArrowLength,ArrowTypeSymb,ArrowLengthSymb,ArrowAngleSymb);
```vbscript
if (NbArrows != 0)
```

          CATDftArrowExtremity calloutAttachment;
          rc = piCallout->GetArrowsAttachment(calloutAttachment);
          calloutAttachment= CATDftArrowTail;
```vbscript
          rc = piCallout->SetArrowsAttachment(calloutAttachment);

```

        }
      }
    }
    ...

---

Note: Up to V5R13, associated texts to the Callout may be based on simple text instance.

[Top]
#### Saving the Document and Exiting

    ...
      // Save the result
      rc = CATDocumentServices::**SaveAs**(*pDoc, (char *)fileName);
      ... // Check rc
      rc = CATDocumentServices::**Remove** (*pDoc);
      ... // Check rc
      // Ends session and drops document
rc = CATDocumentServices::**SaveAs**(*pDoc, (char *)fileName);
```vbscript
```cpp
rc = CATDocumentServices::**Remove** (*pDoc);
      rc = ::**Delete_Session**("SampleSession");

```

```

      ... // Check rc

      return 0;
    }

---

This section represents the usual sequence for saving a newly created CATIA document [3].

[Top]

* * *
### In Short

This use case shows the way to :

  1. Open a Drawing document.
  2. Scan all Callout in the document
  3. Retrieve Associated View to the Callout.
  4. Retrieve Geometric Definition of a Generative View linked to a Callout.
  5. Read and modify representation of a Callout
  6. Save the document.

[Top]

* * *
### References

[1] |  [ Building and Lauching CAA V5 Samples](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [ Load an existing Document](../CAAOmbUseCases/CAAOmbLoadDoc.md)
[Top]

* * *
### History

Version: **1** [May 2004] | Document created
---|---
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
