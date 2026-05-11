// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which Reads a motion of a product in a new replay to be Readd in a *.CATProduct document
//
//  Illustrates :
//     Document loading in session
//     Read a replay within document
//     Read the motion within a replay
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAASiiReadReplay inputDirectory inputFile.CATProduct
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
#ifndef CAASiiReadReplay_H
#define CAASiiReadReplay_H

// Application frame Frameworks
#include "CATUnicodeString.h"

// Declaration
// The application software requires to run within a CATInteractiveApplication
class CAASiiReadReplay
{
  public:
    CAASiiReadReplay ();
    virtual ~CAASiiReadReplay();
    int ReadReplay (const CATUnicodeString& iProduct,
                    const CATUnicodeString& iOutput);

  
};
#endif

