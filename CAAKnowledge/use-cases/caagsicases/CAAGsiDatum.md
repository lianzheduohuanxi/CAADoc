---
title: "Converting a Shape Design Feature into a Datum"
category: "use-case case"
module: "CAAGsiUseCases"
tags: "["CAAGsiNozzle", "CATIGSMProceduralView_var", "CATICkeParm_var", "CATIPrtContainer", "CATICkeParmFactory_var", "CAAGSMInterfaces", "CATIMf3DBehavior_var", "CATIGSMAssemble_var", "CATIGSMFactory", "CATIGSMProceduralView", "CATIPrtPart_var", "CAAGsiObjectUpdate", "CATIDescendants_var", "CATISpecObject_var", "CATIModelEvents_var", "CATInit", "CATIGSMFactory_var", "CATIDescendant", "CAAGsiDatum"]"
source_file: "Doc/online/CAAGsiUseCases/CAAGsiDatum.htm"
converted: "2026-05-11T17:31:50.628699"
---
# Shape Design & Styling

|
## Generative Shape Design

|
### Converting a Shape Design Feature into a Datum

_Using the Shape Design factory to convert a Shape Design feature into a datum_
---|---|---
Use Case

* * *
### Abstract

This article discusses the CAAGsiDatum use case. This use case explains how to convert feature into datum.

  * **What You Will Learn With This Use Case**
  * ****The CAAGsiDatum Use Case**
    * What Does CAAGsiDatum Do
    * How to Launch CAAGsiDatum
    * Where to Find the CAAGsiDatum Code
  * **Step-by-Step**
  * **In Short**
  * **References**

**
---

* * *
### What You Will You Learn With This Use Case

This use case illustrate the ability to convert any Wireframe and Shape Design feature into a Datum.
Wireframe and Shape Design features to be converted do not have any child, that is to say, they do not aggregate other features (Ex: contextual features)

[Top]
### The CAAGsiDatum Use Case

CAAGsiDatum is a use case of the CAAGSMInterfaces.edu framework that illustrates the `ConvertToDatum` method of _theCATIGSMFactory_ interface of the GSMInterfaces framework.

[Top]
#### What Does CAAGsiDatum Do

The goal of CAAGsiDatum is to take the result of surface features of the CAAGsiNozzle use case, join them and convert the join into a corresponding datum feature (skin surface).

[Top]
#### How to Launch CAAGsiDatum

The goal of CAAGsiDatum is to take the result of surface features of the CAAGsiNozzle use case, join them and convert the join into a corresponding datum feature (skin surface).
To launch CAAGsiDatum, you will need to set up the build time environment, then compile CAAGsiDatum along with its prerequisites, and set up the run time environment, and then execute the use case [1].

Launch the use case as follows:

  * With Windows

        e:>CAAGsiDatum inputDirectory/GAAGsiNozzle.CATPart outputDirectory/CAAGsiDatum.CATPart

---
  * With UNIX

        $ CAAGsiDatum inputDirectory/GAAGsiNozzle.CATPart outputDirectory/CAAGsiDatum.CATPart

---

where:

`outputDirectory` | The directory into which `CAAGsiDatum.CATPart is saved`
---|---
`inputDirectory` | The directory into which `CAAGsiNozzle.CATPart is found `
`CAAGsiDatum.CATPart` | The file that contains the part created with the datum surface t

[Top]
#### Where to Find the CAAGsiDatum Code

The CAAGsiDatum use case is made of main program located in the CAAGsiDatum.m module of the CAAGSMInterfaces.edu framework:

Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiDatum.m/`

The CAAGsiDatum use case is made of main program located in the CAAGsiDatum.m module of the CAAGSMInterfaces.edu framework:
Windows | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiDatum.m/`
Unix | `InstallRootDirectory/CAAGSMInterfaces.edu/CAAGsiDatum.m/`

The input CAAGsiNozzle.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu

Windows | ` InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiNozzle.CATPart `

The input CAAGsiNozzle.CATPart is proposed in Data.d directory of CAAGSMInterfaces.edu
Windows | ` InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiNozzle.CATPart `
Unix | ` InstallRootDirectory/CAAGSMInterfaces.edu/Data.d/CAAGsiNozzle.CATPart`

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are four logical step in CAAGsiDatum:

  1. Prolog
  2. Create the join feature
  3. Convert to datum the join feature
  4. Save and close session

We will now comment each of those sections by looking at the code of the main method of file CAAGsiDatum.

[Top]

* * *
#### Prolog

CAAGsiDatum sample first creates a session and opens the input CATPart.

Note: The important feature of the following sequence of code consists in the required call to the GetPart(#) method of the CATPrtContainer interfaces. /

This method allow to load in session the different containers of the part (feature container, geometric container,..)

    ...
    // creates a session
This method allow to load in session the different containers of the part (feature container, geometric container,..)
    char *pSessionName = "SampleSession";
    CATSession *pSession = NULL;
    rc = Create_Session(pSessionName, pSession);
```vbscript
    if (NULL == pSession ) {
```

       cout << "(CAAGsiDatum) ERROR: Create_Session" << endl;
       TestCaseError = 1 ;

    }

    // loads the document and initializes it
cout << "(CAAGsiDatum) ERROR: Create_Session" << endl;
TestCaseError = 1 ;
    cout << "The input document " << InputName << " is opened" << endl ;
    CATDocument *pDoc = NULL;
```cpp
    rc =CATDocumentServices::OpenDocument(InputName, pDoc) ;

    if (NULL == pDoc ) {
```

       cout << "(CAAGsiDatum) ERROR CATDocumentServices::OpenDocument" << endl;
       TestCaseError = 2 ;

    }

    // Part Container
cout << "(CAAGsiDatum) ERROR CATDocumentServices::OpenDocument" << endl;
TestCaseError = 2 ;
    CATIPrtContainer *piPartContainer = NULL ;
    CATIPrtPart_var spPrtPart;

```vbscript
    if ( NULL != pDoc ) {

```

       // queries on the document to get the root container
CATIPrtContainer *piPartContainer = NULL ;
CATIPrtPart_var spPrtPart;
if ( NULL != pDoc ) {
       CATInit *pDocAsInit = NULL;
       pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
```vbscript
       if ( NULL != pDocAsInit ) {

```

        // Extracts from document a reference to its part in hPartAsRequest
CATInit *pDocAsInit = NULL;
pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
if ( NULL != pDocAsInit ) {
       piPartContainer =
          (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
       pDocAsInit->Release(#); pDocAsInit = NULL ;

       if( NULL != piPartContainer ) {
          CATISpecObject_var spPart = piPartContainer->GetPart(#) ;
          spPrtPart = spPart ;

       }
    }
    ...

---

Finally, the wireframe and shape design factory is retrieved. .

    ....
    // Retrieve the Generative Shape Design Interface
Finally, the wireframe and shape design factory is retrieved. .
    CATIGSMFactory_var spGsmFact;
    if ( NULL !=piPartContainer ) {
       CATIGSMFactory * _pFact =NULL;
       rc = piPartContainer -> QueryInterface(IID_CATIGSMFactory ,(void**)&_pFact);
```vbscript
       if (SUCCEEDED(rc) ) {
```

         spGsmFact = _pFact;
```vbscript
         if (_pFact) _pFact -> Release(#); _pFact = NULL;

```

      }
    }
    ...

---

[Top]
#### Create the join feature

Using standard creation method for join (also named assemble),  sweep and loft features are joined

    ...
    // Join
    // ------------------
```cpp
    CATLISTV(CATISpecObject_var) aObjectParametersAssemble;
    aObjectParametersAssemble.Append(spSweep1);
    aObjectParametersAssemble.Append(spLoft1);
    aObjectParametersAssemble.Append(spSweep2);
    aObjectParametersAssemble.Append(spLoft2);

```

    // Create feature
aObjectParametersAssemble.Append(spLoft1);
aObjectParametersAssemble.Append(spSweep2);
aObjectParametersAssemble.Append(spLoft2);
    double MergingDistanceTol = 0.001 ;
    CATBoolean iCheckConnexity = TRUE ;

    CATICkeParm_var spParm;
    CATICkeParmFactory_var spCkeFact = spGsmFact ;
    if (!!spCkeFact) {
```vbscript
```vbscript
       spParm = spCkeFact -> CreateLength("MergingDistance",MergingDistanceTol/1000.0);

```

```

    }
CATICkeParm_var spParm;
CATICkeParmFactory_var spCkeFact = spGsmFact ;
if (!!spCkeFact) {
```vbscript
spParm = spCkeFact -> CreateLength("MergingDistance",MergingDistanceTol/1000.0);
```

    CATIGSMAssemble_var spAssemble = spGsmFact -> CreateAssemble(aObjectParametersAssemble,spParm,iCheckConnexity);
    aObjectParametersAssemble.RemoveAll(#);

    // Insert in procedural view
    // ------------------
CATIGSMAssemble_var spAssemble = spGsmFact -> CreateAssemble(aObjectParametersAssemble,spParm,iCheckConnexity);
aObjectParametersAssemble.RemoveAll(#);
    CATISpecObject_var spSpecTmp = spAssemble;
```vbscript
    if (NULL_var != spSpecTmp) {

```

       // Insert in procedural view
CATISpecObject_var spSpecTmp = spAssemble;
if (NULL_var != spSpecTmp) {
       CATIGSMProceduralView_var ispProcView = spSpecTmp;
       if (NULL_var != ispProcView ) {
```vbscript
```vbscript
          rc = ispProcView ->InsertInProceduralView(#);

```

```

       }
    }

    // Update
    CAAGsiObjectUpdate(spSpecTmp);
    ...

---

The join feature is then

  *  Insert in the procedural view thanks to the InsertInProceduralView method of CATIGSMProceduralView interface of GSMInterfaces framework
  *  Updated thanks to generic service CAAGsiObjectUpdate [[4]](../CAAGsiTechArticles/CAAGsiUpdateShapeDesign.md)

[Top]
#### Convert to datum the join feature

Verify that the feature to convert is not already a Datum

    ....
    // Check the feature to convert is not already a Datum
Verify that the feature to convert is not already a Datum
    CATIMf3DBehavior_var ispBehave(ispSpec);
    if(NULL_var != ispBehave ){

```vbscript
      if ( FAILED( ispBehave -> IsADatum(#) ) ) {

```

          ....
          }
    }
    ...

---

Use the ConvertToDatum method of CATIGSMFactory interface.
This method is only available for features which do not have any child (do not aggregate other features) , The argument "Verif" allow to verify it.

```vbscript
```vbscript
For multi-domain feature, one datum feature is generated by domain of the original feature

```

```

    ....
    CATListValCATISpecObject_var *ListDatum=NULL;

    // Convert Spec in one or more Datum
CATListValCATISpecObject_var *ListDatum=NULL;
    int iVerif =1 ;   // Check feature do not have any child
    rc = ispGsmFact->ConvertToDatum(ispSpec, ListDatum,iVerif);
```vbscript
```vbscript
    if (FAILED(rc)) return E_FAIL;

```

```

    ...

---

Once created the datum feature got the representation of the the original feature thus it is mandatory to remove the original feature
This operation has to be done in 2 step

  * Dispatch the delete event to the model (in interactive session this make the visualization to be re-drawed)
  * Delete the feature itself in using "RemoveChild" of CATIDescendant interface if the feature is aggregated or the "Remove" of LifeCycleObject if not

    ....
    // Delete of Procedural Specification
    // -- Model event for delete / update visualization
    CATIModelEvents_var IME(ispSpec);
    if(NULL_var != IME) {
        CATDelete info(ispSpec->GetImpl(#));
        IME->Dispatch(info);

    }

    // -- Delete Specification
CATDelete info(ispSpec->GetImpl(#));
IME->Dispatch(info);
    CATISpecObject_var ispFather = ispSpec->GetFather(#);

    // Specification is aggretated in the prodecural view
CATISpecObject_var ispFather = ispSpec->GetFather(#);
    if (NULL_var != ispFather) {
       ispFather->Release(#);
       CATIDescendants_var ispDes = ispFather;
       ispDes->RemoveChild (ispSpec);

    }
    // Specification is not in the prodecural view
ispFather->Release(#);
CATIDescendants_var ispDes = ispFather;
ispDes->RemoveChild (ispSpec);
    else {
       LifeCycleObject_var LCO = ispSpec;
       LCO -> remove(#);

    }
    ....

---

The Datum is created , previous feature is deleted, now the Datum has to be inserted in the procedural view as for any other shape designs feature (Wires, Surfaces and Volumes created in CATIGSMFactory).

    ....
    // Insert in procedural view
The Datum is created , previous feature is deleted, now the Datum has to be inserted in the procedural view as for any other shape designs feature (Wires, Surfaces and Volumes created in CATIGSMFactory).
    int i;
    int size = AllDatums.Size(#);
    for(i=1;i<=size;i++) {
       CATIGSMProceduralView_var curobj = AllDatums[i];
       if (NULL_var != curobj ) {
```vbscript
```vbscript
       rc = curobj->InsertInProceduralView(#);
       if (FAILED(rc)) cout << " (CAAGsiDatum)  Failed to insert datum in procedural view" << endl ;

```

```

    ....

---

[Top]
#### Save and close session

Save part and close the session

    ...
    // save
Save part and close the session
    if (NULL != OutputName )      {
```vbscript
```cpp
        rc = CATDocumentServices::SaveAs  (*pDoc, OutputName );
        if (SUCCEEDED(rc))   {
```

```

                cout << " (CAAGsiDatum)  Document saved " << endl;

         }
```vbscript
if (NULL != OutputName )      {
```vbscript
```cpp
rc = CATDocumentServices::SaveAs  (*pDoc, OutputName );
if (SUCCEEDED(rc))   {
```

```

cout << " (CAAGsiDatum)  Document saved " << endl;
         else {
                cout << " ERROR in saving document " <<  endl ;
```

         }
    }
    // Closes the document
else {
cout << " ERROR in saving document " <<  endl ;
    CATDocumentServices::Remove(*pDoc);

    // Ends session and drops document
    Delete_Session("SampleSession");
    ...

---

[Top]

* * *
### In Short

This use case has demonstrated the way to convert de Datum from an existing feature.

[Top]

* * *
### References

[1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [ About Generative Shape Design Features](../CAAGsiTechArticles/CAAGsiShapeDesignFeature.md)
[3] |  [ Inserting a Shape Design Feature in the procedural view](../CAAGsiTechArticles/CAAGsiInsertInProceduralView.md)
[4] | [ Updating a shape Design feature ](../CAAGsiTechArticles/CAAGsiUpdateShapeDesign.md)
[Top]

* * *
### History

Version: **1** [May 2004] | Document created
---|---
[Top]

* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
