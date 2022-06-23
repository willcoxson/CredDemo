// dllmain.h : Declaration of module class.

class CCredDemoModule : public ATL::CAtlDllModuleT< CCredDemoModule >
{
public :
	DECLARE_LIBID(LIBID_CredDemoLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CREDDEMO, "{63cdb236-69ed-41e2-923f-427ea6f42adb}")
};

extern class CCredDemoModule _AtlModule;
