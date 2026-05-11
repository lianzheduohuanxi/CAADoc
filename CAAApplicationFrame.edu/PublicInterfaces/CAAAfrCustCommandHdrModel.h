// COPYRIGHT DASSAULT SYSTEMES 2003

#ifdef _WINDOWS_SOURCE
#ifdef __CAAAfrCustCommandHdrModel
#define ExportedByCAAAfrCustCommandHdrModel __declspec(dllexport)
#else
#define ExportedByCAAAfrCustCommandHdrModel __declspec(dllimport)
#endif
#else
#define ExportedByCAAAfrCustCommandHdrModel
#endif
