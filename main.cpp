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
		cout << "请选择您要的操作：" << endl;
		cin >> nChoice;
		switch (nChoice)
		{
		case 0:
		{
			cout << "退出成功，欢迎下次使用! " << endl;
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
			cout << "错误的指令，请重新选择！" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	}
}