#ifndef CAAVisManagerDefaultDocument_H
#define CAAVisManagerDefaultDocument_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//Local FrameWork
#include "CAAVisManagerDocument.h" // to derive from 

class CAAVisManagerDefaultDocument : public CAAVisManagerDocument
{
public :

   CAAVisManagerDefaultDocument ();
   virtual ~CAAVisManagerDefaultDocument();

private:
       
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerDefaultDocument(const CAAVisManagerDefaultDocument &iObjToCop);
       
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerDefaultDocument & operator = (const CAAVisManagerDefaultDocument &iObjToCop);
       
    // Creation of the Root object
    void CreateModel();
};


#endif
