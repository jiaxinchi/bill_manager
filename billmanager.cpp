#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "const.h"
#include "billmanager.h"
#include "dailybill.h"
#include "socialbill.h"
#include "businessbill.h"

void BillManager::CheckPassword()
{
	int CheckNum = 0;
	while (true)
	{ 
		cout << "请输入登录密码：";
		char cPassword[MAXPL];
		cin >> cPassword;
		if (strcmp(this->cPassword, (const char*)cPassword) == 0)
		{
			return;
		}
		else
		{
			if (CheckNum == 2)
			{
				cout << "密码错误次数达到三次，即将退出账单管理系统！ " << endl;
				system("pause");
				exit(0);
			}
			cout << "密码错误!还剩" << 2 - CheckNum << "次机会！ " << endl;
			CheckNum++;
		}
	}
}

bool BillManager::IsPasswordExist()
{
	ifstream ifs;
	ifs.open(PSFILENAME, ios::in);
	if (ifs.is_open() == 0)
	{
		return false;
	}
	else
	{	//解码
		ifs >> this->cEncryptPassword;
		this->PasswordDecrypt();
		ifs.close();
		return true;
	}
}

void BillManager::SavePassword()
{
	ofstream ofs;
	ofs.open(PSFILENAME, ios::out);

	//加密
	this->PasswordEncrypt();
	ofs << this->cEncryptPassword << endl;
	ofs.close();
}

void BillManager::PasswordEncrypt()
{
	{
		for (int i = 0; i < MAXPL; i++)
		{
			this->cEncryptPassword[i] = (char)((int)this->cPassword[i] + (i + 1)*(i + 2));
		}
	}
}

void BillManager::PasswordDecrypt()
{
	for (int i = 0; i < MAXPL; i++)
	{
		this->cPassword[i] = (char)((int)this->cEncryptPassword[i] - (i + 1)*(i + 2));
	}
}

void BillManager::ChangePassword()
{
	this->CheckPassword();
	while (true)
	{
		cout << "请输入新密码： ";
		char cNewPassword[MAXPL];
		cin >> cNewPassword;
		while (true)
		{
			if (strcmp(this->cPassword, cNewPassword) == 0)
			{
				cout << "新密码不能和原始密码相同，请重新输入： ";
				cin >> cNewPassword;
			}
			else
			{
				break;
			}
		}
		char cConformPassword[MAXPL];
		cout << "请再次输入新密码： ";
		cin >> cConformPassword;
		if (strcmp(cNewPassword, cConformPassword) == 0)
		{
			for (int i = 0; i < MAXPL; i++)
			{
				if (i < sizeof(cNewPassword) / sizeof(char))
				{
					this->cPassword[i] = cNewPassword[i];
				}
				else
				{
					this->cPassword[i] = '\0';
				}
			}
			this->SavePassword();
			cout << "新密码设置成功，请妥善保管！ " << endl;
			return;
		}
		else
		{
			cout << "两次输入的密码不一致，请重新设置！ " << endl;
		}
	}
}

void BillManager::Init_Bill()
{
	ifstream ifs;
	ifs.open(DFILENAME, ios::in);
	if (ifs.is_open() == 0)
	{
		this->m_BillNum = 0;
	}
	else if (ifs.eof())
	{
		this->m_BillNum = 0;
		this->m_EmpIsEmpty = true;
	}
	else
	{
		string temp;
		this->m_BillNum = 0;
		while (getline(ifs, temp))
		{
			this->m_BillNum++;
		}
		ifs.close();

		struct Date date;
		int id;
		int nBilltype;
		double amount;
		string remarks;

		Bill ** tempSpace = new Bill *[this->m_BillNum];
		ifstream ifs;
		ifs.open(DFILENAME, ios::in);

		int i = 0;
		while (ifs >> id && ifs >> date.m_nYear&&ifs >> date.m_nMonth&& ifs >> date.m_nDay && ifs >> nBilltype && ifs >> amount && ifs >> remarks)
		{
			switch (nBilltype)
			{
			case dailybill:
			{
				tempSpace[i] = new DailyBill(id, nBilltype, amount, remarks, date);
				break;
			}
			case socialbill:
			{
				tempSpace[i] = new SocialBill(id, nBilltype, amount, remarks, date);
				break;
			}
			case businessbill:
			{
				tempSpace[i] = new BusinessBill(id, nBilltype, amount, remarks, date);
				break;
			}
			default:
				break;
			}
			i++;
		}
		this->m_BillArray = tempSpace;
		this->m_EmpIsEmpty = false;
	}
	ifs.close();
}

void BillManager::Login()
{
	cout << "*********************************************" << endl;
	cout << "**********欢迎使用【账单管理系统】**********" << endl;
	if (this->IsPasswordExist())
	{
		this->CheckPassword();
		cout << "*****  登录成功，即将进入账单管理系统!  *****" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "初次使用，请设置登录密码： ";
		cin >> this->cPassword;
		cout << "设置成功，请牢记您的登录密码！ " << endl;
		this->SavePassword();
		system("pause");
		system("cls");
	}
}

void BillManager::ShowMenu()
{
	cout << setw(55) << setfill('*') << "" << endl;
	cout << setw(32) << "账单管理系统 V" << VERSION << setw(20) << "" << endl;
	cout << setw(55) << setfill('*') << "" << endl;
	cout << setw(35) << "  00  退出系统  " << setw(20) << "" << endl;
	cout << setw(35) << "  01  添加账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  02  删除账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  03  修改账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  04  查找账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  05  显示全部  " << setw(20) << "" << endl;
	cout << setw(35) << "  06  统计账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  07  清空账目  " << setw(20) << "" << endl;
	cout << setw(35) << "  08  修改密码  " << setw(20) << "" << endl;
	cout << setw(55) << setfill('*') << "" << setfill(' ') << endl;
}

void BillManager::Add_Bill()
{
	cout << "请输入要添加账目的数量： " << endl;
	int addNum = 0;
	cin >> addNum;
	int newSize = this->m_BillNum + addNum;
	Bill ** tempSpace = new Bill *[newSize];

	for (int i = 0; i < this->m_BillNum; i++)
	{
		tempSpace[i] = this->m_BillArray[i];
	}

	if (addNum > 0)
	{
		for (int i = 0; i < addNum; i++)
		{
			int type;
			double amount;
			string remarks;
			struct Date date;
			cout << "请输入账目日期，输入\"0\"为当前日期（年月日以空格隔开）（例如：2000 10 11）： " << endl;
			cin >> date.m_nYear;
			int datetype;//输入的日期是否是默认形式
			if (date.m_nYear == 0)
			{
				datetype = 0;
			}
			else
			{
				datetype = 1;
				cin >> date.m_nMonth;
				cin >> date.m_nDay;
			}
			cout << "请输入第" << i + 1 << "个账目的类型（1：日常开支；2：人情往来；3：生意往来）： ";
			cin >> type;
			if (type != 1 && type != 2 && type != 3)
			{
				cout << "账目类型不正确,请重新输入：" ;
				cin >> type;
			}
			cout << "请输入第" << i + 1 << "个账目的金额（元）： ";
			cin >> amount;
			cout << "请输入第" << i + 1 << "个账目的事由或备注： ";
			cin >> remarks;
			switch (type)
			{
			case 1:
			{
				if (datetype == 0)
				{
					tempSpace[this->m_BillNum + i] = new DailyBill(m_BillNum + i, type, amount, remarks);
				}
				else
				{
					tempSpace[this->m_BillNum + i] = new DailyBill(m_BillNum + i, type, amount, remarks, date);
				}
				break;
			}
			case 2:
			{
				if (datetype == 0)
				{
					tempSpace[this->m_BillNum + i] = new SocialBill(m_BillNum + i, type, amount, remarks);
				}
				else
				{
					tempSpace[this->m_BillNum + i] = new SocialBill(m_BillNum + i, type, amount, remarks, date);
				}
				break;
			}
			case 3:
			{
				if (datetype == 0)
				{
					tempSpace[this->m_BillNum + i] = new BusinessBill(m_BillNum + i, type, amount, remarks);
				}
				else
				{
					tempSpace[this->m_BillNum + i] = new BusinessBill(m_BillNum + i, type, amount, remarks, date);
				}
				break;
			}
			default:
			{
				cout << "账目类型不正确! " << endl;
				break;
			}
			}
		}
		this->m_BillArray = tempSpace;
		this->m_BillNum = newSize;
		this->Save_Bill();
		this->m_EmpIsEmpty = false;
		cout << "账目添加完成！ " << endl;
	}
	else
	{
		cout << "输入有误！ " << endl;
	}
}

void BillManager::Save_Bill()
{
	ofstream ofs;
	ofs.open(DFILENAME, ios::out);
	for (int i = 0; i < this->m_BillNum; i++)
	{
		ofs << this->m_BillArray[i]->m_nBillId << " "
			<< this->m_BillArray[i]->Date.m_nYear << " "
			<< this->m_BillArray[i]->Date.m_nMonth << " " <<
			this->m_BillArray[i]->Date.m_nDay << " " <<
			this->m_BillArray[i]->m_BillType << " " <<
			this->m_BillArray[i]->m_dAmount << " "
			<< this->m_BillArray[i]->m_strRemark << endl;
	}
}

void BillManager::Show_Bill()
{
	if (this->m_EmpIsEmpty)
	{
		cout << "当前系统内无任何账目信息！ " << endl;
	}
	else
	{
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "编号|" << "\t" << setw(11) << "日期|" << setw(13) << "类型|" << setw(13) << "金额(元)|" << "\t" << "备注" << endl;
		cout << "------------------------------------------------------------------------" << endl;

		for (int i = 0; i < this->m_BillNum; i++)
		{
			this->m_BillArray[i]->ShowInfo();
		}
		cout << "------------------------------------------------------------------------" << endl;
	}
}

void BillManager::Del_Bill()
{
	if (this->m_BillNum == 0)
	{
		cout << "当前系统内无任何账目信息！" << endl;
		return;
	}
	int id;
	cout << "请输入要删除的账目编号： " << endl;
	cin >> id;
	if (this->IsIdExist(id))
	{
		cout << "该账目信息如下： " << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "编号|" << "\t" << setw(11) << "日期|" << setw(13) << "类型|" << setw(13) << "金额(元)|" << "\t" << "备注" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		this->m_BillArray[id]->ShowInfo();
		cout << "------------------------------------------------------------------------" << endl;
		cout << "确认要删除该账目吗？(1:yes;0:no): ";
		int conform;
		cin >> conform;
		if (conform == 1)
		{
			Bill ** tempSpace = new Bill *[this->m_BillNum - 1];
			for (int i = 0; i < this->m_BillNum; i++)
			{
				if (i < id)
				{
					tempSpace[i] = this->m_BillArray[i];
				}
				else if ((i > id))
				{
					tempSpace[i - 1] = this->m_BillArray[i];
					tempSpace[i - 1]->m_nBillId--;
				}
			}
			delete[] this->m_BillArray;
			this->m_BillArray = tempSpace;
			this->m_BillNum--;
			cout << "删除成功！ " << endl;
			this->Save_Bill();
		}
		else
		{
			return;
		}
	}
	else
	{
		cout << "没有该账目信息，请确认后查询！ " << endl;
	}
}

void BillManager::Modify_Bill()

{
	if (this->m_BillNum == 0)
	{
		cout << "当前系统内无任何账目信息！" << endl;
		return;
	}
	cout << "请输入您要修改的账目编号： ";
	int id;
	cin >> id;
	if (this->IsIdExist(id))
	{
		cout << "该账目信息如下：" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "编号|" << "\t" << setw(11) << "日期|" << setw(13) << "类型|" << setw(13) << "金额(元)|" << "\t" << "备注" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		this->m_BillArray[id]->ShowInfo();
		cout << "------------------------------------------------------------------------" << endl;
		cout << "确认要修改该账目吗？(1:yes;0:no): ";
		int conform;
		cin >> conform;
		if (conform == 1)
		{
			int billtype;
			double amount;
			string remarks;
			struct Date date;
			cout << "请修改该账目的日期，年月日以空格隔开（例如：2000 10 11）： " << endl;
			cin >> date.m_nYear; cin >> date.m_nMonth; cin >> date.m_nDay;
			cout << "请修改该账目类型（1：日常开支；2：人情往来；3：生意往来）： ";
			cin >> billtype;
			cout << "请修改该账目的金额（元）： ";
			cin >> amount;
			cout << "请修改该账目的事由或备注： ";
			cin >> remarks;
			Bill *tempbill = NULL;
			switch (billtype)
			{
			case dailybill:
			{
				tempbill = new DailyBill(id, billtype, amount, remarks, date);
			}
			case socialbill:
			{
				tempbill = new SocialBill(id, billtype, amount, remarks, date);
			}
			case businessbill:
			{
				tempbill = new BusinessBill(id, billtype, amount, remarks, date);
			}
			default:
				break;
			}
			this->m_BillArray[id] = tempbill;
			//delete tempbill;
			this->Save_Bill();
			cout << "修改完成！ " << endl;
		}
		else
		{
			return;
		}
	}

}

void BillManager::Find_Bill()
{
	if (this->m_BillNum == 0)
	{
		cout << "当前系统内无任何账目信息！" << endl;
		return;
	}
	cout << "请选择查找方式：（1：按日期查找；2：按金额查找） " << endl;
	int findtype;
	cin >> findtype;
	switch (findtype)
	{
	case 1:
	{
		cout << "请输入开始日期（例如：2000 10 11）： " << endl;
		struct Date begin_date;
		cin >> begin_date.m_nYear; cin >> begin_date.m_nMonth; cin >> begin_date.m_nDay;
		cout << "请输入结束日期（例如：2000 10 11）： " << endl;
		struct Date end_date;
		cin >> end_date.m_nYear; cin >> end_date.m_nMonth; cin >> end_date.m_nDay;
		int Num = 0;
		for (int i = 0; i < this->m_BillNum; i++)
		{
			if (
				((this->m_BillArray[i]->Date.m_nYear> begin_date.m_nYear)|| (this->m_BillArray[i]->Date.m_nYear == begin_date.m_nYear&&this->m_BillArray[i]->Date.m_nMonth > begin_date.m_nMonth) ||
				(this->m_BillArray[i]->Date.m_nYear == begin_date.m_nYear&&this->m_BillArray[i]->Date.m_nMonth == begin_date.m_nMonth&&this->m_BillArray[i]->Date.m_nDay >= begin_date.m_nDay))&&

				((this->m_BillArray[i]->Date.m_nYear < end_date.m_nYear) || (this->m_BillArray[i]->Date.m_nYear == end_date.m_nYear&&this->m_BillArray[i]->Date.m_nMonth < end_date.m_nMonth) ||
				(this->m_BillArray[i]->Date.m_nYear == end_date.m_nYear&&this->m_BillArray[i]->Date.m_nMonth == end_date.m_nMonth&&this->m_BillArray[i]->Date.m_nDay <= end_date.m_nDay))
				)
			{
				Num++;
				if (Num == 1)
				{
					cout << "符合条件的账目如下： " << endl;
					cout << "------------------------------------------------------------------------" << endl;
					cout << setw(6) << "编号|" << "\t" << setw(11) << "日期|" << setw(13) << "类型|" << setw(13) << "金额(元)|" << "\t" << "备注" << endl;
					cout << "------------------------------------------------------------------------" << endl;
				}
				m_BillArray[i]->ShowInfo();
			}
		}
		if (Num > 0)
		{
			cout << "------------------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "未查找到符合条件的账目！ " << endl;
		}
		break;
	}
	case 2:
	{
		cout << "请输入要查找的金额范围以空格隔开（例如：100 200）： " << endl;
		double minAmout;
		double maxAmout;
		cin >> minAmout; cin >> maxAmout;
		int Num = 0;
		for (int i = 0; i < this->m_BillNum; i++)
		{
			if (fabs(this->m_BillArray[i]->m_dAmount) >= minAmout && fabs(this->m_BillArray[i]->m_dAmount) <= maxAmout)
			{
				Num++;
				if (Num == 1)
				{
					cout << "符合条件的账目如下： " << endl;
					cout << "------------------------------------------------------------------------" << endl;
					cout << setw(6) << "编号|" << "\t" << setw(11) << "日期|" << setw(13) << "类型|" << setw(13) << "金额(元)|" << "\t" << "备注" << endl;
					cout << "------------------------------------------------------------------------" << endl;
				}
				m_BillArray[i]->ShowInfo();
			}
		}
		if (Num > 0)
		{
			cout << "------------------------------------------------------------------------" << endl;
		}
		else
		{
			cout << "未查找到符合条件的账目！ " << endl;
		}

		break;
	}
	default:
		cout << "输入有误 " << endl;
		break;
	}
}

void BillManager::Count_Bill()
{
	cout << "账目统计如下：" << endl;
	double Sum_daily=0;
	double Sum_daily_out = 0;
	double Sum_Social_in=0;
	double Sum_Social_out = 0;
	double Sum_Business_in=0;
	double Sum_Business_out = 0;
	for (int i = 0; i < this->m_BillNum; i++)
	{
		switch (this->m_BillArray[i]->m_BillType)
		{
		case dailybill:
		{
			Sum_daily += this->m_BillArray[i]->m_dAmount;
			break;
		}
		case socialbill:
		{
			if (this->m_BillArray[i]->m_dAmount < 0)
			{
				Sum_Social_out += this->m_BillArray[i]->m_dAmount;
			}
			else
			{
				Sum_Social_in += this->m_BillArray[i]->m_dAmount;
			}
			break;
		}
		case businessbill:
		{
			if (this->m_BillArray[i]->m_dAmount < 0)
			{
				Sum_Business_out += this->m_BillArray[i]->m_dAmount;
			}
			else
			{
				Sum_Business_in += this->m_BillArray[i]->m_dAmount;
			}
			break;
		}
		default:
			break;
		}
	}
	cout << "--------------------------------------------------" << endl;
	cout << "<日常>  支出总计：" << setw(5) <<Sum_daily<<" 元"<<endl;
	cout << "<生意>  收入总计：" << setw(5)<<abs(Sum_Business_in) << " 元" <<"  支出总计：" << setw(5) << abs(Sum_Business_out) << " 元" << endl;
	cout << "<人情>  收入总计：" << setw(5) << abs(Sum_Social_in) << " 元" <<"  支出总计：" << setw(5) << abs(Sum_Social_out) << " 元" << endl;
	cout << "--------------------------------------------------" << endl;
}

void BillManager::Erase_Bill()
{
	this->CheckPassword();
	cout << "确认要清空所有账目吗？(1:yes;0:no): ";
	int conform;
	cin >> conform;
	if (conform == 1)
	{
		this->m_BillArray = NULL;
		this->m_BillNum = 0;
		this->m_EmpIsEmpty = true;
		remove(DFILENAME);
		cout << "已清空所有账目！ " << endl;
	}
	else
	{
		return;
	}
}

bool BillManager::IsIdExist(int id)
{
	bool flag = false;
	for (int i = 0; i < this->m_BillNum; i++)
	{
		if (id == this->m_BillArray[i]->m_nBillId)
		{
			flag = true;
		}
	}
	return flag;
}