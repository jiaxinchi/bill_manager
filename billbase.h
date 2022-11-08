#pragma once
#include <string>

using namespace std;

struct Date
{
	int m_nYear;
	int m_nMonth;
	int m_nDay;
};

class Bill
{
public:
	//显示账目信息
	virtual void ShowInfo() = 0;

	//获取账目类型
	virtual string GetBillType() = 0;

	//编号
	int m_nBillId;

	// 日期
	struct Date  Date;

	//账目类型
	int m_BillType;

	//金额
	double m_dAmount;

	//事由/备注
	string m_strRemark;
};