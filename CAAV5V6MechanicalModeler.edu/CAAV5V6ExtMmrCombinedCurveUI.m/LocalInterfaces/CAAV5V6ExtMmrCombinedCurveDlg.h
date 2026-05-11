#ifndef CAAV5V6ExtMmrCombinedCurveDlg_H
#define CAAV5V6ExtMmrCombinedCurveDlg_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// Dialog Framework
#include "CATDlgDialog.h"  // needed to derive from CATDlgDialog
#include "CATDlgInclude.h" // needed to use Dialog framework objects

/**
* Class managing the dialog panel used for a Combined Curve creation / edition.
* 
* refer to programming resources of Dialog framework.
* (consult base class description).
*/
// Note : CAAV5V6ExtMmrCombCrvPanelStCmd is the same use case as CAAMmrCombCrvPanelStCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//

class CAAV5V6ExtMmrCombinedCurveDlg: public CATDlgDialog
{
    
    DeclareResource(CAAV5V6ExtMmrCombinedCurveDlg,CATDlgDialog);

public:
    
    CAAV5V6ExtMmrCombinedCurveDlg();
    virtual ~CAAV5V6ExtMmrCombinedCurveDlg();
    
    /**
    * Builds the panel with its control.
    */
    void Build ();
    
    /**
    * Sets the focus on the active entry field ( one of the four fields for Curve.1 to Direction.2 )
    */
    void SetActiveField( int iFieldNumber );

    /**
    * Writes name in the field_number-th field.
    */
    void SetName( int iFieldNumber , CATUnicodeString iName );
    
    /**
    * Returns the field_number-th field of the panel.
    */
    CATDlgSelectorList* GetField(int iFieldNumber );
    
    
private:
    
    CATDlgSelectorList *_sel_curve1 ,
                       *_sel_curve2 ,
                       *_sel_dir1 ,
                       *_sel_dir2;

};

#endif
