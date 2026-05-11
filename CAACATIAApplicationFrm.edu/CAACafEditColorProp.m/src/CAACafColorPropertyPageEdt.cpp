//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include "CAACafColorPropertyPageEdt.h"
#include "CAACafColorPropertyPageDlg.h"

// CAASystem.edu Framework
#include "CAAISysColorProperties.h"

// Visualization Framework
#include "CATPathElement.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATMsgCatalog.h"
#include "CATUnicodeString.h"

// CATIAApplicationFrame Framework 
#include "CATEditorPage.h"

// Other
#include <iostream.h>

// --------------------------------------------------------------------------
// 
// To create the TIE object 
//
#include "TIE_CATIEditProperties.h"
TIE_CATIEditProperties(CAACafColorPropertyPageEdt);

//
// To declare that CAACafColorPropertyPageEdt implements CATIEditProperties, insert 
// the following line in the interface dictionary:
//
//    CAACafColorPropertyPageEdt CATIEditProperties  libCAACafEditProp
//

// To declare that the class is a component main class 
CATImplementClass(CAACafColorPropertyPageEdt, Implementation, CATBaseUnknown , CATNull);

// --------------------------------------------------------------------------

CAACafColorPropertyPageEdt::CAACafColorPropertyPageEdt():CATEditor(),_pColorFrame(NULL)
{
  cout << "CAACafColorPropertyPageEdt::CAACafColorPropertyPageEdt()" << endl ;

  // this method is called once during the application 
}
// --------------------------------------------------------------------------
CAACafColorPropertyPageEdt::~CAACafColorPropertyPageEdt()
{
  cout << "CAACafColorPropertyPageEdt::destructor CAACafColorPropertyPageEdt()" << endl ;

  // this method is called once during the application 
  _pColorFrame = NULL ;
}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::ExtractFromSelection ( CATLISTV(CATBaseUnknown_var)& oExtract,
                                                const CATLISTV(CATBaseUnknown_var) * iSelection)
{
   cout << " CAACafColorPropertyPageEdt::ExtractFromSelection" << endl ;

   oExtract.RemoveAll();

   if ((NULL != iSelection) && ( 0 != iSelection->Size()) )
   {
      CAAISysColorProperties * pISysColorProperties = NULL ;
      HRESULT resu = E_FAIL ;

      // Analyze all Objects in the cso 
      for (int i=1 ; i<= iSelection->Size(); i++ ) 
      {
         if ( NULL_var != (*iSelection)[i]  )
         {
            // The CSO contains CATPathElement 
            CATBaseUnknown_var ukn  = (*iSelection)[i];
            if (  !! ukn )
            {
               CATBaseUnknown * pukn = (CATBaseUnknown *) ukn;

               CATPathElement path = (CATPathElement &) *pukn;
               if (  0 != path.GetSize() )
               {
                  // I retrieve the leaf of the path
                  CATBaseUnknown * pleaf = path[path.GetSize()-1];

                  if ( NULL != pleaf )
                  {
                     resu =  pleaf->QueryInterface(IID_CAAISysColorProperties,
                                                    (void**)&pISysColorProperties) ;

                     // object extracted implements CAAISysColorProperties 
                     // 
                     if ( SUCCEEDED(resu) ) 
                     {
                        oExtract.Append((*iSelection)[i]) ;
                        pISysColorProperties->Release();
                        pISysColorProperties = NULL ;
                     }
                  }
               }
           }
        }
     }
   }
}

// --------------------------------------------------------------------------
CATUnicodeString CAACafColorPropertyPageEdt::GetEditorTitle()
{
    cout << "CAACafColorPropertyPageEdt::GetEditorTitle" << endl;

    CATUnicodeString Title;

    Title = CATMsgCatalog::BuildMessage("CAACafColorPropertyPageDlg",
                                        "ColorPageTitle",
                                         NULL,0,"Color");
   

    return Title;

}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::SetEditorSize(int & oSize )
{
   cout << "CAACafColorPropertyPageEdt::SetEditorSize" << endl;
   oSize = 1;
}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::BuildEditor(CATEditorPage * iEditor)
{
  cout << "CAACafColorPropertyPageEdt::BuildEditor" << endl ;

  // Constructs an empty Dialog box
  _pColorFrame = new CAACafColorPropertyPageDlg(iEditor);

  // Creates Dialog's object of the page.
  _pColorFrame->Build();

}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::SetPropertyValue (CATLISTV(CATBaseUnknown_var)& iExtract,
                                                   ModeReadWrite iMode)
{
  cout << " CAACafColorPropertyPageEdt::SetPropertyValue" << endl ;
   _pColorFrame->SetPropertyValue(iExtract,iMode);
}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::CancelModification(CATLISTV(CATBaseUnknown_var)& extract)
{
  cout << "CAACafColorPropertyPageEdt::CancelModification" << endl ;

   _pColorFrame->CancelModification(extract);
}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::CommitModification(CATLISTV(CATBaseUnknown_var)& iExtract)
{
  cout << "CAACafColorPropertyPageEdt::CommitModification" << endl;

  _pColorFrame->CommitModification(iExtract);
}

// --------------------------------------------------------------------------
void CAACafColorPropertyPageEdt::CloseWindowFromEditor()
{
  cout << " CAACafColorPropertyPageEdt::CloseWindowFromEditor()" << endl ;
}


