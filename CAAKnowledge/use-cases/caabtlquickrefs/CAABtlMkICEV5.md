---
title: "mkICE"
category: "use-case"
module: "CAABtlQuickRefs"
tags: "["CAADialog"]"
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkICEV5.htm"
converted: "2026-05-11T17:33:49.991364"
---
tags: ["CAADialog"]
source_file: "Doc/online/CAABtlQuickRefs/CAABtlMkICEV5.htmmd"
converted: "2026-05-11T17:33:49.991364"
RADE |  Multi-Workspace Application Builder |  mkICE Edit XML ID cards

converted: "2026-05-11T17:33:49.991364"
RADE |  Multi-Workspace Application Builder |  mkICE Edit XML ID cards
Quick Reference

* * *

Abstract This article explains how to use the mkICE command to edit your framework Identity Cards XML files.
      * Synopsis
      * Usage
      * Options
      * Example
      * In Short
---
Synopsis **mkICE** [**-f** XMLfile] [**-F** FW ] [**-c** Cmp] [**-h** | **-help** | **-?**] Usage mkICE (Identity Card Editor) is an IdentityCard.xml graphic editor, providing contextual help and check. ![mkICE dialog window](images/CAABtlmkICE01V5.png) The mkICE window is made up of three panes:
      1. A tree pane showing the XML element nesting as nodes in a tree.
      2. A property pane displaying the  properties of the selected element in the tree
      3. An Error and warning pane
mkICE allows you to add a new elements, at the bottom of the tree, or before or after a given one. Depending on the context and the type of the IdentityCard, a menu proposes the list of available keywords. When selecting an element, the property panel displays all possible attributes for the selected element, with drop down list when the possible values are constrained. **Notes** :
      1. Attributes with an empty value are not copied to the XML file. To specify an attribute, specify a non empty value. To remove an attribute, specify an empty value.
      2. The model modification is only done when leaving the control area.
      3. mkICE is level dependent. You need to use the editor from the proper level of tools to edit an IdentityCard.
During edition, the XML document is checked against the XSD. If any error occurs, the result can be seen in the `Error and warning` pane. [Top] Opening an IdentityCard.xml File To open an existing IdentityCard.xml, click on File>Open or use the shortcut Ctrl o Opening an IdentityCard.h File You can open an IdentityCard.h (File>Open from .h), this will transform the .h to .xml (using mkIC2xml). The rest of the edition will be on the .xml only. Managing Prerequisites You can add and remove prerequisite frameworks, or modify the access mode of a prerequisite framework. Adding a Prerequisite Framework at the Bottom of the Tree
      1. Right click the `codeFramework` root node.
      2. In the contextual menu, point to `Add children`, and click ` prerequisite`. A prerequisite node is added in red at the bottom of the tree.
      3. Click this added prerequisite node. The right pane displays the possible attributes of a prerequisite framework.
      4. In the `name` box, type the name of the framework to set as prerequisite.
      5. In `access`, select the prerequisite framework access mode. Valid values are `Public`, `Protected`, and `Private`. Always select `Public` for an framework installed from the API CD-ROMs.

[Top] Adding a Prerequisite Framework Before or After a Given Node
2. In the contextual menu, point to `Add children`, and click ` prerequisite`. A prerequisite node is added in red at the bottom of the tree.
3. Click this added prerequisite node. The right pane displays the possible attributes of a prerequisite framework.
4. In the `name` box, type the name of the framework to set as prerequisite.
5. In `access`, select the prerequisite framework access mode. Valid values are `Public`, `Protected`, and `Private`. Always select `Public` for an framework installed from the API CD-ROMs.
      1. Right click the node in the tree.
      2. In the contextual menu, point to `Add sibling after` to add prerequisite framework after that node, or to `Add sibling before` to add it before that node, and click `prerequisite`. A prerequisite node is added in red after or before the node depending on you choice.
      3. Click this added prerequisite node. The right pane displays the possible attributes of a prerequisite framework.
      4. In the `name` box, type the name of the framework to set as prerequisite.
      5. In `access`, select the prerequisite framework access mode. Valid values are `Public`, `Protected`, and `Private`. Always select `Public` for an framework installed from the API CD-ROMs.

[Top] Removing a Prerequisite Framework
2. In the contextual menu, point to `Add sibling after` to add prerequisite framework after that node, or to `Add sibling before` to add it before that node, and click `prerequisite`. A prerequisite node is added in red after or before the node depending on you choice.
3. Click this added prerequisite node. The right pane displays the possible attributes of a prerequisite framework.
4. In the `name` box, type the name of the framework to set as prerequisite.
5. In `access`, select the prerequisite framework access mode. Valid values are `Public`, `Protected`, and `Private`. Always select `Public` for an framework installed from the API CD-ROMs.
      1. Right click the node corresponding to the prerequisite framework to delete in the tree.
      2. In the contextual menu, click `Delete`. The prerequisite framework is removed from IdentityCard.xml file.

[Top] Modifying a Prerequisite Framework Access Mode
5. In `access`, select the prerequisite framework access mode. Valid values are `Public`, `Protected`, and `Private`. Always select `Public` for an framework installed from the API CD-ROMs.
1. Right click the node corresponding to the prerequisite framework to delete in the tree.
2. In the contextual menu, click `Delete`. The prerequisite framework is removed from IdentityCard.xml file.
      1. Click the node corresponding to the prerequisite framework to manage in the tree.
      2. In `access`, select the new prerequisite framework access mode.

[Top] Managing Framework Build You can declare a framework to be built or not, or to be not built for one or several operating systems only. Declaring a Framework Build
2. In the contextual menu, click `Delete`. The prerequisite framework is removed from IdentityCard.xml file.
1. Click the node corresponding to the prerequisite framework to manage in the tree.
2. In `access`, select the new prerequisite framework access mode.
      1. Right click the `codeFramework` root node, in the contextual menu, point to `Add children`, and click `built` or Right click a node, in the contextual menu, point to `Add sibling after` to add the build directive after that node, or to `Add sibling before` to add it before that node, and click `built`. A `built` node is added in red in the tree.
      2. Click this added `built` node. The right pane displays the possible attributes of a `built` node.
      3. In the `value` box, select true to build the framework on all available operating systems, or false to prevent this framework from being built on any operating systems.
      4. On the `File` menu, click `Save`.

[Top] Preventing a Framework from Being Built on Certain Operating Systems
1. Right click the `codeFramework` root node, in the contextual menu, point to `Add children`, and click `built` or Right click a node, in the contextual menu, point to `Add sibling after` to add the build directive after that node, or to `Add sibling before` to add it before that node, and click `built`. A `built` node is added in red in the tree.
2. Click this added `built` node. The right pane displays the possible attributes of a `built` node.
3. In the `value` box, select true to build the framework on all available operating systems, or false to prevent this framework from being built on any operating systems.
4. On the `File` menu, click `Save`.
      1. Click the `built` node.
      2. In the `value` list, select `false`.
      3. In the `osConstraint` box, type the operating systems for which you do not want to build the frameworks. See [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md) to know the list of supported operating systems and the possible values to add in the `osConstraint` box, such as intel_a for Windows 32-bit or win_b64 for Windows 64 bit.
      4. On the `File` menu, click `Save`.
 Shortcut

2. In the `value` list, select `false`.
3. In the `osConstraint` box, type the operating systems for which you do not want to build the frameworks. See [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md) to know the list of supported operating systems and the possible values to add in the `osConstraint` box, such as intel_a for Windows 32-bit or win_b64 for Windows 64 bit.
4. On the `File` menu, click `Save`.
Shortcut
Open file | Ctrl+O
Save | Ctrl+S
Delete the selected element | backspace
Copy | Ctrl+C
Cut | Ctrl+X
Paste | Ctrl+V
Comment/uncomment selected element | Alt+C
Undo | Ctrl+Z
Redo | Ctrl+U

[Top] Options mkICE accepts the following options: Option | Description
---|---
`-c `Cmp | Process a file the name of which is not IdentityCard.h. **Internal**.
`-f XMLfile` | Open the XML file XMLfile.
`-F FW` | Open the XML Identity Card of the framework FW. The command must be run at the workspace root.
`-h|-help|-?` | Display the command help.
[Top] Example Open mkICE.

    >cd MyWorkspace
    >mkICE

Open mkICE with a framework Identity Card already in XML.

    >cd MyWorkspace
    >mkICE -F CAADialog.edu

Open mkICE with an explicitly designated IdentityCard XML file.

    >cd MyWorkspace
    >mkICE -f CAADialog.edu/IdentityCard/IdentityCard.xml

[Top] In Short This article gives you mkICE usage instructions. History Version: **1** [Jun 2011] | Document created
---|---
[Top] _Copyright 2013, Dassault Systmes. All rights reserved._
