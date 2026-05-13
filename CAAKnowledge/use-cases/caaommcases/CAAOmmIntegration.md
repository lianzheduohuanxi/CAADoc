---
title: "Integrating a New Mechanical Feature in the CAA Exposed Model"
category: "use case"
module: "CAAOmmUseCases"
tags: "["CATIContainer_var", "CAAOmmverticalLine", "CATISpecObject", "CATIAReferences", "CAAOllTypeLib", "CAAEOmmBuildVerticalLine", "CAAOmmVerticalLine", "CATIAReference", "CAAOmmCatalog", "CATIAHybriShape", "CATIPartRequest", "CATIAPart", "CATIAHybridShape", "CAAIOmmFactory", "CAAIAOmmFactory", "CATIBuild", "CAAIA", "CAAIOmmVerticalLine", "CAAOmm", "CATIAlias"]"
source_file: "Doc/online/CAAOmmUseCases/CAAOmmIntegration.htm"
converted: "2026-05-11T17:33:46.031570"
---
tags: ["CATIContainer_var", "CAAOmmverticalLine", "CATISpecObject", "CATIAReferences", "CAAOllTypeLib", "CAAEOmmBuildVerticalLine", "CAAOmmVerticalLine", "CATIAReference", "CAAOmmCatalog", "CATIAHybriShape", "CATIPartRequest", "CATIAPart", "CATIAHybridShape", "CAAIOmmFactory", "CAAIAOmmFactory", "CATIBuild", "CAAIA", "CAAIOmmVerticalLine", "CAAOmm", "CATIAlias"]
source_file: "Doc/online/CAAOmmUseCases/CAAOmmIntegration.htmmd"
converted: "2026-05-11T17:33:46.031570"
Mechanical Modeler |  |  Integrating a New Mechanical Feature in the CAA Exposed Model _Performing OLE replay on features_

converted: "2026-05-11T17:33:46.031570"
Mechanical Modeler |  |  Integrating a New Mechanical Feature in the CAA Exposed Model _Performing OLE replay on features_
Use Case

* * *

Abstract This article shows how to integrate a new feature in the CATIA OLE-exposed model so that Visual Basic or Java Script can create and manipulate this feature.

  * **What You Will Learn With This Use Case**
  * **The CAAOmm Use Case**
    * What Does CAAOmm Do
    * How to Launch CAAOmm
    * Where to Find the CAAOmm Code
  * **Step-by-Step**
  * **In Short**
  * **References**

---

* * *

What You Will Learn With This Use Case This use case explains how to integrate a new feature so that any OLE-based scripting language can create and use this feature. It shows how to extend the default CATIA OLE model. [Top] The CAAOmm Use Case CAAOmm use case implements a basic mechanical feature, ` CAAOmmVerticalLine`, and provides all the mandatory implementation to be fully OLE integrated. It illustrates IDL interfaces design and MechanicalModeler OLE resources usage. The `CAAOmmVerticalLine` startup is defined in `CAAOmmCatalog.CATfct` file. It is derives from `GSMGeom` (SuperTypeName) which is declared public and derivable in the CATHybridShape.CATSpecs file. Our vertical line feature has two "in" attributes, which are features (_tk_specobject_) from the Vertical Line standpoint. They are actually be point features, hence their name of "Point 1" and "Point2".  [Top] What Does CAAOmm Do CAAOmm includes a simple mechanical feature, drawing a vertical line from a point and limited by the normal projection on another one in the XY plane. This feature is created by a Visual Basic script. **Snapshot of the result** ![](images/CAAOmmUseCaseSnapshot.jpg) [Top] How to Launch CAAOmm The sample contained in CAAOLE4MecMod.edu is intended to be used through a Visual Basic Macro. First, you have:

  * To compile the sample with mkmk -aug [1]
  * To generate the runtime view with mkCreateRuntimeView [1]

Once all the modules contained in CAAOLE4MecMod.edu have been compiled, you have to launch CATIA and properly configure the TypeLib: CATIA has to know about the new OLE object contained in the sample TypeLib named OmmTypeLib, this .tlb file is located under your workspace runtime view (.../code/bin). Thus, you should import this library with the "Option" Menu such as shown below. ![](images/CAAOmmSettings.jpg) Then you should execute the following macro thru the Tools menu:

    Language="VBSCRIPT"

```vbscript
```cpp
    Sub CATMain(#)

```
```

```vbscript
```vbscript
      Dim doc0 As Document
```vbscript
```
```vbscript
```cpp
      Set doc0 = CATIA.Documents.Add("Part")

      Dim body1 As HybridBody
      Set body1 = doc0.Part.HybridBodies.Add(#)

      Dim point1 As HybridShapePointCoord
      Set point1 = doc0.Part.HybridShapeFactory.AddNewPointCoord( 20., 50., 0. )
```
```

```

      body1.AppendHybridShape point1

```vbscript
      Dim point2 As HybridShapePointCoord
```vbscript
```
```vbscript
      Set point2 = doc0.Part.HybridShapeFactory.AddNewPointCoord( -30., 80., 0. )
```
```

      body1.AppendHybridShape point2

```

```vbscript
```vbscript
Set point2 = doc0.Part.HybridShapeFactory.AddNewPointCoord( -30., 80., 0. )
```
```

body1.AppendHybridShape point2
      doc0.Part.InWorkObject = point2
      doc0.Part.Update

```vbscript
```vbscript
      Dim Reference1 As Reference
```vbscript
```
```vbscript
```vbscript
      Set Reference1 = doc0.Part.CreateReferenceFromGeometry ( point1 )

      Dim Reference2 As Reference
      Set Reference2 = doc0.Part.CreateReferenceFromGeometry ( point2)

      Dim CustFact0 As Factory
      Set CustFact0 = doc0.Part.GetCustomerFactory("OmmFactory")

      Dim line1 As OmmVerticalLine
      Set line1 = CustFact0.AddNewVerticalLine( Reference1, Reference2 )
```
```

```

      body1.AppendHybridShape line1

```

```vbscript
```vbscript
Set line1 = CustFact0.AddNewVerticalLine( Reference1, Reference2 )
```
```

body1.AppendHybridShape line1
      line1.Compute

```vbscript
```vbscript
    End Sub

```

```

---
[Top] Where to Find the CAAOmm Code The CAAOmm use case is made of several modules located in the CAAOLE4MecMod.edu framework: Windows | `InstallRootDirectory/CAAOLE4MecMod.edu/`
---|---
Unix | `InstallRootDirectory/CAAOLE4MecMod.edu/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. Modules Repartition

---
Unix | `InstallRootDirectory/CAAOLE4MecMod.edu/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. Modules Repartition
CAAOmmInterfaces.m | Module containing the directives to process the IDL interfaces (TIE and IID)
CAAOmmTypeLib.m | Module containing the directives to create the TypeLib of this sample exposed model objects
CAAOmmImpl.m | Module handling all the interface implementations
Source files Repartition
CAAIAOmmFactory.idl | IDL interface defining the sample OLE exposed factory
CAAIAOmmVerticalLine.idl | IDL interface defining the OLE exposed vertical line behavior
CAAOmmTypeLib.tlb | TypeLib definition including OmmFactory and OmmVerticalLine exposed objects
CAAEOmmFactory.cpp | Extension of the Part document root element implementing CAAIAOmmFactory interface
CAAEOmmVerticalLine.cpp | Extension of the VerticalLine feature implementing CAAIAOmmVerticalLine interface
CAAEOmmBuildVerticalLine.cpp | Extension of the VerticalLine feature implementing the CATIBuild interface (geometrical valuation)
CAAOLE4MecMod.edu.dico | Object Modeler dictionary
CAAOLE4MecMod.edu.iid | Object Modeler dictionary extension (meta objects names, aliases and IID mapping)
CAAOmmCatalog.CATfct | The feature catalog file describing CAAOmmverticalLine Startup

[Top] Step-by-Step # | Step | Where
---|---|---
CAAOLE4MecMod.edu.dico | Object Modeler dictionary
CAAOLE4MecMod.edu.iid | Object Modeler dictionary extension (meta objects names, aliases and IID mapping)
CAAOmmCatalog.CATfct | The feature catalog file describing CAAOmmverticalLine Startup
1 | Designing the Exposed Model | N/A
2 | Creating IDL Interfaces | PublicInterfaces
3 | Creating a Type Library | CAAOmmTypeLib.m
4 | Implementing IDL Interfaces | CAAEOmmFactory.cpp and CAAEOmmVerticalLine.cpp

[Top] Designing the Exposed Model Now that we have a brand new feature, we need to add some code around it in order to integrate it within the world of automation objects that Shape Design exposes. Here is a schematic view, expressed in UML, of the objects involved in that process. The blue boxes depict the objects that we will add as part of this use case. ![](images/CAAOmmUseCaseModel.jpg) Let us first isolate the objects in this schema that are directly exposed to the automation world. Those are the ones whose name begins with "CATIA". The CATIAPart is the top level automation object here. It aggregates a collection of CATIAHybridBody, named CATHybridBodies, which in turn aggregates a collection of CATIAHybridShape, names CATIAHybridShapes. This implements the hierarchy of containers-and-objects that is classical in automation:

3 | Creating a Type Library | CAAOmmTypeLib.m
4 | Implementing IDL Interfaces | CAAEOmmFactory.cpp and CAAEOmmVerticalLine.cpp
    Part
      HybridBodies
        HybridBody
          HybridShapes
            HybridShape

Underneath this hierarchy of automation objects, there is a parallel hierarchy of features, that are not visible from automation, but actually implement in the Mechanical Modeler what those automation objects can do. These are:

    MechanicalPart (corresponds to HybridBodies)
```vbscript
      GSMTool (corresponds to HybridBody and HybridShapes)
        GSMGeom (corresponds to HybridShape: any wireframe/surfacic element)

```

Last, the CATIAPart object can instantiate a CATIAFactory object (through GetCustomerFactory(#)), which in turn can instantiate any automation object that may be needed, in particular instances of CATIA HybridShape. What about adding our Vertical Line feature to this? What we have done so far is creating a new feature with GSMGeom as father. This is the blue box in the lower left corner. The first step is to enrich this feature so that it implements a newly designed automation interface through which it can be manipulated from the automation world. This interface is named CAAIAOmmVerticalLine (CAAIA is CAA counterpart to CATIA as prefix for automation interfaces). This interface has got four methods for manipulating the Vertical Line by the two points that constrain it (blue box at bottom right). Since a Vertical Line is a kind of HybridShape, the CAAIAOmmVerticalLine interface derives from the CATIAHybridShape interface, so that all methods that apply to HybridShape also apply to our line. The script sample for example uses CATIAHybriShape::Compute to update the newly Created CAAOmmVerticalLine. Being a CATIAHybridShape also allows our feature to be put in the collection of Hybrid Shapes of an Hybrid Body, allowing to retrieve it through the same container-object access mechanism as the other Hybrid Shape features.  The code that implements this interface on the CAAOmmVerticalLine feature is beared by an extension to it, named CAAEOmmVerticalLine (bottom center). As our newly created feature inherits from GSMGeom, it inherits mechanical behaviors including an implementation for CATIAHybridShape. The last step consists in extending our automation model so that instances of CAAIAOmmVerticalLine can actually be created. This is done by providing another automation factory, called CAAIAOmmFactory. This factory's single method, AddNewVerticalLine(#), instantiates a CAAIAOmmVerticalLine. The implementation code for CAAIAOmmFactory is beared by the CAAEOmmFactory class, which is an extension to the MechanicalPart Feature. This is mandatory in order for your factory to be found at run time. [Top] Creating IDL Interfaces We are now going to implement the interfaces we need as designed in the previous step. Since these interfaces are to be used in a variety of programming languages, such as Visual Basic or JavaScript, it is not written in a specific language, but in IDL (Interface Definition Language), a language which is specific to the definition of interfaces that can be used in a multi-languages environment. Here is the source file for the factory interface:

    interface CAAIAOmmFactory : CATIAFactory

    {
Last, the CATIAPart object can instantiate a CATIAFactory object (through GetCustomerFactory(#)), which in turn can instantiate any automation object that may be needed, in particular instances of CATIA HybridShape. What about adding our Vertical Line feature to this? What we have done so far is creating a new feature with GSMGeom as father. This is the blue box in the lower left corner. The first step is to enrich this feature so that it implements a newly designed automation interface through which it can be manipulated from the automation world. This interface is named CAAIAOmmVerticalLine (CAAIA is CAA counterpart to CATIA as prefix for automation interfaces). This interface has got four methods for manipulating the Vertical Line by the two points that constrain it (blue box at bottom right). Since a Vertical Line is a kind of HybridShape, the CAAIAOmmVerticalLine interface derives from the CATIAHybridShape interface, so that all methods that apply to HybridShape also apply to our line. The script sample for example uses CATIAHybriShape::Compute to update the newly Created CAAOmmVerticalLine. Being a CATIAHybridShape also allows our feature to be put in the collection of Hybrid Shapes of an Hybrid Body, allowing to retrieve it through the same container-object access mechanism as the other Hybrid Shape features.  The code that implements this interface on the CAAOmmVerticalLine feature is beared by an extension to it, named CAAEOmmVerticalLine (bottom center). As our newly created feature inherits from GSMGeom, it inherits mechanical behaviors including an implementation for CATIAHybridShape. The last step consists in extending our automation model so that instances of CAAIAOmmVerticalLine can actually be created. This is done by providing another automation factory, called CAAIAOmmFactory. This factory's single method, AddNewVerticalLine(#), instantiates a CAAIAOmmVerticalLine. The implementation code for CAAIAOmmFactory is beared by the CAAEOmmFactory class, which is an extension to the MechanicalPart Feature. This is mandatory in order for your factory to be found at run time. [Top] Creating IDL Interfaces We are now going to implement the interfaces we need as designed in the previous step. Since these interfaces are to be used in a variety of programming languages, such as Visual Basic or JavaScript, it is not written in a specific language, but in IDL (Interface Definition Language), a language which is specific to the definition of interfaces that can be used in a multi-languages environment. Here is the source file for the factory interface:
interface CAAIAOmmFactory : CATIAFactory
      HRESULT AddNewVerticalLine(in CATIAReference ipiReferenceOnPoint1,
                                 in CATIAReference ipiReferenceOnPoint2,
                                 out /*IDLRETVAL*/ CAAIAOmmVerticalLine opiVerticalLineOnLine);

    };

    // Interface name : CAAIOmmFactory
    #pragma ID CAAIAOmmFactory "DCE:c726e680-1538-11d4-9eea00508b675465"
    #pragma DUAL CAAIAOmmFactory

    // VB object name : OmmFactory (Id used in Visual Basic)
    #pragma ID OmmFactory "DCE:c726e681-1538-11d4-9eea00508b675465"
    #pragma ALIAS CAAIAOmmFactory OmmFactory

---
The IDL is close to common object programming languages such as Java or C++. Most noticeable differences are:

  * Argument direction (in, out) must be declared
  * A special comment, /* IDLRETVAL */, can be inserted before the last out argument of an interface. It allows this argument to be used as a lvalue in an expression, like in

    ...
      dim myLine as OmmVerticalLine;
```vbscript
      OmmVerticalLine = AddNewVerticalLine(PStart, PEnd);
```

    ...

---
```vbscript
dim myLine as OmmVerticalLine;
```vbscript
OmmVerticalLine = AddNewVerticalLine(PStart, PEnd);
```

The last four lines of the file are #pragmas, ie compiler directives. The first #pragma (ID) is used to associate the interface name as defined for human usage ("OmmFactory") with a GUID (Globally Unique Identifier), which is used by the system to unically indentify your interface. That way, even if another interface is named OmmFactory elsewhere, no confusion can occur. The DUAL #pragma declares that this interface can be used in late binding mode allowing access by automation controlers like VBScript. The ALIAS #pragma is a commodity pragma. It actually defines a shorter name ("OmmFactory") for the interface complete name ("CAAIAOmmFactory"). That way, the entity represented by this interface can be handled in Visual Basic with type "OmmFactory" instead of "CAAIAOmmFactory"), which improves the code readability. Before being used, this alias should be declared as any other ID with a GUID. You can find more information on the IDL language and the automation mechanisms in [2] and [4]. To complete the mechanism allowing to retrieve your factory, you need to put the following line in a file suffixed .iid, in the dictionary. Here it's called CAAOLE4MecMod.edu.iid.

```

    {c726e680-1538-11d4-9eea-00508b675465} CAAIAOmmFactory OmmFactory

---
It contains the GUID of the automation class, its name and the name of the feature that bears its implementation.

    interface CAAIAOmmVerticalLine : CATIAHybridShape
    {
      #pragma PROPERTY Point1

interface CAAIAOmmVerticalLine : CATIAHybridShape
      HRESULT get_Point1(out /*IDLRETVAL*/ CATIAReference opiReferenceOnPoint1);
      HRESULT put_Point1(in CATIAReference ipiReferenceOnPoint1);

      #pragma PROPERTY Point2
HRESULT get_Point1(out /*IDLRETVAL*/ CATIAReference opiReferenceOnPoint1);
HRESULT put_Point1(in CATIAReference ipiReferenceOnPoint1);
      HRESULT get_Point2(out /*IDLRETVAL*/ CATIAReference opiReferenceOnPoint2);
      HRESULT put_Point2(in CATIAReference ipiReferenceOnPoint2);

    };

    // Interface name : CAAIOmmVerticalLine
    #pragma ID CAAIAOmmVerticalLine "DCE:2ea944f0-1539-11d4-9eea00508b675465"
    #pragma DUAL CAAIAOmmVerticalLine

    // VB object name : OmmVerticalLine (Id used in Visual Basic)
    #pragma ID OmmVerticalLine "DCE:2ea944f1-1539-11d4-9eea00508b675465"
    #pragma ALIAS CAAIAOmmVerticalLine OmmVerticalLine

---
The IDL code for the second interface follows the same rules, but introduces one more #pragma, the PROPERTY #pragma. Such a #pragma must precede two methods definitions whose signature is put_* and get_* respectively. The two methods must have one argument, in and out respectively, and the get_* method must qualify its argument with /* IDLRETVAL */. Given those writing conventions, what you get is something that, despite the fact that the interface is totally method-based and does not hold any instance data by itself, appears to the scripting client as an instance data beared by the interface (hence the name 'property'). As a result, such VBasic code becomes possible:

    ...
The IDL code for the second interface follows the same rules, but introduces one more #pragma, the PROPERTY #pragma. Such a #pragma must precede two methods definitions whose signature is put_* and get_* respectively. The two methods must have one argument, in and out respectively, and the get_* method must qualify its argument with /* IDLRETVAL */. Given those writing conventions, what you get is something that, despite the fact that the interface is totally method-based and does not hold any instance data by itself, appears to the scripting client as an instance data beared by the interface (hence the name 'property'). As a result, such VBasic code becomes possible:
      dim myLine as OmmVerticalLine;
```vbscript
```vbscript
      dim PStart as Point;
      dim rPStart as Reference;
```

```

      rPStart = Pstart;
```vbscript
      myLine.Point1 = rPStart;

```

    ...

---
rPStart = Pstart;
myLine.Point1 = rPStart;
What actually happens is an encapsulation by the interface of all the calls to get_Point1 and put_Point1 that are necessary to place a reference on PStart as the starting point for our OmmVerticalLine. The net result is a much simpler and straightforward client VBasic code. [Top] Creating a Type Library IDL source is not used as is by the languages that use it as a medium to resources programmed in other languages. It must be compiled first, and the result of this compilation is called a _typelib_. Creating a typelib is useful for two reasons:

  1. It allows the correctness of IDL source to be verified, producing build-time errors, always better than run-time errors
  2. the typelib is a much more efficient interface information repository that the raw IDL source for clients

So, the next step is to compile our two interfaces into a typelib. Creating a new typelib requires a little directives to be given to our IDL compiler thanks to a couple of new #pragmas. Here is the source code for the file containing those directives. This file has a .tlb extension and is to be put in the src directory of a specific module whose Imakefile.mk type is TYPELIB. Here it's called CAAIAOmmTypeLib.tlb in the CAAOllTypeLib.m module.

    #pragma REPID CAAOmm "DCE:872b73b0-1538-11d4-9eea00508b675465"
    #pragma REPBEGIN CAAOmm
    #pragma REPREQ InfTypeLib
    #pragma REPREQ MecModTypeLib
    #include "CAAIAOmmVerticalLine.idl"
    #include "CAAIAOmmFactory.idl"
    #pragma REPEND CAAOmm

---
The REPID #pragma names our typelib and assign it a GUID, just like we did previously for interfaces and for the same reasons. The CAAOmm typelib code itself is comprised between the delimiting #pragmas REPBEGIN and REPEND. It includes two sections:

  1. REPREQ #pragmas indicate that the newly defined typelib uses interfaces previously defined in other typelibs ("InfTypeLib" and "MecModTypeLib"). That way, definition of interfaces like CATIAReference can be used within CAAOmm while being defined elsewhere.
  2. #include directives import in that typelib definition file the IDL definition for the newly defined interfaces.

[Top] Implementing IDL Interfaces At this point, we are done with what is necessary to allow scripting languages to access our C++ code for the VerticalLine feature, that is, IDL interface definition and a typelib as their repository. What's next? The actual C++ implementation of the interfaces that we have 'promised' to the external world via the typelib. This is explained in six steps:

1. REPREQ #pragmas indicate that the newly defined typelib uses interfaces previously defined in other typelibs ("InfTypeLib" and "MecModTypeLib"). That way, definition of interfaces like CATIAReference can be used within CAAOmm while being defined elsewhere.
2. #include directives import in that typelib definition file the IDL definition for the newly defined interfaces.
  1. Create a C++ class to implement the CAAIAOmmFactory interface
  2. Implement get_Name for this class
  3. Implement get_Parent for this class
  4. Implement the specific method of this interface: CreateVerticalLine
  5. Create a C++ class to implement the CAAIAOmmVerticalLine interface, and implement get_Name and get_Parent for this class
  6. Implement the specific methods of this interface

And this is what we are going to do now:

  1. we start by the Ommfactory interface

         ...
         #include "TIE_CAAIAOmmFactory.h"
1. we start by the Ommfactory interface
         TIE_CAAIAOmmFactory(CAAEOmmFactory);

         CATImplementClass( CAAEOmmFactory,
                            DataExtension,
                            CATBaseUnknown,
                            MechanicalPart );

         ...

---
CATBaseUnknown,
MechanicalPart );
The IDL compilation of our IDL interfaces has produced a TIE_CAAIAOmmFactory.h C++ header file that we are going to use here for the definition of methods that must be provided as implementations for the IDL interface methods. CAAEOmmFactory is the name of the C++ class that we provide as the implementation class for the IDL OmmFactory interface. As per our previous design (see Designing The Exposed Model above), CAAEOmmFactory is an extension (CAA**E**) of the MechanicalPart feature. We can now begin to implement its methods, beginning by get_Name(#).
  2. We can now begin to implement its methods,beginning by get_Name(#).

         ...
The IDL compilation of our IDL interfaces has produced a TIE_CAAIAOmmFactory.h C++ header file that we are going to use here for the definition of methods that must be provided as implementations for the IDL interface methods. CAAEOmmFactory is the name of the C++ class that we provide as the implementation class for the IDL OmmFactory interface. As per our previous design (see Designing The Exposed Model above), CAAEOmmFactory is an extension (CAA**E**) of the MechanicalPart feature. We can now begin to implement its methods, beginning by get_Name(#).
2. We can now begin to implement its methods,beginning by get_Name(#).
         HRESULT CAAEOmmFactory::get_Name(CATBSTR & oName)

         {
           // Instance is a singleton : name is the meta-class alias name
HRESULT CAAEOmmFactory::get_Name(CATBSTR & oName)
           CATUnicodeString str ("**OmmFactory** ");
           str.ConvertToBSTR(&oName);
           return S_OK;

         }
         ...

---
return S_OK;
Our factory must provide a get_Name(#) method because it inherits from the anyObject interface through its CATIAFactory parent (in other words, each scripting object must be able to name itself). As an extension of the MechanicalPartFeature feature that is unique within a Part document, there will be only one CAAIOmmFactory per document. We so choose to return always the same name: OmmFactory.
  3. There is another property that is common to all automation objects, the Parent property. This is the goal of the next methods, still inherited from anyObject interface.

         ...
Our factory must provide a get_Name(#) method because it inherits from the anyObject interface through its CATIAFactory parent (in other words, each scripting object must be able to name itself). As an extension of the MechanicalPartFeature feature that is unique within a Part document, there will be only one CAAIOmmFactory per document. We so choose to return always the same name: OmmFactory.
3. There is another property that is common to all automation objects, the Parent property. This is the goal of the next methods, still inherited from anyObject interface.
         HRESULT __stdcall CAAEOmmFactory::get_Parent(CATBaseDispatch *&opiBaseOnOLEParent)

         {
3. There is another property that is common to all automation objects, the Parent property. This is the goal of the next methods, still inherited from anyObject interface.
HRESULT __stdcall CAAEOmmFactory::get_Parent(CATBaseDispatch *&opiBaseOnOLEParent)
           HRESULT rc=QueryInterface(IID_CATIAPart, (void**) &opiBaseOnOLEParent);
           return rc;

         }
         ...

---
return rc;
The data model exposed through automation is basically an aggregation model. As a result, every exposed object appears as aggregated within a higher level entity: a part contains a collection of its bodies, within which each body contains a collection of its features, and so on. The exposed data model is therefore organized as a tree. For any node in that tree, except the top node, the Parent property is expected to return the aggregating node above its target object. This can sometimes make this property non trivial to implement, if the actual underlying data model is not organized as an aggregation model, as an automation client expects. Here the situation is not desperate, though. Since the OmmFactory can be obtained from the Part through GetCustomerFactory(#), and this is the only path to the factory, the OmmFactory appears to be contained in the Part. Therefore, when asked for its parent, the OmmFactory should return the Part object. However, behind the scenes, ie in the C++ world, the OmmFactory and the Part are actually one single object, or, more precisely, two extensions of the same Object Modeler component, the Mechanical Part. Consequently, the OmmFactory, to return its associated Part, returns itself cast to a CATIAPart interface thanks to an appropriate QueryInterface(#).
  4. After paying this tribute to the Automation world by implementing Parent and Name properties, we can now skip to the actual job of this factory: instantiating VerticalLine feature objects. This longer method is split is severel steps, here is the first one.

         ...
The data model exposed through automation is basically an aggregation model. As a result, every exposed object appears as aggregated within a higher level entity: a part contains a collection of its bodies, within which each body contains a collection of its features, and so on. The exposed data model is therefore organized as a tree. For any node in that tree, except the top node, the Parent property is expected to return the aggregating node above its target object. This can sometimes make this property non trivial to implement, if the actual underlying data model is not organized as an aggregation model, as an automation client expects. Here the situation is not desperate, though. Since the OmmFactory can be obtained from the Part through GetCustomerFactory(#), and this is the only path to the factory, the OmmFactory appears to be contained in the Part. Therefore, when asked for its parent, the OmmFactory should return the Part object. However, behind the scenes, ie in the C++ world, the OmmFactory and the Part are actually one single object, or, more precisely, two extensions of the same Object Modeler component, the Mechanical Part. Consequently, the OmmFactory, to return its associated Part, returns itself cast to a CATIAPart interface thanks to an appropriate QueryInterface(#).
4. After paying this tribute to the Automation world by implementing Parent and Name properties, we can now skip to the actual job of this factory: instantiating VerticalLine feature objects. This longer method is split is severel steps, here is the first one.
         HRESULT __stdcall CAAEOmmFactory::AddNewVerticalLine(
                        CATIAReference * ipiReferenceOnPoint1,
                        CATIAReference * ipiReferenceOnPoint2,
                        CAAIAOmmVerticalLine *& opiVerticalLineOnLine)

         {
HRESULT __stdcall CAAEOmmFactory::AddNewVerticalLine(
CATIAReference * ipiReferenceOnPoint1,
CATIAReference * ipiReferenceOnPoint2,
CAAIAOmmVerticalLine *& opiVerticalLineOnLine)
           HRESULT rc = E_FAIL;
           opiVerticalLineOnLine=NULL;

           //-------------------------------------------------------------------------------
           // -1- Getting a pointer on CATIContainer
           //-------------------------------------------------------------------------------
           **CATIPartRequest** *piPartOnThis = NULL;
           rc = QueryInterface( IID_CATIPartRequest, ( void**) &piPartOnThis );
           ...
rc = QueryInterface( IID_CATIPartRequest, ( void**) &piPartOnThis );
           CATBaseUnknown_var spBUOnMainTool ;
```vbscript
           rc = piPartOnThis->**GetMainBody**("",spBUOnMainTool);

```

           ...
rc = QueryInterface( IID_CATIPartRequest, ( void**) &piPartOnThis );
CATBaseUnknown_var spBUOnMainTool ;
rc = piPartOnThis->**GetMainBody**("",spBUOnMainTool);
           CATISpecObject_var spSpecOnMainTool = spBUOnMainTool ;
           CATIContainer_var spiContainer ( spSpecOnMainTool->**GetFeatContainer**(#));

           ...

---
The goal of this first step is to access the container in which we will create instances of our features.
     * We first get a _CATIPartRequest_ interface on ourselves.
     * The _CATIPartRequest_ interface gives access to the part's main body through `GetMainBody`
     * From the main body, `GetFeatContainer` gives access to the document internal container in which its features are contained.

    ...

      //-------------------------------------------------------------------------------
      // -2- Creating an instance of the CAAOmmVerticalLine startup
      //-------------------------------------------------------------------------------

      CATUnicodeString StartupType = "CAAOmmVerticalLine";
      CATUnicodeString ClientId = "CAA_OLE4MecMod";
      CATUnicodeString StorageName = "CAAOmmCatalog.CATfct";
      CATOsmSUHandler OmmSUHandler(StartupType, ClientId, StorageName);
      CATISpecObject_var spSpecOnInstance = NULL_var;

```vbscript
      rc = OmmSUHandler.Instanciate(spSpecOnInstance, piContainerOnThis);

```

      if( FAILED(rc) )
        return E_FAIL;

      //-------------------------------------------------------------------------------
      // -5- Setting default values for the attributes of the instance
      //-------------------------------------------------------------------------------
      rc = spSpecOnInstance->QueryInterface( IID_CAAIAOmmVerticalLine,
```vbscript
rc = spSpecOnInstance->QueryInterface( IID_CAAIAOmmVerticalLine,
```

                                             (void**) &opiVerticalLineOnLine );

      if( FAILED(rc) )
       return E_FAIL;

      rc = opiVerticalLineOnLine->put_Point1( ipiReferenceOnPoint1 );
```vbscript
```vbscript
      rc = opiVerticalLineOnLine->put_Point2( ipiReferenceOnPoint2 );

```

```

      return rc;

    }

---
The reference to points received in arguments are set onto the instance thanks to the put_Point1(#) and put_Point2(#) method, for which the next section details the implementation.
  5. Now that the CAAIAOmmFactory is implemented, the next step is to implement the CAAIAOmmVerticalLine interface itself. The first section of this implementation consists in providing code for the standard get_Name(#) and get_Parent(#) methods:

         ...
         #include "TIE_CAAIAOmmVerticalLine.h"
The reference to points received in arguments are set onto the instance thanks to the put_Point1(#) and put_Point2(#) method, for which the next section details the implementation.
5. Now that the CAAIAOmmFactory is implemented, the next step is to implement the CAAIAOmmVerticalLine interface itself. The first section of this implementation consists in providing code for the standard get_Name(#) and get_Parent(#) methods:
         TIE_CAAIAOmmVerticalLine( CAAEOmmVerticalLine);

         CATImplementClass( CAAEOmmVerticalLine,
                            DataExtension,
                            CATBaseUnknown,
                            CAAOmmVerticalLine );

         HRESULT CAAEOmmVerticalLine::get_Name(CATBSTR & oName)

         {
CATBaseUnknown,
CAAOmmVerticalLine );
HRESULT CAAEOmmVerticalLine::get_Name(CATBSTR & oName)
           HRESULT rc = E_FAIL;
           CATIAlias* ipAliasOnThis = NULL;

           rc=QueryInterface(IID_**CATIAlias** , (void**) &ipAliasOnThis);
```vbscript
           if (SUCCEEDED(rc)) {
```

             CATUnicodeString str = ipAliasOnThis->**GetAlias**(#);
             ipAliasOnThis->Release(#);
             str.ConvertToBSTR (&oName);

           }
```cpp
if (SUCCEEDED(rc)) {
CATUnicodeString str = ipAliasOnThis->**GetAlias**(#);
ipAliasOnThis->Release(#);
str.ConvertToBSTR (&oName);
           return rc;
```

         }

str.ConvertToBSTR (&oName);
return rc;
         HRESULT __stdcall CAAEOmmVerticalLine::get_Parent(CATBaseDispatch *& opiBaseOnOLEParent)

         {
return rc;
HRESULT __stdcall CAAEOmmVerticalLine::get_Parent(CATBaseDispatch *& opiBaseOnOLEParent)
            HRESULT rc=E_FAIL;
            opiBaseOnOLEParent=NULL;

            **CATISpecObject** * ipSpecObjectOnThis = NULL;
HRESULT rc=E_FAIL;
opiBaseOnOLEParent=NULL;
            rc=QueryInterface(IID_CATISpecObject, (void**) &ipSpecObjectOnThis);
```vbscript
            if (SUCCEEDED(rc)) {
```

               CATISpecObject * pParent = ipSpecObjectOnThis->**GetFather**(#);
               ipSpecObjectOnThis->Release(#);
               ipSpecObjectOnThis = NULL ;

```vbscript
               while ((NULL != pParent) && (NULL == opiBaseOnOLEParent))

```

               {
ipSpecObjectOnThis->Release(#);
ipSpecObjectOnThis = NULL ;
while ((NULL != pParent) && (NULL == opiBaseOnOLEParent))
                  CATISpecObject * pParentCurrent = pParent ;
```cpp
                  rc =  pParentCurrent->QueryInterface(IID_**CATIAHybridShapes** , (void**) &opiBaseOnOLEParent);

                  pParent =  pParentCurrent -> GetFather(#);

```

                  pParentCurrent->Release(#);
                  pParentCurrent = NULL ;

               }
            }
pParentCurrent->Release(#);
pParentCurrent = NULL ;
            return rc;

         }
         ...

---
return rc;
The name of the object is retrieved in a standard way by querying it for the support of CATIAlias, the standard naming interface, and using its GetAlias(#) method for retrieving the actual name. The get_Parent(#) method is implemented by using the parent-child relationship contained in the feature modeler. As any feature, our Vertical Line implements the _CATISpecObject_ interface. This interface provides the GetFather(#) method that returns the mechanical feature aggregating for _this._ However, this direct parent may not be a suitable parent for the automation world. Remember, the automation world presents a data model that is often simpler than the actual underlying data modeler. In this case, what aggregates the Vertical Line in the automation view that we want to provide is a collection of Hybrid Shapes. In the underlying model, the object that correspond to this collection may exist not only as a direct parent to the Vertical Line, but also as its ancestor up the parent-chidren tree. This is why we iterate from parent to grand parent, etc., in the last section of this code, until an object implementing CATIAHybridShapes is finally found, and we return it as the father for our Vertical Line.
  6. The next methods to implements are the methods for getting and putting the points that are the input specs for our line. Here is the code for put_Point1(#), the three others being very similar:

         ...
The name of the object is retrieved in a standard way by querying it for the support of CATIAlias, the standard naming interface, and using its GetAlias(#) method for retrieving the actual name. The get_Parent(#) method is implemented by using the parent-child relationship contained in the feature modeler. As any feature, our Vertical Line implements the _CATISpecObject_ interface. This interface provides the GetFather(#) method that returns the mechanical feature aggregating for _this._ However, this direct parent may not be a suitable parent for the automation world. Remember, the automation world presents a data model that is often simpler than the actual underlying data modeler. In this case, what aggregates the Vertical Line in the automation view that we want to provide is a collection of Hybrid Shapes. In the underlying model, the object that correspond to this collection may exist not only as a direct parent to the Vertical Line, but also as its ancestor up the parent-chidren tree. This is why we iterate from parent to grand parent, etc., in the last section of this code, until an object implementing CATIAHybridShapes is finally found, and we return it as the father for our Vertical Line.
6. The next methods to implements are the methods for getting and putting the points that are the input specs for our line. Here is the code for put_Point1(#), the three others being very similar:
         HRESULT __stdcall CAAEOmmVerticalLine::put_Point1(CATIAReference * ipiReferenceOnPoint1)

         {
6. The next methods to implements are the methods for getting and putting the points that are the input specs for our line. Here is the code for put_Point1(#), the three others being very similar:
HRESULT __stdcall CAAEOmmVerticalLine::put_Point1(CATIAReference * ipiReferenceOnPoint1)
            HRESULT rc=E_FAIL;

            **CATISpecAttrAccess** * piSpecAttrAccessOnThis=NULL;
HRESULT __stdcall CAAEOmmVerticalLine::put_Point1(CATIAReference * ipiReferenceOnPoint1)
HRESULT rc=E_FAIL;
```cpp
            rc=QueryInterface(IID_CATISpecAttrAccess, (void**) &piSpecAttrAccessOnThis);

```

            ...

            **CATISpecAttrKey** * piAttrKeyOnSpec = piSpecAttrAccessOnThis->**GetAttrKey**("Point1");
            ...

            CATISpecObject_var spSpecOnPoint1;
            rc = ::**GetSpecFromReference** (ipiReferenceOnPoint1, spSpecOnPoint1);
            ...

CATISpecObject_var spSpecOnPoint1;
rc = ::**GetSpecFromReference** (ipiReferenceOnPoint1, spSpecOnPoint1);
            piSpecAttrAccessOnThis->**SetSpecObject**(piAttrKeyOnSpec,spSpecOnPoint1);

            ...
rc = ::**GetSpecFromReference** (ipiReferenceOnPoint1, spSpecOnPoint1);
piSpecAttrAccessOnThis->**SetSpecObject**(piAttrKeyOnSpec,spSpecOnPoint1);
            return rc;

         }

---
We begin by retrieving a pointer of _CATISpecAttrAccess_ , on _this,_ ie the Vertical Line. Then we use it to access the "Point1" attribute.  In this method we get the input point ipiReferenceOnPoint1 not as a feature, but as a CATIAReference. CATIAReferences are used because they provide a stable handle onto objects that are manipulated within scripts, whether those objects represent actual underlying model objects or only part of them. So we convert the reference into a real Feature through a call to `GetSpecFromReference`(#), which manages the link from a reference to its referent. The last step consists in assigning the feature we got from GetSpecFromReference(#) as attribute to the vertical line.

[Top]

* * *

In Short This article explains what has to be done in order to integrate a new feature added to a CATIA application to the automation exposed view for that application. As a result, the new feature can be manipulated as the native features from within scripting environments such as Visual Basic. The first step is to 'plug' the new feature and its associated factory as new automation interfaces in the application automation model. From there, where those new behaviors should be implemented in the underlying, actual application model can be deduced. Then, automation interfaces for the new feature and its factory are written using the IDL language, and appropriate dictionary declaration is produced. Some more additional IDL code gathers those new IDL objects definitions within a source code TypeLib, which is compiled into an executable TypeLib that will be used by scripting languages for knowing about those new types at run time. The last part consists in implementing the new IDL interfaces in the underlying model. In addition to the methods defined in the interfaces themselves, the implementations must provide code for methods get_Name(#) and get_Parent(#), that all automation objects must implement. Thanks to get_Parent(#), the exposed automation model can appear as having a parent-child structure which is somehow different (and most often, simpler) than the one existing in the underlying model. [Top]

* * *

References [1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [ Creating Interfaces for Automation](../CAASysTechArticles/CAASysAutomationItf.md)
[3] |  [ Implementing Interfaces for Automation](../CAASysTechArticles/CAASysAutomationImpl.md)
[4] |  [ The CAA V5 IDL Compiler](../CAASysTechArticles/CAASysIDLCompiler.md)
[Top]

* * *

History Version: **1** [Mar 2000] | Document created
---|---
Version: **2** [Dec 2003] | StartUp creation modification
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
