#ifndef CAAOmbNavigModifyRoot_h
#define CAAOmbNavigModifyRoot_h
// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//
//  This is an implementation of the CATINavigModify interface.
//  
//=============================================================================
//  Execute the Use Case:
//  --------------------
//  To execute this Use Case, you must be in a CATIA V5 session.  Create a new
//  document of type "CAAGeometry".  Create geometric elements in the document.  
//  Select the root node "CAASysGeomRootObj":  a tree is displayed containing 
//  the names of all of the elements existing in the document.  
//
//  CATINavigModify::UpdateElem allows the modification of tree nodes by changing
//  node colors using CATIGraphNode::SetColor and by adding icons to nodes using 
//  CATIGraphNode::SetPixelImage.
//
//******************************************************************************

// ObjectModelerBase Framework
#include "CATNodeExtension.h"             // Needed to derive from

// ObjectModelerBase Framework
class CATNavigInstance;

class CAAOmbNavigModifyRoot : public CATNodeExtension
{
   // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAOmbNavigModifyRoot();
    virtual ~CAAOmbNavigModifyRoot();
	
    // UpdateElem
    // ----------
    // Creates the graphical node representation 
    //
    void UpdateElem(CATNavigInstance * iInstance);
 
  private :

    // Copy constructor, not implemented
    // Set as private to prevent the automatic creation as public by the compiler.
    CAAOmbNavigModifyRoot(const CAAOmbNavigModifyRoot &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAOmbNavigModifyRoot & operator = (const CAAOmbNavigModifyRoot &iObjectToCopy);
};

#endif
