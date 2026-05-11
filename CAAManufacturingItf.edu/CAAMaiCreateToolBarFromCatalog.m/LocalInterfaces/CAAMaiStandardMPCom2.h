//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
// 
// Class CAAMaiStandardMPCom2: command for Machining process application 
//=============================================================================
#ifndef CAAMaiStandardMPCom2_H
#define CAAMaiStandardMPCom2_H
//
//========================================================================
// DCN V5R11  28/11/02  Creation
//========================================================================

#include "CATListOfCATUnicodeString.h"
#include "CATCommand.h"

class CATNotification;
class CATUnicodeString;

class  CAAMaiStandardMPCom2 : public CATCommand
{
  public:
	    
    CAAMaiStandardMPCom2 (const CATString * iIdentifier);

    virtual ~CAAMaiStandardMPCom2 ();
	
    CATStatusChangeRC Activate(CATCommand* c, CATNotification* notif);
    
  private:

    // ---> Pas d implementation du copy constructor et de l operateur "="
    CAAMaiStandardMPCom2 (CAAMaiStandardMPCom2 &);
    CAAMaiStandardMPCom2& operator=(CAAMaiStandardMPCom2&);
};
#endif 
