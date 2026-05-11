#ifndef CAAMaiDumpToolPathCommand_H
#define CAAMaiDumpToolPathCommand_H

// COPYRIGHT DASSAULT SYSTEMES 2001

//===========================================================================
//  Abstract of the sample:
//  -----------------------
//
//  Dump of the content of the tool path of a manufacturing operation
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Implementation as a command
//
//===========================================================================
//  Usage:
//  ------
//
//  Launch CATIA V5
//  Inside one of the Manufacturing Workbench (Prismatic Machining Programmer,
//   for example)
//  Select an operation with a tool path
//  A report "DumpToolPath.txt" is created in temporary directory 
//       (by default, C:\Temp for NT, /tmp for UNIX)
//  
//===========================================================================
//  Inheritance:
//  ------------
//
//  CATStateCommand (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  DumpToolPath (method called when an operation is selected)
//
//===========================================================================


#include "CATStateCommand.h"
#include "CAAMaiDumpTPEnv.h"
#include "stdio.h"

class CATPathElementAgent;

class ExportedByCAAMaiDumpTPEnv CAAMaiDumpToolPathCommand : public CATStateCommand
{
   public:
   
      DeclareResource (CAAMaiDumpToolPathCommand,CATStateCommand)
    
      CAAMaiDumpToolPathCommand (CATString* argument);
      virtual ~CAAMaiDumpToolPathCommand();
      void BuildGraph();

      CATBoolean DumpToolPath (void *);

	  void Valuate             (const CATBaseUnknown_var&);

	  // Report file management
	  static FILE* _File;
	  static void CAAMaiWriteString                       (int,const CATUnicodeString&);

   private:

      // Copy constructor, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAAMaiDumpToolPathCommand(const CAAMaiDumpToolPathCommand &iObjectToCopy);
 
      // Assignment operator, not implemented
      // Set as private to prevent from compiler automatic creation as public.
      CAAMaiDumpToolPathCommand & operator  = (const CAAMaiDumpToolPathCommand &iObjectToCopy);

      CATPathElementAgent* _ActAcq;
};
#endif
