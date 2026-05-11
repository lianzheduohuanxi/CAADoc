// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpMultipleMotion
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgTPMultipleMotion object (description of tool motions)
//                                      
//=============================================================================

#ifndef CAAMaiDumpMultipleMotion_h
#define CAAMaiDumpMultipleMotion_h

class CATIMfgTPMultipleMotion_var;

void  CAAMaiDumpMultipleMotion       (int,const CATIMfgTPMultipleMotion_var&);

#endif

