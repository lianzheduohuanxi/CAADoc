// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpNurbsData
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgTPNurbsDescription object (description of nurbs data)
//                                      
//=============================================================================

#ifndef CAAMaiDumpNurbsData_h
#define CAAMaiDumpNurbsData_h

class CATIMfgTPNurbsDescription_var;

void  CAAMaiDumpNurbsData       (int,const CATIMfgTPNurbsDescription_var&);

#endif

