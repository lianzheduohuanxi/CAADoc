# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAADegGeoSDOAddin.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH=  CATApplicationFrame  \
            CATDialogEngine      \
            JS0GROUP \
            CAAAfrGeoCreationWbench

