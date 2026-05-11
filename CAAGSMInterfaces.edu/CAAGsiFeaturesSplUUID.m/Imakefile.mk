# COPYRIGHT Dassault Systemes 2006
#======================================================================
# Imakefile for module CAAGsiFeaturesSplUUID
#======================================================================
# ARCHIVE
BUILT_OBJECT_TYPE=ARCHIVE

LINK_WITH_V5_ONLY=
LINK_WITH_V6_ONLY=
LINK_WITH=\
    $(LINK_WITH_V5_ONLY)           \
    $(LINK_WITH_V6_ONLY)           \
#

OS = COMMON
#if defined(R201)
LINK_WITH_V6_ONLY= \
#
#else
#if defined(CATIAV5R21)
LINK_WITH_V5_ONLY= \
#
#endif
#endif
