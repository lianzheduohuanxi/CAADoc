---
title: "About Collections"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: "["CATIA"]"
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfCollections.htm"
converted: "2026-05-11T17:31:52.408942"
---
## Infrastructure

 |
 ## About Collections

 * * *

  You will find below some tips to retrieve objects in collections.
 ---|---

 An item is retrieved from the collection using the **Item** method and the index of the item in the collection. Usually, the argument representing the index in the **Item** method is a Variant. This means that it can either represent the rank of the item in the collection or the name you assigned to this item using the **Name** property. The rank in a collection begins at 1. For example, assume that the document named **MyDocument** is the sixth document in the Documents collection. To retrieve this document in the **Doc** variable, write:

```vbscript
```vbscript
     Dim Doc As Document
```vbscript
```
```vbscript
```cpp
     Set Doc = CATIA.Documents.Item(6)

```
```

```

```

```vbscript
```vbscript
Dim Doc As Document
```vbscript
```
```cpp
Set Doc = CATIA.Documents.Item(6)
```
```

 or write:

```

```vbscript
```vbscript
     Dim Doc As Document
```vbscript
```
```vbscript
```cpp
     Set Doc = CATIA.Documents.Item("MyDocument")

```
```

```

```

```vbscript
```vbscript
Dim Doc As Document
```vbscript
```
```cpp
Set Doc = CATIA.Documents.Item("MyDocument")
```
```

 Each collection has a **Count** property that holds the number of items in the collection. This is a handy property to scan the whole collection. For example, to print the name of each document in the collection in a message box, write:

```

```cpp
     **For I = 1 To CATIA.Documents.Count**
       **msgbox CATIA.Documents.Item(I).Name**
```vbscript
```
     Next

```

```vbscript
Next
 or write:

     I = 0
     Do
       I = I + 1
```

```cpp
       **msgbox CATIA.Documents.Item(I).Name**
I = 0
```
Do
I = I + 1
```cpp
     Until I = **CATIA.Documents.Count**

 or you can use the **For Each** instruction to scan the collection, and get rid of the counter:
```

```vbscript
```cpp
     For Each Doc In CATIA.Documents
```
```

       **msgbox Doc.Name**
```vbscript
```cpp
For Each Doc In CATIA.Documents
```vbscript
```
```vbscript
     Next

```

```

```

 In this case, the **Doc** variable is reinitialized using the current document, starting with the first one and ending with the last one.

 The **For Each .. Next** syntax is available only with Windows.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
