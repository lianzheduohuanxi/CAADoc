---
```vbscript
title: "Making Your Components Printable"
category: "use case"
module: "CAAPrtUseCases"
tags: ["CAAPrtPrintableString", "CAAPrtStringImage", "CAAPrint", "CAAPrtPrintableObjects", "CATIPrintable"]
source_file: "Doc/online/CAAPrtUseCases/CAAPrtSamplePrintableObjects.htm"
converted: "2026-05-11T17:17:56.133823"
```

---
# 3D PLM Enterprise Architecture

| 
## 3D Visualization - Print

| 
### Making Your Components Printable

_Enabling your components for print_  
---|---|---  
Use Case  

* * *
### Abstract

This article shows how to make your objects printable. 

  * **What You Will Learn With This Use Case**
  * **The CAAPrtPrintableObjects Use Case**
    * What Does CAAPrtPrintableObjects Do
    * How to Launch CAAPrtPrintableObjects
    * Where to Find the CAAPrtPrintableObjects Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---  

* * *
### What You Will Learn With This Use Case

This use case is intended to show how to make a component printable by making the component implement the _CATIPrintable_ interface.

[Top]
### The CAAPrtPrintableObjects Use Case

CAAPrtPrintableObjects is a use case of the CAAPrint.edu framework that illustrates the Print framework capabilities.

[Top]
#### What Does CAAPrtPrintableObjects Do

CAAPrtPrintableObjects is a program that creates a simple component using a single class named _CAAPrtPrintableString_ that holds a character string. This component implements the _CATIPrintable_ interface [1] and its single method `CreatePrintableImage` that creates and returns the component printable image. This is an instance of the _CAAPrtStringImage_ class.

[Top]
#### How to Launch CAAPrtPrintableObjects

To launch CAAPrtPrintableObjects, you will need to set up the build time environment, then compile CAAPrtPrintableObjects along with its prerequisites, set up the run time environment, and then execute the use case [2].

[Top]
#### Where to Find the CAAPrtPrintableObjects Code

To launch CAAPrtPrintableObjects, you will need to set up the build time environment, then compile CAAPrtPrintableObjects along with its prerequisites, set up the run time environment, and then execute the use case [2].
The CAAPrtPrintableObjects use case is made of a several classes located in the CAAPrtPrintableObjects.m module of the CAAPrint.edu framework:

Windows | `InstallRootDirectory\CAAPrint.edu\CAAPrtPrintableObjects.m\`  

The CAAPrtPrintableObjects use case is made of a several classes located in the CAAPrtPrintableObjects.m module of the CAAPrint.edu framework:
Windows | `InstallRootDirectory\CAAPrint.edu\CAAPrtPrintableObjects.m\`
Unix | `InstallRootDirectory/CAAPrint.edu/CAAPrtPrintableObjects.m/`  

where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed.

[Top]
### Step-by-Step

To make a component printable, there are four main steps:
# | Step | Where  
---|---|---  
To make a component printable, there are four main steps:
1 | Makes the component implement _CATIPrintable_ | CAAPrtPrintableString class  
2 | Creates the printable image class | CAAPrtStringImage class  
3 | Writes the `GetSize` method | CAAPrtStringImage class  
4 | Writes the `Decode` method | CAAPrtStringImage class  

The CAAPrtPrintableString component is created using a single class whose name is the component name.

[Top]
#### Makes the Component Implement CATIPrintable

The _CAAPrtPrintableString_ class header file is as follows.

    #include "CATBaseUnknown.h"     _// To derive from CATBaseUnknown_
    #include "CATUnicodeString.h"   _// The string to represent_

The _CAAPrtPrintableString_ class header file is as follows.
    class CATPrintImage;  _// To return the image_

    class  CAAPrtPrintableString : public CATBaseUnknown

    {
class CATPrintImage;  _// To return the image_
class  CAAPrtPrintableString : public CATBaseUnknown
     public:

      **CATDeclareClass** ;   _// Declares that this class belongs to a component_

class  CAAPrtPrintableString : public CATBaseUnknown
public:
      CAAPrtPrintableString (const CATUnicodeString & iString);
      virtual ~CAAPrtPrintableString ();

      _// CATIPrintable interface method_
      CATPrintImage * **CreatePrintableImage**(void); _// Returns the image representing the strin_ g

     private:
      CATUnicodeString _string;  _// The string to print held by the component_

    };  

---  

CATUnicodeString _string;  _// The string to print held by the component_
The `CATDeclareClass` macro declares that this class is part of a component. The class has a constructor that takes the character string as input parameter, a destructor, the `CreatePrintableImage` method of the _CATIPrintable_ interface, and the character string.

Its source file is a follows.

    #include "CAAPrtPrintableString.h"   _// Header of the current class_
    #include "CAAPrtStringImage.h"       _// The class of the image to print_

    _// Print framework_
    #include "TIE_CATIPrintable.h"

    _// Declares that this class implements the CATIPrintable interface_
    **TIE_CATIPrintable(CAAPrtPrintableString);**

    _// Declares that this class is an implementation_
    **CATImplementClass**(**CAAPrtPrintableString** ,**Implementation** , CATBaseUnknown, CATnull);

    CAAPrtPrintableString::CAAPrtPrintableString(const CATUnicodeString & iString)
                         : _string(iString)
    {}

    CAAPrtPrintableString::~CAAPrtPrintableString()
    {}

CAAPrtPrintableString::~CAAPrtPrintableString()
    _// CATIPrintable implementation

    // Returns the image representing the printable object_
CAAPrtPrintableString::~CAAPrtPrintableString()
_// CATIPrintable implementation
    CATPrintImage * CAAPrtPrintableString::CreatePrintableImage(void)

    {
_// CATIPrintable implementation
CATPrintImage * CAAPrtPrintableString::CreatePrintableImage(void)
      return new CAAPrtStringImage(_string);

    }  

---  

return new CAAPrtStringImage(_string);
The `TIE_CATIPrintable` macro creates a TIE object that decouples the interface and its implementation. Clients that hold a pointer to the _CATIPrintable_ interface have in fact a pointer to the TIE object, and not to the _CAAPrtPrintableString_ instance.

The `CATImplementClass` macro declares that the _CAAPrtPrintableString_ class is an implementation, that is, the component main class, other possible classes making up the component being extensions, and that the component OM-derives from _CATBaseUnknown_.

The implementation of the `CreatePrintableImage` method of _CATIPrintable_ simply returns an instance of the _CAAPrtStringImage_ class.

The framework's interface dictionary should include the following line.

    CATPrtPrintableString   CATIPrintable  libCAAPrtPrintableObjects  

---  

This declares that the _CATPrtPrintable_ component implements the _CATIPrintable_ interface, and that the implementation code is located in the shared library or DLL named libCAAPrtPrintableObjects. If the TIE and the method code are located in two different shared libraries or DLL, the one that must be inserted in the interface dictionary is the one that contains the TIE code.

[Top]
#### Creating the Printable Image Class

The printable image class header file is as follows.

    ...
The printable image class header file is as follows.
    class CATPrintGenerator;  _// To use a generator to draw the image_
    class CATPrintParameters; _// To use print parameters_

    class CAAPrtStringImage : public CATPrintImage

    {
class CATPrintGenerator;  _// To use a generator to draw the image_
class CATPrintParameters; _// To use print parameters_
class CAAPrtStringImage : public CATPrintImage
      public:
        CAAPrtStringImage(const CATUnicodeString &iString);
        virtual ~CAAPrtStringImage();

        _// Retrieves the image size_
        int GetSize(float& iWidth, float& iHeight);

        // _Draws the image using a given generator and specified print parameters_
virtual ~CAAPrtStringImage();
_// Retrieves the image size_
int GetSize(float& iWidth, float& iHeight);
        int Decode(CATPrintGenerator* iGenerator, const CATPrintParameters& iParameters);

      private:
        CATUnicodeString _string;   _// The string to draw_  

    };  

---  

CATUnicodeString _string;   _// The string to draw_
This class holds the character string, and has two methods 

  1. `GetSize` to determine and return the printed component size
  2. `Decode` that draws the component image to print using a set of print parameters.

[Top]
#### Writing the GetSize Method

    ...
    int CAAPrtStringImage::**GetSize**(float& oWidth, float& oHeight)
    {
int CAAPrtStringImage::**GetSize**(float& oWidth, float& oHeight)
      _// The size depends on the string length_
      int lg = _string.GetLengthInChar();
      oHeight = 50.f;
      oWidth  = (lg+4)*10.;
      return 1;

    }
    ...  

---  

`GetSize` determines the character string length expressed in number of characters, and computes from this length a height and a width of the character string to print.

[Top]
#### Writing the Decode Method

    ...
    int CAAPrtStringImage::**Decode**(CATPrintGenerator* iGenerator, const CATPrintParameters& iParameters)
    {
int CAAPrtStringImage::**Decode**(CATPrintGenerator* iGenerator, const CATPrintParameters& iParameters)
      iGenerator->**Begin**(iParameters);    _// Initializes generation_

      ...
int CAAPrtStringImage::**Decode**(CATPrintGenerator* iGenerator, const CATPrintParameters& iParameters)
iGenerator->**Begin**(iParameters);    _// Initializes generation_
      iGenerator->**End**();                 _// Ends generation_
      return 1;        _// Returns 1 to indicate successful execution_

    }
    ...  

---  

The `Decode` method encloses its code between the call to the generator `Begin` method with the print parameters, and the call to the generator `End` method, just before returning. Now have a look at what can be put between these two method calls.

      ...
The `Decode` method encloses its code between the call to the generator `Begin` method with the print parameters, and the call to the generator `End` method, just before returning. Now have a look at what can be put between these two method calls.
      iGenerator->**SetDrawWidth**(0.0f);    _// Sets line width_

      int Black=0;                        _// Defines the black color_
      iGenerator->**DefineColor**(Black, 0.0f, 0.0f, 0.0f);
      int Red =1;                         _// Defines the red color_
      iGenerator->**DefineColor**(Red, 1.f, 0.f, 0.f); 
      iGenerator->**SelectDrawColor**(Black); _// Sets the black color as the drawing color_

      _// Defines the text direction: horizontal, from left to right_
      iGenerator ->**SetTextAttribute**(CATPRINTTEXT_DIRECTION, 0.0);
      _// Sets the Courier font_
      iGenerator ->**SetTextAttribute**(CATPRINTTEXT_TYPEFACE, CATPRINTTEXT_COURIER);
      _// Requests bold caracters_
      iGenerator ->**SetTextAttribute**(CATPRINTTEXT_WEIGHT,   CATPRINTTEXT_BOLD);
      _// Defines the character height_
      iGenerator ->**SetTextAttribute**(CATPRINTTEXT_HEIGHT, 16.72);

      ...  

---  

Some initializations are first performed, such as the drawing line width, the black and red colors, the black color being set as the color to use, and some attributes of the text to print.

      ...
Some initializations are first performed, such as the drawing line width, the black and red colors, the black color being set as the color to use, and some attributes of the text to print.
      int lg = _string.GetLengthInChar();

      float y = 10.;
      float x = 10.;
      float x0 = x;
      float y1 = 4*y;
      float y0 = y;
      float x1 = (lg+3)*x;

      _// Draws the string_
      iGenerator ->**DrawGeometricText**(x0+x, y0+y, _string);

      iGenerator->**SelectDrawColor**(Red); _// Sets the red color as the drawing color_
      iGenerator->**MoveTo**(x0, y0); _// Moves to the bottom left corner of the frame_

      for (int i=1; i<=lg+2; i++)       _// Draws a bottom zigzag line_

      {
iGenerator->**SelectDrawColor**(Red); _// Sets the red color as the drawing color_
iGenerator->**MoveTo**(x0, y0); _// Moves to the bottom left corner of the frame_
for (int i=1; i<=lg+2; i++)       _// Draws a bottom zigzag line_
        iGenerator->**LineTo**(x0+i*x-x/2, y0-y/2);
        iGenerator->**LineTo**(x0+i*x, y0);

      }
      ...  

---  

The text is drawn first in black using the `DrawGeometricText`  method, and it is then surrounded by zigzag lines drawn in red. The red color is selected using the `DrawGeometricText` method.The pen moves to the (x0,y0) point, and then the bottom zigzag line drawing begins. The three others zigzag line drawing are not shown.

[Top]

* * *
### In Short

This use case shows the objects involved and what to do to make a component printable. The component must implement the _CATIPrintable_ interface whose single method `CreatePrintableImage` returns an object that bears two methods: `GetSize` that defines the print size from the component contents, and `Decode` that decodes this component contents and that actually prints it.

[Top]

* * *
### References

[1] | [Making Your Components Printable](../CAAPrtTechArticles/CAAPrtPrintableObjects.md)  
---|---  
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
[Top]  

* * *
### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
