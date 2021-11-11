#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	//List();
	//
	//Load();

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::Save()
{
	char str1[256];
	char dir1[256];
	char section[256];
	sprintf_s(section, "아이템 정보");

	ZeroMemory(dir1, sizeof(dir1));
	
	for (int i = 0; i < 100; i++)
	{
		char str2[256];
		char dir2[256];

		//중복확인 45 ~ 53
		sprintf_s(dir2, "\\itemData\\%s%03d.ini", "아이템", i+1);
		GetCurrentDirectory(256, str2);
		strncat_s(str2, 256, dir2, 254);

		GetFileAttributes(str2);

		//같은이름의 파일이 있다면 continue,
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str2)) continue;

		//세이브파일 생성 55 ~ 69
		sprintf_s(dir1, "\\itemData\\%s%03d.ini", "아이템", i+1);

		GetCurrentDirectory(256, str1);
		strncat_s(str1, 256, dir1, 254);

		for (int j = 0; j < _vItem.size(); j++)
		{
			arrItem vItem = _vItem[j];
			WritePrivateProfileString(section, vItem[0].title, vItem[0].value, str1);

			vItem.clear();
		}

		break;
	}

	_vItem.clear();
}

void itemManager::Add(const char* title, const char* value)
{
	//생성시킨 구조체 안에 내용물을 넣는다.
	tagItem _tagItem;

	_tagItem.title = title;
	_tagItem.value = value;

	//내용물이 들어있는 구조체들을 푸시백한다.
	arrItem vItem;
	vItem.push_back(_tagItem);

	//푸시백된 벡터를 푸시백한다.
	_vItem.push_back(vItem);
}

void itemManager::AddItem(const char* type, const char* name, const char* atk, const char* def, const char* speed)
{
	Add("아이템 타입", type);
	Add("아이템 이름", name);
	Add("공격력 증가", atk);
	Add("방어력 증가", def);
	Add("스피드 증가", speed);

	Save();

	itemAmount += 1;
}

void itemManager::List()
{
	AddItem("무기", "과도", "10", "0", "0");
	AddItem("무기", "톱", "15", "0", "0");
	AddItem("방어구", "티셔츠", "13", "0", "0");
	AddItem("방어구", "가죽갑옷", "14", "0", "0");
	AddItem("방어구", "철갑옷", "11", "0", "0");
	AddItem("신발", "고무신", "12", "0", "0");
	AddItem("신발", "운동화", "15", "0", "0");
}

void itemManager::Load()
{
	char file[256];
	char section[256];
	sprintf_s(section, "아이템 정보");

	tagItemInfo _tagItemInfo;

	for (int i = 0; i < itemAmount; i++)
	{
		sprintf_s(file, "\\itemData\\%s%03d.ini", "아이템", i + 1);

		//입력한 num번째의 ini파일의 정보 중, 입력한 title에 해당하는 값을 반환함.
		char data[256] = {};
		char *pos = NULL;
		float value = 0;
		bool isType = false;
		bool isName = false;
		bool isAtk = false;
		bool isDef = false;
		bool isSpeed = false;

		isType = GetPrivateProfileString(section, "아이템 타입", "", data, 256, file);

		string a = data;

		_tagItemInfo.type = a.c_str();

		isType = GetPrivateProfileString(section, "아이템 이름", "", data, 256, file);

		_tagItemInfo.name = data;

		isType = GetPrivateProfileString(section, "공격력 증가", "", data, 256, file);

		_tagItemInfo.atk = data;

		isType = GetPrivateProfileString(section, "방어력 증가", "", data, 256, file);

		_tagItemInfo.def = data;

		isType = GetPrivateProfileString(section, "스피드 증가", "", data, 256, file);

		_tagItemInfo.speed = data;

		_vItemInfo.push_back(_tagItemInfo);
	}
}

