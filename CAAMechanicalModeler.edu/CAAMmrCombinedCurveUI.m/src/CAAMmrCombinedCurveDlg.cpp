// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAMmrCombinedCurveDlg.h"   

//ApplicationFrame Framework
#include "CATApplicationFrame.h"    // needed to get the window of the frame

//Dialog Framework
#include "CATDlgGridConstraints.h"  // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"

//System Framework
#include "CATUnicodeString.h"
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------

CAAMmrCombinedCurveDlg::CAAMmrCombinedCurveDlg( ) :
CATDlgDialog ( ( CATApplicationFrame::GetApplicationFrame() ) -> GetMainWindow ( ) ,
               "CombinedCurve", 
               CATDlgGridLayout | CATDlgWndOK | CATDlgWndCANCEL | CATDlgWndNoResize ),
_sel_curve1   ( NULL ),
_sel_curve2   ( NULL ),
_sel_dir1     ( NULL ),
_sel_dir2     ( NULL )
{
    // never call the Build method of the panel from the constructor
    // it is much better to call it from the same method that created (new) the panel
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------

CAAMmrCombinedCurveDlg::~CAAMmrCombinedCurveDlg()
{
    //  Do not delete the control elements of your dialog: 
    //     this is done automatically
    //  --------------------------------------------------
    
    _sel_curve1   = NULL ;
    _sel_curve2   = NULL ;
    _sel_dir1     = NULL ;
    _sel_dir2     = NULL ;


}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::Build()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::Build()
{
    // Creates the CATDlgLabel for the input field's names.

    CATDlgLabel * label_curve1 = new CATDlgLabel( this , CATString("labelc1") );
    
    CATDlgLabel * label_dir1 = new CATDlgLabel( this , CATString("labeld1") );
    
    CATDlgLabel * label_curve2 = new CATDlgLabel( this , CATString("labelc2") );
    
    CATDlgLabel * label_dir2 = new CATDlgLabel( this , CATString("labeld2") );
    
    // Creates the four input fields .
    CATUnicodeString Prompt_nosel = "no selection";

    _sel_curve1 = new CATDlgSelectorList( this , CATString("selc1"),CATDlgDataModify);
    _sel_curve1->SetVisibleTextHeight(1);
    _sel_curve1->SetLine(Prompt_nosel,0,CATDlgDataModify);

    _sel_dir1   = new CATDlgSelectorList( this , CATString("seld1"),CATDlgDataModify);
    _sel_dir1->SetVisibleTextHeight(1);
    _sel_dir1->SetLine(Prompt_nosel,0,CATDlgDataModify);

    _sel_curve2 = new CATDlgSelectorList( this , CATString("selc2"),CATDlgDataModify);
    _sel_curve2->SetVisibleTextHeight(1);
    _sel_curve2->SetLine(Prompt_nosel,0,CATDlgDataModify);
    
    _sel_dir2   = new CATDlgSelectorList( this , CATString("seld2"),CATDlgDataModify);
    _sel_dir2->SetVisibleTextHeight(1);
    _sel_dir2->SetLine(Prompt_nosel,0,CATDlgDataModify);
        
    
    // Uses the grid of the panel to position the label and the input fields.
    CATDlgGridConstraints cst;  
    cst.Justification = CATGRID_4SIDES;
    cst.H_Span=1;     cst.V_Span=1;
    
    // first column : labels.
    cst.Column=0;     
    
    cst.Row=0; label_curve1 -> SetGridConstraints(cst);
    cst.Row=1; label_dir1   -> SetGridConstraints(cst);
    cst.Row=2; label_curve2 -> SetGridConstraints(cst);
    cst.Row=3; label_dir2   -> SetGridConstraints(cst);
        
    // second column : input fields.
    cst.Column=1;     
    
    cst.Row=0; _sel_curve1 -> SetGridConstraints(cst);
    cst.Row=1; _sel_dir1   -> SetGridConstraints(cst);
    cst.Row=2; _sel_curve2 -> SetGridConstraints(cst);
    cst.Row=3; _sel_dir2   -> SetGridConstraints(cst);
    
    // Finally, makes the panel appear.
    SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::SetActiveField()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::SetActiveField(int iFieldNumber)
{
    //  Deselects all others field when changing of active field ( by clicking in another one ).
    if ( 1 != iFieldNumber ) _sel_curve1 -> ClearSelect();
    if ( 2 != iFieldNumber ) _sel_dir1   -> ClearSelect();
    if ( 3 != iFieldNumber ) _sel_curve2 -> ClearSelect();
    if ( 4 != iFieldNumber ) _sel_dir2   -> ClearSelect();
    return ;
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::SetName()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::SetName(int iFieldNumber , CATUnicodeString iName )
{
    // Writes the name of the selected objet in the active field.
    // Replaces it if the object was already selected.
    
    switch (iFieldNumber )
    {
    case 1 : { _sel_curve1 -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case 2 : { _sel_dir1   -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case 3 : { _sel_curve2 -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case 4 : { _sel_dir2   -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    }
    return ;
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::GetField()
//-------------------------------------------------------------------------

CATDlgSelectorList* CAAMmrCombinedCurveDlg::GetField(int iFieldNumber)
{
    // returns the active field ( used by the state command ).
    switch (iFieldNumber )
    {   
    case 1 : return _sel_curve1;
    case 2 : return _sel_dir1 ;
    case 3 : return _sel_curve2;
    case 4 : return _sel_dir2;
    }
    return NULL ;
}

