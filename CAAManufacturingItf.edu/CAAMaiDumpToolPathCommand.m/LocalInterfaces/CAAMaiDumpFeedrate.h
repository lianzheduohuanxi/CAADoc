// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpFeedrate
//
// External service called by CAAMaiDumpToolPathCommand to dump a reference
//   feedrate on a CATIMfgCompoundTraject object
//                                      
//=============================================================================

#ifndef CAAMaiDumpFeedrate_h
#define CAAMaiDumpFeedrate_h

class CATIMfgCompoundTraject_var;
class CATUnicodeString;

void CAAMaiDumpFeedrate                      (int,const CATIMfgCompoundTraject_var&,CATUnicodeString&);

#endif

