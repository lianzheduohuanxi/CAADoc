#=====================================================================================
#                                     CNEXT - CXR5+
#                          COPYRIGHT DASSAULT SYSTEMES 2004+ 
#-------------------------------------------------------------------------------------
# MODULE      :    CAACloSetup
# FRAMEWORK   :    CAACommonLayoutInterfaces.edu
# AUTHOR      :    ASN
# DATE        :    5.2004
#-------------------------------------------------------------------------------------
#=====================================================================================
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH = JS0CORBA\
            CATCommonLayoutItfUUID
			
SH_LINK_WITH= $(LINK_WITH)



