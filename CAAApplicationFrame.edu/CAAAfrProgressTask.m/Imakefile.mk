# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAAAfrProgressTask.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH=  CATApplicationFrame   \ 
            JS0FM JS0GROUP        \
            DI0PANV2              
