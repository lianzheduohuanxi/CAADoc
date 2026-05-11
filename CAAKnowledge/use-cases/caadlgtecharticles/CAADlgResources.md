---
```vbscript
title: "Assigning Resources to a Dialog Box"
category: "use-case"
module: "CAADlgTechArticles"
tags: ["CATIconPath", "CAADegPointErrorBox", "CAADlgMoreButtonDlg", "CATIA"]
source_file: "Doc/online/CAADlgTechArticles/CAADlgResources.htm"
converted: "2026-05-11T17:17:56.085439"
```

---
# 3D PLM Enterprise Architecture

|
## User Interface - Dialogs

|
### Assigning Resources to a Dialog Box

_How to use external resources for the texts, messages, icons, and pictures_
---|---|---
Technical Article

* * *
### Abstract

When you develop a client application, you need to deal with menus, dialog boxes, prompts, messages, and icons, and to ensure that the texts are enabled to be translated later on in any language your customers may want, without changing any line of code, and without the need to recompile the application. This article gives you information on how the resources are processed, and how to create your dialog objects with everything they do provide to match internationalization and localization needs from the very beginning.

  * **Internationalization and Localization**
  * **Internationalization Resources and Coding Process**
  * **Internationalizing Dialog Boxes**
  * **Understanding Resource Inheritance and Concatenation**
  * **Inter****nationalizing Text**
  * **In Short**
  * **References**

---

* * *
### Internationalization and Localization

Even if your don't know if your client application will be used abroad and by people of a different culture and speaking a language different from yours, it is always easier, safer, and cheaper to design and code it as if it should be. Internationalizing a client application means that no assumptions are made about the language, and more generally the locale, used to run your application when you design and code it. When such an application is presented in front of end users from different countries, the same look and feel, and the same functions, are expected whatever the language and locale used. The localized versions of the application should then behave as the version in the original language.

Even if your don't know if your client application will be used abroad and by people of a different culture and speaking a language different from yours, it is always easier, safer, and cheaper to design and code it as if it should be. Internationalizing a client application means that no assumptions are made about the language, and more generally the locale, used to run your application when you design and code it. When such an application is presented in front of end users from different countries, the same look and feel, and the same functions, are expected whatever the language and locale used. The localized versions of the application should then behave as the version in the original language.
Internationalizing an application is also called National Language enabling. This means that the application should be designed and coded in such a way that it could be afterwards localized. Localizing means translating the user interface into the target languages, and possibly do some additional customization. The key point is that localization never requires to recompile any part of the application. To enable for that, any character string displayed in front of the end user must be located in a external text file.

CAA V5 is natively National Language enabled, that is includes all the necessary stuff for internationalization, and provides you with any tools and mechanisms to facilitate you internationalizing job.

[Top]
### Internationalization Resources and Coding Process

Assume that you need to create this dialog box.
---|---

The dialog box has a title and an Apply push button. If you want to display this, you should simply assign a title to the dialog box as the second parameter of its constructor [1], and a title to the push button using the `SetTitle` method.

    ...
      **SetTitle**("Button");
    ...
      _PButton = new CATDlgPushButton(this,"ThePushButton");
      _PButton->**SetTitle**("Apply");
    ...

---

_PButton->**SetTitle**("Apply");
That's nice and runs well. Nevertheless, if your application is also used by non-English speaking people, for example in France, changing the English character strings to their French equivalents needs to modify your code. You thus need to either manage two versions, one for English and one for French, or you need to supply your code to your customers to let them translate the titles and rebuild the application. None of these solutions is acceptable for both you and your customers. To overcome this issue, we'll simply create a message file to store these titles.

So, internationalizing a client application is a continuous process to execute along the application development, and NOT at the end. Whenever you need to display a title, a text, a character string, or a message, you should know what to do to enable for National Language. You will mainly deal with internationalization with the following:

  * The workshop and workbenches: dialog commands are there arranged in menus and toolbars. Any text to display about a command is NL enabled using the command header
  * The dialog commands: most of the texts are prompts, if we except dialog boxes
  * The dialog boxes: roughly all the controls feature at least a text, such as a push button or a label, or a set of texts, such as a combo or a selector list

To manage texts outside of the code, CATIA associates a resource file with dialog objects. These resource files are stored in the CNext directory of your framework in the development file tree, and are searched for in the directory corresponding to the operating system in the run time view, such as intel_a for Windows running on machines with Intel processors, or aix_a for machines running AIX. But resources are not limited to texts. For example, icons are considered as resources for the client application. They are found using the CATMsgCatalogPath environment variables.

A simple and handy mechanism enables you to simply associate to each class you create the external resource files required. One of these files contains all the strings to display which must be translated into languages, and its name is the class name suffixed by CATNls. The other contains all the strings to display which must not be translated into languages, and its name is the class name suffixed by CATRsc. These files are associated to the class thanks to the `DeclareResource` macro you should insert in the class header file.

    ...
    class MyDialogBox : public CATDlgDocument
    {
      **DeclareResource**(MyDialogBox, CATDlgDocument)
      public :
    ...

---

`DeclareResource `has two parameters: the current class, and its base class. This is due to resource inheritance. The files for this class are:

  * MyDialogBox.CATNls for strings which must translated into languages.
  * MyDialogBox.CATRsc for strings which must not be translated into languages.

The mechanism to find the text to display for a given dialog object aggregated by the class is the following: when a dialog object is instantiated by the `Build` method of the dialog box class, a name is passed as a parameter of its constructor. This name is used as an identifier for the dialog object to recognize it from the other dialog objects.

The message file directory is placed in the resources directory and named `msgcatalog`. It contains the message files for the English language and the resource files. Subdirectories are available for message files for other languages are, such as French or German.
---|---

The mechanism to find the text to display for a given dialog object aggregated by the class is the following: when a dialog object is instantiated by the `Build` method of the dialog box class, a name is passed as a parameter of its constructor. This name is used as an identifier for the dialog object to recognize it from the other dialog objects.
The message file directory is placed in the resources directory and named `msgcatalog`. It contains the message files for the English language and the resource files. Subdirectories are available for message files for other languages are, such as French or German.
The contents of the message files for the dialog box above are shown below MyDialogBox.CATNls. Their contents are shown below, for the English, French, and German languages respectively, along with a snapshot of the dialog box:

    Title               = "Button";
```vbscript
    ThePushButton.Title = "Apply";

```

    Title               = "Bouton";
```vbscript
    ThePushButton.Title = "Appliquer";

```

    Title               = "Schaltflche";
```vbscript
    ThePushButton.Title = "Anwenden";

```

The correspondence between the field to fill in and the text used to fill in this field is ensured by the key placed in the file.

```vbscript
```vbscript
For example, the text that appears in the title bar of the dialog box, that is "Button" in English, is set using the `SetTitle` method. This method applies to `this`, instance of the dialog box. To this method applied to that instance corresponds the Title key in the file. Now let's consider the push button. It is created as the child of the window, since it has `this` as first parameter of its constructor. The second parameter is the push button name set to `ThePushButton` and used to access the push button in the parent/child dialog object tree. Using this name, the title can be referred to in the file using the `ThePushButton.Title` key.

```

```

```vbscript
For example, the text that appears in the title bar of the dialog box, that is "Button" in English, is set using the `SetTitle` method. This method applies to `this`, instance of the dialog box. To this method applied to that instance corresponds the Title key in the file. Now let's consider the push button. It is created as the child of the window, since it has `this` as first parameter of its constructor. The second parameter is the push button name set to `ThePushButton` and used to access the push button in the parent/child dialog object tree. Using this name, the title can be referred to in the file using the `ThePushButton.Title` key.
```

Switching from one language to another using the LANG environment variable with UNIX, or the Regional Settings option followed by a restart with Windows, searches for texts and messages in the directory associated to the language used, and displays the dialog box with texts expressed in that language.

To make an international push button, you can add a file named CATDialogBox.CATRsc with the following contents to display a nice icon instead of the text. The icon declaration superimposes the text declaration.

```vbscript
    ThePushButton.Icon = "I_ControlPoints";

```

This mechanism overrides the `SetTitle` method, and other methods such as `SetHelp` and `SetIcon`. If a class uses the `DeclareResource  `macro and if at run time, a resource file is found, the `SetTitle`, `SetHelp`, or `SetIcon ` methods are not taken into account.

[Top]
### Internationalizing Dialog Boxes
#### Character Strings

Character string are read from files when the application is executed to value help and short help messages, accelerators and mnemonics, and miscellaneous other texts used for window titles, labels, or displayed with the different controls.

Character string are read from files when the application is executed to value help and short help messages, accelerators and mnemonics, and miscellaneous other texts used for window titles, labels, or displayed with the different controls.
This allows for internationalization purposes, that is storing the character strings to display in a file separated from the application source code, and for localization purposes, that is translating these character strings to a given language without needing to rebuild the application. The Dialog framework relies on the objects and mechanisms provided by the Internationalization framework for character strings and for storing and retrieving them from external files.

Common character strings external resources exist for all the Dialog framework objects. They are declared by the abstract class `CATDialog` and the other classes inherit these resources from this class. Some classes can have specific resources. They are described in the class reference information.

The class `CATDialog` declares the following common character strings external resources:

Title | A character string that is used to be displayed with the object, such as the text printed on a push button, or beside a check button or a radio button.

The class `CATDialog` declares the following common character strings external resources:
Title | A character string that is used to be displayed with the object, such as the text printed on a push button, or beside a check button or a radio button.
Mnemonic | A keyboard shortcut to select a menu or a menu item by means of pressing the ALT key and the letter underlined in the menu item. For example, if the File menu is displayed File on your screen, pressing the keys ALT F at the same time selects this menu.
Accelerator | A keyboard shortcut to select a menu item by means of pressing the Ctrl key and the letter or numeral that stands beside it. For example, if the File Open menu item is displayed Open Ctrl O, pressing the keys Ctrl O select the Open file item in the File menu. Meta and Shift keys can also be used.
Help | The help message associated with the object.
ShortHelp | The short help message associated with the object. It is displayed in a balloon beside the object when the mouse moves or stays over this object.
LongHelp | The long help message associated with the object. It is displayed in a balloon beside the object when the end-user clicks on Help button or on the ? box, the cursor becoming a ?, and clicks on the object to get help about it.

The character strings external resources for an object are known when this object is constructed. Possible default values existing in the source code are overwritten by the values found in the resource file. Since the root abstract class for the Dialog framework classes defines the resources available by all its classes, actual resources can be redefined by each class in the hierarchy. The resources taken into account when instantiating a class can result from a search in the resource files declared by each class in the inheritance tree, and in the resource files of the classes whose instances are aggregated.

There is one resource file per class. The file name is the class name. The file contains character strings identified by keys according to the message catalog internationalization standards from the System framework. The keys for an object are built with the name assigned in the object constructor as second argument, possibly concatenated to its parent object, that is the object whose pointer is declared as first argument in the same constructor, except if this parent is the instance of the class itself. Assume you have a window containing a frame which contains a push button. The window `Build` method includes:

    ...
There is one resource file per class. The file name is the class name. The file contains character strings identified by keys according to the message catalog internationalization standards from the System framework. The keys for an object are built with the name assigned in the object constructor as second argument, possibly concatenated to its parent object, that is the object whose pointer is declared as first argument in the same constructor, except if this parent is the instance of the class itself. Assume you have a window containing a frame which contains a push button. The window `Build` method includes:
    _pFrame = new CATDlgFrame(this, "NiceFrame");
```vbscript
```vbscript
    _pPB = new CATDlgPushButton(_Frame, "NicePushButton");

```

```

    ...

---

The frame is constructed with the window as parent, since `this` is used as first argument in its constructor. The push buttons has the frame as parent. The resource file to declare the titles for these objects and for the window could be:

The frame is constructed with the window as parent, since `this` is used as first argument in its constructor. The push buttons has the frame as parent. The resource file to declare the titles for these objects and for the window could be:
    Title = "The Title of the window";
    NiceFrame.Title = "The frame title";
    NiceFrame.NicePushButton.Title = "Push Me";

---

`Title` applies to the window. Only the resource name is required for the class instance to which the resource file applies. ` NiceFrame.Title` sets the frame title, and ` NiceFrame.NicePushButton.Title` sets the push button title. Note that the character strings are enclosed with double quotes and ended using a semi-column.

[Top]
#### Declaring External Resources

When deriving a Dialog framework class for your own application purpose, the resource files for this class is not automatically assigned. You need to explicitly declare it.

To do this, use the `DeclareResource` macro as follows in the class header file:

When deriving a Dialog framework class for your own application purpose, the resource files for this class is not automatically assigned. You need to explicitly declare it.
To do this, use the `DeclareResource` macro as follows in the class header file:
    class MyWindow : public CATDlgDocument

    {
      **DeclareResource**(MyWindow, CATDlgDocument)
      public :
    ...

---

where:

  * `MyWindow` is the class name of your class. The external resource files name are also prefixed by `MyWindow`. They are `MyWindow.CATNls` for text resources, and `MyWindow.CATRsc` for other resources, such as icons.
  * `CATDlgDocument` is the base class for `MyWindow`, that is the class from which `MyWindow` derives. If this base class has also an external resource file declared, this file is concatenated to the `ThisClass` file.

```vbscript
If the base class inherits from its own base class an external resource file, the `ThisClass` class also inherits from it, and so forth along the class inheritance tree.

```

[Top]
### Understanding Resource Inheritance and Concatenation

When the application requests a resource for an object in a dialog window, the resource files of the different classes that make up this dialog windows are scanned. The first resource value found is taken into account, and other possible values found in other resource files are ignored. The external resource files are scanned in the following order:

  * The resource value is searched for in the resource files of the class inheritance tree, starting from the class which uses the resource and up to the first base class. The first value found for this resource is taken into account
  * If the resource is not found, it is searched for in the resource files of the aggregated objects, and in their inheritance tree as well.
  * If it is not found again, the object identifier value is taken into account.

The example below deals with a class CATDlgDocument, but could be applicable to any class declaring external resources, and for any kind of resources. Suppose the class MyDocument to instantiate is defined by the following diagram:

![CATDlgI18NConcat1.gif \(23127 bytes\)](images/CATDlgI18NConcat1.gif)

The Rare radio button is part of a frame class named BaseFrame that is used as base class by a specialized frame class named DerivedFrame. This specialized class is aggregated by reference in a dialog window class named DerivedWindow that itself features a frame provided by a window base class named BaseClass. Each class provides the resources for its own controls. The resources are then searched for in the following order::

  * First in the DerivedWindow.CATNLS file: only the Quantity label title is found
  * Then in the BaseWindow.CATNLS file: the Size label is found
  * Then in the DerivedFrame.CATNls file: the check button titles are found
  * Finally in the BaseFrame.CATNls file: the radio button titles are found.

Suppose now that the DerivedFrame.CATNls resource file redefines the Rare radio button title. This redefined title is taken into account because the aggregated DerivedFrame resource file is searched for before its base class resource file. The dialog box looks like this:

![CATDlgI18NConcat2.gif \(24974 bytes\)](images/CATDlgI18NConcat2.gif)

Suppose now that the DerivedWindow.CATNls resource file itself redefines the Rare radio button title. This redefined title is taken into account because the DerivedWindow resource file is searched for before all the other resource files. The dialog box looks like this:

![CATDlgI18NConcat3.gif \(25687 bytes\)](images/CATDlgI18NConcat3.gif)

[Top]
#### Retrieving Character Strings External Resources

Character strings external resources are stored in message catalogs. The file which contains the message catalog is searched for in the directories declared in the `CATMsgCatalogPath `environment variable.

Character strings external resources are stored in message catalogs. The file which contains the message catalog is searched for in the directories declared in the `CATMsgCatalogPath `environment variable.
The occurrences of the same message catalog file translated in several languages should each be stored in the appropriate directory, such as French, German, Japanese, and so forth, in the `CATMsgCatalogPath` declared directories.

Only the first file name occurrence is taken into account in this directory concatenation.

[Top]
#### Icons

Only the first file name occurrence is taken into account in this directory concatenation.
Icons are read from directories, each icon being stored in a file. The _CATDialog_ class declares the following common icon external resources:

Icon | The icon associated with a given dialog object. For toolbar buttons, in "P2" session, an icon with a shadow is dynamically generated and displayed.

Icons are read from directories, each icon being stored in a file. The _CATDialog_ class declares the following common icon external resources:
Icon | The icon associated with a given dialog object. For toolbar buttons, in "P2" session, an icon with a shadow is dynamically generated and displayed.
IconSel | The icon associated with a given dialog object when this object is selected. This resource is kept for compatibility. For Toolbars buttons, in "P2" session, if not explicitly specified through a resource file or SetIconName, the "select" icon is dynamically generated and displayed.
IconFocus | The icon associated with a given dialog object when the mouse moves over this object. This resource is kept for compatibility. For toolbars buttons, in "P2" session, if not explicitly specified through a resource file or SetIconName, the focus icon is dynamically generated and displayed.
IconDisabled | The icon associated with a given dialog object when this object can not be selected. This resource is deprecated and no longer taken into account. The disabled icon is automatically generated.
IconType | This resource is deprecated and no longer taken into account

Icons are retrieved from directories declared using the environment variable `CATIconPath`. The icons must be of the type BMP and stored in files with the suffix `bmp`, such as `MyIcon.bmp.`

As for character strings, icons are declared in the resource files using a key as follows: `key.Icon = "MyIcon";`

[Top]
### Internationalizing Text

```vbscript
```vbscript
For some Dialog objects, such as _CATDlgCombo, CATDlgSelectorList_ or _CATDlgMultiList_ , it is necessary to create NLS texts for their items. Have a look at this sample extracted from the Burger use case [2]

```

```

![](images/CAADlgResourcesCATMsgCat.jpg)
---

It is a _CATDlgSelectorList_ with a list of items. Here is the code to create such object:

      _pDrinkList = new **CATDlgSelectorList**(pDrinkFrame, "DrinkListId", CATDlgLstMultisel);
      ...

      **CATUnicodeString** usDrinkListLines[11];
_pDrinkList = new **CATDlgSelectorList**(pDrinkFrame, "DrinkListId", CATDlgLstMultisel);
```vbscript
```vbscript
      for ( int j= 0; j < 11; j++)

```

```

      {
```vbscript
for ( int j= 0; j < 11; j++)
```vbscript
        sprintf(pcKey, "Drink%d", j);
```

        sKey = pcKey;
        if ( 0 != **GetResourceValueFromKey**(sKey, usText))
```

        {
```vbscript
sprintf(pcKey, "Drink%d", j);
sKey = pcKey;
if ( 0 != **GetResourceValueFromKey**(sKey, usText))
            usDrinkListLines[j]=usText;
```

        }
      }
```vbscript
if ( 0 != **GetResourceValueFromKey**(sKey, usText))
usDrinkListLines[j]=usText;
      _pDrinkList->**SetLine**(usDrinkListLines, 11);

```

---

The `GetResourceValueFromKey` method of the _CATDialog_ class enables you to find out the NLS text for each line of the list:

  * `sKey` is the keyword associated with the line. Here it is Drink0, Drink1,.... Drink11
  * `usText` is the output value extracted from the NLS file declared in the `DeclareResource` macro of the class header.

In the NLS file, you have such lines:

    ...
In the NLS file, you have such lines:
    Drink0  = "Apple Juice";
    Drink1  = "Orange Juice";
    Drink2  = "Grape Juice";
    Drink3  = "Cola";
    Drink4  = "Punch";
    Drink5  = "Root Beer";
    Drink6  = "Water";
    Drink7  = "Ginger Ale";
    Drink8  = "Milk";
    Drink9  = "Coffee";
    Drink10 = "Tea";

    ...

---

There is another means to create a NLS text. It is the _CATMsgCatalog_ class (System framework). Have a look at this sample extracted from the More/Less use case. [3]

The "More" button becomes "Less". For the same _CATDlgPushButton_ class instance, the instance identifier cannot reference two NLS texts. In this case you can always use the `GetResourceValueFromKey` method as described above or use the _CATMsgCatalog_ class.

    ...
The "More" button becomes "Less". For the same _CATDlgPushButton_ class instance, the instance identifier cannot reference two NLS texts. In this case you can always use the `GetResourceValueFromKey` method as described above or use the _CATMsgCatalog_ class.
    CATDlgPushButton * pPushButtonMore = new CATDlgPushButton(pFrameLeftMore, "PushButtonMore");
    _MoreMsg = CATMsgCatalog::**BuildMessage**("CAADlgMoreButtonDlg","**ButtonMore** ",NULL,0,"More>>");
```vbscript
    _LessMsg = CATMsgCatalog::**BuildMessage**("CAADlgMoreButtonDlg","**ButtonLess** ",NULL,0,"Less>>");
```

    pPushButtonMore->**SetTitle**(_MoreMsg);

    ...

    ...
_LessMsg = CATMsgCatalog::**BuildMessage**("CAADlgMoreButtonDlg","**ButtonLess** ",NULL,0,"Less>>");
pPushButtonMore->**SetTitle**(_MoreMsg);
    pPushButtonMore->**SetTitle**(_LessMsg);

---

The `BuildMessage` static method has the following arguments:

`CAADlgMoreButtonDlg` : | The name of the NLS file
---|---
`ButtonMore` : | The keyword
`NULL `: | An useless information in this case
`0`` `: | An useless information in this case
`"More>>"`` `: | The default text if the `ButtonMore` keyword is not found in the Nls file
_MoreMsg : | The result

In the `CAADlgMoreButtonDlg`.CATNls file you find the such lines:

    ...
In the `CAADlgMoreButtonDlg`.CATNls file you find the such lines:
    ButtonMore = "More" ;
    ButtonLess = "Less" ;

    ...

---

But the full advantage of this class is to build a dynamic text. Considerer this sample:

![](images/CAADlgResourcesCATMsgCat2.jpg)
---

This _CATDlgNotify_ dialog box displays two wrong point indices. "Points 1 and 3 are the same" is the constant text and " " and " " are depending on the end user selection. Here is the code to create such NLS text:

    ...
This _CATDlgNotify_ dialog box displays two wrong point indices. "Points 1 and 3 are the same" is the constant text and " " and " " are depending on the end user selection. Here is the code to create such NLS text:
       CATUnicodeString param[2];
       param[0].BuildFromNum(_FirstPoint);
       param[1].BuildFromNum(_SecondPoint);

       CATUnicodeString Msg1("Points ");
       CATUnicodeString Msg2(" and ");
       CATUnicodeString Msg3(" are the same.");
       CATUnicodeString defaultMsg = Msg1 + param[0] + Msg2 + param[1] + Msg3;

```vbscript
       Msg = **CATMsgCatalog::BuildMessage(** "CAADegPointErrorBox",

```

                            "Phrase",
CATUnicodeString Msg3(" are the same.");
CATUnicodeString defaultMsg = Msg1 + param[0] + Msg2 + param[1] + Msg3;
Msg = **CATMsgCatalog::BuildMessage(** "CAADegPointErrorBox",
                            param,
                            2,
                            defaultMsg);

    ...

---

where:

`CAADegPointErrorBox` : | The name of the NLS file
---|---
`Phrase` : | The keyword
`param` : | The _CATUnicodeString_ array containing the values to build the result
`2 `: | The count of elements to take into account in the `param` array
`defaultMsg` : | The default text
`Msg` : | The result. If there is a problem, its value is `defaultMsg`.

In the CAADegPointErrorBox.CATNls file, you find such line:

    ...
    Phrase = " Points **/p1** and **/p2** are the same" ;
    ...

---

Each /p`i `will be replaced by the `i` value of the `param` array.

[Top]

* * *
### In Short

Internationalizing your application implies to separate resources from the code to enable application localization, that is, for example, titles, prompts, and message translation. Translatable resources are stored in the CATNls-suffixed files, and non translatable resources, such as icon paths, are stored in CATRsc-suffixed files.

Internationalizing your application implies to separate resources from the code to enable application localization, that is, for example, titles, prompts, and message translation. Translatable resources are stored in the CATNls-suffixed files, and non translatable resources, such as icon paths, are stored in CATRsc-suffixed files.
The `DeclareResource` macro makes the link between your dialog main class and its resource files. Each dialog object or control has an identifier set as the constructor second parameter and used to retrieve the resources for this object using a key built thanks to this identifier.

Resources can be inherited and concatenated to enable dialog subsets reuse.

[Top]

* * *
### References

[1] | [Creating Dialog Objects](CAADlgCreatingDialogs.md)
---|---
[2] | [The Burger Order Dialog Box](../CAADlgUseCases/CAADlgBurger.md)
[3] | [ Creating Dialog Boxes Automatically Resizable](../CAADlgUseCases/CAADlgSampleTabulation.md)
[Top]

* * *
### History

Version: **1** [Jan 2000] | Document created
---|---
Version: **2** [Fev 2003] | Document updated to add the Internationalizing Text section
[Top]

* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
