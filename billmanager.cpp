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
		cout << "�������¼���룺";
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
				cout << "�����������ﵽ���Σ������˳��˵�����ϵͳ�� " << endl;
				system("pause");
				exit(0);
			}
			cout << "�������!��ʣ" << 2 - CheckNum << "�λ��ᣡ " << endl;
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
	{	//����
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

	//����
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
		cout << "�����������룺 ";
		char cNewPassword[MAXPL];
		cin >> cNewPassword;
		while (true)
		{
			if (strcmp(this->cPassword, cNewPassword) == 0)
			{
				cout << "�����벻�ܺ�ԭʼ������ͬ�����������룺 ";
				cin >> cNewPassword;
			}
			else
			{
				break;
			}
		}
		char cConformPassword[MAXPL];
		cout << "���ٴ����������룺 ";
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
			cout << "���������óɹ��������Ʊ��ܣ� " << endl;
			return;
		}
		else
		{
			cout << "������������벻һ�£����������ã� " << endl;
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
	cout << "**********��ӭʹ�á��˵�����ϵͳ��**********" << endl;
	if (this->IsPasswordExist())
	{
		this->CheckPassword();
		cout << "*****  ��¼�ɹ������������˵�����ϵͳ!  *****" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "����ʹ�ã������õ�¼���룺 ";
		cin >> this->cPassword;
		cout << "���óɹ������μ����ĵ�¼���룡 " << endl;
		this->SavePassword();
		system("pause");
		system("cls");
	}
}

void BillManager::ShowMenu()
{
	cout << setw(55) << setfill('*') << "" << endl;
	cout << setw(32) << "�˵�����ϵͳ V" << VERSION << setw(20) << "" << endl;
	cout << setw(55) << setfill('*') << "" << endl;
	cout << setw(35) << "  00  �˳�ϵͳ  " << setw(20) << "" << endl;
	cout << setw(35) << "  01  �����Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  02  ɾ����Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  03  �޸���Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  04  ������Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  05  ��ʾȫ��  " << setw(20) << "" << endl;
	cout << setw(35) << "  06  ͳ����Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  07  �����Ŀ  " << setw(20) << "" << endl;
	cout << setw(35) << "  08  �޸�����  " << setw(20) << "" << endl;
	cout << setw(55) << setfill('*') << "" << setfill(' ') << endl;
}

void BillManager::Add_Bill()
{
	cout << "������Ҫ�����Ŀ�������� " << endl;
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
			cout << "��������Ŀ���ڣ�����\"0\"Ϊ��ǰ���ڣ��������Կո�����������磺2000 10 11���� " << endl;
			cin >> date.m_nYear;
			int datetype;//����������Ƿ���Ĭ����ʽ
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
			cout << "�������" << i + 1 << "����Ŀ�����ͣ�1���ճ���֧��2������������3�������������� ";
			cin >> type;
			if (type != 1 && type != 2 && type != 3)
			{
				cout << "��Ŀ���Ͳ���ȷ,���������룺" ;
				cin >> type;
			}
			cout << "�������" << i + 1 << "����Ŀ�Ľ�Ԫ���� ";
			cin >> amount;
			cout << "�������" << i + 1 << "����Ŀ�����ɻ�ע�� ";
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
				cout << "��Ŀ���Ͳ���ȷ! " << endl;
				break;
			}
			}
		}
		this->m_BillArray = tempSpace;
		this->m_BillNum = newSize;
		this->Save_Bill();
		this->m_EmpIsEmpty = false;
		cout << "��Ŀ�����ɣ� " << endl;
	}
	else
	{
		cout << "�������� " << endl;
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
		cout << "��ǰϵͳ�����κ���Ŀ��Ϣ�� " << endl;
	}
	else
	{
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "���|" << "\t" << setw(11) << "����|" << setw(13) << "����|" << setw(13) << "���(Ԫ)|" << "\t" << "��ע" << endl;
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
		cout << "��ǰϵͳ�����κ���Ŀ��Ϣ��" << endl;
		return;
	}
	int id;
	cout << "������Ҫɾ������Ŀ��ţ� " << endl;
	cin >> id;
	if (this->IsIdExist(id))
	{
		cout << "����Ŀ��Ϣ���£� " << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "���|" << "\t" << setw(11) << "����|" << setw(13) << "����|" << setw(13) << "���(Ԫ)|" << "\t" << "��ע" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		this->m_BillArray[id]->ShowInfo();
		cout << "------------------------------------------------------------------------" << endl;
		cout << "ȷ��Ҫɾ������Ŀ��(1:yes;0:no): ";
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
			cout << "ɾ���ɹ��� " << endl;
			this->Save_Bill();
		}
		else
		{
			return;
		}
	}
	else
	{
		cout << "û�и���Ŀ��Ϣ����ȷ�Ϻ��ѯ�� " << endl;
	}
}

void BillManager::Modify_Bill()

{
	if (this->m_BillNum == 0)
	{
		cout << "��ǰϵͳ�����κ���Ŀ��Ϣ��" << endl;
		return;
	}
	cout << "��������Ҫ�޸ĵ���Ŀ��ţ� ";
	int id;
	cin >> id;
	if (this->IsIdExist(id))
	{
		cout << "����Ŀ��Ϣ���£�" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		cout << setw(6) << "���|" << "\t" << setw(11) << "����|" << setw(13) << "����|" << setw(13) << "���(Ԫ)|" << "\t" << "��ע" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		this->m_BillArray[id]->ShowInfo();
		cout << "------------------------------------------------------------------------" << endl;
		cout << "ȷ��Ҫ�޸ĸ���Ŀ��(1:yes;0:no): ";
		int conform;
		cin >> conform;
		if (conform == 1)
		{
			int billtype;
			double amount;
			string remarks;
			struct Date date;
			cout << "���޸ĸ���Ŀ�����ڣ��������Կո���������磺2000 10 11���� " << endl;
			cin >> date.m_nYear; cin >> date.m_nMonth; cin >> date.m_nDay;
			cout << "���޸ĸ���Ŀ���ͣ�1���ճ���֧��2������������3�������������� ";
			cin >> billtype;
			cout << "���޸ĸ���Ŀ�Ľ�Ԫ���� ";
			cin >> amount;
			cout << "���޸ĸ���Ŀ�����ɻ�ע�� ";
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
			cout << "�޸���ɣ� " << endl;
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
		cout << "��ǰϵͳ�����κ���Ŀ��Ϣ��" << endl;
		return;
	}
	cout << "��ѡ����ҷ�ʽ����1�������ڲ��ң�2���������ң� " << endl;
	int findtype;
	cin >> findtype;
	switch (findtype)
	{
	case 1:
	{
		cout << "�����뿪ʼ���ڣ����磺2000 10 11���� " << endl;
		struct Date begin_date;
		cin >> begin_date.m_nYear; cin >> begin_date.m_nMonth; cin >> begin_date.m_nDay;
		cout << "������������ڣ����磺2000 10 11���� " << endl;
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
					cout << "������������Ŀ���£� " << endl;
					cout << "------------------------------------------------------------------------" << endl;
					cout << setw(6) << "���|" << "\t" << setw(11) << "����|" << setw(13) << "����|" << setw(13) << "���(Ԫ)|" << "\t" << "��ע" << endl;
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
			cout << "δ���ҵ�������������Ŀ�� " << endl;
		}
		break;
	}
	case 2:
	{
		cout << "������Ҫ���ҵĽ�Χ�Կո���������磺100 200���� " << endl;
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
					cout << "������������Ŀ���£� " << endl;
					cout << "------------------------------------------------------------------------" << endl;
					cout << setw(6) << "���|" << "\t" << setw(11) << "����|" << setw(13) << "����|" << setw(13) << "���(Ԫ)|" << "\t" << "��ע" << endl;
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
			cout << "δ���ҵ�������������Ŀ�� " << endl;
		}

		break;
	}
	default:
		cout << "�������� " << endl;
		break;
	}
}

void BillManager::Count_Bill()
{
	cout << "��Ŀͳ�����£�" << endl;
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
	cout << "<�ճ�>  ֧���ܼƣ�" << setw(5) <<Sum_daily<<" Ԫ"<<endl;
	cout << "<����>  �����ܼƣ�" << setw(5)<<abs(Sum_Business_in) << " Ԫ" <<"  ֧���ܼƣ�" << setw(5) << abs(Sum_Business_out) << " Ԫ" << endl;
	cout << "<����>  �����ܼƣ�" << setw(5) << abs(Sum_Social_in) << " Ԫ" <<"  ֧���ܼƣ�" << setw(5) << abs(Sum_Social_out) << " Ԫ" << endl;
	cout << "--------------------------------------------------" << endl;
}

void BillManager::Erase_Bill()
{
	this->CheckPassword();
	cout << "ȷ��Ҫ���������Ŀ��(1:yes;0:no): ";
	int conform;
	cin >> conform;
	if (conform == 1)
	{
		this->m_BillArray = NULL;
		this->m_BillNum = 0;
		this->m_EmpIsEmpty = true;
		remove(DFILENAME);
		cout << "�����������Ŀ�� " << endl;
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