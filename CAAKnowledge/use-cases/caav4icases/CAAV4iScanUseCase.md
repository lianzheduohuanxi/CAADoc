---
title: "Scanning a Model to Retrieve V4 Elements"
category: "use case"
module: "CAAV4iUseCases"
tags: ["CATIAV4Interfaces", "CAACATIAV4Interfaces", "CAAV4iEduModelScan", "CAAV4iModelScan"]
source_file: "Doc/online/CAAV4iUseCases/CAAV4iScanUseCase.md"
converted: "2026-05-11T17:33:45.798397"
---
# 3D PLM PPR Hub Open Gateway

| 
## V4 Access

| 
### Scanning a Model to Retrieve V4 Elements

_Working with the elements of model_  
---|---|---  
Use Case  
  
* * *
### Abstract

This article shows how to scan a model. 

  * **What You Will Learn With This Use Case**
  * **The CAAV4iEduModelScan Use Case**  
    * What Does CAAV4iModelScan Do
    * How to Launch CAAV4iEduModelScan
    * Where to Find the CAAV4iEduModelScan Code
  * **Step-by-Step**
  * **In Short**
  * **References**

  
---  
  
* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to retrieve elements of a model. 

[Top] 
### The CAAV4iEduModelScan Use Case

CAAV4iEduModelScan is a use case of the CAACATIAV4Interfaces.edu framework that illustrates CATIAV4Interfaces framework capabilities. 

[Top] 
#### What Does CAAV4iEduModelScan Do

The scaning functions retrieve the elements by creating object of the CATV4iV4Element class.  
CAAV4iEduModelScan begins by opening the .model document.  
Then, it scans the model to retrieve each workspace, every workspace are scaned to retrieves theire sets and finally, the elements of every set are retrieved.  
CAAV4iEduModelScan retrieves all the element of a model. The name of each element is retrieved and put in a file.  
At the end of CAAV4iEduModelScan using the input model DITTOS.model, the output file looks like : 

> > > > \--*MASTER  
>  \----*SET1  
>  \------*CST1  
>  \------*CRV1  
>  \------*SOL1  
>  \------*DIT4  
>  \------*DIT5  
>  \----*SET2  
>  \------*SOL3  
>  \------*SOL5  
>  \----*SET5  
>  \------*DIT6  
>  \------*DIT7  
>  \--DETAIL-1  
>  \----*SET3  
>  \------*SOL7  
>  \------*SOL9  
>  \--DETAIL-2  
>  \----*SET4  
>  \------*SOL11  
>  \------*SOL13 

[Top] 
#### How to Launch CAAV4iEduModelScan

To launch CAAV4iEduModelScan , you will need to set up the build time environment, then compile CAAV4iEduModelScan along with its prerequisites, set up the run time environment, and then execute the use case [1].  
CAAV4iEduModelScan takes two parameters.  

mkrun -c CAAV4iEduModelScan InputModel OutputFile 

Where:

  InputModel : the full path of the model to scan  
  OutputFile : the full path of the output text file. 

You can use the model `DITTOS.model` located in `CAA``CATIAV4Interfaces``.edu/InputData`

  * Windows : `InstallRootDirectory\CAA``CATIAV4Interfaces``.edu\InputData`
  * Unix : `InstallRootDirectory/CAA``CATIAV4Interfaces``.edu/InputData`

[Top] 
#### Where to Find the CAAV4iEduModelScan Code

The CAAV4iEduModelScan use case is made of a single file located in the CAAV4iEduModelScan.m module of the CAACATIAV4Interfaces.edu framework:  
  Windows | `InstallRootDirectory\CAACATIAV4Interfaces.edu\`CAAV4iEduModelScan`.m\`  
---|---  
Unix | `InstallRootDirectory/CAACATIAV4Interfaces.edu/`CAAV4iEduModelScan`.m/`  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. 

[Top] 
### Step-by-Step

There are 4 logical steps in CAAV4iEduModelScan : 

  1. Opening the output file
  2. Opening the model
  3. Retrieving the workspaces
  4. Retrieving the sets
  5. Retrieving the elements

[Top] 
#### Opening the output file
    
    
    ...
      ofstream outputFile (argv[2]);
    ...  
  
---  
  
The second argument of CAAV4iEduModelScan is the full path of the output file. 

[Top] 
#### Opening the model
    
    
    ...
      char* pathname = argv[1];
      CATDocument * doc=NULL;
      CATUnicodeString filename( pathname );
      CATDocumentServices::OpenDocument( filename, doc, readOnlyFlag );
    ...  
  
---  
  
To access to the data of the model, a CATDocument is needed.  
The path of the model passed in argument is converted to a CATString and is used to open the model in "read only" mode. 

[Top] 
#### Retrieving the workspaces
    
    
    ...
      if (! CATV4iGetMaster(doc, wspElem, ier) )
      {
        while(!endWsp && !ier)
        {
          if (wspElem)
            outputFile << "--"<<wspElem->GetId()<<endl;
    
          // the sets of the workspace wspElem are retrieved here
    ...
    
          if ( ! CATV4iGiswsp(wspElem, nextWspElem, wspType, endWsp, ier) )
          {
    ...
            wspElem=nextWspElem;
          }
        }
      }
    ...  
  
---  
  
This part of code consist in retrieving the workspaces of the model.  
_CATV4iGetMaster(doc, wspElem, ier)_ retrieves the MASTER workspace in wspElem.  
Then, while _endWsp_ is false, the identificator of the workspace is printed in the output file and the next workspace is searched using _CATV4iGiswsp_

[Top] 
#### Retrieving the sets
    
    
    ...
          if (! CATV4iGisset(wspElem, setElem, endSet, ier) )
          {
            while(!endSet && !ier)
            {
              if (setElem)
                outputFile << "----"<<setElem->GetId()<<endl;
    
              // the elements of the set setElem are retrieved here
    ...
    
              if (! CATV4iGisset(setElem, nextSetElem, endSet, ier) )
              {
    ...
                setElem=nextSetElem;
              }
            }
          }
    ...  
  
---  
  
This part of code consist in retrieving the set of a workspace.  
_CATV4iGisset(wspElem, setElem, endSet, ier)_ retrieves the first set of the workspace _wspElem_.  
Then, while _endSet_ is false, the identificator of the set is printed in the output file and the next set is searched using _CATV4iGisset(setElem, nextSetElem, endSet, ier)_

[Top] 
#### Retrieving the elements
    
    
    ...
              if (! CATV4iGisels(setElem, NULL, element, endEls, ier) )
              {
                while(!endEls && !ier)
                {
                  if (element)
                    outputFile << "------"<<element->GetId()<<endl;
    ...
    
                  if (! CATV4iGisels(setElem, element, nextElement, endEls, ier) )
                  {
    ...
                    element=nextElement;
                  }
                }
              }
    ...  
  
---  
  
This part of code consist in retrieving the element of a set.  
_CATV4iGisels(setElem, NULL, element, endEls, ier)_ retrieves the first element of the set _setElem_.  
Then, while _endEls_ is false, the identificator of the element is printed in the output file and the next set is searched using _CATV4iGisels(setElem, element, nextElement, endEls, ier)_

[Top] 

* * *
### In Short

These sample show a way to retrieve an element of a model by scaning all the model. 

_[_Top] 

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *
### History

Version: **1** [Jul 2003] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2003, Dassault Systmes. All rights reserved._
