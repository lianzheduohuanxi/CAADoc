# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAAfrGeoDocument.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=CATApplicationFrame   \
          CATObjectModelerBase  \
          JS0FM JS0GROUP DI0PANV2 \
          CAAAfrGeoWindows     \
          CAASysGeoModelInf     \

