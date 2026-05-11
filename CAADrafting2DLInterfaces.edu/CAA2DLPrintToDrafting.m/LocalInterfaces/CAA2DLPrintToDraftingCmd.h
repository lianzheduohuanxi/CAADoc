// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//  Abstract of the sample:
//  ----------------------
//   
//  Interactive command
//
//    This command launches a batch to create a Drawing from 2DLayout 
//    and print the active sheet of the drawing
//=============================================================================
//=============================================================================

#ifndef CAA2DLPrintToDraftingCmd_H
#define CAA2DLPrintToDraftingCmd_H


#include "CATCommand.h"

//-----------------------------------------------------------------------------
class CAA2DLPrintToDraftingCmd : public CATCommand
{
   // CmdDeclareResource (CAA2DLPrintToDraftingCmd, CATCommand);

  public:

    CAA2DLPrintToDraftingCmd (CATString * iArgument);
    virtual ~CAA2DLPrintToDraftingCmd ();

    virtual CATStatusChangeRC Activate ( CATCommand* FromClient, CATNotification* EvtDat );

  private:
    // must not be implemented for command
    CAA2DLPrintToDraftingCmd (CAA2DLPrintToDraftingCmd &);
    CAA2DLPrintToDraftingCmd& operator=(CAA2DLPrintToDraftingCmd&);


};
#endif
