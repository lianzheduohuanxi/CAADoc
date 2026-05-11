#ifndef CAAVisManagerCGRDocument_H
#define CAAVisManagerCGRDocument_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  The CGR document.
//  This class defines a document which load a CGR file and allows to visualize it into
//  a 3D viewer. As it derives from the basic class of any document type CAAVisModelDocument
//  it inherits from its behavior and its management.
//=============================================================================
//  Inheritance:
//  ------------
//            - CAAVisManagerCGRDocument 
//                 - CAAVisModelDocument (Local Framework)
//
//=============================================================================
//  Main Method:
//  ------------
// CreateModel : read the CGR file and visualize the CGR model into a 3D viewer.
//=============================================================================

//Local FrameWork
#include "CAAVisManagerDocument.h"

class CAAVisManagerCGRDocument : public CAAVisManagerDocument
{
public :

   CAAVisManagerCGRDocument ( const char      * iFileName);

   //Destructor.
   virtual ~CAAVisManagerCGRDocument();

private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCGRDocument ();
        
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCGRDocument(const CAAVisManagerCGRDocument &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCGRDocument & operator = (const CAAVisManagerCGRDocument &iObjectToCopy);

    // Creation of the Root Object 
    virtual void CreateModel(const char * iFileName);

};

#endif
