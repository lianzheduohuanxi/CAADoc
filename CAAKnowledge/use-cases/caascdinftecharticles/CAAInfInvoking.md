---
```vbscript
title: "Invoking CATIA from a Scripting Language"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfInvoking.htm"
converted: "2026-05-11T17:31:52.420050"
```

---
## Infrastructure

 |
 ## Invoking CATIA from a Scripting Language

 * * *

 Access to the CATIA object model is provided using scripts in different ways depending on the operating system and on the applications that can share their own objects with CATIA. This also applies for ENOVIA DMU and DELMIA products. In the following you can subsitute "DMU" or "DELMIA" to "CATIA" if you need to access or launch another application based on the common V5 platform.

Access to the CATIA object model is provided using scripts in different ways depending on the operating system and on the applications that can share their own objects with CATIA. This also applies for ENOVIA DMU and DELMIA products. In the following you can subsitute "DMU" or "DELMIA" to "CATIA" if you need to access or launch another application based on the common V5 platform.
 CATIA is an OLE Automation server for Windows and allows macro record and replay for both Windows and UNIX. The following summarizes CATIA scripting capabilities.

 With Windows: |

     * In-process access using Visual Basic Scripting Edition or Visual Basic for Application since CATIA hosts both scripting engines.
     * Out-process access from the following OLE Automation clients:
       * Visual Basic for Applications via other applications like those of Office
       * Windows Scripting Host and scripting languages such as VB Script or JScript
       * an a html page.
 ---|---
 With UNIX: |
     * in-process access using Visual Basic Scripting Edition.

 The macros recorded from the Tools menu and the Record Macro dialog box can use:

     * the VBScript language,
     * the VBA language
     * the CATScript language. This CATIA specific language was designed to allow compatibility between the Unix Basic Script engine and the Windows VBScript engine. As CATIA doesn't anymore hosts the Basic Script engine on Unix since V5R7, it has only been kept for compatibility purpose. It is actually processed by a VBScript engine after removal of the typing information.

 In-process access means that the script interpretation is performed in the same process as CATIA. You usually run the macros from the Macros window triggered from the interactive **Tools- >Macros** command. In this case, the macro is processed by CATIA just like any other command.

In-process access means that the script interpretation is performed in the same process as CATIA. You usually run the macros from the Macros window triggered from the interactive **Tools- >Macros** command. In this case, the macro is processed by CATIA just like any other command.
 Out-process access means that you run the macro from another application running in another process. In this case, the macro should first connect to CATIA to then access its data. This connection starts CATIA if no CATIA process is being running.

 You can find information about in-process and out-process access in:

     * **Running In-process Macros**
     * **Running Out-process Macros**
 ### Running In-process Macros

 In-process access means that the script interpretation is performed in the same process as CATIA using the scripting engine(s) hosted by CATIA. You can run in-process macros with UNIX and Windows. You have three means to run in-process macros:

In-process access means that the script interpretation is performed in the same process as CATIA using the scripting engine(s) hosted by CATIA. You can run in-process macros with UNIX and Windows. You have three means to run in-process macros:
     1. You usually run the macros from the Macros window triggered from the interactive **Tools- >Macros** command. In this case, the macro is processed by CATIA just like any other command.
Note that you can add arguments to the ` CATMain` function:

            Sub CATMain(X, Y)
```vbscript
                ' Here we expect X as a scalar and Y as an object
```

                MsgBox X  & TypeName(Y)
```vbscript
              End Sub

```

MsgBox X  & TypeName(Y)
End Sub
 When launching such a macro, a dialog windows will request valuation of arguments.

 ![](images/CAAScdInfMacArgs.gif)

 Note that even if you use a macro language allowing to type to those arguments, the types won't be user at runtime, so it is recommended to give an explicit name to the variable to avoid end-user mystakes:

```vbscript
            Sub CATMain(iThisNumber, oThatObject)

Sub CATMain(iThisNumber, oThatObject)
```

     2. You can start CATIA and request that a macro being executed as soon as CATIA is started using the -macro option followed by the full path of the macro you want to run:

            CNEXT -macro E/Users\Macros\MacroToRun.CATScript

 This runs the `CATMain` function defined in the `MacroToRun.CATScript` file. Macros can however be stored in other macro libraries like `catvba` documents or any other V5 documents like `CATPart` or ` CATProduct` documents. You can use the following syntax to run the ` CATMain` function defined in the `myMacro` macro of the ` myDocument` document:

            CNEXT -macro myDocument.catvba myMacro
            CNEXT -macro myDocument.CATPart myMacro

 CATIA sessions launched this way will remain active after the end of the macro unless you explicitly end it in the macro using the `CATIA.Quit` method.

     3. You can start CATIA in batch to execute a macro using the -batch option followed by the full path of the macro you want to run:

            CNEXT -batch -macro E/Users\Macros\BatchMacro.CATScript

 this generally improves performances by avoiding visualization refreshes. Any syntax of the `-macro` option can be used with the `-batch` option. CATIA sessions launched this way will end by itself after the execution of the macro.

 ### Running Out-process Macros

this generally improves performances by avoiding visualization refreshes. Any syntax of the `-macro` option can be used with the `-batch` option. CATIA sessions launched this way will end by itself after the execution of the macro.
 Out-process access means that you run the macro from another application running in another process, such as from Visual Basic for Applications associated with products such as Excel or Word. You can also use the Windows Scripting Host to run VBScript or JScript macros by simply double clicking the macro name from the Windows desktop or Explorer, or from the command console. You can finally use VBScript or JScript macros embedded in html pages.

 The macro should first connect to CATIA to then access its data. This connection starts CATIA if no CATIA process is being running. The script is interpreted by the scripting engine hosted by the application from which you start the macro.

 You can run out-process macros with Windows only.

 #### Running Out-process Macros from VBA

The macro should first connect to CATIA to then access its data. This connection starts CATIA if no CATIA process is being running. The script is interpreted by the scripting engine hosted by the application from which you start the macro.
You can run out-process macros with Windows only.
 You can use the following syntax when using or Visual Basic for application

     * If CATIA is already running, the macro should simply connect to CATIA using the **GetObject** method

```vbscript
```vbscript
           Dim CATIA As Object

               Set CATIA = GetObject(, "CATIA.Application")

```

```

 The first argument is left blank.

     * If CATIA is not already running, the macro should start CATIA using the **CreateObject** method

> Dim CATIA As Object

```vbscript
```vbscript
        Set CATIA = CreateObject("CATIA.Application")

```

```

 #### Running Out-process Macros Using the Windows Scripting Host

```vbscript
Set CATIA = CreateObject("CATIA.Application")
 Another way is to use the Windows Scripting Host. This is a language-independent scripting host which enables scripts written in different languages such as Visual Basic, JScript, and Perl, to be run from the Windows desktop, the Windows Explorer, or the command console.

```

 With Visual Basic, your script should begin by the connection to CATIA, using either CreateObject or GetObject, as follows:

> Dim CATIA
```vbscript
```vbscript
    Set CATIA = WScript.CreateObject("CATIA.Application")

```

```

 or

> Dim CATIA
```vbscript
```vbscript
    Set CATIA = WScript.GetObject("", "CATIA.Application")

```

```

```vbscript
Set CATIA = WScript.GetObject("", "CATIA.Application")
 Note that the GetObject method requires that its first argument be blank.

```

 To run the macros from the Windows desktop, simply double click on the macro name. These names are suffixed using vbs for Visual Basic.

 ![](images/CAAInfExplorer.jpg)

To run the macros from the Windows desktop, simply double click on the macro name. These names are suffixed using vbs for Visual Basic.
 To run the macros from the command console, use the **cscript** command as follows:

     cscript e/users\psr\Scripting\Sample\CATIA.vbs

 #### Running Out-process Macros from a Dynamic HTML Page

To run the macros from the command console, use the **cscript** command as follows:
cscript e/users\psr\Scripting\Sample\CATIA.vbs
 You can also run macros VBScript macros embedded in a html page. There are several ways of embedding a macro in a html page:

     * The macro is written using the script tag and run when the page is loaded
     * The macro is written using the script tag and is included or referenced by a form, input, body, or a (anchor) tag.
     * The macro is written using the a tag (anchor) and run as an hyperlink. This is possible with JScript only but a VBScript function can be called by the JScript function.

 [Top]

 * * *

 _Copyright 1994-2004, Dassault Systmes. All rights reserved._
