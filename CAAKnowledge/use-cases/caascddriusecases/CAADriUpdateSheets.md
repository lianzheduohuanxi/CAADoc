---
title: "Untitled"
category: "use-case"
module: "CAAScdDriUseCases"
tags: ["CAAScdDriUseCases", "CAAScrBase", "CAAInfLauchMacro", "CAADriUpdateSheetsSource", "CAAScdInfUseCases", "CAAScdDriTechArticles", "CAADriObjDrawingSheet", "CAADriUpdateSheets", "CAADriObjDrawingDocument", "CAADriUseCases", "CAADriObjDrawingSheets", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdDriUseCases/CAADriUpdateSheets.htm"
converted: "2026-05-11T11:06:32.903801"
---

## Generative Drafting
 
 
## []Updating all Sheets of all Drawing Documents of a
 Given Folder
 
 

---

 
 |![](../CAAScrBase/images/atarget.gif)
 

This macro shows you how to update sheets in Drawing documents.
 
 

This macro retrieves all the drawing documents in a given folder, and
 loops on these documents to open them, update all their *DrawingSheet*
 ****objects, save and close them.
 

 
 
 
 
 |![](../CAAScrBase/images/ainfo.gif)
 

[]CAADriUpdateSheets is launched in CATIA [[1]].
 No open document is needed.
 

 

[CAADriUpdateSheets.CATScript]
 is located in the CAADriUseCases module.  [Execute
 macro] (Windows only).
 

 
 
 
 
 |![](../CAAScrBase/images/ascenari.gif)
 

[]CAADriUpdateSheets includes five steps:
 

 
- [Prolog]
 
- [Creating a File System Object to Handle the Folder
 
- ][Retrieving the Folder
 
- ][Looping on the Drawing Documents to Update
 Their Sheets]
 
- [Saving and Closing the Documents]
 
 
#### []Prolog
 
 
 
```
...
 ' Set the CATIA popup file alerts to False
 ' It prevents to stop the macro at each alert during its execution
 CATIA.DisplayFileAlerts = False
 ...
```

 
 
 
 

The CATIA prompts are disabled thanks to the `DisplayFileAlerts`
 property of the *Application* object set to `False`.
 
#### []Creating a File System Object to Handle the Folder
 
 
 
```
...
 ' Set the file system object containing the folder
 Dim fileSys As FileSystem
 Set fileSys = CATIA.FileSystem 
 ...
```

 
 
 
 

The `FileSystem` property of the *Application* object
 returns a portable object between Windows and Unix. Thanks to this object,
 a folder and its files and subfolders can be retrieved.
 
#### []Retrieving the Folder
 
 
 
```
...
 
' Define the path's folder where we are looking for Drawing documents

 Dim 
sFolderPath
 As 
String
 sFolderPath = InputBox( "Enter a folder path:", "Update All Sheets Of a Folder" ,_
 sDocPath & "\online\CAAScdDriUseCases\samples")

 If 
(Not oFileSys.FolderExists(sFolderPath))
 Then

 Err.Raise 9999,,sFolderPath & ": This Folder does not exist"

 End If

 
' Set the folder object

 Dim 
oFolder
 As 
Folder 

 Set 
oFolder = oFileSys.GetFolder(sFolderPath) 
 ...
```

 
 
 
 

The folder is retrieved in `folder` from the `fileSys`
 object using the `GetFolder` method to which the folder name `sFolderPath`
 is given. `sFolderPath` is initialized to a documentation
 folder using an environment variable and a confirmation is requested using
 the InputBox function. The `FolderExists` method of the `FileSystem`
 object is then used to check the existence of this folder.
 
#### []Looping on the Drawing Documents to Update Their
 Sheets
 
 
 
```
...
 
' Loop on the files collection of the folder

 
' For Each File In Folder.Files

 Dim 
iI, iJ

 For 
iI = 1
 To 
oFolder.Files.Count

 Dim 
oFile
 As 
Object

 Set 
oFile = oFolder.Files.Item(iI)
 
 
' Retrieve in the files collection only the Drawing documents from its extension

 If 
InStr(oFile.Name, ".CATDrawing") <> 0 Then

 
' Set and open a Drawing document

 Dim 
oDoc
 As 
Document 

 Set 
oDoc = CATIA.Documents.Open(oFile.Path)
 MsgBox "Updating Document " & oFile.Path, 0 ' VBOKOnly

 
' Loop on the sheets collection of the drawing document

 
' For Each sheet In oDoc.Sheets 

 For 
iJ = 1
 To 
oDoc.Sheets.Count
 
' Update the sheet even is not necessary

 oDoc.Sheets.Item(iJ).ForceUpdate 

 Next

 ...
```

 
 
 
 

To retrieve each file of the folder, a `For ... To ... Next`
 loop uses the `iI` variable that ranges from 1 to the number of
 files in the folder returned by the `Count` property of the
 collection of files. The collection is retrieved thanks to the `Files`
 property of the *Folder* object. The `Item` method of this
 collection enables you to retrieve the `iI`th file
 in the collection handled using the `oFile` variable. Then,
 using the `InStr` function, each file name is checked for the
 ".CATDrawing" extension before being opened thanks to the `Open`
 method of the *Documents* collection to which the file pathname is
 passed using the `Path` property of the *File* object. A `For
 Each ... In ... Next` embedded loop onto the sheets of the Drawing
 document uses the `Sheets` property of such as document to
 retrieve each sheet. The `ForceUpdate` method of the *Sheet*
 object updates the sheet, even if updating the sheet is not needed.
 
#### []Saving and Closing the Documents
 
 
 
```
...
 
' Save the Drawing document

 
' oDoc.Save

 
' Close the Drawing document

 oDoc.Close

 End If

 Next

End Sub
```

 
 
 
 

When all the sheets are processed, the drawing document is successively
 saved and closed thanks to the `Save` and `Close`
 methods of the *Document* object. The use of `Save` method
 is here commented to avoid access right problems to the documentation
 files.
 <.td>
 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to update Drawing document sheets using the `ForceUpdate`
method of the *DrawingSheet* object.

[[Top]]

---

#### []References

 
 |[1]
 |[Replaying
 a Macro]
 
 
 |[2]
 |*[DrawingDocument]*,
 *[DrawingSheet],*
 [*DrawingSheets*]
 
 
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights reserved.*