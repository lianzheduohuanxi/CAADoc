# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAMmrDatumWindowCmd
#======================================================================
# 
# SHARED LIBRARY
# 
# 
BUILT_OBJECT_TYPE = SHARED LIBRARY

#if defined (CATIAR214)
LINK_WITH = AD0XXBAS \
            DI0PANV2 \
            JS0GROUP \
            JS0FM \
            SystemUUID \
            CATMecModUseItf \
            CATVisFoundation \
            CATAfrFoundation \
            CATDialogEngine \

#elif defined (CATIAV5R23)
LINK_WITH = AD0XXBAS \
            DI0PANV2 \
            JS0GROUP \
            JS0FM \
            SystemUUID \
            CATMecModUseItf \
            CATDialogEngine \
			CATApplicationFrame \
			CATMecModInterfaces \
#endif            
            
            
