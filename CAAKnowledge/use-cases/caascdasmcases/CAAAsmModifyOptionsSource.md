---
title: "CAAAsmModifyOptions.catvbs"
category: "use-case"
module: "CAAScdAsmUseCases"
tags: ["CATIA", "CAAAsmModifyOptions"]
source_file: "Doc/online/CAAScdAsmUseCases/CAAAsmModifyOptionsSource.htm"
converted: "2026-05-11T17:31:50.861645"
---

    ' COPYRIGTH DASSAULT SYSTEMES 2004
    Language="VBSCRIPT"
    
```vbscript
    ' ***********************************************************************
    '   Purpose:      Gets and modifies Assembly Design options
    '   Assumtions:      
    '   Languages:    VBSCRIPT
    '   Locales:      English 
    '   CATIA Level:  V5R15
    ' ***********************************************************************
    
    
```

    
```vbscript
    Sub CATMain()
```vbscript
    ' ----------------------------
    ' Get the settings controller
    ' ----------------------------
```

    
```vbscript
    Set settingControllers1 = CATIA.SettingControllers
```vbscript
    ' ------------------------------
    ' Assembly / General options
    ' ------------------------------
    
    Set asmGeneralSetting = settingControllers1.Item("CATAsmGeneralSettingCtrl")
    ' ------------------------------
    ' Get/Set the options values
    ' ------------------------------
```

    
```

    asmGeneralSetting.AutoUpdateMode = catManualUpdate
    autoUpdt = asmGeneralSetting.AutoUpdateMode
    msgbox "Automatic Update mode = " & autoUpdt
    
    asmGeneralSetting.UpdateStatusMode = catAutomaticCompute
    updtStatus = asmGeneralSetting.UpdateStatusMode
    msgbox "Update Status computation mode = " & updtStatus
    
    asmGeneralSetting.AutoSwitchToDesignMode = catAutoSwitchUnavailable
    autoSwitch = asmGeneralSetting.AutoSwitchToDesignMode
    msgbox "Automatic switch to Design Mode option = " & autoSwitch
    
    asmGeneralSetting.MoveWithFixTExtendMode = catAskIfExtendMoveToFixT
    moveFixT = asmGeneralSetting.MoveWithFixTExtendMode
    msgbox "Move components involved in a Fix Together mode = " & moveFixT
```vbscript
    ' ------------------------------
    ' Lock/Unlock informations
    ' ------------------------------
```

    
    asmGeneralSetting.SetAutoUpdateModeLock True
    isModified = asmGeneralSetting.GetAutoUpdateModeInfo (adminlevel, locked)
    msgbox "Automatic Update : administrator level = " & adminlevel & " - lock status = " & locked
    
    asmGeneralSetting.SetUpdateStatusModeLock False
    isModified = asmGeneralSetting.GetUpdateStatusModeInfo (adminlevel, locked)
    msgbox "Update Status computation : administrator level = " & adminlevel & " - lock status = " & locked
    
    asmGeneralSetting.SetAutoSwitchToDesignModeLock True
    isModified = asmGeneralSetting.GetAutoSwitchToDesignModeInfo (adminlevel, locked)
    msgbox "Automatic switch to Design Mode : administrator level = " & adminlevel & " - lock status = " & locked
    
    asmGeneralSetting.SetMoveWithFixTExtendModeLock False
    isModified = asmGeneralSetting.GetMoveWithFixTExtendModeInfo (adminlevel, locked)
    msgbox "Move components involved in a Fix Together : administrator level = " & adminlevel & " - lock status = " & locked
```vbscript
    ' --------------------------------------------
    ' SaveRepository
    ' --------------------------------------------
```

    
    asmGeneralSetting.SaveRepository
```vbscript
    ' ------------------------------
    ' Assembly / Constraint Options
    ' ------------------------------
```

    
```vbscript
    Set asmConstraintSetting = settingControllers1.Item("CATAsmConstraintSettingCtrl")
```vbscript
    ' ------------------------------
    ' Get/Set the options values
    ' ------------------------------
```

    
```

    asmConstraintSetting.PasteComponentMode = catPasteWithCstOnCopyAndCut
    paste = asmConstraintSetting.PasteComponentMode
    msgbox "Component constraints creation after a Paste = " & paste
    
    asmConstraintSetting.ConstraintCreationMode = catUsePublishedGeometryAnyLevel
    pub = asmConstraintSetting.ConstraintCreationMode
    msgbox "Selectable elements to create a constraint = " & pub
    
    asmConstraintSetting.QuickConstraintMode = catVerifiedConstraintFirst
```vbscript
    Dim newArray(5)
    newArray(0) = "CATAsmPerpendType"
    newArray(1) = "CATAsmSurfContactType"
    newArray(2) = "CATAsmAngleType"
    newArray(3) = "CATAsmDistanceType"
    newArray(4) = "CATAsmCoincidenceType"
    newArray(5) = "CATAsmParallelType"
    asmConstraintSetting.SetQuickConstraintOrderedList newArray
    quick = asmConstraintSetting.QuickConstraintMode
    Dim array
    array = asmConstraintSetting.GetQuickConstraintOrderedList()
    msgbox "Quick Constraint creation mode = " & quick
    msgbox "ordered list : " & array(0) & " - " & array(1) & " - " & array(2) & " - " & array(3) & " - " & array(4) & " - " & array(5) 
```vbscript
    ' ------------------------------
    ' Lock/Unlock informations
    ' ------------------------------
```

    
```

    asmConstraintSetting.SetPasteComponentModeLock False
    isModified = asmConstraintSetting.GetPasteComponentModeInfo (adminlevel, locked)
    msgbox "Component constraints creation after a Paste : admin level = " & adminlevel & " - locked = " & locked
    
    asmConstraintSetting.SetConstraintCreationModeLock True
    isModified = asmConstraintSetting.GetConstraintCreationModeInfo (adminlevel, locked)
    msgbox "Selectable elements to create a constraint : admin level = " & adminlevel & " - locked = " & locked
    
    asmConstraintSetting.SetQuickConstraintModeLock True
    isModified = asmConstraintSetting.GetQuickConstraintModeInfo (adminlevel, locked)
    msgbox "Quick Constraint creation : admin level = " & adminlevel & " - locked = " & locked
```vbscript
    ' --------------------------------------------
    ' SaveRepository, Rollback and ResetToDefault
    ' --------------------------------------------
```

    asmConstraintSetting.SaveRepository
```vbscript
    ' -------------
    ' The End...
    ' -------------
```

    
```vbscript
    End Sub
    
```

```