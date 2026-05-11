---
title: "Contextual Help for an Add-on"
category: "use case"
module: "CAAAfrUseCases"
tags: ["CAAAfrDumpCommandHeader", "CAAAfrExploreHdr", "CAAAfrCuboidHdr", "CAAAfrBoundingEltHdr", "CAAGeometry", "CAAAfrGeoAnalysisWkbHeader", "CATIA", "CAAAfrCylinder2Hdr", "CATIAfr_C2", "CAADialogEngine", "CAACATIAApplicationFrame", "CAAAfrGeoChartWindowAdnHeader", "CATIAfrs", "CATIAApplicationFrame", "CAADoc", "CAAVisualization", "CAAAfrGeoCreationWkbHeader", "CAAAfrCylinder1Hdr", "CATIAtoc", "CAAAfrHistogramChartWindowHdr"]
source_file: "Doc\online\CAAAfrUseCases\CAAAfrSampleContextualHelpCATIA.htm"
converted: "2026-05-11T17:17:55.660612"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Frame

| 

### Contextual Help for an Add-on

_How to create a documentation file tree_  
---|---|---  
Use Case  
  
* * *

### Abstract

This article shows how to create a documentation file tree for an Add-On of the CATIA Application. 

  * **What You Will Learn With This Use Case**
  * **The CAADoc Use Case**
    * What Does CAADoc Do
    * How to Launch CAADoc
    * Where to Find the CAADoc Files
  * **Step-by-Step**
  * **In Short**
  * **References**



* * *

### What You Will Learn With This Use Case

This use case is intended to show you the structure and the contents of a documentation file tree [1] for an Add-On on the CATIA Application.  [Top]

### The CAADoc Use Case

CAADoc is a use case of the CAAApplicationFrame.edu framework that illustrates contextual help on commands created in the CAAGeometry sample use case. [Top]

#### What Does CAADoc Do

The CAAGeometry is a sample document that contains a set of commands in a workshop and in two workbenches: CAA V5: Geometrical Creation and CAA V5: Geometrical Analysis. For some commands there is a contextual help. To do that, we have created a documentation file tree which respects a structure to enable the visualization of HTML pages when the end user clicks F1 on a command.  Launch CATIA , when the application is ready: 
* In the **Start** menu click **Infrastructure** and select **CAA V5: Geometrical Creation**
* In the **File New   **Dialog box select **CAAGeometry** and click **OK**
* On the **Tools** menu click **Options**

  * Select the **Help** Tab Page in the **General** options
  * Enter **< InstallRootDirectory>/CAADoc/CAAApplicationFrame.edu/CAADoc **in the **Technical Documentation** editor
Where <InstallRootDirectory> is the directory where the CAA CD-ROM is installed. 
  * Click**OK**


* Launch the **Point![](images/CAAAfrHOLCAAPoint.jpg) **command
* Click **F1** The following HTML page is displayed: _Fig.1: The Point Command Page_ | ![](images/CAAAfrHOLPointCmd.jpg)  
---  
  
The top of the page contains a link towards the home page of the Add-On [Fig.3] (Home icon). The Point command is a command created in the CAAGeometry workshop so at the right of the banner, you have the icon representing this workshop.

To display this page, the V5 application creates automatically a frame set which contains five HTML pages:

  * At the left top of the frame, the CATIA banner page with the version, the current release, and the home icon,
  * At the right top of the frame, the banner page associated with the CAAGeometry workshop. This page contains the workshop name and its icon,
  * At the top, between the CATIA banner page and the banner page associated with the CAAGeometry workshop, there is a white page. In standard DS documentation, this is the place for the navigation tool.
  * At the left of the frame, the table of contents page associated with the workshop, empty when accessed by contextual help,
  * At the center of the frame, the page associated with the command.


* Launch the **Cuboid** command 
* Click **F1** The following HTML page is displayed:

_Fig.2: The Cuboid Command Page_ ![](images/CAAAfrHOLCuboidCmd.jpg)  
---  
  
The top of the page contains a link towards the home page of the Add-On [Fig.3]. The Cuboid command is a command created in the CAAV5 Geometrical Creation workbench so at the right of the page, you have the icon representing this workbench.

To display this page, the V5 application creates automatically a frame set which contains the same five HTML pages as for the Point command.

* Click the ![](images/CAAAfrHOLnavhome.jpg) icon 

The following HTML page is displayed:

_Fig.3: The Home Page_ ![](images/CAAAfrHOLHomePage.jpg)  
---  
  
This is the home page of the Add-On. You retrieve the icon of the workshop and an icon for each workbench. In clicking them you will reach an information page about these entities. 

* Click the ![](images/CAAAfrHOLAnaWb.jpg) icon 

The following HTML page is displayed:

_Fig.4: The CAA V5 Geometrical Analysis workbench Home Page_ ![](images/CAAAfrHOLAnaWbHomePage.jpg)  
---  
  
To display this page, the V5 application creates automatically a frame frame set (`AnaWbCATIAfrs.htm`) contained in the `CATIAfr_C2` directory. This frame set uses HTML pages from the Geometrical Analysis workbench and is divided in four parts:

  * At the left top of the frame, the CATIA banner page with the version, the current release, and the home icon,
  * At the right top of the frame, the banner page associated with the Geometrical Analysis workbench. This page contains the workbench name and its icon,
  * At the left of the frame, the table of contents page associated with the Geometrical Analysis workbench,
  * At the center of the frame, the page associated with the workbench.


* Click **Back** in the browser
* Click the![](images/CAAAfrHOLCreWb.jpg) icon

The following HTML page is displayed:

_Fig.5: The CAA V5 Geometrical Creation workbench Home Page_ ![](images/CAAAfrHOLCreWbHomePage.jpg)  
---  
  
To display this page, the V5 application creates automatically a frame set which contains the same four HTML pages as for the Geometrical Analysis workbench.

Note that if there is no current command, F1 displays the default contextual help home page, as Help > Contents, Index and Search menu item does. This default page is linked to **CATFrame.HelpTopics** LongHelpId key. If you want this page be part of your product line, you must create such a HTML topic and associate it to **CATFrame.HelpTopics** key in your own **CommonId2url.CATNls** file.

[Top]

#### How to Launch CAADoc

To launch CAADoc , you will need to set up the build time environment, then compile all the modules of the following frameworks:

  * CAAApplicationFrame.edu
  * CAACATIAApplicationFrame.edu
  * CAADialogEngine.edu
  * CAASystem.edu
  * CAAVisualization.edu



Next set up the run time environment, and then execute the use case [2].

Then, in the window where you run the mkrun command, do not type the module name on the command line, but type CNEXT instead. When the application is ready make the scenario given in the above section. 

[Top]

#### Where to Find the CAADoc Files

The CAADoc use case is made of several files located in the CAADoc module of the CAAApplicationFrame.edu framework:

Windows | `<InstallRootDirectory>\CAADoc\CAAApplicationFrame.edu\CAADoc\`  
---|---  
Unix | `<InstallRootDirectory>/CAADoc/CAAApplicationFrame.edu/CAADoc/`  
  
where `<InstallRootDirectory>` is the directory where the CAA CD-ROM is installed.

[Top]

### Step-by-Step

There are two logical steps in CAADoc:

  1. Creating the Documentation File Tree Structure and Contents
  2. Inserting the French Version



[Top]

#### Creating the Documentation File Tree Structure

![](images/CAAAfrHOLCAADoc.jpg)

At first create two sub-directories: the **online** and the **resources** directories.

##### Contents of the online directory

The online directory contains the **HomePage.htm** file [Fig.3] and a set of directories:

![](images/CAAAfrHOLonlinecontents.jpg)

The **CATIAfr_C2** directory contains the following files:

![](images/CAAAfrHOLPLcontents.jpg)  
---  
  
The CATIA banner page: CATIAbnr.htm file

![](images/CAAAfrHOLCAADocPLBanner.jpg)

The Analysis workbench frame page: AnaWbCATIAfrs.htm file

![](images/CAAAfrHOLAnaWbCATIAFrs.jpg)

The Analysis workbench banner page: AnaWbCATIAbnr.htm file

![](images/CAAAfrHOLAnaWbCATIABnr.jpg)

The Creation workbench frame page: CreWbCATIAfrs.htm file

![](images/CAAAfrHOLCreWbCATIAFrs.jpg)

The Creation workbench banner page: CreWbCATIAbnr.htm file

![](images/CAAAfrHOLCreWbCATIABnr.jpg)

The Geometry workshop frame page: GeoWsCATIAfrs.htm file

![](images/CAAAfrHOLGeoWsCATIAFrs.jpg)

The Geometry workshop banner page: GeoWbCATIAbnr.htm file

![](images/CAAAfrHOLGeoWsCATIABnr.jpg)

**AnaWb_C2** , **CreWb_C2** and **GeoWs_C2** are directories associated with the CAA V5 Geometrical Analysis workbench, the CAA V5 Geometrical Creation workbench and the CAAGeometry workshop respectively. 

> Detail of the **AnaWb** directory contents:
> 
> ![](images/CAAAfrHOLCAADocOnlineAnaWb.jpg)
> 
>   * **AnaWbboundingelement.htm** :  the page for the Bounding Elements command 
>   * **AnaWbCATIAtoc.htm** : an empty page which can contain tools for the AnaWb directory.
>   * **AnaWbpr01.htm** : the page associated with the CAA V5 Geometrical Analysis workbench.
>   * **AnaWbtoc.htm** : a page which contains links to another commands of the same module.
> 

> 
> Note that the AnaWb suffix, the name of the directories, are mandatory before the command pages and before the product line toc file. 

The **images** directory contains all the images used through the HTML pages of the AnaWb_C2, CreWb_C2 and GeoWs_C2 directories.

The **icons_C2** directory contains the **no_navigation.htm** file

##### Contents of the resources directory

This directory contains only the **msgcatalog** directory. 

![](images/CAAAfrHOLCAADocResources.jpg)

This msgcatalog directory contains the **CommonId2url**.CATNls file. 
    
    
    CAAAfrGeometryWksHeader.CAAAfrPointHdr = "GeoWs_C2/GeoWspoint.htm" ;
    CAAAfrGeometryWksHeader.CAAAfrPlaneHdr = "GeoWs_C2/GeoWsplane.htm" ;
    
    
    CAAAfrGeometryWksHeader.CAAAfrExploreHdr = "GeoWs_C2/GeoWsexplore.htm" ;
    CAAAfrDumpCommandHeader.CAAAfrDumpHdr = "GeoWs_C2/GeoWsdump.htm" ;
    CAAAfrGeoAnalysisWkbHeader.CAAAfrBoundingEltHdr = "AnaWb_C2/AnaWbboundingelement.htm" ;
    CAAAfrGeoCreationWkbHeader.CAAAfrCuboidHdr = "CreWb_C2/CreWbcuboid.htm" ;
    CAAAfrGeoCreationWkbHeader.CAAAfrCylinder1Hdr = "CreWb_C2/CreWbcylinder1.htm" ;
    CAAAfrGeoCreationWkbHeader.CAAAfrCylinder2Hdr = "CreWb_C2/CreWbcylinder2.htm" ;
    CAAAfrGeoChartWindowAdnHeader.CAAAfrHistogramChartWindowHdr = "GeoWs_C2/GeoWsChartWindow.htm" ;  
  
---  
  
In the CAAAfrGeometryWksHeader.CATRsc the resources file associated with the CAAAfrGeometryWksHeader class you find:
    
    
    CAAAfrGeometryWksHeader.CAAAfrPointHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPointHdr" ;
    CAAAfrGeometryWksHeader.CAAAfrPlaneHdr.LongHelpId      = "CAAAfrGeometryWksHeader.CAAAfrPlaneHdr" ;
    CAAAfrGeometryWksHeader.CAAAfrExploreHdr.LongHelpId     = "CAAAfrGeometryWksHeader.CAAAfrExploreHdr" ;  
  
---  
  
#### Inserting the French Version

##### The French Documentation

The French version is created at the first level of the CAADoc documentation file tree. 

![](images/CAAAfrHOLCAADocFrench.jpg)

The French directory contains two sub-directories: the **online** and the **resources** directories:

##### Contents of the online directory 

The **online** directory contains the French directory

![](images/CAAAfrHOLFrenchContents.jpg)

The French directory contains the **HomePage.htm** file [Fig.3] and a set of directories such as the English version:

![](images/CAAAfrHOLCAADocFrenchonlineFrench.jpg)  
---  
  
##### The **resources** directory  

![](images/CAAAfrHOLCAADocResourcesFrench.jpg)

The CommonId2url.CATNls file is inserted in the resources directory of the documentation file tree inside the French directory of the msgcatalog directory. This file contains the same thing as the English version.

[Top]

* * *

### In Short

This article explains the structure and the contents of a documentation file tree for the contextual help.

[Top]

* * *

### References

[1] | [Contextual Help](../CAAAfrTechArticles/CAAAfrHelpOnLine.htm)  
---|---  
[2] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.htm)  
[Top]  
  
* * *

### History

Version: **1** [Dec 2002] | Document created  
---|---  
Version: **2** [Dec 2003] | Navigation icon introduction  
Version: **3** [Oct 2014] | Review  
Version: **4** [May 2016] | Default LongHelpId  
[Top]  
  
* * *

_Copyright 2001-2014, Dassault Systmes. All rights reserved._
