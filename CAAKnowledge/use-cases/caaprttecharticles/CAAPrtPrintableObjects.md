---
title: "Making Your Components Printable"
category: "tech-article"
module: "CAAPrtTechArticles"
tags: "["CAACmp", "CAAECmpPrintable", "CAACmpInstanceToPrint", "CATIPrintable", "CAACmpImage"]"
source_file: "Doc/online/CAAPrtTechArticles/CAAPrtPrintableObjects.htm"
converted: "2026-05-11T17:17:56.147286"
---
# 3D PLM Enterprise Architecture

|
## 3D Visualization - Print

|
### Making Your Components Printable

_How to enable your components for printing_
---|---|---
Technical Article

* * *
### Abstract

This article explains how you can make your own components printable.

  * **Understanding Printable Components and Images**
  * **Implementing the _CATIPrintable_ Interface**
  * **Creating the Printable Image Class**
  * **In Short**
  * **References**

* * *
### Understanding Printable Components and Images

An component becomes printable when you can build a printable image of it. As an example, a _CATViewer_ instance is a printable component because you can build from it its printable image companion, that is a _CATPrintViewerImage_ instance able to decode the contents of the viewer and to perform rendering not on the screen but on the paper. The Print framework provides the following classes to make printable the main CAA V5 components:

CAA V5 Printable Components | Corresponding Printable Images

An component becomes printable when you can build a printable image of it. As an example, a _CATViewer_ instance is a printable component because you can build from it its printable image companion, that is a _CATPrintViewerImage_ instance able to decode the contents of the viewer and to perform rendering not on the screen but on the paper. The Print framework provides the following classes to make printable the main CAA V5 components:
CAA V5 Printable Components | Corresponding Printable Images
CATViewer | CATPrintViewerImage
CAT2DBagRep | CATPrint2DRepImage
CAT2DBagRep | CATPrint3DRepImage
CATPrintFile | CATPrintFileImage
CATPixelImage | CATPrintPixelImage

Any component can be made printable. For example, a class deriving from _CATFrmWindow_ could implement _CATIPrintable_ to return an image of its main viewer, or a composition gathering several of its viewers if needed.

To make a component of your own printable, you need to:

  1. Make your component implement the _CATIPrintable_ interface
The `CreatePrintableImage` method of _CATIPrintable_ should return a pointer to an instance of the printable image class associated with the component
  2. Create this printable image class
This class should implement two methods:
     1. `GetSize` to determine and return the component size
     2. `Decode` that draws the component image to print using a set of print parameters.

These methods are called by the `Print` method of the _CATPrinterDevice_ or of the _CATPrintImage_ classes when the print is requested.

Assume that the component to make printable is represented by the main class _CAACmp_. This component must implements the _CATIPrintable_ interface, for example using the _CAAECmpPrintable_ code extension class of _CAACmp_. Then, the _CAACmpImage_ class, printable image companion class of _CAACmp_ , will do the printing job.

[Top]
### Implementing the CATIPrintable Interface

_CATIPrintable_ includes the single `CreatePrintableImage` method that should return a pointer to an instance of the printable image class associated with the component.

![](images/CAACATIPrintable.gif)

The _CAAECmpPrintable_ header file is as follows:

    #include "CATBaseUnknown.h"
The _CAAECmpPrintable_ header file is as follows:
    class CAAECmpPrintable : public CATBaseUnknown

    {
The _CAAECmpPrintable_ header file is as follows:
class CAAECmpPrintable : public CATBaseUnknown
      CATDeclareClass;
      public :
        CAAECmpPrintable(#);
        virtual ~CAAECmpPrintable(#);
        virtual CATPrintImage * **CreatePrintableImage**(void);
```vbscript
      private :

```

        **CAAECmpPrintable(const CAAECmpPrintable & printableObjectToCopy);
```cpp
CAAECmpPrintable(#);
virtual ~CAAECmpPrintable(#);
virtual CATPrintImage * **CreatePrintableImage**(void);
private :
        CAAECmpPrintable & operator = (const CAAECmpPrintable & printableObjectToCopy);
```

    **};

---

CAAECmpPrintable & operator = (const CAAECmpPrintable & printableObjectToCopy);
The `CATDeclareClass` macro [1] declares that _CAAECmpPrintable_   is part of a component. As any extension class, it features a default constructor and a destructor declared as public. This enables it to be instantiated when a pointer to _CATIPrintable_ is asked for, and to delete it when the pointer is released. The _CATIPrintable_ method is also declared as public. A copy constructor and an assignment operator are declared as private. They are not implemented in the source file. This prevents the compiler to create them by default as public and to accommodate room for them in the virtual function table, because pointers to extension classes must never be handled by clients directly.

The _CAAECmpPrintable_ source file is as follows:

    #include "CAACmp.h"
    #include "CAACmpImage.h"
    #include "CAAECmpPrintable.h"

```cpp
    CATImplementClass(CAAECmpPrintable,  // Extension class name
                      CodeExtension,     // Code extension
                      CATBaseUnknown,    // Always OM-derive extensions from CATBaseUnknown
                      CAACmp);           // Main class of the extended component
```

    #include "TIE_CATIPrintable.h"       // Declares that CAAECmpPrintable implements
```cpp
CATImplementClass(CAAECmpPrintable,  // Extension class name
CodeExtension,     // Code extension
CATBaseUnknown,    // Always OM-derive extensions from CATBaseUnknown
CAACmp);           // Main class of the extended component
    TIE_CATIPrintable(CAAECmpPrintable); // CATIPrintable

    CAAECmpPrintable::CAAECmpPrintable(#) {}
    CAAECmpPrintable::~CAAECmpPrintable(#) {}

    CATPrintImage * CAAECmpPrintable::**CreatePrintableImage**(void)
```

    {
CAAECmpPrintable::CAAECmpPrintable(#) {}
CAAECmpPrintable::~CAAECmpPrintable(#) {}
CATPrintImage * CAAECmpPrintable::**CreatePrintableImage**(void)
      return new CAACmpImage( (CAACmp*) **GetImpl**(#) );

    }

---

The `CATImplementClass` macro [1] is used as usual to declare the extension class name, the extension type, the OM-derived component that must always be _CATBaseUnknown_ for extensions, and the extended component. `CreatePrintableImage` simply returns a pointer to the instance of the component printable image class it has just created.

[Top]
### Creating the Printable Image Class

The _CAACmpImage_ printable image class should include a constructor, a destructor, and the two methods `GetSize` and `Decode`. Below is the _CAACmpImage_ header file:

    ...
    #include "CATPrintImage.h"
    ...
    class CAACmpImage : public CATPrintImage
    {
class CAACmpImage : public CATPrintImage
      public :
        CAACmpImage(CAACmp *pCAACmpInstanceToPrint);
        virtual ~CAACmpImage(#);
        int **GetSize**(float &oWidth, float &oHeight);
        int **Decode**(CATPrintGenerator *pGenerator,
                   const CATPrintParameters &Parameters);
      private :
        CAACmp * _pCAACmpInstanceToPrint;

    };

---

Note that:

  * The constructor takes a pointer to an instance of _CAACmp_ as parameter, stored as a the private data member `_pCAACmpInstanceToPrint`
  * The `GetSize` method returns the width and the height of the image
  * The `Decode` method is called by the `Print` method of the _CATPrinterDevice_ or of the _CATPrintImage_ class. Its parameters are the requested generator or driver, and the print parameters. Its job is to actually draw the image by using the generator drawing methods, according to the print parameters.

The constructor and the destructor of this class should be as follows:

    CAACmpImage::CAACmpImage(CAACmp *pCAACmpInstanceToPrint)

    {
The constructor and the destructor of this class should be as follows:
CAACmpImage::CAACmpImage(CAACmp *pCAACmpInstanceToPrint)
      _pCAACmpInstanceToPrint = pCAACmpInstanceToPrint;
      _pCAACmpInstanceToPrint->**AddRef**(#);

    }

_pCAACmpInstanceToPrint = pCAACmpInstanceToPrint;
_pCAACmpInstanceToPrint->**AddRef**(#);
    CAACmpImage::~CAACmpImage(#)

    {
_pCAACmpInstanceToPrint->**AddRef**(#);
CAACmpImage::~CAACmpImage(#)
```vbscript
      if (NULL != _pCAACmpInstanceToPrint)

```

      {
CAACmpImage::~CAACmpImage(#)
if (NULL != _pCAACmpInstanceToPrint)
        _pCAACmpInstanceToPrint->**Release**(#);
        _pCAACmpInstanceToPrint = NULL;

      }
    }

---

The pointer to the component to print is stored as a data member and thus must be Addref'd to prevent the component destruction while in use by the printing task. It must be released when the printing task completes.

The `GetSize` and `Decode` methods are component dependent. Refer to the example provided [2].

[Top]

* * *
### In Short

Any CAA V5 component for which it makes sense, that is, usually those that can be displayed, can be made printable. This is possible thanks to the _CATIPrintable_ interface that the component should implement, possibly by means of a code extension, which role is to return a printable image class associated with the component that has the know-how of decoding the component contents and of printing it. The methods of this class are directly called by the print process.

Top

* * *
### References

[1] | [Creating Components](../CAASysTechArticles/CAASysCreatingComponent.md)
---|---
[2] | [Making Your Components Printable](../CAAPrtUseCases/CAAPrtSamplePrintableObjects.md)
[Top]

* * *
### History

Version: **1** [Mar 2000] | Document created
---|---
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
