// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFVisuPoint_H
#define CAAEPstINFVisuPoint_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFPoint component, implementing the CATI3DGeoVisu 
//  interface to enable the visualization of a line.
//
//  This class derives from the CATExtIVisu adapter.
//
//  Illustrates programming the visualization of an object by implementing the
//  CATI3DGeoVisu interface of the Visualization framework.
//
//  Inheritance:
//  ------------
//            
//  CATExtIVisu (Visualization)
//     CATBaseUnknown (System Framework)  
//
//===========================================================================

// Visualization Framework
#include "CATExtIVisu.h" // Visualization Framework

class  CAAEPstINFVisuPoint : public CATExtIVisu
{
    CATDeclareClass;

    public:

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFVisuPoint();
    virtual ~CAAEPstINFVisuPoint();

    // Constructs the CAT3DRep for the Point. 
    CATRep * BuildRep();

    // Modify the graphic properties
    virtual void SetPointGraphicAttribute(CATRep * iRep, 
                                          CATVisPropertyType iPropertyType, 
                                          CATVisPropertiesValues & iPropertyValue);

    private:

    // Copy constructor and assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEPstINFVisuPoint(const CAAEPstINFVisuPoint &iObjectToCopy);
    CAAEPstINFVisuPoint & operator = (const CAAEPstINFVisuPoint &iObjectToCopy);
};
#endif 
