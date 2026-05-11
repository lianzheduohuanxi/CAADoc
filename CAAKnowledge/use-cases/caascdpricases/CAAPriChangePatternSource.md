---
title: "CAAPriPatternDescription.CATScript"
category: "general"
module: "CAAScdPriUseCases"
tags: ["CATIA", "CAAPriChangePattern", "CAAPriPatternDescription"]
source_file: "Doc\online\CAAScdPriUseCases\CAAPriChangePatternSource.htm"
converted: "2026-05-11T17:31:51.213996"
---


    Option Explicit
    ' COPYRIGTH DASSAULT SYSTEMES 2004
    
    ' ***********************************************************************
    '   Purpose:      Changes pattern description
    '   Assumptions:   Looks for CAAPriChangePattern.htm in the DocView   
    '   Author: 
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R14
    ' ***********************************************************************
    
    Sub CATMain()
    
    Dim oPartDocument As PartDocument
    Dim oPart As Part
    Dim oSelection As Selection
    Dim InputObjectType(0) As String
    Dim oStatus as String
    Dim oCircularPattern as CircPattern
    
    ' ------------
    ' Get the part document
    ' ------------
    Set oPartDocument = CATIA.ActiveDocument
    ' ------------
    ' Get the part
    ' ------------
    Set oPart = oPartDocument.Part
    ' ------------
    ' Get the selection
    ' ------------
    Set oSelection = oPartDocument.Selection
    ' ------------
    ' Set the selection type
    ' ------------
    InputObjectType(0) = "CircPattern"
    ' ------------
    ' Get the status
    ' ------------
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a circular pattern", True )
    ' ------------
    ' Get the object in the selection
    ' ------------
    Set oCircularPattern = oSelection.Item(1).Value
    ' ------------
    ' Set the circular pattern instance number
    ' ------------
    oCircularPattern.AngularRepartition.InstancesCount.Value = 6
    ' ------------
    ' Set the circular pattern instance as Unequal Angular Spacing mode
    ' ------------
    oCircularPattern.CircularPatternParameters = catUnequalAngularSpacing
    oCircularPattern.SetUnequalStep 6
    ' ------------
    ' Set the circular pattern Unequal Angular Spacing
    ' ------------
    oCircularPattern.SetInstanceAngularSpacing 2, 30.000000
    oCircularPattern.SetInstanceAngularSpacing 3, 75.000000
    oCircularPattern.SetInstanceAngularSpacing 4, 75.000000
    oCircularPattern.SetInstanceAngularSpacing 5, 30.000000
    oCircularPattern.SetInstanceAngularSpacing 6, 75.000000
    ' ------------
    ' Update the part
    ' ------------
    oPart.Update 
    
    
    End Sub
    
    
