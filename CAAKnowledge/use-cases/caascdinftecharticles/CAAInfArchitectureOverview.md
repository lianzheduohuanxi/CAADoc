---
title: "Object Architecture Overview"
category: "concept"
module: "CAAScdInfTechArticles"
tags: "["CATIA"]"
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfArchitectureOverview.htm"
converted: "2026-05-11T17:31:52.406949"
---
|
 ## Infrastructure

 |
 ## Object Architecture Overview

 * * *

  You will find in this section how the CAA V5 exposed Automation objects are described, and get information about:
     * **Object Diagrams, Object Descriptions and Object References** that shows you where and how objects are described
     * **About Objects, Collections, Properties, and Methods** that helps you understand the basics of the object technique required by scripting
     * **About Inheritance, Aggregation, and Object Model** that describes the two object mechanisms you need to know to write macros.
 ---|---
 ### Object Diagrams, Object Descriptions and Object References

 To describe objects, their properties and methods, and the relationships between objects, we use object diagrams and object descriptions.

 Object diagrams describe the overall structure of how objects are linked together:

 ![](../CAAScrAutomationImages/images/applicat.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/docs.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/doc.gif)](CAAInfObjDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parderim.gif)![](../CAAScrAutomationImages/images/partdoc.gif)[![Part Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdMmrTechArticles/CAAMmrTocPartDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/part.gif)](../CAAScdMmrTechArticles/CAAMmrObjPart.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/proddoc.gif)[![Product Structure Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdPstTechArticles/CAAPstTocProductDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)[![](../CAAScrAutomationImages/images/draftdoc.gif)](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)[![Drawing Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdDriTechArticles/CAADriTocDrawingDocument.md)![](../CAAScrAutomationImages/images/space.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/drsheets.gif)](../CAAScdDriTechArticles/CAADriObjDrawingSheets.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/analydoc.gif)[![Analysis Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/processdoc.gif)[![Process Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdDmiTechArticles/CAADmiTocActivity.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/functdoc.gif)[![Functional Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdFsiTechArticles/CAAFsiTocFunctionalDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/matdoc.gif)[![Material Document Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdMatTechArticles/CAAMatTocMaterial.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parlower.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/cataldoc.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/select.gif)

  **Legend** ![](../CAAScrAutomationImages/images/yellbox.gif) Collection
![](../CAAScrAutomationImages/images/purpbox.gif) Abstract object
![](../CAAScrAutomationImages/images/bluebox.gif) Object ![right arrow](../CAAScrAutomationImages/images/rtarrow.gif) Click arrow to expand chart
![](../CAAScrAutomationImages/images/uparrow.gif) Click arrow to return to previous chart
 ---|---

 You can learn from the diagram above that the **Application** object aggregates a **Documents** collection. The **Documents** collection aggregates any number of Documents. The **Document** object is an abstract object, and only its derived types can actually be created, that is:

     * The **PartDocument** for Part Design
     * The **ProductDocument** for Assembly Design
     * The **DrawingDocument** for Drafting
     * The **AnalysisDocument** for Analysis
     * The **ProcessDocument** for the Process modeler
     * The **FunctionalDocument** for the Product Functional Definition modeler
     * The **MaterialDocument** for materials
     * The **CatalogDocument**.

 All those documents inherit the **Selection** object aggregated by the **Document** object. But only the **PartDocument** object has an aggregated **Part** object, and only the **DrawingDocument** has an aggregated **DrawingSheets** collection.

 The ![](../CAAScrAutomationImages/images/rtarrow.gif) symbol shows that the object to which it refers, that is the object located just left of the symbol, is the root of an object structure expanded in another object diagram. The symbol ![](../CAAScrAutomationImages/images/uparrow.gif) shows that the root object near it can be found in one or several object diagrams as an object to expand.

```vbscript
```vbscript
 For main objects, _Object Descriptions_ describes how to use it.

```

```

```vbscript
```vbscript
 For all objects, _Object References_ contains complete reference of inheritance, properties and methods, thus encompassing all other link types between objects.

```

```

 ### About Objects, Collections, Properties, and Methods

```cpp
For all objects, _Object References_ contains complete reference of inheritance, properties and methods, thus encompassing all other link types between objects.
 Scripting languages such as Visual Basic rely on objects. Most pieces of data you can access are objects. With CATIA or DELMIA, documents, windows, viewers, cameras, parts, sketches, pads, even lines and curves, are represented as objects in Visual Basic. An _object_ is depicted using a blue box in the object diagrams, such as ![](../CAAScrAutomationImages/images/applicat.gif) .

```

 A _collection_ is an object that contains other objects. Like with stamps collecting, where all objects in the collection are stamps, a collection contains usually objects of the same type. For example a document collection contains documents. A collection is always denoted as a plural name to easily help recognize a collection among other objects. The document collection is thus named **Documents**. A collection is depicted using a yellow box in the object diagrams, such as ![](../CAAScrAutomationImages/images/docs.gif). The collection index begins at 1, and not 0. Usually, an object in the collection is reached using its index, but it can also be reached using the name you assign to it. This ability of referring to an object using its name in the collection is stated in the documentation of each collection object, such as **Documents** , when the index type is Variant, for example in the **Item** method.

 A _property_ is part of an object and helps to characterize it. For example, the Document object has the **FullName** property, which stores its full name, that is the file name that contains the document and the path to access this file. Retrieving property values of an object makes it possible to distinguish it among other objects of the same type. Modifying property values of an object changes the object characteristics and implies that the object itself is thus modified. To prevent from non-desired property modifications, an object can have read-only properties from which you can retrieve their values, but never set them.

 To retrieve or set the value of a property of a given object, write the object reference followed by a period and the property name. For example, you can retrieve in the **DocName** variable the value of  the full name of the active document as follows:

```cpp
 **DocName = CATIA.ActiveDocument.FullName**

 Or you can set this full name from the **DocName** variable as follows:
```

```cpp
 **CATIA.ActiveDocument.FullName = DocName**

Or you can set this full name from the **DocName** variable as follows:
```
```cpp
 An object reference always starts from the root object, that is the application object which is always set to **CATIA** with in-process access. Then you use the Application object's properties to access the objects. In this case, the application object has the **ActiveDocument** property which holds the active document. You simply need to write **CATIA.ActiveDocument** to refer to the active document. Then the Document object has the **FullName** property to hold its full name. Simply add a period followed by **FullName** , and you get this full name.

 In the same way, you can request to see the hidden elements of the active document by setting the value of its **SeeHiddenElements** property to **True** , as follows:
```

```cpp
 **CATIA.ActiveDocument.SeeHiddenElements = True**

 A _method_ is an action that you can request an object to do. For example, you can request to save the active document. To do this, the **Document** object includes the **Save** method. Simply request the document to save itself as follows:
```

```cpp
 **CATIA.ActiveDocument.Save**

 Methods have often arguments requested by the action. For example, the **SaveAs** method carries out the action of saving a document with another name than the current one. This new name must be provided to perform this action, otherwise the **SaveAs** method cannot work. This name is passed as an argument of the **SaveAs** method. To save the active document with the name **NewName** , proceed as follows:
```

```cpp
 **CATIA.ActiveDocument.SaveAs "NewName"**

 You will find in the **object reference** that each method is qualified as either a **Function** or a **Sub** , and with parentheses, even if they have no arguments, as follows:
```

```vbscript
```vbscript
     Function NewCamera(#) As Camera

     Sub Update(#)

```
```

```vbscript
 This is a Visual Basic notation to distinguish a method that returns a value, or **Function** , from one that doesn't, or **Sub**. Note that the returned value of a **Function** is indicated using the **As** keyword. In the example above, the **NewCamera** method is a **Function** because it returns a **Camera** object. See also **[Some Tips about Sub and Function](CAAInfSubFunction.md) **to know more about **Sub** and **Function**.
 ### About Inheritance, Aggregation, and Object Model
```

```vbscript
This is a Visual Basic notation to distinguish a method that returns a value, or **Function** , from one that doesn't, or **Sub**. Note that the returned value of a **Function** is indicated using the **As** keyword. In the example above, the **NewCamera** method is a **Function** because it returns a **Camera** object. See also **[Some Tips about Sub and Function](CAAInfSubFunction.md) **to know more about **Sub** and **Function**.
 Inheritance and aggregation are the two main kinds of relationship between objects.
```

 An object that inherits from another, named the _base_ object, inherits the properties and the methods of this base object and adds them to its own properties and methods. Inheritance helps to specialize objects while gathering common properties and methods in the base object. Inheritance is a iterative process, since an object can inherit from an object which itself inherits from another object which itself inherits, and so forth, and the lowest object in the inheritance tree inherits the properties and methods of all the objects above it. Inheritance is depicted using the following symbol ![](../CAAScrAutomationImages/images/parderiv.gif) in the object diagrams.

 In the following diagram, the **PartDocument** object is a specialized document that is dedicated to parts, and which inherits the properties and methods of the Document object. In addition, the PartDocument object has its own properties and methods. For example, PartDocument inherits the Save method from Document, like ProductDocument and DrawingDocument, and owns the **PartNumber** property, which is a specific property for a part, but which does not make sense for Document.

 ![](images/baspg0-36.gif) ![](../CAAScrAutomationImages/images/applicat.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/docs.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchildHigh.gif)![](../CAAScrAutomationImages/images/docWithmethod.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parderimH.gif)![](../CAAScrAutomationImages/images/partdocWithmethod.gif)[![Product Structure Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdPstTechArticles/CAAPstTocProductDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/proddoc.gif)[![Product Structure Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdPstTechArticles/CAAPstTocProductDocument.md)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)[![](../CAAScrAutomationImages/images/draftdoc.gif)](../CAAScdDriTechArticles/CAADriObjDrawingDocument.md)[![Product Structure Object Diagram](../CAAScrAutomationImages/images/rtarrow.gif)](../CAAScdPstTechArticles/CAAPstTocProductDocument.md)
 **Legend** ![](../CAAScrAutomationImages/images/yellbox.gif) Collection
![](../CAAScrAutomationImages/images/purpbox.gif) Abstract object
![](../CAAScrAutomationImages/images/bluebox.gif) Object ![right arrow](../CAAScrAutomationImages/images/rtarrow.gif) Click arrow to expand chart
![](../CAAScrAutomationImages/images/uparrow.gif) Click arrow to return to previous chart
 ---|---

 Assume that **MyPart** is a **PartDocument** document and is the active document. Assume that the **PartDocument** object has a **PartNumber** Read/Write property to return and set the part number. You can write the following to set its part number, and then save it:

 **MyPart.PartNumber = "123456789-0"
Assume that **MyPart** is a **PartDocument** document and is the active document. Assume that the **PartDocument** object has a **PartNumber** Read/Write property to return and set the part number. You can write the following to set its part number, and then save it:
MyPart.Save**

 In this example, the value of the **PartNumber** property owned by **MyPart** as a **PartDocument** object is modified, and then the **Save** method of the **Document** object is executed against **MyPart**.

 Some objects are depicted with a blue box with an italic typeface, such as ![](../CAAScrAutomationImages/images/doc.gif). These are abstract objects. An _abstract object_ owns properties and methods like any other object, but it cannot be created. Only objects which inherits from it and which are not abstract objects can be created. For example, the **Document** object is an abstract object which owns properties and methods shared by all documents, but cannot be created as such. Only objects of types **PartDocument** , **ProductDocument** , **DrawingDocument** , **AnalysisDocument** and **CatalogDocument** which inherit from it can actually be created. The active document referred to in the examples given in **About Objects, Collections, Properties, and Methods **is necessarily an instance of one of these types.

 _Aggregation_ is the ability of an object to contain another one. For example, the Application object contains (aggregates) a Documents collection object. Within CAA V5 automation objects models, the aggregation of a series of objects of the same type is usually reserved to collection objects. For example, the Documents collections contains (aggregates) a series of Documents, each of them being a PartDocument, a ProductDocument, or any other kind of Document object. Aggregation is depicted in Object Diagrams using a line between the two objects.

 You may find a _role_ description on this line. A **Prism** object for example aggregates two **Limit** objects, its first limit and its second limit:

 ![](../CAAScrAutomationImages/images/sketshap.gif)
![](../CAAScrAutomationImages/images/parderil.gif)![](../CAAScrAutomationImages/images/parchila.gif)![](../CAAScrAutomationImages/images/sketch.gif)
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/prism.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/propprism1limit.gif)![](../CAAScrAutomationImages/images/limit.gif)
![](../CAAScrAutomationImages/images/space.gif)![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/propprism2limit.gif)![](../CAAScrAutomationImages/images/limit.gif)
 ---

 The aggregation link is bi-directional because the **Parent** property of each object allows to retrieve its aggregating object. For clarification purpose, mono-directional relationships may be visible on a diagram. They are depicted using the following symbol ![](../CAAScrAutomationImages/images/parderiv.gif) .

 Here, for example, the **Sketch** object is aggregated by a **Sketches** collection that is not visible but is referred to by the **SketchBasedShape** object.

 * * *

 ![](../CAAScrAutomationImages/images/propprism1limit.gif)
 #### References

 [1] | [Infrastructure Automation Objects](CAAInfTocApplication.md)
 ---|---

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
