//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//
// Local Framework
#include "CAACafTexturePropertyPageEdt.h"
#include "CAACafTexturePropertyPageDlg.h"

// CAASystem.edu Framework
#include "CAAISysTextureProperties.h"

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
TIE_CATIEditProperties(CAACafTexturePropertyPageEdt);

// To declare that the class is a component main class 
CATImplementClass(CAACafTexturePropertyPageEdt, Implementation, CATBaseUnknown , CATNull);

//
// To declare that CAACafTexturePropertyPageEdt implements CATIEditProperties, insert 
// the following line in the interface dictionary:
//
//    CAACafTexturePropertyPageEdt CATIEditProperties  libCAACafEditTextureProp
//
// --------------------------------------------------------------------------

CAACafTexturePropertyPageEdt::CAACafTexturePropertyPageEdt():CATEditor(),_pTextureFrame(NULL)
{
    cout << "CAACafTexturePropertyPageEdt::CAACafTexturePropertyPageEdt()" << endl ;

    // this method is called once during the application 
}

// --------------------------------------------------------------------------
CAACafTexturePropertyPageEdt::~CAACafTexturePropertyPageEdt()
{
   cout << "CAACafTexturePropertyPageEdt::destructor CAACafTexturePropertyPageEdt()" << endl ;

   // this method is called once during the application 
   _pTextureFrame = NULL ;
}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::ExtractFromSelection ( CATLISTV(CATBaseUnknown_var)& oExtract,
                                                 const CATLISTV(CATBaseUnknown_var) * iSelection)
{
   cout << " CAACafTexturePropertyPageEdt::ExtractFromSelection" << endl ;

   oExtract.RemoveAll();

   if ( (NULL !=iSelection) && ( 0 != iSelection->Size()) )
   {
      CAAISysTextureProperties * pISysTexProperties = NULL ;
      HRESULT resu = E_FAIL;

      // Analyze all Objects in the cso 
      int nb = iSelection->Size() ;
      for (int i=1 ; i<= nb; i++ ) 
      {
         if ( NULL_var != (*iSelection)[i]  )
         {
            // The CSO contains CATPathElement 
            CATBaseUnknown_var ukn  = (*iSelection)[i];
            if ( !! ukn )
            {
               CATBaseUnknown * pukn = (CATBaseUnknown *) ukn;

               CATPathElement path = (CATPathElement &) *pukn;
               if ( 0 !=  path.GetSize() )
               {
                  // I retrieve the leaf of the path
                  CATBaseUnknown * pleaf = path[path.GetSize()-1];

                  if ( NULL != pleaf )
                  {
                     resu =  pleaf->QueryInterface(IID_CAAISysTextureProperties,
                                                    (void**)&pISysTexProperties) ;

                     // object extracted implements CAAISysTextureProperties 
                     // 
                     if ( SUCCEEDED(resu) ) 
                     {
                        oExtract.Append((*iSelection)[i]) ;
                        pISysTexProperties->Release();
                        pISysTexProperties = NULL ;
                     }
                  }
               }
            }
         }
     }
   }
}

// --------------------------------------------------------------------------
CATUnicodeString CAACafTexturePropertyPageEdt::GetEditorTitle()
{
    cout << "CAACafTexturePropertyPageEdt::GetEditorTitle" << endl;

    CATUnicodeString Title;

    Title = CATMsgCatalog::BuildMessage("CAACafTexturePropertyPageDlg",
                                        "TexturePageTitle",
                                         NULL,0,"Texture");
   

    return Title;

}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::SetEditorSize(int & oSize )
{
   cout << "CAACafTexturePropertyPageEdt::SetEditorSize" << endl;
   oSize = 1;
}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::BuildEditor(CATEditorPage * iEditor)
{
  cout << "CAACafTexturePropertyPageEdt::BuildEditor" << endl ;

  // Constructs an empty Dialog box
  _pTextureFrame = new CAACafTexturePropertyPageDlg(iEditor);

  // Creates Dialog's object of the page.
  _pTextureFrame->Build();

}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::SetPropertyValue (CATLISTV(CATBaseUnknown_var)& iExtract,
                                                     ModeReadWrite iMode)
{
   cout << " CAACafTexturePropertyPageEdt::SetPropertyValue" << endl ;
   _pTextureFrame->SetPropertyValue(iExtract,iMode);
}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::CancelModification(CATLISTV(CATBaseUnknown_var)& extract)
{
   cout << "CAACafTexturePropertyPageEdt::CancelModification" << endl ;

   _pTextureFrame->CancelModification(extract);
}

// --------------------------------------------------------------------------
void CAACafTexturePropertyPageEdt::CommitModification(CATLISTV(CATBaseUnknown_var)& iExtract)
{
  cout << "CAACafTexturePropertyPageEdt::CommitModification" << endl;

  _pTextureFrame->CommitModification(iExtract);
}

// -------------------------------------------------------------------------- 
void CAACafTexturePropertyPageEdt::CloseWindowFromEditor()
{
  cout << " CAACafTexturePropertyPageEdt::CloseWindowFromEditor()" << endl ;
}


