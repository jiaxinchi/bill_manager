#include <iomanip>
#include<iostream>
#include "dailybill.h"
#include "const.h"
 
DailyBill::DailyBill(int id, int billtype, double amount, string remarks)
{
	this->m_nBillId = id;
	this->m_BillType = billtype;
	this->m_dAmount = amount;
	this->m_strRemark = remarks;
	time_t now = time(0);
	tm *to_tm = localtime(&now);
	this->Date = { to_tm->tm_year + 1900, to_tm->tm_mon + 1, to_tm->tm_mday };
}

DailyBill::DailyBill(int id, int billtype, double amount, string remarks, struct Date date)
{
	this->m_nBillId = id;
	this->m_BillType = billtype;
	this->m_dAmount = amount;
	this->m_strRemark = remarks;
	this->Date = date;
}

void DailyBill::ShowInfo()
{
	cout << setw(5) << this->m_nBillId << "|"
		<< "\t" << setw(4) << setfill('0') << this->Date.m_nYear << "/" << setw(2) << setfill('0') << this->Date.m_nMonth << "/" << setw(2) << setfill('0') << this->Date.m_nDay << setfill(' ') << "|"
		<< setw(12) << this->GetBillType() << "|"
		<< setw(12) << this->m_dAmount << "|"
		<< "\t" << this->m_strRemark << endl;
}

string DailyBill::GetBillType()
{
	return string("日常开支 ");
}

DailyBill::~DailyBill()
{
}
