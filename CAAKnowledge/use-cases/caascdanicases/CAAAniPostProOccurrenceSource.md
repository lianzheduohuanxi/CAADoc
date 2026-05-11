---
title: "CAAAniPostProOccurrence.catvbs"
category: "general"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProOccurrence", "CAAScdAniUseCases"]
source_file: "Doc\online\CAAScdAniUseCases\CAAAniPostProOccurrenceSource.htm"
converted: "2026-05-11T17:31:51.761551"
---


    ' COPYRIGHT DASSAULT SYSTEMES 2000
    
    ' ***********************************************************************
    '   Purpose:      To Change the occurrence of an image
    '   Assumptions:   Frequency case is computed with at least 4 occurrences
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R16
    ' ***********************************************************************
    
    Sub CATMain()
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    
    
    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
    
    
    
    ' Retrieve the Analysis Manager
    Set oAnalysisManager = oAnalysisDocument.Analysis
    
    
    
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    
    
    
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    
    
    
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    
    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    Set oAnalysisImage = oAnalysisImages.Item("Von Mises Stress (nodal values).1")
    
    'Modify current occurrence of Image Von Mises Stress (nodal values)
    '==================================================================
    oAnalysisImage.SetCurrentOccurrence 4
    oAnalysisImage.Update
    
    End Sub
    
