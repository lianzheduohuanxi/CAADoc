// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpCycle
//
// External service called by CAAMaiDumpToolPathCommand to dump a 
//    CATIMfgToolPathCycle object (description of a machining cycle)
//                                      
//=============================================================================

#ifndef CAAMaiDumpCycle_h
#define CAAMaiDumpCycle_h

class CATIMfgToolPathCycle_var;

void  CAAMaiDumpCycle       (int,const CATIMfgToolPathCycle_var&);

#endif

