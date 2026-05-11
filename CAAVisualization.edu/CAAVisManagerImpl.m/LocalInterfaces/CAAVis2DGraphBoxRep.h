#ifndef CAAVis2DGraphBoxRep_H
#define CAAVis2DGraphBoxRep_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// Visualization FW
#include "CAT2DBagRep.h" // To derive from

#define BOXWIDTH  11.0
#define BOXHEIGHT 8.0


class CAAVis2DGraphBoxRep : public CAT2DBagRep
{
   public : 

    CAAVis2DGraphBoxRep(const char * title,
                        float height=BOXHEIGHT, 
                        float width=BOXWIDTH);

    virtual ~CAAVis2DGraphBoxRep();

   private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVis2DGraphBoxRep ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVis2DGraphBoxRep(const CAAVis2DGraphBoxRep &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVis2DGraphBoxRep & operator = (const CAAVis2DGraphBoxRep &iObjectToCopy);

};

#endif
