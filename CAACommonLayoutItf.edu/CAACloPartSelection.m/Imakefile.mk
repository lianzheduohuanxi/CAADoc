#=====================================================================================
#                                     CNEXT - CXR5+
#                          COPYRIGHT DASSAULT SYSTEMES 2004+ 
#-------------------------------------------------------------------------------------
# MODULE      :    CAACloPartSelection
# FRAMEWORK   :    CAACommonLayoutInterfaces.edu
# AUTHOR      :    ASN
# DATE        :    12.2004
#-------------------------------------------------------------------------------------
#=====================================================================================
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH = JS0CORBA\
            CATCommonLayoutItfCPP \
            CATCommonLayoutItfUUID \
			CATCclInterfaces \
            KnowledgeItf \
			CATPspUUID CATPspUtilities \

			
SH_LINK_WITH= $(LINK_WITH)



