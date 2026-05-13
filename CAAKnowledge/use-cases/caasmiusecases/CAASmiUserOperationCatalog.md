---
title: "Untitled"
category: "use-case"
module: "CAASmiUseCases"
tags: ["CAADocStyleSheets", "CAASmgOperationSU", "CAASmiUserOperationCatalog", "CAAISmiUserMachFeature", "CATIMfgMachiningFeature", "CAASurfaceMachiningItf", "CAASmiOperationSampleOverview", "CATIM3xFeature", "CAASmiUserOperationUI", "CAAToolAngle", "CAADocUseCases", "CAASmgOperation", "CAASmgOperationWithMA", "CAASmiTechArticles", "CAASmgOperationWithMASU", "CAASmiUserOperation", "CAASmgMachiningFeature", "CAAUserOperationCatalog", "CAADocRunSample", "CAAOffset"]
source_file: "Doc/online/CAASmiUseCases/CAASmiUserOperationCatalog.htmmd"
converted: "2026-05-11T11:27:02.777035"
---

---

    
    
    

---

    
    

### 
        What You Will Learn With This Use Case
    

        This use case is intended to help you to generate a new library containing **Surface
            Machining Operation StartUps**.
    

        This involves the following:
    

        
- Creating a new library of activities.
        
- Add StartUps in this library.
        
- Add strategy parameters on StartUps.
    
    

        [Top]
    
    

### 
        The CAASmiUserOperationCatalog Use Case
    

        CAASmiUserOperationCatalog is a use case of the CAASurfaceMachiningItf.edu framework
        that illustrates Surface Machining capabilities.
    

        It is the first step of the sample described in the technical article [1].
    

        [Top]
    
    

#### 
        What Does CAASmiUserOperationCatalog Do
    

        CAASmiUserOperationCatalog enables the customer to generate a new catalog containing
        two new StartUps :
    

        
- The startup of CAA Plunge Operation is **CAASmgOperation**. It uses its own machining
            feature: **CAASmgMachiningFeature** and has three parameters: CAAStep, CAAToolAngle
            and CAAApproachDistance.
        
- The startup of CAA Box Operation is **CAASmgOperationWithMA**. It uses machining
            areas and has one parameter CAAOffset.
    
    

        [Top]
    
    

#### 
        How to Launch CAASmiUserOperationCatalog
    

        To launch CAASmiUserOperationCatalog, you will need to set up the runtime environment
        and then execute the CATfctEditorAssistant tool as indicated.
    
    

        To have more explanation on the usage of the CATFctEditorAssistant tool, please
        refer to the Creating Startups in Catalogs use case.
    

        [Top]
    
    

#### 
        Where to Find the CAASmiUserOperationCatalog Code
    

        The CAASmiUserOperationCatalog.osm file is located in the InputData directory of
        the CAASurfaceMachiningItf.edu framework:
    

        `InstallRootDirectory/CAASurfaceMachiningItf.edu/InputData`
    

        where `InstallRootDirectory` is the root directory of your CAA installation.
    

        [Top]
    
    

### 
        Step-by-Step
    

        There are five logical steps in CAAUserOperationCatalog for the creation of a new
        activities catalog:
    

        
- Creating a new activities catalog 
        
- Creating a startup in this catalog
        
- Adding strategy parameters to the startup
        
- Upgrading the activities catalog
    
    
    

### 
        Creating a new activities catalog
    

        To create a catalog, run the CATfctEditorAssistant with the **-create-new-catalog**
        option and the **-using-template** option. This option with the "delmia" argument
        allows to create a specific "process" container named *SPPLibCont* that will
        contain the activities startup.
    
    

        Once the above command has been executed, you will find two new files:
    

        
- CAAUserOperationCatalog.CATfct 
        
- CAAUserOperationCatalog.osm 
    
    

        Both files represent the same version of an empty catalog with a root container.
        The only difference is that the `.osm` file is readable while the `.CATfct`
        catalog is not:
    
    

        [Top]
    
    

### 
        Creating a startup in this Catalog
    

        To define the startup of a new User Defined Operation, the new startup must derive
        from the startup "MfgUserDefinedMO" which is defined in the ManufacturingActivities.feat
        catalog. In the new catalog, we create a new startup of type "CAASmgOperation".
    
    

        This is done with the following lines in CAAUserOperationCatalog.osm:
    
    

        Note that the "AuthorizedItems" attribute holds a list of string so that it is possible
        to add several type of features.
    

        The call to the `synchronize` method is necessary to be sure that any
        modification on the mother startup MfgUserDefinedMO is propagated on the new startup.
    

        [Top]
    
    
    

### 
        Adding Strategy Parameters to the startup
    

        Then we add four new strategy parameters "CAAStep", "CAAToolAngle", "CAAApproachDistance"
        and "Box Offset" to the startup.
    
    

        The AddStrategyParameteris a method to
        be called on the StrategyParameters feature that creates a new literal feature and
        adds it to the strategy block of parameters. It takes 3 input arguments:
    

        
- a **name** : this is the name of the attribute that will contain the strategy
            parameter to be created
        
- a **dimension** : this is the dimension of the parameter to be created.
            

            It can be regular types (`String, Integer, Real, Boolean`) or magnitudes
            (`LENGTH, ANGLE, ...`). For the complete list of available magnitudes,
            look at the Magnitudes Reference article.
        
- a **value**: this is the default value that the parameter will hold once it is
            created
    
    

        [Top]
    
    

### 
        Upgrading the activities catalog
    

        Now that the OSM file has been updated with the required startup and attributes,
        you can use CATfctEditorAssistant to create the corresponding catalog. This is done
        by upgrading the empty catalog created previously. This catalog
        must be in the runtime view.
    
    

        Keep in mind that CATfctEditorAssitant will look up the catalog in the run-time
        view but will output to the location specified on the command-linee.
    

        Note that the catalog can be upgraded as many times as necessary using the same
        methodology. First you modify the osm file then you launch the CATFctEditorAssistant
        with the appropriate arguments.
    

        [Top]
    

---

    
    

### 
        In Short
    

        This article provides an example on how to generate and upgrade a catalog of User
        Defined Machining Operations thanks to the osm language.
    

        In this example we generate a catalog named "CAAUserOperationCatalog.CATfct" that
        contains one startup of a User Defined Operation with the CATFctEditorAssistant
        on line tool. It derives from the late type "MfgUserDefinedMO" as every user defined
        operation should do. The "MfgUserDefinedMO" is a standard user defined operation.
        The corresponding startup of this operation is defined in the ManufacturingActivities.feat
        catalog.
    

        For this user defined activity we authorized a "CATIMfgMachiningFeature" machining
        feature, which is a standard machining feature defined in the Manufacturing.feat
        catalog.
    

        We also add several strategy parameters on this startup in several steps to illustrate
        the upgrade mechanism.
    

        This use case has demonstrated how to create Operations StartUps in the newly created
        "CAAUserOperationCatalog.CATFct library. It derives from the late type "MfgUserDefinedMO"
        as every user defined operation should do it.
    

        This StartUp will later be used in the next use case [3].
    

        [Top]
    

---

    
    

### 
        References
    
    

---

    
    

### 
        History
    
    

---

    
    

        *Copyright  2002, Dassault Systmes. All rights reserved.*
    

         

```vbscript
$ mkrun -c sh
$ cd your_workspace_root
$ # Make sure that no previous catalog exists in the runtime view, including in the concatenation
$ rm OS_directory//resources/graphic/CAAUserOperationCatalog.CATfct

$ # Create empty catalog in the runtime view and empty osm (the absolute path for the catalog is MANDATORY)$
$ CATfctEditorAssistant -create-new-catalog -catalog-name $PWDb&gt;/OS_directory/r/resources/graphic/CAAUserOperationCatalog.CATfct
    -with-client-id CLIENT -using-template delmia
$
$ # Modify the body of container of empty OSM CAAUserOperationCatalog.osm with the osm: InputData/CAAUserOperationCatalog.osm. 
$
$ # Updage the empty calalog Note that the upgraded catalog will be output in the current directory
$ CATfctEditorAssistant -update-catalog -catalog-name CAAUserOperationCatalog.CATfct
    -with-client-id CLIENT -with-osm CAAUserOperationCatalog.osm

$ # the mkrun shell
$ exit
```

```vbscript
CATfctEditorAssistant -create-new-catalog -catalog-name CAAUserOperationCatalog.CATfct -with-client-id CLIENT -using-template delmia
```

```vbscript
/**
* Copyright Dassault Systemes 2006
* delmia.osm catalog skeleton
* use this skeleton to create Machining catalog
*/
document `CAAUserOperationCatalog.CATfct` {
	history("xxx","","xxxx-xx-xx 12:38",0., xxxxxxxxxx-xxxx-xxxx-xxxxxxxxxxxxxxxx)
	check_revision(xxxxxxxxxx-xxxx-xxxx-xxxxxxxxxxxxxxxx)
	
	container `SPPLibCont` #root #isa(SPPLibCont) #uuid(xxxxxxxxxx-xxxx-xxxx-xxxxxxxxxxxxxxxx) {
		
// insert here your startups

	}
}
```

```vbscript
...
		// User Startup deriving from MfgUserDefinedMO
		// --------------------------------------------------
		feature CAASmgOperationSU MfgUserDefinedMO@`ManufacturingActivities.feat` #startup #isa(CAASmgOperation) {
			AuthorizedItems=["CATIMfgMachiningFeature","CAAISmiUserMachFeature"]
			Representation="I_CAASmgOperation"		
			synchronize(#)
		}
		
		// Second user Startup deriving from MfgUserDefinedMO
		// --------------------------------------------------
		feature CAASmgOperationWithMASU MfgUserDefinedMO@`ManufacturingActivities.feat` #startup #isa(CAASmgOperationWithMA) {
			AuthorizedItems=["CATIMfgMachiningFeature","CATIM3xFeature"]
			Representation="I_CAASmgOperationWithMA"		
				
			synchronize(#)
		}
        ...
```

```vbscript
...
		// User Startup deriving from MfgUserDefinedMO
		// --------------------------------------------------
		feature CAASmgOperationSU MfgUserDefinedMO@`ManufacturingActivities.feat` #startup #isa(CAASmgOperation) {
			AuthorizedItems=["CATIMfgMachiningFeature","CAAISmiUserMachFeature"]
			Representation="I_CAASmgOperation"		
			synchronize(#)
		    
			// Use behavior defined on MfgParameter to create new Strategy parameters on new user startup
			this->StrategyParameters->AddStrategyParameter(CAAStep,LENGTH,10.)
			this->StrategyParameters->AddStrategyParameter(CAAToolAngle,ANGLE,2.0)	
			this->StrategyParameters->AddStrategyParameter(CAAApproachDistance,LENGTH,20.)	
		}
		
		// Second user Startup deriving from MfgUserDefinedMO
		// --------------------------------------------------
		feature CAASmgOperationWithMASU MfgUserDefinedMO@`ManufacturingActivities.feat` #startup #isa(CAASmgOperationWithMA) {
			AuthorizedItems=["CATIMfgMachiningFeature","CATIM3xFeature"]
			Representation="I_CAASmgOperationWithMA"		
				
			synchronize(#)
		    
			// Use behavior defined on MfgParameter to create new Strategy parameters on new user startup
			this->StrategyParameters->AddStrategyParameter(`Box Offset`,LENGTH,0.0)	
		}
        ...
```

```vbscript
CATfctEditorAssistant -update-catalog -catalog-name CAAUserOperationCatalog.CATfct -with-client-id CLIENT -with-osm CAAUserOperationCatalog.osm
```