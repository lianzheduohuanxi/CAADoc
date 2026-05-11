# COPYRIGHT DASSAULT SYSTEMES  2000
#
# LOAD MODULE 
#
BUILT_OBJECT_TYPE=LOAD MODULE
PROGRAM_NAME = CAALifEventsMain

LINK_WITH = CAALifBasis ObjectModeler \
						AC0SPBAS AC0CATPL JS0GROUP    NS0SI18N    \
						Collections CATObjectSpecsModeler\
			            CATObjectModelerBase \
                        KnowledgeItf


SYS_LIBPATH =

