/* COPYRIGHT DASSAULT SYSTEMES 2006 */
#ifndef _CATSYSSHA256_H_
#define _CATSYSSHA256_H_



#include "CATWTypes.h"


void CATSysSHA_256 (char * iMessage, int iLen, DWORD *H);
void CATSysSH2Enc ( DWORD *PT, DWORD *Key, DWORD *CT);
void CATSysSH2Dec ( DWORD *PT, DWORD *Key, DWORD *CT);


#endif // 
