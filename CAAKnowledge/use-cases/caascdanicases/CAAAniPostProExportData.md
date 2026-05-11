---
title: "Exporting Data on Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProExportData", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProExportData.md"
converted: "2026-05-11T17:31:51.747550"
---
## Analysis Modeler

| 
## Exporting Data on Images  
  
  
* * *

  This use case shows you how to export data on images using VB. The macro opens an Analysis document which already contains a computed Frequency case and images. Data is exported on Material fringe image which is created under Properties.1 as shown in the figure. Data is exported with and without mesh part id. ![](images/MaterialFringe.gif)    
---|---  
  CAAAniPostProExportData is launched in CATIA [1]. No open document is needed. [ CAAAniPostProExportData](CAAAniPostProExportDataSource.md) is located in the CAAScdAniUseCases module. **[Execute macro](macros/CAAAniPostProExportData.catvbs)** (Windows only).    
  CAAAniPostProExportData includes the following steps:

  1. Prolog
  2. Retrieve Analysis Cases and Analysis Sets from the Analysis Document
  3. Generate the report
  4. Epilog

#### Prolog

| 
    
    
    ...
    
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sOut = CATIA.SystemService.Environ("CATTemp")
    
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```vbscript
    ' ----------------------------------------------------------- 
    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    
```

    
    ...  
  
```

---  
  
Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. The CATTemp environment variable stores temporary data. On windows it points to  C/Documents and Settings\user\Local Settings\Application Data\DassaultSystemes\CATTemp and on unix it points to /CATSettings/CATTemp.
#### **Retrieve Analysis Cases and Analysis Sets from Analysis Document**
    
    
    ...
    
    ' Retrieve the folder stored in sOut
```vbscript
    Set fileSystem1 = CATIA.FileSystem
    Set folder1 = fileSystem1.GetFolder(sOut)
    
```

    
    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```

    
```

    
    ' Retrieve the analysis cases and the first analysis case
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    
```

    ' Retrieve the analysis cases and the Frequency case solution
```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.ItemByType("PropertySet")
    
    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    Set oAnalysisImage = oAnalysisImages.Add("Material_Fringe", False, False, True)
    ...  
  
```

```

---  
  
According to the general [Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , and the **Analysis Model**. 

Property set is retrieved from the list of analysis sets. From the property set list of images is retrieved and material fringe image is added to it.
#### Generate the Report
    
    
    ...  
    
    ' Retrieve the folder stored in sOut
```vbscript
    Set fileSystem1 = CATIA.FileSystem
    Set folder1 = fileSystem1.GetFolder(sout)
    
```

    
    'export data in exportfile1.txt (format txt)
    oAnalysisImage.ExportData folder1, "exportfile1", "txt"
    
    
    'export data in exportfile2.xls (format xls)
    oAnalysisImage.ExportData folder1, "exportfile2", "xls"
    
    
    'export data (with mesh part id) in exportfile3.txt (format txt) 
    oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile3", "txt"
    
    
    'export data (with mesh part id) in exportfile4.xls (format xls) 
    oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile4", "xls"
    
    
    
    ...  
  
```

---  
  
The sOut variable stores the path of the folder in which the repots is generated. The method _ExportData_ is called on an image and it generates a txt or xls file. The exported file contains the values at different coordinates. If the data is exported using the method  _ExportDataWithMeshPartId_ then the exported data also contains the name of the mesh corresponding to each value.
#### Epilog
    
    
    ...
    End Sub
    ...  
  
```

---  
  
To run the macro interactively CATDocView environment variable must be defined.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to export data in txt and xls format.

[Top]

* * *
#### References

[1]| [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._

 

 

 

 
