// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerApplicationFrame.h"

#include <iostream.h>
//-------------------------------------------------------------------------------

CAAVisManagerApplicationFrame::CAAVisManagerApplicationFrame(CATInteractiveApplication *iParent,
                                                             const CATString& iObjectName, 
                                                             CATDlgStyle iStyle) : 
                               CATDlgDocument(iParent,iObjectName,iStyle)
{

}

//-------------------------------------------------------------------------------

CAAVisManagerApplicationFrame::~CAAVisManagerApplicationFrame()
{
   cout << " CAAVisManagerApplicationFrame::~CAAVisManagerApplicationFrame() " << endl;
}
