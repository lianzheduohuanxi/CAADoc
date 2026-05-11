---
title: "About VB, VBA, Debug, and Portability"
category: "use-case"
module: "CAAScdInfTechArticles"
tags: ["CATIA"]
source_file: "Doc/online/CAAScdInfTechArticles/CAAInfHints.htm"
converted: "2026-05-11T17:31:52.415555"
---
## Infrastructure
 
 | 
 ## About VB, VBA, Debug, and Portability  
   
   
 * * *
 ## Tips about VB and VBA
 
 Since V5R7 Dassault Systemes products based on the V5 Platform don't use anymore the Basic Script scripting engine on Unix platforms. The `CATScript` language has been kept for compatibility and is processed by a vbscript scripting engine after removal of the typing information.
 
 This has no impact on macros but you may still experience the following problem when recording macros in `CATScript` language and copy/pasting the result in a VB/VBA project . 
 
 The typing requirement are incompatible for Basic Script code and VB code. When a **method returns an abstract object** like the **ActiveDocument** method that returns a **Document** ,**** Basic Script expects the variable in which the return value will be stored to be of the type declared by the signature of the method:

> Dim oDoc As Document
```vbscript
    Set oDoc = CATIA.ActiveDocument ' returns a Document
 
```

 If this document is a **PartDocument** you can then use specific methods or properties like the Part property that does not exist on the general **Document** but only on the **PartDocument** :

> Dim oPart As Part
```vbscript
    Set oPart = oDoc.Part
 
```

 When using VB, you will need a PartDocument object to use the Part property:

> Dim oDoc As **Part** Document
```vbscript
    Set oDoc = CATIA.ActiveDocument ' returns a Document
    
    Dim oPart As Part
    Set oPart = oDoc.Part
 
```

```vbscript
 For documentation examples, we choose as much as possible a VBScript/Basic Script portable syntax. So, when copy/pasting samples from the documentation in a VB project, you will have to proceed to take care of virtual objects.
 
```

 You will also have to take care of **methods with array parameters** like in the following example where we extract and display the multiple possible values of a **StringParameter** in VBScript or BasicScript:

> Dim strParam1 As StrParam
```vbscript
    Set strParam1 = parameters1.Item("STRING")
    
```

    iSize = strParam1.GetEnumerateValuesSize()
    
    Redim myArray(iSize-1)
    strParam.GetEnumerateValues myArray
    
```vbscript
    For i = 0 To iSize-1
        msgbox myArray(i)
    Next
 
```

 Copy/pasting this piece of code in a VB project may lead, depending on your VB/VBA level to a compilation error because VB may be unable to deal with the signatures that we use for our array types and issues the following message:

> `Function or interface marked as restricted, or the function uses an automation type not supported by Visual Basic.`
 
 A simple workaround is to un-type the variable on which the method is applied.

> Dim strParam1 ' **As StrParam** 
```vbscript
    Set strParam1 = parameters1.Item("STRING")
    
```

    iSize = strParam1.GetEnumerateValuesSize()
    
    Redim myArray(iSize-1)
    strParam.GetEnumerateValues myArray
    
```vbscript
    For i = 0 To iSize-1
        msgbox myArray(i)
    Next
    
```

 
 When the array is the only argument of a method, the following syntax, using parenthesis, should be avoided:

> Redim myArray(15)
    strParam.GetEnumerateValues (myArray)
    
 
```vbscript
 For methods that are not functions (meaning that they do not have a return value), this syntax requires to pass the argument by reference which may not work in some cases. The right syntax uses either no parenthesis:

```

> strParam.GetEnumerateValues myArray
 
 or the **call** keyword: 

> call strParam.GetEnumerateValues (myArray)
    
 
```
 ## Script Debugger
 
 When developing in-process macros, you can use Microsoft (R) Script Debugger than you can download freely from Microsoft (R) web site. Once installed, an error or a **Stop** order in the script will give hand to the debugger:

> For i = 0 To Ubound(myArray)
        **Stop**
        msgbox myArray(i)
    Next
 
 See the Script Debugger's documentation for more information on how to proceed.
 ## Portability
 
 On windows  platform, CAA V5 scripting capability relies on the VBScript engine provided by the platform and requires VBScript 5.0 as a minimum level. On Unix platforms, a VBScript 3.0 engine is installed when the Version 5 is installed.
 
 Portable macros must so avoid usage of VBScript features that appeared after version 3.0 of the language. Information on version in which VBscript language elements appeared can be found in the scripting section of the Microsoft Developers Network site.
 
 The [ CAA V5 Automation Coding Rules](../CAAScrTechArticles/CAAScrScriptCodingRules.md) Technical Article contains portability rules that describe in more details a few points that must also be considered to write portable code.
 
 [Top]
 ## Inter releases compatibility
 ### Virtual Function Tables compatibility
 
 The CAA V5 Automation Object Model evolves with each new release. The list of the methods of an object may change. Depending on the way VB or VBA calls those methods this may have an impact on your application even if a new method has been added. 
 
 The following code for example:

> Dim oObject
    oObject.DoThis
    
 
 Where oObject is not typed, will perform a late binding call to _DoThis_ , using the _Invoke_ method at build time and leaving _oObjet_ perform the actual call to _DoThis_ at runtime inside its implementation of _Invoke_. The following code however:

> Dim oObject  **As**  SpecificTypeOfObject
    oObject.DoThat
    
 
 will perform an early binding call, meaning basically that a description of the virtual function table of _oObject_ will be re-created from the information available in the type library describing the _SpecificTypeOfObject_ type and the call will be made using a position in this table. 
 
 If, on a new release, the order of methods in this virtual function table changes, which may be the case when adding new methods, the application will call the wrong method leading to difficult-to-debug runtime problems. 
 
 Moreover, the description extracted by VB/VBA from the type library doesn't seem to be always refreshed when the type library changes. Meaning that recompiling the project may not correct the problem. Here is a method that solves this problem:
 
     * open you VB or VBA project 
     * remove all references to V5 type libraries using the _Project/References_ or _Tools/References_ menu items. 
     * save and close the project 
     * re-open the project and add again the needed references. 
 ### Obsolete Typelibs
 
 Some type libraries may become obsolete and disappear on a new V5 release. If an existing VBA project has references on a type library that doesn't exist anymore. If your access rights allow you to modify the Windows Registry, references to those libraries are automatically removed when opening the CATVBA file. If it's not the case, the following message may be experienced when launching a macro:

> CNEXT CATScriptError Message Scripting ERR_1000   
          
          Execute the script "XXXXX" |XXXXX=  
          
          The script entry point could not be found.  
          
          XXXXX  
          
          Define a "CATMain" procedure which will be the entry point of the script.  
          
          
          
 
 To avoid this, launch VBA (Alt-F11) and use the _Tools/References_ menu item to launch the _References_ panel. In this panel, uncheck the reference to the concerned type library and click on OK. 
 
 This problem may also occur in VBA project of non V5 applications.
 ### Running Two Versions or Releases on the Same Machine
 
 You may need to run two, for example, CATIA or DELMIA versions on the same machine. For example, you want to run V5R27 and V5R28, or V5R27 and **3D** EXPERIENCER2017x. If you want to run macros, note that CATIA or DELMIA use a scripting server associated with a given version/release, and so you cannot concurrently run macros in two different CATIA or DELMIA application windows running two different versions.
 
 To switch running macros from one version to another one, say from V5R27 to **3D** EXPERIENCER2017x, do the following:
 
     * Close all CATIA or DELMIA windows.
     * Unset the V5R27 scripting server: 
       1. Open a prompt window in administrator mode.
       2. Change to the folder in which you installed CATIA or DELMIA.
 
 By default, this folder is:
 
 `C/Program Files\Dassault Systemes\B27\win_b64\code\bin`
 
 Replace `win_b64` with `intel_a` if you run a 32 bit version.
 
       3. Run the following command: 
              
              catstart -run "V5RegServer -unset CATIA"
 
       4. This command is a silent command. Wait about for one minute to let it complete.
     * Set the **3D** EXPERIENCER2017x scripting server: 
       1. Open a prompt window in administrator mode.
       2. Change to the folder in which you installed CATIA or DELMIA.
 
 By default, this folder is:
 
 `C/Program Files\Dassault Systemes\B419\win_b64\code\bin`
 
 Replace `win_b64` with `intel_a` if you run a 32 bit version.
 
       3. Run the following command:
              
              catstart -run "DSYAdmRegSrv -set CATIA" [ -env MyV6Environment -DirEnv MyV6EnvDirectory]
 
       4. This command is a silent command. Wait about for one minute to let it complete before starting CATIA or DELMIA V6R2011.
 
 To unset a V6/**3D** EXPERIENCE scripting server, use the -unset option of the DSYAdmRegSrv command. In the same way, to set a V5 scripting server, use the -set option of the V5RegServer command.
 
 In V5 many environment files can be created in any folders, so it is recommended to use the `-end` and the `-direnv` options. In V6/**3D** EXPERIENCE only one environment file is created at installation time and is located in the CATEnv folder of the installation folder, so those options can be omitted unless you are using Apps created with the CAA C++ API.
 ###  Support of boolean type in CATVBA
 
 There is a known limitation concerning the usage of the Boolean type in the V5 Automation methods invoked from VBA. In V5 applications, the Boolean type  
is defined as an 'unsigned char' where the VBA definition is a short. When a V5 method returns True, the returned integer value is 1, though VBA is expecting -1. Because of this difference, the following VBA code will not work as expected (the method boolMethod returns True):

> `If myObj.boolMethod() = True Then // This test will fail  
...  
End If `
 
```

 to correct this limitation, you have to write some code like this :

> `If myObj.boolMethod() Then End If `
 
 or

> ` If myObj.boolMethod() != False Then   
...  
End If `
 
```

```vbscript
 For the same reason, the 'Not' operator cannot be applied directly on the returned value of such method:

```

> `Not(myObj.boolMethod())`
 
 will return True instead of returning False. To use correctly the 'Not' operator you have to use a variable to store the boolean value before applying the operator : 

> `Dim myBool  
myBool = myObj.boolMethod()  
Not(myBool) `
 
 will correctly return False  

 
 Note that this limitation is specific to VBA and is not concerning VBScript.
 
 Another very specific problem may occur when using a VBA class featuring a function that returns a boolean. In the following example:
     
```vbscript
     Sub CATMain()
```vbscript
         Dim oClass1 As Class1
         Set oCLass1 = New Class1    
         Dim bReture As Boolean
         bReture = oClass.IsRetureBooleanFunction()
         
         Dim RefreshDisp As Boolean
         CATIA.RefreshDisplay = False
         RefreshDisp = CATIA.RefreshDisplay
         Debug.Print " CASE FALSE : False expected=" & CInt(False) & " False returned=" & CInt(RefreshDisp)
         CATIA.RefreshDisplay = True
         RefreshDisp = CATIA.RefreshDisplay
         Debug.Print " CASE TRUE : True expected=" & CInt(True) & " True returned= " & CInt(RefreshDisp)
     End Sub
     
```

 
 The class `Class1` offers the `IsRetureBooleanFunction` function:
     
```vbscript
     Function IsRetureBooleanFunction() As Boolean
         IsRetureBooleanFunction = True
     End Function
     
```

 
 The execution of `CATMain` shows that the value returned by `CATIA.RefreshDisplay` is always invalid. A simple workaround consists in declaring the `IsRetureBooleanFunction` function this way:
     
```vbscript
     Function IsRetureBooleanFunction() As **Variant**
         IsRetureBooleanFunction = True
     End Function
     
```

 ### Limitation for VBA in a 64 bit context when a macro program declares a function
 
 The following kind of declaration:

> ` Private Declare Function MyFunctionNameInDll Lib "E/My.dll" (...) As ...`
 
 is not possible in a 64 bit context if the `My.dll` is a 64 bit dll. The V5 VBA integration for 64 bit applications is based on a separate 32 bit application dedicated to VBA. A DLL referenced by a VBA macro must so be a 32 bit one. Moreover, such a 32-bit dll cannot use the dlls from the V5 installation that are, in that case, 64 ones. 
 ### Usage if the VBA DoEvent function
 
 The general purpose of the VBA function `DoEvent` is to allow the System to manage input events so that the UI becomes more responsive.
 
 Beside this function is generally dangerous because it can generate unexpected reentrancy. CATIA infrastructure is not architectured to manage event treatment while the process is blocked into a VBA macro execution. Calling `DoEvent` while a macro is executed can so lead to unpredictable behavior.
 
 Using `DoEvent` in VBA macros is not recommended.
 
 * * *
 
 _Copyright 1999-2017, Dassault Systmes. All rights reserved._

```