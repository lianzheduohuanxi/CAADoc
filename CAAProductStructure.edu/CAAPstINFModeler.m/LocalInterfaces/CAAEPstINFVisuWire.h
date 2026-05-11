// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFVisuWire_H
#define CAAEPstINFVisuWire_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFWire component, implementing the CATI3DGeoVisu 
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

// Mathematics Framework
class CATMathPoint ;

// ObjectModelerBase Framework
class CATISpecObject;
class CATLISTP(CATISpecObject) ;

class  CAAEPstINFVisuWire : public CATExtIVisu
{
    CATDeclareClass;

    public:

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFVisuWire();
    virtual ~CAAEPstINFVisuWire();

    // Constructs the CAT3DRep for the Point. 
    CATRep * BuildRep();

    // Modify the point graphic properties
    virtual void SetPointGraphicAttribute(CATRep * iRep, 
                                          CATVisPropertyType iPropertyType, 
                                          CATVisPropertiesValues & iPropertyValue);

    
    // Modify the lineic graphic properties
    virtual void SetLineGraphicAttribute(CATRep * iRep, 
                                          CATVisPropertyType iPropertyType, 
                                          CATVisPropertiesValues & iPropertyValue);
    private:

    // Copy constructor and assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEPstINFVisuWire(const CAAEPstINFVisuWire &iObjectToCopy);
    CAAEPstINFVisuWire & operator = (const CAAEPstINFVisuWire &iObjectToCopy);

    // To retrieve the coordinates from the points forming the wire
    HRESULT RetrieveCoordinates(int iNbPoint,
                        CATLISTP(CATISpecObject) * iListOfPoint,
                        float ** opCoordTable,
                        CATMathPoint & ioExtrem1,
                        CATMathPoint & ioExtrem2);

};
#endif 
