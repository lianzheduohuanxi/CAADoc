---
title: "Product Document Automation Objects"
category: "general"
module: "CAAScdPstTechArticles"
tags: ["CATIA", "CATIAFixTogethers"]
source_file: "Doc\online\CAAScdPstTechArticles\CAAPstTocProductDocument.htm"
converted: "2026-05-11T17:31:52.343589"
---

# Product Document Automation Objects

| ![](../CAAScrAutomationImages/images/proddoc.gif)[![Application Object Diagram](../CAAScrAutomationImages/images/uparrow.gif)](../CAAScdInfTechArticles/CAAInfTocApplication.htm)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/product.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/products.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/publics.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/public.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)[![](../CAAScrAutomationImages/images/constrs.gif)](../CAAScdMmrTechArticles/CAAMmrObjConstraints.htm)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/constrnt.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/fixtgrs.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/fixtgr.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/move.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/position.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/analyze.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/relatns.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/relation.gif)[![Relation Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdKniTechArticles/CAAKniTocRelation.htm)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/params.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/param.gif)[![Parameter Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdKniTechArticles/CAAKniTocParameter.htm)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/psttechobj.gif)![](../CAAScrAutomationImages/images/anyobj.gif)  
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/getitem.gif)![](../CAAScrAutomationImages/images/anyobj.gif)  
![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/parderim.gif)![](../CAAScrAutomationImages/images/asmconv.gif)  
![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/matmanager.gif)  
![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/space2.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/posmat.gif)  
---  
  
**Legend**

![](../CAAScrAutomationImages/images/yellbox.gif) Collection  
![](../CAAScrAutomationImages/images/purpbox.gif) Abstract object  
![](../CAAScrAutomationImages/images/bluebox.gif) Object

![right arrow](../CAAScrAutomationImages/images/rtarrow.gif) Click arrow to expand chart  
![](../CAAScrAutomationImages/images/uparrow.gif) Click arrow to return to previous chart

The **ProductDocument** object aggregates, or includes, a product tree structure starting with a single product, named the root product, which includes a collection of products. Each of the products of this collection can itself include a collection of products, and so forth.

Each product is positioned in the 3D space thanks to the **Position** object which represents the product's 3D-axis system expressed with respect to the assembly's 3D-axis system. The **Move** object allows the object moving. Constraints can be set to constrain the product's position and move.

The following diagram shows such a tree structure for a (simple) car.

![](images/baspp3-2.gif)

A given product, such as the cylinder head or the gear box, is in fact a product component of a product reference. This product reference is neither accessible using macros nor from interactive commands. It is nevertheless created when you create a product component. Products that appear duplicated, such as the wheels, can be product components pointing to the same product reference. In this example, the LeftRearWheel and RightRearWheel objects can be two product components of a single wheel product reference. Creating references enables consistency management. When a modification is brought to a product, such as its part number, or its master shape representation which we'll see below, the modification is brought through a component to the reference, and is propagated to all the components which point to this reference.

The root product is retrieved by the **ProductDocument** object using its **Product** property. Each product, starting with the root product, may include a **Products** collection which gathers all the products just below this product in the product tree structure. This collection is built using the **AddNewProduct** , **AddComponent** and **AddExternalComponent** methods:

  * **AddNewProduct** creates both a reference to the product and a component in the **ProductDocument**
  * **AddComponent** creates a product component from a product reference already existing in the **ProductDocument** , that is a product component of a product already created in any of the **Products** collection of the **ProductDocument** using the **AddNewProduct** method
  * **AddExternalComponent** creates a product component using the root product of another **ProductDocument**.



Each product reference can have a master shape representation which defines its geometry, material properties, and so forth, and used to display or print it, and maybe more, for example to analyze or manufacture it. This is optional, but is often required to represent actual products. This master shape representation is shared by all the components pointing to this product reference, and can be a CATIA Version 4 model, a CATIA Version 5 part, a VRML file, or whatever format supported by CATIA Version 5. The methods **AddMasterShapeRepresentation** , **RemoveMasterShapeRepresentation** , and **GetMasterShapeRepresentation** manage the master shape representation.

Each product component in the tree structure is positioned in the space according to the position of its own 3D-axis system with respect to the product document's 3D axis-system, this position being possibly determined according to positioning constraints relative to the product above it in the tree structure. This means that each product component is positioned with respect to the root product according to a cascading position combination from the root product to the current product across the product tree structure. Its position can be set or retrieved using the **Position** property, whatever the constraints applied. The **Move** property allows a movable object retrieval to move the product as required by a move operation while ensuring that the positioning constraints are matched. The movable object returned is the product object itself, meaning that a product is movable, but with some other applications, this could be different. For example, the movable object returned from an edge in a pad is the whole pad, since the edge cannot be moved alone and is linked to the other edges and faces in the pad. The actual move is performed using the **Apply** method. This method takes a table with twelve items as input which define the move. This table contains the move matrix elements and has the following structure, assuming that `M` is the table identifier:
    
    
    M(0)=Ux M(3)=Vx M(6)=Wx M(9)=Tx
    M(1)=Uy M(4)=Vy M(7)=Wy M(10)=Ty
    M(2)=Uz M(5)=Vz M(8)=Wz M(11)=Tz

The first nine items represent an axis rotation, and the last three a translation. It expresses the product 3D-axis system (T,U,V,W) with respect to the root product 3D-axis system(O,xy,z), where:

  * `Ux`, `Uy` and `Uz` are the components of the U vector with respect to (O,x,y,z)
  * `Vx`, `Vy` and `Vz` are the components of the V vector with respect to (O,x,y,z)
  * `Wx`, `Wy` and `Wz` are the components of the W vector with respect to (O,x,y,z)
  * `Tx`, `Ty` and `Tz` are the coordinates of the new origin T with respect to (O,x,y,z)



![](images/baspp3-4.gif)

The two collections of **Constraint** and **FixTogether** objects can be retrieved from the root product object using its `Connections` method. For example, assuming `product1` is the root product, the **FixTogethers** collection can be retrieved as follows.
    
    
    Dim fixTogethers1 As FixTogethers
    Set fixTogethers1 = product1.Connections("CATIAFixTogethers")

The **AssemblyConvertor** , **MaterialManager** , and **PositionedMaterial** objects can be retrieved from the root product using its `GetItem` method, with  the "BillOfMaterial", "CATMatManagerVBExt", and "CATMaterialVBExt" strings as argument respectively. Here is an example to retrieve the **MaterialManager** object from the **Product** object. 
    
    
    Dim oRootProduct As Product
    ...
    Dim oMatManager As MaterialManager
    Set oMatManager = oRootProduct.GetItem("CATMatManagerVBExt")

Note that the **MaterialManager** and the **PositionedMaterial** objects can be retrieved the same way from the **Part** object.

* * *

_Copyright © 1999-2013, Dassault Systèmes. All rights reserved._
