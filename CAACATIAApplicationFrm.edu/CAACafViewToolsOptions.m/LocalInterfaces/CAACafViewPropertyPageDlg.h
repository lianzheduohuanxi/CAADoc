#ifndef CAACafViewPropertyPageDlg_H
#define CAACafViewPropertyPageDlg_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing a Dialog object dedicated to a Tools/Options page.This 
//  page is managing by the  CAACafViewPropertyPageEdt editor. 
//
//  See CAACafElementPropertyPageDlg for all details. 
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, Tools/Options 
//  
//===========================================================================
//  Inheritance:
//  ------------
//       CATDlgFrame (Dialog Framework)
//          CATDlgBox      (Dialog Framework)
//               CATDialog    (Dialog Framework)
//                  CATCommand  ( System Framework)
//                      CATBaseUnknown (System Framework)
//                   
//
//===========================================================================
//  Main Methods:
//  -------------
//
//  Build         -> Construction of the Dialog object
//  ValueSettings -> Valuation of the Dialog object from the setting file
// 
//   xxxxCB       -> All these methods modify the dialog object, and the 
//                    setting file. With Repository mechanism, ( commit/rollback)
//                    it's easy to manage the save, no need to keep the old
//                    values from the last commit. 
//
//===========================================================================
#include "CATDlgFrame.h"          // Needed to derive from CATDlgFrame

// Dialog Framework
class CATDlgRadioButton;
class CATDlgSlider;

// System Framework
class CAAICafGeometryViewSettingAtt;

class CAACafViewPropertyPageDlg : public CATDlgFrame
{
    // NLS Macro. It declares the resource files 
    // CAACafViewPropertyPageDlg.CATNls (CATRsc) located in 
    // CNext/resources/msgcatalog
    //
    DeclareResource(CAACafViewPropertyPageDlg, CATDlgFrame);

  public :

    CAACafViewPropertyPageDlg(CATDialog * parent);
    virtual ~CAACafViewPropertyPageDlg();

    void Build();

    void ValueSettings();
 
  private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafViewPropertyPageDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafViewPropertyPageDlg(const CAACafViewPropertyPageDlg &iObjectToCopy);

    // Assignment operator , not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafViewPropertyPageDlg & operator = (const CAACafViewPropertyPageDlg &iObjectToCopy);

    // Callbacks 
    void OnRadModify         (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
  private :

    // Dialog Objects
    CATDlgRadioButton    * _pIdAxis;
    CATDlgRadioButton    * _pIdPlane;
    CATDlgRadioButton    * _pIdWall;

    // The setting  controller 
    CAAICafGeometryViewSettingAtt * _pISettingAttForCtrl ;

 
};

#endif
