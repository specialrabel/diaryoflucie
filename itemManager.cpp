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
	sprintf_s(section, "������ ����");

	ZeroMemory(dir1, sizeof(dir1));
	
	for (int i = 0; i < 100; i++)
	{
		char str2[256];
		char dir2[256];

		//�ߺ�Ȯ�� 45 ~ 53
		sprintf_s(dir2, "\\itemData\\%s%03d.ini", "������", i+1);
		GetCurrentDirectory(256, str2);
		strncat_s(str2, 256, dir2, 254);

		GetFileAttributes(str2);

		//�����̸��� ������ �ִٸ� continue,
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str2)) continue;

		//���̺����� ���� 55 ~ 69
		sprintf_s(dir1, "\\itemData\\%s%03d.ini", "������", i+1);

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
	//������Ų ����ü �ȿ� ���빰�� �ִ´�.
	tagItem _tagItem;

	_tagItem.title = title;
	_tagItem.value = value;

	//���빰�� ����ִ� ����ü���� Ǫ�ù��Ѵ�.
	arrItem vItem;
	vItem.push_back(_tagItem);

	//Ǫ�ù�� ���͸� Ǫ�ù��Ѵ�.
	_vItem.push_back(vItem);
}

void itemManager::AddItem(const char* type, const char* name, const char* atk, const char* def, const char* speed)
{
	Add("������ Ÿ��", type);
	Add("������ �̸�", name);
	Add("���ݷ� ����", atk);
	Add("���� ����", def);
	Add("���ǵ� ����", speed);

	Save();

	itemAmount += 1;
}

void itemManager::List()
{
	AddItem("����", "����", "10", "0", "0");
	AddItem("����", "��", "15", "0", "0");
	AddItem("��", "Ƽ����", "13", "0", "0");
	AddItem("��", "���װ���", "14", "0", "0");
	AddItem("��", "ö����", "11", "0", "0");
	AddItem("�Ź�", "����", "12", "0", "0");
	AddItem("�Ź�", "�ȭ", "15", "0", "0");
}

void itemManager::Load()
{
	char file[256];
	char section[256];
	sprintf_s(section, "������ ����");

	tagItemInfo _tagItemInfo;

	for (int i = 0; i < itemAmount; i++)
	{
		sprintf_s(file, "\\itemData\\%s%03d.ini", "������", i + 1);

		//�Է��� num��°�� ini������ ���� ��, �Է��� title�� �ش��ϴ� ���� ��ȯ��.
		char data[256] = {};
		char *pos = NULL;
		float value = 0;
		bool isType = false;
		bool isName = false;
		bool isAtk = false;
		bool isDef = false;
		bool isSpeed = false;

		isType = GetPrivateProfileString(section, "������ Ÿ��", "", data, 256, file);

		string a = data;

		_tagItemInfo.type = a.c_str();

		isType = GetPrivateProfileString(section, "������ �̸�", "", data, 256, file);

		_tagItemInfo.name = data;

		isType = GetPrivateProfileString(section, "���ݷ� ����", "", data, 256, file);

		_tagItemInfo.atk = data;

		isType = GetPrivateProfileString(section, "���� ����", "", data, 256, file);

		_tagItemInfo.def = data;

		isType = GetPrivateProfileString(section, "���ǵ� ����", "", data, 256, file);

		_tagItemInfo.speed = data;

		_vItemInfo.push_back(_tagItemInfo);
	}
}

