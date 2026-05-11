// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef CAA2DLWindowWarning_H
#define CAA2DLWindowWarning_H

#include "CATDlgNotify.h"


class CATString;
class CATUnicodeString;
class CATDialog;
  

/**
 * Notification dialog box. 
 * The added feature compared to a usual CATDlgNotify is that this class manages 
 * its own destruction, so no callback to add on Unix OS, nor RequestDelayedDestruction() 
 * to be called.
 */
class CAA2DLWindowWarning : public CATDlgNotify
{

  public:


/**
 * Constructor. @see CATDlgNotify.
 */
	CAA2DLWindowWarning(CATDialog *iParent, const CATString & , const CATUnicodeString & , CATDlgStyle);
   

  protected:

/**
 * @nodoc .
 */		
	~CAA2DLWindowWarning();

  private:
  
  CAA2DLWindowWarning (const CAA2DLWindowWarning&);
  CAA2DLWindowWarning &operator = (const CAA2DLWindowWarning&);
  
  void PushOk (CATCommand *, CATNotification *, CATCommandClientData); 
};

/**
 * creates a window of current CATApplicationFrame
 */
CAA2DLWindowWarning* CAA2DLWindowCreateMsgBox(const CATString & , const CATUnicodeString & , CATDlgStyle);

#endif
