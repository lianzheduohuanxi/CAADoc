---
title: "Managing Magnitudes and Units"
category: "general"
module: "CAADlgTechArticles"
tags: ["CATInteractiveApplication", "CATIA"]
source_file: "Doc\online\CAADlgTechArticles\CAADlgManagingUnits.htm"
converted: "2026-05-11T17:17:56.047533"
---

# 3D PLM Enterprise Architecture

| 

## User Interface - Dialogs

| 

### Managing Magnitudes and Units

_How to make combo, editor, and spinner numerical fields match real values_  
---|---|---  
Technical Article  
  
* * *

### Abstract

The figures that are displayed and entered in combos, editors, and spinners of your application, are usually values that represent magnitudes. These magnitudes are expressed according to a unit system that must match the country, the business, or the customer habits or rules. 

  * **How Does CATIA Manages Magnitudes and Units**
  * **Managing Magnitudes and Units for the Application**
  * **Managing Magnitudes and Units for a Control**
  * **Converting a Magnitude Value for Display in the End User Unit System**
  * **In Short**
  * **References**

  
---  
  
* * *

### How Does CATIA Manages Magnitudes and Units

CATIA manages the magnitudes required by a number of applications, such as length, mass, or speed. The values of these magnitudes that the end user may enter or select, or that the application may display for modification, can be entered using either combos[1], editors[2], or spinners[3]. These values can be expressed in a wide range of units, allowing the end user to work with the units that are usual to the task, business, or country habits. This is only a faade that hides the internal value storage made according to the International Unit System (SI). By default, values are also expressed using this system in combos, editors, and spinners. If you choose to use a different unit for a given magnitude, you need to specify it. Then, conversions are made whenever a value is displayed between the SI unit of the storage and the chosen unit, and conversely when a value is entered.

Magnitudes and units [4] to use throughout an application are declared at the application level. The CATInteractiveApplication class supplies two methods, `SetMagnitudeCurrentUnit` and `GetMagnitudeCurrentUnit` to respectively set and get the unit associated with a given magnitude to use in all the combos, editors, and spinners of the application. If an application doesn't specify anything, the default unit system is SI.

Then, for each combo, editor, or spinner, you should set the magnitude to which this control is dedicated. If you want to use for a given control a different unit than the one used for the application, you should set this unit to the control instead of the magnitude. In addition, you can set a precision to the control, that is, the number of digits displayed.

[Top]

### Managing Magnitudes and Units for the Application

You can assign a given unit to a magnitude to be used throughout the application using the `SetMagnitudeCurrentUnit` method. Suppose you want to express the lengthes in feet.
    
    
    ...
    IntAppliInstance.SetMagnitudeCurrentUnit(CATDlgControl::Length,
                                             CATDlgControl::Foot);
    ...  
  
---  
  
You can get the application current unit for a given magnitude using the `GetMagnitudeCurrentUnit` method.
    
    
    ...
    CATDlgControl::Unit = CurrentLengthUnit;
    CurrentLengthUnit == IntAppliInstance.SetMagnitudeCurrentUnit(CATDlgControl::Length);
    if (CurrentLengthUnit == CATDlgControl::Meter)
      ...  // System used is SI
    else if (CurrentLengthUnit == CATDlgControl::Foot)
      ...  // System used is Imperial  
  
---  
  
When you set a unit associated with a given magnitude, all the controls that will be created afterwards for this magnitude will express values using this unit. Nevertheless, any control created for this magnitude prior to the unit modification keeps the unit that was current when it was created. It is therefore recommended to set all the units for the magnitude you will use when initializing the application, except if you use the SI unit system which is the default.

[Top]

### Managing Magnitudes and Units for a Control

For each control you create that displays and/or is used to enter a value, you must assign it the corresponding magnitude using the `SetMagnitude` or the `SetUnit` method.

![CATDlgUnit1.gif \(4686 bytes\)](images/CATDlgUnit1.gif)

The example given uses a combo which is assigned a length magnitude. The length unit is set to inch  for the application.
    
    
    ...
    CATDlgCombo * pCombo;
    pCombo = new CATDlgCombo (pParent, "ComboId",
                              CATDlgCmbDropDown|CATDlgCmbDouble|CATDlgCmbEntry);
    pCombo->SetMagnitude(CATDlgControl::Length);
    ...  
  
---  
  
The combo can then be used to enter and display length units expressed in inches. You cannot reset this unit afterwards. When the end user enters a length using the combo, for example 400,000.95 inches, the internal value handled by CATIA, namely for the combo the value returned  as a double by the `GetValue` method, is converted to the SI unit for lengthes, that is, meters, here 10,135.2 meters. If you want to use a different unit than the one defined at the application level, use the `SetUnit` method instead of `SetMagnitude`. For example, you can choose to express the length assigned to the four editors in millimeters.
    
    
    ...
    CATDlgEditor * pEditor1;
    pEditor1 = new CATDlgEditor(pParent, "EditorId", CATDlgEdtDouble);
    pEditor1->SetUnit(CATDlgControl::Millimeter);
    ...  
  
---  
  
You can also choose the precision used to display the entered values. The precision can range from 1 to 15 inclusively, the default being five digits. The four editors have their precisions set to 1, 4, 8, an twelve respectively. This is possible thanks to the `SetPrecision` method.
    
    
    ...
    pEditor1->SetPrecision(1);
    pEditor2->SetPrecision(4);
    pEditor3->SetPrecision(8);
    pEditor4->SetPrecision(12);
    ...  
  
---  
  
These three methods `SetMagnitude`, `SetUnit`, and `SetPrecision`, have their getter companion methods.
    
    
    ...
    CATDlgControl::Magnitude EditorCurrentMagnitude;
    CATDlgControl::Unit      EditorCurrentUnit;
    int                      EditorCurrentPrecision;
    EditorCurrentMagnitude = pEditor1->GetMagnitude();
    EditorCurrentUnit      = pEditor1->GetUnit();
    EditorCurrentPrecision = pEditor1->GetPrecision();
    ...  
  
---  
  
[Top]

### Converting a Magnitude Value for Display in the End User Unit System

You may want to display a magnitude value according to the end units elsewhere than in a combo, and editor, or a spinner. This is usually the case if you want to show one or several values in a notification window, possibly in an information, warning, or error message. In this case, no automatic conversion is made from the SI unit system and the end user unit system. You must use the `GetDoubleValueString` method of the interactive application to perform this conversion.

For example, the following code converts a length whose value is stored or retrieved as a double in DoubleValue into a CATUnicodeString that can be used to create a message.
    
    
    double DoubleValue = ...; // Value expressed in SI
    CATUnicodeString ucValue; // Value expressed in the end user unit system
                              // ready for use in a message
    ucValue = IntAppliInstance.GetDoubleValueString(DoubleValue, CATDlgControl::Length);  
  
---  
  
[Top]

* * *

### In Short

The interactive application instance holds a set a magnitudes expressed in the SI units. These magnitude can be used in combos, editors, and spinners to enter or display values representing these magnitudes. CATIA stores the values in the SI unit system, but you can change the unit used for a given magnitude at the application level. Then, all controls to which this magnitude is assigned will use this unit. You can also change the unit for a given magnitude and for a given control at the control level.

[Top]

* * *

### References

[1] | [Combo](../CAADlgQuickRefs/CAADlgCATDlgCombo.htm)  
---|---  
[2] | [Editor](../CAADlgQuickRefs/CAADlgCATDlgEditor.htm)  
[3] | [Spinner](../CAADlgQuickRefs/CAADlgCATDlgSpinner.htm)  
[4] | [Magnitudes And Units](../CAADlgQuickRefs/CAADlgMagnitudesAndUnits.htm)  
[Top]  
  
* * *

### History

Version: **1** [Jan 2000] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2000, Dassault Systmes. All rights reserved._
