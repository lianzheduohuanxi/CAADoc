# COPYRIGHT DASSAULT SYSTEMES 2000

BUILT_OBJECT_TYPE=LOAD MODULE

LINK_WITH = \
            JS0GROUP \
            JS0FM \
            DI0PANV2 \
            CATObjectModelerBase \
            CATApplicationFrame \
            CATProductStructure1 \
            CATSaiSpaceAnalysisItf \
            MecModItfCPP\
            $(LINK_WITH_DEBUG)\


#if os SunOS
LINK_WITH_DEBUG = CATObjectSpecsModeler
#else
LINK_WITH_DEBUG =
#endif

OS = AIX

OS = HP-UX

OS = IRIX

OS = SunOS

OS = Windows_NT






