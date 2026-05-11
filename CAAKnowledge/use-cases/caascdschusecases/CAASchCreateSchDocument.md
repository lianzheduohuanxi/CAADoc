---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASchSCH_Detail01", "CAAScrBase", "CAAInfLauchMacro", "CAASchCreateSchDocumentSource", "CAAScdInfUseCases", "CAASchCreateSchDocument", "CAASCH_Detail01", "CAAScdSchUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocument.htm"
converted: "2026-05-11T11:06:32.607080"
---

## Schematics Platform Modeler
 
 
## []Creating a Schematic Document from an Existing 
 Document
 
 
 
 

---

 
 
 
 ![](../CAAScrBase/images/atarget.gif)
 |[]This macro shows you how to create a 
 new schematic document from an opened document.

This macro opens the 
 document CAASchSCH_Detail01.CATProduct. From the root object of this 
 document, the macro obtains a handle on the current CNEXT session. The 
 macro creates a new schematic document and add it to this session.
 
 
 ![](../CAAScrBase/images/ainfo.gif)
 |[]CAASchCreateSchDocument is launched in 
 CATIA [[1]]. No open document is needed.

 [
 CAASchCreateSchDocument.CATScript ]is located in the CAAScdSchUseCases 
 module. [Execute macro] 
 (Windows only).
 
 
 ![](../CAAScrBase/images/ascenari.gif)
 |[]CAASchCreateSchDocument includes the 
 following steps:

 
- [Prolog]
 
- [Get a the current CNEXT session]
 
- [Create a new schematic document]
 
- [Set the drawing standard]
 
 
#### []Prolog
 

The macro first loads CAASCH_Detail01.CATProduct.
 
 
 |    ...

    ' Open the schematic document 
 

    Dim sFilePath

    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _

            "online\CAAScdSchUseCases\samples\CAASCH_Detail01.CATProduct")

 

    Dim objSchDoc As Document

    Set objSchDoc = CATIA.Documents.Open(sFilePath)

   
 ...
 
 
 

Next, the macro acquires the schematic root object from the document. 
 The schematic root is the top node of the object instance tree in a 
 schematic document.
 
 
 |    ...

   
 ' Find the top node of the schematic object tree - schematic root.

    Dim objPrdRoot As Product

    Dim objSchRoot As SchematicRoot

    If ( Not ( objSchDoc Is Nothing ) ) Then

      Set objPrdRoot = objSchDoc.Product
 

      If ( Not ( objPrdRoot Is Nothing ) ) Then

        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")

      End If

    End If

   
 ...
 
 
 
#### []Get a the current CNEXT session
 

Using the GeSchematicSession method, a handle on the SchSession 
 interface can be obtained. This interface provides a method to create a new 
 schematic document.
 
 
 |    ...

      
 '-----------------------------------------------------------------------

      
 ' Get the schematic session.

      
 '-----------------------------------------------------------------------

 

       Set objSchSession = objSchRoot.GetSchematicSession

   
 ...
 
 
 
#### []Create a new schematic document
 
 
 |    ...

          '---------------------------------------------------------------------

        
 ' Create another schematic document.

        
 '---------------------------------------------------------------------

        
 'bInteractive = true

         bInteractive = false

         objSchSession.CreateDocument "CATProduct",bInteractive,objSchDocNew

   
 ...
 
 
 
#### []Set the drawing standard of the 
 drafting viewer in the schematic document
 

A schematic document has a drafting viewer embedded in it. The drawing 
 standard of that drafting viewer can be set by calling the 
 SetDrawingStandard method. This macro also illustrates how to use the 
 GetDrawingStandard method to retrieve the drawing standard of a schematic 
 document.
 
 
 |    ...

         If ( Not ( objSchDocNew Is Nothing ) ) Then

 

            Set objPrdRoot = Nothing

            Set objSchRoot = Nothing

 

            Set objPrdRoot = objSchDocNew.Product
 

            If ( Not ( objPrdRoot Is Nothing ) ) Then

               Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")

            End If

 

            If ( Not ( objSchRoot Is Nothing ) ) Then

               objSchRoot.SetDrawingStandard catISO

               strMessage = strMessage & "drawing standard set to catISO" & vbCr

               Dim std As CatDrawingStandard

               std = objSchRoot.GetDrawingStandard

               strMessage = strMessage & "drawing standard = " & std & vbCr

            End If

   
 ...
 
 
 
 
 
 

[[Top]]

---

 
 
#### []In Short
 

This use case shows how to create a schematic document from the root of an 
 existing document. A message logging the status of the critical steps is 
 displayed at the end of the use case. 
 

 ![](images/CAASchCreateSchDocument.jpg)
 

[[Top]]

---

 
 
#### []References
 
 
 |[1]
 |[
 Replaying a Macro]
 
 
 
 
 |[[Top]]
 
 
 

---

 
 

*Copyright 2001, Dassault Systmes. All rights reserved.*