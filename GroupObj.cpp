#include "StdAfx.h"
#include "groupobj.h"
#include "PinkCard2.h"

CGroupObj::CGroupObj(CProgramConfiguration* cfg)
: lpcfg(NULL)
{
 lpcfg = cfg;
}

CGroupObj::~CGroupObj(void)
{
	for(int lop = 0;lop < (int)vp_group.size();lop++)
	{
     vp_group.erase(&vp_group[lop]);
     delete vp_group[lop];
	}
}

bool CGroupObj::LoadGroup(CString& CSGroupFileName)
{
return false;
}

bool CGroupObj::SaveGroups(CString& CSPath)
{
 //Main loop
 CString CStmp;
 for(unsigned int lop = 0;lop < vp_group.size();lop++)
 {
  CStmp = CSPath;
  CStmp.Append((char*)vp_group[lop]->SGroup_name.c_str());
  CStmp.Append(".grp");
  ofstream fout(CStmp);
  //second loop
  for(unsigned int lop2 = 0;lop2 < vp_group[lop]->VSGroup_data.size();lop2++)
  {
    fout << (char*)vp_group[lop]->VSGroup_data[lop2].c_str() << endl;
  }
  fout.close();
 }
return true;
}

int CGroupObj::LoadAllGroups(void)//Only names to vector not file extension
{
 CString CSpath;
 CString CSPatNam;
 lpcfg->IOSysFilesPath(true,CSpath);//Load CString data from CfgObj to variable CSpath
 CSpath.Append("*.grp");
 CFileFind finder;
 BOOL bResult = finder.FindFile(CSpath.GetBuffer(0));
 CSpath.ReleaseBuffer();
 if (bResult == 0) return 0;
 vp_group.clear();
 int iGrpCnt = 0;
 for(;;)
 {
  iGrpCnt++;
  bResult = finder.FindNextFile(); 
  vp_group.push_back(new Group);
  vp_group[vp_group.size() - 1]->SGroup_name = finder.GetFileTitle();
  CSPatNam = finder.GetFilePath();
  ifstream fin(CSPatNam);
   char buf[301];
   CString CSBuf;
   while(!fin.eof())
   {
    ZeroMemory(buf,sizeof(buf));
    fin.getline(buf,300);
	CSBuf = buf;
	if(CSBuf.GetLength() != 0)
	{
	 vp_group[vp_group.size() - 1]->VSGroup_data.push_back((string)CSBuf);
	}
   }
  fin.close();
  if(bResult == 0) break;
 }
return iGrpCnt;
}

bool CGroupObj::AddEmptyGroup(const CString& CSGroupName)
{
 vp_group.push_back(new Group);
 vp_group[vp_group.size() - 1]->SGroup_name = CSGroupName;
return true;
}

int CGroupObj::GetGroupNames(vector<string>& vs_container)
{
 for(int lop = 0;lop < (int)vp_group.size();lop++)
 {
  vs_container.push_back(vp_group[lop]->SGroup_name);
 }
 return (int)vs_container.size();
}

int CGroupObj::FindGroup(const CString& CSGroupName)
{
 CString csTemp;
 vector <Group*>::size_type vsize = vp_group.size();
 register unsigned int lop;
 for(lop = 0;lop < vsize ;lop++)
 {
  csTemp =  (char*)vp_group[lop]->SGroup_name.c_str(); 
  if(csTemp == CSGroupName) return lop;
 }
return -1;
}

bool CGroupObj::DeleteGroup(const CString& CSGrpName)
{
 int igrindex = FindGroup(CSGrpName);
 if(igrindex >= 0)
 { 
  delete vp_group[igrindex];   
  vp_group.erase(&vp_group[igrindex]);
 return true;
 }
return false;
}

bool CGroupObj::AddItemToGroup(const CString& CSGroupName , const CString& CSItemString)
{
 int igrindex = FindGroup(CSGroupName);
 string sTmp(CSItemString);
 if(igrindex >= 0)
 {
  vp_group[igrindex]->VSGroup_data.push_back(sTmp);
 return true;
 }
return false;
}

int CGroupObj::GetGroupData(vector<CString>& vsDataContainer, const CString& CSGroupName)
{
int igrindex = FindGroup(CSGroupName);
if(igrindex >= 0)
{
	unsigned int lop = 0;
	 for(lop = 0;lop < vp_group[igrindex]->VSGroup_data.size();lop++)
	 {
	   vsDataContainer.push_back((char*)vp_group[igrindex]->VSGroup_data[lop].c_str());
	 }
 return lop;
}
return -1;
}

int CGroupObj::FindItem(const CString& CSGrpName , const CString& CSItemString)
{
int igrindex = FindGroup(CSGrpName);
 if(igrindex >= 0)
 {
  unsigned int iGrpDataSize = (int)vp_group[igrindex]->VSGroup_data.size(); 
   for(unsigned int lop = 0;lop < iGrpDataSize;lop++)
   {
    CString CStmp = (char*)vp_group[igrindex]->VSGroup_data[lop].c_str();
	if(CStmp == CSItemString) return lop;
   }
 }
return -1;
}

vector <string>::iterator CGroupObj::FindItemItr(const CString& CSGrpName , const CString& CSItemString)
{
 int igrindex = FindGroup(CSGrpName);
 vector <string>::iterator Itr = vp_group[igrindex]->VSGroup_data.begin();
  if(igrindex >= 0)
  {
    unsigned int iGrpDataSize = (int)vp_group[igrindex]->VSGroup_data.size(); 
    for(unsigned int lop = 0;lop < iGrpDataSize;lop++)
    {
     CString CStmp = (char*)vp_group[igrindex]->VSGroup_data[lop].c_str();
     if(CStmp == CSItemString) return Itr;
     Itr++;
    }
  }
return vp_group[igrindex]->VSGroup_data.begin();
}

bool CGroupObj::DelItemFromGroup(const CString& CSGrpName, const CString& CSItemString)
{
 int igrindex = FindGroup(CSGrpName);
 vector <string>::iterator Iter = FindItemItr(CSGrpName,CSItemString);
 if(igrindex >= 0)
 {
  vp_group[igrindex]->VSGroup_data.erase(Iter);
 return true;
 }
return false;
}

