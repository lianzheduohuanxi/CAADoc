# COPYRIGHT DASSAULT SYSTEMES 2000
#======================================================================
# Imakefile for module CAAMmrCombinedCurveAddIn.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH= CATAfrFoundation \
           CATMecModLiveUseItf \
           JS0GROUP \
           CATGSMUseItf

#elif defined (CATIAV5R23)
LINK_WITH=CATApplicationFrame    \  
          CATMecModLiveUseItf \
          JS0GROUP \
		  CATGSMUseItf
#endif
