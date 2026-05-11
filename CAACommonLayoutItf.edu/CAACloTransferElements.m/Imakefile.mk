#=====================================================================================
#                                     CNEXT - CXR5+
#                          COPYRIGHT DASSAULT SYSTEMES 2015+ 
#-------------------------------------------------------------------------------------
# MODULE      :    CAACloTransferElements
# FRAMEWORK   :    CAACommonLayoutInterfaces.edu
# AUTHOR      :    MVA5
# DATE        :    5.2015
#-------------------------------------------------------------------------------------
#=====================================================================================
BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH = JS0CORBA \
            CATCommonLayoutItfCPP \
            CATCommonLayoutItfUUID \
			CATCclInterfaces \
            KnowledgeItf \
			CATPspUUID CATPspUtilities \
			CAAPspUtilities \
			AS0STARTUP \ # To use CATIProduct
			CATArrangementItfCPP 

			
SH_LINK_WITH= $(LINK_WITH)



