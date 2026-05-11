// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAAfrComboRep_h
#define CAAAfrComboRep_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//  This class is the representation ( a CATCommand ) of the 
//  CAAAfrComboColorHeader in the tool bar.
//
//  The current color is kept by the UIActive object of the CAAGeometry 
//  document. 
//  
//===========================================================================

// System Framework
#include "CATAfrCommandHeaderRep.h" // to derive from 

class CATString ;
class CATDialog ;
class CATDlgCombo ;

class CAAAfrComboRep : public CATAfrCommandHeaderRep
{

public:
  
  // Constructor
  // -----------
  // iParent kept by the CAAAfrHeaderRep class instance will be
  // the dialog object parent of CATDlgCombo created by 
  // this class.
  //
  CAAAfrComboRep(const CATDialog * iParent, CATString & iCommandName);

  // Destructor
  // ----------
  // The CATDlgCombo instance created in this class instance must
  // be released.
  //
  virtual ~CAAAfrComboRep();

  // Build
  // -----
  // This method  creates the CATDlgCombo instance 
  // and calls SetCurrentColor to set the current 
  // selected color
  //
  HRESULT Build();

private:

  // SelectCB
  // -------- 
  // This method advises the UI active object that there is
  // a new current color
  //
  void SelectCB(CATCommand * iPublishingCommand, 
                CATNotification * iNotification, 
                CATCommandClientData iData);

  // ModifiedCB
  // ----------
  // Callback method when the MRU manager sends a
  // notification when its list of items is modified.
  // 
  void ModifiedCB(CATCallbackEvent  iEvent, 
                  void            *       , 
                  CATNotification * iNotification, 
                  CATSubscriberData iData,
		              CATCallback       iCallBack);

  // SetCurrentColor
  // ---------------
  // This method queries the UIActive object to know the
  // current color, and modifies the CATDlgCombo instance
  //
  HRESULT SetCurrentColor() ;

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrComboRep(const CAAAfrComboRep &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrComboRep & operator = (const CAAAfrComboRep &iObjectToCopy);

private:

     // The CATDlgCombo instance created by CreateRep method
     CATDlgCombo    * _pCombo;

     // The data in the model which keeps the current color
     //
     CATBaseUnknown * _pUIActiveObject ;

     // The 10 (r,g,b) predefined color 
     //
     int              _ColorTable[30] ;
};

#endif
