#pragma once
#include "billbase.h"

using namespace std;

class DailyBill : public Bill
{
public:

	//构造函数
	DailyBill(int id, int billtype, double amount, string remarks);

	DailyBill(int id, int billtype, double amount, string remarks, struct Date date);

	//显示账目信息
	virtual void ShowInfo();

	//获取账目类型
	virtual string GetBillType();

	//析构函数
	~DailyBill();
};