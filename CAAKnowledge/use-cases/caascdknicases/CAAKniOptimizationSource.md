---
```vbscript
title: "CAAKniOptimization.CATScript"
category: "use-case"
module: "CAAScdKniUseCases"
tags: ["CATIA", "CAAKniOptimization"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniOptimizationSource.htmmd"
converted: "2026-05-11T17:31:51.983820"
```

---
tags: ["CATIA", "CAAKniOptimization"]
source_file: "Doc/online/CAAScdKniUseCases/CAAKniOptimizationSource.htmmd"
converted: "2026-05-11T17:31:51.983820"
    Option Explicit
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2001

```

```

```vbscript
```vbscript
    Dim Language as String
    Language="VBScript"
```
```

```vbscript
```vbscript
```vbscript
    ' ***********************************************************************
    '   Purpose:    This macro shows how to create and run an optimization feature.
    '               It shows the follwing steps.
    '               - Creates two parameters and a formula
    '               - Creates and sets up the optimization feature
    '               - Runs the optimization.
    '
    '   The optimization problem consists in finding the value of x that minimizes fx.
    '   knowing that fx = x*x + 8.
    '   The objective is fx and the free parameter is x.
    '
    '   Assumption: This macro is intended to be run on a newly created part document.
    '   Languages:    VBScript
    '   Locales:      English (United States)
    '   CATIA Level:  V5R7
    ' ***********************************************************************
```

```

```

```vbscript
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
```vbscript
    ' Set the CATIA popup file alerts to False
    ' It prevents to stop the macro at each alert during its execution
```
```vbscript
    CATIA.DisplayFileAlerts = False
    ' Retrieve your active document - CATIA is your application
```
    ' You get the active document by using the ActiveDocument property
    ' on your application object
```vbscript
    Dim oActiveDoc As Document
    Set oActiveDoc = CATIA.ActiveDocument
    ' Check whether the document is a CATPart
```
    If (InStr(oActiveDoc.Name,".CATPart")) <> 0  Then
            ' Retrieve the collection object which contains
            ' all the document relations.
            ' The statements below are only valid when the active
            ' document is a CATPart
```vbscript
            Dim oRelations As Relations
            Set oRelations = oActiveDoc.Part.Relations
            ' Retrieve the collection object which contains
```
            ' all the document parameters.
```vbscript
            Dim oParameters As Parameters
            Set oParameters = oActiveDoc.Part.Parameters
            ' Create Real type parameter as objective to be optimized.
```
```vbscript
            Dim oFx As Parameter
            Set oFx = oParameters.CreateReal("Real1", 199 )
```
```

```

```

```vbscript
```vbscript
```vbscript
' Create Real type parameter as objective to be optimized.
```vbscript
Dim oFx As Parameter
Set oFx = oParameters.CreateReal("Real1", 199 )
```
```

```

            oFx.Rename "fx"
```

```vbscript
```vbscript
```vbscript
            ' Create Real type parameter as free parameter.
```vbscript
            Dim oX As Parameter
            Set oX = oParameters.CreateReal("Real2", 299 )
```
```

```

```

```vbscript
```vbscript
```vbscript
' Create Real type parameter as free parameter.
```vbscript
Dim oX As Parameter
Set oX = oParameters.CreateReal("Real2", 299 )
```
```

```

            oX.Rename "x"
```

```vbscript
```vbscript
```vbscript
            ' Create a formula to be optimized.
```vbscript
            Dim oFormula As Formula
            Set oFormula = oRelations.CreateFormula(                     _
```
```

```

```

                                       "Objective",                      _
                                       "This is the objective function.",_
                                       oFx,                              _
                                       "x*x + 8.0")
```vbscript
```vbscript
```vbscript
            ' Retrieve the collection object which contains
            ' all the document optimizations.
```vbscript
            Dim oOptimizations As Optimizations
            Set oOptimizations = oRelations.Optimizations
            ' Create the optimization feature.
```
```vbscript
            Dim oOptimization1 As Optimization
            Set oOptimization1 = oOptimizations.CreateOptimization(#)
```
```

```

```

```vbscript
```vbscript
```vbscript
' Create the optimization feature.
```vbscript
Dim oOptimization1 As Optimization
Set oOptimization1 = oOptimizations.CreateOptimization(#)
            oOptimization1.OptimizationType = catMinimum
```
            oOptimization1.AlgorithmType = catSimulatedAnnealing

```

```

```

oOptimization1.OptimizationType = catMinimum
```vbscript
```vbscript
oOptimization1.AlgorithmType = catSimulatedAnnealing
```vbscript
            'Set up the optimization feature attributes.
            oOptimization1.MaxEvalsNb = 300
```
            oOptimization1.UseMaxTime = True
            oOptimization1.MaxTime = 2 '2 minutes.
            oOptimization1.UseMaxEvalsWoImprovement = True
            oOptimization1.MaxEvalsWoImprovement = 20

```

```

```vbscript
```vbscript
```vbscript
```vbscript
            'Set up the free parameters of the optimization and their steps (this is optional).
    	'The step helps the algorithm to get an order of magnitude of the changes of values
```
    	'acceptable for each free parameters.
```

```

```

```vbscript
```vbscript
            Dim oFreeParameters As FreeParameters
```vbscript
```
```vbscript
            Set oFreeParameters = oOptimization1.FreeParameters
```
```

            oFreeParameters.AddFreeParameter(oX)
```

```vbscript
```vbscript
```vbscript
            'The following is optional, but usually reducing the range of input parameters helps to
            'solve the problem faster. In this case there only is one free parameter but optimizations
            ' can be run with multiple free parameters.
```vbscript
            Dim p As FreeParameter
            For Each p in oFreeParameters
```
```

```

```

```vbscript
```vbscript
```vbscript
' can be run with multiple free parameters.
```vbscript
Dim p As FreeParameter
```
```

```

```

For Each p in oFreeParameters
```vbscript
```vbscript
                    p.Step = 0.1
                    p.InfRange = -1000
                    p.SupRange = 2000
            Next
```vbscript
            'Set the parameter that must be optimized.
            oOptimization1.ObjectiveParameter = oFx
```
```

```

            msgbox "Before optimisation :" & oFx.Name & " =  " & oFx.Value & " and " & oX.Name & " = " & oX.Value
```vbscript
            'Running the optimization without the progress bar dialog box (False).
```

            oOptimization1.Run False

```vbscript
```vbscript
'Running the optimization without the progress bar dialog box (False).
```

oOptimization1.Run False
            msgbox "After optimisation :" & oFx.Name & " =  " & oFx.Value & " and " & oX.Name & " = " & oX.Value
```vbscript
            ' Update the document
```

```

```vbscript
```vbscript
```vbscript
            CATIA.ActiveDocument.Part.Update

```
```

```

    else
```vbscript
       MsgBox "The active document must be a CATPart"
```vbscript
```
```vbscript
    End If
```vbscript
    End Sub

```
```

```
