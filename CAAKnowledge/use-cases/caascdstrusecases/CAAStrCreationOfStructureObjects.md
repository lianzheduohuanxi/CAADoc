---
title: "Untitled"
category: "use-case"
module: "CAAScdStrUseCases"
tags: ["CAAScrBase", "CAAStrCreationOfStructureObjectsSource", "CATIA", "CAAScrJavaScript", "CAAScdInfUseCases", "CAAScdStrUseCases", "CAAStrCreationOfStructureObjects", "CAAInfLauchMacro", "CAAScdStrImg1"]
source_file: "Doc/online/CAAScdStrUseCases/CAAStrCreationOfStructureObjects.htm"
converted: "2026-05-11T11:27:02.596959"
---

---

      

This step describes how to get the structure object factory.
      

#### Creating ends of members
      
      

We have to define all the ends we need to define the members. All 
      these ends are on grid geometry.
      

#### Creating members
      
      

Members are created using the section document and ends defined in the
      previous step. The variable sectionName has to be valuated with the
      section path.
      

#### Creating end-plates
      
      

End plates are created at  the base of each member.
      

#### Creating a plate
      
      

We have created a plate on top of the four members. The contour is
      defined by the selection of  vertices on these members.
      

 
    
  

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create structure objects

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
    Dim doc As Document

    Dim StrWorkbench As StrWorkbench
    Dim strFactory As StrObjectFactory

    Set doc = CATIA.ActiveDocument
    Dim rootProduct As Product
    Set rootProduct = doc.Product

    Set StrWorkbench = doc.GetWorkbench(&quot;StrWorkbench&quot;)
    Set strFactory = rootProduct.GetTechnologicalObject(&quot;StructureObjectFactory&quot;)

    Dim documents As Documents
    Set documents = CATIA.Documents
  ...
```

```vbscript
...
  ' column 1
    Dim reference11 As Reference
    Set reference11 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.12;(Brp:(GSMPlane.3);Brp:(GSMIntersect.10;(Brp:(GSMPlane.1);Brp:(GSMPlane.2)))));None:(Limits1:();Limits2:()));GSMIntersect.12)&quot;)
    Dim extremity11 As AnyObject
    Set extremity11 = strFactory.AddDefExtFromReference(reference11, 0)

    Dim reference12 As Reference
    Set reference12 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.11;(Brp:(xy-plane);Brp:(GSMIntersect.10;(Brp:(GSMPlane.1);Brp:(GSMPlane.2)))));None:(Limits1:();Limits2:()));GSMIntersect.11)&quot;)
    Dim extremity12 As AnyObject
    Set extremity12 = strFactory.AddDefExtFromReference(reference12, 0)

    ' column 2
    Dim reference21 As Reference
    Set reference21 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.9;(Brp:(GSMPlane.3);Brp:(GSMIntersect.7;(Brp:(GSMPlane.1);Brp:(zx-plane)))));None:(Limits1:();Limits2:()));GSMIntersect.9)&quot;)
    Dim extremity21 As AnyObject
    Set extremity21 = strFactory.AddDefExtFromReference(reference21, 0)

    Dim reference22 As Reference
    Set reference22 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.8;(Brp:(xy-plane);Brp:(GSMIntersect.7;(Brp:(GSMPlane.1);Brp:(zx-plane)))));None:(Limits1:();Limits2:()));GSMIntersect.8)&quot;)
    Dim extremity22 As AnyObject
    Set extremity22 = strFactory.AddDefExtFromReference(reference22, 0)

    ' column 3
    Dim reference31 As Reference
    Set reference31 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.5;(Brp:(xy-plane);Brp:(GSMIntersect.4;(Brp:(yz-plane);Brp:(GSMPlane.2)))));None:(Limits1:();Limits2:()));GSMIntersect.5)&quot;)
    Dim extremity31 As AnyObject
    Set extremity31 = strFactory.AddDefExtFromReference(reference31, 0)

    Dim reference32 As Reference
    Set reference32 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.6;(Brp:(GSMPlane.3);Brp:(GSMIntersect.4;(Brp:(yz-plane);Brp:(GSMPlane.2)))));None:(Limits1:();Limits2:()));GSMIntersect.6)&quot;)
    Dim extremity32 As AnyObject
    Set extremity32 = strFactory.AddDefExtFromReference(reference32, 0)

    ' column 4
    Dim reference41 As Reference
    Set reference41 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.3;(Brp:(GSMPlane.3);Brp:(GSMIntersect.1;(Brp:(yz-plane);Brp:(zx-plane)))));None:(Limits1:();Limits2:()));GSMIntersect.3)&quot;)
    Dim extremity41 As AnyObject
    Set extremity41 = strFactory.AddDefExtFromReference(reference41, 0)

    Dim reference42 As Reference
    Set reference42 = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Selection_BorderFVertex:(BEdge:(Brp:(GSMIntersect.2;(Brp:(xy-plane);Brp:(GSMIntersect.1;(Brp:(yz-plane);Brp:(zx-plane)))));None:(Limits1:();Limits2:()));GSMIntersect.2)&quot;)
    Dim extremity42 As AnyObject
    Set extremity42 = strFactory.AddDefExtFromReference(reference42, 0)
  ...
```

```vbscript
...
    dim sectionName as string
    sectionName = InputBox(&quot;Section path&quot;,&quot;Parameters&quot;, &quot;...\HEA120.CATPart&quot;)
    
    ' column 1    
    Dim docSection1 As Document
    Set docSection1 = documents.Read(sectionName)

    Dim section1 As StrSection
    Set section1 = strFactory.AddSection(docSection1)

    dim member1 as StrMember
    Set member1 = strFactory.AddMember(section1, &quot;catStrCenterCenter&quot;, 0, extremity11, extremity12, &quot;Column&quot;)
        
    ' column 2
    Dim docSection2 As Document
    Set docSection2 = documents.Read(sectionName)

    Dim section2 As StrSection
    Set section2 = strFactory.AddSection(docSection2)

    dim member2 as StrMember
    Set member2 = strFactory.AddMember(section2, &quot;catStrCenterCenter&quot;, 0, extremity21, extremity22, &quot;Column&quot;)
        
    ' column 3
    Dim docSection3 As Document
    Set docSection3 = documents.Read(sectionName)

    Dim section3 As StrSection
    Set section3 = strFactory.AddSection(docSection3)

    dim member3 as StrMember
    Set member3 = strFactory.AddMember(section3, &quot;catStrCenterCenter&quot;, 0, extremity31, extremity32, &quot;Column&quot;)
        
    ' column 4
    Dim docSection4 As Document
    Set docSection4 = documents.Read(sectionName)

    Dim section4 As StrSection
    Set section4 = strFactory.AddSection(docSection4)

    dim member4 as StrMember
    Set member4 = strFactory.AddMember(section4, &quot;catStrCenterCenter&quot;, 0, extremity41, extremity42, &quot;Column&quot;)
  ...
```

```vbscript
...
    Dim plate1 As StrPlate
    Set plate1 = strFactory.AddRectangularEndPlate(member1, catEndExtremity, 0.005, 0.2, 0.2, catStrStandardOrientation, &quot;EndPlate&quot;)
	
    Dim plate2 As StrPlate
    Set plate2 = strFactory.AddRectangularEndPlate(member2, catEndExtremity, 0.005, 0.2, 0.2, catStrStandardOrientation, &quot;EndPlate&quot;)
	
    Dim plate3 As StrPlate
    Set plate3 = strFactory.AddRectangularEndPlate(member3, catStartExtremity, 0.005, 0.2, 0.2, catStrStandardOrientation, &quot;EndPlate&quot;)
	
    Dim plate4 As StrPlate
    Set plate4 = strFactory.AddRectangularEndPlate(member4, catEndExtremity, 0.005, 0.2, 0.2, catStrStandardOrientation, &quot;EndPlate&quot;)
```

```vbscript
...
```

```vbscript
...
    Dim contour(3) As Reference

    Set contour(0) = rootProduct.CreateReferenceFromName("Produit1/Column_2/!Selection_FVertex:(Vertex:(Neighbours:(Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;9999)));None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;1);None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10018)));None:();Cf11:()));Cf11:());StrFunRibSweep.1;Z0;G4702)")
    Set contour(1) = rootProduct.CreateReferenceFromName("Produit1/Column_4/!Selection_FVertex:(Vertex:(Neighbours:(Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10039)));None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;2);None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10058)));None:();Cf11:()));Cf11:());StrFunRibSweep.1;Z0;G4702)")
    Set contour(2) = rootProduct.CreateReferenceFromName("Produit1/Column_5/!Selection_FVertex:(Vertex:(Neighbours:(Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10068)));None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;1);None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10069)));None:();Cf11:()));Cf11:());StrFunRibSweep.1;Z0;G4702)")
    Set contour(3) = rootProduct.CreateReferenceFromName("Produit1/Column_3/!Selection_FVertex:(Vertex:(Neighbours:(Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10029)));None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;1);None:();Cf11:());Face:(Brp:(StrFunRibSweep.1;0:(Brp:(GSMLine.1);Brp:(IntSection.1;10030)));None:();Cf11:()));Cf11:());StrFunRibSweep.1;Z0;G4702)")

    Dim support As Reference
    Set support = rootProduct.CreateReferenceFromName(&quot;Produit1/grid/!Plane.3&quot;)

    Dim plate As StrPlate
    Set plate = strFactory.AddPlate(support, 0.005, catStrStandardOrientation, contour, 0.0, &quot;PlateType&quot;)
```

```vbscript
...
```