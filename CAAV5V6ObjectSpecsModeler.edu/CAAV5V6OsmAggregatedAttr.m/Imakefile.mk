#
# COPYRIGHT DASSAULT SYSTEMES 2000
#

BUILT_OBJECT_TYPE=LOAD MODULE
#if defined (CATIAR214) 

LINK_WITH = JS0CORBA CAAAdpUtilities CAAV5V6FmExtUtilities CATPLMIntegrationAccess \
			CATPLMComponentInterfaces CAT3DPhysicalRepItf CATPLMIdentificationAccess \
			FeatureModelerExt CATOmbLifeCycle CATPLMIntegrationUse\
			
#elif defined (CATIAV5R23) 

LINK_WITH = CATObjectModelerBase \
            CATObjectSpecsModeler \
			JS0CORBA FeatureModelerExt
			
#endif   	 



