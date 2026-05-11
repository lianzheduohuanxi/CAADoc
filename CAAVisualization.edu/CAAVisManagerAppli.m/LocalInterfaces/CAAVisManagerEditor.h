#ifndef CAAVisManagerEditor_H
#define CAAVisManagerEditor_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
// Abstract of the class:
//  ----------------------
// Control Class .
//
//
//
//=============================================================================

// Sytem FrameWork
#include "CATBaseUnknown.h"  

// Local FrameWork
class CAAVisManagerCmdSelector;
class CAAVisManagerDocument;
class CATPSO;
class CATHSO;

class CAAVisManagerEditor : public CATBaseUnknown
{
 public:
    
    // Contructs the document from an application and a title.
    CAAVisManagerEditor(CAAVisManagerDocument *iDocument) ;

    //destructor
    virtual ~CAAVisManagerEditor();
    
    CATPSO                     * GetPSO();
    CATHSO                     * GetHSO();
    CAAVisManagerCmdSelector   * GetSelector();
    CAAVisManagerDocument      * GetDocument();

 private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerEditor();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerEditor(const CAAVisManagerEditor &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerEditor & operator = (const CAAVisManagerEditor &iObjectToCopy);
  
 private:

    //
    CAAVisManagerCmdSelector * _pSelector;

    CATPSO                   * _pPSO      ;
    CATHSO                   * _pHSO      ;
    
    // The document to visualize
    CAAVisManagerDocument    * _pDocument ;

};

#endif
