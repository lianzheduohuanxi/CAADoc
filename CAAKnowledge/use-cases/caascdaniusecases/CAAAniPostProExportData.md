---
title: "Exporting Data on Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniPostProExportData", "CATIA", "CAAAniPostProExportDataSource", "CAAScrJavaScript", "CAAScdAniUseCases", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProExportData.htm"
converted: "2026-05-11T11:27:02.500743"
---

---

      

Open the Analysis document. The Analysis document is fetched in the
      documentation installation path, this path has already been stored in the `sDocPath`
      variable. In the collection of documents, two documents can be retrieved;
      the Analysis document and the Part document. The CATTemp environment 
		variable stores temporary data. On windows it points to 
		C:\Documents and Settings\user\Local Settings\Application Data\DassaultSystemes\CATTemp and on unix it points 
		to /CATSettings/CATTemp.
		

#### **Retrieve Analysis Cases and Analysis Sets 
		from Analysis Document**
      
		

According to the general [Analysis
      Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures to
      navigate or retrieve the required objects. First, from the **Document**,
      we find the **Analysis Manager Object**, and the **Analysis Model**. 
		

Property set is retrieved from the list of analysis sets. From the 
		property set list of images is retrieved and material fringe image is 
		added to it.
      

#### Generate the Report
      

The sOut variable stores 
		the path of the folder in which the repots is generated. The method *
		ExportData* is called on an image and it generates a txt or xls file. 
		The exported file contains the values at different coordinates. If the 
		data is exported using the method  *ExportDataWithMeshPartId *
		then the exported data also contains the name of the mesh corresponding 
		to each value.
		

#### Epilog
		

To run the macro interactively CATDocView 
		environment variable must be defined.

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to export 
data in txt and xls format.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

 

 

 

```vbscript
...
```

```vbscript
&#39; ----------------------------------------------------------- 
&#39; Optional: allows to find the sample wherever it&#39;s installed

  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
  sOut = CATIA.SystemService.Environ(&quot;CATTemp&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
&#39; ----------------------------------------------------------- 
' Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
' Retrieve the folder stored in sOut
Set fileSystem1 = CATIA.FileSystem
Set folder1 = fileSystem1.GetFolder(sOut)
```

```vbscript
' Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis
			
' Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```

```vbscript
' Retrieve the analysis cases and the first analysis case
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```

```vbscript
' Retrieve the analysis cases and the Frequency case solution
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.ItemByType("PropertySet")

Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Add("Material_Fringe", False, False, True)
...
```

```vbscript
...
```

```vbscript
' Retrieve the folder stored in sOut
Set fileSystem1 = CATIA.FileSystem
Set folder1 = fileSystem1.GetFolder(sout)
```

```vbscript
'export data in exportfile1.txt (format txt)
oAnalysisImage.ExportData folder1, "exportfile1", "txt"
```

```vbscript
'export data in exportfile2.xls (format xls)
oAnalysisImage.ExportData folder1, "exportfile2", "xls"
```

```vbscript
'export data (with mesh part id) in exportfile3.txt (format txt) 
oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile3", "txt"
```

```vbscript
'export data (with mesh part id) in exportfile4.xls (format xls) 
oAnalysisImage.ExportDataWithMeshPartId folder1, "exportfile4", "xls"
```

```vbscript
...
```

```vbscript
...
End Sub
...
```