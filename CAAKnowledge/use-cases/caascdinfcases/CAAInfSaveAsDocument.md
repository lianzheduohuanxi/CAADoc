---
title: "Saving a New CATIA Document"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CAAInfSaveAsDocument", "CAAScdInfUseCases", "CAAInfReadDocument", "CAAInfCloseDocument", "CAAInfCreateDocument", "CATIA", "CAAInfWriteDocument3", "CAAInfSaveDocument", "CAAInfWriteDocument2", "CAAInfWriteDocument1"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfSaveAsDocument.md"
converted: "2026-05-11T17:31:52.389482"
---

| 
 ## Infrastructure
 
 | 
 ## Saving a New CATIA Document  
   
   
 * * *
 
  This macro shows you how to save a new CATIA document that is currently in the session. In order to save an existing CATIA document in the same storage location and under the same name, see the CAAInfSaveDocument [1] sample for a detailed description.    
 ---|---  
  CAAInfSaveAsDocument is launched in CATIA [2]. An existing document called "CAAInfReadDocument.CATPart" must be found in the CATDocView. [CAAInfSaveAsDocument.CATScript ](CAAInfSaveAsDocumentSource.md)is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfSaveAsDocument.CATScript) (Windows only).    
  CAAInfSaveAsDocument includes five steps:
     1. Retrieving the CATDocView Environment Variable and Checking its Valuation
     2. Retrieving the CATTEMP Environment Variable and Checking its Valuation
     3. Saving the Active CATIA Document
     4. Saving the CATIA Document Specified by an Object Variable
     5. Saving the CATIA Document Specified by its Name
 #### Retrieving the CATDocView Environment Variable and Checking its Valuation
 
 | 
     ' Optional: allows to find the sample wherever it may be installed
     
```vbscript
         Dim sDocPath  As String
         DocPath=CATIA.SystemService.Environ("CATDocView")
         If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
                 Err.Raise 9999,,"No Doc Path Defined"
         End If
 
```

 Define the `sDocPath` variable to retrieve the CATDocView environment variable value which holds the documentation path where the Part document used below is stored. Also, check that this variable is valuated. [Top]
 #### Retrieving the CATTEMP Environment Variable and Checking its Valuation
 
 | 
     ' Optional: allows to specify where document should be saved
     
```vbscript
         Dim sTmpPath  As String
         sTmpPath=CATIA.SystemService.Environ("CATTemp")
         If (Not CATIA.FileSystem.FolderExists(sTmpPath)) Then
             Err.Raise 9999,,"No Tmp Path Defined"
         End If
 
```

 Define a variable to use for the current CATTEMP in order to define the document storage path of saved document. Also, verify that this variable has been valuated. Define the `sTmpPath` variable to retrieve the CATTEMP environment variable value to define the path where the Part document used below will saved. Also, check that this variable is valuated. [Top]
 #### Saving the Active CATIA Document
 
 | 
     
     ...
```vbscript
         'Create a new part document.
         'Add the new document to the end of the collection of documents.
         'Create and display a new window for the new document.
         'Activate the new document and the window.
```

```vbscript
          Dim oFirstNewPartDoc As Document
          Set oFirstNewPartDoc = CATIA.Documents.**Add**("Part")
         'The document just created is the active one.
         'Save the new document.
```

```

          **CATIA.ActiveDocument.SaveAs(sTmpPath & _
            "\CAAInfWriteDocument1.CATPart")
     ** ...  
   
 ---  
   
 An existing CATIA document is created using the `Add` method of the _Documents_ collection (_Documents_ object). See the CAAInfCreateDocument [3] sample for a description of how to create a new CATIA document. Because the `Add` method also activates the new document, you can execute the `SaveAs` method on the `ActiveDocument` property of the CATIA application in order to save it: the document is thus saved in the storage path name and location specified in the argument of the `SaveAs` method. If a document with the same name already exists, a prompt will request that you specify whether or not you want that document to be overwritten with this one. Note that before exiting the session, the document should also be closed. See the CAAInfCloseDocument [4] sample for a description of how to close a document.
 
 [Top]  
   
 | 
 #### Saving the CATIA Document Specified by an Object Variable
 
 | 
     
     ...
        'Create a second new part document.
```vbscript
          Dim oSecondNewPartDoc As Document
          Set oSecondNewPartDoc = CATIA.Documents.Add("Part")
         'Save the new document using the variable name defined for it.
          oSecondNewPartDoc.SaveAs(sTmpPath & _
            "\CAAInfWriteDocument2.CATPart")
       ...  
   
```

```

 ---  
   
 A second way of saving a new CATIA document is to use execute the `SaveAs` method directly on the variable already assigned to handle the document: the document is thus saved in the storage path name and location specified in the argument of the `SaveAs` method. If a document with the same name already exists, a prompt will request that you specify whether or not you want that document to be overwritten with this one. Note that before exiting the session, the document should also be closed.
 
 [Top]  
   
 | 
 #### Saving the CATIA Document Specified by its Name
 
 | 
     
     ...
          'Open an existing document.
```vbscript
           Dim iThirdPartDoc As Document
           Set iThirdPartDoc = CATIA.Documents.Open(sDocPath & _
             "\online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
          'Save the new document by specifying its name.
           CATIA.Documents.Item("CAAInfReadDocument.CATPart").SaveAs(sTmpPath & _
             "\CAAInfWriteDocument3.CATPart")
     
```

       ...  
   
```

 ---  
   
 Finally, the third way of saving a new CATIA document is by executing the `SaveAs` method on an existing document that has been retrieved from the _Documents_ collection by specifying its name to the argument of the `Item` method: a new document identical to the existing one is then saved under the storage path name and location specified in the argument of the `SaveAs` method. If a document with the same name already exists, a prompt will request that you specify whether or not you want that document to be overwritten with this one. Note that before exiting the session, the document should also be closed.
 
 [Top]  
   
 * * *
 #### In Short
 
 This use case has shown the three ways of saving a new CATIA document during an interactive session:
 
     * Using the `ActiveDocument` property of the CATIA application
     * Using the variable assigned to handle the document
     * Using the name of an existing document retrieved from the document collection by the `Item` method
 
 In all three cases, it is necessary to specify the path name and location where the new document will be stored.
 
 [Top]
 
 * * *
 #### References
 
 [1] | [Saving an Existing CATIA Document](CAAInfSaveDocument.md)  
 ---|---  
 [2] | [Replaying a Macro](CAAInfLauchMacro.md)  
 [3] | [Creating a New CATIA Document](CAAInfCreateDocument.md)  
 [4] | [Closing a CATIA Document](CAAInfCloseDocument.md)  
 [Top]
 
 * * *
 
 _Copyright 2001, Dassault Systmes. All rights reserved._
