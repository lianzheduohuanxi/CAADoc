---
```vbscript
title: "Accessing Spatial Integration Data"
category: "use case"
module: "CAACloUseCases"
tags: ["CAACommonLayoutItf", "CAACloPspSpatialPhysical", "CATIArrNode_var", "CAACloPspSpatialPhysicalMain", "CAACloPlacePart", "CATIPspPhysical", "CATIArrSegmentsString", "CAAPspUtilities", "CATIPspSpatial", "CATIUnknownList", "CAAPspBaseEnvProtected", "CAAPlantShipInterfaces", "CAACloPspEduIn", "CATIA"]
source_file: "Doc/online/CAACloUseCases/CAACloPspSpatialPhysical.htmmd"
converted: "2026-05-11T17:33:49.507426"
```

---
tags: ["CAACommonLayoutItf", "CAACloPspSpatialPhysical", "CATIArrNode_var", "CAACloPspSpatialPhysicalMain", "CAACloPlacePart", "CATIPspPhysical", "CATIArrSegmentsString", "CAAPspUtilities", "CATIPspSpatial", "CATIUnknownList", "CAAPspBaseEnvProtected", "CAAPlantShipInterfaces", "CAACloPspEduIn", "CATIA"]
source_file: "Doc/online/CAACloUseCases/CAACloPspSpatialPhysical.htmmd"
converted: "2026-05-11T17:33:49.507426"
Equipment & Systems |  Distributive Systems |  Accessing Spatial Integration Data _How to access integration data._

converted: "2026-05-11T17:33:49.507426"
Equipment & Systems |  Distributive Systems |  Accessing Spatial Integration Data _How to access integration data._
Use Case

* * *

Abstract This article discusses the CAACloPspSpatialPhysical use case.
    * **Overview**
      * What You Will Learn
      * What CAACloPspSpatialPhysical Does
      * How to Launch CAACloPspSpatialPhysical
      * Where to Find CAACloPspSpatialPhysical Files
    * **Step-by-Step**
      * Initialization.
      * Use Case Execution.
      * Retrieving Physical Objects Associated to a Spatial Object.
    * **In Short**
    * **References**

* * *

Overview CAACloPspSpatialPhysical is a use case of the CAACommonLayoutItf.edu framework. It illustrates a CATPlantShipInterfaces interface that is implemented by CATCommonLayout. [Top] What You Will Learn This use case is intended to show you how to obtain integration data from spatial object. [Top] What CAACloPspSpatialPhysical Does CAACloPspSpatialPhysical retrieves the physical objects and corresponding connectors associated at the extremity of the spatial object.   [Top] How to Launch CAACloPspSpatialPhysical To launch CAACloPspSpatialPhysical, you will need to set up the build time environment, then compile CAACloPspSpatialPhysical along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1]. When launching the use case, you must pass the following arguments:
    * **CAACloPspEduIn.CATProduct** - the entire pathname, name and extension (.CATProduct) of the input product. Normally, it should be stored in the CNext/resources/graphic/CAACloPspEduIn directory of the CAACommonLayoutItf.edu framework.
[Top] Where to Find CAACloPspSpatialPhysical Files CAACloPspSpatialPhysical code is located in the CAACloPspSpatialPhysical.m use case module of the CAACommonLayoutItf.edu framework: Windows | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPspSpatialPhysical.m`
---|---
Overview CAACloPspSpatialPhysical is a use case of the CAACommonLayoutItf.edu framework. It illustrates a CATPlantShipInterfaces interface that is implemented by CATCommonLayout. [Top] What You Will Learn This use case is intended to show you how to obtain integration data from spatial object. [Top] What CAACloPspSpatialPhysical Does CAACloPspSpatialPhysical retrieves the physical objects and corresponding connectors associated at the extremity of the spatial object.   [Top] How to Launch CAACloPspSpatialPhysical To launch CAACloPspSpatialPhysical, you will need to set up the build time environment, then compile CAACloPspSpatialPhysical along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1]. When launching the use case, you must pass the following arguments:
Unix | `InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPspSpatialPhysical.m`
where `InstallRootDirectory` is the root directory of your CAA V5 installation. It is made of  two unique source files named CAACloPspSpatialPhysicalMain.cpp and CAACloPspSpatialPhysical.cpp. [Top] Step-by-Step The remainder of this document describes the various parts of CAACloPspSpatialPhysicalMain.cpp and CAACloPspSpatialPhysical.cpp.

    * Initialization.
    * Use Case Execution.
    * Retrieving Physical Objects Associated to a Spatial Object.
[Top] Initialization. CAACloPspSpatialPhysicalMain.cpp contains the main method that initiates processing. It reads the command line argument to find the path of the data file to be processed. It also creates the CAACloPspSpatialPhysical class and calls the DoSample method of CAACloPspSpatialPhysical.

    // COPYRIGHT DASSAULT SYSTEMES 2011
    //=============================================================================
    //
    // CAACloPspSpatialPhysicalMain
    // This sample illustrates how to use the CAA Plant Ship interfaces to:
    // 1.Query spatial objects.
    //
    //
    //  Prerequisite:
    //  -------------------
    //  This sample uses the input product CAACloPspEduIn.CATProduct.
    //
    //  Running the program:
    //  -------------------
    //  To run this program, you can use the command:
    //
    //       mkrun -c "CAACloPspSpatialPhysical CAACloPspEduIn.CATProduct"
    //
    //  where "CAACloPspEduIn.CATProduct" is the full path name of the input product.
    //
    //=============================================================================
    //
    #include <iostream.h>
    #include <string.h>

    // This framework
    #include "CAACloPspSpatialPhysical.h"

    // System
    #include "CATErrorMacros.h"
    #include "CATUnicodeString.h"

    //=============================================================================
    //   Main
    //=============================================================================
    int main (int argc, char **argv)
    {
int main (int argc, char **argv)
      cout <<"Start main CAACloPspSpatialPhysical"  << endl;

      CATUnicodeString FileToBeLoaded = NULL;

      int rc = 0;

      CATTry

      {
int rc = 0;
CATTry
```vbscript
        if (argc > 1)

```

        {
CATTry
if (argc > 1)
          FileToBeLoaded = argv[1];

        }

```vbscript
if (argc > 1)
FileToBeLoaded = argv[1];
        if (FileToBeLoaded.GetLengthInChar(#))
```

        {
FileToBeLoaded = argv[1];
if (FileToBeLoaded.GetLengthInChar(#))
          cout << "**** must input the file name of " << endl;
          cout << "a CATProduct with Piping application objects " << endl;

        }

cout << "**** must input the file name of " << endl;
cout << "a CATProduct with Piping application objects " << endl;
        else

        {
cout << "a CATProduct with Piping application objects " << endl;
else
          CAACloPspSpatialPhysical myObject;
          cout << "FileToBeLoaded = " << FileToBeLoaded << endl;
```vbscript
          rc = myObject.DoSample(FileToBeLoaded);

```

        }
      }

cout << "FileToBeLoaded = " << FileToBeLoaded << endl;
rc = myObject.DoSample(FileToBeLoaded);
```vbscript
      CATCatch (CATError, pError)

```

      {
CATCatch (CATError, pError)
        cout << "error in main " << endl;
        cout  << "error message : "  <<

          ( error ->GetNLSMessage(#)).ConvertToChar(#)<<endl;

cout << "error in main " << endl;
cout  << "error message : "  <<
        delete error;
        rc = 999;

      }
delete error;
rc = 999;
      CATEndTry;

      cout  << "End main CAACloPspSpatialPhysical"  << endl;
      return rc;

    }

[Top] Use Case Execution. The CAACloPspSpatialPhysical DoSample method runs the use cases. It starts by calling CreateCATProductEnv to load the input data model and create a CATIA product environment. CreateCATProductEnv is part of the CAAPspBaseEnvProtected class which is defined in these files. InstallRootDirectory/CAAPlantShipInterfaces.edu/PublicInterfaces/CAAPspBaseEnvProtected.h
return rc;
InstallRootDirectory/CAAPlantShipInterfaces.edu/CAAPspUtilities.m/src/CAAPspBaseEnvProtected.cpp
After CAACloPspSpatialPhysical calls CreateCATProductEnv it calls ApplicationInit to initialize the Piping application. ApplicationInit is also a part of the CAAPspBaseEnvProtected class. With the data model and application properly initialized DoSample runs the use case. The code for DoSample is shown below.

    //=============================================================================
    //  Execute the CAACloPspSpatialPhysical sample code.
    //=============================================================================
After CAACloPspSpatialPhysical calls CreateCATProductEnv it calls ApplicationInit to initialize the Piping application. ApplicationInit is also a part of the CAAPspBaseEnvProtected class. With the data model and application properly initialized DoSample runs the use case. The code for DoSample is shown below.
    HRESULT CAACloPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)

    {
HRESULT CAACloPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPspSpatialPhysical::DoSample             ==="<< endl;
      cout <<"============================================================"<< endl;
      cout <<" File: " << iuFileToBeLoaded << endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.

      CATTry
      {
        //  Load input document
CATTry
        CreateCATProductEnv(iuFileToBeLoaded);
        cout << "Product environment created." << endl;

        //  Initialize Piping Design application
```vbscript
CreateCATProductEnv(iuFileToBeLoaded);
cout << "Product environment created." << endl;
        ApplicationInit("CATPiping");
        cout << "Piping application initialized." << endl;

```

        // Retrieve a list of physical objects and connectors associated at the extremity of the spatial object.
```vbscript
ApplicationInit("CATPiping");
cout << "Piping application initialized." << endl;
        HRESULT rcListCntrPhy = ListConnectedPhysicalsToSpatial(#);
        cout << "rcListCntrPhy = " << rcListCntrPhy << endl;
```

```vbscript
        // Set return code.
HRESULT rcListCntrPhy = ListConnectedPhysicalsToSpatial(#);
```
cout << "rcListCntrPhy = " << rcListCntrPhy << endl;
        if (SUCCEEDED(rcListCntrPhy))
        rc = CATReturnSuccess;

      }  // end CATTry

```vbscript
if (SUCCEEDED(rcListCntrPhy))
rc = CATReturnSuccess;
      CATCatch (CATError, pError)
```

      {
rc = CATReturnSuccess;
CATCatch (CATError, pError)
        cout << "CAACloPspSpatialPhysical::DoSample *** Error Caught ***" << endl;
        cout << pError;

```vbscript
        rc = CATReturnError(pError);

```

      } // end CATCatch

rc = CATReturnError(pError);
      CATEndTry;

      cout << "CAACloPspSpatialPhysical::DoSample rc = " << rc << endl;
      return rc;

    }

[Top] Retrieving Physical Objects Associated to a Spatial Object. The CATIPspPhysical interface is used to retrieve pointer associated to the spatial object. In this sample, the CATIPspPhysical interface pointer is obtained from a physical part in the document. Using the spatial object associated to the previous physical object, we find its CATIPspSpatial interface. The physical objects and corresponding connectors associated at the extremity of the spatial object can be retrieved using the CATIPspSpatial interface.

    //===============================================================================================================
    // Retrieve all physical objects and corresponding connectors associated at the extremity of the spatial object.
    //===============================================================================================================
     HRESULT CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial(#)
    {
HRESULT CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial(#)
      cout <<"======================================================================"<< endl;
      cout <<"===   CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial    ==="<< endl;
      cout <<"======================================================================"<< endl;

      HRESULT rc = E_FAIL;

      CATIPspPhysical     *piPhysical  = NULL;
      CATIPspSpatial      *piSpatial  = NULL;
      IUnknown            *piUnknown  = NULL;
      CATIArrSegmentsString  *pRun  = NULL;

      CATIArrNode_var ospEndPoint1  = NULL_var;
      CATIArrNode_var ospEndPoint2  = NULL_var;
      CATIArrNode_var spArrNode  = NULL_var;

      CATIUnknownList  *piListOfPhysicals  = NULL;
      CATIUnknownList  *piListOfConnectors	 = NULL;

      CATTry

      {
        //-------------------------------------------------------------------------
        //  CATIPspPhysical methods
        //-------------------------------------------------------------------------
CATTry
        piPhysical  = GetAPhysicalObject(#);
```vbscript
```vbscript
        if ( NULL != piPhysical )

```

```

        {
          //----------------------------------------------------------------------
          //  Get the spatial object associated to the physical object
          //----------------------------------------------------------------------
          if ( SUCCEEDED(piPhysical->GetSpatial(piUnknown)) && NULL != piUnknown )
          {
            //  Find CATIPspSpatial interface
```vbscript
if ( SUCCEEDED(piPhysical->GetSpatial(piUnknown)) && NULL != piUnknown )
            piUnknown->QueryInterface(IID_CATIPspSpatial,(void**)&piSpatial);
            piUnknown->Release(#);
            piUnknown = NULL;
```

          }
          //-------------------------------------------------------------------------
          //  CATIPspSpatial methods
          //-------------------------------------------------------------------------
          if ( NULL != piSpatial )
          {
            //----------------------------------------------------------------------------------------------------
            //  Get a list of physical objects and connectors associated at the extremity of the spatial object.
            //----------------------------------------------------------------------------------------------------
```vbscript
if ( NULL != piSpatial )
```vbscript
            if (SUCCEEDED (piSpatial->QueryInterface(IID_CATIArrSegmentsString, (void**)&pRun)))
```

```

            {
```vbscript
if (SUCCEEDED (piSpatial->QueryInterface(IID_CATIArrSegmentsString, (void**)&pRun)))
              pRun->GetEndPoints(ospEndPoint1,ospEndPoint2);
              if(!!ospEndPoint1)
                spArrNode = ospEndPoint1;

              if ( SUCCEEDED(piSpatial->ListConnectedPhysicals( spArrNode, piListOfPhysicals, piListOfConnectors ))
```

                && NULL != piListOfPhysicals  && NULL != piListOfConnectors )
              {
spArrNode = ospEndPoint1;
if ( SUCCEEDED(piSpatial->ListConnectedPhysicals( spArrNode, piListOfPhysicals, piListOfConnectors ))
                unsigned int ListSize = 0;
                piListOfPhysicals->Count(&ListSize);
                cout << "Number of physical objects associated to the first extremity of the spatial object: " << (int)ListSize << endl;
                piListOfPhysicals->Release(#);  piListOfPhysicals = NULL;

                piListOfConnectors->Count(&ListSize);
                cout << "Number of connectors connected to the first extremity of the spatial object: " << (int)ListSize << endl;
                piListOfConnectors->Release(#);  piListOfConnectors = NULL;
                rc = S_OK;

              }
            }
cout << "Number of connectors connected to the first extremity of the spatial object: " << (int)ListSize << endl;
piListOfConnectors->Release(#);  piListOfConnectors = NULL;
rc = S_OK;
```vbscript
            if ( NULL != pRun )

```

            {
rc = S_OK;
if ( NULL != pRun )
              pRun->Release(#);
              pRun = NULL;

            }
```vbscript
if ( NULL != pRun )
pRun->Release(#);
pRun = NULL;
            piSpatial->Release(#);
            piSpatial = NULL;
```

          } // end piSpatial
pRun = NULL;
piSpatial->Release(#);
piSpatial = NULL;
          piPhysical->Release(#);
          piPhysical = NULL;

        } // end piPhysical
      } // end CATTry
piPhysical->Release(#);
piPhysical = NULL;
      CATCatch (CATError, error)

      {
piPhysical = NULL;
CATCatch (CATError, error)
```vbscript
```vbscript
        if ( NULL != piPhysical ) { piPhysical->Release(#); piPhysical = NULL; }
        if ( NULL != piSpatial ) { piSpatial->Release(#); piSpatial = NULL; }
        if ( NULL != piUnknown ) {  piUnknown->Release(#); piUnknown = NULL; }
```

```

        cout << "CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial *** CATRethrow" << endl;
        CATRethrow;

      }
```vbscript
if ( NULL != piSpatial ) { piSpatial->Release(#); piSpatial = NULL; }
```vbscript
if ( NULL != piUnknown ) {  piUnknown->Release(#); piUnknown = NULL; }
```

cout << "CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial *** CATRethrow" << endl;
CATRethrow;
      CATEndTry;
      cout << "CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial rc = " << rc << endl;
      return rc;
```

    }

[Top] In Short This use case has demonstrated how to use the Psp interfaces to obtain object integration data. Specifically, it has illustrated:
    * Initialize the CATIA product environment and piping application.
    * Obtaining the necessary Psp Interfaces.
    * Listing the physical parts and corresponding connectors associated at the extremity of the spatial object.
[Top]

* * *

References [1] | [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---

* * *

Footnotes 1. This documents uses Unix-style forward slash (/) to separate directory names. Windows users should use backslash (/) instead of forward slash (/).
---

* * *

History Version: **1** [February 2011] | Document created
---|---
[Top]

* * *

_Copyright 2011, Dassault Systmes. All rights reserved._
