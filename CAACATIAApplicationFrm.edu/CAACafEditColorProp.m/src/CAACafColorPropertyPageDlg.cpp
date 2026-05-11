//
// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAACafColorPropertyPageDlg.h"

// CAASystem.edu Framework
#include "CAAISysColorProperties.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgSlider.h"
#include "CATDlgGridConstraints.h"

// Visualization Framework
#include "CATPathElement.h"

// C++ Standard library
#include <iostream.h>

//---------------------------------------------------------------------------------------
CAACafColorPropertyPageDlg ::CAACafColorPropertyPageDlg (CATDialog * iParent) :
 CATDlgFrame(iParent, "ColorPageFrame", CATDlgFraNoFrame|CATDlgFraNoTitle|CATDlgGridLayout),
 _pRedSlider(NULL), _pGreenSlider(NULL),_pBlueSlider(NULL)
{
   cout << "CAACafColorPropertyPageDlg ::CAACafColorPropertyPageDlg " << endl;
}

//---------------------------------------------------------------------------------------
CAACafColorPropertyPageDlg ::~CAACafColorPropertyPageDlg ()
{
   cout << "CAACafColorPropertyPageDlg ::~CAACafColorPropertyPageDlg " << endl;
   _pRedSlider   = NULL ;
   _pBlueSlider  = NULL ;
   _pGreenSlider = NULL ;
}

//---------------------------------------------------------------------------------------
void CAACafColorPropertyPageDlg ::Build()
{
   cout << "CAACafColorPropertyPageDlg ::Build Begin" << endl;

  CATDlgFrame          * pRedFrame ;
  CATDlgFrame          * pGreenFrame  ;
  CATDlgFrame          * pBlueFrame  ;

  pRedFrame   = new CATDlgFrame(this, "RedFrame",CATDlgGridLayout);                         
  pBlueFrame  = new CATDlgFrame(this, "BlueFrame",CATDlgGridLayout);                            
  pGreenFrame = new CATDlgFrame(this, "GreenFrame",CATDlgGridLayout);
                            
  _pRedSlider    = new CATDlgSlider(pRedFrame,"RedSlider");
  _pBlueSlider   = new CATDlgSlider(pBlueFrame,"BlueSlider");
  _pGreenSlider  = new CATDlgSlider(pGreenFrame,"GreenSlider");

  // Sliders with 255 steps between 0 and 255
  _pRedSlider->SetRange(0,255,255);
  _pGreenSlider->SetRange(0,255,255);
  _pBlueSlider->SetRange(0,255,255);

  pRedFrame->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
  _pRedSlider->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
  pBlueFrame->SetGridConstraints(1,0,1,1,CATGRID_LEFT);
  _pGreenSlider->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
  pGreenFrame->SetGridConstraints(2,0,1,1,CATGRID_LEFT);
  _pBlueSlider->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
 
}

//---------------------------------------------------------------------------------------
void CAACafColorPropertyPageDlg::SetPropertyValue(CATLISTV(CATBaseUnknown_var) & iExtract,
                                                  ModeReadWrite iMode)
{
   cout << " CAACafColorPropertyPageDlg SetPropertyValue" << endl;

   // From iExtract, you get the Dialog's object values 
   // In this case, the first object is taken to initialize the dialog object

   if ( iExtract.Size() > 0 )
   {
      // the first object selected
      CATBaseUnknown_var elt = (iExtract)[1];
      if ( !! elt )
      {
         CATBaseUnknown *pPath = (CATBaseUnknown *) elt;
 
         CATPathElement &path = (CATPathElement &)*pPath;

         if ( 0 != path.GetSize() )
         {
            // the leaf of the first object
            CATBaseUnknown * currentp = path[path.GetSize()-1];

            if ( NULL != currentp )
            {
               // Property values are on the CAAISysColorProperties interface
               // of the first object 
               CAAISysColorProperties * pISysTexProperties = NULL ;
               HRESULT resu =  currentp->QueryInterface(IID_CAAISysColorProperties,
                                              (void**)&pISysTexProperties) ;

               // Get values of this first object to initialize the Dialog's object
               if ( SUCCEEDED(resu) ) 
               {
                  int red,green,blue ;
                  pISysTexProperties->GetColor(red,green,blue);

                  _pRedSlider->SetCurrentValue((float)red);
                  _pGreenSlider->SetCurrentValue((float)green);
                  _pBlueSlider->SetCurrentValue((float)blue);

                  pISysTexProperties->Release();
                  pISysTexProperties = NULL ;
               }
            }
         }
      }
   }

}

//---------------------------------------------------------------------------------------
void CAACafColorPropertyPageDlg::CommitModification(CATLISTV(CATBaseUnknown_var) & iExtract)
{
   cout << " CAACafColorPropertyPageDlg CommitModification" << endl;

   HRESULT resu ;
   CAAISysColorProperties * pISysTexProperties = NULL ;

   int nb = iExtract.Size() ;
   for ( int i=1 ; i <= nb ; i++ )
   {
      // current object to modify 
      CATBaseUnknown_var elt = (iExtract)[i];
      if ( !! elt )
      {
         CATBaseUnknown *pPath = (CATBaseUnknown *) elt;
 
         CATPathElement &path = (CATPathElement &)*pPath;

         if ( 0 != path.GetSize() )
         {
             CATBaseUnknown * currentp = path[path.GetSize()-1];

             if ( NULL != currentp )
             {
                resu =  currentp->QueryInterface(IID_CAAISysColorProperties,
                                              (void**)&pISysTexProperties) ;

                // Modification of the model with the current values
                // of each slider
	        if ( SUCCEEDED(resu) ) 
                {
                    int red   = (int) _pRedSlider->GetCurrentValue();
                    int green = (int) _pGreenSlider->GetCurrentValue();
                    int blue  = (int) _pBlueSlider->GetCurrentValue();

                    pISysTexProperties->SetColor(red,green,blue);

                    pISysTexProperties->Release();
                    pISysTexProperties = NULL ;
	        }
	     }
         }
      }
   }

}

//---------------------------------------------------------------------------------------
void CAACafColorPropertyPageDlg::CancelModification(CATLISTV(CATBaseUnknown_var) & iExtract)
{
   cout << " CAACafColorPropertyPageDlg CancelModification" << endl;
   // Nothing special to do for this sample 
}

//---------------------------------------------------------------------------------------
void CAACafColorPropertyPageDlg::CloseWindowFromEditor()
{
   cout << " CAACafColorPropertyPageDlg CloseWindowFromEditor" << endl;
}
