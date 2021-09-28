#pragma once

// CProgramConfiguration command target
class CProgramConfiguration : public CObject
{
DECLARE_SERIAL(CProgramConfiguration);
public:
	CProgramConfiguration();
	virtual ~CProgramConfiguration();
	bool LoadData(void);
	bool SaveData(void);
	CString CSNetProvName;
	CString CSLastUsedDomain;
	CString CSLastGroupName;
	CString& IOSysFilesPath(bool get,CString& CSPath);
	CString CSSkinPath;
	bool bShowSplashScreen;
	bool bUseBmpSkin;
	bool bAutoHideOnSend;
private:
	CString CSSysFilesPath;
	void Serialize(CArchive& archive);
	int IPortNumber;
};


