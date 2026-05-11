// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpRotation
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgToolPathMotionCommand object (description of rotation)
//                                      
//=============================================================================

#ifndef CAAMaiDumpRotation_h
#define CAAMaiDumpRotation_h

class CATIMfgToolPathMotionCommand_var;

void  CAAMaiDumpRotation       (int,const CATIMfgToolPathMotionCommand_var&);

#endif

