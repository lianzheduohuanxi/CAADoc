# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrCombinedCurveAddIn.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH= CATAfrFoundation \
           JS0GROUP \
           CATGSMUseItf \
#elif defined (CATIAV5R23)
LINK_WITH= CATApplicationFrame   \ 
          JS0GROUP \
		   CATGSMUseItf \
#endif
