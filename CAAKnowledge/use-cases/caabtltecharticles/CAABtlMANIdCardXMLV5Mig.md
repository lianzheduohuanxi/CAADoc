---
```vbscript
title: "Migrating Your Identity Cards to XML"
category: "use-case"
module: "CAABtlTechArticles"
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANIdCardXMLV5Mig.htm"
converted: "2026-05-11T17:33:46.071110"
```

---
tags: []
source_file: "Doc/online/CAABtlTechArticles/CAABtlMANIdCardXMLV5Mig.htm"
converted: "2026-05-11T17:33:46.071110"
RADE |  Multi-Workspace Application Builder |  Migrating Your Identity Cards to XML _From .h to .xml_

converted: "2026-05-11T17:33:46.071110"
RADE |  Multi-Workspace Application Builder |  Migrating Your Identity Cards to XML _From .h to .xml_
Technical Article

* * *

Abstract The **IdentityCard** file is encoded in XML starting with V6R2012x. The IdentityCard.h format is still supported, but you are strongly encouraged to migrate your Identity Cards to XML. You can migrate your Identity Card files using either mkICE or mkIc2Xml.

  * Using mkICE
  * Using mkIc2Xml
  * References

---
Using mkICE

Using mkICE
  1. In a command prompt located at the root folder of your workspace and initialized with the appropriate TCK using the tck_init and tck_profile commands, type mkICE [2]. The `Identity Card Editor` dialog window opens.
  2. On the `File` menu, click `Open from .h`. The `Open` dialog box opens.
  3. Navigate you workspace to find the IdentityCard.h file to migrate and click `Open`. The IdentityCard.h file content is converted to XML and displayed.
  4. On the `File` menu, click `Save`. The IdentityCard.xml is saved.
  5. Delete the IdentityCard.h file.

[Top] Using mkIc2Xml

4. On the `File` menu, click `Save`. The IdentityCard.xml is saved.
5. Delete the IdentityCard.h file.
  1. In a command prompt located at the root folder of your workspace and initialized with the appropriate TCK using the tck_init and tck_profile commands, type mkIc2Xml followed by the names of your frameworks [3]. For example:

         >ls *\IdentityCard\*.h
         A.edu/IdentityCard/IdentityCard.h  A.tst/IdentityCard/IdentityCard.h  A/IdentityCard/IdentityCard.h
         >**mkIc2Xml A A.edu A.tst**
         == Starting generation: 3 framework(s) to do
A.edu/IdentityCard/IdentityCard.h  A.tst/IdentityCard/IdentityCard.h  A/IdentityCard/IdentityCard.h
         A Done [1/3]
         A.edu Done [2/3]
         A.tst Done [3/3]

         == Generation done
         >ls *\IdentityCard\*.xml
A Done [1/3]
A.edu Done [2/3]
A.tst Done [3/3]
         A.edu/IdentityCard/IdentityCard.xml  A.tst/IdentityCard/IdentityCard.xml  A/IdentityCard/IdentityCard.xml

  2. Delete the IdentityCard.h files of you frameworks.

[Top] References [1] |  Framework Architecture Rules
---|---
[2] | [mkICE](../CAABtlQuickRefs/CAABtlMkICEV5.md)
[3] | [mkIc2Xml](../CAABtlQuickRefs/CAABtlMkIc2XmlV5.md)
History Version: **1** [Jun 2011] | Document created
---|---
[Top] _Copyright 2013, Dassault Systmes. All rights reserved._
