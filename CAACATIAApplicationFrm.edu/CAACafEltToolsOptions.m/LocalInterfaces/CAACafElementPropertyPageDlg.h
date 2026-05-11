#ifndef CAACafElementPropertyPageDlg_H
#define CAACafElementPropertyPageDlg_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing a Dialog object dedicated to a Tools/Options page.This 
//  page is managed by the  CAACafElementPropertyPageEdt editor. 
//
//  Who manages what ?:
//  -------------------
//  Options of your page are kept in a repository file 
//   
//  CAACafElementPropertyPageDlg gets the controller repository in its 
//  constructor.
//
//  The CAACafElementPropertyPageDlg class modifies at each interaction 
//  on the dialog objects of the page the repository file thanks to
//  the CAAICafGeometryEltSettingAtt interface. 
//   
//  The CAACafElementPropertyPageEdt class manages the repository for reset,
//  cancel and close. When resetting, the dialog class can 
//  be called to restore, with the saved values, the dialog objects of 
//  the page.
//  
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
//  Build         -> Construction of the dialog object
//  ValueSettings -> Valuation of the dialog object from the setting file
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
class CAAICafGeometryEltSettingAtt;

class CAACafElementPropertyPageDlg : public CATDlgFrame
{
    // NLS Macro. It declares the resource files 
    // CAACafElementPropertyPageDlg.CATNls  located in 
    // CNext/resources/msgcatalog 
    //
    DeclareResource(CAACafElementPropertyPageDlg, CATDlgFrame);

  public :

	// Constructor/Destructor
    // ----------------------
    // See CAACafElementPropertyPageEdt to know the lifecycle 
    // of this class.
    // 
    CAACafElementPropertyPageDlg(CATDialog * iParent);
    virtual ~CAACafElementPropertyPageDlg();

	// Build
    // -----
    // Builds Property Page Dialog objects.
    //
    void Build();

	// ValueSettings
    // ------------- 
    // Sets up Dialog objects from the setting file.
    // 
    // This method is called just after the Build method by the 
    // CAACafElementPropertyPageEdt::SetUserSettingsValue method. 
    // 
    void ValueSettings();

  private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafElementPropertyPageDlg ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafElementPropertyPageDlg(const CAACafElementPropertyPageDlg &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafElementPropertyPageDlg & operator = (const CAACafElementPropertyPageDlg &iObjectToCopy);

    // Callbacks 
    void IdHideCB            (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
    void IdShowCB            (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
    void IdPreSelectShowCB   (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
    void MaxPointCB          (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
    void ImplPointHideCB     (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);
    void ImplPointShowCB     (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData);

  private :

    // Dialog Objects
    CATDlgRadioButton    * _pIdHide;
    CATDlgRadioButton    * _pIdShow;
    CATDlgRadioButton    * _pIdPreSelectShow;
    CATDlgRadioButton    * _pImplPointShow;
    CATDlgRadioButton    * _pImplPointHide;
    CATDlgSlider         * _pMaxPoint;
   
    // The setting  controller 
    CAAICafGeometryEltSettingAtt * _pISettingAttForCtrl ;
};

#endif
