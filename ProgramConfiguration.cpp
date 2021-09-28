// ProgramConfiguration.cpp : implementation file
//

#include "stdafx.h"
#include "PinkCard2.h"
#include "ProgramConfiguration.h"


// CProgramConfiguration

CProgramConfiguration::CProgramConfiguration()
: CSNetProvName(_T(""))
, CSLastUsedDomain(_T(""))
, IPortNumber(0)
, CSLastGroupName(_T(""))
, bShowSplashScreen(false)
{
}

CProgramConfiguration::~CProgramConfiguration()
{
}


CString& CProgramConfiguration::IOSysFilesPath(bool get,CString& CSPath)
{
 if(get == true)//read data
 {
  CSPath = CSSysFilesPath;
 }else//save data
 {
  CSSysFilesPath = CSPath;
 }
return CSPath;
}

//CProgramConfiguration member functions
bool CProgramConfiguration::SaveData(void)
{
  //Open cfg file "PinkCard2.cfg"
  CFile* pFile = new CFile();
  ASSERT (pFile != NULL);
  if (!pFile->Open("PinkCard2.cfg", CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate | CFile::modeNoTruncate))
  {
  	return false;
  }
  // Create archive ...
  bool bReading = false;  // ... for writing
  CArchive* pArchive = NULL;
  pFile->SeekToBegin();
  UINT uMode = (bReading ? CArchive::load : CArchive::store);
  pArchive = new CArchive (pFile, uMode);
  ASSERT (pArchive != NULL);
  Serialize(*pArchive);
  pArchive->Close();
  delete pArchive;
  pFile->Close();
  delete pFile;
return true;
}

void CProgramConfiguration::Serialize(CArchive& archive)
{
    TRY
	{
	CObject::Serialize(archive);
	if(archive.IsStoring())
		archive <<
		CSLastGroupName << 
		CSLastUsedDomain << 
		CSNetProvName << 
		IPortNumber << 
		bShowSplashScreen << 
		CSSysFilesPath << 
		CSSkinPath << 
		bAutoHideOnSend << 
		bUseBmpSkin;
	else
        archive >> 
		CSLastGroupName >> 
		CSLastUsedDomain >> 
		CSNetProvName >> 
		IPortNumber >> 
		bShowSplashScreen >> 
		CSSysFilesPath >> 
		CSSkinPath >> 
		bAutoHideOnSend >> 
		bUseBmpSkin;
	}
	CATCH(CArchiveException,pEx)
	{
     AfxMessageBox("PinkCard2 config file is broken, program create new with default settings");
    }END_CATCH;
return;
}

IMPLEMENT_SERIAL(CProgramConfiguration,CObject,0);

bool CProgramConfiguration::LoadData(void)
{
  //Open cfg file "PinkCard2.cfg"
  CFile* pFile = new CFile();
  ASSERT (pFile != NULL);
  if (!pFile->Open("PinkCard2.cfg", CFile::modeRead | CFile::shareExclusive))
  {
  	return false;
  }
  //Create archive ...
  bool bReading = true;//... for reading
  CArchive* pArchive = NULL;
  pFile->SeekToBegin();
  UINT uMode = (bReading ? CArchive::load : CArchive::store);
  pArchive = new CArchive (pFile, uMode);
  ASSERT (pArchive != NULL);
  CArchiveException mmm;
  Serialize(*pArchive);
  pArchive->Close();
  delete pArchive;
  pFile->Close();
  delete pFile;
return true;
}


