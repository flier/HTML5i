// dllmain.h : Declaration of module class.

class CHTML5iModule : public ATL::CAtlDllModuleT< CHTML5iModule >
{
public :
	DECLARE_LIBID(LIBID_HTML5iLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HTML5I, "{A0950964-3B86-4C7B-AB52-28CBE4BD4216}")
};

extern class CHTML5iModule _AtlModule;
