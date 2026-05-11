---
title: "Creating a CAA V5 Batch"
category: "use case"
module: "CAABatUseCases"
tags: ["CAABatBatchSample", "CATIBatchElementCAA", "CATIBatch", "CATIBatchCAA", "CATIBatchElementsCAA", "CAABatchInfrastructure"]
source_file: "Doc/online/CAABatUseCases/CAABatBatchSample.md"
converted: "2026-05-11T17:33:45.740129"
---
# Middleware

| 
## BatchInfrastructure

| 
### Creating a CAA V5 Batch

Writing and using a CAA V5 Batch  
---|---|---  
Use Case  
  
* * *
### Abstract

This article discusses the CAABatBatchSample use case. This use case explains how to implement and use a simple CAA V5 Batch.

  * **What You Will Learn With This Use Case**
  * **The CAABatBatchSample Use Case**
    * What Does  **CAABatBatchSample** Do
    * How to Launch  **CAABatBatchSample**
    * Where to Find the**CAABatBatchSample** Code
  * **Step-by-Step**
  * **In Short**
  * **References**

* * *
### What You Will Learn With This Use Case

A V5 batch is a non interactive program which fits 3 principles.  
  
        \- The code is implemented in a library, by the “batchmain” function.   
        \- The batch is described in a XML file known as “file descriptor”.   
        \- Its inputs and outputs are described in one to card-index XML file known as “parameter file”.   
  
This use case is intended to help you to make your first steps in creating your own CAA V5 Batch. The main points are:  
  
        \- Write the batchmain library   
        \- Write your Batch Descriptor file   
        \- Write your Batch Parameter file   
  [Top]
### The CAABatBatchSample Use Case

CAABatBatchSample is a use case of the CAABatchInfrastructure.edu framework that illustrates the batch infrastructure capabilities.  
  [Top]
#### What Does CAABatBatchSample Do

This batch sample takes as input a list of .model files and renames it to .CATPart files.  
  
Warning: this batch sample does not convert model file to CATPart file. It is only about renaming the files.  
 [Top]
#### How to Launch CAABatBatchSample

**The Parameter file**  
  
The parameter file syntax is decided by the batch author, depending on the Batch Infrastructure rules.  
  
The parameter file used in this sample is _  
 _ | 
    
    
    _<?xml version="1.0" encoding="UTF-8"?>
    <!DOCTYPE root SYSTEM "Parameters.dtd" >
    <root batch_name="BatchSample" >
    <inputParameters>
    <file id="file1" filePath="XXX\CAABatchInfrastructure.edu\Data.d\ATTRIBUTCXR1.model" type="bin"/>
    <file id="file2" filePath="XXX\CAABatchInfrastructure.edu\Data.d\BOBINE.model" type="bin"/>
    <file id="file3" filePath="XXX\CAABatchInfrastructure.edu\Data.d\CUBE.model" type="bin"/>
    <simple_arg id="action" value="1"/> 
    </inputParameters>
    <outputParameters>
    <folder id="out_dir" folderPath="" type="bin" extension="CATPart" />
    </outputParameters>
    
    </root>_  
  
---  
  
_  
_ where:  
  
    oBatchSample is the name of the descriptor file.   
    o<inputParameters> and </inputParameters> are the tags used to define the input parameters section.   
    o<outputParameters> and </outputParameters> are the tags used to define the output parameters section.   
        o “XXX\ATTRIBUTCXR1.model” is the full path of the input file  
        o folderPath attribute is the full path for the output directory. If this attribute is set to “”, such as in the example, the directory defined with the $BATCH_HOME variable is used.  
  
The Parameters.dtd file used to check the xml files syntax is provided by the Batch Infrastructure and is used for all batches.  
  
**The Descriptor file:**  
  
The Descriptor file allows the system to make a list of all the available batches. It must be stored in the Framework/CNext/resources/batchdesc directory.  
  
It is created once by the batch author and should not be changed by user.   
The descriptor file used in this sample is _  
 _
    
    
    _The descriptor file used in this sample is <?xml version='1.0' encoding='UTF-8' standalone='no' ?>
    <!DOCTYPE batch SYSTEM "BatchDescriptor.dtd">
    
    <batch name="BatchSample" 
    description="Sample batch" 
    commandline="CATBatch CAABatBatchSample" />_  
  
---  
  
_  
_ where:  
  
        o BatchSample is the batch name.  
  
        o CAABatBatchSample is the name of the library to load, i.e. the library where the batchmain is implemented.  
  
The BatchDescriptor.dtd file used to check the xml files syntax is provided by the Batch Infrastructure and is used for all batches.  
 

  
To launch the use case you have to follow the following steps:  
  
    Edit the parameter file ParamSample.xml in the CAABatchInfrastructure.edu/Data.d directory  
  
    Change the “file1” “file2” and “file3” values, by completing the path with the full path on your machine  
  
```vbscript
    Set up the run time environment (mkrun on build time installation and catstart on runtime installation)  
  
```

    Launch the following command
    
    
    CATBatch XXX/ParamSample.xml  
  
```

---  
  
[Top]
#### Where to Find the CAABatBatchSample

The CAABatBatchSample use case is made of a single function named batchmain located in the CAABatBatchSample.m module of the CAABatchInfrastructure.edu framework:

Windows | InstallRootDirectory\CAABatchInfrastructure.edu\ CAABatBatchSample.m\  
---|---  
Unix | InstallRootDirectory/CAABatchInfrastructure.edu/ CAABatBatchSample.m/  
  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

There are seven logical steps to implement _CATBatBatchSample_ :

  1. Initializing the completion state
  2. Using the batch log
  3. Retrieving CATIBatch Interface 
  4. Retrieving Input parameters
  5. Retrieving field=value argument by its id
  6. Retrieves the output parameters
  7. Renaming input files

[Top]
#### Initializing the completion state
    
    
    CATBatStatePubCAA* pub = CATBatStatePubCAA::GetCAAStatePub();
    
    pub->SetBatchState(10);  
  
---  
  
The CATBatStatePubCAA object is used to publish a completion state for the batch.  
  
The method SetBatchState allows the batch author to set the completion state of the task during the batch  
execution.

[Top]
#### Using the batch log
    
    
    CATBatchLogCAA::PutInLog("filepath: ");
    CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
    
    CATBatchLogCAA::PutInLog("\n");  
  
---  
  
The batch author can write in a batch log during the program execution. It allows the system to log information about  
what the batch is doing. It can be useful if the batch end abnormally.   
This log is written in the $BATCH_HOME/uuid/uuidLog.txt file. The default value for BATCH_HOME is /tmp (on UNIX) or  
C/temp (on Windows) and uuid is a generated identifier for each batch execution  
The only parameter allowed in the PutInLog method is a string.

[Top]

* * *
#### Retrieving CATIBatch Interface
    
    
    CATIBatchCAA* batch = GetCATIBatchCAA();  
  
---  
  
The XML parameter file is read, at batch start, and an XML tree is generated in memory. CATIBatch is the main interface to access XML parameters tree from the batch.

Interfaces CATIBatchElementCAA (for a tag) and CATIBatchElementsCAA (for a list of tags) can be retrieved from CATIBatchCAA allowing accessing the whole XML tree

[Top]
#### Retrieving Input parameters 
    
    
    //Retrieves InputParameters section from the XML parameter file
    CATIBatchElementCAA* inputParameters = NULL;
    HRESULT hr = batch->get_InputParametersCAA(inputParameters);
    
    //Retieves all the <file> tags included in the inputParameters section
    CATIBatchElementsCAA* inputFiles = NULL;
    hr = inputParameters->get_FileListCAA(inputFiles);
    
    // We scan the list of <file> 
    long childrenCount = 0;
    hr = inputFiles->get_Count(childrenCount);
    CATIBatchElementCAA * elem = NULL;
    CATListOfCATUnicodeString listOfV4Files;
    
    for ( int i = 0; i<childrenCount; i++ )
    {
    	hr = inputFiles->ItemCAA( i, elem );
    // for each <file> we retrieve the file path corresponding to the attribute "filePath" of the
    // <file> tag.
    	CATUnicodeString usfile_path;
    	elem->get_Path(usfile_path); 
    
    
    // We write this path in the log of the batch available in $BATCH_HOME/uuid/uuidLog.txt 
    // at the end of the execution. Default for BATCH_HOME is /tmp or C/temp and uuid is a
    // generated identifier for each batch execution.
    	CATBatchLogCAA::PutInLog("filepath: ");
    	CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
    	CATBatchLogCAA::PutInLog("\n");
    ...
    
    //We store the file path in a list for later use
    l	istOfV4Files.Append( usfile_path ); 
    
    }
    
    ...  
  
---  
  
“get_FileListCAA” is a method which extracts all the <file> tags from the input parameters. This method is used because we know that in our particular sample, the input parameters contains a file list.   
  
An other call could have been:  
  
        elem->ParameterCAA(“file1”, inputFile ) ;  
  
        elem->ParameterCAA(“file2”, inputFile ) ;  
  
        elem->ParameterCAA(“file3”, inputFile ) ;  
  
where  
  
    “file1” “file2” and “file3” are the id of the tags you want to retrieve in the parameter file  
  
    inputFile is a CATIBatchElementCAA pointer to those tags  
  
“get_Path” is a method which extracts a “file path” type argument only from <file> and <folder> tags. All those methods are listed and commented in CATIBatchElementCAA and CATIBatchElementsCAA.

[Top]
#### Retrieving field=value argument by its id
    
    
    //We retrieve the <simple_arg> tag 
    CATIBatchElementCAA* oAction = NULL;
    CATUnicodeString usId = "action";
    
    // The Parameter method can be used to retrieve any tag (<file>, <folder>, <simple_arg>)
    giving 
    // in the value of its "id" attribute. Here the tag is <simple_arg id="action" value="1"/>
    hr = inputParameters->ParameterCAA(usId, oAction);
    
    ...
    
    
    // As we know the type of our value we directly call the right cast method to get it as a
    long.
    long action = 0;
    
    hr = oAction->LongArg(action); 
    ...  
  
---  
  
The tag <simple_arg> allows the batch author to describe “field=value” like arguments using the XML syntax.  
  
“LongArg” is a method used to retrieve the value of a long type argument. Equivalent methods exist on CATIBatchElementCAA interface according to the type expected for the given tag value (e.g StringArg() )  
 

[Top]
#### Retrieves the output parameters
    
    
    //Retrieves the outputParameters section
    CATIBatchElementCAA * outputParameters = NULL;
    hr = batch->get_OutputParametersCAA(outputParameters);
    
    //We retrieve the tag which id="out_dir", our output directory
    CATIBatchElementCAA* oDir = NULL;
    usId = "out_dir";
    
    hr = outputParameters->ParameterCAA(usId, oDir);
    
    // We retrieve the path of this directory (value of the attribute "folderPath")
    CATUnicodeString us_path;
    oDir->get_Path(us_path);
    
    ...  
  
---  
  
The output parameters are read in the parameter file.

[Top]
#### Renaming input files
    
    
    char in_filename[CATMaxPathSize];
    char in_dirname[CATMaxPathSize];
    
    char out_fullfilename[CATMaxPathSize];
    CATUnicodeString out_fullfilename_us;
    
    CATBatchLogCAA::PutInLog("Output Creation \n");
    
    for (int ii=1; ii<=listOfV4Files.Size(); ii++)
    {
    	memset(in_filename, '\0', CATMaxPathSize);
    	memset(in_dirname, '\0', CATMaxPathSize);
    	memset(out_fullfilename, '\0', CATMaxPathSize);
    
    	CATSplitPath( listOfV4Files[ii].CastToCharPtr(), in_dirname, in_filename);
    
    	char* ptr = NULL;
    	CATSysStrtok(in_filename, ".", &ptr);
    	sprintf(out_fullfilename, "%s%c%s.CATPart", us_path.ConvertToChar() , dir_delim, in_filename);
    
    	CATBatchLogCAA::PutInLog("creating output : ");
    	CATBatchLogCAA::PutInLog(out_fullfilename);
    	CATBatchLogCAA::PutInLog("\n");
    	out_fullfilename_us = out_fullfilename;
    
    	CATFCopy(&(listOfV4Files[ii]), &out_fullfilename_us, 0);
    }  
  
---  
  
The input files are renamed with the .CATPart extension. This is the purpose of the batch.

[Top]
### In Short

This use case has demonstrated the way to create and launch a V5 batch

 _[_Top]

* * *
### References

[1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *
### History

Version: **1** [March 2006] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 1994-2005, Dassault Systmes. All rights reserved._
