// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAACafComboWindow.h"

// Dialog Framework
#include "CATInteractiveApplication.h" // For the current application to destroy

// CATIAApplicationFrame Framework
#include "CATComboColor.h"
#include "CATComboSymbol.h"
#include "CATComboDashed.h"
#include "CATComboWeight.h"

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAACafComboWindow::CAACafComboWindow(CATInteractiveApplication * iParentCommand)
: CATDlgDocument(iParentCommand, "CAACafComboWindowId"),
  _pApplication(iParentCommand),
  _pComboColor(NULL),
  _pComboWeight(NULL),
  _pComboSymbol(NULL),
  _pComboDashed(NULL)

{
  cout << "CAACafComboWindow::CAACafComboWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAACafComboWindow::~CAACafComboWindow()
{ 
  cout << "CAACafComboWindow::~CAACafComboWindow" << endl; 
  _pApplication = NULL ;
  _pComboColor=NULL ;
  _pComboWeight=NULL; 
  _pComboSymbol=NULL; 
  _pComboDashed=NULL;
}

//--------------------------------------------------------------------------------------

void CAACafComboWindow::Build()
{
  cout << "CAACafComboWindow::Build" << endl;

  // Constructs the CATComboColor 
  // The first color is white (255,255,255)
  _pComboColor = new CATComboColor(this,"ComboColorId") ;

  // Constructs the CATComboSymbol 
  // The first symbol is a plus
  _pComboSymbol = new CATComboSymbol(this,"ComboSymbolId",NULL,2) ;

  // Constructs the CATComboDashed 
  // The first type of line is solid (1)
  _pComboDashed = new CATComboDashed(this,"ComboDashedId") ;

  // Constructs the CATComboWeight 
  // The first thickness (weight) is the 25 ieme 
  _pComboWeight = new CATComboWeight(this,"ComboWeightId",NULL,25) ;

  // Sets a callback to get the color 
  AddAnalyseNotificationCB(_pComboColor,
                           "CATDlgComboSelectNotification",
                           (CATCommandMethod)&CAACafComboWindow::ColorSelected, NULL);

  // Sets a callback to get the symbol 
  AddAnalyseNotificationCB(_pComboSymbol,
                           "CATDlgComboSelectNotification",
                           (CATCommandMethod)&CAACafComboWindow::SymbolSelected, NULL);

  // Sets a callback to get the line type 
  AddAnalyseNotificationCB(_pComboDashed,
                           "CATDlgComboSelectNotification",
                           (CATCommandMethod)&CAACafComboWindow::LineTypeSelected, NULL);

  // Sets a callback to get the line weight 
  AddAnalyseNotificationCB(_pComboWeight,
                           "CATDlgComboSelectNotification",
                           (CATCommandMethod)&CAACafComboWindow::LineWeightSelected, NULL);

  // On the Close 
  AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAACafComboWindow::Exit, NULL);

}

//--------------------------------------------------------------------------------------

void CAACafComboWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAACafComboWindow::ColorSelected(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   cout << "CAACafComboWindow::ColorSelected is"<< endl;

   unsigned int r,v,b ;
   _pComboColor->GetSelectedColor(&r,&v,&b);

   cout << "r="<< r << " v="<< v << " b="<< b << endl;
}

//------------------------------------------------------------------------------

void CAACafComboWindow::SymbolSelected(CATCommand         * iSendingCommand,
                           CATNotification    * iSentNotification,
                           CATCommandClientData iUsefulData)
{
   cout << "CAACafComboWindow::SymbolSelected is"<< endl;

   unsigned int symbol = _pComboSymbol->GetSelect();

   cout << "Index of the symbol is= " << symbol << endl;
}
//------------------------------------------------------------------------------

void CAACafComboWindow::LineTypeSelected(CATCommand         * iSendingCommand,
                           CATNotification    * iSentNotification,
                           CATCommandClientData iUsefulData)
{
   cout << "CAACafComboWindow::LineTypeSelected is"<< endl;

   unsigned int linetype = _pComboDashed->GetSelect();

   cout << "Index of the line type is= " << linetype << endl;

}
//------------------------------------------------------------------------------

void CAACafComboWindow::LineWeightSelected(CATCommand         * iSendingCommand,
                           CATNotification    * iSentNotification,
                           CATCommandClientData iUsefulData)
{
   cout << "CAACafComboWindow::LineWeightSelected is"<< endl;

   unsigned int lineweight = _pComboWeight->GetSelect();

   cout << "Index of the line weight is= " << lineweight << endl;
}
//------------------------------------------------------------------------------

