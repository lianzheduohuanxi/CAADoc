---
```vbscript
title: "Creating an Attribute"
category: use-case case"
module: "CAACgmModel"
tags: ["CAAGeometricObjects", "CAAGobAT", "CAADoc", "CATICGMObject", "CATICGMProjectionPtSur", "CAAGMModelGemBrowser", "CAAGMModelAttribute", "CAAGMModelInterfaces", "CAAGMModelAttributeCreation", "CAAGMModelAttributeManagement"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGobAttCreation.htmmd"
converted: "2026-05-11T17:33:48.342765"
```

---
# Creating an Attribute

---
Use Case
## Abstract

An attribute is a piece of information intended to be added to an object. Prior to adding an attribute to an object you must implement this attribute.
    * What You Will Learn With This Use Case
    * The CAAGMModelAttributeCreation Use Case
      * What Does CAAGMModelAttributeCreation Do
      * How to Launch CAAGMModelAttributeCreation
      * Where to Find the CAAGMModelAttributeCreation Code
    * Step-by-Step
    * In Short
    * References
---
## What You Will Learn With This Use Case

The use case creates an attribute an add it to objects. The attribute implementation is defined in the CAAGMModelAttribute.m module.
## The CAAGMModelAttributeCreation Use Case

CAAGMModelAttributeCreation is a use case of the CAAGMModelInterfaces.edu framework that illustrates GMModelInterfaces framework capabilities.
### What Does CAAGMModelAttributeCreation Do

This use case creates two PLines. An attribute is added to these geometries.
### How to Launch CAAGMModelAttributeCreation

This use case creates two PLines. An attribute is added to these geometries.
To launch CAAGMModelAttributeCreation, you will need to set up the build time environment, then compile CAAGMModelAttributeCreation.m and CAAGMModelAttribute.m along with their prerequisites, set up the run time environment, and then execute the use case [1].

```vbscript
If you simply type CAAGMModelAttributeCreation with no argument, the use case executes, but doesn't save the result in an NCGM file. If you want to save this result, provide the full pathname of the NCGM file to create. For example:

```

`CAAGMModelAttributeCreation /u/AttCreation.NCGM`

This NCGM file can be displayed using the CAAGMModelGemBrowser use case.
### Where to Find the CAAGMModelAttributeCreation Code

The CAAGMModelAttributeCreation use case is made of a main named CAAGMModelAttributeCreation.cpp located in the CAAGMModelAttributeCreation.m module of the CAAGMModelInterfaces.edu framework:

`InstallRootFolder/CAADoc/CAAGMModelInterfaces.edu/CAAGMModelAttributeCreation.m/`

The CAAGMModelAttributeCreation use case is made of a main named CAAGMModelAttributeCreation.cpp located in the CAAGMModelAttributeCreation.m module of the CAAGMModelInterfaces.edu framework:
where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.

The use case uses a class defined in the CAAGMModelAttribute.m module.

## Step-by-Step

where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.
The use case uses a class defined in the CAAGMModelAttribute.m module.
The main program peforms the following steps:

    * Creating the Geometry Factory
    * Creating the CATPLines
    * Retrieving the Attribute Identifier
    * Creating the Attribute
    * Managing the Attributes
    * Managing the References
    * Writing the Model and Closing the Container
### Creating the Geometry Factory

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.

The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). This creation is done by the global function `::CATCreateCGMContainer`. Notice that the factory can be defined by reading a NCGM file that was previously stored. In that case, the global function `::CATLoadCGMContainer` must be used.
    CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
```vbscript
    if (NULL==piGeomFactory) return (1);

```

### Creating the CATPLines

CATGeoFactory* piGeomFactory = **::CATCreateCGMContainer**(#) ;
if (NULL==piGeomFactory) return (1);
A CATPLine is a line in the space of a surface, whatever the surface is. To create a CATPLine, one must specifies the starting and end points: these points are expressed in terms of parameters on the surface. No assumption must be made on the parameterization of the surface. The ways to define a CATSurParameter are:

    * Projecting a 3D point on the surface with the geometric operator CATICGMProjectionPtSur.
    * Using the `CATSurface::GetParam` method (only for canonical surfaces and a point that is known to be on the surface).
    * Using the barycentric constructor, after retrieving the limits (`CATSurface::GetLimits`) of the surface: this way is illustrated below.

Now, the CATPLines can be created by using the `CATGeoFactory::CreatePLine` method.

    // (c) --- Create a first PLine on piGeoPlane (geometric plane
    //
Now, the CATPLines can be created by using the `CATGeoFactory::CreatePLine` method.
    	CATPLine * piPline1 = NULL;

    	{
CATPLine * piPline1 = NULL;
    		CATSurParam iStartParam1 ( 0,0 , piGeoPlane->GetParamReference(#) ) ;
    		CATSurParam iEndParam1   ( 0,80, piGeoPlane->GetParamReference(#) ) ;
    		piPline1 = piGeomFactory->CreatePLine(iStartParam1,iEndParam1,piGeoPlane);
```vbscript
```vbscript
    		if (NULL==piPline1 )

```

```

    		{
    			::CATCloseCGMContainer(piGeomFactory);
CATSurParam iEndParam1   ( 0,80, piGeoPlane->GetParamReference(#) ) ;
piPline1 = piGeomFactory->CreatePLine(iStartParam1,iEndParam1,piGeoPlane);
```vbscript
if (NULL==piPline1 )
    			return (1);

```

    		}
    	}
### Retrieving the Attribute Identifier

return (1);
This operation is done by the CATCGMAttrId::FindAttrId static method which takes as its arguments the attribute name and the logical name of the load module containing the attribute implementation.

Go to the CAAGMModelAttribute.m module and take a look at the CAAGMModelAttributeManagement.cpp file which implements the CAAGMModelAttributeManagement attribute type. The attribute name is the first argument of the CATCGMImplAttribute macro (i.e. CAAGMModelAttributeManagement) while the CAAGobAT is a string allowing the system to access the load module which contains your implementation.

    CATCGMImplAttribute(CAAGMModelAttributeManagement, CATCGMStreamAttribute, CAAGobAT, 1);

Important:

You must declare the domain name (CAAGobAT) both in the dictionary (CAAGeometricObjects.edu.dico) and in the AppDef macro. In the present use case, the AppDef declaration is located in a separate file but you could gather all declarations into CAAGMModelAttributeManagement.cpp. If you need implement several attribute types, you can choose to gather all declarations in the same file as well and use a single AppDef declaration.

    // (a) --- Find the attribute identifier
    //
You must declare the domain name (CAAGobAT) both in the dictionary (CAAGeometricObjects.edu.dico) and in the AppDef macro. In the present use case, the AppDef declaration is located in a separate file but you could gather all declarations into CAAGMModelAttributeManagement.cpp. If you need implement several attribute types, you can choose to gather all declarations in the same file as well and use a single AppDef declaration.
    const char*  iAttr = "CAAGMModelAttributeManagement";
    const char*  iDomainName = "CAAGobAT";
    const CATCGMAttrId* pAttrId = CATCGMAttrId::FindAttrId(iAttr,iDomainName) ;

### Creating the Attribute

const char*  iAttr = "CAAGMModelAttributeManagement";
const char*  iDomainName = "CAAGobAT";
const CATCGMAttrId* pAttrId = CATCGMAttrId::FindAttrId(iAttr,iDomainName) ;
This operation can be done in two ways:

    * Either by using the UAIDPtr macro.
    * Or by using the CreateAttribute static method.

    CAAGMModelAttributeManagement * piAttr1
     =(CAAGMModelAttributeManagement *) CATCGMAttribute::CreateAttribute(pAttrId);
### Managing the Attribute

The attribute is assigned a value. The SetValue method is defined in the attribute implementation. Then the attribute is added to each PLines.

```vbscript
    // (c) --- Set its value to 2
    //         The SetValue method is defined in the CAAGMModelAttribute.m module
```
    //
    piAttr1->SetValue(2);

    // (d) --- Add it to the piPline1 and piPline2 CATPlines
    //
piAttr1->SetValue(2);
    piPline1->PutAttribute(piAttr1);
    piPline2->PutAttribute(piAttr1);

### Managing the References

piPline1->PutAttribute(piAttr1);
piPline2->PutAttribute(piAttr1);
You can cut the reference to an object by using the ReleaseAttribute method applied to the geometry you want to remove the attribute from. In the extract below, at first the number of objects pointed to by the attribute is 2. We check the new number of references after one reference has been cut.

    // (e) --- Retrieve the number of references
    //
You can cut the reference to an object by using the ReleaseAttribute method applied to the geometry you want to remove the attribute from. In the extract below, at first the number of objects pointed to by the attribute is 2. We check the new number of references after one reference has been cut.
    cout << "Number of objects pointed to by the attribute: (2 expected)";
    cout << piAttr1->GetNbAttrRef(#) << endl;

    // (f) --- Release the link between the attribute and piPline2
    //
cout << "Number of objects pointed to by the attribute: (2 expected)";
cout << piAttr1->GetNbAttrRef(#) << endl;
    piPline2->ReleaseAttribute(piAttr1);

    // (g) --- Retrieve the new number of references
    //
piPline2->ReleaseAttribute(piAttr1);
    cout << "---------------------------------- " << endl;
    cout << "After ReleaseAttribute on piPline2 " << endl;
    cout << "Number of objects pointed to by the attribute: (1 expected)";
    cout << piAttr1->GetNbAttrRef(#) << endl;

### Writing the Model and Closing the Container

cout << "After ReleaseAttribute on piPline2 " << endl;
cout << "Number of objects pointed to by the attribute: (1 expected)";
cout << piAttr1->GetNbAttrRef(#) << endl;
To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved.

The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.

    if(1==toStore)

     {
    #ifdef _WINDOWS_SOURCE
The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
if(1==toStore)
       ofstream filetowrite(pfileName, ios::binary ) ;

    #else
```vbscript
if(1==toStore)
ofstream filetowrite(pfileName, ios::binary ) ;
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
```

    #endif

       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close(#);
     }

     //
     // Closes the container
     //

     **::CATCloseCGMContainer**(piGeomFactory);
## In Short

The use case illustrates how to create and use CGM attributes.
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
## History

Version: **1** [Dec 2006] | Document created
---|---
