# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6ExtMmrMultiMeasureAddIn.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH= JS0GROUP \
           CATAfrFoundation \
           CATGSMUseItf \

#elif defined (CATIAV5R23)
LINK_WITH= JS0GROUP \
           CATGSMUseItf \
		   CATApplicationFrame   \
#endif          
              
          
          
