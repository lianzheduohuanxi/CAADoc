---
title: "Placing Parts"
category: "use case"
module: "CAACloUseCases"
tags: "["CATIArrNode_var", "CATIPspConnection", "CATIProduct", "CATIAHybridShapeFactory", "CAAPspUtilities", "CATIPspConnectable", "CATIArrSegment", "CAACloPlacePart", "CATIArrSegmentsString", "CATIPspPhysicalProduct", "CAACloEduRuns", "CATIAPart", "CATIArrSegment_var", "CATIPspPlacePartOnRun", "CATIUnknownList", "CATIPspLogicalLine", "CATIPspConnector", "CATIPspPartConnector", "CAACommonLayoutItf", "CATIUnknownListImpl"]"
source_file: "Doc/online/CAACloUseCases/CAACloPlacePart.htm"
converted: "2026-05-11T17:33:49.487432"
---
tags: ["CATIArrNode_var", "CATIPspConnection", "CATIProduct", "CATIAHybridShapeFactory", "CAAPspUtilities", "CATIPspConnectable", "CATIArrSegment", "CAACloPlacePart", "CATIArrSegmentsString", "CATIPspPhysicalProduct", "CAACloEduRuns", "CATIAPart", "CATIArrSegment_var", "CATIPspPlacePartOnRun", "CATIUnknownList", "CATIPspLogicalLine", "CATIPspConnector", "CATIPspPartConnector", "CAACommonLayoutItf", "CATIUnknownListImpl"]
source_file: "Doc/online/CAACloUseCases/CAACloPlacePart.htmmd"
converted: "2026-05-11T17:33:49.487432"
Equipment & Systems |  Distributive Systems |  Placing Parts _How to place parts._

converted: "2026-05-11T17:33:49.487432"
Equipment & Systems |  Distributive Systems |  Placing Parts _How to place parts._
Use Case

* * *

Abstract This article discusses the CAACloPlacePart use case.
    * **Overview**
      * What You Will Learn
      * What CAACloPlacePart Does
      * How to Launch CAACloPlacePart
      * Where to Find CAACloPlacePart Files
    * **Step-by-Step**
      * Initialization
      * Use Case Execution
      * Support Methods
      * Parts in Space
      * Parts on Run Segments
      * Parts on Run Nodes
      * Parts on Part Connectors
    * **In Short**
    * **References**

* * *

Overview CAACloPlacePart is a use case of the CAACommonLayoutItf.edu framework. It illustrates a CATPlantShipInterfaces interface that is implemented by CATCommonLayout. [Top] What You Will Learn This use case is intended to show you how to place parts using the CATIPspPlacePartOnRun interface. [Top] What CAACloPlacePart Does CAACloPlacePart places tubing parts. It places a valve and tube in space. It also places parts on run segments, run nodes and part connectors.   [Top] How to Launch CAACloPlacePart To launch CAACloPlacePart, you will need to set up the build time environment, then compile CAACloPlacePart along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article [1].  Launch the use case with the following command. CAACloPlacePart MyRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct1 where MyRootDirectory is the pathname of the root directory where you copied and built the use case.  [Top] Where to Find CAACloPlacePart Files The CAACloPlacePart code consists of three files located in the CAACloPlacePart.m use case module of the CAACommonLayoutItf.edu framework: InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPlacePart.m/LocalInterfaces/CAACloPlacePart.h
InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPlacePart.m/src/CAACloPlacePart.cpp
InstallRootDirectory/CAACommonLayoutItf.edu/CAACloPlacePart.m/src/CAACloPlacePartMain.cpp
where `InstallRootDirectory` is the root directory of your CAA V5 installation1.  This sample uses two C++ source files: CAACloPlacePartMain.cpp and CAACloPlacePart.cpp. CAACloPlacePartMain.cpp holds the main method which initiates the sample code. CAACloPlacePart.cpp defines the class that places parts. CAACloPlacePart has a corresponding header (.h) file.  The CAACloPlacePart also uses three data files: InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct
InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CATTubTubingLine20010507183018970.CATProduct
InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/TubingWP.CATProduct
CAACloEduRuns.CATProduct is the main data model for the use cases. It is the file which should be referenced in the execution command line. CATTubTubingLine20010507183018970.CATProduct and TubingWP.CATProduct are used by CAACloEduRuns.CATProduct.  [Top] Step-by-Step The remainder of this document describes the various parts of CAACloPlacePartMain.cpp and CAACloPlacePart.cpp.

    * Initialization
    * Use Case Execution
    * Support Methods
    * Parts in Space
    * Parts on Run Segments
    * Parts on Run Nodes
    * Parts on Part Connectors
[Top] Initialization CAACloPlacePartMain.cpp contains the main method that initiates processing. It reads the command line argument to find the path of the data file to be processed. It also creates the CAACloPlacePart class and calls the DoSample method of CAACloPlacePart.

    // COPYRIGHT DASSAULT SYSTEMES 2008
    //=============================================================================
    //
    // CAACloPlacePartMain
    //
    //  This sample illustrates how to use the CAA Plant Ship interfaces to place parts.
    //
    //
    //  Prerequisite:
    //  -------------------
    //  This sample uses the input drawing CAACloEduRuns.CATProduct.
    //
    //  Running the program:
    //  -------------------
    //  To run this program, you can use the command:
    //
    //        CAACloPlacePart MyRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct
    //
    //  where MyRootDirectory is the pathname of the root directory where you copied and built the use case.
    //
    //=============================================================================
    //
    #include <iostream.h>
    #include <string.h>

    // This framework
    #include "CAACloPlacePart.h"

    // System
    #include "CATErrorMacros.h"
    #include "CATUnicodeString.h"

    //=============================================================================
    //   Main
    //=============================================================================
    int main (int argc, char **argv)
    {

int main (int argc, char **argv)
      cout << "Start main CAACloPlacePart" << endl;

      int rc = 0;

      HRESULT rcError = CATReturnFailure;

      CATUnicodeString FileToBeLoaded = NULL;

      CAACloPlacePart myObject;

      CATTry

      {
CAACloPlacePart myObject;
CATTry
```vbscript
        if (argc > 1)

```

        {

CATTry
if (argc > 1)
          FileToBeLoaded = argv[1];

        }

        if (FileToBeLoaded.IsNull(#))
        {

```cpp
if (FileToBeLoaded.IsNull(#))
           cout << "**** must input the file name of " << endl;
           cout << "a CATProduct with Piping application objects " << endl;
```

        }

cout << "**** must input the file name of " << endl;
cout << "a CATProduct with Piping application objects " << endl;
        else

        {
cout << "a CATProduct with Piping application objects " << endl;
else
          cout << "FileToBeLoaded = " << FileToBeLoaded << endl;

```vbscript
          rcError = myObject.DoSample(FileToBeLoaded);

```

        }
      }

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "error in main " << endl;

```cpp
        rcError = CATReturnError(pError);

```

    	} // end CATCatch

rcError = CATReturnError(pError);
      CATEndTry;

      cout << "CAACloPlacePart rcError = " << rcError << endl;

```vbscript
      if (FAILED(rcError))

```

      {
cout << "CAACloPlacePart rcError = " << rcError << endl;
if (FAILED(rcError))
        rc = 999;
        CATError *pError = CATError::CATGetLastError(rcError);

```vbscript
        if (pError)

```

        {
rc = 999;
CATError *pError = CATError::CATGetLastError(rcError);
if (pError)
          cout << pError;
          Flush(pError);

        }
      }

cout << pError;
Flush(pError);
      cout << "CAACloPlacePart rc = " << rc << endl;
      cout << "End main CAACloPlacePart" << endl;

      return rc;

    }

[Top] Use Case Execution The CAACloPlacePart DoSample method runs the use cases. It starts by calling CreateCATProductEnv to load the input data model and create a CATIA product enviroment. CreateCATProductEnv is part of the CAAPspBaseEnvProtected class which is defined in these files. InstallRootDirectory/CAAPlantShipInterfaces.edu/PublicInterfaces/CAAPspBaseEnvProtected.h
return rc;
InstallRootDirectory/CAAPlantShipInterfaces.edu/CAAPspUtilities.m/src/CAAPspBaseEnvProtected.cpp
After CAACloPlacePart calls CreateCATProductEnv it calls ApplicationInit to initialize the Tubing application. ApplicationInit is also a part of the CAAPspBaseEnvProtected class. With the data model and application properly initialized DoSample runs the use case. The use case places parts in free space, on run segments, on run nodes and on part connectors. The code for DoSample is shown below.

    //=============================================================================
    //  Execute the CAACloPlacePart sample code.
    //=============================================================================
After CAACloPlacePart calls CreateCATProductEnv it calls ApplicationInit to initialize the Tubing application. ApplicationInit is also a part of the CAAPspBaseEnvProtected class. With the data model and application properly initialized DoSample runs the use case. The use case places parts in free space, on run segments, on run nodes and on part connectors. The code for DoSample is shown below.
    HRESULT CAACloPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)

    {
HRESULT CAACloPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)
      cout <<"============================================================"<< endl;

      cout <<"===       CAACloPlacePart::DoSample                      ==="<< endl;
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

        //  Initialize Tubing Design application
```cpp
CreateCATProductEnv(iuFileToBeLoaded);
cout << "Product environment created." << endl;
        ApplicationInit("CATTubing");
        cout << "Tubing application initialized." << endl;

```

        // Place a part in space.
```cpp
ApplicationInit("CATTubing");
cout << "Tubing application initialized." << endl;
        HRESULT rcSpace = PlacePartInSpace(#);
        cout << "rcSpace = " << rcSpace << endl;

```

        // Route a string in space.
HRESULT rcSpace = PlacePartInSpace(#);
cout << "rcSpace = " << rcSpace << endl;
        HRESULT rcStringInSpace = RouteStringPartInSpace(#);
        cout << "rcStringInSpace = " << rcStringInSpace << endl;

        // Place parts on run segments.
HRESULT rcStringInSpace = RouteStringPartInSpace(#);
cout << "rcStringInSpace = " << rcStringInSpace << endl;
        HRESULT rcSegment = PlacePartOnRunSegment(#);
        cout << "rcSegment = " << rcSegment << endl;

        // Place parts on part conntectors.
HRESULT rcSegment = PlacePartOnRunSegment(#);
cout << "rcSegment = " << rcSegment << endl;
        HRESULT rcPartCtr = PlacePartOnPartConnector(#);
        cout << "rcPartCtr = " << rcPartCtr << endl;

        // Place parts on run nodes.
HRESULT rcPartCtr = PlacePartOnPartConnector(#);
cout << "rcPartCtr = " << rcPartCtr << endl;
        HRESULT rcNode = PlacePartOnRunNode(#);
        cout << "rcNode = " << rcNode << endl;

        // Place part on part conntector and reconnect run.
HRESULT rcNode = PlacePartOnRunNode(#);
cout << "rcNode = " << rcNode << endl;
        HRESULT rcPartCtrNCnt = PlacePartOnPartConnectorAndReconnectRun(#);
        cout  << "rcPartCtrNCnt = " << rcPartCtrNCnt  << endl;

```cpp
        // Set return code.
HRESULT rcPartCtrNCnt = PlacePartOnPartConnectorAndReconnectRun(#);
```
cout  << "rcPartCtrNCnt = " << rcPartCtrNCnt  << endl;
        if (SUCCEEDED(rcSpace) &&
```vbscript
            SUCCEEDED(rcStringInSpace) &&
            SUCCEEDED(rcSegment) &&
            SUCCEEDED(rcPartCtr) &&
            SUCCEEDED(rcNode) &&
            SUCCEEDED(rcPartCtrNCnt))

```

          rc = CATReturnSuccess;

      } // end CATTry

```cpp
SUCCEEDED(rcPartCtrNCnt))
rc = CATReturnSuccess;
    	CATCatch (CATError, pError)
```

    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::DoSample *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      cout << "CAACloPlacePart::DoSample rc = " << rc << endl;
      return rc;

    }

[Top] Support Methods The CAACloPlacePart has several methods that support the use scenario.
    * **GetPartConnector** retrieves a part connector given a part and the connector number.
    * **GetPartConnectorData** gets connector position, alignment and up direction relative to an input axis object.
    * **GetConnectedPart** retrieves the connector and part connected to a part connector.
    * **TestPartConnectorData** tests connector position, alignment and up direction against expected values.
    * **TestConnectedPart** tests the connector and part connected to a part connector.
The code for the support methods is shown below.

    //=============================================================================
    // Get a part connector.
    //=============================================================================
The code for the support methods is shown below.
    HRESULT CAACloPlacePart::GetPartConnector(const IUnknown *ipiPartUnk,
                                              const int &iConnectorNumber,
                                              IUnknown *&opiPartConnector)

    {

HRESULT CAACloPlacePart::GetPartConnector(const IUnknown *ipiPartUnk,
const int &iConnectorNumber,
IUnknown *&opiPartConnector)
      cout <<"============================================================"<< endl;
      cout <<"===    CAACloPlacePart::GetPartConnector                 ==="<< endl;
      cout <<"============================================================"<< endl;

```vbscript
      cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;

      cout <<" Connector number " << iConnectorNumber << endl;
```

      opiPartConnector = NULL;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
opiPartConnector = NULL;
HRESULT rc = CATReturnFailure;
      CATIPspPhysicalProduct *piPhysProd = NULL;

      CATIUnknownList *piListCtrs = NULL;

      int NumOfCtrs = 0;

      unsigned int ListSize = 0;

      CATTry

      {
unsigned int ListSize = 0;
CATTry
        if (ipiPartUnk &&
```cpp
            SUCCEEDED(((IUnknown*)ipiPartUnk)->QueryInterface(IID_CATIPspPhysicalProduct,(void**)&piPhysProd)))

```

        {

          //----------------------------------------------------------------------
          //  List part connectors
          //----------------------------------------------------------------------
          if ( SUCCEEDED(piPhysProd->ListConnectors(NULL,&piListCtrs))
               && NULL != piListCtrs )
          {

             //  Get list of part connectors
```vbscript
if ( SUCCEEDED(piPhysProd->ListConnectors(NULL,&piListCtrs))
```vbscript
```vbscript
             if ( SUCCEEDED(piListCtrs->Count(&ListSize)) ) NumOfCtrs = ListSize;

```

```

             cout << "Number of connectors on part: " << NumOfCtrs << endl;
             if (0 < iConnectorNumber &&
                 NumOfCtrs >= iConnectorNumber)
```

             {

cout << "Number of connectors on part: " << NumOfCtrs << endl;
if (0 < iConnectorNumber &&
NumOfCtrs >= iConnectorNumber)
```vbscript
               rc = piListCtrs->Item(iConnectorNumber-1,&opiPartConnector);

```

             } // End if valid ctr number.

           } // End if valid list of part ctrs.
        } // End if valid input part.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::GetPartConnector *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piPhysProd) {piPhysProd->Release(#); piPhysProd = NULL;}
```vbscript
      if (piListCtrs) {piListCtrs->Release(#); piListCtrs = NULL;}
```

      cout <<" opiPartConnector = " << opiPartConnector << endl;
      cout << "CAACloPlacePart::GetPartConnector rc = " << rc << endl;

      return rc;

    }

    //=============================================================================
    //  Get location data for a part connector.
    //=============================================================================
    HRESULT CAACloPlacePart::GetPartConnectorData(const IUnknown *ipiPartUnk,
                                                  const int &iConnectorNumber,
                                                  IUnknown *ipiRelAxisUnk,
                                                  CATMathPoint &oCtrPosition,
                                                  CATMathDirection &oCtrAlign,
                                                  CATMathDirection &oCtrUp)

    {

CATMathPoint &oCtrPosition,
CATMathDirection &oCtrAlign,
CATMathDirection &oCtrUp)
      cout <<"============================================================"<< endl;
      cout <<"===    CAACloPlacePart::GetPartConnectorData             ==="<< endl;
      cout <<"============================================================"<< endl;

```vbscript
      cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;

      cout <<" Connector number " << iConnectorNumber << endl;
```

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<" Connector number " << iConnectorNumber << endl;
HRESULT rc = CATReturnFailure;
      CATIMovable *piRelAxis = NULL;
      IUnknown *piCtrUnk = NULL;

      CATIPspPartConnector *piPartCntr = NULL;

      CATTry

      {

CATIPspPartConnector *piPartCntr = NULL;
CATTry
        rc = GetPartConnector(ipiPartUnk,
                              iConnectorNumber,
                              piCtrUnk);
```vbscript
        if (SUCCEEDED(rc) && piCtrUnk)

```

        {

piCtrUnk);
if (SUCCEEDED(rc) && piCtrUnk)
```vbscript
```vbscript
          if (ipiRelAxisUnk)

```

```

            ((IUnknown*)ipiRelAxisUnk)->QueryInterface(IID_CATIMovable,(void**)&piRelAxis);

```cpp
if (ipiRelAxisUnk)
          cout << "piRelAxis = " << piRelAxis << endl;

          if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspPartConnector,(void**)&piPartCntr)))
```

          {

cout << "piRelAxis = " << piRelAxis << endl;
if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspPartConnector,(void**)&piPartCntr)))
            rc = CATReturnSuccess;

            //  Get connector position
            piPartCntr->GetPosition(piRelAxis,oCtrPosition);

            //  Get connector alignment direction
            piPartCntr->GetAlignmentDirection(piRelAxis,oCtrAlign);

            //  Get connector up direction
piPartCntr->GetAlignmentDirection(piRelAxis,oCtrAlign);
            piPartCntr->GetUpDirection(piRelAxis,oCtrUp);

```vbscript
            if (piPartCntr) {piPartCntr->Release(#); piPartCntr = NULL;}

```

          } // End if valid part connector.

piPartCntr->GetUpDirection(piRelAxis,oCtrUp);
if (piPartCntr) {piPartCntr->Release(#); piPartCntr = NULL;}
```vbscript
```vbscript
          if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}

```

```

        } // End if valid part ctr.

      } // end CATTry

```vbscript
if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
```cpp
    	CATCatch (CATError, pError)
```

```

    	{
CATCatch (CATError, pError)
        cout << "CAACloPlacePart::GetPartConnectorData *** Error Caught ***" << endl;

        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

rc = CATReturnError(pError);
      CATEndTry;

      if (piRelAxis) {piRelAxis->Release(#); piRelAxis = NULL;}
```vbscript
```vbscript
      if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
      if (piPartCntr) {piPartCntr->Release(#); piPartCntr = NULL;}

```

```

      cout << "oCtrPosition = " << oCtrPosition << endl;
      cout << "oCtrAlign = " << oCtrAlign << endl;
      cout << "oCtrUp = " << oCtrUp << endl;
      cout << "CAACloPlacePart::GetPartConnectorData rc = " << rc << endl;

      return rc;

    }

    //=============================================================================
    //  Get part connected to a part ctr.
    //=============================================================================
    HRESULT CAACloPlacePart::GetConnectedPart(const IUnknown *ipiPartUnk,
                                              const int &iConnectorNumber,
                                              IUnknown *&opiConnectedCtr,
                                              IUnknown *&opiConnectedPart)

    {

const int &iConnectorNumber,
IUnknown *&opiConnectedCtr,
IUnknown *&opiConnectedPart)
      cout <<"============================================================"<< endl;
      cout <<"===    CAACloPlacePart::GetConnectedPart                 ==="<< endl;
      cout <<"============================================================"<< endl;

```vbscript
      cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;

      cout <<" Connector number " << iConnectorNumber << endl;
```

      opiConnectedCtr = NULL;

      opiConnectedPart = NULL;
      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
opiConnectedPart = NULL;
HRESULT rc = CATReturnFailure;
      IUnknown *piCtrUnk = NULL;
      CATIPspConnection *piPspConnection = NULL;

      CATIPspConnector *piPspConnector = NULL;
      CATIUnknownList *piListConnections  = NULL;

      IUnknown *piUnk = NULL;
      CATIUnknownList *piListCtr  = NULL;

      CATIPspConnector *piPspConnectedCtr = NULL;
      CATIPspConnectable *piPspConnectedPart = NULL;

      CATTry

      {
CATIPspConnector *piPspConnectedCtr = NULL;
CATIPspConnectable *piPspConnectedPart = NULL;
CATTry
        rc = GetPartConnector(ipiPartUnk,
                              iConnectorNumber,
                              piCtrUnk);

```vbscript
        if (SUCCEEDED(rc) && piCtrUnk)

```

        {
          // Get connected objects.
piCtrUnk);
if (SUCCEEDED(rc) && piCtrUnk)
```vbscript
```cpp
          if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnector)))

```

```

          {

```cpp
if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnector)))
```vbscript
```vbscript
            if ( SUCCEEDED(piPspConnector->ListConnections (NULL, &piListConnections)) &&

```

```

                 piListConnections )
```

            {
```vbscript
if ( SUCCEEDED(piPspConnector->ListConnections (NULL, &piListConnections)) &&
piListConnections )
              cout << "piListConnections = " << piListConnections << endl;

```

              // Get a connection
piListConnections )
cout << "piListConnections = " << piListConnections << endl;
              unsigned int numCnx = 0;
              piListConnections->Count(&numCnx);

```vbscript
              for ( unsigned int iiCnx = 0; iiCnx < numCnx; iiCnx++ )

```

              {

piListConnections->Count(&numCnx);
for ( unsigned int iiCnx = 0; iiCnx < numCnx; iiCnx++ )
```vbscript
```vbscript
                if ( SUCCEEDED(piListConnections->Item(iiCnx,&piUnk)) && (NULL != piUnk) )

```

```

                {

```cpp
if ( SUCCEEDED(piListConnections->Item(iiCnx,&piUnk)) && (NULL != piUnk) )
                  piUnk->QueryInterface(IID_CATIPspConnection,(void**)&piPspConnection);
                  cout << "piPspConnection = " << piPspConnection << endl;

```vbscript
                  if (piUnk) {piUnk->Release(#); piUnk = NULL;}

                  if (piPspConnection &&
```

```vbscript
                      SUCCEEDED(piPspConnector->ListConnectedCntrs (piPspConnection, &piListCtr)) &&

```

                      piListCtr )
```

                  {
```vbscript
if (piPspConnection &&
```vbscript
SUCCEEDED(piPspConnector->ListConnectedCntrs (piPspConnection, &piListCtr)) &&
```

piListCtr )
                    unsigned int numCtr = 0;
                    piListCtr->Count(&numCtr);

                    for ( unsigned int iiCtr = 0; iiCtr < numCtr; iiCtr++ )
```

                    {

piListCtr->Count(&numCtr);
for ( unsigned int iiCtr = 0; iiCtr < numCtr; iiCtr++ )
```vbscript
```vbscript
                      if ( SUCCEEDED(piListCtr->Item(iiCtr,&piUnk)) && (NULL != piUnk) )

```

```

                      {

```cpp
if ( SUCCEEDED(piListCtr->Item(iiCtr,&piUnk)) && (NULL != piUnk) )
                        piUnk->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnectedCtr);
                        cout << "piPspConnectedCtr = " << piPspConnectedCtr << endl;

```vbscript
                        if (piUnk) {piUnk->Release(#); piUnk = NULL;}

                        if (piPspConnectedCtr)
```

```

                        {
```vbscript
if (piUnk) {piUnk->Release(#); piUnk = NULL;}
```vbscript
if (piPspConnectedCtr)
```

                          piPspConnectedCtr->GetAssociatedConnectable(&piPspConnectedPart);
                          cout << "piPspConnectedPart = " << piPspConnectedPart << endl;

                          if (piPspConnectedPart)
```

                          {
piPspConnectedCtr->GetAssociatedConnectable(&piPspConnectedPart);
cout << "piPspConnectedPart = " << piPspConnectedPart << endl;
if (piPspConnectedPart)
                            piPspConnectedCtr->QueryInterface(IID_IUnknown,(void**)&opiConnectedCtr);

                            piPspConnectedPart->QueryInterface(IID_IUnknown,(void**)&opiConnectedPart);
                            break;

                          }
piPspConnectedCtr->QueryInterface(IID_IUnknown,(void**)&opiConnectedCtr);
piPspConnectedPart->QueryInterface(IID_IUnknown,(void**)&opiConnectedPart);
break;
                          if (piPspConnectedCtr) {piPspConnectedCtr->Release(#); piPspConnectedCtr = NULL;}
```vbscript
```vbscript
                          if (piPspConnectedPart) {piPspConnectedPart->Release(#); piPspConnectedPart = NULL;}

```

```

                        }
                      } // End if valid ctr list item.

                    } // End loop on connected ctrs.
                    if (piListCtr) {piListCtr->Release(#); piListCtr = NULL;}
                  } // End if valid list of ctrs.

                  if (piPspConnection) {piPspConnection->Release(#); piPspConnection = NULL;}
                } // End if valid cnx list item.

              } // End loop on connections.
              if (piListConnections) {piListConnections->Release(#); piListConnections = NULL;}
            } // End if valid list of connections.

          } // End if valid psp ctr
          if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
        } // End if valid ctr.

      } // end CATTry

```vbscript
if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
```cpp
    	CATCatch (CATError, pError)
```

```

    	{
CATCatch (CATError, pError)
        cout << "CAACloPlacePart::GetConnectedPart *** Error Caught ***" << endl;

        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

rc = CATReturnError(pError);
      CATEndTry;

      if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
```vbscript
```vbscript
      if (piPspConnection) {piPspConnection->Release(#); piPspConnection = NULL;}
      if (piPspConnector) {piPspConnector->Release(#); piPspConnector = NULL;}
      if (piListConnections) {piListConnections->Release(#); piListConnections = NULL;}
      if (piUnk) {piUnk->Release(#); piUnk = NULL;}
      if (piListCtr) {piListCtr->Release(#); piListCtr = NULL;}
      if (piPspConnectedCtr) {piPspConnectedCtr->Release(#); piPspConnectedCtr = NULL;}
      if (piPspConnectedPart) {piPspConnectedPart->Release(#); piPspConnectedPart = NULL;}

```

```

      cout <<" opiConnectedCtr = " << opiConnectedCtr << endl;
      cout <<" opiConnectedPart = " << opiConnectedPart << endl;

      if (opiConnectedCtr && opiConnectedCtr)
        rc = CATReturnSuccess;

      cout << "CAACloPlacePart::GetConnectedPart rc = " << rc << endl;
      return rc;

    }
    #define PointTolerance  0.01 // mm
cout << "CAACloPlacePart::GetConnectedPart rc = " << rc << endl;
return rc;
    int ArePointsEqual(const CATMathPoint &iPoint0,
                       const CATMathPoint &iPoint1)

    {

int ArePointsEqual(const CATMathPoint &iPoint0,
const CATMathPoint &iPoint1)
      return (iPoint0.DistanceTo(iPoint1) <= PointTolerance);

    }

return (iPoint0.DistanceTo(iPoint1) <= PointTolerance);
    int AreVectorsEqual(const CATMathVector &iVector0,
                        const CATMathVector &iVector1)

    {

int AreVectorsEqual(const CATMathVector &iVector0,
const CATMathVector &iVector1)
      return ArePointsEqual(CATMathO+iVector0, CATMathO+iVector1);

    }

    //=============================================================================
    //  Test location data for a part connector.
    //=============================================================================

    HRESULT CAACloPlacePart::TestPartConnectorData(const IUnknown *ipiPartUnk,
                                                   const int &iConnectorNumber,
                                                   IUnknown *ipiRelAxisUnk,
                                                   const CATMathPoint &iCtrPosition,
                                                   const CATMathDirection &iCtrAlign,
                                                   const CATMathDirection &iCtrUp)

    {

const CATMathPoint &iCtrPosition,
const CATMathDirection &iCtrAlign,
const CATMathDirection &iCtrUp)
      cout <<"============================================================"<< endl;
      cout <<"===    CAACloPlacePart::TestPartConnectorData            ==="<< endl;
      cout <<"============================================================"<< endl;

```vbscript
      cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;

```

      cout <<" Connector number " << iConnectorNumber << endl;
      cout << "iCtrPosition = " << iCtrPosition << endl;

      cout << "iCtrAlign = " << iCtrAlign << endl;
      cout << "iCtrUp = " << iCtrUp << endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout << "iCtrUp = " << iCtrUp << endl;
HRESULT rc = CATReturnFailure;
      CATIMovable *piRelAxis = NULL;

      IUnknown *piCtrUnk = NULL;
      CATIPspPartConnector *piPartCntr = NULL;

      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;

      CATTry

      {

CATMathDirection ctrUp;
CATTry
        if (SUCCEEDED(GetPartConnectorData(ipiPartUnk,
                                           iConnectorNumber,
                                           ipiRelAxisUnk,
                                           ctrPosition,
                                           ctrAlign,
                                           ctrUp)))

        {

ctrPosition,
ctrAlign,
ctrUp)))
          cout << "ctrPosition = " << ctrPosition << endl;
          cout << "ctrAlign = " << ctrAlign << endl;

          cout << "ctrUp = " << ctrUp << endl;

          if (ArePointsEqual(ctrPosition, iCtrPosition) &&
```vbscript
              AreVectorsEqual(ctrAlign, iCtrAlign) &&
              AreVectorsEqual(ctrUp, ctrUp))

```

          {

```vbscript
if (ArePointsEqual(ctrPosition, iCtrPosition) &&
```vbscript
AreVectorsEqual(ctrAlign, iCtrAlign) &&
AreVectorsEqual(ctrUp, ctrUp))
```

            rc = CATReturnSuccess;
```

          }

        } // End if get valid part ctr data succeeded.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::TestPartConnectorData *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piRelAxis) {piRelAxis->Release(#); piRelAxis = NULL;}
```vbscript
```vbscript
      if (piCtrUnk) {piCtrUnk->Release(#); piCtrUnk = NULL;}
      if (piPartCntr) {piPartCntr->Release(#); piPartCntr = NULL;}

```

```

      cout << "CAACloPlacePart::TestPartConnectorData rc = " << rc << endl;
      return rc;

    }

cout << "CAACloPlacePart::TestPartConnectorData rc = " << rc << endl;
return rc;
    int AreObjectsEqual(const IUnknown *ipiObject0,
                        const IUnknown *ipiObject1)

    {

int AreObjectsEqual(const IUnknown *ipiObject0,
const IUnknown *ipiObject1)
      int rc = 0;

      IUnknown *piObjectUnk0 = NULL;

      IUnknown *piObjectUnk1 = NULL;

```vbscript
      if (ipiObject0 == ipiObject1)

```

      {

IUnknown *piObjectUnk1 = NULL;
if (ipiObject0 == ipiObject1)
        rc = 1;

      }
```vbscript
if (ipiObject0 == ipiObject1)
rc = 1;
      else if (!ipiObject0 || !ipiObject1)
```

      {

rc = 1;
else if (!ipiObject0 || !ipiObject1)
        rc = 0;

      }
else if (!ipiObject0 || !ipiObject1)
rc = 0;
      else if (SUCCEEDED(((IUnknown*)ipiObject0)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk0)) &&
               SUCCEEDED(((IUnknown*)ipiObject1)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk1)) &&
               piObjectUnk0 == piObjectUnk1)

      {

else if (SUCCEEDED(((IUnknown*)ipiObject0)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk0)) &&
SUCCEEDED(((IUnknown*)ipiObject1)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk1)) &&
piObjectUnk0 == piObjectUnk1)
        rc = 1;

      }

rc = 1;
      if (piObjectUnk0) {piObjectUnk0->Release(#); piObjectUnk0 = NULL;}
```vbscript
```vbscript
      if (piObjectUnk1) {piObjectUnk1->Release(#); piObjectUnk1 = NULL;}

```

```

      return rc;

    }

    //=============================================================================
    //  Test part connected to a part ctr.
    //=============================================================================
    HRESULT CAACloPlacePart::TestConnectedPart(const IUnknown *ipiPartUnk,
                                               const int &iConnectorNumber,
                                               const IUnknown *ipiConnectedPart,
                                               const int &iConnectedConnectorNumber)

    {

const int &iConnectorNumber,
const IUnknown *ipiConnectedPart,
const int &iConnectedConnectorNumber)
      cout <<"============================================================"<< endl;
      cout <<"===    CAACloPlacePart::TestConnectedPart                ==="<< endl;
      cout <<"============================================================"<< endl;

```vbscript
      cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;

```

      cout <<" Connector number " << iConnectorNumber << endl;
      cout <<" ipiConnectedPart = " << ipiConnectedPart << endl;

      cout <<" iConnectedConnectorNumber = " << iConnectedConnectorNumber << endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<" iConnectedConnectorNumber = " << iConnectedConnectorNumber << endl;
HRESULT rc = CATReturnFailure;
      IUnknown *piConnectedCtr = NULL;
      IUnknown *piConnectedPart = NULL;

      IUnknown *piConnectedCtrExpected = NULL;

      CATTry

      {

IUnknown *piConnectedCtrExpected = NULL;
CATTry
        if (SUCCEEDED(GetConnectedPart(ipiPartUnk,
                                       iConnectorNumber,
                                       piConnectedCtr,
                                       piConnectedPart)) &&
            piConnectedCtr &&
            piConnectedPart &&
            AreObjectsEqual(piConnectedPart, ipiConnectedPart))

        {
piConnectedPart)) &&
piConnectedCtr &&
piConnectedPart &&
AreObjectsEqual(piConnectedPart, ipiConnectedPart))
          cout <<" piConnectedCtr = " << piConnectedCtr << endl;

          if (SUCCEEDED(GetPartConnector(ipiConnectedPart,
                                         iConnectedConnectorNumber,
                                         piConnectedCtrExpected)) &&
              piConnectedCtrExpected)

          {

iConnectedConnectorNumber,
piConnectedCtrExpected)) &&
piConnectedCtrExpected)
            cout <<" piConnectedCtrExpected = " << piConnectedCtrExpected << endl;
```vbscript
            if (AreObjectsEqual(piConnectedCtr, piConnectedCtrExpected))

```

              rc = CATReturnSuccess;

          }
        } // End if valid ctr.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::TestConnectedPart *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piConnectedCtr) {piConnectedCtr->Release(#); piConnectedCtr = NULL;}
```vbscript
```vbscript
      if (piConnectedPart) {piConnectedPart->Release(#); piConnectedPart = NULL;}
      if (piConnectedCtrExpected) {piConnectedCtrExpected->Release(#); piConnectedCtrExpected = NULL;}

```

```

      cout << "CAACloPlacePart::TestConnectedPart rc = " << rc << endl;
      return rc;

    }

[Top] Parts in Space CAACloPlacePart places a valve and a tube in space. The valve is placed by the method PlacePartInSpace. PlacePartInSpace first performs setup necessary for placing any part. It gets a tubing application object and derives a CATIPspPlacePartOnRun interface object from the application object. It calls GetChildObject to find the tubing work package (TubingWP.1) which is a child of the data model's root product. It finds the tubing line in TubingWP.1 using the method GetALogicalLine. Both GetChildObject and GetALogicalLine are part of CAAPspBaseEnvProtected.  After accomplishing it's setup duties PlacePartInSpace begins it's major work of placing a valve. The first step is to find the correct valve in the catalog. The CATIPspPlacePartOnRun method GetReferencePartFromCatalog is used to find a reference part in the catalog. GetReferencePartFromCatalog takes standard as an input to help decode attribute values. It also can accept a specification ("spec"). In the sample the spec is set to null so no specification is used. If spec is set the catalog search will be limited to parts that meet the given specification. Part type and part number are the key arguments that define the part which is being looked for. The parent product is also sent to GetReferencePartFromCatalog. This helps GetReferencePartFromCatalog decode various names more efficiently. The found reference product is returned in the argument, piReferencePart. And the corresponding catalog part name is returned in the last argument, uCatalogPartName.  The second part placement step is to position and properly connect an instance product in the data model. This is accomplished using PlacePartInSpace. PlacePartInSpace accepts the same standard for input as was used for GetReferencePartFromCatalog. It accepts a function type which tracks the purpose of the instance part. The reference part is sent to PlacePartInSpace to define the part being placed. The logical line defines the tubing line into which the new part will become a member. The new part ID can be specified. In the sample code the ID is null which instructs the part placement engine to generate the part ID according to it's preset rules. Up direction, horizontal orientation and position all define how the new part is positioned. The new instance part is returned in piInstancePart.  Catalog part name returned by GetReferencePartFromCatalog needs to be set on the new part. Once the new part is placed the PlacePartInSpace tests part connector data to ensure that the part is positioned correctly. Connector data is tested using the TestPartConnectorData method.  The code for PlacePartInSpace is shown below.

    //=============================================================================
    //  Place parts in space.
    //=============================================================================
    HRESULT CAACloPlacePart::PlacePartInSpace(#)
    {
HRESULT CAACloPlacePart::PlacePartInSpace(#)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPlacePart::PlacePartInSpace              ==="<< endl;

      cout <<"============================================================"<< endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<"============================================================"<< endl;
HRESULT rc = CATReturnFailure;
      CATObject *piAppObject = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;

      IUnknown *piReferencePart = NULL;
      CATIProduct *piParentProduct = NULL;

      CATIPspLogicalLine *piLogicalLine = NULL;
      IUnknown *piInstancePart = NULL;

      CATUnicodeString uCatalogPartName = "";

      CATUnicodeString uPlacePartErrorMessage;
      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "";

      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uFunctionType;
      CATUnicodeString uPlacedPartID;
      CATMathDirection upDirection;

      CATMathDirection horizontalOrientation;
      CATMathPoint position;

      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;

      CATMathDirection ctrUp;

      CATTry

      {
        // Get application object.
CATMathDirection ctrUp;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
            SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {

```vbscript
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

```cpp
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");

```

          cout << "piParentProduct = " << piParentProduct << endl;

```vbscript
          piLogicalLine = GetALogicalLine(piParentProduct);

```

          cout << "piLogicalLine = " << piLogicalLine << endl;

```

          // Get reference part
          //uPartType = "CATTubControlValve";
cout << "piLogicalLine = " << piLogicalLine << endl;
          uPartType = ""; // Null string option used to search entire catalog.
          cout << "Part type null" << endl;

          uPartNumber = "V_BALL-TF-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                         uSpecName,
                                                         uPartType,
                                                         uPartNumber,
                                                         piParentProduct,
                                                         piReferencePart,
                                                         uCatalogPartName);

          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

          if (SUCCEEDED(rc) &&
              piReferencePart)

          {

            // Place part in space.
```cpp
if (SUCCEEDED(rc) &&
piReferencePart)
            uFunctionType = "CATTubControlValveFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine

            upDirection.SetCoord(0, 0, 1); // Part up direction parallel to z-axis.
            horizontalOrientation.SetCoord(0,1,0); // Align part parallel to y-axis.

            position.SetCoord(1000,2000,4000); // Position part at (1000, 2000, 4000) in mm.
            rc = piPlacePart->PlacePartInSpace (uStandard,
                                                uFunctionType,
                                                piReferencePart,
                                                piParentProduct,
                                                piLogicalLine,
                                                uPlacedPartID,
                                                upDirection,
                                                horizontalOrientation,
                                                position,
                                                piInstancePart);

            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
```

            {
```vbscript
              // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
              piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

              // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
              ctrPosition.SetCoord(1014.61,2000,4000);
              ctrAlign.SetCoord(1,0,0);

              ctrUp.SetCoord(0,0,1);
              rc = TestPartConnectorData(piInstancePart,
                                         1,
                                         piParentProduct,
                                         ctrPosition,
                                         ctrAlign,
                                         ctrUp);

```vbscript
              if (SUCCEEDED(rc))

```

              {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                ctrPosition.SetCoord(985.395,2000,4000);

                ctrAlign.SetCoord(-1,0,0);
                ctrUp.SetCoord(0,0,1);

                rc = TestPartConnectorData(piInstancePart,
                                           2,
                                           piParentProduct,
                                           ctrPosition,
                                           ctrAlign,
                                           ctrUp);

              }
            }

ctrAlign,
ctrUp);
            else

            {
              rc = CATReturnFailure;
            }
          }
else
rc = CATReturnFailure;
```vbscript
          if (FAILED(rc))

```

          {

```vbscript
if (FAILED(rc))
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
```

          }
        } // End if valid place part object.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{
CATCatch (CATError, pError)
        cout << "CAACloPlacePart::PlacePartInSpace *** Error Caught ***" << endl;

        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

rc = CATReturnError(pError);
      CATEndTry;

      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```vbscript
```vbscript
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

      cout << "CAACloPlacePart::PlacePartInSpace rc = " << rc << endl;
      return rc;

    }

cout << "CAACloPlacePart::PlacePartInSpace rc = " << rc << endl;
return rc;
After CAACloPlacePart places a valve in space it places a tube in space. The tube is placed by the method RouteStringPartInSpace. RouteStringPartInSpace is very similar to PlacePartInSpace. A minor difference is that RouteStringPartInSpace finds a tube in the catalog instead of a valve. Another relatively minor difference is that RouteStringPartInSpace sets an ID for the new part using the uPlacedPartID argument. The major difference is that RouteStringPartInSpace must define the tube node points and bend radii. The bend radii are defined with a list of double values that are interpretted as millimeter lengths. The tube node points are defined by creating a part and creating points in the new part. Connector data is tested using the TestPartConnectorData method.  The code for RouteStringPartInSpace is shown below.

    //=============================================================================
    //  Place string parts in space.
    //=============================================================================
After CAACloPlacePart places a valve in space it places a tube in space. The tube is placed by the method RouteStringPartInSpace. RouteStringPartInSpace is very similar to PlacePartInSpace. A minor difference is that RouteStringPartInSpace finds a tube in the catalog instead of a valve. Another relatively minor difference is that RouteStringPartInSpace sets an ID for the new part using the uPlacedPartID argument. The major difference is that RouteStringPartInSpace must define the tube node points and bend radii. The bend radii are defined with a list of double values that are interpretted as millimeter lengths. The tube node points are defined by creating a part and creating points in the new part. Connector data is tested using the TestPartConnectorData method.  The code for RouteStringPartInSpace is shown below.
    HRESULT CAACloPlacePart::RouteStringPartInSpace(#)

    {
HRESULT CAACloPlacePart::RouteStringPartInSpace(#)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPlacePart::RouteStringPartInSpace        ==="<< endl;

      cout <<"============================================================"<< endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<"============================================================"<< endl;
HRESULT rc = CATReturnFailure;
      CATObject *piAppObject = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;

      IUnknown *piReferencePart = NULL;
      CATIProduct *piParentProduct = NULL;

      CATIPspLogicalLine *piLogicalLine = NULL;
      CATIUnknownList *piListPoints = NULL;

      IUnknown *piInstancePart = NULL;
      CATIAProducts *piParentProducts = NULL;

      CATIAProduct *piPartForPointsProduct = NULL;
      CATBaseDispatch *piPartForPointsShape = NULL;

      CATIAPartDocument *piPartForPointsDoc = NULL;
      CATIAPart *piPartForPoints = NULL;

      CATIAFactory *piShapeFactory = NULL;
      CATIAHybridShapeFactory *piHybridShapeFactory = NULL;

      CATIAHybridShapePointCoord *piPoint = NULL;
      CATIUnknownListImpl *piListImpl = NULL;

      CATUnicodeString uCatalogPartName = "";

      CATUnicodeString uPlacePartErrorMessage;
      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "";

      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uDocumentType;
      CATBSTR documentTypeBSTR;
      CATBSTR partNumberBSTR;

      CATUnicodeString uFunctionType;
      CATUnicodeString uPlacedPartID;
      CATMathDirection firstPointUpDirection;
      CATListOfDouble listBendRadii;
      CATMathPoint ctrPosition;

      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;

      CATTry

      {
        // Get application object.
CATMathDirection ctrUp;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
            SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {

```vbscript
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

```cpp
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");

```

          cout << "piParentProduct = " << piParentProduct << endl;

```vbscript
          piLogicalLine = GetALogicalLine(piParentProduct);

```

          cout << "piLogicalLine = " << piLogicalLine << endl;

```

          // Get reference part
piLogicalLine = GetALogicalLine(piParentProduct);
cout << "piLogicalLine = " << piLogicalLine << endl;
          uPartType = "CATTubBendableTube";

          uPartNumber = "TUBE-BENDABLE-TIV-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                         uSpecName,
                                                         uPartType,
                                                         uPartNumber,
                                                         piParentProduct,
                                                         piReferencePart,
                                                         uCatalogPartName);

          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

          if (SUCCEEDED(rc) &&
              piReferencePart)

          {

            // Create points for bendable routing.
```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
            if (piParentProduct &&
```cpp
                SUCCEEDED(piParentProduct->QueryInterface(IID_CATIAProducts,(void**)&piParentProducts)))
```

```

            {

```vbscript
if (piParentProduct &&
```cpp
SUCCEEDED(piParentProduct->QueryInterface(IID_CATIAProducts,(void**)&piParentProducts)))
```

              cout << "piParentProducts = " << piParentProducts << endl;

```

              // Create part to hold points.
cout << "piParentProducts = " << piParentProducts << endl;
              uDocumentType = "Part";

              uDocumentType.ConvertToBSTR(&documentTypeBSTR);
              uPartNumber = "PartForPointsTubing";
              uPartNumber.ConvertToBSTR(&partNumberBSTR);

              HRESULT rcPointsPart = piParentProducts->AddNewComponent(documentTypeBSTR,
                                                                       partNumberBSTR,
                                                                       piPartForPointsProduct);

              cout << "rcPointsPart = " << rcPointsPart << endl;
              cout << "piPartForPointsProduct = " << piPartForPointsProduct << endl;

```vbscript
              if (piPartForPointsProduct)

```

              {
cout << "rcPointsPart = " << rcPointsPart << endl;
cout << "piPartForPointsProduct = " << piPartForPointsProduct << endl;
if (piPartForPointsProduct)
                piPartForPointsProduct->GetMasterShapeRepresentation(TRUE, piPartForPointsShape);

                cout << "piPartForPointsShape = " << piPartForPointsShape << endl;
                if (piPartForPointsShape &&
```cpp
                    SUCCEEDED(piPartForPointsShape->QueryInterface(IID_CATIAPartDocument,(void**)&piPartForPointsDoc)))

```

                {

cout << "piPartForPointsShape = " << piPartForPointsShape << endl;
if (piPartForPointsShape &&
```cpp
SUCCEEDED(piPartForPointsShape->QueryInterface(IID_CATIAPartDocument,(void**)&piPartForPointsDoc)))
```

                  cout << "piPartForPointsDoc = " << piPartForPointsDoc << endl;
                  piPartForPointsDoc->get_Part(piPartForPoints);

                  cout << "piPartForPoints = " << piPartForPoints << endl;
```vbscript
                  if (piPartForPoints)

```

                  {

cout << "piPartForPoints = " << piPartForPoints << endl;
if (piPartForPoints)
                    piPartForPoints->get_HybridShapeFactory(piShapeFactory);
                    if (piShapeFactory)
                      piShapeFactory->QueryInterface(IID_CATIAHybridShapeFactory,(void**)&piHybridShapeFactory);

                    cout << "piHybridShapeFactory = " << piHybridShapeFactory << endl;
```vbscript
                    if (piHybridShapeFactory)

```

                    {

cout << "piHybridShapeFactory = " << piHybridShapeFactory << endl;
if (piHybridShapeFactory)
```vbscript
```cpp
                      piListImpl = new CATIUnknownListImpl(#);
                      if (piListImpl)

```

```

                        piListImpl->QueryInterface (IID_CATIUnknownList,(void**)&piListPoints);
                      cout << "piListPoints = " << piListPoints << endl;

```vbscript
                      if (piListPoints)

```

                      {
piListImpl->QueryInterface (IID_CATIUnknownList,(void**)&piListPoints);
cout << "piListPoints = " << piListPoints << endl;
if (piListPoints)
                        double points[4][3] = { {-1500.0, -1000.0, 0.0},

                                                {-2500.0, -1000.0, 0.0},
                                                {-2500.0, 500.0, 0.0},
                                                {-3500.0, 500.0, 0.0} };

                        for (unsigned int iiPoint = 0; iiPoint < 4; iiPoint++)
                        {

```vbscript
for (unsigned int iiPoint = 0; iiPoint < 4; iiPoint++)
                          cout << "iiPoint = " << iiPoint << endl;
                          piHybridShapeFactory->AddNewPointCoord(points[iiPoint][0],
                                                                 points[iiPoint][1],
                                                                 points[iiPoint][2],
                                                                 piPoint);

                          cout << "piPoint = " << piPoint << endl;
                          piListPoints->Add(iiPoint, piPoint);

                          if (piPoint) {piPoint->Release(#); piPoint = NULL;}
```

                        } // End loop on points.

                      } // End valid list of points.
                    } // End valid shape factory.
                  } // End valid part for points.
                } // End valid shape.
              } // End valid part for points product.

            } // End valid parent product.

            // Place part in space.
            uFunctionType = "CATTubTubeFunction";
            uPlacedPartID = "TestTubeWithBends";

            firstPointUpDirection.SetCoord(0, 0, 1); // Up direction parallel to z-axis.
            listBendRadii.RemoveAll(#);

            listBendRadii.Append(25.4); // Bend radius in mm (1in).
            listBendRadii.Append(25.4);

            rc = piPlacePart->RouteStringPartInSpace (uStandard,
                                                      uFunctionType,
                                                      piReferencePart,
                                                      piParentProduct,
                                                      piLogicalLine,
                                                      uPlacedPartID,
                                                      firstPointUpDirection,
                                                      piListPoints,
                                                      listBendRadii,
                                                      piInstancePart);

            cout << "piInstancePart = " << piInstancePart << endl;

```vbscript
            if (piInstancePart)

```

            {
```vbscript
              // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
              piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

              // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
              ctrPosition.SetCoord(-1500,-1000,0);
              ctrAlign.SetCoord(1,0,0);

              ctrUp.SetCoord(0,0,1);
              rc = TestPartConnectorData(piInstancePart,
                                         1,
                                         piParentProduct,
                                         ctrPosition,
                                         ctrAlign,
                                         ctrUp);

```vbscript
              if (SUCCEEDED(rc))

```

              {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                ctrPosition.SetCoord(-3500,500,0);

                ctrAlign.SetCoord(-1,0,0);
                ctrUp.SetCoord(0,0,1);

                rc = TestPartConnectorData(piInstancePart,
                                           2,
                                           piParentProduct,
                                           ctrPosition,
                                           ctrAlign,
                                           ctrUp);

              }
            }

ctrAlign,
ctrUp);
            else

            {
              rc = CATReturnFailure;
            }
          }
else
rc = CATReturnFailure;
```vbscript
          if (FAILED(rc))

```

          {

```vbscript
if (FAILED(rc))
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
```

          }
        } // End if valid place part object.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{
CATCatch (CATError, pError)
        cout << "CAACloPlacePart::RouteStringPartInSpace *** Error Caught ***" << endl;

        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

rc = CATReturnError(pError);
      CATEndTry;

      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```vbscript
```vbscript
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piListPoints) {piListPoints->Release(#); piListPoints = NULL;}
      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
      if (piParentProducts) {piParentProducts->Release(#); piParentProducts = NULL;}
      if (piPartForPointsProduct) {piPartForPointsProduct->Release(#); piPartForPointsProduct = NULL;}
      if (piPartForPointsShape) {piPartForPointsShape->Release(#); piPartForPointsShape = NULL;}
      if (piPartForPointsDoc) {piPartForPointsDoc->Release(#); piPartForPointsDoc = NULL;}
      if (piPartForPoints) {piPartForPoints->Release(#); piPartForPoints = NULL;}
      if (piShapeFactory) {piShapeFactory->Release(#); piShapeFactory = NULL;}
      if (piHybridShapeFactory) {piHybridShapeFactory->Release(#); piHybridShapeFactory = NULL;}
      if (piPoint) {piPoint->Release(#); piPoint = NULL;}
      if (piListImpl) {piListImpl->Release(#); piListImpl = NULL;}

```

```

      cout << "CAACloPlacePart::RouteStringPartInSpace rc = " << rc << endl;
      return rc;

    }

[Top] Parts on Run Segments The CAACloPlacePart method PlacePartOnRunSegment places parts on run segments. PlacePartOnRunSegment performs the same setup as PlacePartInSpace. In addition it finds Run-0043, which is a child of TubingWP.1, using the GetChildObject. PlacePartOnRunSegment places a union and a tube two segments of Run-0043. The union is flipped twice to test the FlipPlacedPart method. The placement of the tube causes the union and tube to be connected.  Parts are placed on run segments using the CATIPspPlacePartOnRun method PlacePartOnRunSegment. The major change from placing a part in space is that a run segment is needed. The list of run segments is retrieved with CATIArrSegmentsString::ListSegments. The union is placed on the first segment and the tube is placed on the second segment. Union is flipped using FlipPlacedPart method of CATIPspPlacePartOnRun. The run segment defines the part up direction and horizontal alignment. Position data is still sent to fix the parts position on the segment. Connector data is tested using the TestPartConnectorData method and the connection is tested with the TestConnectedPart method.

    //=============================================================================
    //  Place parts on run segments.
    //=============================================================================
    HRESULT CAACloPlacePart::PlacePartOnRunSegment(#)
    {
HRESULT CAACloPlacePart::PlacePartOnRunSegment(#)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPlacePart::PlacePartOnRunSegment         ==="<< endl;

      cout <<"============================================================"<< endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<"============================================================"<< endl;
HRESULT rc = CATReturnFailure;
      CATObject *piAppObject = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;

      CATIProduct *piParentProduct = NULL;
      CATIPspLogicalLine *piLogicalLine = NULL;

      CATIArrSegmentsString *piRun = NULL;
      IUnknown *piReferencePart = NULL;

      CATIArrSegment *piSegment = NULL;
      IUnknown *piInstancePart = NULL;

      IUnknown *piConnectedPart = NULL;
      IUnknown *piInstanceUnion = NULL;

      CATUnicodeString uCatalogPartName = "";

      CATUnicodeString uPlacePartErrorMessage;
      CATListValCATBaseUnknown_var listOfSegments;
      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "";

      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uFunctionType;
      CATUnicodeString uPlacedPartID;
      CATMathPoint position;

      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;
      CATIArrSegment_var spSegment;

      CATTry

      {
        // Get application object.
CATIArrSegment_var spSegment;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
            SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {

```vbscript
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

```cpp
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");

```

          cout << "piParentProduct = " << piParentProduct << endl;

```

          //piLogicalLine = GetALogicalLine(piParentProduct);
```cpp
piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
cout << "piParentProduct = " << piParentProduct << endl;
          cout << "piLogicalLine = " << piLogicalLine << endl;

```cpp
          piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0043", piParentProduct);

```

          cout << "piRun = " << piRun << endl;

          if (piRun)
```

          {

cout << "piRun = " << piRun << endl;
if (piRun)
            piRun->ListSegments(listOfSegments);
            cout << "listOfSegments.Size(#) = " << listOfSegments.Size(#) << endl;

            do

            { // Dummy loop to allow easy exit on fail.
              // ==============================================================================
              // Place union on segment
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubUnion";
              uPartNumber = "UNION-BULKHEAD-FFSM-16";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                if (listOfSegments.Size(#) >= 1)
```

                {
piReferencePart)
if (listOfSegments.Size(#) >= 1)
                  spSegment = listOfSegments[1];

                  if (!!spSegment)
                    spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);

                  cout << "piSegment = " << piSegment << endl;

                }

spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);
cout << "piSegment = " << piSegment << endl;
```vbscript
                if (piSegment)

```

                {

                  // Place part on run segment.
```cpp
if (piSegment)
                  uFunctionType = "CATTubTubeFunction";
                  uPlacedPartID = ""; // Null string uses name generated by PP engine

                  position.SetCoord(-200,-800,0); // in mm.
                  rc = piPlacePart->PlacePartOnRunSegment (uStandard,
                                                           uFunctionType,
                                                           piReferencePart,
                                                           piSegment,
                                                           piLogicalLine,
                                                           uPlacedPartID,
                                                           position,
                                                           piInstancePart);

                  cout << "piInstancePart = " << piInstancePart << endl;

                  if (piInstancePart)
```

                  {
```vbscript
      	         // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                    piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                    piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceUnion);

                    // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceUnion);
                    ctrPosition.SetCoord(-171.006,-800,0);
                    ctrAlign.SetCoord(1,0,0);

                    ctrUp.SetCoord(0,0,1);

                    cout << "Union after placement" << endl;

                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-228.994,-800,0);

                      ctrAlign.SetCoord(-1,0,0);
                      ctrUp.SetCoord(0,0,1);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                      // ------------------------------------------
                      // Test flip of union.
                      // ------------------------------------------
                      if (SUCCEEDED(rc))
                      {
                        // Flip first time.
```vbscript
if (SUCCEEDED(rc))
```vbscript
```vbscript
                        rc = piPlacePart->FlipPlacedPart(piInstancePart);

                        if (SUCCEEDED(rc))
```

```

```

                        {
rc = piPlacePart->FlipPlacedPart(piInstancePart);
```vbscript
if (SUCCEEDED(rc))
```

                          cout << "Union after first flip" << endl;

                          // Test part connectors.
```vbscript
if (SUCCEEDED(rc))
cout << "Union after first flip" << endl;
                          ctrPosition.SetCoord(-171.006,-800,0);
                          ctrAlign.SetCoord(1,0,0);

                          ctrUp.SetCoord(0,0,1);
                          rc = TestPartConnectorData(piInstancePart,
                                                     2,
                                                     piParentProduct,
                                                     ctrPosition,
                                                     ctrAlign,
                                                     ctrUp);

                          if (SUCCEEDED(rc))
```

                          {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                            ctrPosition.SetCoord(-228.994,-800,0);

                            ctrAlign.SetCoord(-1,0,0);
                            ctrUp.SetCoord(0,0,1);

                            rc = TestPartConnectorData(piInstancePart,
                                                       1,
                                                       piParentProduct,
                                                       ctrPosition,
                                                       ctrAlign,
                                                       ctrUp);

```vbscript
                            if (SUCCEEDED(rc))

```

                            {
                              // Flip second time. Union should be back to original flip
ctrUp);
if (SUCCEEDED(rc))
```vbscript
```vbscript
                              rc = piPlacePart->FlipPlacedPart(piInstancePart);

                              if (SUCCEEDED(rc))

```

```

                              {
rc = piPlacePart->FlipPlacedPart(piInstancePart);
```vbscript
if (SUCCEEDED(rc))
```

                                cout << "Union after second flip" << endl;

                                // Test part connectors.
```vbscript
if (SUCCEEDED(rc))
cout << "Union after second flip" << endl;
                                ctrPosition.SetCoord(-171.006,-800,0);
                                ctrAlign.SetCoord(1,0,0);

                                ctrUp.SetCoord(0,0,1);
                                rc = TestPartConnectorData(piInstancePart,
                                                           1,
                                                           piParentProduct,
                                                           ctrPosition,
                                                           ctrAlign,
                                                           ctrUp);

                                if (SUCCEEDED(rc))
```

                                {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                                  ctrPosition.SetCoord(-228.994,-800,0);

                                  ctrAlign.SetCoord(-1,0,0);
                                  ctrUp.SetCoord(0,0,1);

                                  rc = TestPartConnectorData(piInstancePart,
                                                             2,
                                                             piParentProduct,
                                                             ctrPosition,
                                                             ctrAlign,
                                                             ctrUp);

                                } // End if connector test succeeded

                              } // End if flip succeeded
                            } // End if connector test succeeded.
                          } // End if connector test succeeded
                        } // End if flip succeeded
                      } // End if connector test succeeded.

                    }
                  }

                  else
                  {
                    rc = CATReturnFailure;
                  }
                } // End if valid segment.
              } // End if valid reference part.

rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```

```vbscript
```vbscript
              if (piSegment) {piSegment->Release(#); piSegment = NULL;}
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

              // ==============================================================================
              // Place bendable on segment
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubBendableTube";
              uPartNumber = "TUBE-BENDABLE-TIV-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                if (listOfSegments.Size(#) >= 2)
```

                {
piReferencePart)
if (listOfSegments.Size(#) >= 2)
                  spSegment = listOfSegments[2];

                  if (!!spSegment)
                    spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);

                  cout << "piSegment = " << piSegment << endl;

                }

spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);
cout << "piSegment = " << piSegment << endl;
```vbscript
                if (piSegment)

```

                {

                  // Place part on run segment.
```cpp
if (piSegment)
                  uFunctionType = "CATTubTubeFunction";
                  uPlacedPartID = ""; // Null string uses name generated by PP engine

                  position.SetCoord(-800,-600,0); // in mm.
                  rc = piPlacePart->PlacePartOnRunSegment (uStandard,
                                                           uFunctionType,
                                                           piReferencePart,
                                                           piSegment,
                                                           piLogicalLine,
                                                           uPlacedPartID,
                                                           position,
                                                           piInstancePart);

                  cout << "piInstancePart = " << piInstancePart << endl;

                  if (piInstancePart)
```

                  {
```vbscript
                    // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                    piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                    // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                    ctrPosition.SetCoord(-228.994,-800,0);
                    ctrAlign.SetCoord(1,0,0);

                    ctrUp.SetCoord(0,0,1);
                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                      rc = TestConnectedPart(piInstancePart,
```

                                             1,
                                             piInstanceUnion,
                                             2);

```vbscript
                      if (SUCCEEDED(rc))

```

                      {
piInstanceUnion,
2);
if (SUCCEEDED(rc))
                        ctrPosition.SetCoord(-1600,-1500,0);

                        ctrAlign.SetCoord(1,0,0);
                        ctrUp.SetCoord(0,0,1);

                        rc = TestPartConnectorData(piInstancePart,
                                                   2,
                                                   piParentProduct,
                                                   ctrPosition,
                                                   ctrAlign,
                                                   ctrUp);

                      } // End if connected part test succeeded.

                    } // End if ctr 1 test succeeded.
                  } // End if valid instance part.
ctrUp);
                  else

                  {
                    rc = CATReturnFailure;
                  }
                } // End if valid segment.

              } // End if valid reference part.
            } while (0); // End dummy loop for easy exit on fail.
          } // End if valid run.

          if (FAILED(rc))
          {

```vbscript
if (FAILED(rc))
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
```

          }
        } // End if valid place part object.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::PlacePartOnRunSegment *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```vbscript
```vbscript
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piRun) {piRun->Release(#); piRun = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (piSegment) {piSegment->Release(#); piSegment = NULL;}
      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
      if (piConnectedPart) {piConnectedPart->Release(#); piConnectedPart = NULL;}
      if (piInstanceUnion) {piInstanceUnion->Release(#); piInstanceUnion = NULL;}

```

```

      cout << "CAACloPlacePart::PlacePartOnRunSegment rc = " << rc << endl;
      return rc;

    }

[Top] Parts on Run Nodes The CAACloPlacePart method PlacePartOnRunNode places parts on run nodes. Again setup is very similar to previous methods. Run-044 is used for part placement. CATIArrSegmentsString::ListNodes finds the run nodes. A valve is placed on the first node which is an extremity (or exterior) node at the beginning of the run. An elbow is placed on the fifth node which is interior or a corner. A bendable tube is placed on the second node. It expands to meet the valve and the union and is connected to them. The nodes are the only position data needed since they provide location and the connected segments provide up direction and horizontal orientation. Connector data is tested using the TestPartConnectorData method and the connections are tested with the TestConnectedPart method. Run-044 is broken at an elbow and newly formed Run is connected to the elbow using BreakAndTrimRuns and ConnectRunToPart methods of CATIPspPlacePartOnRun respectively.

    //=============================================================================
    //  Place parts on run nodes.
    //=============================================================================
    HRESULT CAACloPlacePart::PlacePartOnRunNode(#)
    {
HRESULT CAACloPlacePart::PlacePartOnRunNode(#)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPlacePart::PlacePartOnRunNode            ==="<< endl;

      cout <<"============================================================"<< endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<"============================================================"<< endl;
HRESULT rc = CATReturnFailure;
      CATObject *piAppObject = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;

      CATIProduct *piParentProduct = NULL;
      CATIPspLogicalLine *piLogicalLine = NULL;

      CATIArrSegmentsString *piRun = NULL;
      IUnknown *piReferencePart = NULL;

      CATIArrNode *piNode = NULL;
      IUnknown *piInstancePart = NULL;

      IUnknown *piConnectedPart = NULL;
      IUnknown *piInstanceValve = NULL;

      IUnknown *piInstanceElbow = NULL;

      CATUnicodeString uCatalogPartName = "";

      CATUnicodeString uPlacePartErrorMessage;
      CATListValCATBaseUnknown_var listOfNodes;
      CATUnicodeString uStandard = "SSTL";

      CATUnicodeString uSpecName = "";
      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uFunctionType;

      CATUnicodeString uPlacedPartID;
      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;
      CATIArrNode_var spNode;

      CATTry

      {
        // Get application object.
CATIArrNode_var spNode;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
            SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {

```vbscript
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

```cpp
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");

```

          cout << "piParentProduct = " << piParentProduct << endl;

```

          //piLogicalLine = GetALogicalLine(piParentProduct);
```cpp
piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
cout << "piParentProduct = " << piParentProduct << endl;
          cout << "piLogicalLine = " << piLogicalLine << endl;

```cpp
          piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0044", piParentProduct);

```

          cout << "piRun = " << piRun << endl;

          if (piRun)
```

          {

cout << "piRun = " << piRun << endl;
if (piRun)
            piRun->ListNodes(listOfNodes);
            cout << "listOfNodes.Size(#) = " << listOfNodes.Size(#) << endl;

            do

            { // Dummy loop to allow easy exit on fail.
              // ==============================================================================
              // Place valve on exterior node
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubControlValve";
              uPartNumber = "V_BALL-TF-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                if (listOfNodes.Size(#) >= 1)
```

                {
piReferencePart)
if (listOfNodes.Size(#) >= 1)
                  spNode = listOfNodes[1];

                  if (!!spNode)
                    spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);

                  cout << "piNode = " << piNode << endl;

                }

spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
cout << "piNode = " << piNode << endl;
```vbscript
                if (piNode)

```

                {

```cpp
if (piNode)
                  uFunctionType = "CATTubControlValveFunction";
                  uPlacedPartID = ""; // Null string uses name generated by PP engine

                  rc = piPlacePart->PlacePartOnRunNode(uStandard,
                                                       uFunctionType,
                                                       piReferencePart,
                                                       piNode,
                                                       piLogicalLine,
                                                       uPlacedPartID,
                                                       piInstancePart);

                  cout << "piInstancePart = " << piInstancePart << endl;

                  if (piInstancePart)
```

                  {
```vbscript
    		   // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                    piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                    piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceValve);

                    // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceValve);
                    ctrPosition.SetCoord(-500,800,0);

                    ctrAlign.SetCoord(-1,0,0);
                    ctrUp.SetCoord(0,0,1);

                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-470.79,800,0);

                      ctrAlign.SetCoord(1,0,0);
                      ctrUp.SetCoord(0,0,1);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }

ctrAlign,
ctrUp);
                  else

                  {
                    rc = CATReturnFailure;
                  }
                } // End if valid segment.
              } // End if valid reference part.

rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```

```vbscript
```vbscript
              if (piNode) {piNode->Release(#); piNode = NULL;}
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

              // ==============================================================================
              // Place elbow on interior node.
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubNonReducingElbow";
              uPartNumber = "ELBOW-90-BULKHEAD-FFSM-16";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                if (listOfNodes.Size(#) >= 5)
```

                {
piReferencePart)
if (listOfNodes.Size(#) >= 5)
                  spNode = listOfNodes[5];

                  if (!!spNode)
                    spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);

                  cout << "piNode = " << piNode << endl;

                }

spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
cout << "piNode = " << piNode << endl;
```vbscript
                if (piNode)

```

                {

```cpp
if (piNode)
                  uFunctionType = "CATTubTubeFunction";
                  uPlacedPartID = ""; // Null string uses name generated by PP engine

                  rc = piPlacePart->PlacePartOnRunNode(uStandard,
                                                       uFunctionType,
                                                       piReferencePart,
                                                       piNode,
                                                       piLogicalLine,
                                                       uPlacedPartID,
                                                       piInstancePart);

                  cout << "piInstancePart = " << piInstancePart << endl;

                  if (piInstancePart)
```

                  {
```vbscript
    		   // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                    piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                    piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceElbow);

                    // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceElbow);
                    ctrPosition.SetCoord(-741.3,2000,1800);

                    ctrAlign.SetCoord(-1,0,0);
                    ctrUp.SetCoord(0,0,-1);

                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-700,2063.53,1800);

                      ctrAlign.SetCoord(0,1,0);
                      ctrUp.SetCoord(0,0,-1);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }

ctrAlign,
ctrUp);
                  else

                  {
                    rc = CATReturnFailure;
                  }
                } // End if valid segment.
              } // End if valid reference part.

rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```

```vbscript
```vbscript
              if (piNode) {piNode->Release(#); piNode = NULL;}
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

              // ==============================================================================
              // Place bendable on node.
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubBendableTube";
              uPartNumber = "TUBE-BENDABLE-TIV-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                if (listOfNodes.Size(#) >= 2)
```

                {
piReferencePart)
if (listOfNodes.Size(#) >= 2)
                  spNode = listOfNodes[2];

                  if (!!spNode)
                    spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);

                  cout << "piNode = " << piNode << endl;

                }

spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
cout << "piNode = " << piNode << endl;
```vbscript
                if (piNode)

```

                {

```cpp
if (piNode)
                  uFunctionType = "CATTubTubeFunction";
                  uPlacedPartID = ""; // Null string uses name generated by PP engine

                  rc = piPlacePart->PlacePartOnRunNode(uStandard,
                                                       uFunctionType,
                                                       piReferencePart,
                                                       piNode,
                                                       piLogicalLine,
                                                       uPlacedPartID,
                                                       piInstancePart);

                  cout << "piInstancePart = " << piInstancePart << endl;

                  if (piInstancePart)
```

                  {
```vbscript
                    // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                    piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                    // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                    ctrPosition.SetCoord(-500,800,0);
                    ctrAlign.SetCoord(1,0,0);

                    ctrUp.SetCoord(0,0,1);
                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                      rc = TestConnectedPart(piInstancePart,
```

                                             1,
                                             piInstanceValve,
                                             1);

```vbscript
                      if (SUCCEEDED(rc))

```

                      {
piInstanceValve,
1);
if (SUCCEEDED(rc))
                        ctrPosition.SetCoord(-741.3,2000,1800);

                        ctrAlign.SetCoord(1,0,0);
                        ctrUp.SetCoord(0,-1,0);

                        rc = TestPartConnectorData(piInstancePart,
                                                   2,
                                                   piParentProduct,
                                                   ctrPosition,
                                                   ctrAlign,
                                                   ctrUp);

```vbscript
                        if (SUCCEEDED(rc))

```

                        {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                          rc = TestConnectedPart(piInstancePart,
```

                                                 2,
                                                 piInstanceElbow,
                                                 1);

                        } // End if part ctr 2 test succeeded.

                      } // End if part ctr 1 connected part test succeeded
                    } // End if part ctr 1 test succeeded.
                  }
                  else
                  {

                    rc = CATReturnFailure;
                  }
                } // End if valid segment.
              } // End if valid reference part.

              // ==============================================================================
              // Test BreakAndTrimRuns and ConnectRunToPart
              // ==============================================================================
    	    IUnknown *opiRun1 = NULL;
              IUnknown *opiRun2 = NULL;
    	    rc = piPlacePart->BreakAndTrimRuns(piInstanceElbow,
                                       	    opiRun1,
    		                                 opiRun2);
    	    cout << "BreakAndTrimRuns rc = " << rc << endl;

    	    rc = piPlacePart->ConnectRunToPart(opiRun2,piInstanceElbow);
    	    cout << "ConnectRunToPart rc = " << rc << endl;

    	    if (opiRun1) {opiRun1->Release(#); opiRun1 = NULL;}
```vbscript
```vbscript
    	    if (opiRun2) {opiRun2->Release(#); opiRun2 = NULL;}

```

```

            } while (0); // End dummy loop for easy exit on fail.

          } // End if valid run.

          if (FAILED(rc))
          {

```vbscript
if (FAILED(rc))
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
```

          }
        } // End if valid place part object.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::PlacePartOnRunNode *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```vbscript
```vbscript
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piRun) {piRun->Release(#); piRun = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (piNode) {piNode->Release(#); piNode = NULL;}
      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
      if (piConnectedPart) {piConnectedPart->Release(#); piConnectedPart = NULL;}
      if (piInstanceValve) {piInstanceValve->Release(#); piInstanceValve = NULL;}
      if (piInstanceElbow) {piInstanceElbow->Release(#); piInstanceElbow = NULL;}

```

```

      cout << "CAACloPlacePart::PlacePartOnRunNode rc = " << rc << endl;
      return rc;

    }

[Top] Parts on Part Connectors The CAACloPlacePart method PlacePartOnPartConnector places parts on part connectors. Again a very similar set up to previous methods is used. The method begins by placing a valve in space and then a union on one of the valve connectors. The part connector provides all of the position data needed for placement. A further example is provided of placing parts on part connectors of parts on runs. A valve is placed on Segment 5 of Run-044. A union is also placed on this valve. After that a sleeve and a nut are stacked on the union as would be necessary to connect a tube to the union. When the parts are placed on parts connectors they are connected to the existing part. Connector data is tested using the TestPartConnectorData method and the connections are tested with the TestConnectedPart method.

    //=============================================================================
    //  Place parts on part connectors.
    //=============================================================================
    HRESULT CAACloPlacePart::PlacePartOnPartConnector(#)
    {
HRESULT CAACloPlacePart::PlacePartOnPartConnector(#)
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloPlacePart::PlacePartOnPartConnector      ==="<< endl;

      cout <<"============================================================"<< endl;

      HRESULT rc = CATReturnFailure;

      // Interface pointer variables used below in the try section.
cout <<"============================================================"<< endl;
HRESULT rc = CATReturnFailure;
      CATObject *piAppObject = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;

      IUnknown *piReferencePart = NULL;
      CATIProduct *piParentProduct = NULL;

      CATIPspLogicalLine *piLogicalLine = NULL;
      IUnknown *piInstancePart = NULL;

      IUnknown *piInstancePartPrevious = NULL;
      IUnknown *piPlaceOnCtr = NULL;

      CATIArrSegmentsString *piRun = NULL;
      CATIArrSegment *piSegment = NULL;

      CATUnicodeString uCatalogPartName = "";

      CATUnicodeString uPlacePartErrorMessage;
      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "";

      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uFunctionType;
      CATUnicodeString uPlacedPartID;
      CATMathDirection upDirection;

      CATMathDirection horizontalOrientation;
      CATMathPoint position;
      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;

      CATListValCATBaseUnknown_var listOfSegments;
      CATIArrSegment_var spSegment;

      CATTry

      {
        // Get application object.
CATIArrSegment_var spSegment;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
            SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {

```vbscript
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

```cpp
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");

```

          cout << "piParentProduct = " << piParentProduct << endl;

```vbscript
          piLogicalLine = GetALogicalLine(piParentProduct);

```

          cout << "piLogicalLine = " << piLogicalLine << endl;

```cpp
          piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0044", piParentProduct);

```

          cout << "piRun = " << piRun << endl;

          if (piRun)
```

          {

cout << "piRun = " << piRun << endl;
if (piRun)
            piRun->ListSegments(listOfSegments);
            cout << "listOfSegments.Size(#) = " << listOfSegments.Size(#) << endl;

```vbscript
            if (listOfSegments.Size(#) >= 5)

```

            {
piRun->ListSegments(listOfSegments);
cout << "listOfSegments.Size(#) = " << listOfSegments.Size(#) << endl;
if (listOfSegments.Size(#) >= 5)
              spSegment = listOfSegments[5];

              if (!!spSegment)
                spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);

              cout << "piSegment = " << piSegment << endl;

            }
          } // End if valid run.

          if (piSegment)
          {

            do
            { // Dummy loop to allow easy exit on fail.

              // ==============================================================================
              // Place valve in space.
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubControlValve";
              uPartNumber = "V_BALL-TF-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Place part in space.
```cpp
if (SUCCEEDED(rc) &&
piReferencePart)
                uFunctionType = "CATTubControlValveFunction";
                uPlacedPartID = ""; // Null string uses name generated by PP engine

                upDirection.SetCoord(0, 0, 1); // Part up direction parallel to z-axis.
                horizontalOrientation.SetCoord(0,1,0); // Align part parallel to y-axis.

                position.SetCoord(1000,2000,-4000); // Position part at (1000, 2000, 4000) in mm.
                rc = piPlacePart->PlacePartInSpace (uStandard,
                                                    uFunctionType,
                                                    piReferencePart,
                                                    piParentProduct,
                                                    piLogicalLine,
                                                    uPlacedPartID,
                                                    upDirection,
                                                    horizontalOrientation,
                                                    position,
                                                    piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

                if (piInstancePart)
```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(1014.61,2000,-4000);
                  ctrAlign.SetCoord(1,0,0);

                  ctrUp.SetCoord(0,0,1);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                    ctrPosition.SetCoord(985.395,2000,-4000);

                    ctrAlign.SetCoord(-1,0,0);
                    ctrUp.SetCoord(0,0,1);

                    rc = TestPartConnectorData(piInstancePart,
                                               2,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

                  }
                }

ctrAlign,
ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}

```

              piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```vbscript
```vbscript
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

              // ==============================================================================
              // Place union on valve.
              // ==============================================================================
              // Get reference part
              uPartType = "TubingUnion";
              uPartNumber = "UNION-BULKHEAD-TMFL-16-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Get valve ctr 2.
```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                rc = GetPartConnector(piInstancePartPrevious,
                                      2,
                                      piPlaceOnCtr);

                cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

```

                // Place part on connector.
piPlaceOnCtr);
cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;
                uFunctionType = "CATTubTubeFunction";

                uPlacedPartID = ""; // Null string uses name generated by PP engine
                rc = piPlacePart->PlacePartOnPartConnector (uStandard,
                                                            uFunctionType,
                                                            piReferencePart,
                                                            piPlaceOnCtr,
                                                            piLogicalLine,
                                                            uPlacedPartID,
                                                            piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

```vbscript
                if (piInstancePart)

```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(985.395,2000,-4000);
                  ctrAlign.SetCoord(1,0,0);

                  ctrUp.SetCoord(0,0,1);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                    rc = TestConnectedPart(piInstancePart,
```

                                           1,
                                           piInstancePartPrevious,
                                           2);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
piInstancePartPrevious,
2);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(905.639,2000,-4000);

                      ctrAlign.SetCoord(-1,0,0);
                      ctrUp.SetCoord(0,0,1);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }
                }

ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}
```

              piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```vbscript
```vbscript
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
              if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}

```

```

              // ==============================================================================
              // Place valve on run segment.
              // ==============================================================================
              // Get reference part
              uPartType = "CATTubControlValve";
              uPartNumber = "V_BALL-TF-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Place part on segment.
```cpp
if (SUCCEEDED(rc) &&
piReferencePart)
                uFunctionType = "CATTubControlValveFunction";
                uPlacedPartID = ""; // Null string uses name generated by PP engine

                position.SetCoord(-700,3000,1800); // in mm.
                rc = piPlacePart->PlacePartOnRunSegment (uStandard,
                                                         uFunctionType,
                                                         piReferencePart,
                                                         piSegment,
                                                         piLogicalLine,
                                                         uPlacedPartID,
                                                         position,
                                                         piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

                if (piInstancePart)
```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(-700,2985.395,1800);
                  ctrAlign.SetCoord(0,-1,0);

                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
                    ctrPosition.SetCoord(-700,3014.61,1800);

                    ctrAlign.SetCoord(0,1,0);
                    ctrUp.SetCoord(1,0,0);

                    rc = TestPartConnectorData(piInstancePart,
                                               2,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

                  }
                }

ctrAlign,
ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
              if (FAILED(rc)) break;
```vbscript
```vbscript
              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}

```

```

              piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```vbscript
```vbscript
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}

```

```

              // ==============================================================================
              // Place union on valve on run.
              // ==============================================================================
              // Get reference part
              uPartType = "TubingUnion";
              uPartNumber = "UNION-BULKHEAD-TMFL-16-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Get valve ctr 2.
```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                rc = GetPartConnector(piInstancePartPrevious,
                                      2,
                                      piPlaceOnCtr);

                cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

```

                // Place part on connector.
piPlaceOnCtr);
cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;
                uFunctionType = "CATTubTubeFunction";

                uPlacedPartID = ""; // Null string uses name generated by PP engine
                rc = piPlacePart->PlacePartOnPartConnector (uStandard,
                                                            uFunctionType,
                                                            piReferencePart,
                                                            piPlaceOnCtr,
                                                            piLogicalLine,
                                                            uPlacedPartID,
                                                            piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

```vbscript
                if (piInstancePart)

```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(-700,3014.61,1800);
                  ctrAlign.SetCoord(0,-1,0);

                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                    rc = TestConnectedPart(piInstancePart,
```

                                           1,
                                           piInstancePartPrevious,
                                           2);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
piInstancePartPrevious,
2);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-700,3094.366,1800);

                      ctrAlign.SetCoord(0,1,0);
                      ctrUp.SetCoord(1,0,0);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }
                }

ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
              if (FAILED(rc)) break;
```vbscript
```vbscript
              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}

```

```

              piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```vbscript
```vbscript
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
              if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}

```

```

              // ==============================================================================
              // Place sleeve on union.
              // ==============================================================================
              // Get reference part
              uPartType = "TubingBNutSleeve";
              uPartNumber = "SLEEVE-CSFR-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Get union ctr 2.
```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                rc = GetPartConnector(piInstancePartPrevious,
                                      2,
                                      piPlaceOnCtr);

                cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

```

                // Place part on connector.
piPlaceOnCtr);
cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;
                uFunctionType = "CATTubTubeFunction";

                uPlacedPartID = ""; // Null string uses name generated by PP engine
                rc = piPlacePart->PlacePartOnPartConnector (uStandard,
                                                            uFunctionType,
                                                            piReferencePart,
                                                            piPlaceOnCtr,
                                                            piLogicalLine,
                                                            uPlacedPartID,
                                                            piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

```vbscript
                if (piInstancePart)

```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(-700,3094.366,1800);
                  ctrAlign.SetCoord(0,-1,0);

                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                    rc = TestConnectedPart(piInstancePart,
```

                                           1,
                                           piInstancePartPrevious,
                                           2);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
piInstancePartPrevious,
2);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-700,3094.366,1800);

                      ctrAlign.SetCoord(0,1,0);
                      ctrUp.SetCoord(1,0,0);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }
                }

ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
              if (FAILED(rc)) break;
```vbscript
```vbscript
              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}

```

```

              piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
```vbscript
```vbscript
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
              if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}

```

```

              // ==============================================================================
              // Place nut on sleeve.
              // ==============================================================================
              // Get reference part
              uPartType = "TubingNut";
              uPartNumber = "B-NUT-CSFR-16S";

              rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
                                                             uSpecName,
                                                             uPartType,
                                                             uPartNumber,
                                                             piParentProduct,
                                                             piReferencePart,
                                                             uCatalogPartName);

              cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;

              if (SUCCEEDED(rc) &&
                  piReferencePart)

              {

                // Get sleeve ctr 2.
```vbscript
if (SUCCEEDED(rc) &&
piReferencePart)
                rc = GetPartConnector(piInstancePartPrevious,
                                      2,
                                      piPlaceOnCtr);

                cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

```

                // Place part on connector.
piPlaceOnCtr);
cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;
                uFunctionType = "CATTubTubeFunction";

                uPlacedPartID = ""; // Null string uses name generated by PP engine
                rc = piPlacePart->PlacePartOnPartConnector (uStandard,
                                                            uFunctionType,
                                                            piReferencePart,
                                                            piPlaceOnCtr,
                                                            piLogicalLine,
                                                            uPlacedPartID,
                                                            piInstancePart);

                cout << "piInstancePart = " << piInstancePart << endl;

```vbscript
                if (piInstancePart)

```

                {
```vbscript
                  // Set catalog part name
cout << "piInstancePart = " << piInstancePart << endl;
```
if (piInstancePart)
                  piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

                  // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                  ctrPosition.SetCoord(-700,3094.366,1800);
                  ctrAlign.SetCoord(0,-1,0);

                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart,
                                             1,
                                             piParentProduct,
                                             ctrPosition,
                                             ctrAlign,
                                             ctrUp);

```vbscript
                  if (SUCCEEDED(rc))

```

                  {
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                    rc = TestConnectedPart(piInstancePart,
```

                                           1,
                                           piInstancePartPrevious,
                                           2);

```vbscript
                    if (SUCCEEDED(rc))

```

                    {
piInstancePartPrevious,
2);
if (SUCCEEDED(rc))
                      ctrPosition.SetCoord(-700,3094.366,1800);

                      ctrAlign.SetCoord(0,1,0);
                      ctrUp.SetCoord(1,0,0);

                      rc = TestPartConnectorData(piInstancePart,
                                                 2,
                                                 piParentProduct,
                                                 ctrPosition,
                                                 ctrAlign,
                                                 ctrUp);

                    }
                  }
                }

ctrUp);
                else

                {
                  rc = CATReturnFailure;
                }
              }
else
rc = CATReturnFailure;
```vbscript
              if (FAILED(rc)) break;

              if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}
```

```vbscript
```vbscript
              if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
              if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
              if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}

```

```

            } while (0); // End dummy loop for easy exit on fail.

          } // End if valid run segment.

          if (FAILED(rc))
          {

```vbscript
if (FAILED(rc))
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
```

          }
        } // End if valid place part object.
      } // end CATTry

    	CATCatch (CATError, pError)
    	{

CATCatch (CATError, pError)
        cout << "CAACloPlacePart::PlacePartInSpace *** Error Caught ***" << endl;
        cout << pError;

```cpp
        rc = CATReturnError(pError);

```

    	} // end CATCatch

cout << pError;
rc = CATReturnError(pError);
      CATEndTry;

      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```vbscript
```vbscript
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
      if (piInstancePartPrevious) {piInstancePartPrevious->Release(#); piInstancePartPrevious = NULL;}
      if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}
      if (piRun) {piRun->Release(#); piRun = NULL;}
      if (piSegment) {piSegment->Release(#); piSegment = NULL;}

```

```

      cout << "CAACloPlacePart::PlacePartOnPartConnector rc = " << rc << endl;
      return rc;

    }

[Top] Place part on part connector and reconnect run to the placed part. The CAACloPlacePart method PlacePartOnPartConnectorAndReconnectRun(#) places part on part connectors and reconnects the run to the placed part. Again a very similar set up to previous methods is used. The part connector provides all of the position data needed for placement. Here the last argument to PlacePartOnPartConnector function is true (i.e. 1) and ipiconnector (second connector of the valve) is not connected to the run. As a result, union is placed on the second connector of the valve, Run is broken and both old and new runs are then connected to the placed part (union). Connector data is tested using the TestPartConnectorData method and the connections are tested with the TestConnectedPart method.

    //=============================================================================
    //  Place part on part connector and reconnect run to the placed part.
    //=============================================================================
    HRESULT CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun(#)
    {
HRESULT CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun(#)
      cout <<"===================================================================="<< endl;
      cout <<"===   CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun   ==="<< endl;
      cout <<"===================================================================="<< endl;
      HRESULT rc = E_FAIL;

      CATObject *piAppObject = NULL;
      CATIPspLogicalLine *piLogicalLine = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;
      CATIProduct *piParentProduct = NULL;
      CATIProduct *piValve = NULL;
      IUnknown *pUnkPart = NULL;
      IUnknown *piReferencePart = NULL;
      IUnknown *piInstancePart = NULL;
      IUnknown *piPlaceOnCtr = NULL;

      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "";
      CATUnicodeString uPartType;
      CATUnicodeString uPartNumber;
      CATUnicodeString uCatalogPartName  = "";
      CATMathPoint ctrPosition;
      CATMathDirection ctrAlign;
      CATMathDirection ctrUp;

      CATTry

      {
        // Get application object.
CATMathDirection ctrUp;
CATTry
```cpp
        piAppObject = new CATObject("CATTubing");

```

        cout << "piAppObject = " << piAppObject << endl;

        if (piAppObject &&
```cpp
                  SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))

```

        {
cout << "piAppObject = " << piAppObject << endl;
if (piAppObject &&
```cpp
SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
```

          cout << "piPlacePart = " << piPlacePart << endl;

          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
          cout << "piParentProduct = " << piParentProduct << endl;

          piLogicalLine = GetALogicalLine(piParentProduct);
          cout << "piLogicalLine = " << piLogicalLine << endl;

```cpp
          piValve = (CATIProduct*)GetChildObject(IID_CATIProduct, "T-001", piParentProduct);

```

          cout << "piValve = " << piValve << endl;

```vbscript
          if (piValve)

```

          {
cout << "piValve = " << piValve << endl;
if (piValve)
           piValve->QueryInterface(IID_IUnknown,(void**)&pUnkPart);

            // Get reference part
```vbscript
if (piValve)
piValve->QueryInterface(IID_IUnknown,(void**)&pUnkPart);
           uPartType = "TubingUnion";
           uPartNumber = "UNION-BULKHEAD-TMFL-12-16S";
           piParentProduct = piValve->GetFatherProduct(#);
```vbscript
           rc = piPlacePart->GetReferencePartFromCatalog (uStandard,
```

                                                          uSpecName,
                                                          uPartType,
                                                          uPartNumber,
                                                          piParentProduct,
                                                          piReferencePart,
                                                          uCatalogPartName);

            cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;
            if (SUCCEEDED(rc) &&
              piReferencePart)
```

            {

cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar(#) << endl;
if (SUCCEEDED(rc) &&
piReferencePart)
              rc = GetPartConnector(piInstancePartPrevious,
                                      2,
                                      piPlaceOnCtr);
              cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

              // Place part on connector.
rc = GetPartConnector(piInstancePartPrevious,
2,
piPlaceOnCtr);
cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;
              CATUnicodeString uFunctionType = "CATTubTubeFunction";

              CATUnicodeString uPlacedPartID  = ""; // Null string uses name generated by PP engine

              rc = piPlacePart->PlacePartOnPartConnector (uStandard,
                                                          uFunctionType,
                                                          piReferencePart,
                                                          piPlaceOnCtr,
                                                          piLogicalLine,
                                                          uPlacedPartID,
                                                          piInstancePart,
                                                          1);

              if (SUCCEEDED(rc) &&
                  piInstancePart)

              {
```vbscript
                // Set catalog part name
```vbscript
```
if (SUCCEEDED(rc) &&
piInstancePart)
                piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);

```

                // Test part connectors.
piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
                ctrPosition.SetCoord(646.329,1587.59,0);
                ctrAlign.SetCoord(-0.05,-1,0);
                ctrUp.SetCoord(0,0,1);
                rc = TestPartConnectorData(piInstancePart,
                                           2,
                                           piParentProduct,
                                           ctrPosition,
                                           ctrAlign,
                                           ctrUp);
```vbscript
                if (SUCCEEDED(rc))

```

                {
ctrPosition,
ctrAlign,
ctrUp);
if (SUCCEEDED(rc))
```vbscript
                  rc = TestConnectedPart(piInstancePart,
```

                                           2,
                                           pUnkPart,
                                           2);
```vbscript
                 if (SUCCEEDED(rc))

```

                  {
2,
pUnkPart,
2);
if (SUCCEEDED(rc))
                    ctrPosition.SetCoord(651.013,1667.21,0);
                    ctrAlign.SetCoord(0.05,1,0);
                    ctrUp.SetCoord(1,0,0);
                    rc = TestPartConnectorData(piInstancePart,
                                               1,
                                               piParentProduct,
                                               ctrPosition,
                                               ctrAlign,
                                               ctrUp);

                  }
                }
              }
            }
          }
        }
      } // end CATTry

     CATCatch (CATError, pError)
     {
CATCatch (CATError, pError)
         cout << "CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun *** Error Caught ***" << endl;
         cout << pError;
```cpp
         rc = CATReturnError(pError);

```

     } // end CATCatch

cout << "CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun *** Error Caught ***" << endl;
cout << pError;
rc = CATReturnError(pError);
    CATEndTry;

      if (piInstancePart) {piInstancePart->Release(#); piInstancePart = NULL;}
```vbscript
```vbscript
      if (piPlaceOnCtr) {piPlaceOnCtr->Release(#); piPlaceOnCtr = NULL;}
      if (piReferencePart) {piReferencePart->Release(#); piReferencePart = NULL;}
      if (pUnkPart) {pUnkPart->Release(#); pUnkPart = NULL;}
      if (piValve) {piValve->Release(#); piValve = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(#); piLogicalLine = NULL;}
      if (piParentProduct) {piParentProduct->Release(#); piParentProduct = NULL;}
      if (piPlacePart) {piPlacePart->Release(#); piPlacePart = NULL;}
      if (piAppObject) {piAppObject->Release(#); piAppObject = NULL;}
```

```

      cout << "CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun rc = " << rc << endl;
      return rc;

    }

[Top] In Short This use case has demonstrated how to use the CATIPspPlacePartOnRun interface to place parts in various situations. Specifically, it has illustrated how to:
    * Initialize the CATIA product environment and tubing application.
    * Place non-string and string parts in space.
    * Place parts on run segments.
    * Place parts on run nodes.
    * Place parts on part connectors.
[Top]

* * *

References [1] | [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---

* * *

Footnotes 1. This documents uses Unix-style forward slash (/) to separate directory names. Windows users should use backslash (/) instead of forward slash (/).
---

* * *

History Version: **1** [January 2008] | Document created
---|---
[Top]

* * *

_Copyright 2008, Dassault Systmes. All rights reserved._
