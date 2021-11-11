#pragma once
#include "singletonBase.h"
#include <vector>

enum itemType
{
	weapon,
	armor,
	shoes
};

struct tagItem
{
	const char* title;		//지정할 값의 종류
	const char* value;		//값
};

struct tagItemInfo
{
	const char* type;
	const char* name; 
	const char* atk; 
	const char* def; 
	const char* speed;
};

class itemManager : public singletonBase<itemManager>
{
private:
	typedef vector<tagItem>						arrItem;
	typedef vector<tagItem>::iterator			arrItemIter;

	typedef vector<arrItem>						arrItems;
	typedef vector<arrItem>::iterator			arrItemsIter;

	typedef vector<tagItemInfo>					arrItemInfo;
	typedef vector<tagItemInfo>::iterator		arrItemInfoIter;

private:
	arrItems _vItem;
	arrItemsIter _viItem;
	
	arrItemInfo _vItemInfo;
	arrItemInfoIter _viItemInfo;

	tagItemInfo _itemInfo;

	int itemAmount = 0;

public:
	HRESULT init();
	void release();

	void Save();
	void Add(const char* title, const char* value);
	void AddItem(const char* type, const char* name, const char* atk, const char* def, const char* speed);
	void List();
	void Load();

	tagItemInfo check(int num) { return _vItemInfo[num]; }
};

