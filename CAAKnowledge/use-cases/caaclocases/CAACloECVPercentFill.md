---
```vbscript
title: "Distributive Systemes"
category: "use case"
module: "CAACloUseCases"
tags: ["CAACommonLayoutItf", "CAACloECVPercentFill", "CATIEcvPercentFill", "CAAEPFforNetworkArc", "CAACommonLayoutInterfaces", "CAAEPFforNetworkNode"]
source_file: "Doc/online/CAACloUseCases/CAACloECVPercentFill.htmmd"
converted: "2026-05-11T17:33:49.355969"
```

---
tags: ["CAACommonLayoutItf", "CAACloECVPercentFill", "CATIEcvPercentFill", "CAAEPFforNetworkArc", "CAACommonLayoutInterfaces", "CAAEPFforNetworkNode"]
source_file: "Doc/online/CAACloUseCases/CAACloECVPercentFill.htmmd"
converted: "2026-05-11T17:33:49.355969"
Distributive Systemes |  Electrical Cable Route Management (ECV) |  Custom Computation of Cableway Percent Fill  _ How the user can define the way percent fill shall be computed and used_

converted: "2026-05-11T17:33:49.355969"
Distributive Systemes |  Electrical Cable Route Management (ECV) |  Custom Computation of Cableway Percent Fill  _ How the user can define the way percent fill shall be computed and used_
Use Case

* * *

Abstract CAACloECVPercentFill is a use case of the CAACommonLayoutItf.edu framework. It illustrates a CATCommonLayoutInterfaces interface to be implemented to define custom computation of percent fill during cable routing.
    * ** What You Will Learn With This Use Case**
    * ** The CAACloECVPercentFill Use Case**
      * What Does CAACloECVPercentFill Do
      * How to Launch CAACloECVPercentFill
      * Where to Find the CAACloECVPercentFill Code
    * ** Step-by-Step**
    * ** In Short**
    * **References**
---

* * *

What You Will Learn With This Use Case This ECV product use case is intended to show how to invoke user implementation for determining Node percent fill for Hanger and Node & Arc percent fill for Raceway/Conduit cableways using the CATIEcvPercentFill interface. [Top] The CAACloECVPercentFill Use Case CAACloECVPercentFill is a use case of the CAACommonLayoutInterfaces.edu framework that illustrates Electrical Cable Routing capabilities using custom percent fill. [Top] What Does CAACloECVPercentFill Do This use case:           Illustrates a capability to have a user implementation automatically invoked when CATIEcvPercentFill interface from CATCommonLayoutInterfaces is implemented on CATEcwLightNwkNodeForPercentFill and / or CATEcwLightNwkArcForPercentFill objects

> > > > > > > > > > > > > > > > > > > > > > > > > > > > > >   [Top]

What You Will Learn With This Use Case This ECV product use case is intended to show how to invoke user implementation for determining Node percent fill for Hanger and Node & Arc percent fill for Raceway/Conduit cableways using the CATIEcvPercentFill interface. [Top] The CAACloECVPercentFill Use Case CAACloECVPercentFill is a use case of the CAACommonLayoutInterfaces.edu framework that illustrates Electrical Cable Routing capabilities using custom percent fill. [Top] What Does CAACloECVPercentFill Do This use case:           Illustrates a capability to have a user implementation automatically invoked when CATIEcvPercentFill interface from CATCommonLayoutInterfaces is implemented on CATEcwLightNwkNodeForPercentFill and / or CATEcwLightNwkArcForPercentFill objects
How to Launch CAACloECVPercentFill  To launch CAACloECVPercentFill, you will need to set up the build time environment, then compile CAACloECVPercentFill.m along with its prerequisites, set up the run time Enovia environment, and then follow the detailed sample steps.                                                                                                                                                                      [Top] Where to Find the CAACloECVPercentFill Code CAACloECVPercentFill code is located in the CAACloECVPercentFill.m use case module of the CAACommonLayoutItf.edu framework: Windows |  InstallRootDirectory/ CACommonLayoutItf.edu/CAACloECVPercentFill.m

How to Launch CAACloECVPercentFill  To launch CAACloECVPercentFill, you will need to set up the build time environment, then compile CAACloECVPercentFill.m along with its prerequisites, set up the run time Enovia environment, and then follow the detailed sample steps.                                                                                                                                                                      [Top] Where to Find the CAACloECVPercentFill Code CAACloECVPercentFill code is located in the CAACloECVPercentFill.m use case module of the CAACommonLayoutItf.edu framework: Windows |  InstallRootDirectory/ CACommonLayoutItf.edu/CAACloECVPercentFill.m
Unix |  InstallRootDirectory/ CAACommonLayoutItf.edu/CAACloECVPercentFill.m
CAACommonLayoutItf.edu framework contains dictionary file: Windows |  InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico

How to Launch CAACloECVPercentFill  To launch CAACloECVPercentFill, you will need to set up the build time environment, then compile CAACloECVPercentFill.m along with its prerequisites, set up the run time Enovia environment, and then follow the detailed sample steps.                                                                                                                                                                      [Top] Where to Find the CAACloECVPercentFill Code CAACloECVPercentFill code is located in the CAACloECVPercentFill.m use case module of the CAACommonLayoutItf.edu framework: Windows |  InstallRootDirectory/ CACommonLayoutItf.edu/CAACloECVPercentFill.m
Unix |  InstallRootDirectory/ CAACommonLayoutItf.edu/CAACloECVPercentFill.m
CAACommonLayoutItf.edu framework contains dictionary file: Windows |  InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico
Unix |  InstallRootDirectory/CAACommonLayoutItf.edu/CNext/code/dictionary/CAACommonLayoutItf.edu.dico
where InstallRootDirectory is the root directory of your CAA V5 installation.  C++ source files: CAAEPFforNetworkNode.cpp: This is the implementation of CATIEcvPercentFill on CATEcwLightNwkNodeForPercentFill object.  CAAEPFforNetworkArc.cpp: This is the implementation of CATIEcvPercentFill on CATEcwLightNwkArcForPercentFill.  CAAEPFforNetworkNode.h and CAAEPFforNetworkArc.h are the corresponding header (.h) files. [Top] Step-by-Step There are three logical steps in CAACloECVPercentFill:

    * Prolog
    * Mechanism of Working
      * Hanger Cableway Network
      * Raceway/Conduit Cableway Network
    * Detailed Scenario
      * Sample 1 (Hanger Cableway Network)
      * Sample 2 (Raceway/Conduit Cableway Network)
                                                                                                                                                                                                                                                [Top] Prolog Prior to implementation of this Use case, user should have knowledge about ECV product. Refer V5 documentation.  The user will have to provide implementation depending on type of cableway network:          1. Hanger Network: CATIEcvPercentFill on CATEcwLightNwkNodeForPercentFill
        2. Raceway / Conduit Network: CATIEcvPercentFill on CATEcwLightNwkNodeForPercentFill and CATEcwLightNwkArcForPercentFill
2. Raceway / Conduit Network: CATIEcvPercentFill on CATEcwLightNwkNodeForPercentFill and CATEcwLightNwkArcForPercentFill
```vbscript
If no user implementation exists, then default implementation will get invoked.

```

NOTE:

```vbscript
        For R19sp5+ level, environment variable ECV_CAAPercentFill needs to be set
```vbscript
```vbscript
        For R20GA level and above, no environment variable is needed.

```

```

```

```vbscript
```vbscript
For *.h sample, refer image below:

```

```

    class CAAEPFforNetworkNode: public CATBaseUnknown

    {
class CAAEPFforNetworkNode: public CATBaseUnknown
    CATDeclareClass;

    public:

    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
public:
    CAAEPFforNetworkNode(#);
    virtual ~ CAAEPFforNetworkNode(#);

    /**
    * Implements a function from an interface.
    * @href CATIEcvPercentFill#ComputePercentFillValue
    */
    HRESULT ComputePercentFillValue
    		(CATEcwLightNwkNodeForPercentFill * pNwkNode,
    		CATEcwLightNwkArcForPercentFill * pNwkArc,
    		CATLISTP(CATEcwLightNwkArcForPercentFill)
    		 	pListOfCATEcwLightNwkArcForPercentFill,
    		CATEcwLightNwkCableForPercentFill * pNwkCable,
    		CATLISTP(CATEcwLightNwkCableForPercentFill)
    			pListOfCATEcwLightNwkCableForPercentFill,
    		int iRoutingMode,
    		int iRouteToolsOptionStackCableOption,
    		int iPFToBeSetOnNode,
    		double & odComputedPercentFill);

    private:

    };
    #endif

---
 [Top] Mechanism of Working The implementation will have the routine ComputePercentFillValue in which user needs to calculate Node percent fill for Hanger and Node & Arc percent fill for Raceway/Conduit cableways. This/these user implementation(s) shall be invoked multiple times when user performs different operations such as         1. Load the cable(s) data from database
        2. Different routing modes - Route a cable, Delete a route, Delete a sub route, Validate a route. These above operations are mapped to four types of Routing mode - the 6th argument of ComputePercentFillValue routine. The percent fill needs to be calculated according to the routing mode. Hanger Cableway Network: Code in CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkNode.cpp gets invoked.  Note:i) The 2nd argument (CATEcwLightNwkArcForPercentFill *pNwkArc) will be always NULL as hanger network does not have the physical arc.  ii) The 3rd argument CATLISTP(CATEcwLightNwkArcForPercentFill)   pListOfCATEcwLightNwkArcForPercentFill should not be used in the implementation. Raceways/Conduits Cableway Network:  Code in CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkNode.cpp and CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkArc.cpp gets invoked. Here, both CATEcwLightNwkNodeForPercentFill *  pNwkNode and CATEcwLightNwkArcForPercentFill *pNwkArc (1st and 2nd argument of ComputePercentFillValue) will be valid as raceway network has both nodes as well as arc.3rd argument CATLISTP(CATEcwLightNwkArcForPercentFill)  pListOfCATEcwLightNwkArcForPercentFill is not used in the implementation. Example of dictionary (***.dic) CATEcwLightNwkNodeForPercentFill       CATIEcvPercentFill        libXYZ (where libXYZ is the library where the implementation resides) CATEcwLightNwkArcForPercentFill         CATIEcvPercentFill        libXYZ (where libXYZ is the library where the implementation resides) General scenario:          1. Use Electrical cable database Importer command in VPM Nav workbench.
```vbscript
    2. Use Set context Electrical cable database in VPM Nav workbench.
    3. Use Manage cables from database command in Electrical cableway routing workbench.
```
          a. Load the cables
          b. Perform various operations such as Auto Route, partial route, delete route, delete sub route and validate route.

                                                                                                                                                                                                                                                [Top] Detailed Scenario: Sample 1 (Hanger Cableway Network): Prerequisite:  This sample uses the following products as work packages located in CAACommonLayoutItf.edu/InputData/HangerModel: Hanger Model work packages: MWY1_ECV.CATProduct, LWY1_ECV.CATProduct, EQT1_ECV.CATProduct, EQT2_ECV.CATProduct, ELD1_ECV.CATProduct Code invoked: CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkNode.cpp Steps to be followed:      1. Insert the work packages under PRC and save the PRC.
```vbscript
2. Use Set context Electrical cable database in VPM Nav workbench.
3. Use Manage cables from database command in Electrical cableway routing workbench.
```
a. Load the cables
b. Perform various operations such as Auto Route, partial route, delete route, delete sub route and validate route.
2. Use Electrical cable database Importer command in VPM Nav workbench.
```vbscript
3. Use Set context Electrical cable database in VPM Nav workbench.
4. Use Manage cables from database command in Electrical Cableway routing workbench.
```

               ![](images/image001.png)           5. Load All Cables              ![](images/image003.png)             6. AutoRoute 1st 3 cables - 1 cable each time 1027, 1028, 1030. Here the Routing mode will be 1.
2. Use Electrical cable database Importer command in VPM Nav workbench.
```vbscript
3. Use Set context Electrical cable database in VPM Nav workbench.
4. Use Manage cables from database command in Electrical Cableway routing workbench.
```
                    Code at line no. 160 gets invoked.
                    User can save the percent fill report by the Save As option in the below panel.
             We get Electrical cable database result as follows which mentions about the percent fill at each node: (say for cable-1027)

               ![](images/image005.png)

```vbscript
> 7. Set Context again, Load all cables
>  8. As the cables are already routed and we are again loading the same, it should Get percent fill for existing network, thus user implementation for load mode
```
>      CAAEPFforNetworkNode::ComputePercentFillValue gets invoked for first time.
>          Here routing mode will be 3. Code at line no. 167 gets invoked
>          Save the report using Save As.
>  9. Delete partial route for 1030 from M30 to M33
>          Here the Routing mode will be 2; Code at line no. 162 gets invoked.
>          Save the report using Save As.
>

 [Top] Sample 2 (Raceway/Conduit Cableway Network): Prerequisite:  This sample uses the following products as work packages located in
CAACommonLayoutItf.edu/InputData/ RacewayModel.
  Raceway model work packages:  WKP_Raceway.CATProduct, WKP_EQT_RWY.CATProduct, WKP_ELD_RWY.CATProduc Code invoked:         1. CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkNode.cpp
        2. CAACommonLayoutItf.edu/CAACloECVPercentFill.m/src/CAAEPFforNetworkArc.cpp
  Steps to be followed:

> 1. Insert the work packages under PRC and save the PRC.
>  2. Use Electrical cable database Importer command in VPM Nav workbench.
>          Here the PRM resource "TypeofECVDataToBeImported" needs to be set to "2" in the active Project xml (available under Tools->Project Management->Select Browse).
>          Note that CNext xml cannot be used for this purpose.
```vbscript
>  3. Use Set context Electrical cable database in VPM Nav workbench.
>  4. Use Manage cables from database command in Electrical Cableway routing workbench.
```
>  5. Load All Cables
>  6. AutoRoute 1st 2 cables cable 01 and cable 02.
>          Here the Routing mode will be 1. Code at line no.158 in CAAEPFforNetworkArc.cpp gets invoked.
>          Percent fill calculation is different for stack option check.
>          User can save the percent fill report by the Save As option in the above panel.
>  7. Again set the context. Load the cables.
>  8. As the cables are already routed and we are again loading the same, it should get percent fill for existing network, thus user implementation for load mode gets invoked for first time.
>          Here routing mode will be 3. Code mentioned in the step 6 gets invoked.
>  9. Select Cable 01, Select Delete sub route option, and select FROM Node 63 to TO Node 75 so as to delete the sub route between these two nodes.
>          For deletion of the sub route the routing mode will be 2. Code at line 180 in CAAEPFforNetworkArc.cpp gets invoked.
>          Save the report using the Save As option.
>  10. Select the Cable 01, Select Validate Route option, and click ok to validate the route.
>          Code at line no. 206 in CAAEPFforNetworkArc.cpp gets invoked.
>          Save the report using the Save As option.
```vbscript
>  11. Set the context again
>  12. Load all the cables.
```
>  13. Select Cable-01, select the partial route option and then select FROM Node 62 to TO Node 86. Click ok to generate reports.
>          Here, Routing mode will be 1 and code invoked will be same as at step 6 above.
>          Save the report using Save As.
>  14. Go to previous dialog, Validate the cable -01 using Validate option.
>  15. The route gets validated and status gets changed to fully routed cable.
>          Save the report using Save As.

 [Top]

* * *

In Short This use case has demonstrated how the user implementation to calculate node and Arc percent fill shall be invoked for CATIEcvPercentFill interface. [Top]

* * *

References [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---
 [Top]

* * *

* * *

_Copyright 2009, Dassault Systmes. All rights reserved._
