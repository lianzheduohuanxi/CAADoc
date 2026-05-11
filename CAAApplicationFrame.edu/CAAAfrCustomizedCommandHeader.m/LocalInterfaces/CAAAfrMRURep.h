// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAAfrMRURep_h
#define CAAAfrMRURep_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//  This class is the representation ( a CATCommand ) of the CAAAfrMRUHeader
//  in the menu bar.
//
//  The list of the most recent used items are kept by the MRU manager
//  a unique CAAAfrMRUManager class instance during the session. 
//
//===========================================================================

// Local framework
class CAAIAfrMRUManagement ;

// System Framework
#include "CATAfrCommandHeaderRep.h" // to derive from 
class CATString ;

// Dialog Framework
class CATDialog ;
class CATDlgPushItem ;

#define MRU_MAX_SIZE 5 

class CAAAfrMRURep : public CATAfrCommandHeaderRep
{

public:
  
  // Constructor
  // -----------
  // iParent kept by the CAAAfrHeaderRep class instance will be
  // the dialog object parent of each dialog object created by 
  // this class.
  //
  CAAAfrMRURep(const CATDialog * iParent, CATString & iCommandName);

  // Destructor
  // ----------
  // Each dialog object created in this class instance must
  // be released.
  //
  virtual ~CAAAfrMRURep();

  // Build
  // ----- 
  // This method calls the ModifyListItem method
  //
  HRESULT Build();
  
private:

  // SelectCB
  // --------
  // Callback method when a push item is selected
  // this method notifies the MRU manager thanks its
  // CAAIAfrMRUManager interface. The ModifiedCB method
  // will be called to modify the push item order.
  // At the end of the method a command which displays
  // the name of the selected item.
  //
  void SelectCB(CATCommand           * iPublishingCommand, 
                CATNotification      * iNotification, 
                CATCommandClientData   iData);

  // ModifiedCB
  // ----------
  // Callback method when the MRU manager sends a
  // notification when its list of items is modified.
  // 
  void ModifiedCB(CATCallbackEvent       iEvent, 
                  void            *       , 
                  CATNotification * iNotification, 
                  CATSubscriberData iData,
		              CATCallback iCallBack);

  // ModifyListItem
  // ---------------
  // Method called by ModifiedCB, CreateRep and ModifyRep
  //
  HRESULT ModifyListItem() ;

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrMRURep(const CAAAfrMRURep &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAAfrMRURep & operator = (const CAAAfrMRURep &iObjectToCopy);

private:

  // Dialog objects created by ModifyListItem
  CATDlgPushItem            * _pItemList[MRU_MAX_SIZE];
  
  // A pointer on the MRU manager to update or retrieve its
  // list of items.
  CAAIAfrMRUManagement      * _pIAfrMRUManagement ;

};

#endif
