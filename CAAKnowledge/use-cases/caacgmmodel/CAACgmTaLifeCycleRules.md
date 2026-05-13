---
```vbscript
title: "Object Life Cycle: Rules"
category: use-case
module: "CAACgmModel"
tags: ["CATICGMContainer", "CATICGMTopWire"]
source_file: "Doc/online/CAACgmModel/CAACgmTaLifeCycleRules.htmmd"
converted: "2026-05-11T17:33:47.987993"
```

---
# Object Life Cycle: Rules

---
Technical Article
## Abstract

Object life cycle of CGM objects is managed through the implicit/explicit status assigned to objects. Here are the rules to comply with for a correct management of object life cycle.
    * Creating and Removing Objects
    * How to Create the Geometry Factory
    * Implicit and Explicit Objects
    * Recommendations to Avoid Memory Leaks

---
## Creating and Removing Objects

CGM objects can be created:

CGM objects can be created:
    1. Either by the geometry factory

`CATPlane * piPlane = _theFactory_ ->CreatePlane(CATMathOIJ);`
CGM objects can be created:
1. Either by the geometry factory
    2. Or by operators

`CATICGMTopWire * pWireOp1 = CATCGMCreateTopWire(_theFactory_ , …);`

1. Either by the geometry factory
2. Or by operators
Objects which are no longer of any use must be removed with ` CATICGMContainer::Remove`. There are two options to remove an object:

    1. The KeepDependancies option:

`pfactory->Remove(Body1,CATICGMContainer::KeepDependancies);`
Objects which are no longer of any use must be removed with ` CATICGMContainer::Remove`. There are two options to remove an object:
1. The KeepDependancies option:
    2. The RemoveDependancies option:

`pfactory->Remove(Body1,CATICGMContainer::RemoveDependancies);`

1. The KeepDependancies option:
2. The RemoveDependancies option:
These options applies to the objects pointed to by the object to be removed. Refer to Implicit and Explicit Objects.

**Note** : The default mode of the `Remove` method is `CATICGMContainer::KeepDependancies`, due to legacy reasons. However, it is strongly recommended to use this method with `CATICGMContainer::RemoveDependancies` to enhance the memory management.
## How to Create the Geometry Factory

These options applies to the objects pointed to by the object to be removed. Refer to Implicit and Explicit Objects.
There are two factories:

    1. the explicit one which is dedicated to topology

`CATGeoFactory* theFactory = ::CATCreateCGMContainer(#) ;`
There are two factories:
1. the explicit one which is dedicated to topology
    2. and the implicit one which is dedicated to geometry.

`CATGeoFactory * piImplicitFactory = theFactory- >GetImplicitGeoFactory(#);`
## Implicit and Explicit Objects

The implicit/explicit status of an object is related to its life cycle. Any object created as implicit is removed when:

    * an object O pointing to it is removed with the RemoveDependancies option.
    * the object O is the only one pointing to it.

The implicit/explicit status of an object is related to its life cycle. Any object created as implicit is removed when:
The RemoveDependancies and KeepDependancies option are ineffective on explicit objects. In other words, no matter the Remove option, removing an object pointing to an explicit object does not remove the pointed to object. This explicit object has to be removed directly by the Remove method.

Fig.1 The Remove Options ![](images/CGM_life_cycle_0.png)

> Body 1 and CATSurface removed

Fig.1 The Remove Options ![](images/CGM_life_cycle_0.png)
 _Body1 (explicit or explicit) pointing to CATSurface(implicit)_ | _Body1 removed
 with KeepDependancies (CATSurface not removed)_ | _Body1 removed
 with RemoveDependancies_

 _Body1 and Body 2 (explicit or explicit) pointing to CATSurface(implicit)_ | _Body1 removed
 with KeepDependancies (CATSurface not removed)_ | _Body1 removed
 with RemoveDependancies (CATSurface not removed as it is pointed to by Body2)_

 _Body1 (explicit or explicit) pointing to CATSurface(explicit)_ | _Body1 removed
 with KeepDependancies (CATSurface not removed)_ | _Body1 removed
 with RemoveDependancies (CATSurface not removed_)

Notes:

    * Only the objects pointed to by generic naming are streamed on disk whether they are implicit or explicit.
    * Only explicit objects have their visualization computed.
## Recommendations to Avoid Memory Leaks

    1. Create all objects as implicit (not only the geometry)

    2. The resulting body to be kept as a final object in the container must be declared as explicit right after its creation (GetResult).
`Object->SetMode(CatCGMExplicit)`

1. Create all objects as implicit (not only the geometry)
2. The resulting body to be kept as a final object in the container must be declared as explicit right after its creation (GetResult).
    3. All superfluous objects, either explicit or implicit should be removed with the RemoveDependancies option `pFactory->Remove(Object,CATICGMContainer::RemoveDependancies`

    4.  Objects which are no longer needed by the application should be removed after the creation of the final body.

**WARNING:**
3. All superfluous objects, either explicit or implicit should be removed with the RemoveDependancies option `pFactory->Remove(Object,CATICGMContainer::RemoveDependancies`
4.  Objects which are no longer needed by the application should be removed after the creation of the final body.
Objects not referred to by generic naming and not managed properly can potentially inflate the virtual memory size.

## History

Version: **1** [Oct 2011] | Document created
---|---
