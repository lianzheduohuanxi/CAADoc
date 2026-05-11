// COPYRIGHT Dassault Systemes 2006
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "CATWTypes.h"
#include "CATDataType.h"
#include "CATSysSHA256.h"
 

static DWORD Hini[8] = { 0x6a09e667, 
			 0xbb67ae85,
			 0x3c6ef372,
			 0xa54ff53a,
			 0x510e527f,
			 0x9b05688c,
			 0x1f83d9ab,
			 0x5be0cd19 };

static const DWORD K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


#define ROTR(n,x)	((x >> n) | (x << (32-n)))
#define SHR(n,x)	(x >> n)

#define SIG0(x)		(ROTR(2,x) ^ ROTR(13,x) ^ ROTR(22,x))
#define SIG1(x)		(ROTR(6,x) ^ ROTR(11,x) ^ ROTR(25,x))
#define sig0(x)		(ROTR(7,x) ^ ROTR(18,x) ^ SHR(3,x))
#define sig1(x)		(ROTR(17,x) ^ ROTR(19,x) ^ SHR(10,x))

#define Maj(x,y,z)	((x & y) ^ (x & z) ^ (y & z))
#define Ch(x,y,z)	((x & y) | ((~x) & z))


 
//*****************************************************************************
//*          fips 180-2                                                       *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
void CATIntSHA256 ( DWORD *iM, DWORD *H)
{
  // M est un DWORD[16], H  DWORD{8]
  DWORD M[16];
  memcpy(M, iM, 16*sizeof(DWORD));
#ifdef _ENDIAN_LITTLE
  for (int i=0; i< 16; i++)
    {
      *((char *)(&M[i]))	^=	*(((char *)(&M[i]))+3);
      *(((char *)(&M[i]))+3)	^=	*((char *)(&M[i]));
      *((char *)(&M[i]))	^=	*(((char *)(&M[i]))+3);
      *(((char *)(&M[i]))+1)	^=	*(((char *)(&M[i]))+2);
      *(((char *)(&M[i]))+2)	^=	*(((char *)(&M[i]))+1);
      *(((char *)(&M[i]))+1)	^=	*(((char *)(&M[i]))+2);
    }
#endif
  DWORD  W[64];
  DWORD  a= H[0], b= H[1], c= H[2], d= H[3];
  DWORD  e= H[4], f= H[5], g= H[6], h= H[7];
  DWORD T1=0, T2=0;

  int t = 0;
  for ( ; t < 16; t++)
    W[t] = M[t];
  for ( t = 16; t < 64; t++)
    W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

  for ( t=0; t< 64; t++)
    {
      T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
      T2 = SIG0(a) + Maj(a,b,c);
      h = g;
      g = f;
      f = e; 
      e = d + T1;
      d = c; 
      c = b; 
      b = a;
      a = T1 + T2;
      //printf ( "t=%d %x %x %x %x %x %x %x %x \n", t,a,b,c,d,e,f,g,h);
    }
  //printf("\n");
  H[0] += a;
  H[1] += b;
  H[2] += c; 
  H[3] += d;
  H[4] += e;
  H[5] += f;
  H[6] += g;
  H[7] += h;
}
  


 
//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************	
void CATSysSHA_256 ( char *message, int iLen, DWORD *H)
{
  memcpy ( H , Hini, 8*sizeof(DWORD));
  // iLen longueur en bytes
  int NBBloc = iLen/64;

  for ( int i=0; i< NBBloc ; i++)
    {
      // on travaille sur des blocs de 512bits soit 16 DWORD, ou 64 char
      CATIntSHA256((DWORD*) &message[i*64], H);
    }

  // padding
  int l = iLen *8;
  int k = 448 - 1 - l % 512;
  CATULONG64 L = l;
  char M[64];
  memset ( M, '\0', 64);
  memcpy ( M, &message[NBBloc*64], iLen - NBBloc*64);
  // on a toujours la place d'ajouter un 0x80
  char c = (char)0x80 ;
  memcpy ( M + iLen - NBBloc*64, &c, 1);

#ifdef _ENDIAN_LITTLE
  char *Buff = (char*)&L;
  Buff[0]^=Buff[7];
  Buff[7]^=Buff[0];
  Buff[0]^=Buff[7];
  Buff[1]^=Buff[6];
  Buff[6]^=Buff[1];
  Buff[1]^=Buff[6];
  Buff[2]^=Buff[5];
  Buff[5]^=Buff[2];
  Buff[2]^=Buff[5];
  Buff[3]^=Buff[4];
  Buff[4]^=Buff[3];
  Buff[3]^=Buff[4];
#endif

  if ( k < 0)
    {
      CATIntSHA256((DWORD*)M, H);
       memset ( M, '\0', 64);
       memcpy ( M+56, &L, sizeof(CATULONG64));
       CATIntSHA256((DWORD*)M, H);
    }
  else
    {
      memcpy ( M+56, &L, sizeof(CATULONG64)); 
      CATIntSHA256((DWORD*)M, H);
    }
}





 
//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
void CATSysSH2Enc ( DWORD *PT, DWORD *Key, DWORD *CT)
{
  // Key est un DWORD[16], PT DWORD{8]
  DWORD  W[64];
  DWORD  a= PT[0], b= PT[1], c= PT[2], d= PT[3];
  DWORD  e= PT[4], f= PT[5], g= PT[6], h= PT[7];
  DWORD T1=0, T2=0;

  int t = 0;
  for ( ; t < 16; t++)
    W[t] = Key[t];
  for ( t = 16; t < 64; t++)
    W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

  for ( t=0; t< 64; t++)
    {
      T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
      T2 = SIG0(a) + Maj(a,b,c);
      h = g;
      g = f;
      f = e; 
      e = d + T1;
      d = c; 
      c = b; 
      b = a;
      a = T1 + T2;
    }
  CT[0] = a;
  CT[1] = b;
  CT[2] = c; 
  CT[3] = d;
  CT[4] = e;
  CT[5] = f;
  CT[6] = g;
  CT[7] = h;
}
  


	
 
//*****************************************************************************
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*****************************************************************************
void CATSysSH2Dec ( DWORD *CT, DWORD *Key, DWORD *PT)
{
  // Key est un DWORD[16], PT DWORD{8]
  DWORD  W[64];
  DWORD  a= CT[0], b= CT[1], c= CT[2], d= CT[3];
  DWORD  e= CT[4], f= CT[5], g= CT[6], h= CT[7];
  DWORD R1=0, R2=0;

  
  int t = 0;
  for ( ; t < 16; t++)
    W[t] = Key[t];
  for ( t = 16; t < 64; t++)
    W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];

  for ( t=63 ; t >=0 ; t--)
    {
      R1 = SIG1(f) + Ch(f,g,h);
      R2 = a - SIG0(b)  - Maj(b,c,d);
      a = b;
      b = c;
      c = d;
      d = e - R2;
      e = f;
      f = g;
      g = h;
      h = R2 - R1 - K[t] -W[t];
    }

  PT[0] = a;
  PT[1] = b;
  PT[2] = c; 
  PT[3] = d;
  PT[4] = e;
  PT[5] = f;
  PT[6] = g;
  PT[7] = h;
}
