# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6MmrPartWksAddin.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH=CATAfrFoundation \
          CATMecModLiveUseItf \
          CATGSMUseItf \      
          CATMecModUIUseItf \
          JS0GROUP
#elif defined (CATIAV5R23)
LINK_WITH=CATApplicationFrame    \    
          CATMechanicalModelerUI \
          JS0GROUP 
#endif
