# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6MmrFreezeInternalCopy.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
#if defined (CATIAR214)
LINK_WITH  = JS0GROUP \
		     JS0FM	\
			 DI0PANV2	\
			 CATMathematics	\
			 CATDialogEngine \
			 CATVisItf	\
			 CATMecModUseItf \
			 CATMecModLiveUseItf \
			 CATMecModUIUseItf\ 
			 CATObjectModelerBase \
			 DataCommonProtocolUse
#elif defined (CATIAV5R23)
LINK_WITH = JS0GROUP \
			JS0FM	\
			DI0PANV2	\
			CATMathematics	\
			CATDialogEngine	\
			MecModItfCPP	\
			CATObjectModelerBase \
			CATObjectSpecsModeler \
			CATViz \
			CATMecModUseItf \
#endif
