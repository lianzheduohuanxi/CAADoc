---
title: "CAAInfCreateDocument.CATScript"
category: "general"
module: "CAAScdInfUseCases"
tags: ["CATIA", "CAAInfCreateDocument"]
source_file: "Doc\online\CAAScdInfUseCases\CAAInfCreateDocumentSource.htm"
converted: "2026-05-11T17:31:52.356061"
---


    Option Explicit
    ' COPYRIGHT DASSAULT SYSTEMES 2001
    
    ' *****************************************************************************
    '   Purpose:       Create a New Document.
    '   Assumtions:   None
    '   Author: 
    '   Languages:   VBScript
    '   Locales:        English 
    '   CATIA Level:  V5R7 
    ' *****************************************************************************
    
    
    Sub CATMain()
    
        'Create a new part document.
        'Add the new document to the end of the collection of documents.
        'Create and display a new window for the new document.
        'Activate the new document and the window.
        Dim oNewPartDoc As Document
        Set oNewPartDoc = CATIA.Documents.Add("Part")
       
    End Sub
    
    
