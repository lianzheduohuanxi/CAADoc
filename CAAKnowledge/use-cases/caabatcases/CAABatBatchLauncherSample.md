---
```vbscript
title: "Launching CAA V5 Batch"
category: "use case"
module: "CAABatUseCases"
tags: ["CATIBatchElementCAA", "CAABatBatchInfrastructure", "CATIBatchCAA", "CATIBatchElementsCAA", "CAABatchInfrastructure", "CAABatBatchLauncherSample"]
source_file: "Doc/online/CAABatUseCases/CAABatBatchLauncherSample.htm"
converted: "2026-05-11T17:33:45.726629"
```

---
# Middleware

|
## BatchInfrastructure

|
### Launching CAA V5 Batch

_Launching a CAA V5 Batch from a code source._
---|---|---
Use Case

* * *
### Abstract

This article shows how to launch a CAA V5 Batch from a code source.

  * **What You Will Learn With This Use Case**
  * **The CAABatBatchLauncherSample Use Case**
    * What Does CAABatBatchLauncherSample Do
    * How to Launch CAABatBatchLauncherSample
    * Where to Find the CAABatBatchLauncherSample Code
  * **Step-by-Step**
  * **In Short**
  * **References**

|

* * *
### What You Will Learn With This Use Case

This use case is intended to show you how to launch CAA V5 Batch in a code source, using the Batch APIs. [Top]
### The CAABatBatchLauncherSample Use Case

CAABatBatchLauncherSample is a use case of the CAABatBatchInfrastructure.edu framework that illustrates Batch infrastructure capabilities. [Top]
#### What Does CAABatBatchLauncherSample Do

The CAABatBatchLauncherSample 's purpose is to show how to launch and monitor a CAA V5 Batch. The example batch takes as input  a list of .model files and renames them to .CATPart files.  To do this, the use case will show how to :     \- generate a XML describing the input files.     \- use callback to be notified of the end of the batch replay     \- analyze the generated XML file describing the outputs.
**_Warning_** : this batch sample does not convert model files to CATPart files. It is only about renaming the files.
  [Top]
#### How to Launch CAABatBatchLauncherSample

The CAABatBatchLauncherSample 's purpose is to show how to launch and monitor a CAA V5 Batch. The example batch takes as input  a list of .model files and renames them to .CATPart files.  To do this, the use case will show how to :     \- generate a XML describing the input files.     \- use callback to be notified of the end of the batch replay     \- analyze the generated XML file describing the outputs.
To launch CAABatBatchLauncherSample , you will need to set up the build time environment ,then compile CAABatBatchLauncherSample along with its prerequisites, set up the run time environment :            -     set ADL_ODT_IN variable to the directory where the input files to rename are located : | Windows |  InstallRootDirectory\CAABatchInfrastructure.edu\Data.d\

Unix |  InstallRootDirectory/CAABatchInfrastructure.edu/Data.d/

            -    set BATCH_HOME to a writable directory where all the renamed files will be copied.

 and then execute the use case :

            -     launch the start command mkrun -c  CAABatBatchLauncherSample

[Top]
#### Where to Find the CAABatBatchLauncherSample Code

The CAABatBatchLauncherSample use case is made of a single function named batchmain located in the CAABatBatchLauncherSample.m module of the CAABatchInfrastructure.edu framework:

The CAABatBatchLauncherSample use case is made of a single function named batchmain located in the CAABatBatchLauncherSample.m module of the CAABatchInfrastructure.edu framework:
Windows |  InstallRootDirectory\CAABatchInfrastructure.edu\ CAABatBatchLauncherSample.m\

The CAABatBatchLauncherSample use case is made of a single function named batchmain located in the CAABatBatchLauncherSample.m module of the CAABatchInfrastructure.edu framework:
Windows |  InstallRootDirectory\CAABatchInfrastructure.edu\ CAABatBatchLauncherSample.m\
Unix |  InstallRootDirectory/CAABatchInfrastructure.edu/ CAABatBatchLauncherSample.m/

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.
There are seven logical steps in CAABatBatchLauncherSample:

  1. Generating the XML input
  2. Retrieving the CATBatClientMonitorCAA interface
  3. Initialization of the CATBatClientMonitorCAA
  4. Initialization of callbacks
  5. Starting the CAA V5 Batch
  6. Analyzing output files and result check
  7. Cleaning up

[Top]
#### Generating the input XML input

    ...
    CATBatchParameters input_param;
CATBatchParameters input_param;
    input_param.BeginBuffer("BatchSample", "ParamTest.xml");

    input_param.BeginInput();
    input_param.InsertFile("file1", "CAABatchInfrastructure.edu\\Data.d\\ATTRIBUTCXR1.model", "", COMM_FILE_BINARY);
    input_param.InsertFile("file2", "CAABatchInfrastructure.edu\\Data.d\\BOBINE.model", "", COMM_FILE_BINARY);
    input_param.InsertFile("file3", "CAABatchInfrastructure.edu\\Data.d\\CUBE.model", "", COMM_FILE_BINARY);

    input_param.InsertSimpleArg("action", "1");
    input_param.EndInput();

    const char* out_folder = "";

    input_param.BeginOutput();
    input_param.InsertFolder("out_dir", out_folder, "" , COMM_FILE_BINARY, "CATPart");
    input_param.EndOutput();
    input_param.EndBuffer();

    ...

---

To launch a CAA V5 Batch, an XML input file must be defined. The first part of the sample aims at generating that XML file, which is not provided as input data in this sample.

This XML file contains :

    * _BatchSample_ is the name of the descriptor file.
    * _ParamTest.xml_ is the name of the parameter file .
    * XXX\ATTRIBUTCXR1.model” is the full path of the input files.
    * _out_folder_  attribute is the full path for the output directory. If this attribute is set to “”, such as in the example, the directory defined with the BATCH_HOME variable is used.
    * _BeginInput_() and _EndInput_() are used at the beginning and the end of the input data section.
    * _BeginOutput_() and _EndOutput_() methods are used at the beginning and the end of output data section.

The Parameters.dtd file used to check the xml files syntax is provided by the Batch Infrastructure and is used for all batches.

More details about the parameter file can be found in the use case "Creating a CAA V5 Batch".[1]

[Top]
#### Retrieving the CATBatClientMonitorCAA interface

    ...
    	CATBatClientMonitorCAA* cliMonitor = CATBatClientMonitorCAA::GetTheClientMonitorCAA();

    ...

---

The method  _GetTheClientMonitorCAA_ returns a pointer to the interface CATBatClientMonitorCAA.
####
#### Initialization of the CATBatClientMonitorCAA

    ...
    	HRESULT hr = cliMonitor->InitializeV5Monitoring();
    ...

---

The method _InitializeV5Monitoring_ initializes the ability of monitoring CAA V5 Batchs.

#### Initialization of callbacks

    ...
    	CATBatchEventWatcher evt(&cond_for_exit);
    ...

---

CATBatchEventWatcher evt(&cond_for_exit);
A specific object to register callbacks on batch events must be created : CATBatchEventWatcher. In this example, the only event we're looking for is the CATBatchEndNotif. (end of the batch execution) When the batch replay is finished, the main can check the result of the  file renaming.

The initialization of the call is done with the AddCallback method that is called by the constructor of the  CATBatchEventWatcher class.

The CATBatchEventWatcher  class is defined in an other source of this sample (CATBatchEventWatcher.h and CATBatchEventWatcher.cpp). It contains the call back definition and the notification emission when the batch replay is finished.

#### Starting the CAA V5 Batch

    ...
    	CATUnicodeString path_param;
CATUnicodeString path_param;
    	input_param.GetFullPath(path_param);

```vbscript
    	hr = cliMonitor->StartV5Batch(path_param, uuid);

```

    	evt.SetUUID(uuid);

    ...

---

evt.SetUUID(uuid);
The method _GetFullPath_ retrieves the full path of the previously generated XML parameter file.

_SetUUID_ is called after we start the CAA V5 Batch because we need to know the batch identifier, uuid, which is an output argument retrieved by a call to the _StartV5Batch_ method _._ It is a unique identifier that identifies the running batch. It is used as an input argument to get information about the batch execution. In this example, it is used in the _SetUUID_ method to tell the CATBatchEventWatcher which CATBatchEventNotif it must expect.

At the end of the batch replay, a notification is received by the CATBatchEventWatcher (the callback was initialized in the previous step). The UUID is used to check which batch is ending, and avoids confusion if there are several bachs running at the same time.

####
#### Analyzing output files and result check
####

    ...

    	CATIBatchCAA* outputParamfile =NULL;
CATIBatchCAA* outputParamfile =NULL;
```vbscript
     	if (rc==0)

```

    	{
CATIBatchCAA* outputParamfile =NULL;
if (rc==0)
```vbscript
```vbscript
    		hr = GetOutputXMLFile(outputParamfile, uuid);

```

```

    		CATIBatchElementCAA* outputParametersSection = NULL;

```vbscript
    		hr = outputParamfile->get_OutputParametersCAA(outputParametersSection);

```

    		CATIBatchElementsCAA* fileList=NULL;
```vbscript
    		hr = outputParametersSection->get_FileListCAA(fileList);

```

    		CATIBatchElementCAA* elem = NULL;
    		long fileCount = 0;
```vbscript
    		hr = fileList->get_Count(fileCount);

```

    		CATUnicodeString path;
```vbscript
    		for ( int ii = 0; ii<fileCount; ii++ )

```

    		{
hr = fileList->get_Count(fileCount);
CATUnicodeString path;
for ( int ii = 0; ii<fileCount; ii++ )
```vbscript
    			hr = fileList->ItemCAA( ii, elem );
```

    			elem->get_Path(path);

    			printf("Found output <%s>\n", path.CastToCharPtr());

    		}

    	}

    ...

---

The batch has ended. The Return Code is 0, so the batch ended with success. We now open the generated output file to analyze its content. We retrieve the generated file thanks to the batch uuid, its unique identifier.

The batch has ended. The Return Code is 0, so the batch ended with success. We now open the generated output file to analyze its content. We retrieve the generated file thanks to the batch uuid, its unique identifier.
We create an access to the CATIBatchCAA  interface to call the methods that will allow us to retrieves all the parameters of the output file. The list of rename file is retrieved, the number of item counted. In this example, the complete paths of renamed files are read with the _get_Path_ method and printed on the standard output so that the end user can check the sample has done its work correctly.

To check if the sample has done its work correctly, open the $BATCH_HOME directory and check there are the 3 renamed files :
ATTRIBUTCXR1.CATPart, CUBE.CATPart and BOBINE.CATPart.

#### Cleaning up

To check if the sample has done its work correctly, open the $BATCH_HOME directory and check there are the 3 renamed files :
ATTRIBUTCXR1.CATPart, CUBE.CATPart and BOBINE.CATPart.
    CATDeleteFile(path_param.CastToCharPtr());

    CATBatchLogCAA::DeleteLogs(uuid);

---

CATBatchLogCAA::DeleteLogs(uuid);
Before leaving, we do some clean up.

_CATDeleteFile_ deletes the input parameter file. The method _DeleteLogs_ from the CATBatchLogCAA interface cleans the batch log files.

[Top]

* * *
### In Short

A CAA V5 batch can be launched in source code using APIs provided by the CATBatClientMonitorCAA interface.

_[_Top]

* * *
### References

[1] | [Creating a CAA V5 Batch](CAABatBatchSample.md)
---|---
[Top]

* * *
### History

Version: **1** [Jan 2007] | Document created
---|---
[Top]

* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
