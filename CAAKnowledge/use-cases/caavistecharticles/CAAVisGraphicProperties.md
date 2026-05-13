---
```vbscript
title: "Graphical Properties"
category: tech-article
module: "CAAVisTechArticles"
tags: ["CATIAVisPropertySet", "CATIA", "CATIProperty", "CATIVisProperties", "CATISelectShow", "CATIVisu", "CAAEPstVisPropertiesPoint"]
source_file: "Doc/online/CAAVisTechArticles/CAAVisGraphicProperties.htmmd"
converted: "2026-05-11T17:31:52.277889"
```

---
#  3D PLM Enterprise Architecture

|
## 3D Visualization

|
### Graphical Properties

How to use or implement the _CATIVisProperties_ Interface
---|---|---
Technical Article

* * *
### Abstract

The first objective of this article is to understand what are the graphical properties. The second is to explain how they are integrated in the visualization process. Three interfaces are important: _CATIVisProperties_ , _CATIVisu_ and _CATIProperty_. The first enables to associate with a feature a set of graphical properties, the second uses the _CATIVisProperties_ interface to update the graphic attributes of the graphic representations, and the last stores the data. _CATIVisProperties_ is the main interface of this system.

  * **Principe of the Graphical Properties **
    * The Graphical Properties are Graphical Attributes
    * The Types of Geometry
    * The Graphical Properties by Geometry Type
    * Integration of the Graphical Properties in the Visualization Process
      * Generalites
      * Default behaviors of the SetxxxGraphicAttribute methods
    * In short the Standard Graphical Properties by Type of Geometry
    * Automation
  * **The Interactive Commands**
    * The Properties Command
    * The Graphic Properties Toolbar
    * The Hide/Show Command
  * **Using CATIVisProperties**
  * **Implementing CATIVisProperties**
  * **In Short**
  * **References**

---

* * *
### Principe of the Graphical Properties

Before to go into all the details, a little example to set the subject. Suppose a cube feature [Fig.1 ] which is composed of two types of geometry: faces (6) and edges (12). On this feature, for the set of faces and for the set of edges, graphical properties are put. For faces, it is possible to set a color, a degree of opacity and for the lines, a color, a type and a thickness.

_Fig.1: Graphical Properties on the Cube Feature_ ![](images/CAAVisPropGrapCube.jpg)
---

Before to go into all the details, a little example to set the subject. Suppose a cube feature [Fig.1 ] which is composed of two types of geometry: faces (6) and edges (12). On this feature, for the set of faces and for the set of edges, graphical properties are put. For faces, it is possible to set a color, a degree of opacity and for the lines, a color, a type and a thickness.
_Fig.1: Graphical Properties on the Cube Feature_ ![](images/CAAVisPropGrapCube.jpg)
The principe of the graphical properties lies on the fact that an element (a feature) contains one or several sub-types. A sub-type is sorted by type of geometry: point, line, surfacic etc.... and for each sub-type a set of graphical properties is associated. To integrate them in the visualization process, there is three main interfaces: _CATIVisProperties_ , _CATIProperty_ et _CATIVisu_.

  * _CATIVisProperties_ enables to associate graphical properties to a feature,
  * it uses the _CATIProperty_ to perpetuate the data,
  * it is used by the _CATIVisu_ to update the graphical properties of the graphical representations.

_Fig.2: Relationship Between the Three Interfaces_ ![](images/CAAVisPropGrapSchema.jpg)
---

On this shema, you can see that:

  * The feature implements the three interfaces
  * _CATIVisProperties_ is the central interface.
  * The feature doesn't implement the _CATIVisu_ interface, but an interface which C++ derives from _CATIVisu_. But to generalize the subject, in this article, only the _CATIVisu_ interface will be mentioned.

You can notice that if the componant is not a feature, it can't have graphical properties because the _CATIProperty_ is to use AsIs.
#### The Graphical Properties are Graphical Attributes

You can notice that if the componant is not a feature, it can't have graphical properties because the _CATIProperty_ is to use AsIs.
The graphical properties are visual properties, it means that the properties can be directly use by the visualization processus. These attributs, classified by storage way, are the following:

  1. The graphic attribute, the _CATGraphicAttributeSet_

     * The color,
     * The type of the line (solid, dashed, ...),
     * The thickness of the line,
     * The degree of opacity,
     * The visibility state (show/no show)
     * The selectionabilite state (pick/no pick)
     * The flag for the lowint color

The "Using Graphic Attributes" [1] article enables to familiarize you with this class.

The "Using Graphic Attributes" [1] article enables to familiarize you with this class.
  2. The Graphic Primitive, a _CATGraphicPrimitive_

The marker of the point is set at the _CAT3DMarkeGP_ or _CAT2DMarkerGP_ construction class.

  3. Other:

The number of the layer .

To specify the type of the graphical properties, there is the _CATVisPropertyType_ enum.

  * `CATVPColor `for the color
  * `CATVPOpacite `for the opacity
  * `CATVPWidth `for the line width (thickness)
  * `CATVPLineType `for the line type
  * `CATVPSymbol `for the symbol of the marker
  * `CATVPShow `for the show/no show flag
  * `CATVPPick `for the pick/no pick flag
  * `CATVPInheritance` for the inheritance flag
  * `CATVPLowInt` for the lowint color flag
  * `CATVPLayer` for the layer

At these values, an another one which doesn't represent a property but a set of properties: `CATVPAllProperties.`

The data for the graphical properties (the color, the flag) will be write (read) on a _CATVisPropertiesValues._ It's detailed in the "Using CATIVisProperties" section.
#### The Types of Geometry

At these values, an another one which doesn't represent a property but a set of properties: `CATVPAllProperties.`
The data for the graphical properties (the color, the flag) will be write (read) on a _CATVisPropertiesValues._ It's detailed in the "Using CATIVisProperties" section.
The information stored on the _CATIVisProperties_ is the type (s) of geometry supported by the feature.

CATIA V5 supplies some types of geometry, those in relationship with the dimension of the sub-type are:

  * `CATVPPoint` (O D)
  * `CATVPLine` for a wire and `CATVPEdge` for a line on a surface (1D)
  * `CATVPMesh` for a surface (2D)

an another is for the assembling models:

  * `CATVPAsm`

an another is for the assembling models:
At these five values, there is a last `CATVPGlobalType. `This type regroups together the graphical properties independant of the sub-types: the visibility state, the selectionnability state, the lowint color flag and the number of the layer. Actually in fact, it is not possible to set the points of a wire on a layer, and set its curves on an other layer. It is the globally the element which is on a layer.

These six types, `CATVPPoint`, `CATVPLine`  ,`CATVPEdge` ,`CATVPMesh`, `CATVPAsm`  and `CATVPGlobalType `are _CATVisGeomType_

#### The Graphical Properties by Geometry Type

At these five values, there is a last `CATVPGlobalType. `This type regroups together the graphical properties independant of the sub-types: the visibility state, the selectionnability state, the lowint color flag and the number of the layer. Actually in fact, it is not possible to set the points of a wire on a layer, and set its curves on an other layer. It is the globally the element which is on a layer.
These six types, `CATVPPoint`, `CATVPLine`  ,`CATVPEdge` ,`CATVPMesh`, `CATVPAsm`  and `CATVPGlobalType `are _CATVisGeomType_
To associate graphical properties for a type of geometry, there is the _CATVisPropertiesValues_ class. On an instance of this class, you set the color, the type of point and so on.

On the _CATIProperty_ interface, a copy of this instance is stored. So, a priori, you can set any graphical properties for any type of geometry. But at last, only the graphic properties  interpretable by the process visualization are important. It means that you can set a degree of opacity for your lineic feature, but the visualization process could not translate that. The next section describes that.

#### Integration of the Graphical Properties in the Visualization Process
##### Generalites

In the visualization process, there are two cases to distinguish, even though they join together at the end. The total and the partial revisualization of the model. But at first, it is important to give the methods of the _CATExtIVisu_ adapter class of the _CATIVisu_ interface in relationship with the properties:

  * `virtual CATRep * **BuildRep**(#)`
  * `virtual void **SetGraphicAttribut**(#)`
  * `virtual int **ModifyRep**(const CATNotification & iNotif)`
  * `virtual void **SetPointGraphicAttribute**(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValues)`
  * `virtual void **SetMeshGraphicAttribute**(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValues)`
  * `virtual void **SetLineGraphicAttribute**(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValues`
  * `virtual void **SetEdgeGraphicAttribute**(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValues)`
  * `virtual void **SetAsmGraphicAttribute**(CATRep * iRep, CATVisPropertyType iPropertyType, CATVisPropertiesValues & iPropertyValues)`

  1. The total revisualization of the model

1. The total revisualization of the model
After the construction of the graphic representation (_CATRep_ class), realized by the `BuildRep` method, the `SetGraphicAttribut `method is called. The default implementation of this method, those of the _CATExtIVisu_ adapter class, calls successively (*) the following methods:_ _

     1. Method not exposed to process the independent properties of the sub-elements : visibility, selectionability, layer and lowint (`CATVPGlobalType`)
     2. SetPointGraphicAttribute (`CATVPPoint`)
     3. SetLineGraphicAttribute  (`CATVPLine`)
     4. SetMeshGraphicAttribute (`CATVPMesh`)
     5. SetEdgeGraphicAttribute (`CATVPEdge`)
     6. SetAsmGraphicAttribute (`CATVPAsm`)

(*) These methods are called only if the type of geometry,  set in bracket in the previous list, is defined by the feature.

5. SetEdgeGraphicAttribute (`CATVPEdge`)
6. SetAsmGraphicAttribute (`CATVPAsm`)
The `SetGraphicAttribut `method calls these methods with `CATVPAllProperties `as second argument. It means that all the graphical properties are set on the graphic representation for the given type of geometry. ` `

  2. The partial revisualization of the model

After a _CATModifyVisProperties_ notification, a partial revisualization of the model is done. In fact only the graphical properties are changed. This notification contains the type of the geometry and its new graphical properties. The `ModifyRep` analyzes the input's notification, and calls one of the six methods concerned by the type of geometry. The difference between the total revisualization is the second argument of these methods: it is not necessary `CATVPAllProperties, `but can be one of the _CATVisPropertyType_ enumeration as __`CATVPColor` for example.

In the two cases, the process converges towards the same methods. Their goal is to modify the graphic representation (and their associated graphic attributes) in taken account of the graphic properties set on the `CATVisPropertiesValues `instance`,` the third argument of these methods. It is important to know what do they do in their default implementation, because if the default behavior doesn't fit your need, you will do reimplement those concerned by the type of geometry defined by your feature. See "Implementing CATIVisProperties".

Before to detail them, we have described the second and the third argument of these six methods, there is still the first. It is a `_CATRep_ `pointer which comes from the visualization process. Indeed, it is the graphic representation created in your `BuildRep` extension.

##### Default Behaviors of the SetxxxGraphicAttribute methods

  * **SetPointGraphicAttribute**

The graphical properties processed are the color and the symbol of the marker. The method takes care only the _CAT3DPointRep_ or the _CAT2DPointRep_ class. If your graphic representation is a _CAT3DCustomRep,_ it will be necessary to reimplement it.

  * **SetLineGraphicAttribute**

See SetEdgeGraphicAttribute

  * **SetMeshGraphicAttribute**

The graphical properties processed are the color and the degree of opacity. If the graphic representation is a _CATSurfacicRep,_ the graphic attributes of each faces will be modified, and also the graphic attributes associated to each level of detail [2]. Otherwise, the graphic attribute of the graphic representation is changed.

  * **SetEdgeGraphicAttribute**

The graphical properties processed are the color, the type and the thickness of the line. If the graphic representation is:
    * a _CATSurfacicRep,_ the graphic attributes of each edges will be modified,
    * a CAT3DCustomRep or a CAT2DCustomRep, all the graphic attributes will be modified
    * otherwise, the graphic attribute of the graphic representation is changed

  * **SetAsmGraphicAttribute**

The graphical properties processed are the color, the type of the line, the thickness, the degree of opacity and the inheritance.

#### In short the Standard Graphical Properties by Type of Geometry

The graphical properties processed are the color, the type of the line, the thickness, the degree of opacity and the inheritance.
This section describes in table form [Tab.1] for each type of geometry, the graphical properties taken account by the _CATExtIVisu_ methods that we have detailed just above.

_Tab.1: The Graphic Properties for Each Type of Geometry _ | **The type  of the Geometry** | **Graphic Properties  **

This section describes in table form [Tab.1] for each type of geometry, the graphical properties taken account by the _CATExtIVisu_ methods that we have detailed just above.
_Tab.1: The Graphic Properties for Each Type of Geometry _ | **The type  of the Geometry** | **Graphic Properties  **
CATVPGlobalType |

  * Show/no show state
  * Number of  layer
  * Pick/no pick state
  * Lowint color state

CATVPPoint |

  * Color
  * Symbol of the marker

CATVPLine |  as edge
CATVPEdge |

  * Color
  * Thickness
  * Linetype

CATVPMesh |

  * Color
  * Degree of opacity

CATVPAsm |

  * Inheritance
  * Color
  * Degree of opacity
  * Linetype
  * Thickness

#### Automation

In implementing the _CATIVisProperties_ interface on your feature, you benefit automatically of the _CATIAVisPropertySet_ automation interface .
### The interactive Commands
#### The Properties Command

In implementing the _CATIVisProperties_ interface on your feature, you benefit automatically of the _CATIAVisPropertySet_ automation interface .
```vbscript
If your feature implements _CATIVisProperties,_ when you launch the Properties Commands, the Graphic tab page appears. Its contents depends on the type of geometry defined by the feature. There are three possible cases:

```

  1. In the case where the type of  geometry is  `CATVPPoint` and/or `CATVPLine` and/or `CATVPEdge` and/or `CATVPMesh` (with or without `CATVPGlobalType`):
_Fig.3: The Properties Dialog Box - Case 1_ ![](images/CAAVisPropGrapEditProperties.jpg)

---

1. In the case where the type of  geometry is  `CATVPPoint` and/or `CATVPLine` and/or `CATVPEdge` and/or `CATVPMesh` (with or without `CATVPGlobalType`):
_Fig.3: The Properties Dialog Box - Case 1_ ![](images/CAAVisPropGrapEditProperties.jpg)
This is a sample with a feature which are the types `CATVPGlobalType` and `CATVPPoint`. This page contains two frames:

     * The first is without title, but it contains the sub-frames:  Fill, Edges, Lines and Curves and Points. This frame appears if one of the following type of geometry is defined by the feature: `CATVPPoint, CATVPLine, CATVPEdge `or `CATVPMesh`. If the type is not supported by the feature, its options are disable. In this example, only the point properties (color and symbol) are available.
     * The second whose the title is Show Pick and Layers, appears only if the  `CATVPGlobalType` type is supported by the feature.
This is a sample with a feature which are the types `CATVPGlobalType` and `CATVPPoint`. This page contains two frames:
  2. In the case where the type of  geometry is `CATVPAsm` (with or without `CATVPGlobalType`):
_Fig.4: The Properties Dialog Box - Case 2_ ![](images/CAAVisPropGrapEditProperties2.jpg)

---

2. In the case where the type of  geometry is `CATVPAsm` (with or without `CATVPGlobalType`):
_Fig.4: The Properties Dialog Box - Case 2_ ![](images/CAAVisPropGrapEditProperties2.jpg)
This is an example where the feature defined the types `CATVPAsm` and `CATVPGlobalType`. This page contains two frames:

     * The first has for title "Graphic Properties"
     * The second, Show Pick and Layers, appears only if the  `CATVPGlobalType` type is supported by the feature.
This is an example where the feature defined the types `CATVPAsm` and `CATVPGlobalType`. This page contains two frames:
  3. In the case where the type of  geometry is only `CATVPGlobalType`
_Fig.5: The Properties Dialog Box - Case 3_ ![](images/CAAVisPropGrapEditProperties3.jpg)

---

3. In the case where the type of  geometry is only `CATVPGlobalType`
_Fig.5: The Properties Dialog Box - Case 3_ ![](images/CAAVisPropGrapEditProperties3.jpg)
Only the "Show Pick and Layers" appears.

#### The Graphic Properties Toolbar

Only the "Show Pick and Layers" appears.
The Graphic Properties toolbar, [Fig. 6] is the following:

_Fig.6: The Graphic Properties Toolbar_ ![](images/CAAVisPropGrapToolbarWithCom.jpg)

---

The Graphic Properties toolbar, [Fig. 6] is the following:
_Fig.6: The Graphic Properties Toolbar_ ![](images/CAAVisPropGrapToolbarWithCom.jpg)
When a feature is selected, the toolbar is updated in taken account of the feature's properties. If several features are selected, the behavior is the following:

  * If there are several possible values for a combo, the combo displays undefined (like the combo color in the previous picture [Fig. 6])
  * If there are more than N features selected, all combos are undefined. The value N is customizable through the Tools/Options/Display/Navigation page, in the "Limit Display to Manipulators" option .

You can notice that in this toolbar, there is only one combo for each type of property. Assume that your feature defined the `CATVPPoint` and the `CATVPLine` types. These two types have in common the color property. So a choice must be done to define the type concerned by the color property. It is the goal of the `GetSubTypefromPath `method of the _CATIVisProperties_ interface. This point will be detailed in the Implementing CATIVisProperties" section.
#### The Hide/Show Command

The Hide/Show command enables to hide or show the selected features. But to benefit of this functionality on your feature, it must implement the _CATISelectShow  _ interface. It uses the _CATIVisProperties_ to modify the visibility state of the feature.

[Top]
### Using CATIVisProperties

The Hide/Show command enables to hide or show the selected features. But to benefit of this functionality on your feature, it must implement the _CATISelectShow  _ interface. It uses the _CATIVisProperties_ to modify the visibility state of the feature.
```vbscript
If this section detailed the usage of the _CATIVisProperties_ interface, the "Modifying Object Graphical Properties" article [3] exposes a concrete use case.

```

This interface contains five main methods:

  1. `**GetPropertiesAtt**(CATVisPropertiesValues & oValues, CATVisPropertyType iPropType, CATVisGeomType iGeomType )`
  2. `**SetPropertiesAtt**`(`CATVisPropertiesValues & iValues, CATVisPropertyType iPropType, CATVisGeomType iGeomType )`

The first retrieves the properties from the _CATIProperty_ interface and the second modifies them on the _CATIProperty_ interface

These two methods function on the same principle: the property values are on the _CATVisPropertiesValues_ instance and  two keys

     * `iGeomType, `precises` `the type of the geometry concerned by the property
     * `iPropType, `precises` `the type of the property valid on the _CATVisPropertiesValues_ instance

Example: Lets change the color (`CATVPColor` for the property type)  of a line (`CATVPLine` for the geometry type) represented by the `pLine` pointer.

    ...
    **CATIVisProperties** * pIVisPropertiesOnLine = NULL;
Example: Lets change the color (`CATVPColor` for the property type)  of a line (`CATVPLine` for the geometry type) represented by the `pLine` pointer.
    HRESULT rc = pLine ->**QueryInterface**(IID_CATIVisProperties, (void **) & pIVisPropertiesOnLine );
```vbscript
    if ( SUCCEEDED(rc) )

```

    {
HRESULT rc = pLine ->**QueryInterface**(IID_CATIVisProperties, (void **) & pIVisPropertiesOnLine );
if ( SUCCEEDED(rc) )
       CATVisPropertiesValues MyPropertyOnLine ;
       MyPropertyOnPoint.**SetColor**(255,0,0);
```vbscript
       rc = pIVisPropertiesOnLine ->**SetPropertiesAtt**(MyPropertyOnLine, CATVPColor ,CATVPLine );

```

    }
    ...

---

At first, the _CATVisPropertiesValues_ instance, `MyPropertyOnLine`, is valuated with the color thanks to the `SetColor` method. Next calling the `SetPropertiesAtt` method modifies on the _CATIProperty_ interface only the color of the line geometry because the second argument is `CATVPColor` and the third is `CATVPLine`.

At first, the _CATVisPropertiesValues_ instance, `MyPropertyOnLine`, is valuated with the color thanks to the `SetColor` method. Next calling the `SetPropertiesAtt` method modifies on the _CATIProperty_ interface only the color of the line geometry because the second argument is `CATVPColor` and the third is `CATVPLine`.
  3. `**ResetPropertiesAtt**`(`CATVisPropertyType iPropType, CATVisGeomType iGeomType )`

This methods enables to invalidate the property set on the _CATIProperty_. It means that at the next `GetPropertiesAtt `calls, ``the returned properties values will be the standard values. The returned code of the `GetPropertiesAtt `method, S_AUTOMATIC, precises that the returned properties values is the standard. To set new specific properties, a new `SetPropertiesAtt` will be necessary.

Example: Always with the line, pointed by  `pIVisPropertiesOnLine`, the color of the `CATVPLine` geometry type is reseted.

         ...
This methods enables to invalidate the property set on the _CATIProperty_. It means that at the next `GetPropertiesAtt `calls, ``the returned properties values will be the standard values. The returned code of the `GetPropertiesAtt `method, S_AUTOMATIC, precises that the returned properties values is the standard. To set new specific properties, a new `SetPropertiesAtt` will be necessary.
Example: Always with the line, pointed by  `pIVisPropertiesOnLine`, the color of the `CATVPLine` geometry type is reseted.
         HRESULT rc = pIVisPropertiesOnLine ->**ResetPropertiesAtt**(CATVPColor ,CATVPLine);
```vbscript
         if ( SUCCEEDED(rc) )

```

         {
HRESULT rc = pIVisPropertiesOnLine ->**ResetPropertiesAtt**(CATVPColor ,CATVPLine);
if ( SUCCEEDED(rc) )
            CATVisPropertiesValues MyPropertyOnLine ;
            rc = pIVisPropertiesOnLine ->**GetPropertiesAtt**(MyPropertyOnLine, CATVPColor ,CATVPLine );
```vbscript
```vbscript
            if ( S_AUTOMATIC == rc )

```

```

            {

            }else cout <<" error" << endl;
         }
         ...

---

In this example, you can see that after the `ResetPropertiesAtt `call`, `for the same key` ``CATVPColor` and `CATVPLine, `the `GetPropertiesAtt `method returns the` ``S_AUTOMATIC `value`. `It means that the color sets on the `MyPropertyOnLine` instance, is the standard color, so the same value as those returned by the `GetStandardProperties `method with the same keys`. `

In this example, you can see that after the `ResetPropertiesAtt `call`, `for the same key` ``CATVPColor` and `CATVPLine, `the `GetPropertiesAtt `method returns the` ``S_AUTOMATIC `value`. `It means that the color sets on the `MyPropertyOnLine` instance, is the standard color, so the same value as those returned by the `GetStandardProperties `method with the same keys`. `
Note: if any `SetPropertiesAtt` call has been  done on the feature, it has standard values.

  4. `**GetStandardProperties**(CATVisPropertiesValues & oValues, CATVisPropertyType iPropType, CATVisGeomType iGeomType )`

This method retrieves the standard properties. These values are the values managed by the _CATIVisProperties_ implementation [Tab. 2] and are not the standard of creation that you can manage with the "Standards..." command.

_Tab.2: The standard values for each type of property _ | **The type  of the property** | **The standard value**

This method retrieves the standard properties. These values are the values managed by the _CATIVisProperties_ implementation [Tab. 2] and are not the standard of creation that you can manage with the "Standards..." command.
_Tab.2: The standard values for each type of property _ | **The type  of the property** | **The standard value**
Color | white (255,255,255)
Symbol  | Cross
Thickness of a line | 1
Type of a line | Solid
Degree of opacity | 0
Number of the layer | 0

Caution: The contents of this table can be different between two implementations of the _CATIVisProperties_ interface. The DS features, implementing the `GetStandardProperties `methods`, `have perhaps another standard values. Here the standard values defined by the _CATExtIVisProperties_ methods are exposed.

  5. `**IsGeomTypeDefined**(CATVisGeomType iGeomType)`

Tells if  a given type of geometry is recognized by the feature.

[Top]
### Implementing CATIVisProperties

Tells if  a given type of geometry is recognized by the feature.
```vbscript
If this section detailed the implementation of the _CATIVisProperties_ interface, the "Implementing CATIVisProperties" article exposes a concrete use case. You will find this article in the Product Process Resouce (PPR) part of the CAA encyclopedie.

```

To implement this interface you use the _CATExtVisProperties_ adapter class. __There are two methods to overwrite:

  * `IsGeomTypeDefined`

It is the method to define one or several type of geometry for the feature. Here is an example for a feature which defined the `CATVPPoint` and the `CATVPGlobalType` types.

    ...
It is the method to define one or several type of geometry for the feature. Here is an example for a feature which defined the `CATVPPoint` and the `CATVPGlobalType` types.
    HRESULT CAAEPstVisPropertiesPoint::**IsGeomTypeDefined**(CATVisGeomType & iGeomType)

    {
It is the method to define one or several type of geometry for the feature. Here is an example for a feature which defined the `CATVPPoint` and the `CATVPGlobalType` types.
HRESULT CAAEPstVisPropertiesPoint::**IsGeomTypeDefined**(CATVisGeomType & iGeomType)
        HRESULT rc = E_FAIL ;

        if ( (**CATVPPoint** == iGeomType) || (**CATVPGlobalType** == iGeomType) )
            rc =  S_OK ;
        return rc ;

    }
    ...

---

This method returns S_OK when the type is valid otherwise E_FAIL.

**Overwrite or not the methods of the _CATExtIVisu_ adapter class of the _CATIVisu_ interface**

This method returns S_OK when the type is valid otherwise E_FAIL.
You have chosen one or several types among the following types: `CATVPPoint`, `CATVPLine`, `CATVPEdge`, `CATVPAsm`, `CATVPMesh. `But in studying the default behavior of the methods of the _CATExtIVisu_ class, associated at each type you have chosen, you note that their process don't fit your need: the graphic representation of your feature will not be correctly modified.

Take an example, the feature is a wire which contains lineic sub-elements (lines) and points. The type of geometry are `CATVPPoint` and `CATVPLine. `So the methods of the _CATExtIVisu_ are _SetPointGraphicAttribute_ to modify the points attributes and _SetLineGraphicAttribute_ for those of the lines. The graphic representation of the feature is a _CAT3DCustomRep_ with one _CAT3DMarkerGP_ for all the points and one _CAT3DLineGP_ for all the lines. It is necessary to overwrite these two methods because:

    * The `SetPointGraphicAttribute` method doesn't process the _CAT3DCustomRep_ as graphic representation.
    * The `SetLineGraphicAttribute` method modifies all its graphic attributes, so the attribute for the point will be also changed.

  * `GetSubTypeFromPath`

This method enables to define the type of geometry concerned by the graphic properties displayed in the Graphic Properties toolbar. See the section "The Graphic Properties Toolbar"

Here an example for the point feature:

    ...
This method enables to define the type of geometry concerned by the graphic properties displayed in the Graphic Properties toolbar. See the section "The Graphic Properties Toolbar"
Here an example for the point feature:
    HRESULT CAAEPstVisPropertiesPoint::GetSubTypeFromPath(CATPathElement & iPathElement,
                                                          CATVisPropertyType iPropertyType,
                                                          CATVisGeomType & oGeomType,
                                                          unsigned int & oPropertyNumber)
        HRESULT rc = E_FAIL ;

        switch ( iPropertyType )

        {
unsigned int & oPropertyNumber)
HRESULT rc = E_FAIL ;
switch ( iPropertyType )
```vbscript
        case **CATVPColor** :
        case **CATVPSymbol** :
```

            oGeomType = **CATVPPoint** ;

            rc = S_OK ;
            break;

        }
oGeomType = **CATVPPoint** ;
rc = S_OK ;
break;
        oPropertyNumber = 0 ;
        return rc ;

    }
    ...

---

In the toolbar, the color and the symbol are associated to the `CATVPPoint` geometry.

You can note that `oPropertyNumber` should be always set to zero and that the graphic properties associated to the `CATVPGlobalType` type are not processed (`CATVPShow`, `CATVPLayer`, `CATVPPick`,`CATVPLowint`), it is by default done.

[Top]

* * *
### In Short

This article describes how the graphic properties are integrated in the visualization process. The principle is that a feature can have a set of graphic properties for each of its component's geometry. Each component is defined as a geometry type. Three interface are essentials:

  * _CATIProperty_

It stores permanently the data. A feature natively implements this interface.

  * _CATIVisProperties_

It kepts the type of geometry defined on the feature. Its implementation asks sometimes to overwrite some methods of the _CATExtIVisu_ class adapter of the _CATIVisu_ interface.

  * _CATIVisu_

It uses the _CATIVisProperties_ to know the properties to associate to the graphic representation.

[Top]

* * *
### References

[1] | [Using Graphic Attributes](../CAAVisUseCases/CAAVisSampleGraphicAtt.md)
---|---
[2] | [Creating Levels of Details](../CAAVisUseCases/CAAVisSampleLOD.md)
[3] | [Modifying Object Graphical Properties](../CAAVisUseCases/CAAVisSampleUseCATIVisProperties.md)
[Top]

* * *
### History

Version: **1** [Jun 2002] | Document created
---|---
[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
