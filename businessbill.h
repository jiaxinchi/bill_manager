#pragma once
#include <string>
#include<iostream>
# include <ctime>
#include "billbase.h"

using namespace std;

class BusinessBill : public Bill
{
public:

	//构造函数
	BusinessBill(int id, int billtype, double amount, string remarks);

	BusinessBill(int id, int billtype, double amount, string remarks, struct Date date);

	//显示账目信息
	virtual void ShowInfo();

	//获取账目类型
	virtual string GetBillType();

	//析构函数
	~BusinessBill();
};