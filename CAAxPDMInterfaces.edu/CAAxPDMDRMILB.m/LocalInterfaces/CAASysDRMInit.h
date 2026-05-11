/* COPYRIGHT DASSAULT SYSTEMES 2006 */
#ifndef __CAASysDRMINITH
#define __CAASysDRMINITH


#include "CATDlgDialog.h"
class CATDlgEditor;
class CATDlgMultiList;
class CATDlgCheckButton;
class CATDlgRadioButton;

class CAASysDRMInit : public CATDlgDialog
{
public:
  CAASysDRMInit();
  ~CAASysDRMInit();
private:
  void OKCB(CATCommand *, CATNotification *, CATCommandClientData);
  CATDlgRadioButton * _K128;
  CATDlgRadioButton * _K256;
};


#endif
