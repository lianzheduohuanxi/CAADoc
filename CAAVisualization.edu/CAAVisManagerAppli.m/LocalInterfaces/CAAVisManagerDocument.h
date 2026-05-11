#ifndef CAAVisManagerDocument_H
#define CAAVisManagerDocument_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
// Abstract of the class:
//  ----------------------
//  Base class of the application document.
//
//
//
//=============================================================================

// Sytem FrameWork
#include "CATBaseUnknown.h"  
#include "CATString.h"  

class CAAVisManagerEditor ;
class CAAVisManagerWindow ;

class CAAVisManagerDocument : public CATBaseUnknown
{
 public:
    
    // Contructs the document from an application and a title.
    // iTitle -> the title to set in the window 
    CAAVisManagerDocument(const CATString & iTitle ) ;

    //destructor
    virtual ~CAAVisManagerDocument();
    
    // Retreives the root container of the current document. 
    // And the root container points to a model.
    CATBaseUnknown *GetRootContainer() const;

    // Adds a CGR file in the current document
    HRESULT InsertCGR(const char *iName);

    virtual CAAVisManagerWindow * CreateDefaultWindow();

 private :

    // Constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerDocument();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerDocument(const CAAVisManagerDocument &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerDocument & operator = (const CAAVisManagerDocument &iObjectToCopy);
  
    // 
    void CleanModel(CATBaseUnknown * ioObject);

 protected:

    // Root Container
    CATBaseUnknown * _pRootContainer;
    
    // It's the name of the Document class 
    CATString        _Title ;

 private:
   
    CAAVisManagerEditor * _pEditor ;
    
    // To have a different indice for the Window Identificator 
    static int            _ViewIndice ;

};

#endif
