//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include "CAACafTexturePropertyPageDlg.h"
#include "CAAISysTextureProperties.h"

// Dialog Framework
#include "CATDlgCheckButton.h"

// Visaulization Framework
#include "CATPathElement.h"

// others
#include <iostream.h>

//-----------------------------------------------------------------------
CAACafTexturePropertyPageDlg ::CAACafTexturePropertyPageDlg (CATDialog * iParent) :
 CATDlgFrame(iParent, "TexturePageFrame", CATDlgFraNoFrame|CATDlgFraNoTitle),
 _pMetal(NULL), _pRough(NULL)
{
   cout << "CAACafTexturePropertyPageDlg ::CAACafTexturePropertyPageDlg " << endl;
}

//-----------------------------------------------------------------------
CAACafTexturePropertyPageDlg ::~CAACafTexturePropertyPageDlg ()
{
   cout << "CAACafTexturePropertyPageDlg ::~CAACafTexturePropertyPageDlg " << endl;
   // These Dialog's object are automatically deleted .
  _pMetal = NULL ;
  _pRough = NULL ;
}

//-----------------------------------------------------------------------
void CAACafTexturePropertyPageDlg ::Build()
{
   cout << "CAACafTexturePropertyPageDlg ::Build Begin" << endl;

  _pMetal  = new CATDlgCheckButton(this,"Metal");
  _pRough  = new CATDlgCheckButton(this,"Rough");

}

//-----------------------------------------------------------------------
void CAACafTexturePropertyPageDlg::SetPropertyValue(CATLISTV(CATBaseUnknown_var) & iExtract,
                                                    ModeReadWrite iMode)
{
   cout << " CAACafTexturePropertyPageDlg SetPropertyValue" << endl;

   // From iExtract, you get the Dialog's object values 
   // In this case, the first object is taken to initialize the dialog object

   _pMetal->SetState(CATDlgCheck);
   _pRough->SetState(CATDlgCheck);
   
   int IsMetalic = 1 ;
   int IsRough   = 1 ;

   if ( iExtract.Size() > 0 )
   {
      // the first object selected
      CATBaseUnknown_var elt = (iExtract)[1];
      if ( !! elt )
      {
         CATBaseUnknown *pPath = (CATBaseUnknown *) elt;

         CATPathElement &path = (CATPathElement &)*pPath;

         if (path.GetSize() > 0 )
         {
            // the leaf of the first object
            CATBaseUnknown * currentp = path[path.GetSize()-1];

            if ( NULL != currentp )
            {
               // Property values are on the CAAISysTextureProperties interface
               // of the first object 
               CAAISysTextureProperties * pISysTexProperties = NULL ;
               HRESULT resu =  currentp->QueryInterface(IID_CAAISysTextureProperties,
                                              (void**)&pISysTexProperties) ;

               // Get values of this first object to initialize the Dialog's object
               if ( SUCCEEDED(resu) ) 
               {
                  pISysTexProperties->GetMetal(IsMetalic);
                  if ( 0 == IsMetalic ) _pMetal->SetState(CATDlgUncheck);
                  pISysTexProperties->GetRough(IsRough);
                  if (  0 == IsRough   ) _pRough->SetState(CATDlgUncheck);

                  pISysTexProperties->Release();
                  pISysTexProperties = NULL;
               }
            }
         }
      }
   }

}

//----------------------------------------------------------------------- 
void CAACafTexturePropertyPageDlg::CommitModification(CATLISTV(CATBaseUnknown_var) & iExtract)
{
   cout << " CAACafTexturePropertyPageDlg CommitModification" << endl;

   HRESULT resu ;
   CAAISysTextureProperties * pISysTexProperties = NULL ;

   int nb = iExtract.Size() ;
   for ( int i=1 ; i <= nb ; i++ )
   {
      // current object to modify 
      CATBaseUnknown_var elt = (iExtract)[i];
      if ( !! elt)
      {
         CATBaseUnknown *pPath = (CATBaseUnknown *) elt;

         CATPathElement &path = (CATPathElement &)*pPath;
   
         if (path.GetSize() > 0  )
         {
            CATBaseUnknown * currentp = path[path.GetSize()-1];
   
            if ( NULL != currentp )
            { 
                resu =  currentp->QueryInterface(IID_CAAISysTextureProperties,
                                                 (void**)&pISysTexProperties) ;
   
                // Modification of the model with the current values
                if ( SUCCEEDED(resu) ) 
                {
                   if ( _pMetal->GetState() == CATDlgCheck )
                      pISysTexProperties->SetMetal(1);
                   else
                      pISysTexProperties->SetMetal(0);
   
                   if ( _pRough->GetState() == CATDlgCheck )
                      pISysTexProperties->SetRough(1);
                   else
                      pISysTexProperties->SetRough(0);
   
                   pISysTexProperties->Release();
                   pISysTexProperties = NULL ;
                }
             }
         }
      }
   }

}

//-----------------------------------------------------------------------
void CAACafTexturePropertyPageDlg::CancelModification(CATLISTV(CATBaseUnknown_var) & iExtract)
{
	cout << " CAACafTexturePropertyPageDlg CancelModification" << endl;
	// Nothing special to do for this sample 
}

//-----------------------------------------------------------------------
void CAACafTexturePropertyPageDlg::CloseWindowFromEditor()
{
	cout << " CAACafTexturePropertyPageDlg CloseWindowFromEditor" << endl;
}
