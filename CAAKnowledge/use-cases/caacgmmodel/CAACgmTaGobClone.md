---
```vbscript
title: "The Clone and Transformation Managers"
category: "use-case"
module: "CAACgmModel"
tags: ["CATIA", "CATICGMObjects", "CATICGMObject"]
source_file: "Doc/online/CAACgmModel/CAACgmTaGobClone.htm"
converted: "2026-05-11T17:33:47.903606"
```

---
# The Clone and Transformation Managers  

---  
Technical Article  
## Abstract

The copy and paste of geometric objects that takes into account their forward linked objects, is called cloning. This process is supported by the CATCloneManager class. Moreover, the geometric objects can also be moved, with or without copy, through a specific process handled by the CATTransfoManager class. Why these classes are needed, how they are used and how a geometric object and a manager cooperate are the main topics of this paper. 
    * Operators to Copy or Move Objects
    * The CATCloneManager
      * Two Modes of Cloning
      * A Code Sample
      * How a CATICGMObject and a CATCloneManager Cooperate
    * The CATTransfoManager
      * Inherited Properties
      * New Properties
    * In Short
    * References  
---  
## Operators to Copy or Move Objects

CATCloneManager is a class representing an operator that manages the copy and paste of a set of objects implementing the CATICGMObject interface, that is to say the persistent objects provided by the CGM offering. This operation, that also takes into account the forward linked object, is called a **cloning** , and is especially useful to design your own cut, copy, paste applications.

CATCloneManager is a class representing an operator that manages the copy and paste of a set of objects implementing the CATICGMObject interface, that is to say the persistent objects provided by the CGM offering. This operation, that also takes into account the forward linked object, is called a **cloning** , and is especially useful to design your own cut, copy, paste applications.
Why is there a specific class for this process, instead of a method in each class of each geometric object? This could be the easiest way to do when the objects to clone are isolated, that is, have no links with other objects. But take now two curves C1 and C2 laying on the same surface. You want to globally copy the set of the three objects C1, C2 and the underlying surface. If the copy process was at the geometric object level, the surface would be twice copied, and the resulting objects would not represent an exact image of the global initial set.

To prevent from this kind of configuration, the cloning process has a global knowledge of the objects to clone. Therefore, the role of the **CATCloneManager** is to federate the way to copy and paste objects and their forward linked objects. In particular, the manager clones a list of selected objects, without unnecessarily duplicating the forward common linked objects.

The same frame occurs for the transformation of geometric objects implementing the CATGeometry interface. For these objects that have a geometric meaning, the geometric transformation process follows the same way than the clone process. Hence, an object implementing the CATGeometry interface, which is a kind of CATICGMObject interface, will be geometrically transformed, with or without duplication, by the mean of a **CATTransfoManager** instance, which is a kind of CATCloneManager instance.

Fig1: Inheritance Between CATCloneManager and CATTransfoManager ![Inheritance between CATCloneManager and CATTransfoManager](images/CAACgmGobClone1.gif)  

---  
## The CATCloneManager

Fig1: Inheritance Between CATCloneManager and CATTransfoManager ![Inheritance between CATCloneManager and CATTransfoManager](images/CAACgmGobClone1.gif)
The programmer gives to the CATCloneManager the objects to be cloned together, by calling the `CATCloneManager::Add` method. All the objects must belong to the same container (a container is an object containing other objects) to be processed in a single operation.

The copy and paste is not made at the creation of the clone process, or when objects are added to the list to copy, but triggered by the `CATCloneManager:Run` method.

After the run, you can retrieve the cloned object corresponding to each object of the input list.

If there are topological objects to clone (topological objects are kind of geometric objects), the CATCloneManager creates, under request, the topological journal associated with the cloning operation.

The CATCloneManager instances are transient, and therefore cannot be streamed.

### Two Modes of Cloning

```vbscript
If there are topological objects to clone (topological objects are kind of geometric objects), the CATCloneManager creates, under request, the topological journal associated with the cloning operation.
The CATCloneManager instances are transient, and therefore cannot be streamed.
The cloning process can be done as a single copy or a full copy. This mode is ruled by the **CATCloneManagerType:**

```

`CatCGMSingleDuplicate`
The cloning process can be done as a single copy or a full copy. This mode is ruled by the **CATCloneManagerType:**
    Only copies and pastes the objects that are `Add`ed to the CATCloneManager. This is only available if the objects are copied from and pasted in the same container.

`CatCGMFullDuplicate`
The cloning process can be done as a single copy or a full copy. This mode is ruled by the **CATCloneManagerType:**
Only copies and pastes the objects that are `Add`ed to the CATCloneManager. This is only available if the objects are copied from and pasted in the same container.
    Copies and pastes the objects that are `Add`ed to the CATCloneManager and their forward linked objects.
Fig2: Behavior of the Duplication According to the CATCloneManagerType ![Behavior of the duplication according to the CATCloneManagerType](images/CAACgmGobClone2.gif) | These diagrams show the behavior of the CATCloneManager for each mode: C1 and C2 are two curves laying on the same Surface. Then, C1 and C2 have Surface as forward linked object. When C2 is selected in SingleDuplicate, its copy C2_c lays on Surface. In FullDuplicate, Surface is also duplicated in Surface_c When C1 and C2 are selected in SingleDuplicate, their copies C1_c and C2_c respectively lay on Surface. In FullDuplicate, their copies lay on Surface_c, the copy of Surface, that has been duplicated _only once_.  

### A Code Sample

Copies and pastes the objects that are `Add`ed to the CATCloneManager and their forward linked objects.
Fig2: Behavior of the Duplication According to the CATCloneManagerType ![Behavior of the duplication according to the CATCloneManagerType](images/CAACgmGobClone2.gif) | These diagrams show the behavior of the CATCloneManager for each mode: C1 and C2 are two curves laying on the same Surface. Then, C1 and C2 have Surface as forward linked object. When C2 is selected in SingleDuplicate, its copy C2_c lays on Surface. In FullDuplicate, Surface is also duplicated in Surface_c When C1 and C2 are selected in SingleDuplicate, their copies C1_c and C2_c respectively lay on Surface. In FullDuplicate, their copies lay on Surface_c, the copy of Surface, that has been duplicated _only once_.
The following example illustrates how to copy the two curves C1 and C1 of the previous section and paste them into an other container. The result will be two new curves laying on the same new surface, with the same characteristics as the initial one.

    CATCloneManager MyManager(GeoFactoryForPasting); // the CATGeoFactory is also a container
    MyManager.Add(C1);   
    MyManager.Add(C2);

    // Copies C1 and C2 and paste them in GeoFactoryForPasting
CATCloneManager MyManager(GeoFactoryForPasting); // the CATGeoFactory is also a container
MyManager.Add(C1);
MyManager.Add(C2);
    MyManager.Run();  

    // Retrieves the copy of C1  
MyManager.Add(C1);
MyManager.Add(C2);
MyManager.Run();
    CATICGMObject* ClonedObject=MyManager.ReadImage(C1);

### How a CATICGMObject and a CATCloneManager Cooperate

MyManager.Run();
CATICGMObject* ClonedObject=MyManager.ReadImage(C1);
The CATCloneManager globally manages the cloning, but delegates the copy of a single object to each object. 

    1. The CATCloneManager asks the object to clone itself through the `CATICGMObject::Clone` method.
    2. The object to clone asks back the CATCloneManager for the copy of its forward linked objects through the `CATCloneManager::ComputeImage` method. 

       * If the copy of the forward linked object has already been created during the cloning process, it is directly returned
       * Otherwise, the process re-runs at the step 1 for the linked object.

1. The CATCloneManager asks the object to clone itself through the `CATICGMObject::Clone` method.
2. The object to clone asks back the CATCloneManager for the copy of its forward linked objects through the `CATCloneManager::ComputeImage` method.
Hence, there are two types of methods of a CATCloneManager:

    * "user methods", that you call to clone CATICGMObjects, as in the code sample : 

`Add`
Hence, there are two types of methods of a CATCloneManager:
    Adds objects of the same container to the set of objects to clone.

`Run`
Adds objects of the same container to the set of objects to clone.
    Triggers the cloning process.

`ReadImage`
Adds objects of the same container to the set of objects to clone.
Triggers the cloning process.
    Retrieves a pasted object.

`WriteReport`
Triggers the cloning process.
Retrieves a pasted object.
    Writes topological items in the journal.

`GetFactory`
Retrieves a pasted object.
Writes topological items in the journal.
    Retrieves the factory of the pasted objects.

    * "object methods", to use for writing the `Clone` method of a new class of CATICGMObject . These methods are not seen by the CAA programmer. 

`ComputeImage`
    Called inside the code of a CATICGMObject.
## The CATTransfoManager

This operator is a kind of CATCloneManager, that moves CATGeometry objects, with or without copying them. This part highlights the new properties and behaviors with respect to those inherited from CATCloneManager.
### Inherited Properties

The global architecture is of course inherited. It includes: 

    * The cooperation between the manager ant the objects it manages.
    * The behavior of "users" and "objects" methods that have already been described.
    * The fact that it cannot be streamed.
### New Properties

    * The first new property is obviously the transformation. The CATTransfoManager takes two types of transformations: 
      * Linear transformations, instances of CATMathTransformation, representing a simple displacement of the object. These linear transformations must be invertible.
      * Non linear transformations, instances of CATMathNonLinearTransformation, which definition depends on the point where the transformation is done. This is useful for describing deformations such as sheet metal folding and unfolding.
    * Now, the CatCGMSingleDuplicate/FullDuplicate mode has no more meaning for transformations. It is replaced by the **CATTransfoManagerType** , defined as follows: 

`CATTransfoManager::Replace`
    `T`ransforms the objects that are `Add`ed to the CATransfoManager and their forward linked objects that are not geometrically invariant. In some cases, a copy occurs, when a pointing object is not in the selection. Do not use this mode for the transformation of topological objects, because of the smart mechanism. For your reminder, a topological object is a kind of geometric object with logical boundaries and the smart mechanism is the fact that topological objects to modify have first to be duplicated.
`CATTransfoManager::Duplicate`
    Copies, transforms and pastes objects that are `Add`ed to the CATransfoManager and their forward linked objects that are not geometrically invariant, without unnecessarily duplicating common forward linked objects. In particular, a CATTransfoManager with this option and the identity transformation gives the same result as a CATCloneManager with `CatCGMSingleDuplicate` mode.
`CATTransfoManager::FullDuplicate`
Copies, transforms and pastes objects that are `Add`ed to the CATransfoManager and their forward linked objects that are not geometrically invariant, without unnecessarily duplicating common forward linked objects. In particular, a CATTransfoManager with this option and the identity transformation gives the same result as a CATCloneManager with `CatCGMSingleDuplicate` mode.
    Duplicates and transforms the objects that are `Add`ed to the CATTransfoManager. Duplicates a forward linked object even if it is geometrically invariant by the transformation.

The rules for the duplication of the forward linked objects in the same container are as follows: 

    * If a forward linked object is geometrically **invariant** by the transformation, this object is not duplicated, except if this forward linked object is specifically `Add`ed to the CATTransfoManager. Invariant means that the transformation does not change the object with regards to its maximum limits: for example, a line is invariant by a transformation along its direction, a circle is invariant by a rotation around an axis perpendicular to its plane and passing by its center.
    * Any forward linked object that is not geometrically invariant is copied or replaced.

The rules for the duplication of the forward linked objects in the same container are as follows:
The following figures illustrate the behavior of the CATTransfoManager in different cases:

Fig3: Behavior of the CATTransfoManager when a Forward Linked Object Belongs to the Selection, According to the CATTransfoManagerType ![CATTransfoManager Behavior](images/CAACgmGobClone3.gif) | In these diagrams, a forward linked object (Surface) belongs to the selection. If an object that points to Surface is not in the selection (as C1), Surface is duplicated and moved in Surface_d. In replace mode, the other selected objects C2 and C3 point now to this new surface Surface_d. If all the objects pointing to Surface are selected : * In replace mode, Surface is moved: the relative position between the curves and Surface remains the same, and C1, C2, C3 are not touched. Note that in some rare cases, the curves will also be moved, because the parameterization of the transformed surface can change from the initial one. This is the case when the surface is defined from a curve or another surface, themselves invariant by the transformation. * In duplicate mode, all is duplicated. Notice that the duplicated surface only needs to be moved.  

The following figures illustrate the behavior of the CATTransfoManager in different cases:
Fig3: Behavior of the CATTransfoManager when a Forward Linked Object Belongs to the Selection, According to the CATTransfoManagerType ![CATTransfoManager Behavior](images/CAACgmGobClone3.gif) | In these diagrams, a forward linked object (Surface) belongs to the selection. If an object that points to Surface is not in the selection (as C1), Surface is duplicated and moved in Surface_d. In replace mode, the other selected objects C2 and C3 point now to this new surface Surface_d. If all the objects pointing to Surface are selected : * In replace mode, Surface is moved: the relative position between the curves and Surface remains the same, and C1, C2, C3 are not touched. Note that in some rare cases, the curves will also be moved, because the parameterization of the transformed surface can change from the initial one. This is the case when the surface is defined from a curve or another surface, themselves invariant by the transformation. * In duplicate mode, all is duplicated. Notice that the duplicated surface only needs to be moved.
Fig4: Behavior of the CATTransfoManager when a Forward Linked Object Does not Belong to the Selection, nor a Pointing Object ![CATTransfoManager Behavior](images/CAACgmGobClone4.gif) | In these diagrams, a forward linked object Surface does not belong to the selection, nor the pointing curve C1. In replace mode, if Surface is invariant, there is no need to duplicate it. C2 and C3 are only moved. If Surface is not invariant, it must be duplicated before the transformation In duplicate mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are duplicated and moved, pointing to the same Surface. If Surface is not invariant, all is duplicated.  

Fig3: Behavior of the CATTransfoManager when a Forward Linked Object Belongs to the Selection, According to the CATTransfoManagerType ![CATTransfoManager Behavior](images/CAACgmGobClone3.gif) | In these diagrams, a forward linked object (Surface) belongs to the selection. If an object that points to Surface is not in the selection (as C1), Surface is duplicated and moved in Surface_d. In replace mode, the other selected objects C2 and C3 point now to this new surface Surface_d. If all the objects pointing to Surface are selected : * In replace mode, Surface is moved: the relative position between the curves and Surface remains the same, and C1, C2, C3 are not touched. Note that in some rare cases, the curves will also be moved, because the parameterization of the transformed surface can change from the initial one. This is the case when the surface is defined from a curve or another surface, themselves invariant by the transformation. * In duplicate mode, all is duplicated. Notice that the duplicated surface only needs to be moved.
Fig4: Behavior of the CATTransfoManager when a Forward Linked Object Does not Belong to the Selection, nor a Pointing Object ![CATTransfoManager Behavior](images/CAACgmGobClone4.gif) | In these diagrams, a forward linked object Surface does not belong to the selection, nor the pointing curve C1. In replace mode, if Surface is invariant, there is no need to duplicate it. C2 and C3 are only moved. If Surface is not invariant, it must be duplicated before the transformation In duplicate mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are duplicated and moved, pointing to the same Surface. If Surface is not invariant, all is duplicated.
Fig5: Behavior of the CATTransfoManager when All the Pointing Objects Are in the Selection, but not the Forward Linked Object ![CATTransfoManager Behavior](images/CAACgmGobClone5.gif) | In these diagrams, the forward linked object Surface does not belong to the selection, but all the pointing curves C1 and C2 are selected. In replace mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are only moved. If Surface is not invariant, it is moved, and the C1 and C2 are not touched. In duplicate mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are duplicated and moved, pointing to the same Surface. If Surface is not invariant, all is duplicated.  

Fig4: Behavior of the CATTransfoManager when a Forward Linked Object Does not Belong to the Selection, nor a Pointing Object ![CATTransfoManager Behavior](images/CAACgmGobClone4.gif) | In these diagrams, a forward linked object Surface does not belong to the selection, nor the pointing curve C1. In replace mode, if Surface is invariant, there is no need to duplicate it. C2 and C3 are only moved. If Surface is not invariant, it must be duplicated before the transformation In duplicate mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are duplicated and moved, pointing to the same Surface. If Surface is not invariant, all is duplicated.
Fig5: Behavior of the CATTransfoManager when All the Pointing Objects Are in the Selection, but not the Forward Linked Object ![CATTransfoManager Behavior](images/CAACgmGobClone5.gif) | In these diagrams, the forward linked object Surface does not belong to the selection, but all the pointing curves C1 and C2 are selected. In replace mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are only moved. If Surface is not invariant, it is moved, and the C1 and C2 are not touched. In duplicate mode, if Surface is invariant, there is no need to duplicate it. C1 and C2 are duplicated and moved, pointing to the same Surface. If Surface is not invariant, all is duplicated.
The specific methods of a CATTransfoManager are 

    * "User methods", that you call to transform CATGeometry objects: 

`GetMathTransformation`
The specific methods of a CATTransfoManager are
    Retrieves the transformation.

`GetMathNonLinearTransformation`
Retrieves the transformation.
    Retrieves the non linear transformation.

`RetrieveTransfoW`
Retrieves the transformation.
Retrieves the non linear transformation.
    Retrieves the 1D transformation to apply to an object that lays to another object that is geometrically invariant along one direction.

    * "Object methods", to use for writing the `Move3D` and `CloneAndMove3D` methods of a new class of CATGeometry you want to create: `Compute, ComputeW, ComputeUV, SetTransfoW, SetTransfoUV, IsIdentity`, `IsSimilitide, GetOrientationChange`, `IsInvariant` that are called inside the code of a CATGeometry. These methods are not seen by the CAA programmer.
## In Short

    * The CATCloneManager is an operator that copies and pastes a set of CATICGMObject, and their forward linked objects if needed.
    * The CATTransfoManager is a kind of CATCloneManager that also moves set of CATGeometry objects.
    * These operators cooperate with the objects for more efficiency.
## References

[1] | [The Objects of CATIA Geometric Modeler](CAACgmTaGobGeoObjects.md)  
---|---  
[2] | [The Management of Foreign Data](CAACgmTaGobAttribute.md)  
[3] | [The Curves of CATIA Geometric Modeler](CAACgmTaGobCurves.md)  
[4] | [The Surfaces of CATIA Geometric Modeler](CAACgmTaGobSurfaces.md)  
## History

Version: **1** [Mar 2000] | Document created  
---|---
