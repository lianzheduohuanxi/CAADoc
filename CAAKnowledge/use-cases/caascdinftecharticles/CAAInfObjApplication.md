---
```vbscript
title: "Application Object"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjApplication.htm"
converted: "2026-05-11T17:31:52.425072"
```

---
# Application Object

source_file: "Doc/online/CAAScdInfTechArticles/CAAInfObjApplication.htm"
converted: "2026-05-11T17:31:52.425072"
 See Also | Use Cases | Properties | Methods  

 ![Application object](../CAAScrAutomationImages/images/applicat.gif)  
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/docs.gif)  
![](../CAAScrAutomationImages/images/parmult.gif)[![](../CAAScrAutomationImages/images/windows.gif)](CAAInfObjWindows.md)  
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/printers.gif)  
![](../CAAScrAutomationImages/images/parmult.gif)![](../CAAScrAutomationImages/images/filesys.gif)  
![](../CAAScrAutomationImages/images/parchild.gif)![](../CAAScrAutomationImages/images/sysserv.gif)  
 ---  

 **_Represents the current CNext application and its frame window._**

 CATIA products. The root object is the **Application** , which aggregates, or includes, **Documents** , a **Document** collection, and **Windows** , a **Window** collection. A collection is an object that gathers objects of the same type and is denoted as a plural name. **Documents** gathers **Document** objects and provides methods for managing individual documents in the collection.The documents belong to one of the four types, that is the **PartDocument** , the **ProductDocument,** the **DrawingDocument** and the **AnalysisDocument**. **Windows** gathers **Window** objects, and provides methods for managing individual windows in the collection.

 In addition to this functional view, we can superimpose another view to help understand some basic mechanisms:

 ![](images/baspp1-2.gif)

In addition to this functional view, we can superimpose another view to help understand some basic mechanisms:
 All objects, and not only those shown in this diagram, except collections, derive from the **AnyObject** abstract object which supplies the **Application** , **Name** , and **Parent** properties. You can then use these properties and this method against any object, since any object features them. All collections derive from the **Collection** abstract object which supplies in addition the **Count** property.

 The **Application** property returns the application to which an object belongs. When running in-process macros, there is only one application named **CATIA**. The **Name** property allows any object to be assigned a name. The **Parent** property allows the parent object to be retrieved, the parent object being the object which aggregates the current one. The **Count** property of the **Collection** object returns the number of items in the collection. In addition, a **Collection** object can supply an Item, an **Add** , and a **Remove** method.

 The root object for all CATIA macros is **Application** . This corresponds to the CATIA frame window. The CATIA application is always named **CATIA** for in-process access, and you should only refer to it since it already exists when you run an in-process macro. The application aggregates, or includes, a document collection accessed using the **Documents** property, and a >window collection accessed using the **Windows** property. The document collection stores the currently opened documents and the window collection stores the currently opened windows for these documents. The active document is the document opened in the active window, that is the window in which the end-user is currently working. They are accessed using the **ActiveDocument** and the **ActiveWindow** properties respectively.

 The **Application** object has other properties, such as **FileSearchOrder** which allows a pathname concatenation searched for when opening files to be set or retrieved. As the application represents the frame window, you can set the frame dimensions and location using the properties **Width** , **Height** , **Left** and **Top** respectively, with values expressed in screen pixels.

 The **Application** object aggregates also a **SystemService** object which provides for example the **Environ** method to get the value of a given environment variable.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
