---
```vbscript
title: "Creating Foreign Surfaces"
category: "use case"
module: "CAACgmModel"
tags: ["CAAAmtForeign", "CAAGMModelForeignSurfaceData", "CAADoc", "CAAGobFS", "CAAGobApplicationName", "CAAGMModelCreation", "CAAAdvancedMathematics", "CAAGMModelForeign", "CAAGMModelInterfaces", "CAAAmtForeignFunctionXY", "CAAAmtForeignFct", "CAAAmtForeignFctXY", "CAAAForeignSurfaceSample", "CATICGMDomainBinder", "CATIA", "CATIForeignSurface"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGobForeign.htm"
converted: "2026-05-11T17:33:48.383671"
```

---
# Creating Foreign Surfaces

---
Use Case
## Abstract

The GeometricObjects framework exposes the interfaces for the geometry: points, curves, surfaces, and some related classes (such as knot vector or surface and curve parameters for example). Moreover, it offers the programmer the capability to introduce its own definition of curve and surface. Such "foreign" definition is then taken into account as any CATIA curve and surface. The use cases illustrates the introduction of a new kind of surface. The way to use the geometry (and the foreign geometry in particular) is detailed in the CAAGMModelCreation use case. The same methodology can be used to introduce foreign curves, only differing by the parent class to derive.
    * What You Will Learn With This Use Case
    * The CAAGMModelForeign Use Case
      * What Does CAAGMModelForeign Do
      * How to Launch CAAGMModelForeign
      * Where to Find the CAAGMModelForeign Code
    * Step-by-Step
    * In Short
    * References
---
## What You Will Learn With This Use Case

This use case explains the introduction of a new kind of geometric surface by describing all the steps of its introduction on a concrete case. The mathematical definition of the new surface is given by the CAAAmtForeignFunctionXY class, already presented in the CAAAmtForeign use case [6] of the CAAAdvancedMathematics.edu framework.
## The CAAGMModelForeign Use Case

CAAGMModelForeign is a use case of the CAAGMModelInterfaces.edu framework that illustrates the GMModelInterfaces framework capabilities.
### What Does CAAGMModelForeign Do

CAAGMModelForeign is a use case of the CAAGMModelInterfaces.edu framework that illustrates the GMModelInterfaces framework capabilities.
The use case creates a new type of surface, which mathematical definition uses the CAAAmtForeignFctXY mathematical function class.

The principle of the introduction of a new kind of surface is fully described in [1]. Once defined the mathematical definition ` CAAAmtForeignFctXY`, one must create a persistent attribute to be the data of `CATIForeignSurface`. For that:

    * Defines the class attribute deriving from CATForeignSurfaceData class: CAAGMModelForeignSurfaceData.
    * Defines the correspondence between the physical module name (CAAGMModelForeign) and a logical one (CAAGobFS).
    * Defines the dictionary.
### How to Launch CAAGMModelForeign

As CAAGMModelForeign only provides the definition of the new surface, it cannot be run alone: you must launch CAAGMModelCreation to execute the CAAGMModelForeign code.

To launch CAAGMModelCreation, you will need to set up the build time environment, then compile CAAGMModelForeign.m and CAAGMModelCreation.m along with their prerequisites (such as CAAAmtForeignFct.m), set up the run time environment, and then execute the use case [7]. Do not forget to run the `mkCreateRuntimeView` command to update the runtime dictionary.
### Where to Find the CAAGMModelForeign Code

As CAAGMModelForeign only provides the definition of the new surface, it cannot be run alone: you must launch CAAGMModelCreation to execute the CAAGMModelForeign code.
To launch CAAGMModelCreation, you will need to set up the build time environment, then compile CAAGMModelForeign.m and CAAGMModelCreation.m along with their prerequisites (such as CAAAmtForeignFct.m), set up the run time environment, and then execute the use case [7]. Do not forget to run the `mkCreateRuntimeView` command to update the runtime dictionary.
The CAAGMModelForeign use case contains the definition of the new class located:

    * In the ProtectedInterfaces directory of the CAAGMModelInterfaces.edu framework for the header CAAGMModelForeignSurfaceData.h
    * In the CAAGMModelForeign.m module of the CAAGMModelInterfaces.edu framework for the corresponding source code CAAGMModelForeignSurfaceData.cpp

`InstallRootFolder\CAADoc\`CAAGMModelInterfaces`.edu\CAAGMModelForeign.m\`

where `InstallRootFolder` [7] is the folder where the API CD-ROM is installed.

Moreover, in order to register this new class:

    * The correspondence between the physical module name (CAAGMModelForeign) and a logical one (CAAGobFS) is defined by CAAGobApplicationName.cpp of the CAAGMModelForeign.m module of the CAAGMModelInterfaces.edu framework.
    * The dictionary must be defined in the CNext directory of the CAAGMModelInterfaces.edu framework.
## Step-by-Step

The use case is divided into the following steps:

    * The CAAGMModelForeignSurfaceData.h Header
    * The CAAGMModelForeignSurfaceData.cpp Source Code
    * The CAAGobApplicationName.cpp Code and Dictionary

Following the described scheme, first define the header of the surface attribute.
### The CAAGMModelForeignSurfaceData.h Header

Following the described scheme, first define the header of the surface attribute.
The new attribute class CAAGMModelForeignSurfaceData derived from the CATForeignSurfaceData class, which is a special streamable attribute dedicated to the foreign surface introduction.

Methods are overridden to declare the specific behavior of the new class (only some of them are displayed below).

    class **ExportedByCAAGMModelForeign** CAAGMModelForeignSurfaceData : public **CATForeignSurfaceData**

    {
Methods are overridden to declare the specific behavior of the new class (only some of them are displayed below).
class **ExportedByCAAGMModelForeign** CAAGMModelForeignSurfaceData : public **CATForeignSurfaceData**
```vbscript
      public :

```

    // Mandatory macro for inheriting from CATCGMAttribute.
      **CATCGMDeclareAttribute** (CAAGMModelForeignSurfaceData,CATForeignSurfaceData);

    // Constructs the surface data.
    // S(u,v) = iOrigin + u*iUDirection
    //                  + v*iVDirection
    //                  + iHeight*cos(u)*cos(v)*iUDirection^iVDirection,
    // uMin<=u<=uMax, vMin<=v<=vMax. </pre>
```vbscript
      CAAGMModelForeignSurfaceData(const CATMathPoint  & iOrigin,
                               const CATMathVector & iUDirection,
                               const CATMathVector & iVDirection,
                               const double          iHeight,
                               const double          iUMin,
                               const double          iUMax,
                               const double          iVMin,
                               const double          iVMax       ) ;
```

     //------------------------------------------------------------------------------
     // Mandatory methods for CATCGMAttribute
     //------------------------------------------------------------------------------
    // Default constructor.
      CAAGMModelForeignSurfaceData();

    // Streams the data.
      void   **Stream**(CATCGMStream & iStr) const ;

    // Unstreams the data.
      void **UnStream**(CATCGMStream & iStr) ;

     //------------------------------------------------------------------------------
     // Mandatory methods for CATForeignGeometryData
     //------------------------------------------------------------------------------
    // Clones this CAAAForeignSurfaceSample.
      CATForeignGeometryData* **Clone**(CATCloneManager & iCloning) const ;

    // Moves this CAAAForeignSurfaceSample.
      void **Move3D**(CATTransfoManager & iTransfo) ;

    // ... //

    // Retrieves the mathematical equation associated with a patch.
void **Move3D**(CATTransfoManager & iTransfo) ;
      void CreateLocalEquation(const long iPatchU, const long iPatchV,
                               const CATMathFunctionXY* & oFx,
                               const CATMathFunctionXY* & oFy,
                               const CATMathFunctionXY* & oFz) ;

```vbscript
      private :

```

      // Data
      // S(u,v) = Origin + u*dU + v*dV + Height*cos(u)*cos(v)*dU^dV,
      // uMin<=u<=uMax, vMin<=v<=vMax.
private :
      double _uMin      ;
      double _uMax      ;
      double _vMin      ;
      double _vMax      ;
      double _Origin[3] ;
      double _Height    ;
      double _dU[3]     ;
      double _dV[3]     ;

    };

    * The `ExportedByCAAGMModelForeign` variable is defined in the `CAAGMModelForeign.h` header.
    * The `CATCGMDeclareAttribute` macro is also mandatory to declare the derivation.
    * Private data contains the definition of the surface parameters.
### The CAAGMModelForeignSurfaceData.cpp Source Code

This section emphasizes on some methods of the .cpp:

This section emphasizes on some methods of the .cpp:
    1. Declaring the Derivation between the CAAGMModelForeignSurfaceData Class and the CATForeignSurfaceDATA Base Class
    2. Streaming and Unstreaming
    3. Cloning
    4. Applying a Geometric Transformation
    5. Creating the Corresponding Mathematical Equations
    1. Declaring the Derivation between the CAAGMModelForeignSurfaceData Class and the CATForeignSurfaceData Base Class

Once again, a macro must be declared: `CATCGMImplAttribute`.

           // CAAGobFS is the application name that you will find in the dictionary.
           // This application name is declared in the CAAGobApplicationName.cpp file.
           // 1 must not be changed.
           **CATCGMImplAttribute**(CAAGMModelForeignSurfaceData, CATForeignSurfaceData, CAAGobFS, 1);

    2. Streaming and Unstreaming

Stream and unstream methods are mandatory to allow your data to be saved and read. In this use case, the foreign surface is standalone: it does not point to any other CGM objects. If it were not, use the `CATCGMStreamAttribute::AddLink` method. In this case, the stream and unstream processes will automatically take the links into account, so that you do not worry about them.

           //-----------------------------------------------------------------------------------
2. Streaming and Unstreaming
Stream and unstream methods are mandatory to allow your data to be saved and read. In this use case, the foreign surface is standalone: it does not point to any other CGM objects. If it were not, use the `CATCGMStreamAttribute::AddLink` method. In this case, the stream and unstream processes will automatically take the links into account, so that you do not worry about them.
           void CAAGMModelForeignSurfaceData::**Stream**(CATCGMStream & iStr) const

           //-----------------------------------------------------------------------------------
           {
void CAAGMModelForeignSurfaceData::**Stream**(CATCGMStream & iStr) const
             iStr.WriteDouble( _uMin      ) ;
             iStr.WriteDouble( _uMax      ) ;
             iStr.WriteDouble( _vMin      ) ;
             iStr.WriteDouble( _vMax      ) ;
             iStr.WriteDouble( _Origin, 3 ) ;   // streams the origin (array of 3 doubles)
             iStr.WriteDouble( _Height    ) ;   // streams the other values
             iStr.WriteDouble( _dU    , 3 ) ;   // streams the first vector (array of 3 doubles)
             iStr.WriteDouble( _dV    , 3 ) ;   // streams the second vector (array of 3 doubles)

           }
           //-----------------------------------------------------------------------------------
iStr.WriteDouble( _Height    ) ;   // streams the other values
iStr.WriteDouble( _dU    , 3 ) ;   // streams the first vector (array of 3 doubles)
iStr.WriteDouble( _dV    , 3 ) ;   // streams the second vector (array of 3 doubles)
           void CAAGMModelForeignSurfaceData::**UnStream**(CATCGMStream & iStr)

           //-----------------------------------------------------------------------------------
           {
void CAAGMModelForeignSurfaceData::**UnStream**(CATCGMStream & iStr)
             iStr.ReadDouble( _uMin      ) ;
             iStr.ReadDouble( _uMax      ) ;
             iStr.ReadDouble( _vMin      ) ;
             iStr.ReadDouble( _vMax      ) ;
             iStr.ReadDouble( _Origin, 3 ) ;   // unstreams the origin (array of 3 doubles)
             iStr.ReadDouble( _Height   ) ;    // unstreams the other values
             iStr.ReadDouble( _dU    , 3 ) ;   // unstreams the first vector (array of 3 doubles)
             iStr.ReadDouble( _dV    , 3 ) ;   // unstreams the second vector (array of 3 doubles)

           }

iStr.ReadDouble( _Height   ) ;    // unstreams the other values
iStr.ReadDouble( _dU    , 3 ) ;   // unstreams the first vector (array of 3 doubles)
iStr.ReadDouble( _dV    , 3 ) ;   // unstreams the second vector (array of 3 doubles)
    3. Cloning

The clone process [2] is managed by the `CATCloneManager`, that duplicates the `CATIForeignSurface` instance. It remains to provide the clone of the attribute, as below:

           //---------------------------------------------------------------------------------------
3. Cloning
The clone process [2] is managed by the `CATCloneManager`, that duplicates the `CATIForeignSurface` instance. It remains to provide the clone of the attribute, as below:
           CATForeignGeometryData* CAAGMModelForeignSurfaceData::**Clone**(**CATCloneManager** & iCloning) const

           //---------------------------------------------------------------------------------------
           { // only duplicates the attribute.
             // The duplication of the CATIForeignSurface is made by the clone manager
CATForeignGeometryData* CAAGMModelForeignSurfaceData::**Clone**(**CATCloneManager** & iCloning) const
             return new CAAGMModelForeignSurfaceData(CATMathPoint(_Origin),
                                                 CATMathVector(_dU),
```vbscript
                                                 CATMathVector(_dV),
```

                                                 _Height,
                                                 _uMin,
                                                 _uMax,
                                                 _vMin,
                                                 _vMax) ;

           }

_uMax,
_vMin,
_vMax) ;
    4. Applying a Geometric Transformation

The transformation process [2] is managed by the `CATTransfoManager,` that coaches the `CATIForeignSurface` instance. It remains to provide the transformation of the parameters, as below:

           //------------------------------------------------------------------------------------
4. Applying a Geometric Transformation
The transformation process [2] is managed by the `CATTransfoManager,` that coaches the `CATIForeignSurface` instance. It remains to provide the transformation of the parameters, as below:
           void CAAGMModelForeignSurfaceData::**Move3D**(**CATTransfoManager** & iTransfo)

           //------------------------------------------------------------------------------------
           { // manages the attribute values.
             // The duplication of the CATIForeignSurface is made by the clone manager

void CAAGMModelForeignSurfaceData::**Move3D**(**CATTransfoManager** & iTransfo)
```vbscript
             if ( FALSE == iTransfo.IsIdentity() )    // in case of a non-identity tranformation

```

             {
```vbscript
if ( FALSE == iTransfo.IsIdentity() )    // in case of a non-identity tranformation
                 CATMathTransformation* pMathTransfo = NULL;
                 iTransfo.GetMathTransformation( pMathTransfo ) ;

                 if ( NULL != pMathTransfo )
```

                 {

iTransfo.GetMathTransformation( pMathTransfo ) ;
if ( NULL != pMathTransfo )
                   double determinant = pMathTransfo->GetMatrix().Determinant() ;
```vbscript
                   if (  determinant > 0. )           // only direct tranformations

```

                   {

double determinant = pMathTransfo->GetMatrix().Determinant() ;
if (  determinant > 0. )           // only direct tranformations
                     CATMathVector Vector ;

           // Gets the value before the transformation
           //  --> reads the values of _dU and affects them to Vector
CATMathVector Vector ;
                     Vector.SetCoord(_dU) ;
```vbscript
                     Vector = (*pMathTransfo) * Vector ; // Uses the operator for the math. transf.

```

           // Sets the value after the transformation
           //  --> reads the values of Vector and affects them to _dU
Vector.SetCoord(_dU) ;
Vector = (*pMathTransfo) * Vector ; // Uses the operator for the math. transf.
                     Vector.GetCoord(_dU) ;

                     Vector.SetCoord(_dV) ;              // Gets the value before the transformation
                     Vector = (*pMathTransfo) * Vector ;
                     Vector.GetCoord(_dV) ;              // Sets the value after the transformation

                     CATMathPoint Point ;

                     Point.SetCoord(_Origin) ;           // Gets the value before the transformation
                     Point = (*pMathTransfo) * Point ;
                     Point.GetCoord(_Origin) ;           // Sets the value after the transformation

           // determinant is the scale factor of the transformation
Point.SetCoord(_Origin) ;           // Gets the value before the transformation
Point = (*pMathTransfo) * Point ;
Point.GetCoord(_Origin) ;           // Sets the value after the transformation
                     _Height /= determinant ;            // Sets the height after the transformation

                   }
                 }
              }
           }

    5. Creating the Corresponding Mathematical Equations

The equations of a surface can be accessed thanks to the following ` CATSurface` methods, that must be called in this order:

       * `CATSurface::Lock`: locks the surface modifications during the edition of the equations.
       * `CATSurface::GetEquation`: retrieves the corresponding mathematical equations.
       * `CATSurface::Unlock`: frees the surface.

To perform the `GetEquation` step, the `CATIForeignSurface` needs to recover the mathematical equations of the foreign surface: this is the goal of the `CreateLocalEquation` method. The `CATIForeignSurface` deletes the allocated equations when unlock the surface.

    //--------------------------------------------------------------------------------
To perform the `GetEquation` step, the `CATIForeignSurface` needs to recover the mathematical equations of the foreign surface: this is the goal of the `CreateLocalEquation` method. The `CATIForeignSurface` deletes the allocated equations when unlock the surface.
    void CAAGMModelForeignSurfaceData::**CreateLocalEquation**(
                              const long iPu,  // useless, only one patch
                              const long iPv,  // useless, only one patch
                              const CATMathFunctionXY* & oFx,
                              const CATMathFunctionXY* & oFy,
                              const CATMathFunctionXY* & oFz)

    //---------------------------------------------------------------------------------
    { // Creates the mathematical equations relative to the egg box
      // S(u,v) = Origin + u*dU + v*dV + Height*cos(u)*cos(v)*dU^dV.
const CATMathFunctionXY* & oFy,
const CATMathFunctionXY* & oFz)
      oFx = new CAAAmtForeignFctXY(_dU[0],_dV[0],
                                   _Height*(_dU[1]*_dV[2]-_dU[2]*_dV[1]),
                                   _Origin[0]) ;
      oFy = new CAAAmtForeignFctXY(_dU[1],_dV[1],
                                   _Height*(_dU[2]*_dV[0]-_dU[0]*_dV[2]),
                                   _Origin[1]) ;
      oFz = new CAAAmtForeignFctXY(_dU[2],_dV[2],
                                   _Height*(_dU[0]*_dV[1]-_dU[1]*_dV[0]),
                                   _Origin[2]) ;

    }
### The CAAGobApplicationName.cpp Code and Dictionary

_Height*(_dU[0]*_dV[1]-_dU[1]*_dV[0]),
_Origin[2]) ;
This file defines the logical name (here `CAAGobFS`) of the load module containing the `CAAGMModelForeignSurfaceData` definition, by the mean of the `AppDef` macro.

    // GeometricObjects
    #include "AppDef.h"  // to use in next line

    // CAAGobFS is the unique name identifying the application
    **AppDef**(**CAAGobFS**);

The dictionary keeps track of the correspondence between the logical application name and the physical load module `libCAAGMModelFo`reign.

    **CAAGobFS** 		CATICGMDomainBinder 		**libCAAGMModelForeign**
## In Short

This use case demonstrates a concrete case of introduction of a new type of foreign surfaces.
## References

[1] | [The Management of Foreign Data](CAACgmTaGobAttribute.md)
---|---
[2] | [The Clone and Transformation Managers](CAACgmTaGobClone.md)
[3] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)
[4] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)
[5] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
[6] | [Foreign Mathematical Functions](CAACgmUcAmtForeign.md)
[7] | [Creating and Transforming Geometry](CAACgmUcGobCreation.md)
## History

Version: **1** [Apr 2000] | Document created
---|---
