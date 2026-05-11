// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which creates a motion of a product in a new replay to be created in a *.CATProduct document
//
//  Illustrates :
//     Document loading in session
//     Create a replay within document
//     Create the motion within a replay
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAASiiCreateReplay inputDirectory inputFile.CATProduct
//
//  Inputs      :
//     inputDirectory        : directory containing the file
//     inputFile.CATProduct  : name of the file
//
//  Return Code :
//     0 : OK
//     1 : Bad input (argument number or file)
//     2 : Problem in loading the file
//     3 : Simulation error
//
//============================================================================================
#ifndef CAASiiCreateReplay_H
#define CAASiiCreateReplay_H

// Application frame Frameworks
#include "CATUnicodeString.h"

// Declaration
// The application software requires to run within a CATInteractiveApplication
class CAASiiCreateReplay
{
  public:
    CAASiiCreateReplay ();
    virtual ~CAASiiCreateReplay();
    int CreateReplay (const CATUnicodeString& iProduct,
                      const CATUnicodeString& iOutput);

  
};
#endif

