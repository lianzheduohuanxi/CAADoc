// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
//   
//  Interactive command
//
//    Command to select a 3D annotation and edit Unicode description
//
//=============================================================================
//  Usage:
//  ------
//
//=============================================================================
//  Main Methods:
//  ------------
//
//
//=============================================================================

#ifndef CAATpiDumpTextContentCmd_H
#define CAATpiDumpTextContentCmd_H

#include "CATStateCommand.h"

class CATPathElementAgent;
class CATDlgDialog;
class CATDlgEditor;
class CATUnicodeString;

//-----------------------------------------------------------------------------
class CAATpiDumpTextContentCmd : public CATStateCommand
{
  CmdDeclareResource (CAATpiDumpTextContentCmd, CATStateCommand)

public:

  CAATpiDumpTextContentCmd ();
  ~CAATpiDumpTextContentCmd ();

  void BuildGraph ();

  CATStatusChangeRC Activate(CATCommand *,CATNotification *);

  boolean DumpTextContentOnSelection (void * ipData);

  void MyClose(CATCommand * iCommand, CATNotification * iNotif, CATCommandClientData iData);

private:
  // must not be implemented for command
  CAATpiDumpTextContentCmd (CAATpiDumpTextContentCmd &);
  CAATpiDumpTextContentCmd& operator=(CAATpiDumpTextContentCmd&);

  void AddHexaDisplayToText(CATUnicodeString & ioText);

  CATPathElementAgent * _pAcquisitionAgent;
  CATDlgDialog * _pFrame;
  CATDlgEditor * _pEditor;
};
#endif


