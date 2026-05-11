#ifndef CAAGSMFrmSelectorCtxMenuDef_H
#define CAAGSMFrmSelectorCtxMenuDef_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMFrmSelectorCtx
//---------------------------------------------------------------------
// 
//  Defines  for contextual menu activation 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------


#include "CATDataType.h"

typedef CATULONG64 CAAGSMFrmSelectorCtxMenuDef;

#define Id_NoMenu                 CATULONG64(CATULONG64(1)<<0)
#define Id_SketchBased            CATULONG64(CATULONG64(1)<<1)
#define Id_PointMenu              CATULONG64(CATULONG64(1)<<2)
#define Id_MidpointMenu           CATULONG64(CATULONG64(1)<<3)
#define Id_EndpointMenu           CATULONG64(CATULONG64(1)<<4)
#define Id_LineMenu               CATULONG64(CATULONG64(1)<<5)
#define Id_PlaneMenu              CATULONG64(CATULONG64(1)<<6)
#define Id_IntersectMenu          CATULONG64(CATULONG64(1)<<7)
#define Id_ProjectMenu            CATULONG64(CATULONG64(1)<<8)
#define Id_AssembleMenu           CATULONG64(CATULONG64(1)<<9)
#define Id_BoundaryMenu           CATULONG64(CATULONG64(1)<<10)
#define Id_ExtractMenu            CATULONG64(CATULONG64(1)<<11)
#define Id_ExtractC0Menu          CATULONG64(CATULONG64(1)<<12)
#define Id_ExtractC1Menu          CATULONG64(CATULONG64(1)<<13)
#define Id_ExtractMultiMenu       CATULONG64(CATULONG64(1)<<14)
#define Id_ExtrapolMenu           CATULONG64(CATULONG64(1)<<15)
#define Id_LawMenu                CATULONG64(CATULONG64(1)<<16)
#define Id_ExtremumMenu           CATULONG64(CATULONG64(1)<<17)
#define Id_CurveSmoothMenu        CATULONG64(CATULONG64(1)<<18)
#define Id_SpineMenu		      CATULONG64(CATULONG64(1)<<19)
#define Id_LoftMenu			      CATULONG64(CATULONG64(1)<<20)
#define Id_MultiplePointMenu      CATULONG64(CATULONG64(1)<<21)
#define Id_TrimMenu               CATULONG64(CATULONG64(1)<<22)
#define Id_AffinityMenu           CATULONG64(CATULONG64(1)<<23)
#define Id_SplitMenu              CATULONG64(CATULONG64(1)<<24)
#define Id_CurveParMenu           CATULONG64(CATULONG64(1)<<25)
#define Id_AxisSystemMenu         CATULONG64(CATULONG64(1)<<26)
#define Id_ExtrudeMenu            CATULONG64(CATULONG64(1)<<27)
#define Id_OffsetMenu             CATULONG64(CATULONG64(1)<<28)
#define Id_InverseMenu            CATULONG64(CATULONG64(1)<<29)
#define Id_RefAxisMenu		      CATULONG64(CATULONG64(1)<<30)
#define Id_RefPlanesMenu	      CATULONG64(CATULONG64(1)<<31)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Dimension 0 menus
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Id_PointsMenu			   Id_PointMenu     | \
                                                                    Id_IntersectMenu | \
                                                                    Id_ProjectMenu   | \
                                                                    Id_MidpointMenu  | \
                                                                    Id_EndpointMenu
/*zero dim mix*/
#define Id_Point_PlaneMenu						Id_PointsMenu | \
                                                                    Id_PlanesMenu

/*zero dim mix*/
#define Id_Point_FiniteWireMenu				Id_PointsMenu          | \
                                                                    Id_FiniteWireCurveMenu | \
                                                                    Id_ProjectMenu

#define Id_Point_WireMenu						Id_PointsMenu    | \
                                                                    Id_WireCurveMenu | \
                                                                    Id_ProjectMenu

/*zero dim mix*/
#define Id_Point_FiniteWire_FiniteSurfaceMenu	Id_PointsMenu          | \
                                                                    Id_FiniteWireCurveMenu | \
                                                                    Id_FiniteSurfacesMenu

#define Id_Point_FiniteWire_SurfaceMenu		Id_PointsMenu          | \
                                                                    Id_FiniteWireCurveMenu | \
                                                                    Id_SurfacesMenu

#define Id_Point_Wire_FiniteSurfaceMenu		Id_PointsMenu         | \
                                                                    Id_WireCurveMenu      | \
                                                                    Id_FiniteSurfacesMenu

#define Id_Point_Wire_SurfaceMenu				Id_PointsMenu    | \
                                                                    Id_WireCurveMenu | \
                                                                    Id_SurfacesMenu

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Dimension 1 menus
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Id_FiniteLinesMenu			Id_LineMenu      | \
                                                        Id_IntersectMenu

#define Id_LinesMenu				Id_LineMenu      | \
                                                        Id_RefAxisMenu   | \
                                                        Id_IntersectMenu

#define Id_FiniteWireCurveMenu		Id_AssembleMenu     | \
                                                        Id_BoundaryMenu     | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_CurveParMenu     | \
                                                        Id_FiniteLinesMenu

#define Id_WireCurveMenu			Id_AssembleMenu     | \
                                                        Id_BoundaryMenu     | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_CurveParMenu     | \
                                                        Id_LinesMenu

#define Id_FiniteWireSpineMenu		Id_FiniteLinesMenu  | \
                                                        Id_AssembleMenu     | \
                                                        Id_ProjectMenu      | \
                                                        Id_ExtrapolMenu     | \
                                                        Id_CurveSmoothMenu  | \
                                                        Id_BoundaryMenu     | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_SpineMenu        | \
                                                        Id_CurveParMenu

#define Id_WireSpineMenu			Id_LinesMenu        | \
                                                        Id_AssembleMenu     | \
                                                        Id_ProjectMenu      | \
                                                        Id_ExtrapolMenu     | \
                                                        Id_CurveSmoothMenu  | \
                                                        Id_BoundaryMenu     | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_SpineMenu        | \
                                                        Id_CurveParMenu

#define Id_FiniteWireGuideMenu		Id_FiniteWireCurveMenu | \
                                                        Id_CurveSmoothMenu

#define Id_WireGuideMenu			Id_WireCurveMenu   | \
                                                        Id_CurveSmoothMenu

#define Id_WireOnSurfaceMenu		Id_AssembleMenu     | \
                                                        Id_BoundaryMenu     | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_CurveSmoothMenu  | \
                                                        Id_ProjectMenu      | \
                                                        Id_IntersectMenu    | \
                                                        Id_CurveParMenu

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Dimension 2 menus
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Id_PlanesMenu				Id_PlaneMenu     | \
                                                        Id_RefPlanesMenu

#define Id_FiniteSurfacesMenu		Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_ExtrapolMenu     | \
                                                        Id_AssembleMenu     | \
                                                        Id_ExtrudeMenu

#define Id_SurfacesMenu			Id_PlanesMenu       | \
                                                        Id_ExtractMenu      | \
                                                        Id_ExtractC0Menu    | \
                                                        Id_ExtractC1Menu    | \
                                                        Id_ExtractMultiMenu | \
                                                        Id_ExtrapolMenu     | \
                                                        Id_AssembleMenu     | \
                                                        Id_ExtrudeMenu

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// All 
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define Id_AllForTest             Id_PointMenu   | \
                                                        Id_MidpointMenu           | \
                                                        Id_EndpointMenu           | \
                                                        Id_LineMenu               | \
														Id_RefAxisMenu		      | \
                                                        Id_PlaneMenu              | \
                                                        Id_RefPlanesMenu	      | \
														Id_IntersectMenu          | \
                                                        Id_ProjectMenu            | \
                                                        Id_AssembleMenu           | \
                                                        Id_BoundaryMenu           | \
                                                        Id_ExtractMenu            | \
                                                        Id_ExtractC0Menu          | \
                                                        Id_ExtractC1Menu          | \
                                                        Id_ExtractMultiMenu       | \
                                                        Id_ExtrapolMenu           | \
                                                        Id_LawMenu                | \
                                                        Id_ExtremumMenu           | \
                                                        Id_CurveSmoothMenu        | \
                                                        Id_SpineMenu		      | \
                                                        Id_LoftMenu			      | \
                                                        Id_MultiplePointMenu      | \
                                                        Id_TrimMenu               | \
                                                        Id_AffinityMenu           | \
                                                        Id_SplitMenu              | \
                                                        Id_CurveParMenu           | \
                                                        Id_AxisSystemMenu         | \
                                                        Id_ExtrudeMenu            | \
                                                        Id_OffsetMenu             | \
                                                        Id_InverseMenu            
                                                       

#endif
