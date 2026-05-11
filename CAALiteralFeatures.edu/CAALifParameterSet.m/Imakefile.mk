# COPYRIGHT DASSAULT SYSTEMES  2000

#
# LOAD MODULE
#
# 09-03-04 AAL: built_object_type=none because we can't prereq PartInterfaces which is necessary
# to include CATIPad in this use case.

BUILD=NO
BUILT_OBJECT_TYPE=NONE
PROGRAM_NAME = CAALifParameterSetMain

#
LINK_WITH =	CAALifBasis\
			CATObjectSpecsModeler\
			CATObjectModelerBase \
	     	DI0PANV2\
			JS0GROUP JS0FM Collections  \
            MecModItf PartItf KnowledgeItf


#
