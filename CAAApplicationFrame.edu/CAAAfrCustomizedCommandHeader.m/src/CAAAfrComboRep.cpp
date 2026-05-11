// COPYRIGHT DASSAULT SYSTEMES 2003

// Local framework
#include "CAAAfrComboRep.h"
#include "CAAIAfrTemporaryObjectColor.h"

// ApplicationFrame framework
#include "CATFrmEditor.h"

// Visualization Framework
#include <CATPathElement.h>

// Dialog framework
#include "CATDialog.h"
#include "CATDlgCombo.h"

// System framework
#include "CATString.h"
#include "CATBoolean.h"

#include "iostream.h"
//----------------------------------------------------------------------------

CAAAfrComboRep::CAAAfrComboRep(const CATDialog * iParent,CATString & iCommandName): 
                 CATAfrCommandHeaderRep(iParent,iCommandName)
                ,_pUIActiveObject(NULL),_pCombo(NULL)
{
   cout <<" CAAAfrComboRep::CAAAfrComboRep" << iCommandName.ConvertToChar() << endl;
   
   float val ;
   for ( int i= 0 ; i < 10 ; i++)
   {
      // red
      val = (255 * i / 9 ); 
      _ColorTable[i*3]   = (int)val;

      // green
      _ColorTable[i*3+1] = 10 ;

      // blue
      val = (255 * (9-i) / 9); 
      _ColorTable[i*3+2] = (int)val;
   }

   // Retrieve the UI active Object
   CATFrmEditor * pEditor   = CATFrmEditor::GetCurrentEditor();
   if ( NULL != pEditor )
   {
       // Retrieves the root object of the CAAGeometry model
       CATPathElement path = pEditor->GetUIActiveObject();
       if ( 0 != path.GetSize() ) 
       {
          _pUIActiveObject=path[path.GetSize()-1];

          // Keep a interface pointer = AddRef to do
          if (NULL != _pUIActiveObject)
          {
            _pUIActiveObject->AddRef();
          }
       }
   }

   // Callback to be advised when someone modifies
   // the current color
   if ( NULL != _pUIActiveObject )
   {
      ::AddCallback(this,
               _pUIActiveObject,
	           "CAAAfrComboColorNotification",
	            (CATSubscriberMethod)&CAAAfrComboRep::ModifiedCB,
	            NULL);
   }
}

//----------------------------------------------------------------------------

CAAAfrComboRep::~CAAAfrComboRep()
{
    cout <<" CAAAfrComboRep::~CAAAfrComboRep" << endl;

    if ( NULL != _pUIActiveObject )
    {
       // Callback set in the constructor
       ::RemoveSubscriberCallbacks(this, _pUIActiveObject);

        _pUIActiveObject->Release();
        _pUIActiveObject = NULL ;
    }

    const CATDialog * pParent = NULL ;
    GetDialogParent(&pParent);
    if ( NULL != pParent )
    {
      if (((CATDialog *)pParent)->GetChildCount() > 0)
      {
        if ( NULL != _pCombo )
        {
           _pCombo->RequestDelayedDestruction();
          _pCombo = NULL ;
        }
      }
    }
}

//----------------------------------------------------------------------------

HRESULT  CAAAfrComboRep::Build()
{
   cout <<" CAAAfrComboRep::Build" << endl;

   // Creation of the graphic representation 
   const CATDialog * pParent = NULL ;
   GetDialogParent(&pParent);

   _pCombo = new CATDlgCombo((CATDialog *)pParent, "CAAAfrEduCombo", CATDlgCmbColor);

   // To be prevent when the end user selects an element into the combo
   // and modify the UI active object
   AddAnalyseNotificationCB(_pCombo,
			   _pCombo->GetComboSelectNotification(),
			   (CATCommandMethod)&CAAAfrComboRep::SelectCB,
			   (CATCommandClientData)NULL);

   // Fills the combo
   for ( int i=0 ; i < 10 ; i++)
   {
     _pCombo->SetLine(CATUnicodeString(),
			(unsigned char)_ColorTable[i*3 ], 
			(unsigned char)_ColorTable[i*3+1], 
			(unsigned char)_ColorTable[i*3+2], 
			i);
   }

   // Sets the current color in the combo
   SetCurrentColor();

   // To receive notification 
   _pCombo->SetFather(this);

   return S_OK ;
}

//----------------------------------------------------------------------------

void CAAAfrComboRep::SelectCB(CATCommand * iPublishingCommand, 
			      CATNotification * iNotification, 
			      CATCommandClientData iData)
{
  cout << "CAAAfrComboRep::SelectCB " << endl;

  if ( NULL != _pUIActiveObject )
  {
    // Modifies the current color
    CAAIAfrTemporaryObjectColor * pITemporaryObjectColor = NULL ;
    HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAIAfrTemporaryObjectColor,
                                                  (void**) & pITemporaryObjectColor);
    
    if ( SUCCEEDED(rc) && (NULL != _pCombo))
    {
      int val = _pCombo->GetSelect();

      pITemporaryObjectColor->SetCurrentColor(_ColorTable[val*3 ],
                                                  _ColorTable[val*3+1],
                                                  _ColorTable[val*3+2]);

      pITemporaryObjectColor->Release();
      pITemporaryObjectColor = NULL ;
    }
  }

}

//----------------------------------------------------------------------------

HRESULT CAAAfrComboRep::SetCurrentColor()
{
    cout <<" CAAAfrComboRep::SetCurrentColor()" << _pUIActiveObject << endl;

   // Select the current color
   CAAIAfrTemporaryObjectColor * pITemporaryObjectColor = NULL ;
   HRESULT rc = E_FAIL;

   if ( NULL != _pUIActiveObject )
   {
      rc = _pUIActiveObject->QueryInterface(IID_CAAIAfrTemporaryObjectColor,
                                                    (void**) & pITemporaryObjectColor);
      
      if ( SUCCEEDED(rc) && ( NULL != _pCombo) )
      {
          int r,g,b ;
          pITemporaryObjectColor->GetCurrentColor(r,g,b);

          int position = 0 ;
          CATBoolean FOUND = FALSE ;
          while ( ( FALSE == FOUND) && ( position < 10 ))
          {
            if ( (r == _ColorTable[position*3 ]) &&
                  (g == _ColorTable[position*3+1 ]) &&
                  (b == _ColorTable[position*3+2 ]) )
            {
                FOUND = TRUE ;
                cout <<" Position Found=" << position << "For _pCombo" << _pCombo << endl;
            }else position ++ ;
          }

          if ( TRUE == FOUND) 
          {
            // The last argument specifies that no notification
            // will be sent, so SelectCB will be not called
            // so avoid a loop
            //
            _pCombo->SetSelect(position,0);
          }

          pITemporaryObjectColor->Release();
          pITemporaryObjectColor = NULL ;
      }
   }

   return rc ;
}

//----------------------------------------------------------------------------

void CAAAfrComboRep::ModifiedCB(CATCallbackEvent, 
                                void *, 
                                CATNotification *iNotification,
                                CATSubscriberData,
                                CATCallback)
{
   cout <<" CAAAfrComboRep::ModifiedCB"  << endl;

   SetCurrentColor();
}


