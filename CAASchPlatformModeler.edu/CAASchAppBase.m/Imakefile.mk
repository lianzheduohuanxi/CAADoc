#=====================================================================================
#                                     CNEXT - CXR4+
#                          COPYRIGHT DASSAULT SYSTEMES 2000+ 
#-------------------------------------------------------------------------------------
# MODULE      :    CAASchAppBase
# FRAMEWORK   :    CAASchPlatformModeler.edu
# AUTHOR      :    VSO
# DATE        :    1.2000
#-------------------------------------------------------------------------------------
# DESCRIPTION :    
#-------------------------------------------------------------------------------------
# COMMENTS    :    
#-------------------------------------------------------------------------------------
# MODIFICATIONS     user  date        purpose
#    HISTORY        ----  ----        -------
#                   bcy    3/28/2002   useless link with irregularities
# removed: BIG:CATDraftingInterfaces SMALL:ProductStructureProtIDL
#=====================================================================================
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH = AC0SPBAS \
			AD0XXBAS \
			AS0STARTUP \
			CD0WIN \
			CATSchUUID \ 
			CATSchItfCPP \
			CATVisualization \
			CAASchAppUtilities \
			JS0CORBA
			
SH_LINK_WITH= $(LINK_WITH)



