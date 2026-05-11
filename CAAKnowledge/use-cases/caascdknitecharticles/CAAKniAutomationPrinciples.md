---
```vbscript
title: "Knowledge Advisor Overview"
category: "concept"
module: "CAAScdKniTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdKniTechArticles/CAAKniAutomationPrinciples.htm"
converted: "2026-05-11T17:31:52.000294"
```

---
## Automation

|
## Knowledge Advisor Overview

* * *

This article provides the basis for understanding how to create macros using knowledgeware features. These
knowledgeware features are supplied in the Infrastructure product (parameters, formulas and design tables) as
well as in the Knowledge Advisor product (rules and checks).

The CATIA Knowledge Advisor automation objects are those whereby you can create and manipulate the knowledgeware features in a script. These automation objects can be divided into two categories:

  1. The objects which provide you with the creation methods. They are the _Relations_ and _Parameters_ collections. These objects are only implemented on CATPart documents.
  2. The knowledgeware objects whereby you can manipulate the Parameter, Formula, Rule, Check and  Design Table features once they have been created. The hierarchy of these objects is described in the [Parameter](CAAKniTocParameter.md) and [Relation](CAAKniTocRelation.md) tree structures.

The Use Cases provided as samples are fully commented and should help you understand how to
proceed to write simple macros as well as fully-fledged macros manipulating knowledgeware features.

### Creating Knowledgeware Objects

The Use Cases provided as samples are fully commented and should help you understand how to
proceed to write simple macros as well as fully-fledged macros manipulating knowledgeware features.
The entry point is the Relations or Parameters collection. To retrieve the appropriate collection, you must: retrieve the Part object of the active document. This Part object aggregates all the objects making up the CATPart: the Bodies, the Relations, the Parameters to name but a few. Mull over the Part properties, they all provide you with collections or factories to create objects.

You can retrieve a Parameters object that way:

```vbscript
    Dim oActiveDoc As Document
```vbscript
```vbscript
    Set oActiveDoc = CATIA.ActiveDocument

    Dim oParams As Parameters
    Set oParams = oActiveDoc.Part.Parameters

```

```

```

```vbscript
Dim oParams As Parameters
```vbscript
Set oParams = oActiveDoc.Part.Parameters
```

```

but prior to writing this, you must check that your document is a CATPart.

To create the object, you just have to use the appropriate Create _xxx_ method.

```vbscript
    Dim oSphereRadius As Parameter
```vbscript
```vbscript
    Set oSphereRadius = oParameters.CreateInteger("StringLength",0)

```

```

```

### Scanning the Knowledgeware Objects in their Collections

Parameters as well as Relations can be scanned in their collections. An item is retrieved from its collection using the **Item** method and the index of the item in the collection. Usually, the argument representing the index in the **Item** method is a Variant. This means that it can either represent the rank of the item in the collection or the name you assigned to this item using the **Name** property. The rank in a collection begins at 1. For example, assume that the Parameter named "StringLength" is the sixth parameter in the Parameters collection. To retrieve this parameter in the oParameters collection, write:

```vbscript
    Dim oParam1 As Parameter
```vbscript
```vbscript
    Set oParam1 = oParams.Item(6)

```

```

```

```vbscript
Dim oParam1 As Parameter
```vbscript
Set oParam1 = oParams.Item(6)
```

```

or write:

```vbscript
    Dim oParam1 As Parameter
```vbscript
```vbscript
    Set oParam1 = oParams.Name("StringLength")

```

```

```

```vbscript
Dim oParam1 As Parameter
```vbscript
Set oParam1 = oParams.Name("StringLength")
```

```

Each collection has a **Count** property that holds the number of items in the collection. This is a handy property to scan the whole collection.

_**Warning**_

When counting the items in a Parameters collection, mind that you count all the document parameters and not only the user parameters.

### Manipulating Knowledgeware Objects

_**Warning**_
When counting the items in a Parameters collection, mind that you count all the document parameters and not only the user parameters.
After they have been created, knowledgeware objects are managed through their properties and methods. To find out what they are, see the Knowledge Advisor Automation API Reference.

[Top]

* * *

_Copyright 1994-2004, Dassault Systmes. All rights reserved._
