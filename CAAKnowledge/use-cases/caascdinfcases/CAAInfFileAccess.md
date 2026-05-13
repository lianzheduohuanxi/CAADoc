---
title: "Accessing Files and Folders"
category: "use-case"
module: "CAAScdInfUseCases"
tags: "["CAAScdInfUseCases", "CATIA", "CAAInfFileAccess"]"
source_file: "Doc/online/CAAScdInfUseCases/CAAInfFileAccess.htm"
converted: "2026-05-11T17:31:52.362048"
---
|
## Infrastructure

|
## Accessing Files and Folders

* * *

  This macro shows you how to access files and folders using CAA V5 portable automation objects. It creates a text file, fills it with data, copies this file and re-extracts the data from the copy.
---|---
This macro shows you how to access files and folders using CAA V5 portable automation objects. It creates a text file, fills it with data, copies this file and re-extracts the data from the copy.
  CAAInfFileAccess is launched in CATIA [1]. No open document is needed. [CAAInfFileAccess.CATScript](CAAInfFileAccessSource.md) is located in the CAAScdInfUseCases module. [Execute macro](macros/CAAInfFileAccess.CATScript) (direct execution of the macro only works on windows).
  CAAInfFileAccess includes five steps:

  1. Prolog
  2. Deleting Existing Files if Needed
  3. Creating the Input File
  4. Duplicating the Input File
  5. Extracting Data from the Output File

#### Prolog

|

      ...
```vbscript
```vbscript
        Dim sLF as String
```vbscript
```
```vbscript
        sLF = Chr(10)

```vbscript
        Dim sMessage as String
        sMessage = InputBox ("Enter a message", "Message", "Hello World")
```
```

```

```

```vbscript
```vbscript
```vbscript
        ' ------------------------------------------
        ' Get the file system object
```cpp
        Dim oFileSys as FileSystem
        Set oFileSys = CATIA.FileSystem
        ' ------------------------------------------
```
        ' Retrieve a folder for temporary files
```cpp
        Dim sTmpPath as String
        sTmpPath=CATIA.SystemService.Environ("CATTemp")
        If (Not oFileSys.FolderExists(sTmpPath)) Then
```
```vbscript
          Err.Raise 9999,,"No Tmp Path Defined"
        End If
```
```

```

```

      ...

---

A variable is defined for the _LineFeed_ character.  The _InputBox_ function asks the user to enter a message string whose default value will be "Hello World".

![](images/filac1.gif)

A variable is defined for the _LineFeed_ character.  The _InputBox_ function asks the user to enter a message string whose default value will be "Hello World".
The _FileSystem_ object is the root object for all file/folder access. Input and output files will be created in the folder dedicated to temporary CATIA data. We use the _SystemService_ object to get its full path defined in the _CATTemp_ environment variable.

The existence of this folder is checked using the `FolderExists` method of the _FileSystem_ object.

####  Deleting Existing Files if Needed

      ...
The existence of this folder is checked using the `FolderExists` method of the _FileSystem_ object.
```vbscript
```vbscript
        ' ------------------------------------------
        ' Delete possibly existing input and output files

```

```

```vbscript
```vbscript
        Dim sFilOu As String ' Output file full path
        sFilOu = sTmpPath & "/caatmpfilou.txt"
```
        If (oFileSys.FileExists(sFilou)) Then
            oFileSys.DeleteFile sFilOu
        End If
```

      ...

---

`FileExists` and `DeleteFile`, two methods of the _FileSystem_ object are used to check the existence of the output file and delete it if needed. The same operation is then performed on the input file.
####  Creating the Input File

    ...
```vbscript
         ' ---------------------------------------
```

```vbscript
```vbscript
```vbscript
' ---------------------------------------
        ' Create file FilIn
```

```

```

```vbscript
```vbscript
        Dim oFilIn As File
```vbscript
```
```vbscript
```vbscript
        Set oFilIn = oFileSys.CreateFile(sFilIn, FALSE)
        Dim oStream As TextStream
        Set oStream = oFilIn.OpenAsTextStream("ForWriting")
```
```

```

        oStream.Write "<MESSAGE>"  & sLF
        oStream.Write "<VALUE>"
        oStream.Write sMessage
        oStream.Write "</VALUE>"   & sLF
        oStream.Write "</MESSAGE>" & sLF
        oStream.Close
```

      ...

---

sFilIn contains the full path of the input file. This file is created using the `CreateFile` method of the _FileSystem_ object that returns a _File_ object. The `OpenAsTextStream` method allows to return a _TextStream_ object from the _File_ object. The `ForWriting` option specifies that the content of this file will be modified. This _TextStream_ object makes it possible to manipulate the file content as a stream of text.

Successive uses of the `Write` method fill the input file. In this case, the message is wrapped by XML-like tags. The _sLF_ variable is used to specify the end of a line. The text stream is then closed using the `Close` method.
####  Duplicating the Input File

    ...
Successive uses of the `Write` method fill the input file. In this case, the message is wrapped by XML-like tags. The _sLF_ variable is used to specify the end of a line. The text stream is then closed using the `Close` method.
```vbscript
```vbscript
         ' ---------------------------------------
        ' Duplicate FilIn in FilOu
```

```

        oFileSys.CopyFile sFilIn, sFilOu, FALSE

    ...

---

The `CopyFile` method of the _FileSystem_ object creates a copy of the input file. It uses its full name, contained in the `sFilIn` variable and uses the content of the `sFilOu` variable as full name of the copy.
####  Extracting Data from the Output File

    ...
The `CopyFile` method of the _FileSystem_ object creates a copy of the input file. It uses its full name, contained in the `sFilIn` variable and uses the content of the `sFilOu` variable as full name of the copy.
```vbscript
```vbscript
        ' ---------------------------------------
        ' Get the result from the output file

```

```

```vbscript
```vbscript
        Dim oFilOu As File
```vbscript
```
```vbscript
```vbscript
        Set oFilOu = oFileSys.GetFile(sFilOu)
        Set oStream = oFilOu.OpenAsTextStream("ForReading")

        Dim sBuffer As String
```
```

```

        sMessage = ""
        sBuffer = oStream.ReadLine
        Do  Until oStream.AtEndOfStream
            sMessage = sMessage & sBuffer
            sBuffer = oStream.ReadLine
        Loop

```

```vbscript
sBuffer = oStream.ReadLine
Loop
        oStream.Close

```

        msgbox sMessage

---

Using the `GetFile` method, a File object is obtained for the output file. `OpenAsTextStream` is then used to get a text stream, but this time a _ForReading_ usage is specified. The `ReadLine` method is used in a loop to read each line of the output file. Each read line is concatenated to the `sMessage` string. The end of the file is detected using the `AtEndOfStream` method.

```vbscript
The `sMessage` variable now contains the whole content of the output file. The `MsgBox` function is used to display this content in a message box.

![](images/filac2.gif)
```

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to access files and folder using CAA V5 _FileSystem_ , _SystemService_ , _File_ and _TextStream_ automation objects.

[Top]

* * *
#### References

[1] | [Replaying a Macro](CAAInfLauchMacro.md)
---|---
[2] | _FileSystem, SystemService, File, TextStream_
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
