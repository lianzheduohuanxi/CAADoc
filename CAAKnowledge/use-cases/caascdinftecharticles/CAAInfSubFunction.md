---
```vbscript
title: "About Subs and Functions"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfSubFunction.htm"
converted: "2026-05-11T17:31:52.446744"
```

---
## Infrastructure

 |
 ## About Subs and Functions

 * * *

 A method exposed by an objects is called by Visual Basic:

     * a **Sub** if it doesn't return any value
     * a **Function** if its does.

 Be careful when the methods requests arguments. To pass arguments to a **Sub** with Visual Basic Script, do not use parentheses as follows:

> Object.Sub arg1, arg2, arg3

 But use parentheses with a **Function** :

> Dim ReturnedObject As AnyObject
```vbscript
```vbscript
    Set ReturnedObject = Object.Function (arg1, arg2, arg3)

```

```

```vbscript
Set ReturnedObject = Object.Function (arg1, arg2, arg3)
 You must use **Set** only if the returned value is an object, but not if it is a character string or a number. Nevertheless, character string and number defined as CATIA literals are objects and **Set** must be used if a **Function** returns a literal object.

```

 Finally, you don't have to use **Set** if you store your return value in a **Property** :

> myObject.aggregatedObject = Object.Function (arg1, arg2, arg3)

 because there is no actual _aggregatedObject_ variable, a property is a syntactical shortcut for _accessor_ methods, here _get_aggregatedObject_ and _set_aggregatedObject_ , allowing to present those methods as an attribute of the object. The previous syntax is so equivalent to:

> myObject.set_aggregatedObject( Object.Function (arg1, arg2, arg3) )

 and no **Set** is required.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
