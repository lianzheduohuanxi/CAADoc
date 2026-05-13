---
title: "Contextual Help"
category: "tech-article"
module: "CAAAfrTechArticles"
tags: "["CATIAfr_C2", "CATIA_P3", "CAAAfrPointHdr", "CATIA_PLM_Express", "CAAApplicationFrame", "CAAAfrGeometryWksHeader", "CAAGeometry", "CATIA", "CATIA_STUDENT"]"
source_file: "Doc/online/CAAAfrTechArticles/CAAAfrHelpOnLine.htm"
converted: "2026-05-11T17:17:55.880772"
---
#  3D PLM Enterprise Architecture

|
## User Interface - Frame

|
### Contextual Help

_Structure and contents of a technical documentation file tree_
---|---|---
Technical Article

* * *
### Abstract

This article shows how to create a technical documentation file tree and how to set a link from the command to its associated technical topic.

  * **How to Activate the Contextual Help**
  * **Contextual Help Mechanism**
    * The URL Link
    * The Mapping File
    * Multi-Documentation
  * **Contents of the Documentation File Tree**
  * **In Short**
  * **References**

---

* * *
### How to Activate the Contextual Help

During the execution of an interactive command, the corresponding contextual documentation can be made available by clicking on the F1 key. A HTML page is then displayed in a browser explaining in detail the role of the command through a common task. Here is an example with the "Shaft" command:

_Fig.1: Help text for the "Shaft" command_ ![](images/CAAAfrHOLPadDoc.jpg)
---

During the execution of an interactive command, the corresponding contextual documentation can be made available by clicking on the F1 key. A HTML page is then displayed in a browser explaining in detail the role of the command through a common task. Here is an example with the "Shaft" command:
_Fig.1: Help text for the "Shaft" command_ ![](images/CAAAfrHOLPadDoc.jpg)
In order for the F1 key to enable the display of the help text page, it is necessary for the command to have the "focus", i.e., it must be either in exclusive or shared mode. See the "CAA Command Model" [1]  article for further explanations regarding the mode of a command.

Because of this limitation on the usage of the F1 key, there exists a second way of accessing the contextual documentation: by moving on the command the mouse pointer after having started the "What's This ?" command represented by the  ![](images/CAAAfrHOLWhatIsThis.jpg)  icon. If a contextual help topic is available, a "More Info" link has been added to the long help text.

_Fig.2: More Info_ ![](images/CAAAfrHOLMoreInfo.jpg)

---

Because of this limitation on the usage of the F1 key, there exists a second way of accessing the contextual documentation: by moving on the command the mouse pointer after having started the "What's This ?" command represented by the  ![](images/CAAAfrHOLWhatIsThis.jpg)  icon. If a contextual help topic is available, a "More Info" link has been added to the long help text.
_Fig.2: More Info_ ![](images/CAAAfrHOLMoreInfo.jpg)
By clicking on it, a HTML page is displayed. Just above, it is an example with the "Reframe" command for which the F1 key cannot be activated.

[Top]
### Contextual Help Mechanism

On the one hand, there is a command and on the other a HTML page. The command is in a normal Framework containing code, whereas the HTML page is in a specific documentation file tree. The runtime link is established through a URL link:

  * The URL link is specified in the resources file associated to the command
  * The address of the HTML page is associated to the URL link through a mapping file

Therefore, by transition, starting from the command, it is possible to reach the documentation page.
#### The URL Link

Therefore, by transition, starting from the command, it is possible to reach the documentation page.
The URL link for a command is a resource. It can thus be found in the CATRsc files for the commands. The keyword used to associate a URL link is **LongHelpId.**

Example:

Let's have a look at an example based on the "Point" command for the CAAGeometry document used for command use cases. Here is an extract from the CAAAfrGeometryWksHeader.CATRsc file which is the resource file associated to the _CATCommandHeader_ class for the " Point" command. This file is set in the CAAApplicationFrame.edu/CNext/resources/msgcatalog directory:

    CAAAfrGeometryWksHeader.CAAAfrPointHdr.**LongHelpId** = "CAAAfrGeometryWksHeader.CAAAfrPointHdr";

---

CAAAfrGeometryWksHeader.CAAAfrPointHdr.**LongHelpId** = "CAAAfrGeometryWksHeader.CAAAfrPointHdr";
where:

CAAAfrGeometryWksHeader | is the command header resource file name

where:
CAAAfrGeometryWksHeader | is the command header resource file name
CAAAfrPointHdr | is the identifier of the CAAAfrGeometryWksHeader class instance created for the Point command
LongHelpId   | is the keyword dedicated to associate a URL to the command
CAAAfrGeometryWksHeader.CAAAfrPointHdr | is the URL link.

```vbscript
```vbscript
For naming the URL link, follow the recommended rules for objects providing contextual help. For commands, see the "Creating Resources for Command Header" [2] technical article and for the Tools Options pages, see the "Application Property Access" [3] article.

```

```

#### The Mapping File
##### Contents of the Mapping File

The mapping file contains the equivalences between the URL links and the **relative** **addresses** of the HTML pages in the documentation file tree.

Example:

```vbscript
```vbscript
For the same "Point" command like just above, in the mapping file you have the following line:

```

```

```vbscript
    CAAAfrGeometryWksHeader.CAAAfrPointHdr = "GeoWs_C2/GeoWspoint.md";

```

---

CAAAfrGeometryWksHeader.CAAAfrPointHdr = "GeoWs_C2/GeoWspoint.md";
where:

CAAAfrGeometryWksHeader.CAAAfrPointHdr    | URL defined in the resources file for the "Point" command -see the URL link section

where:
CAAAfrGeometryWksHeader.CAAAfrPointHdr    | URL defined in the resources file for the "Point" command -see the URL link section
GeoWs_C2/GeoWspoint.md | Relative position of the HTML page for the Point command in the documentation file tree . It is always the same syntax: **ModuleName/CommandPageName.md  **

  * **ModuleName** is a directory in the documentation file tree which contains a set of HTML pages and a table of contents page. The directory's location in the documentation file tree is explained in the Contents of the Documentation File Tree section.
  * **CommandPageName**.**htm** is set in the ModuleName directory. It is a page which contains the information that can help the end user to better understand the command.

##### Name of the Mapping file

The mapping file name is CommonId2url.CATNls.
##### Location of the Mapping File

The location of the mapping file in the documentation file tree is explained by the [Fig.5]
#### Multi-Documentation

```vbscript
```vbscript
For Dassault Systemes commands, the documentation can be found in an installation directory. Each DS partner has his own documentation file tree. This is why it is possible, at runtime, to concatenate the documentation file trees. Here is a screen shot of the Help tab page of the General option of the Options command.

```

```

_Fig.3: Concatenation of documentation path _ ![](images/CAAAfrHOLToolsOptionsComment.jpg)
---

![](../CAAIcons/images/warning.gif)The order of concatenation is important: When searching for a page, the search goes from the first to the last path, ending as soon as the page has been found.

Note: The CATUserDocView variable is no longer available.

[Top]
### Contents of the Documentation File Tree

Note: The CATUserDocView variable is no longer available.
At runtime, a page associated to the command is created and displayed in the browser. This page has a frame set containing five sub-parts:

_Fig.4: Organization of the created page_ ![](images/CAAAfrHOLFrame.jpg)

---
At runtime, a page associated to the command is created and displayed in the browser. This page has a frame set containing five sub-parts:
_Fig.4: Organization of the created page_ ![](images/CAAAfrHOLFrame.jpg)
The information page:

               **1** | It is a HTML file which contains any information that can help the end user to better understand the command.

_Fig.4: Organization of the created page_ ![](images/CAAAfrHOLFrame.jpg)
The information page:
Each file is located in a module directory, as explained in the [Fig.5].

The information page:
Each file is located in a module directory, as explained in the [Fig.5].
The banner page of the current module:

                **2** | A module is a set of information pages for the same workbench, solution, product, etc. The location of the modules directories in the documentation file tree depends on the language, it is explained in the [Fig.5].   This banner page is a HTML page which contains information about the current module, that is the module where the information page is located. The workbench name, its icon ... For a DS product line, the name of this banner file depends on the module name and on the product line: <**ModuleName** ><**ProductLineGroup** >**bnr**.htm.  **< ProductLineGroup>** represents the product line group, it depends on the product line:  The following table presents the corresponding product line group for each product line: |  Product Line Group |        Product Line
---|---
CATIA |

  * CATIA_P3
  * CATIA_STUDENT
  * CATIA_PLM_Express

DELMIA |

  * DELMIA

DMU |

  * ENOVIA_3d_com
  * ENOVIA_V5_VPM
  * ENOVIA_DMU_Navigator

This file is not located in the module directory but is located in the same directory as the banner page of the product line. Refer to the fourth row of this table.

```vbscript
```vbscript
For a non DS product line, the name of this banner file depends on the module name and on the product line name: <**ModuleName** ><**ProductLineName** >**bnr**.htm. This file is located in the <**ProductLineName** > directory. Refer to the  "What Is the Product Line Visual Identity" technical article [4], to find the name of the product line.

```

```

The table of contents page for the current module:

                **3** | It is a HTML file which contains links to the information pages found in the same module. There is only one table of contents files per module

```vbscript
```vbscript
For a DS product line, the name of this toc file depends on the module name and on the product line: <**ModuleName** ><**ProductLineGroup** >**toc**.htm.

```

```

****Refer to the second row of this table to get values of <**ProductLineGroup** > for each product line. For a non DS product line, the name of this toc file depends on the module name and on the product line name: <**ModuleName** ><**ProductLineName** >**toc**.htm. Refer to the  "What Is the Product Line Visual Identity" technical article [4], to find the name of the product line. Note: when the page is displayed in contextual help, another file is used. The name of this file is <**ModuleName** >**toc**.htm. This file is empty. Both files are located in the module directory.
The banner page of the product line:

                 **4** | It is a HTML file which contains links to generic pages or functions and especially a link to the home page that contains information regarding all the modules.

```vbscript
```vbscript
For a DS product line, the name of this banner file depends on the product line group: <**ProductLineGroup** >**bnr**.htm.

```

```

****Refer to the second row of this table to get values of <**ProductLineGroup** > for each product line. For a non DS product line, the name of this toc file depends on the product line name: <**ProductLineName** >**bnr**.htm. Refer to the  "What Is the Product Line Visual Identity" technical article [4], to find the name of the product line. This banner file is, therefore, unique and is saved in a directory whose name depends on the product line:

  * CATIAfr_C2 for CATIA_P3,
  * catsfr_C2 for CATIA_STUDENT,
  * xatfr_C2 for CATIA_PLM_Express,
  * DELMIAfr_D2 for DELMIA,
  * omdfr_O2 for ENOVIA_3d_com,
  * lcafr_L2 for ENOVIA_V5_VPM,
  * DMUfr_E2 for  ENOVIA_DMU_Navigator,
  * The name of the product line for a non DS product line [4]

The location of this directory in the documentation file tree depends on the language, it is explained by the [Fig.5]
![](../CAAIcons/images/hand.gif)The navigation page:

                 **5** | It is a HTML page which contains a navigation tool. This file is located in a directory whose name depends on the product line: icons<**BrandExtension** >.  **< BrandExtension>** represents the brand extension, it depends on the product line:  The following table presents the corresponding brand extension for each product line: |  Brand extension |        Product Line
---|---
_C2 |

  * CATIA_P3
  * CATIA_STUDENT
  * CATIA_PLM_Express

_D2 |

  * DELMIA

_W2 |

  * DELMIA_Automation

_O2 |

  * ENOVIA_3d_com

_L2 |

  * ENOVIA_V5_VPM

_E2 |

  * ENOVIA_DMU_Navigator

_V2 |

  * ENOVIA_CES

```vbscript
```vbscript
For a non DS product line, the name of this directory depends on the product line name: icons_<**ProductLineName** >. Refer to the  "What Is the Product Line Visual Identity" technical article [4], to find the name of the product line.

```

```

```vbscript
For a non DS product line, the name of this directory depends on the product line name: icons_<**ProductLineName** >. Refer to the  "What Is the Product Line Visual Identity" technical article [4], to find the name of the product line.
```

The location of this directory in the documentation file tree depends on the language, it is explained by the [Fig.5]

Note: this file is used only in contextual help.

The architecture of the documentation file tree is the following:

_Fig.5: Architecture of the Documentation File Tree _ ![](images/CAAAfrHOLDirectoryEnglish.jpg)

---
![](images/CAAAfrHOLDirectoryLang.jpg)

The documentation file tree contains at the first level the online and resources directories for the English version, and a directory for each non English version. The non English version directory contains itself the  resources and online directories. The contents of these two sub-directories is the following:

  * The **resources** sub-directory.

> This sub-directory always contains the **msgcatalog** directory. For the English version, this directory contains the mapping file, otherwise it contains a language directory containing the mapping file.

  * The **online** sub-directory.

> For the English version, the online directory contains:
>
>   * **module_xxx** : each directory which represents a logical grouping for a workbench, a solution, a product, etc. It contains the documentation files for the commands and the table of contents file (toc). The online directory can have several modules.
>

>
> ![](../CAAIcons/images/warning.gif) The names of these modules mustn't include the '_' character.
>
>   * **image** : The images used in the documentation files.
>   * **ProductLineName** : the directory which contains the banner file of the product line and the banner of each module.
>   * ![](../CAAIcons/images/hand.gif)**icons_xxx** : the directory which contains the no_navigation.md file.
>

>
> For a non English version, between the online directory and all these above directories there is the language directory.

Refer you to the "Contextual Help for an Add-on" use case [6] for an example.

[Top]

* * *
### In Short

This article has demonstrated how to create a documentation directory and described the mechanisms for a contextual help.

[Top]

* * *
### References

[1] | [The CAA Command Model](../CAADegTechArticles/CAADegCommandModel.md)
---|---
[2] | [Creating Resources for Command Headers](CAAAfrI18NHeader.md)
[3] | [Application Property Access](../CAACafTechArticles/CAACafToolsOptions.md)
[4] | [What Is the Product Line Visual Identity](CAAAfrVisualIdentity.md)
[5] | [Creating a Product Line Visual Identity](../CAAAfrUseCases/CAAAfrSampleVisualIdentity.md)
```cpp
[6] | [Contextual Help for an Add-On](../CAAAfrUseCases/CAAAfrSampleContextualHelpCATIA.md)
[Top]
```

* * *
### History

Version: **1** [Mar 2002] | Document created
---|---
Version: **1** [Mar 2002] | Document created
Version: **2** [Nov 2002] | Document updated
Version: **3** [Jan 2003] | Document updated
Version: **4** [Nov 2007] | Document updated
Version: **5** [Sep 2008] | Document updated
Version: **6** [Oct 2014] | Review

[Top]

* * *

_Copyright 2002, Dassault Systmes. All rights reserved._
