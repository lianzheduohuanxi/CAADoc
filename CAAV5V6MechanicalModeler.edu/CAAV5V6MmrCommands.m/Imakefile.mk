# COPYRIGHT DASSAULT SYSTEMES 2012
#======================================================================
# Imakefile for module CAAV5V6MmrCommands.m
#======================================================================
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

#if defined (CATIAR214)
LINK_WITH=  CATMathematics   \
            JS0FM JS0GROUP   \
            DI0PANV2 JS0CORBA    CATOMY  CATPLMIdentificationAccess  \
            CATAfrFoundation CATVisItf AD0XXBAS \
            CATPLMComponentInterfaces CATPLMIdentificationAccess CATMecModUseItf CATMecModLiveUseItf \
            CATDialogEngine CATVisFoundation
#elif defined (CATIAV5R23)
LINK_WITH=  CATMathematics   \
            JS0FM \
			JS0GROUP   \
            CATMecModUseItf \
			CATMecModLiveUseItf \
            CATDialogEngine \
			CATVisualization \ 
			CATMecModInterfaces
#endif
