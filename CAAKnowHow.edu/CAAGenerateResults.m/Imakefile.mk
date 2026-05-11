// COPYRIGHT DASSAULT SYSTEMES 2002
##########################################################################
#
#       makefile customization lib:  Test for Vol
#
##########################################################################
#
# SHARED LIBRARY
#
# -------------------------------------------------------------------------

BUILT_OBJECT_TYPE=LOAD MODULE

# CC flags
LOCAL_CCFLAGS   =

LINK_WITH       =   AD0XXBAS AC0XXLNK              \
					AC0SPBAS AC0SPDOC              \
					NS0S3STR                       \
					CO0LSTPV CO0LSTST CO0RCINT KnowledgeItf CATProductStructure1\
					JS0CORBA JS0ERROR JS03TRA JS0SCBAK JS0FM JS0STR Rule CAACommonFunction 
#
#CATIA_LSTCOMDYN=NO ???
#
# -------------------------------------------------------------------------

OS 	= AIX

# templates aix
#INSTANCIATION_MODE = -qnotempinc

# -------------------------------------------------------------------------

OS 	= IRIX

# templates irix
#INSTANCIATION_MODE = -no_auto_include -no_prelink

# -------------------------------------------------------------------------

OS = HP-UX

INSTANCIATION_MODE = -pta -ptv

# -------------------------------------------------------------------------

OS = SunOS

#INSTANCIATION_MODE = -pta -ptv

