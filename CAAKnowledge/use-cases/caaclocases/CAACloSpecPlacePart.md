---
title: "Placing Spec Parts"
category: "use case"
module: "CAACloUseCases"
tags: ["CAACommonLayoutItf", "CATIPspDefinePhysicalPart", "CAACloSpecPlace", "CATIProduct", "CAACloPlacePart", "CAACloEduRuns", "CAACloSpecPlacePartMain", "CAAPspUtilities", "CATIPspPlacePartOnRun", "CAAPlantShipInterfaces", "CAAPspBaseEnvProtected", "CAACloSpecPlacePart", "CATIPspLogicalLine", "CATICloPartRules", "CATIA"]
source_file: "Doc\online\CAACloUseCases\CAACloSpecPlacePart.htm"
converted: "2026-05-11T17:33:49.530102"
---

Equipment & Systems |  Distributive Systems |  Placing Spec Parts _How to place spec parts_  
---|---|---  
Use Case  
  
* * *

Abstract This article discusses the CAACloSpecPlacePart use case.
    * **Overview**
      * What You Will Learn
      * What CAACloSpecPlacePart Does
      * How to Launch CAACloSpecPlacePart
      * Where to Find CAACloSpecPlacePart Files
    * **Step-by-Step**
      * Initialization
      * Use Case Execution
      * Parts in Space
    * **In Short**
    * **References**  
---  
  
* * *

Overview CAACloSpecPlacePart is a use case of the CAACommonLayoutItf.edu framework. It illustrates the following.
    * CATIPspDefinePhysicalPart, CATIPspPlacePartOnRun and CATICloPartRules interfaces that are implemented by CATCommonLayout.
[Top] What You Will Learn This use case is intended to show you how to:
    * Get the part number using the CATIPspDefinePhysicalPart interface.
    * Get function type using the CATICloPartRules interface. 
    * Place spec part using the CATIPspPlacePartOnRun interface.
[Top] What CAACloSpecPlacePart Does CAACloSpecPlacePart places tubing part. It places a union in space. [Top] How to Launch CAACloSpecPlacePart To launch CAACloSpecPlacePart, you will need to set up the build time environment, then compile CAACloSpecPlacePart along with its prerequisites, set up the run time environment, and then execute the sample. This is fully described in the referenced article[1]. Launch the use case with the following command.
    
    CAACloSpecPlacePart  MyRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct1
    

where MyRootDirectory is the pathname of the root directory where you copied and built the use case. [Top] Where to Find CAACloSpecPlacePart Files The CAACloSpecPlacePart code consists of three files located in the CAACloSpecPlacePart.m use case module of the CAACommonLayoutItf.edu framework: 
    
    InstallRootDirectory/CAACommonLayoutItf.edu/CAACloSpecPlacePart.m/LocalInterfaces/CAACloSpecPlacePart.h
    InstallRootDirectory/CAACommonLayoutItf.edu/CAACloSpecPlacePart.m/src/CAACloSpecPlacePart.cpp
    InstallRootDirectory/CAACommonLayoutItf.edu/CAACloSpecPlacePart.m/src/CAACloSpecPlacePartMain.cpp
    

where `InstallRootDirectory` is the root directory of your CAA V5 installation1. This sample uses two C++ source files: CAACloSpecPlacePartMain cpp and CAACloSpecPlacePart.cpp. CAACloSpecPlacePartMain.cpp holds the main method which initiates the sample code. CAACloSpecPlacePart.cpp defines the class that places parts. CAACloSpecPlacePart has a corresponding header (.h) file. The CAACloSpecPlacePart also uses three data files: 
    
    InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct
    InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/CATTubTubingLine20010507183018970.CATProduct
    InstallRootDirectory/CAACommonLayoutItf.edu/CNext/resources/graphic/CAACloEduRuns/TubingWP.CATProduct
    

CAACloEduRuns.CATProduct is the main data model for the use cases. It is the file which should be referenced in the execution command line. CATTubTubingLine20010507183018970.CATProduct and TubingWP.CATProduct are used by CAACloEduRuns.CATProduct.  [Top] Step-by-Step The remainder of this document describes the various parts of CAACloSpecPlacePartMain.cpp and CAACloSpecPlacePart.cpp.
    * Initialization
    * Use Case Execution
    * Parts in Space
[Top] Initialization CAACloSpecPlacePartMain.cpp contains the main method that initiates processing. It reads the command line argument to find the path of the data file to be processed. It also creates the CAACloSpecPlacePart class and calls the DoSample method of CAACloSpecPlacePart.
    
    	// COPYRIGHT DASSAULT SYSTEMES 2011
    //=============================================================================
    //
    // CAACloSpecPlacePartMain
    //
    //  This sample illustrates how to use the CAA Plant Ship interfaces to place spec parts.
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
    //        CAACloSpecPlacePart MyRootDirectory/CAAPlantShipInterfaces.edu/CNext/graphic/CAACloEduRuns/CAACloEduRuns.CATProduct
    //  
    //  where MyRootDirectory is the pathname of the root directory where you copied and built the use case.
    //
    //=============================================================================
    //
    #include <iostream.h>
    #include <string.h>
    
    
    // This framework
    #include "CAACloSpecPlacePart.h"
    
    // System
    #include "CATErrorMacros.h"
    #include "CATUnicodeString.h"
    
    //=============================================================================
    //   Main
    //=============================================================================
    int main (int argc, char **argv)
    {
    
      cout << "Start main CAACloSpecPlacePart" << endl;
      
      int rc = 0;
    
      HRESULT rcError = CATReturnFailure;
    
      CATUnicodeString FileToBeLoaded = NULL;
    
      CAACloSpecPlacePart myObject;
    
    
      CATTry 
      {
        if (argc > 1)
        {
    
          FileToBeLoaded = argv[1];
        }
    
        if (FileToBeLoaded.IsNull())
        {
    
           cout << "**** must input the file name of " << endl;
           cout << "a CATProduct with Piping application objects " << endl;
        }
    
        else
        {
          cout << "FileToBeLoaded = " << FileToBeLoaded << endl;
    
          rcError = myObject.DoSample(FileToBeLoaded);
        }
      }
    
    	CATCatch (CATError, pError)
    	{
    
        cout << "error in main " << endl;
    
        rcError = CATReturnError(pError);
    	} // end CATCatch
    
    
      CATEndTry;
    
      cout << "CAACloPlacePart rcError = " << rcError << endl;
    
      if (FAILED(rcError))
      { 
        rc = 999;
        CATError *pError = CATError::CATGetLastError(rcError);
    
        if (pError)
        {
          cout << pError;
          Flush(pError);
        }
      }
    
      cout << "CAACloSpecPlacePart rc = " << rc << endl;
      cout << "End main CAACloSpecPlacePart" << endl;
    
      return rc;
    }
    

[Top] Use Case Execution The CAACloSpecPlacePart DoSample method runs the use cases. It starts by calling CreateCATProductEnv to load the input data model and create a CATIA product environment. CreateCATProductEnv is part of the CAAPspBaseEnvProtected class which is defined in these files.
    
    InstallRootDirectory/CAAPlantShipInterfaces.edu/PublicInterfaces/CAAPspBaseEnvProtected.h
    InstallRootDirectory/CAAPlantShipInterfaces.edu/CAAPspUtilities.m/src/CAAPspBaseEnvProtected.cpp
    

After CAACloSpecPlace calls CreateCATProductEnv it calls ApplicationInit to initialize the Tubing application. ApplicationInit is also a part of the CAAPspBaseEnvProtected class. With the data model and application properly initialized DoSample runs the use case. The use case get the part number, function type and use this information to place part in space. It then sets specification on placed part. The code for DoSample is shown below.
    
    //=============================================================================
    //  Execute the CAACloSpecPlacePart sample code.
    //=============================================================================
    HRESULT CAACloSpecPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)
    {
      cout <<"============================================================"<< endl;
    
      cout <<"===       CAACloSpecPlacePart::DoSample                      ==="<< endl;
      cout <<"============================================================"<< endl;
      cout <<" File: " << iuFileToBeLoaded << endl;
    
      HRESULT rc = CATReturnFailure;
    
      // Interface pointer variables used below in the try section.
    
    
      CATTry 
      {
    
        //  Load input document
        CreateCATProductEnv(iuFileToBeLoaded);
        cout << "Product environment created." << endl;
    
        //  Initialize Tubing Design application
        ApplicationInit("CATTubing");
        cout << "Tubing application initialized." << endl;
    
        // Place a part in space.
        HRESULT rcSpace = PlaceSpecPartInSpace();
        cout << "rcSpace = " << rcSpace << endl;
    
    
        
        // Set return code.
        if (SUCCEEDED(rcSpace))
          rc = CATReturnSuccess;
      } // end CATTry
    
    	CATCatch (CATError, pError)
    	{
    
        cout << "CAACloSpecPlacePart::DoSample *** Error Caught ***" << endl;
        cout << pError;
    
        rc = CATReturnError(pError);
    	} // end CATCatch
    
      CATEndTry;
    
      cout << "CAACloSpecPlacePart::DoSample rc = " << rc << endl;
      return rc;
    }

[Top] Parts in Space CAACloSpecPlacePart places an union in space. The union is placed by the method PlaceSpecPartInSpace. PlaceSpecPartInSpace first performs setup necessary for placing any part. It calls GetChildObject to find the tubing work package (TubingWP.1) which is a child of the data model's root product. It finds the tubing line in TubingWP.1 using the method GetALogicalLine. Both GetChildObject and GetALogicalLine are part of CAAPspBaseEnvProtected. It gets a tubing application object and derives CATIPspDefinePhysicalPart, CATIPspPlacePartOnRun and CATICloPartRules interface objects respectively from the application object. After accomplishing its setup duties PlaceSpecPartInSpace begins its major work of placing a union. The first step is to find the correct union in the catalog. The CATIPspDefinePhysicalPart method GetPartNumbers is used to find a list of PartNumbers. GetPartNumbers takes standard, Part Type, Specification name and Logical Line as input arguments and the List of PartNumbers is returned in the output argument, oListPartNumbers. For finding the reference part in the catalog the CATIPspPlacePartOnRun interface’s method GetReferencePartFromCatalog is used. GetReferencePartFromCatalog takes standard as an input to help decode attribute values. It also can accept a specification ("spec"). In the sample the spec is set to null so no specification is used. If spec is set the catalog search will be limited to parts that meet the given specification. Part type and part number are the key arguments that define the part which is being looked for. The part number is taken from the List of part numbers returned by the GetPartNumbers method; here the first part number in the list is passed as an argument. The parent product is also sent to GetReferencePartFromCatalog. This helps GetReferencePartFromCatalog decode various names more efficiently. The found reference product is returned in the argument, piReferencePart. And the corresponding catalog part name is returned in the last argument, uCatalogPartName.  In order to get the Function types the CATICloPartRules interface’s GetPartFunctions method is used. It takes the reference product piReferencePart returned by GetReferencePartFromCatalog, the standard, the specification name and nominal size as input arguments and returns list of function types and list of section types lFunctionTypes and lSectionTypes respectively as output arguments. The second part placement step is to position and properly place an instance product in the data model. This is accomplished using PlacePartInSpace. PlacePartInSpace accepts the same standard for input as was used for GetReferencePartFromCatalog. It accepts the first function type from the list of the function types returned by the GetPartFunctions method which tracks the purpose of the instance part. The reference part is sent to PlacePartInSpace to define the part being placed. The logical line defines the tubing line into which the new part will become a member. The new part ID can be specified. In the sample code the ID is null which instructs the part placement engine to generate the part ID according to its preset rules. Up direction, horizontal orientation and position all define how the new part is positioned. The new instance part is returned in piInstancePart. Catalog part name returned by GetReferencePartFromCatalog needs to be set on the new part this is done by the CATIPspPlacePartOnRun interface’s SetCatalogPartName method which takes new part instance piInstancePart and catalog name uCatalogPartName as input arguments. The specification is set on the part instance by using CATIPspDefinePhysicalPart interface’s SetSpecification method which takes new part instance piInstancePart and specification name uSpecNameas input arguments. Apart from using PlaceSpecPartInSpace method, user can use other part placement APIs available in the CATIPspPlacePartOnRun to place part on run, on connector and then set specification using SetSpecification method to spec driven part.  The code for PlaceSpecPartInSpace is shown below.
    
    //=============================================================================
    //  Place parts in space.
    //=============================================================================
    HRESULT CAACloSpecPlacePart::PlaceSpecPartInSpace()
    {
      cout <<"============================================================"<< endl;
      cout <<"===       CAACloSpecPlacePart::PlaceSpecPartInSpace              ==="<< endl;
    
      cout <<"============================================================"<< endl;
    
      HRESULT rc = CATReturnFailure;
    
      // Interface pointer variables used below in the try section.
      CATObject *piAppObject = NULL;
      CATIPspDefinePhysicalPart *piDefPhyPart = NULL;
      CATICloPartRules *piPartRules = NULL;
      CATIPspPlacePartOnRun *piPlacePart = NULL;
      IUnknown *piReferencePart = NULL;
      CATIProduct *piParentProduct = NULL;
      CATIPspLogicalLine *piLogicalLine = NULL;
      IUnknown *piInstancePart = NULL;
    
      CATUnicodeString uCatalogPartName = "";
      CATUnicodeString uPlacePartErrorMessage;
      CATUnicodeString uStandard = "SSTL";
      CATUnicodeString uSpecName = "SS150R";
      CATUnicodeString uPartType = "Union";
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
        piAppObject = new CATObject("CATTubing");
    
        cout << "piAppObject = " << piAppObject << endl;
    
        if (piAppObject)
        {
    
          piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
    
          cout << "piParentProduct = " << piParentProduct << endl;
    
          piLogicalLine = GetALogicalLine(piParentProduct);
    
          cout << "piLogicalLine = " << piLogicalLine << endl;
          
          if (
                SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspDefinePhysicalPart,(void**)&piDefPhyPart))  && 
                SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart))  && 
                SUCCEEDED(piAppObject->QueryInterface(IID_CATICloPartRules,(void**)&piPartRules))
              )
           {
    	cout << "piDefPhyPart = " << piDefPhyPart << endl;
    	cout << "piPlacePart = " << piPlacePart << endl;
    	cout << "piPartRules = " << piPartRules << endl;
    
    
          // Get the part number
          CATUnicodeString oListPartNumbers;
    
          piDefPhyPart->GetPartNumbers(uStandard, 
                                       uPartType, 
                                       uSpecName, 
                                       piLogicalLine, 
                                       oListPartNumbers);
    
           uPartNumber = oListPartNumbers[1];
          
          // Get reference part
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart,
                                                         uCatalogPartName);
    
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;
    
          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
          
           // Get the Function type.
           CATListOfCATUnicodeString lFunctionTypes;
           CATListOfInt lSectionTypes;
           CATUnicodeString uNominalSize = "1/4in";
           
           piPartRules->GetPartFunctions(piReferencePart,
           			             uStandard, 
                                         uPartType, 
                                         uSpecName, 
                                         uNominalSize,	 
                                         lFunctionTypes,
                                         lSectionTypes);
                                         
            uFunctionType = lFunctionTypes[1];
    
            // Place part in space.
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
             {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart,uCatalogPartName);
            
              // Set specification. 
              piDefPhyPart->SetSpecification(piInstancePart,uSpecName);
              
              // Verification 
              // Specification set and Function type used, can be verified by saving the document and
              // Launching the CATIA. (Go to properties of the placed part, by right clicking the mouse.)    
    
             } 
             else
             {
              rc = CATReturnFailure;
             }
           }//piReferencePart
           if (FAILED(rc))
           {
            piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
            cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
           }
          } // piDefPhyPart piPlacePart piPartRules
         } // piAppObject
       } // end CATTry
    
    	
      CATCatch (CATError, pError)
      {
        cout << "CAACloPlacePart::PlacePartInSpace *** Error Caught ***" << endl;
    	 
        cout << pError;
    	 
        rc = CATReturnError(pError);
      } // end CATCatch
    
    
      CATEndTry;
    
      if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
      if (piDefPhyPart) {piDefPhyPart->Release(); piDefPhyPart = NULL;}
      if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
      if (piPartRules) {piPartRules->Release(); piPartRules = NULL;}
      if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
      if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
      if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
      if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
    
      cout << "CAACloSpecPlacePart::PlacePartSpecInSpace rc = " << rc << endl;
      return rc;
    }
    

In Short This use case has demonstrated how to use the CATIPspDefinePhysicalPart, CATIPspPlacePartOnRun and CATICloPartRules interfaces to place parts in space. Specifically, it has illustrated how to: 
    * Initialize the CATIA product environment and tubing application.
    * Place part in space.
[Top]

* * *

References [1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
  
* * *

Footnotes 1. This document uses Unix-style forward slash (/) to separate directory names. Windows users should use backslash (\) instead of forward slash (/).   
---  
  
* * *

History Version: **1** [January 2011] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2011, Dassault Systmes. All rights reserved._
