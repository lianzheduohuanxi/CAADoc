---
```vbscript
title: "mkCreateIC"
category: "use-case"
module: "CAABtlQuickRefs"
tags: ["CAADialog"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkCreateICV5.htm"
converted: "2026-05-11T17:33:49.959860"
```

---
tags: ["CAADialog"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkCreateICV5.htm"
converted: "2026-05-11T17:33:49.959860"
RADE |  Multi-Workspace Application Builder |  mkCreateIC _Create an XML ID card_

converted: "2026-05-11T17:33:49.959860"
RADE |  Multi-Workspace Application Builder |  mkCreateIC _Create an XML ID card_
Technical Article

* * *

Abstract This article explains how to use the mkCreateIC command to create an empty framework Identity Cards to XML files.
      * Synopsis
      * Usage
      * Options
      * Example
      * In Short
---
Synopsis **mkCreateIC** [**-W** WSPath] [**-lFW** FWlist | FW1 [FW2 ...]] [**-cps**] [**-h** | **-help** | **-?**] Usage mkCreateIC is used to create a proper empty Identitycard.xml file for a new framework, given its type. Options mkCreateIC accepts the following options: Option | Description
---|---
`-cps` | Create component Identity Cards. **Internal**.
`-h|-help|-?` | Display the command help.
`-lFW FWlist` | Process the frameworks the names of which are listed in the file located at the path FWlist.
`-W WSPath` | Path of the workspace to process. Default is the current folder.
`FW1 [FW2 ...]` | Process frameworks FW1, FW2? etc.
Example Create an empty XML Identity Card for the CAADialog.edu framework.

    >cd MyWorkspace
    >mkCreateIC CAADialog.edu

The empty XML Identity Card created looks like this:

    <?xml version='1.0' ?>
    <eduFramework xmlns = "http://www.3ds.ic"
The empty XML Identity Card created looks like this:
                  xmlns:xsi = "http://www.w3.org/2001/XMLSchema-instance"
                  xsi:schemaLocation = "http://www.3ds.ic ICModel.xsd"

    />

[Top] In Short In this article you have learnt how to create new IdentityCard.xml without using copy paste. History Version: **1** [Jun 2011] | Document created
---|---
[Top] _Copyright 2013, Dassault Systmes. All rights reserved._
