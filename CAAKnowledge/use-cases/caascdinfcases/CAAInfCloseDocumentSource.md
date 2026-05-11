---
title: "CAAInfCloseDocument.CATScript"
category: "general"
module: "CAAScdInfUseCases"
tags: ["CAAScdInfUseCases", "CATIA", "CAAInfCloseDocument", "CAAInfReadDocument"]
source_file: "Doc\online\CAAScdInfUseCases\CAAInfCloseDocumentSource.htm"
converted: "2026-05-11T17:31:52.352570"
---


    Option Explicit
    ' COPYRIGHT DASSAULT SYSTEMES 2001
    
    ' *****************************************************************************
    '   Purpose:       Close a  Document.
    '   Assumtions:   Looks for CAAInfReadDocument.CATPart
    '                         in the CATDocView   
    '   Author: 
    '   Languages:   VBScript
    '   Locales:        English 
    '   CATIA Level:  V5R7 
    ' *****************************************************************************
    
    
    Sub CATMain()
    
        ' -----------------------------------------------------------------------------------------------
        ' Optional: allows to find the sample wherever it may be installed
        Dim sDocPath As String
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' ------------------------------------------------------------------------------------------------ 
       
        'Open the document. 
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
           "online\CAAScdInfUseCases\samples\CAAInfReadDocument.CATPart")
        Dim iPartDoc As Document
        Set iPartDoc = CATIA.Documents.Open(sFilePath)
    
        'Close the active document which is the document just opened.
         CATIA.ActiveDocument.Close()
    
        'Open the same document again.
         Set iPartDoc = CATIA.Documents.Open(sFilePath)
    
        'Close the document using the variable defined for it.
         iPartDoc.Close()
    
         'Open the same document a third time.
          Set iPartDoc = CATIA.Documents.Open(sFilePath)
    
         'Close the document by specifying its name.
          CATIA.Documents.Item("CAAInfReadDocument.CATPart").Close()
       
    End Sub
    
    
