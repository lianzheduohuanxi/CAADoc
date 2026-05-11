// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAATopSweepSegmentSkinSkin_H
#define CAATopSweepSegmentSkinSkin_H

class CATGeoFactory;
class CATTopData;
class CATBody;

// ===========================================================================
// 
// Illustrates how to create a sweep segment skin skin
//
// ===========================================================================
int CAATopSweepSegmentSkinSkin(CATGeoFactory * iFactory 
                               ,CATTopData * iTopData 
                               ,CATBody * iGuideBody1 
                               ,CATBody * iGuideBody2
                               ,CATBody * iSpineBody 
                               );               
#endif

