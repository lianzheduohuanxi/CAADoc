// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADegPointErrorBox.h"

// System FW
#include "CATMsgCatalog.h"

//C++ Standard library
#include "iostream.h"

//---------------------------------------------------------------------------

CAADegPointErrorBox::CAADegPointErrorBox(CATDialog * iParent,const int iFirstPoint,const int iSecondPoint): 
        CATDlgNotify (iParent, 
		      "PointErrorId", 
               CATDlgNfyError| CATDlgNfyOK | CATDlgWndModal),
	_FirstPoint(iFirstPoint),
	_SecondPoint(iSecondPoint)
                             
{
  cout << "CAADegPointErrorBox::CAADegPointErrorBox" << endl; 
}

CAADegPointErrorBox::~CAADegPointErrorBox()
{
  cout << "CAADegPointErrorBox::~CAADegPointErrorBox" << endl;
}

//-------------------------------------------------------------------------

void CAADegPointErrorBox::Build()
{
   cout << "CAADegPointErrorBox::Build" << endl;
  
   CATUnicodeString Msg ;

   CATUnicodeString param[2];
   param[0].BuildFromNum(_FirstPoint);
   param[1].BuildFromNum(_SecondPoint);

   CATUnicodeString Msg1("Points ");
   CATUnicodeString Msg2(" and ");
   CATUnicodeString Msg3(" are the same.");
   CATUnicodeString defaultMsg = "";
   defaultMsg.Append(Msg1);
   defaultMsg.Append(param[0]);
   defaultMsg.Append(Msg2);
   defaultMsg.Append(param[1]);
   defaultMsg.Append(Msg3);

   Msg = CATMsgCatalog::BuildMessage("CAADegPointErrorBox", // catalog name
                        "Phrase",    // key string
                        param,       // parameters
                        2,           // number of parameters
                        defaultMsg); // default message

   SetText(Msg);

   //Callback
   AddAnalyseNotificationCB(this, this->GetNfyOKNotification(),
                (CATCommandMethod)&CAADegPointErrorBox::ClickOK,
                            NULL);

   AddAnalyseNotificationCB(this, this->GetWindCloseNotification(),
                (CATCommandMethod)&CAADegPointErrorBox::ClickOK,
                            NULL);
}

//-----------------------------------------------------------------------

void CAADegPointErrorBox::ClickOK    (CATCommand          * iPublisher,
                                      CATNotification     * iNotification,
                                      CATCommandClientData  iUsefulData)
{
   cout << "CAADegPointErrorBox::ClickOK" << endl;

   RequestDelayedDestruction();
}
