---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASchQueryCompRoute", "CAAScrBase", "CATIASchAppConnectable", "CATIASchCntrLocation", "CATIASchGRR", "CATIASchCompGraphic", "CATIASchGRRRoute", "CATIASchRouteGraphic", "CAASCH_CompRoute01", "CAAScdSchUseCases", "CATIAProduct", "CATIASchGRRComp", "CATIA"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRouteSource.htm"
converted: "2026-05-11T11:06:32.559065"
---

```
Option Explicit

' COPYRIGHT DASSAULT SYSTEMES 2004

' *****************************************************************************

' Purpose: Provides a list of component and route from a schematic 

' document. List all the defining points of the component

' route instances. For each component instance, also lists

' the defining points of its connectors.

' Languages: VBScript

' Locales: English 

' CATIA Level: V5R15 

' *****************************************************************************

Sub 
CATMain()

 
' ------------------------------------------------------------------------- 

 
' Optional: allows to find the sample wherever it's installed

 dim 
sDocPath
 As 
String 
 sDocPath=CATIA.SystemService.Environ("CATDocView")

 If 
(Not CATIA.FileSystem.FolderExists(sDocPath))
 Then

 Err.Raise 9999,sDocPath,"No Doc Path Defined"

 End If

 
' ------------------------------------------------------------------------- 

 
' Open the schematic document 

 Dim 
sFilePath
 sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
 "online\CAAScdSchUseCases\samples\CAASCH_CompRoute01.CATProduct")

 Dim 
objSchDoc
 As 
Document

 Set 
objSchDoc = CATIA.Documents.Open(sFilePath)

 Dim 
strMessage
 As 
String

 strMessage = _
 "--------------------------------------------------------------------" & vbCr
 strMessage = strMessage & _
 "Output traces from CAASchQueryCompRoute.CATScript" & vbCrLf

 
' Find the top node of the schematic object tree - schematic root.

 Dim 
objPrdRoot
 As 
Product

 Dim 
objSchRoot
 As 
SchematicRoot

 If 
( Not ( objSchDoc Is Nothing ) )
 Then

 Set 
objPrdRoot = objSchDoc.Product 

 If 
( Not ( objPrdRoot Is Nothing ) )
 Then

 Set 
objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")

 End If

 End If

 Dim 
objSchLComps
 As 
SchListOfObjects

 Dim 
objSchLCompRefs
 As 
SchListOfObjects

 Dim 
objSchLRoutes
 As 
SchListOfObjects

 Dim 
objSchSession
 As 
SchSession

 Dim 
objCurDoc
 As 
Document

 Dim 
strCurDocName
 As 
String

 If 
( Not ( objSchRoot Is Nothing ) )
 Then

 Set 
objSchSession = objSchRoot.GetSchematicSession

 
'-----------------------------------------------------------------------

 
'| Query the name of the current document 

 
'-----------------------------------------------------------------------

 If 
( Not ( objSchSession Is Nothing ) )
 Then

 Set 
objCurDoc = objSchSession.GetCurrentDocument

 If 
( Not ( objCurDoc Is Nothing ) )
 Then

 strCurDocName = objCurDoc.Name
 strMessage = strMessage & "Current Document = " & strCurDocName & vbCr

 End If

 End If

 End If

 Dim 
intNbComp
 As 
Integer

 Dim 
intNbRoute
 As 
Integer

 Dim 
intIndex
 As 
Integer

 Dim 
objPrd
 As 
Product

 Dim 
strName
 As 
String

 
' ------------------------------------------------------------------------- 

 
' | List schematic component references in the model

 
' ------------------------------------------------------------------------- 

 Set 
objSchLCompRefs = objSchRoot.GetRefComponents

 If 
( Not ( objSchLCompRefs Is Nothing ) )
 Then

 
 int
NbComp = objSchLCompRefs.Count
 strMessage = strMessage & "Number of schematic component REFERENCES = " _
 &
 int
NbComp & vbCr

 If 
(intNbComp > 0)
 Then

 For 
intIndex = 1 To
 int
NbComp

 Set 
objPrd = Nothing
 strName = ""

 Set 
objPrd = objSchLCompRefs.Item (intIndex,"CATIAProduct")

 If 
( Not ( objPrd Is Nothing ) )
 Then

 strName = objPrd.Name
 strMessage = strMessage & " member " & intIndex _
 & "= " & strName & vbCr

 End If 

 Next 

 End If

 End If

 
' ------------------------------------------------------------------------- 

 
' | List schematic component instances in the model

 
' ------------------------------------------------------------------------- 

 Set 
objSchLComps = objSchRoot.GetComponents

 Dim 
objGRRCompInst
 As 
SchGRRComp

 Dim 
objCompGraphInst
 As 
SchCompGraphic

 Dim 
objCntbl
 As 
SchAppConnectable

 Dim 
objLCntrs
 As 
SchListOfObjects

 Dim 
objSchLDbComp
 As 
SchListOfDoubles

 Dim 
objLFilter
 As 
SchListOfBSTRs

 Dim 
db6Matrix(6)
 As 
Double

 Dim 
intNb
 As 
Integer

 Set 
objLFilter = Nothing

 If 
( Not ( objSchLComps Is Nothing ) )
 Then

 
 int
NbComp = objSchLComps.Count
 strMessage = strMessage & "Number of schematic component INSTANCES = " _
 &
 int
NbComp & vbCr

 If 
(intNbComp > 0)
 Then

 Dim 
iCntr
 As 
Integer

 Dim 
intNbCntr
 As 
Integer

 Dim 
objLDbCntr
 As 
SchListOfDoubles

 Dim 
objCntr
 As 
SchCntrLocation

 Dim 
objGRR
 As 
SchGRR

 Dim 
intNCoord
 As 
Integer

 Dim 
dbCntrX
 As 
Double

 Dim 
dbCntrY
 As 
Double

 For 
intIndex = 1 To
 int
NbComp

 Set 
objPrd = Nothing

 Set 
objCompGraphInst = Nothing

 Set 
objGRRCompInst = Nothing

 Set 
objCntbl = Nothing

 Set 
objLCntrs = Nothing

 Set 
objGRR = Nothing

 Set 
objSchLDbComp = Nothing

 strName = ""

 Set 
objPrd = objSchLComps.Item (intIndex,"CATIAProduct")

 If 
( Not ( objPrd Is Nothing ) )
 Then

 strName = objPrd.Name
 strMessage = strMessage & " member " & intIndex _
 & "= " & strName & vbCr

 Set 
objCompGraphInst = objSchRoot.Ge
tInt
erface ("CATIASchCompGraphic", _
 objPrd) 

 End If 

 
 
'------------------------------------------------------------------

 
' Get the orientation matrix of the symbol representing the 

 
' component instance.

 
'------------------------------------------------------------------

 If 
( Not ( objCompGraphInst Is Nothing ) )
 Then

 Set 
objGRRCompInst = GetComponentImage (objCompGraphInst)

 If 
( Not ( objGRRCompInst Is Nothing ) )
 Then

 objGRRCompInst.GetTransformation2D objSchLDbComp

 If 
( Not ( objSchLDbComp Is Nothing ) )
 Then

 
 int
Nb = objSchLDbComp.Count

 If 
(
 int
Nb > 5 )
 Then

 db6Matrix(0) = objSchLDbComp.Item(1)
 db6Matrix(1) = objSchLDbComp.Item(2)
 db6Matrix(2) = objSchLDbComp.Item(3)
 db6Matrix(3) = objSchLDbComp.Item(4)
 db6Matrix(4) = objSchLDbComp.Item(5)
 db6Matrix(5) = objSchLDbComp.Item(6)

 strMessage = strMessage & "---- rotation matrix = " & _
 "(" & db6Matrix(0) & "," & db6Matrix(1) & "," _
 & db6Matrix(2) & "," & db6Matrix(3) & ")" & vbCr
 strMessage = strMessage & "---- instance origin = " & _
 "(" & db6Matrix(4) & "," & db6Matrix(5) & ")" & vbCr 
 

 End If 

 End If 

 End If 
'--- If ( Not ( objGRRComp Is Nothing )...

 Set 
objCntbl = objSchRoot.Ge
tInt
erface ("CATIASchAppConnectable",_
 objCompGraphInst)

 Set 
objGRR = objSchRoot.Ge
tInt
erface ("CATIASchGRR", objGRRCompInst)

 End If 
'---if ( Not ( objCompGraphInst Is Nothing ) ...

 
 
'------------------------------------------------------------------

 
' Get the connector locations of all component instances

 
'------------------------------------------------------------------

 If 
( Not ( objCntbl Is Nothing ) And Not ( objGRR Is Nothing ) )
 Then

 Set 
objLCntrs = objCntbl.AppListConnectors (objLFilter)

 If 
( Not ( objLCntrs Is Nothing ) )
 Then

 
 int
NbCntr = objLCntrs.Count

 If 
(
 int
NbCntr > 0)
 Then

 For 
iCntr = 1 To
 int
NbCntr

 Set 
objLDbCntr = Nothing

 Set 
objCntr = Nothing

 Set 
objCntr = objLCntrs.Item (iCntr,"CATIASchCntrLocation")

 If 
( Not ( objCntr Is Nothing ))
 Then

 objCntr.GetPosition objGRR, objLDbCntr

 If 
( Not ( objLDbCntr Is Nothing ) )
 Then

 
 int
NCoord = objLDbCntr.Count

 If 
(
 int
NCoord > 1 )
 Then

 dbCntrX = objLDbCntr.Item(1)
 dbCntrY = objLDbCntr.Item(2)
 strMessage = strMessage & "---- ... connector " & iCntr 
 strMessage = strMessage & " position = " & dbCntrX & _
 "," & dbCntrY & vbCr

 End If 

 End If

 End If 
'---If ( Not ( objCntr Is Nothing )) ... 

 Next 
'--- For iCntr ...

 End If 
'--- If ( NbCntr > 0 ...

 End If 
'--- Not ( objLCntr Is Nothing ...

 End If 
'---if ( Not ( objCntbl Is Nothing )) ...

 Next 
'--- For intIndex = 1 

 End If 
'--- If (intNbComp > 0) ...

 End If 
'--- If ( Not ( objSchLComps Is Nothing ) ...

 
' ------------------------------------------------------------------------- 

 
' | List schematic route instances

 
' ------------------------------------------------------------------------- 

 Set 
objSchLRoutes = objSchRoot.GetRoutes

 Dim 
objGRRRoute
 As 
SchGRRRoute

 Dim 
objSchRouteGraph
 As 
SchRouteGraphic

 Dim 
objSchLDbRoute
 As 
SchListOfDoubles

 Dim 
intNbOut
 As 
Integer

 If 
( Not ( objSchLRoutes Is Nothing ) )
 Then

 
 int
NbRoute = objSchLRoutes.Count
 strMessage = strMessage & "Number of schematic route instances = " & _
 
 int
NbRoute & vbCr

 If 
(intNbRoute > 0)
 Then

 For 
intIndex = 1 To
 int
NbRoute

 Set 
objPrd = Nothing

 Set 
objGRRRoute = Nothing

 Set 
objSchRouteGraph = Nothing

 strName = ""

 Set 
objPrd = objSchLRoutes.Item (intIndex,"CATIAProduct")

 If 
( Not ( objPrd Is Nothing ) )
 Then

 
'strName = objPrd.Name

 strName = objPrd.PartNumber
 strMessage = strMessage & " member " & _
 
 int
Index & "= " & strName & vbCr

 Set 
objSchRouteGraph = objSchRoot.Ge
tInt
erface ("CATIASchRouteGraphic", _
 objPrd) 

 End If

 
'------------------------------------------------------------------

 
' Get the route points x-y coordinates of the route. 

 
'------------------------------------------------------------------

 If 
( Not ( objSchRouteGraph Is Nothing ) )
 Then

 Set 
objGRRRoute = GetRoutePrimitives (objSchRouteGraph,objSchRoot)

 If 
( Not ( objGRRRoute Is Nothing ) )
 Then

 Set 
objSchLDbRoute = Nothing
 objGRRRoute.GetPath objSchLDbRoute

 If 
( Not ( objSchLDbRoute Is Nothing ) And _
 
 int
NbOut > 3 )
 Then

 
 int
Nb = objSchLDbRoute.Count

 Dim 
iIndex
 As 
Integer

 Dim 
jIndex
 As 
integer

 Dim 
dbX
 As 
Double

 Dim 
dbY
 As 
Double

 Dim 
intNbPoint
 As 
Integer
 
 int
NbPoint =
 int
NbOut/2

 If 
( (intNbOut =
 int
Nb ) And (intNbPoint > 1) )
 Then

 strMessage = strMessage & "---- route points = [" 

 For 
iIndex = 1 To
 int
NbPoint
 jIndex = ((iIndex-1) * 2) + 1
 dbX = objSchLDbRoute.Item(jIndex)
 dbY = objSchLDbRoute.Item(jIndex+1)
 strMessage = strMessage & "(" & dbX & "," & dbY & ")"

 Next 

 strMessage = strMessage & "]" & vbCr

 End If 

 End If 
'--- If ( Not ( objSchLDbRoute Is Nothing ...

 End If 
'--- If ( Not ( objGRRRoute Is Nothing )...

 End If 
'---if ( Not ( objSchRouteGraph Is Nothing ) ... 

 

 Next 
'--- For intIndex = 1 To intNbRoute

 End If 
'--- If (intNbRoute > 0) ...

 End If 
'--- If ( Not ( objSchLRoutes Is Nothing ) ...

 strMessage = strMessage & _
 "--------------------------------------------------------------------" & vbCr
 MsgBox strMessage

End Sub

' -----------------------------------------------------------------------------

' | Find the first symbol used for the input schematic component.

' | Input: objSchCompGraph: the schematic component 

' | (a CATIASchCompGraphic interface handle).

' | Returns: the component image (the symbol instance)

' -----------------------------------------------------------------------------

Private Function GetComponentImage (objSchCompGraphArg
 As 
SchCompGraphic)
 As 
SchGRRComp

 Dim 
objSchLSymbols
 As 
SchListOfObjects

 If 
( Not ( objSchCompGraphArg Is Nothing ) )
 Then

 Set 
objSchLSymbols = objSchCompGraphArg.ListGraphicalImages

 If 
( Not ( objSchLSymbols Is Nothing ) )
 Then

 Set 
GetComponentImage = objSchLSymbols.Item (1,"CATIASchGRRComp")

 End If

 End If

End Function

' -----------------------------------------------------------------------------

' | Find the first graphical primitives of an input route.

' | Input: objSchRouteGraph: the schematic route

' | (a CATIASchRouteGraphic interface handle).

' | objSchRootGraph: the schematic root 

' | Returns: the route graphic primitives

' -----------------------------------------------------------------------------

Private Function GetRoutePrimitives (objSchRouteGraphArg
 As 
SchRouteGraphic, _
 objSchRootArg
 As 
SchematicRoot)
 As 
SchGRRRoute

 Dim 
objSchLGRR
 As 
SchListOfObjects

 Dim 
objSchGRR
 As 
SchGRR

 If 
( Not ( objSchRouteGraphArg Is Nothing ) And _ 
 Not ( objSchRootArg Is Nothing ) )
 Then

 Set 
objSchLGRR = objSchRouteGraphArg.ListGraphicalPrimitives

 If 
( Not ( objSchLGRR Is Nothing ) )
 Then

 Set 
objSchGRR = objSchLGRR.Item (1,"CATIASchGRR")

 If 
( Not ( objSchGRR Is Nothing ) )
 Then

 Set 
GetRoutePrimitives = objSchRootArg.Ge
tInt
erface ("CATIASchGRRRoute", _
 objSchGRR)

 End If

 End If

 End If

End Function
```