---
```vbscript
title: "CAAInfFileAccess.CATScript"
category: "use-case"
module: "CAAScdInfUseCases"
tags: ["CATIA", "CAAInfFileAccess"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfFileAccessSource.htm"
converted: "2026-05-11T17:31:52.364041"
```

---
tags: ["CATIA", "CAAInfFileAccess"]
source_file: "Doc/online/CAAScdInfUseCases/CAAInfFileAccessSource.htm"
converted: "2026-05-11T17:31:52.364041"
    Option Explicit

```vbscript
    ' COPYRIGTH DASSAULT SYSTEMES 2001
    ' ***********************************************************************
    '   Purpose:      Create a text file, duplicate it and read the result.
    '   Assumtions:      
    '   Author: 
    '   Languages:    VBScript BasicScript
    '   Locales:      English 
    '   CATIA Level:  V5R6 
    ' ***********************************************************************

```

    Sub CATMain()

```vbscript
        Dim sLF As String
        sLF = Chr(10) 

        Dim sMessage As String
        sMessage = InputBox ("Enter a message", "Message", "Hello World")
```

```vbscript
        ' ------------------------------------------
        ' Get the file system object
        Dim oFileSys As FileSystem
        Set oFileSys = CATIA.FileSystem
        ' ------------------------------------------
        ' Retrieve a folder for temporary files
        Dim sTmpPath As String 
        sTmpPath=CATIA.SystemService.Environ("CATTemp")
        If (Not oFileSys.FolderExists(sTmpPath)) Then
          Err.Raise 9999,,"No Tmp Path Defined"
        End If
        ' ------------------------------------------
        ' Delete possibly existing input and output files
        Dim sFilOu As String ' Output file full path
        sFilOu = CATIA.FileSystem.ConcatenatePaths(sTmpPath, "caatmpfilou.txt")
        If (oFileSys.FileExists(sFilou)) Then 
```

```vbscript
Dim sFilOu As String ' Output file full path
sFilOu = CATIA.FileSystem.ConcatenatePaths(sTmpPath, "caatmpfilou.txt")
If (oFileSys.FileExists(sFilou)) Then
            oFileSys.DeleteFile sFilOu
        End If

        Dim sFilIn As String ' Intput file full path
        sFilIn = CATIA.FileSystem.ConcatenatePaths(sTmpPath, "caatmpfilin.txt")
        If (oFileSys.FileExists(sFilIn)) Then 
            oFileSys.DeleteFile sFilIn
        End If
```

```vbscript
        ' ---------------------------------------
        ' Create file FilIn  
        Dim oFilIn As File    
        Set oFilIn = oFileSys.CreateFile(sFilIn, FALSE)
        Dim oStream As TextStream
        Set oStream = oFilIn.OpenAsTextStream("ForWriting")
```

```vbscript
Set oFilIn = oFileSys.CreateFile(sFilIn, FALSE)
Dim oStream As TextStream
Set oStream = oFilIn.OpenAsTextStream("ForWriting")
        oStream.Write "<MESSAGE>"  & sLF
        oStream.Write "<VALUE>"
        oStream.Write sMessage 
        oStream.Write "</VALUE>"   & sLF
        oStream.Write "</MESSAGE>" & sLF
        oStream.Close
        ' ---------------------------------------
        ' Duplicate FilIn in FilOu 
        oFileSys.CopyFile sFilIn, sFilOu, FALSE
```

```vbscript
        ' ---------------------------------------
        ' Get the result from the output file  
        Dim oFilOu As File
        Set oFilOu = oFileSys.GetFile(sFilOu)
        Set oStream = oFilOu.OpenAsTextStream("ForReading")

        Dim sBuffer As String
        sMessage = ""
        sBuffer = oStream.ReadLine
        Do  Until oStream.AtEndOfStream
            sMessage = sMessage & sBuffer 
            sBuffer = oStream.ReadLine
```

Do  Until oStream.AtEndOfStream
sMessage = sMessage & sBuffer
sBuffer = oStream.ReadLine
        Loop

Loop
        oStream.Close

        msgbox sMessage

    End Sub
