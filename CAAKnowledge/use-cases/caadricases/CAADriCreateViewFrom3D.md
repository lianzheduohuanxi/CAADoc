---
```vbscript
title: "Creating a View from 3D"
category: "use case"
module: "CAADriUseCases"
tags: ["CATIDftStandardManager", "CATIDftDrawing", "CATIDftDocumentServices", "CATIContainer_var", "CATIA", "CATITPSList", "CATITPSDocument", "CAADrwCreateViewFrom3D", "CATIStringList", "CATIDftView", "CATITPSView", "CATITPSComponent", "CATISpecObject", "CAADrwCreatViewFrom3D", "CATInit", "CATIDftGenViewFactory", "CAADraftingInterfaces", "CATITPSSet", "CATIDftSheet"]
source_file: "Doc/online/CAADriUseCases/CAADriCreateViewFrom3D.htm"
converted: "2026-05-11T17:31:50.983117"
```

---
# Mechanical Design

| 
## Drafting

| 
### Creating a View from 3D

_How_ _to create a view from 3D with annotations created by the Functional and Tolerancing and Annotation workbench_  
---|---|---  
Use Case  

* * *
### Abstract

This article discusses the CAADrwCreateViewFrom3D use case. This use case explains how to create _a view from 3D_ with annotations created by Functional and Tolerancing and Annotation workbench.

  * **What You Will Learn With This Use Case**
  * **The CAADrwCreateViewFrom3D Use Case**
    * What Does CAADrwCreateViewFrom3D Do
    * How to Launch  CAADrwCreateViewFrom3D
    * Where to Find the  CAADrwCreateViewFrom3D Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to create a Drawing generative view from a TPS view. A TPS view __ is defined in a 3D part, product or process that is assigned 3D tolerance specifications and annotations. The Drawing generative View will be associated to the part document and the TPS view. All the modifications applied in the TPS view will be propagated in the Drawing generative view by update. 

_Fig 1: The part document containing a TPS View (Front View.1)_  
---  
![](images/CAACreateVIewFrom3D1.jpg)  

[Top]
### The CAADrwCreateViewFrom3D Use Case

CAADrwCreateViewFrom3D is a use case of the CAADraftingInterfaces.edu framework that illustrates DraftingInterfaces framework capabilities.

[Top]
#### What Does CAADrwCreateViewFrom3D Do?

  _Fig. 2: Drawing Document with the view from 3D_  
---  
![](images/CAACreateVIewFrom3D2.jpg)  

Fig. 2 represents the Drawing document in which a front view has been created from the active TPS view of Annotation Set in the Part document. Note: A red cross is created to inform the end user that the text leader is associative to hidden geometry in the view.

[Top]
#### How to Launch CAADrwCreateViewFrom3D

Fig. 2 represents the Drawing document in which a front view has been created from the active TPS view of Annotation Set in the Part document. Note: A red cross is created to inform the end user that the text leader is associative to hidden geometry in the view.
To launch CAADrwCreateViewFrom3D, you will need to set up the build time environment, then compile CAADrwCreateViewFrom3D along with its prerequisites, set up the run time environment, and then execute the use case [1].

When you launch the use case, pass the full pathname of the Drawing file as argument. A Part file is delivery in the following path: CAADraftingInterfaces.edu\CNext\resources\graphic\PadWith3DAnnotations.CATPart. 

  * With Windows 

When you launch the use case, pass the full pathname of the Drawing file as argument. A Part file is delivery in the following path: CAADraftingInterfaces.edu\CNext\resources\graphic\PadWith3DAnnotations.CATPart.
        e:> mkrun -c cmd
        CAADrwCreateViewFrom3D c/.../PadWith3DAnnotations.CATPart c/DrawingTestOutput.CATDrawing  

---  
  * With UNIX 

        $ mkrun -c cmd
        CAADrwCreateViewFrom3D /u/users/.../PadWith3DAnnotations.CATPart /u/users/DrawingTestOutput.CATDrawing  

---  

[Top]
#### Where to Find the CAADrwCreateViewFrom3D Code

The CAADrwCreateViewFrom3D use case is made of a single source file named CAADrwCreateViewFrom3D .cpp located in the CAADrwCreateViewFrom3D.m module of the CAADraftingInterfaces.edu framework:

The CAADrwCreateViewFrom3D use case is made of a single source file named CAADrwCreateViewFrom3D .cpp located in the CAADrwCreateViewFrom3D.m module of the CAADraftingInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateViewFrom3D.m\`  

The CAADrwCreateViewFrom3D use case is made of a single source file named CAADrwCreateViewFrom3D .cpp located in the CAADrwCreateViewFrom3D.m module of the CAADraftingInterfaces.edu framework:
Windows | ` InstallRootDirectory\CAADraftingInterfaces.edu\CAADrwCreateViewFrom3D.m\`
Unix | ` InstallRootDirectory/CAADraftingInterfaces.edu/CAADrwCreateViewFrom3D.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are five steps in CAADrwCreatViewFrom3D:

  1. Creating and Initializing the Document
  2. Creating the Drawing in the Document
  3. Retrieving the Part Document and the Active TPS View
  4. Creating the View from 3D
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
    if (FAILED(hr)) return 1;

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
#### Retrieving the Part Document and  the Active View of the TPS Annotation Set

    ...
    // READ THE PART DOCUMENT AND GET ACTIVE TPS VIEW
    // ====================================================
      CATDocument *pDocPart = NULL;
CATDocument *pDocPart = NULL;
      if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) )

      {
CATDocument *pDocPart = NULL;
if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) )
        CATInit *piDocAsInit = 0;
        if( SUCCEEDED(pDocPart->QueryInterface(IID_CATInit, (void**)&piDocAsInit)) )

        {
```vbscript
if( SUCCEEDED(CATDocumentServices::OpenDocument(pfileNamePart, pDocPart)) )
CATInit *piDocAsInit = 0;
if( SUCCEEDED(pDocPart->QueryInterface(IID_CATInit, (void**)&piDocAsInit)) )
          CATITPSDocument *piTPSDoc= NULL;
          if (SUCCEEDED(piDocAsInit->QueryInterface(IID_CATITPSDocument,(void **)&piTPSDoc)))
```

          {
```vbscript
if( SUCCEEDED(pDocPart->QueryInterface(IID_CATInit, (void**)&piDocAsInit)) )
CATITPSDocument *piTPSDoc= NULL;
if (SUCCEEDED(piDocAsInit->QueryInterface(IID_CATITPSDocument,(void **)&piTPSDoc)))
            CATITPSList *piTPSList = NULL;
            if (SUCCEEDED(piTPSDoc->GetSets(&piTPSList)))
```

            {
```vbscript
if (SUCCEEDED(piDocAsInit->QueryInterface(IID_CATITPSDocument,(void **)&piTPSDoc)))
CATITPSList *piTPSList = NULL;
if (SUCCEEDED(piTPSDoc->GetSets(&piTPSList)))
              unsigned int nbSet;
              piTPSList->Count(&nbSet);
              if (nbSet > 0)
```

              {
unsigned int nbSet;
piTPSList->Count(&nbSet);
if (nbSet > 0)
                CATITPSComponent *piTPSCmp = NULL;
                if (SUCCEEDED(piTPSList->Item(0,&piTPSCmp)))

                {
```vbscript
if (nbSet > 0)
CATITPSComponent *piTPSCmp = NULL;
if (SUCCEEDED(piTPSList->Item(0,&piTPSCmp)))
                  if (piTPSCmp)
```

                  {
CATITPSComponent *piTPSCmp = NULL;
if (SUCCEEDED(piTPSList->Item(0,&piTPSCmp)))
if (piTPSCmp)
                    CATITPSSet *piTPSSet = NULL;
                    if (SUCCEEDED(piTPSCmp->QueryInterface(IID_CATITPSSet,(void **)&piTPSSet)))

                    {
```vbscript
if (piTPSCmp)
CATITPSSet *piTPSSet = NULL;
if (SUCCEEDED(piTPSCmp->QueryInterface(IID_CATITPSSet,(void **)&piTPSSet)))
                      CATITPSView *piTPSActiveView = NULL;
                      if (SUCCEEDED(piTPSSet->GetActiveView (&piTPSActiveView)) && piTPSActiveView)
```

                      {
```vbscript
if (SUCCEEDED(piTPSCmp->QueryInterface(IID_CATITPSSet,(void **)&piTPSSet)))
CATITPSView *piTPSActiveView = NULL;
if (SUCCEEDED(piTPSSet->GetActiveView (&piTPSActiveView)) && piTPSActiveView)
                        IUnknown *pTPSViewUk = NULL;
                        if (SUCCEEDED(piTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
```

                        {
                          // Call a Sub Program to Create a Drawing View from TPS View in a Drawing Document
                          // =========================================================================
IUnknown *pTPSViewUk = NULL;
if (SUCCEEDED(piTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
                          hr = CreateViewFrom3DInDrawingDoc(pNewDoc,piTPSActiveView);

    ...  

---  

[Top]
#### Creating the View from 3D

    ...
    // Sub program to create a Drawing Generative View from TPS View.
    // =========================================================
    HRESULT CreateViewFrom3DInDrawingDoc(CATDocument *ipNewDoc, CATITPSView *ipiTPSActiveView)
    {
HRESULT CreateViewFrom3DInDrawingDoc(CATDocument *ipNewDoc, CATITPSView *ipiTPSActiveView)
      HRESULT hr = E_FAIL;

      if (ipNewDoc && ipiTPSActiveView)

      {
      // DRAWING STANDARD CREATION
      // ===============================

      // Gets the drawing feature using the CATIDftDocumentServices interface
      CATIDftDrawing *piDftDrawing = NULL;
      CATIDftDocumentServices *piDftDocServices = NULL;
      CATIContainer_var spDrwCont;
      if (SUCCEEDED(ipNewDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))

      {
CATIDftDrawing *piDftDrawing = NULL;
CATIDftDocumentServices *piDftDocServices = NULL;
CATIContainer_var spDrwCont;
if (SUCCEEDED(ipNewDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices)))
        piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
        piDftDocServices->Release(); 
        piDftDocServices = NULL;
        if (piDftDrawing)

        {
piDftDocServices->GetDrawing(IID_CATIDftDrawing, (void **)&piDftDrawing);
piDftDocServices->Release();
piDftDocServices = NULL;
if (piDftDrawing)
          CATISpecObject *piDrawingSO=NULL;
          if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))

          {
```vbscript
if (piDftDrawing)
CATISpecObject *piDrawingSO=NULL;
if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))
            spDrwCont = piDrawingSO->GetFeatContainer();
            if (NULL_var != spDrwCont)
```

            {
```vbscript
if (SUCCEEDED(piDftDrawing->QueryInterface(IID_CATISpecObject,(void **)&piDrawingSO)))
spDrwCont = piDrawingSO->GetFeatContainer();
if (NULL_var != spDrwCont)
              CATIDftStandardManager *piStdmgr = NULL;
              hr = spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
              if (SUCCEEDED(hr))
```

              {
                // Find a standard in the list of allowed standards
CATIDftStandardManager *piStdmgr = NULL;
hr = spDrwCont->QueryInterface(IID_CATIDftStandardManager,(void**)&piStdmgr);
if (SUCCEEDED(hr))
                CATIStringList *piListstd = NULL;
                if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) && piListstd )

                {
CATIStringList *piListstd = NULL;
if ( SUCCEEDED(piStdmgr->GetAvailableStandards(&piListstd)) && piListstd )
                  unsigned int nbrstd = 0;
                  piListstd->Count(&nbrstd);
                  for (unsigned int indice = 0; indice < nbrstd; indice ++)

                  {
unsigned int nbrstd = 0;
piListstd->Count(&nbrstd);
for (unsigned int indice = 0; indice < nbrstd; indice ++)
                    wchar_t *wstd = NULL;
                    if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) && wstd )

                    {
```vbscript
for (unsigned int indice = 0; indice < nbrstd; indice ++)
wchar_t *wstd = NULL;
if ( SUCCEEDED ( piListstd->Item ( indice, &wstd ) ) && wstd )
    		  CATUnicodeString stdname;
    		  const CATUnicodeString ISO_UncS = "ISO";
    		  stdname.BuildFromWChar(wstd);
    		  if ( stdname == ISO_UncS ) 
```

                      {
                        // Import the ANSI standard in the document
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

            // Creation of new generative view from TPS view in the active sheet of the Drawing Document
piStdmgr->Release (); piStdmgr=NULL;
            CATIDftView *piDftViewFrom3D = NULL;
            CATIDftSheet *piDftSheet = NULL;
            piDftDrawing->GetActiveSheet(&piDftSheet);

            // View anchor point definition
CATIDftView *piDftViewFrom3D = NULL;
CATIDftSheet *piDftSheet = NULL;
piDftDrawing->GetActiveSheet(&piDftSheet);
            double ptOrigin[2] = {150.0,150.0};
            IUnknown *pTPSViewUk = NULL;
            if (SUCCEEDED(ipiTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))

            {
double ptOrigin[2] = {150.0,150.0};
IUnknown *pTPSViewUk = NULL;
if (SUCCEEDED(ipiTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
              CATIDftGenViewFactory *piDftGenViewFact = NULL;
              if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact))) 

              {
```vbscript
if (SUCCEEDED(ipiTPSActiveView->QueryInterface(IID_IUnknown,(void **)&pTPSViewUk)))
CATIDftGenViewFactory *piDftGenViewFact = NULL;
if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact)))
                hr = piDftGenViewFact->CreateViewFrom3D(ptOrigin, pTPSViewUk, &piDftViewFrom3D);
                piDftGenViewFact->Release();piDftGenViewFact=NULL;
```

              }
```vbscript
if (piDftSheet && SUCCEEDED(piDftSheet->QueryInterface(IID_CATIDftGenViewFactory,(void **)&piDftGenViewFact)))
hr = piDftGenViewFact->CreateViewFrom3D(ptOrigin, pTPSViewUk, &piDftViewFrom3D);
piDftGenViewFact->Release();piDftGenViewFact=NULL;
              pTPSViewUk->Release();
              pTPSViewUk=NULL;
```

            }
piDftGenViewFact->Release();piDftGenViewFact=NULL;
pTPSViewUk->Release();
pTPSViewUk=NULL;
            piDrawingSO->Release();
            piDrawingSO=NULL;

          }
pTPSViewUk=NULL;
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

The sub program `CreateViewFrom3DInDrawingDoc` creates a View from 3D by using the method `CreateViewFrom3D` of the _CATIDftGenViewFactory_ interface. This interface is implemented by the Sheet.

**Note** : Before the creation of the Drawing View, the Drawing Standard has to be correctly initialized. **It must be identical to the Standard used by the Annotation Set aggregating the TPS View in the 3D document** [3].  

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
  2. Retrieve the active TPS view in the Annotation Set
  3. Create a Drawing document, and initialize the standard
  4. Create a view from 3D by using the `CreateViewFrom3D` method defined in CATIDftGenViewFactory
  5. Save the Drawing document.

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] |  [ Loading a Document](../CAAOmbUseCases/CAAOmbLoadDoc.md)  
[3] |  Technological Product Specification Overview  
[Top]  

* * *
### History

Version: **1** [Jan 2005] | Document created  
---|---  
[Top]  

* * *

_Copyright 2005, Dassault Systmes. All rights reserved._
