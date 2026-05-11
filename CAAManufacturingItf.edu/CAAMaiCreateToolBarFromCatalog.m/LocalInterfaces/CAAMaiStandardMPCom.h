//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
// 
// Class CAAMaiStandardMPCom2: command for Machining process application 
#ifndef CAAMaiStandardMPCom_H
#define CAAMaiStandardMPCom_H
//
#include "CATListOfCATUnicodeString.h"
#include "CATCommand.h"

class CATNotification;
class CATUnicodeString;

class  CAAMaiStandardMPCom : public CATCommand
{
  public:
	    
    CAAMaiStandardMPCom (const CATString * iIdentifier);

    virtual ~CAAMaiStandardMPCom ();
	
    CATStatusChangeRC Activate(CATCommand* c, CATNotification* notif);
    
  private:

    // ---> Pas d implementation du copy constructor et de l operateur "="
    CAAMaiStandardMPCom (CAAMaiStandardMPCom &);
    CAAMaiStandardMPCom& operator=(CAAMaiStandardMPCom&);
};
#endif 
