// COPYRIGHT DASSAULT SYSTEMES 2002

#ifdef _WINDOWS_SOURCE
#ifdef __CAASysAutomationImpl
#define ExportedByCAASysAutomationImpl __declspec(dllexport)
#else // CAASysAutomationImpl
#define ExportedByCAASysAutomationImpl __declspec(dllimport)
#endif // CAASysAutomationImpl
#else // _WINDOWS_SOURCE
#define ExportedByCAASysAutomationImpl
#endif // _WINDOWS_SOURCE
