#ifndef CAAMmrCombinedCurveDlg_H
#define CAAMmrCombinedCurveDlg_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// Dialog Framework
#include "CATDlgDialog.h"  // needed to derive from CATDlgDialog
#include "CATDlgInclude.h" // needed to use Dialog framework objects

/**
* Class managing the dialog panel used for a Combined Curve creation / edition.
* 
* refer to programming resources of Dialog framework.
* (consult base class description).
*/
class CAAMmrCombinedCurveDlg: public CATDlgDialog
{
    
    DeclareResource(CAAMmrCombinedCurveDlg,CATDlgDialog);

public:
    
    CAAMmrCombinedCurveDlg();
    virtual ~CAAMmrCombinedCurveDlg();
    
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
