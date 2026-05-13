---
title: "Updating all Sheets of all Drawing Documents of a Given Folder"
category: "use-case"
module: "CAAScdDriUseCases"
tags: "["CAADriUpdateSheets", "CATIA", "CAADriUseCases", "CAAScdDriUseCases"]"
source_file: "Doc/online/CAAScdDriUseCases/CAADriUpdateSheets.htm"
converted: "2026-05-11T17:31:51.112727"
---
|
## Generative Drafting

|
## Updating all Sheets of all Drawing Documents of a Given Folder

* * *

  This macro shows you how to update sheets in Drawing documents. This macro retrieves all the drawing documents in a given folder, and loops on these documents to open them, update all their _DrawingSheet_ ****objects, save and close them.
---|---
This macro shows you how to update sheets in Drawing documents. This macro retrieves all the drawing documents in a given folder, and loops on these documents to open them, update all their _DrawingSheet_ ****objects, save and close them.
  CAADriUpdateSheets is launched in CATIA [1]. No open document is needed. [CAADriUpdateSheets.CATScript](CAADriUpdateSheetsSource.md) is located in the CAADriUseCases module.  [Execute macro](macros/CAADriUpdateSheets.CATScript) (Windows only).
  CAADriUpdateSheets includes five steps:

  1. Prolog
  2. Creating a File System Object to Handle the Folder
  3. Retrieving the Folder
  4. Looping on the Drawing Documents to Update Their Sheets
  5. Saving and Closing the Documents

#### Prolog

|

      ...
```vbscript
```cpp
      ' Set the CATIA popup file alerts to False
```
```

```vbscript
```vbscript
```vbscript
```cpp
' Set the CATIA popup file alerts to False
      ' It prevents to stop the macro at each alert during its execution
```
```

```

```

```vbscript
```cpp
      CATIA.DisplayFileAlerts = False
```
```

      ...

---

The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
#### Creating a File System Object to Handle the Folder

      ...
The CATIA prompts are disabled thanks to the `DisplayFileAlerts` property of the _Application_ object set to `False`.
```vbscript
```vbscript
```vbscript
      ' Set the file system object containing the folder

```
```

```

```vbscript
```vbscript
      Dim fileSys As FileSystem
```vbscript
```
```cpp
      Set fileSys = CATIA.FileSystem
```
```

```

      ...

---

The `FileSystem` property of the _Application_ object returns a portable object between Windows and Unix. Thanks to this object, a folder and its files and subfolders can be retrieved.
#### Retrieving the Folder

    ...
The `FileSystem` property of the _Application_ object returns a portable object between Windows and Unix. Thanks to this object, a folder and its files and subfolders can be retrieved.
```vbscript
```vbscript
        ' Define the path's folder where we are looking for Drawing documents

```

```

```vbscript
```vbscript
        Dim sFolderPath As String
```vbscript
```
        sFolderPath = InputBox( "Enter a folder path:", "Update All Sheets Of a Folder" ,_
```

                                sDocPath & "/online/CAAScdDriUseCases/samples")
        If (Not oFileSys.FolderExists(sFolderPath)) Then
```vbscript
```vbscript
```vbscript
          Err.Raise 9999,,sFolderPath & ": This Folder does not exist"
        End If
```
```

```

```

```vbscript
```vbscript
```vbscript
```vbscript
        ' Set the folder object
        Dim oFolder As Folder
        Set oFolder = oFileSys.GetFolder(sFolderPath)
```
```

```

```

      ...

---

The folder is retrieved in `folder` from the `fileSys` object using the `GetFolder` method to which the folder name `sFolderPath` is given. `sFolderPath` is initialized to a documentation folder using an environment variable and a confirmation is requested using the InputBox function. The `FolderExists` method of the `FileSystem` object is then used to check the existence of this folder.
#### Looping on the Drawing Documents to Update Their Sheets

    ...
The folder is retrieved in `folder` from the `fileSys` object using the `GetFolder` method to which the folder name `sFolderPath` is given. `sFolderPath` is initialized to a documentation folder using an environment variable and a confirmation is requested using the InputBox function. The `FolderExists` method of the `FileSystem` object is then used to check the existence of this folder.
```vbscript
```vbscript
         ' Loop on the files collection of the folder
        ' For Each File In Folder.Files

```

```

```vbscript
```vbscript
        Dim iI, iJ
```vbscript
```
```vbscript
        For iI = 1 To oFolder.Files.Count
```vbscript
            Dim oFile As Object
            Set oFile = oFolder.Files.Item(iI)
```
```

```

```

```vbscript
```vbscript
```cpp
            '  Retrieve in the files collection only the Drawing documents from its extension
            If InStr(oFile.Name, ".CATDrawing") <> 0 Then
```cpp
                ' Set and open a Drawing document
                Dim oDoc As Document
                Set oDoc = CATIA.Documents.Open(oFile.Path)
```
```

```

```

```vbscript
```vbscript
```vbscript
```cpp
' Set and open a Drawing document
Dim oDoc As Document
Set oDoc = CATIA.Documents.Open(oFile.Path)
```
```

```

```vbscript
                MsgBox "Updating Document " & oFile.Path, 0  ' VBOKOnly
```
```

```vbscript
```vbscript
```vbscript
                ' Loop on the sheets collection of the drawing document
                ' For Each sheet In oDoc.Sheets
                For iJ = 1 To oDoc.Sheets.Count
                    ' Update the sheet even is not necessary
```

```

```

```vbscript
```vbscript
```vbscript
' For Each sheet In oDoc.Sheets
For iJ = 1 To oDoc.Sheets.Count
' Update the sheet even is not necessary
```

```

                    oDoc.Sheets.Item(iJ).ForceUpdate
                Next
```

      ...

---

To retrieve each file of the folder, a `For ... To ... Next` loop uses the `iI` variable that ranges from 1 to the number of files in the folder returned by the `Count` property of the collection of files. The collection is retrieved thanks to the `Files` property of the _Folder_ object. The `Item` method of this collection enables you to retrieve the `iI`th file in the collection handled using the `oFile` variable. Then, using the `InStr` function, each file name is checked for the ".CATDrawing" extension before being opened thanks to the `Open` method of the _Documents_ collection to which the file pathname is passed using the `Path` property of the _File_ object. A `For Each ... In ... Next` embedded loop onto the sheets of the Drawing document uses the `Sheets` property of such as document to retrieve each sheet. The `ForceUpdate` method of the _Sheet_ object updates the sheet, even if updating the sheet is not needed.
#### Saving and Closing the Documents

    ...
```vbscript
```vbscript
```vbscript
                ' Save the Drawing document
                ' oDoc.Save
                ' Close the Drawing document
```

```

```

```vbscript
```vbscript
```vbscript
' Save the Drawing document
' oDoc.Save
' Close the Drawing document
```

```

                oDoc.Close
```vbscript
            End If

```

```

oDoc.Close
```vbscript
End If
```vbscript
```vbscript
        Next

```

```

```

```vbscript
```vbscript
    End Sub

```
```

---

When all the sheets are processed, the drawing document is successively saved and closed thanks to the `Save` and `Close` methods of the _Document_ object. The use of `Save` method is here commented to avoid access right problems to the documentation files.

<.td>

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to update Drawing document sheets using the `ForceUpdate` method of the _DrawingSheet_ object.

[Top]

* * *
#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[2] | _[DrawingDocument](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)_ , _[DrawingSheet](../CAAScdDriTechArticles/CAADriObjDrawingSheet.md),_ [_DrawingSheets_](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md)
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
