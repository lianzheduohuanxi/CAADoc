---
title: "The Management of Foreign Data"
category: "use-case"
module: "CAACgmModel"
tags: "["CATICGMObject", "CATICGMDomainBinder", "CATICGMObjects", "CATIA", "CATIForeignSurface"]"
source_file: "Doc/online/CAACgmModel/CAACgmTaGobAttribute.htm"
converted: "2026-05-11T17:33:47.890093"
---
# The Management of Foreign Data

---
Technical Article
## Abstract

The geometric attributes are a quick way to add data on CGM objects. Moreover, they are used to introduce foreign surfaces into CGM, that this paper precisely details.

  * CGM Attributes
    * Definition
    * Characterization
    * Management
    * Stream and Unstream
    * Non Persistent Attribute: Sample
  * The Introduction of a Foreign Surface Class
    * Base Principle
    * CATForeignGeometryData
    * CATForeignSurfaceData
    * CATMathFunctionXY
    * How to Proceed
  * In Short
  * References

---
## CGM Attributes
### Definition

A CGM attribute (CATCGMAttribute class) is an object that can be pointed to by a CGM object (CATICGMObject interface, or its derived interfaces such a CATGeometry, CATSurface, CATCurve for example). It contains data that you want to add to a CGM object, without deriving from the corresponding interface. This is useful:

  * To stamp an object (during a scan process for example).
  * To attach temporary processed data (such as extracted meshing).
  * To store foreign data with specific management methods.
  * In particular, this is used to introduce foreign surface into CGM.

Depending on your need, you can create _temporary_ or _streamable_ attribute classes, by deriving your own class from the CATCGMAttribute class and CATCGMStreamAttribute class respectively:

  * Temporary attributes are only living during the time of your program execution.
  * Streamable attributes can be translated into a sequence of bytes to be saved on a given media, and read from a sequence of bytes that comes from a previous translation.

Fig. 1: The Objects Involved in the Attribute Mechanisms ![Foreign](images/CAACgmGobForeign0.gif) | An attribute is a CATCGMAttribute object that is referenced by a CATICGMObject. It can be temporary or streamable You create your own attribute class by derivation. All derived object from the CATICGMObject interface obviously owns the attributes management mechanism.
---|---
### Characterization

An attribute is characterized by a class name, an application name and a version number. The application name is a logical name for the physical load module that contains the attribute class. The mapping between the logical and physical names is realized through the _static query implementation_ as precisely described in the Object Modeler documentation. What you need to know here is that you have to create a header that contains the physical name, a source that declares the mapping and a line into a dictionary. The header is as follows:

    //-----------------------------------------------------------------------------
    //         header XXX.h for the physical load name (XXX)
    //-----------------------------------------------------------------------------
    #ifdef  _WINDOWS_SOURCE
    #ifdef  __XXX
    #define ExportedByXXX   __declspec(dllexport)
    #else
    #define ExportedByXXX   __declspec(dllimport)
    #endif
    #else
    #define ExportedByXXX
    #endif

The source is:

    //-----------------------------------------------------------------------------
    //         source MyApplicationName.cpp for the mapping
    //  logical load name (MyApplicationName) - physical load name (XXX)
    //  through the dictionary
    //-----------------------------------------------------------------------------
    #include "AppDef.h"
    **AppDef(MyApplicationName)** ;

The dictionary `MyApplicationName.dico` contains the following line:

    MyApplicationName        CATICGMDomainBinder        libXXX

Now, you have to declare the mapping in your attribute class by the mean of the macro `CATCGMDeclareAttribute`, as showed in the header example ` MyAttributeClass.h` below, and the macro `CATCGMImplAttribute`, as in the code example for a persistent (or streamable) `MyAttributeClass.cpp`:

    #ifndef MyAttributeClass_H
    #define MyAttributeClass_H
Now, you have to declare the mapping in your attribute class by the mean of the macro `CATCGMDeclareAttribute`, as showed in the header example ` MyAttributeClass.h` below, and the macro `CATCGMImplAttribute`, as in the code example for a persistent (or streamable) `MyAttributeClass.cpp`:
    class CATCGMAttributeDef;
    class CATCGMStream;
    class CATICGMObject;
    class CATCGMContainer;

    #include "CATCGMStreamAttribute.h"
    #include "XXX.h"

    //-----------------------------------------------------------------------------
    // case of a streamable attribute
    class ExportedByXXX MyAttributeClass : public CATCGMStreamAttribute
    {
      **CATCGMDeclareAttribute**(MyAttributeClass, CATCGMStreamAttribute);
class ExportedByXXX MyAttributeClass : public CATCGMStreamAttribute
      public :
      virtual void Stream(CATCGMStream & ioStream);
      virtual void UnStream(CATCGMStream & iStream);

    // own methods..
public :
virtual void Stream(CATCGMStream & ioStream);
virtual void UnStream(CATCGMStream & iStream);
      void SetValue(long iVal);
      void GetValue (long & oVal);
      protected :

    // useful- returns 1 if TRUE 0 otherwise
void SetValue(long iVal);
void GetValue (long & oVal);
protected :
        virtual long Compare(const CATCGMAttribute &iOtherAttribute);

    };
    // useful
protected :
virtual long Compare(const CATCGMAttribute &iOtherAttribute);
    ExportedByXXX void CastTo(CATCGMAttribute * iMyAttribute, MyAttributeClass * & oMyAttribute);

    #endif

The corresponding source `MyAttributeClass.cpp` is:

    #include "CATCGMAttrId.h"
    #include "MyAttributeClass.h"
    #include "CATBaseUnknown.h"
    #include "CATCGMStream.h"

    void CastTo(CATCGMAttribute * curattr, MyAttributeClass * & retour)
    {
void CastTo(CATCGMAttribute * curattr, MyAttributeClass * & retour)
      retour =NULL;
      if (curattr ->IsATypeOf(UAIDPtr(MyAttributeClass)))
```vbscript
```vbscript
        retour = (MyAttributeClass *) curattr;

```

```

    }
    // declaration of the class, the application and the version.
    **CATCGMImplAttribute**(MyAttributeClass,CATCGMStreamAttribute,MyApplication,1);

    void MyAttributeClass::Stream(CATCGMStream & Str)
    {Str.WriteLong(streamedvalue);}

    void MyAttributeClass::UnStream(CATCGMStream & Str)
    {Str.ReadLong(streamedvalue);}

    void MyAttributeClass::SetValue(long val)
    { streamedvalue=val;}

    void MyAttributeClass::GetValue (long & val)
    { val = streamedvalue;}

void MyAttributeClass::GetValue (long & val)
    long MyAttributeClass::Compare(const CATCGMAttribute & NewAttr)

    {
void MyAttributeClass::GetValue (long & val)
long MyAttributeClass::Compare(const CATCGMAttribute & NewAttr)
      long idef = 0;
      MyAttributeClass * newattr;
      CastTo((MyAttributeClass *)&NewAttr, newattr);
```vbscript
      if (streamedvalue== newattr->streamedvalue)
```

        idef=1;
      return idef;

    }
### Management

idef=1;
return idef;
Once defined, an attribute can be used by a CATICGMObject. Hence, the `CATICGMObject::PutAttribute` method allows a CATICGMObject to point to an attribute.

Now, the attributes can be read (`CATICGMObject::GetAttribute`) or released (`CATICGMObject::ReleasedAttribute`). If a CATICGMObject releases an attribute that is no more used, the attribute is deleted.

A CATICGMObject may point several attributes of different classes; conversely, an attribute may be pointed by several CATICGMObjects of the same container (a container is a set that contains objects). If a CATICGMObject is deleted, the attribute(s) that it points is(are) also deleted if this(these) attribute(s) is(are) no more pointed by any other CATICGMObjects.

### Stream and Unstream

Now, the attributes can be read (`CATICGMObject::GetAttribute`) or released (`CATICGMObject::ReleasedAttribute`). If a CATICGMObject releases an attribute that is no more used, the attribute is deleted.
A CATICGMObject may point several attributes of different classes; conversely, an attribute may be pointed by several CATICGMObjects of the same container (a container is a set that contains objects). If a CATICGMObject is deleted, the attribute(s) that it points is(are) also deleted if this(these) attribute(s) is(are) no more pointed by any other CATICGMObjects.
The stream and unstream mechanisms allow you to translate a (persistent) object into a sequence of bytes and vice et versa. To unstream a file (at the File/Read operation for example), the unstream process uses the mapping between the application name and the load module name to load the right physical load module. If the load module is not found during the unstream process, the attribute is copied and referenced by the the CATICGMObject, but not seen, so that the model can be read and the data are not lost, but not usable too.

To write the stream and unstream methods for your own attribute, take into account that:

  * For that purpose, the CATMathStream class offers you methods to stream and unstream data according to their type ("long", "double", "string", "char" for example).
  * These methods take into account the NT/Unix platform type, so you do not have to care with this point, except if you decide to stream your data as a whole buffer. For that reason also, do not use the stream method of a "long" to stream two"int".
  * You must write and read the data in the same order. If you have arrays of variable length, write the length of the array before the values.
  * The upward and downward compatibility may be managed by using the method that gives you the object data length to unstream, especially if you only add (or suppress) data . If not sufficient, you may use a version number to insure the compatibility of your different versions of attributes.
  * Do not let point your streamable attribute to other objects.

### Non Persistent Attribute: Sample

First described the application name through the dictionary and the corresponding header file.

The header of a new attribute class can be as as follows:

    #ifndef UserNonPersistentAttr_H_
    #define UserNonPersistentAttr_H_
    #include "XXX.h"
    #include "CATCGMAttribute.h"

    class ExportedByXXX UserNonPersistentAttr : public CATCGMAttribute
    {
class ExportedByXXX UserNonPersistentAttr : public CATCGMAttribute
    public :
    CATCGMDeclareAttribute(UserNonPersistentAttr,CATCGMAttribute);
```vbscript
    UserNonPersistentAttr(#);
    UserNonPersistentAttr(const UserNonPersistentAttr&);
```

    UserNonPersistentAttr& operator=(const UserNonPersistentAttr&);
    virtual ~UserNonPersistentAttr(#);

    };
    #endif

The source file is then:

    #include "UserNonPersistentAttr.h"
The source file is then:
    CATCGMImplAttribute(UserNonPersistentAttr,CATCGMAttribute,NoAppDef,1);

    //
The source file is then:
CATCGMImplAttribute(UserNonPersistentAttr,CATCGMAttribute,NoAppDef,1);
    UserNonPersistentAttr::UserNonPersistentAttr(#) :
    CATCGMAttribute(#)

    {
    }
    //
UserNonPersistentAttr::UserNonPersistentAttr(#) :
CATCGMAttribute(#)
    UserNonPersistentAttr::UserNonPersistentAttr(const UserNonPersistentAttr&)

    {
    }
    //
UserNonPersistentAttr::UserNonPersistentAttr(const UserNonPersistentAttr&)
    UserNonPersistentAttr& UserNonPersistentAttr::operator=(const UserNonPersistentAttr&)

    {
    return *this;
    }
    //
UserNonPersistentAttr& UserNonPersistentAttr::operator=(const UserNonPersistentAttr&)
return *this;
    UserNonPersistentAttr::~UserNonPersistentAttr(#)

    {
    }

To use it:

    //Creates a UserNonPersistentAttr
    UserNonPersistentAttr * pMyAttr=new UserNonPersistentAttr(#);
    //
    // Puts it on a line
    piLine->PutAttribute(pMyAttr);
    //
    // Gets it from the line
piLine->PutAttribute(pMyAttr);
    UserNonPersistentAttr * pRetrievedAttr=
        (UserNonPersistentAttr*) piLine->GetAttribute(UAIDPtr(UserNonPersistentAttr))

    //
    //Releases it from the line if no more needed
UserNonPersistentAttr * pRetrievedAttr=
(UserNonPersistentAttr*) piLine->GetAttribute(UAIDPtr(UserNonPersistentAttr))
    piLine->ReleaseAttribute(pRetrievedAttr);

## The Introduction of a Foreign Surface Class

piLine->ReleaseAttribute(pRetrievedAttr);
CATIA Geometric Modeler offers a large variety of surfaces (CATSurface interface) from elementary surfaces to Nurbs surfaces, and from sampled surfaces to procedural surfaces. All the capabilities of these surfaces are described in the [2] paper.

You may need to introduce your own surface classes, either you want to have a special interface for existing CATSurfaces (for example, you want to have a class for Bezier surface, that is a specific case of CATNurbsSurface), or you have developed own methods that are optimized for a given type of surfaces.

This section describes the way to introduce foreign surfaces in CGM. Once introduced, they can be handled as any CATSurface: thus, they can be used, for example, by the geometric operators or as the geometric support of topological faces as any CATSurface. All CATSurface must be C2 continuous (at least twice differentiable). So does your own surfaces.

### Base Principle

You may need to introduce your own surface classes, either you want to have a special interface for existing CATSurfaces (for example, you want to have a class for Bezier surface, that is a specific case of CATNurbsSurface), or you have developed own methods that are optimized for a given type of surfaces.
This section describes the way to introduce foreign surfaces in CGM. Once introduced, they can be handled as any CATSurface: thus, they can be used, for example, by the geometric operators or as the geometric support of topological faces as any CATSurface. All CATSurface must be C2 continuous (at least twice differentiable). So does your own surfaces.
The base principle is to involve an attribute class called CATForeignSurfaceData and the interface CATIForeignSurface in a bi-directional relashionship: the CATIForeignSurface is a void shell, that is filled by the CATForeignSurfaceData, as attribute of CATIForeignSurface.

  * CATIForeignSurface retrieves the CATForeignSurfaceData attribute through a `GetAttribute` method, called here `GetData`.
  * CATForeignSurfaceData can ask for its reference by the `GetReference` method.

The base principle is to involve an attribute class called CATForeignSurfaceData and the interface CATIForeignSurface in a bi-directional relashionship: the CATIForeignSurface is a void shell, that is filled by the CATForeignSurfaceData, as attribute of CATIForeignSurface.
You only have to derive your own attribute class from CATForeignSurfaceData, and overload the pure virtual (at least) methods.

Fig. 2: The Mechanism of Introduction of a Foreign Surface ![Foreign](images/CAACgmGobForeign2.gif) | CGM offers two objects that are bi-directionally linked. CATIForeignSurface and CATForeignSurfaceData. To introduce your own surface object, you have to derive CATForeignSurfaceData, and overload the methods to fit the properties of your object. Then, a CATIForeignSurface object that have a MySurfaceData object as data is handled as any CATSurface by CGM, and with the behavior you have given it.

You only have to derive your own attribute class from CATForeignSurfaceData, and overload the pure virtual (at least) methods.
Fig. 2: The Mechanism of Introduction of a Foreign Surface ![Foreign](images/CAACgmGobForeign2.gif) | CGM offers two objects that are bi-directionally linked. CATIForeignSurface and CATForeignSurfaceData. To introduce your own surface object, you have to derive CATForeignSurfaceData, and overload the methods to fit the properties of your object. Then, a CATIForeignSurface object that have a MySurfaceData object as data is handled as any CATSurface by CGM, and with the behavior you have given it.
CATForeignSurfaceData is a CATCGMStreamAttribute. Hence, it globally owns the same properties as its father, except that:

  * A CATForeignSurfaceData cannot be pointed by several CATIForeignSurface, and a CATIForeignSurface cannot point several CATForeignSurfaceData (although it can points other CATCGMAttribute that are not CATForeignSurfaceData).
  * If the load module containing the attribute class is not found, the file is not readable.

Once described the general mechanism, we detail now the methods of CATForeignGeometryData and CATForeignSurfaceData, that must or may be written for taking into account the properties of your own surface.
### CATForeignGeometryData

This class handles the common behavior of all the foreign geometric objects. It is the counterpart of the CATGeometry interface. We find here

  * Pure virtual methods, that you must overload for your own object:
    * `Stream` and `Unstream` (as previously explained).
    * `Clone` duplicates your object.
    * `Move3D` transforms your object according to a given mathematical transformation (rotation, symmetry, etc.).
  * Virtual methods, that have a default behavior. You may overload them to increase the performances or to better fit the behavior of your own class:
    * `CloneAndMove3D` duplicates, then transforms your object.
    * `GetSize` gives an approximated evaluation of the size of your object, while `Dump` writes information about the object.
    * `CheckUp` performs some checks on your objects.

If you compare the methods that are requested for your object with the CATGeometry and CATICGMObject methods, you can notice that nothing maps the `GetLinks` method. Indeed, if your object refers to an other one, that is foreign or CGM, this forward linked object would not be taken into account in any CGM processes up to now.
### CATForeignSurfaceData

This class handles the behavior of the foreign surfaces. It is the counterpart of the CATSurface interface. Let us first remind some important CATSurface properties:

  * As a surface is a bi-parameterized geometric element, it may be represented by three functions of two variables, called **CATMathFunctionXY** (`(FX(u,v), FY(u,v), FZ(u,v))`). `(u,v)` are the parameters of a point on the surface and are managed by the `CATSurParam` class. Each type of surface is responsible for the mapping (called _evaluation_) between the `(u,v)` parameters and their corresponding coordinates in the 3D space. Hence the evaluation of a point of a surface amounts to the evaluation of the CATMathFunctionXY.
    * If you do not find the type of function you want in CGM (CATMathFunctionXY or one of its derivated classes), you must derive your own function class.
  * Surfaces can have several _patch_ es in each direction: a patch is a part of the surface where it is many infinitely deferentiable. At the frontier of the patch the function is only C2 continuous, and the continuity properties are modeled by a nodal vector (the CATKnotVector class). The patches are located with a patch number `iPatchU` in the first direction and a patch number `iPatchV` in the second direction. Hence, you can use a local parameter on a given patch, or a global parameter, that takes in account the whole surface. The patch numbers are not necessarily positive, but their values are consecutive. Notice that the nodal vectors must not be periodic.
  * A surface has a current limitation, and a maximum limitation, outside which it is not defined or cannot be extrapolated and then cannot be evaluated. A surface limitation is defined by two `CATSurParam` objects and managed by a `CATSurLimits` class. The current limitation defines the area of the surface that is useful, visualized and used by default by the geometric operators.

Hence, the main methods of the CATForeignSurfaceData are:

  * pure virtual methods you must overload for your own object
    * `GetLimits, GetInternalMaxLimits` and `GetMaxLimits` return the current and maximum limitation respectively, `SetLimits` defines a current limitation.
    * `Extrapolate` must extend the MaxLimits of this surface.
    * `GetKnotVector` retrieves the nodal representation if your surface has several patches.
    * `IsConfused` tests is the transformation of your surface is globally coincident with another surface.
    * `IsPeriodicU`, `IsPeriodicV` test whether the surface is periodic along U and V.
  * Virtual methods, that have a default behavior. You may overload them to increase the performances or to better fit the behavior of your own class:
    * `GetBox` , `GetBoundingBox`, `GetInternalMaxLimits`, `GetInternalMaxBoundingBox` deal with limitations of a part of a surface, and are defined by default, as soon as the evaluators on the corresponding CATMathFunctionXY are available. So do the different `Eval` methods.
    * `CreateParam` returns a CATSurParam on the surface.
    * `IsInvariant` tests is your surface is geometrically invariant by a mathematical transformation.
    * `HasImplicitEquation`, `GetImplicitEquation`, `GetParam`, `GetParamOnIsopar` deal with surfaces that have an implicit equation. In this case, it allows to have directly the mapping from the `(x,y,z)` cartesian coordinates of a point to the `(u,v)` parameters.
    * `HasMathCurve`, `GetMathCurve` returns the mathematical representation of an iso-parametric curve of a surface if this mathematical representation exists.
    * `CreateOffset` returns the result of the offset of a surface. By default, it creates the procedural CATOffsetSurface.
### CATMathFunctionXY

This class manages the evaluators that are used by the surface evaluators. There are already CATMathLinearXY, CATMathFunctionXY, CATMathPolynomXY are kind of CATMathFunctionXY that are already provided in CGM.

```cpp
If needed however, you may derive your own class of function to fit your object behavior, and overload at least the evaluator `Eval` of the value of the function.

```

The evaluation of the first and second derivatives may be approximated by default. So do the interval evaluators. It is however strongly recommended to overload the first derivatives evaluation, the best being to also write the second derivatives evaluation. If you overload the interval evaluators you will increase the CPU performances.

### How to Proceed

```cpp
If needed however, you may derive your own class of function to fit your object behavior, and overload at least the evaluator `Eval` of the value of the function.
The evaluation of the first and second derivatives may be approximated by default. So do the interval evaluators. It is however strongly recommended to overload the first derivatives evaluation, the best being to also write the second derivatives evaluation. If you overload the interval evaluators you will increase the CPU performances.
This section summarizes the steps for the integration of your own surface class.

```

    * Analyze the need of a new type of CATMathFunctionXY. If needed:
      * Create your own class `MyFunctionXY` of function of two variables, by derivation of CATMathFunctionXY.
      * Write the evaluators of this new function.
      * Optionally, write the evaluation of the first and second derivatives, and the interval evaluators.
      * Write the `Stream` and `UnStream` methods for this object.
    * Create your class `MySurfaceData` by derivation of the CATForeignSurfaceData class:
      * Write the mandatory methods (do not forget the methods of the CATCGMStreamAttribute as `Stream` and `UnStream` or the methods of CATForeignGeometryData as `Clone` and `Move`, and the default constructor).
      * Optionally, write the other CATForeignSurfaceData methods.
      * Possibly write specific methods for this class.
    * You are ready to use your own surface class and to test it:
      * Create a `MySurfaceData` object.
      * Create a `CATIForeignSurface` object with the `CATGeoFactory::CreateForeignSurface` method, by giving a pointer to the `MySurfaceData` object.
      * And use the created `CATIForeignSurface` as any surface in CGM.
## In Short

    * The geometric attributes allow you to put additional data on all object deriving from the CATICGMObject interface.
    * Foreign surfaces are added into CGM by the derivation of the CATForeignSurfaceData (and possibly a CATMathFunctionXY). This CATForeignSurfaceData is the attribute filling the void CATIForeignSurface, that may be then handled as any CATSurface.
    * The following table summarizes the properties of the different attributes:  Attribute | Pointed by | Streamable
---|---|---
CATCGMAttribute | one or more CATICGMObject | no
CATCGMStreamAttribute | one or more CATICGMObject of the same container | yes
A file is readable, even if the attribute class load module is not found
CATForeignSurfaceData | only one CATIForeignSurface, that points only one CATForeignSurfaceData | yes
A file is not readable if the attribute class load module is not found

## References

[1] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)
---|---
[2] | [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)
## History

Version: **1** [Mar 2000] | Document created
---|---
