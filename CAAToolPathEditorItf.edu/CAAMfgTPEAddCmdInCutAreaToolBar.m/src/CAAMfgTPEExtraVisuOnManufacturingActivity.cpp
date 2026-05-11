//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//===================================================================
//
// CAAMfgTPEExtraVisuOnManufacturingActivity.cpp
// Provide implementation to interface CATIMfgTPEExtraVisu
//
// Sample code for : CAA Manufacturing
//
// Mission         : Customize tool path editor visualization.
//
// Type            : Interactive functionality
//
//===================================================================

#include "CAAMfgTPEExtraVisuOnManufacturingActivity.h"
 
// Manufacturing
#include "CATIMfgToolPathManagement.h"
#include "CATIMfgToolPath.h"
#include "CATIMfgToolMotion.h"
#include "CATIMfgCompoundTraject.h"

// VisualizationBase 
#include "CAT3DBagRep.h"
#include "CAT3DCustomRep.h"
#include "CAT3DPolylineGP.h"

// System 
#include "CATListOfFloat.h"

// Tie the implementation to its interface
#include "TIE_CATIMfgTPEExtraVisu.h"
TIE_CATIMfgTPEExtraVisu(CAAMfgTPEExtraVisuOnManufacturingActivity);

CATImplementClass( CAAMfgTPEExtraVisuOnManufacturingActivity,
                   DataExtension,
                   CATBaseUnknown,
                   ManufacturingActivity );
 

//========================================================================
// Constructor
//========================================================================
CAAMfgTPEExtraVisuOnManufacturingActivity::CAAMfgTPEExtraVisuOnManufacturingActivity():
    CATExtIVisu()
{
}

//========================================================================
// Destructor
//========================================================================
CAAMfgTPEExtraVisuOnManufacturingActivity::~CAAMfgTPEExtraVisuOnManufacturingActivity()
{
}
 
//========================================================================
// BuildRep()
//========================================================================
CATRep* CAAMfgTPEExtraVisuOnManufacturingActivity::BuildRep()
{
    CAT3DBagRep * pExtraRep = NULL;

    // Retrieves the tool path management interface
    CATIMfgToolPathManagement_var spMfgToolPathManagement(this);    
    if (NULL_var == spMfgToolPathManagement) return NULL;
        
    // Gets the tool path of the activity
    CATIMfgToolPath_var spMfgToolPath;
    spMfgToolPathManagement->GetToolPath(spMfgToolPath);

    // Is it a compound traject ?
    CATIMfgCompoundTraject_var spMfgCompoundTraject(spMfgToolPath);
    if (NULL_var == spMfgCompoundTraject) return NULL;

    // Retrieves all elementary trajects of the tool path
    CATListValCATBaseUnknown_var ListOfElementaryTrajects;	
    spMfgCompoundTraject->GetAllElementaryTrajects(ListOfElementaryTrajects);
    int NbOfElementaryTrajects = ListOfElementaryTrajects.Size();
    if (0 == NbOfElementaryTrajects) return NULL;

    // Get points coordinates of first middle part of tool path
    CATListOfFloat PointsCoordinates;
	for (int i = 1; i <= NbOfElementaryTrajects; i++)
	{
        CATIMfgToolMotion_var spMfgToolMotion = ListOfElementaryTrajects[i];
        if (NULL_var != spMfgToolMotion)
        {
		    int NbPoints = spMfgToolMotion->GetNumberOfTipPoints();
            for (int j = 1; j <= NbPoints /2; j++)
            {
                double TipPointCoord[3] = { 0., 0., 0.};
                if (TRUE == spMfgToolMotion->GetTipPoint(j, TipPointCoord[0], TipPointCoord[1], TipPointCoord[2]))
                {
                    PointsCoordinates.Append( (float) TipPointCoord[0]);
                    PointsCoordinates.Append( (float) TipPointCoord[1]);
                    PointsCoordinates.Append( (float) TipPointCoord[2]);
                }
            }
        }
    }

    // Creates Graphic Rep
    int NbCoord = PointsCoordinates.Size();
    if (NbCoord < 3) return NULL;
    float * pPointsArray = new float[NbCoord];
    PointsCoordinates.FillArray(pPointsArray,NbCoord);  
    CAT3DPolylineGP* p3DPolylineGP = new CAT3DPolylineGP(pPointsArray, NbCoord/3);
    if (NULL != p3DPolylineGP)
    {
        CATGraphicAttributeSet GA;
        GA.SetColor(WHITE); // White color
        GA.SetThickness(2); // 0.35mm
        GA.SetPickMode(1); // Not pickable
        
        CAT3DCustomRep* pCustomRep = new CAT3DCustomRep(p3DPolylineGP,GA);
        if (pCustomRep)
        {
            pExtraRep = new CAT3DBagRep();
            if (pExtraRep) pExtraRep->AddChild(*pCustomRep);
        }
    }
    if (pPointsArray) delete [] pPointsArray;

    return pExtraRep;
}

