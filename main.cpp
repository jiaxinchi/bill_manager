#include<iostream>
#include <fstream>
#include <iomanip>
#include "const.h"
#include "billmanager.h"
#include "dailybill.h" 
#include "socialbill.h"
#include "businessbill.h"

using namespace std;

int main()
{
	BillManager bm;
	bm.Login();
	bm.Init_Bill();
	while (true)
	{
		bm.ShowMenu();
		int nChoice;
		cout << "��ѡ����Ҫ�Ĳ�����" << endl;
		cin >> nChoice;
		switch (nChoice)
		{
		case 0:
		{
			cout << "�˳��ɹ�����ӭ�´�ʹ��! " << endl;
			system("pause");
			return 0;
		}
		case 1:
		{
			bm.Add_Bill();
			break;
		}
		case 2:
		{
			bm.Del_Bill();
			break;
		}
		case 3:
		{
			bm.Modify_Bill();
			break;
		}
		case 4:
		{
			bm.Find_Bill();
			break;
		}
		case 5:
		{
			bm.Show_Bill();
			break;
		}
		case 6:
		{
			bm.Count_Bill();
			break;
		}
		case 7:
		{
			bm.Erase_Bill();
			break;
		}
		case 8:
		{
			bm.ChangePassword();
			break;
		}
		default:
		{
			cout << "�����ָ�������ѡ��" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	}
}