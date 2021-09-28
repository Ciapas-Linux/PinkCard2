#pragma once

#include "ProgramConfiguration.h"

class CGroupObj
{
public:
	CGroupObj(CProgramConfiguration* cfg = NULL);
	~CGroupObj(void);
private:

struct Group
{
 string SGroup_name;
 string Sgroup_comment;
 vector<string> VSGroup_data;
};

vector<Group*> vp_group;

public:
	bool LoadGroup(CString& CSGroupFileName);
	bool SaveGroups(CString& CSPath);
	int LoadAllGroups(void);
	bool AddEmptyGroup(const CString& CSGroupName);
	int GetGroupNames(vector<string>& vs_container);
	int FindGroup(const CString& CSGroupName);
	bool DeleteGroup(const CString& CSGrpName);
	CProgramConfiguration* lpcfg;
	bool AddItemToGroup(const CString& CSGroupName , const CString& CSItemString);
	int GetGroupData(vector<CString>& vsDataContainer, const CString& CSGroupName);
	int FindItem(const CString& CSGrpName , const CString& CSItemString);
	vector <string>::iterator CGroupObj::FindItemItr(const CString& CSGrpName , const CString& CSItemString);
	bool DelItemFromGroup(const CString& CSGrpName, const CString& CSItemString);
};
