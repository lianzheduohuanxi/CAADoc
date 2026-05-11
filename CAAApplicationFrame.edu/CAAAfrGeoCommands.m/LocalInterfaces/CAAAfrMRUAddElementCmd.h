#ifndef CAAAfrMRUAddElementCmd_h
#define CAAAfrMRUAddElementCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//===========================================================================

// Dialog framework
#include "CATDlgDialog.h"  //Needed to derive from

class CATDlgEditor ;

class CAAAfrMRUAddElementCmd : public CATDlgDialog
{ 
  // Declares the CAAAfrMRUAddElementCmd.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAAAfrMRUAddElementCmd, CATDlgDialog)
  
public :

    CAAAfrMRUAddElementCmd();
    virtual ~CAAAfrMRUAddElementCmd();  
  
  private :

    // CloseBox
    // --------
    // 
    //
    void CloseBox(CATCommand              *iPublishingCommand, 
                  CATNotification         *iNotification, 
                  CATCommandClientData     iUsefulData);

    // OkCloseBox
    // --------
    // 
    //
    void OkCloseBox(CATCommand              *iPublishingCommand, 
                  CATNotification         *iNotification, 
                  CATCommandClientData     iUsefulData);

    void Build();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUAddElementCmd(const CAAAfrMRUAddElementCmd &iObjectToCopy );

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUAddElementCmd & operator = (const CAAAfrMRUAddElementCmd &iObjectToCopy );

  private :

    CATDlgEditor     * _pEditor ;

};
#endif

