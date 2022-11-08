#pragma once
#include<iostream>
#include<fstream>
#include "billbase.h"

using namespace std;

class BillManager
{

public:

	virtual void CheckPassword();

	virtual bool IsPasswordExist();

	virtual void SavePassword();

	virtual void PasswordEncrypt();

	virtual void PasswordDecrypt();

	virtual void ChangePassword();

	virtual void Init_Bill();

	virtual void Login();

	virtual void ShowMenu();

	virtual void Add_Bill();

	virtual void Save_Bill();

	virtual void Show_Bill();

	virtual void Del_Bill();

	virtual void Modify_Bill();

	virtual void Find_Bill();

	virtual void Count_Bill();

	virtual void Erase_Bill();

	virtual bool IsIdExist(int id);

	int m_BillNum = 0;

	Bill ** m_BillArray;

	bool m_EmpIsEmpty = true;

	char cPassword[MAXPL] = "";

	char cEncryptPassword[MAXPL] = "";
};