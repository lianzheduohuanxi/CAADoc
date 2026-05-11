#ifndef CAAAfrMRUSelElementCmd_h
#define CAAAfrMRUSelElementCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//===========================================================================

// Dialog framework
#include "CATDlgDialog.h"  //Needed to derive from

class CATDlgEditor ;

class CAAAfrMRUSelElementCmd : public CATDlgDialog
{ 
  // Declares the CAAAfrMRUSelElementCmd.CATNls file as the dialog message catalog
  // This file is set in the Cnext\resources\msgcatalog of the current FW
  //
  DeclareResource(CAAAfrMRUSelElementCmd, CATDlgDialog)
  
  public :

    CAAAfrMRUSelElementCmd();
    virtual ~CAAAfrMRUSelElementCmd();  
  
  private :

    // CloseBox
    // --------
    // 
    //
    void CloseBox(CATCommand              *iPublishingCommand, 
                  CATNotification         *iNotification, 
                  CATCommandClientData     iUsefulData);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUSelElementCmd(const CAAAfrMRUSelElementCmd &iObjectToCopy );

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrMRUSelElementCmd & operator = (const CAAAfrMRUSelElementCmd &iObjectToCopy );

    void Build();
};
#endif


