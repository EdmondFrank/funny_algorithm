// 有 1000 个一模一样的瓶子，其中有 999 瓶是普通的水，有一瓶是毒药。
// 任何喝下毒药的生物都会在一星期之后死亡。
// 现在，你只有 10 只小白鼠和一星期的时间，如何检验出哪个瓶子里有毒药？

#include <iostream>
using namespace std; 
 
int main(){
	const int mouse_num = 10;//老鼠数量
	int mouse[mouse_num] = {0};//老鼠喝水一周后的状态'0'为存活，'1'为死亡
	int drug = 0;//假设有毒瓶子号为177,即喝水一周后老鼠的状态｛0 0 1 0 1 1 0 0 0 1｝
	for (int i = 0; i < mouse_num; i++)
	{
		cin>>mouse[i];//输入老鼠喝水后的存活状态
	}
	for (int i = 0; i < mouse_num; i++)
	{
		drug |= (mouse[i] << (mouse_num - i - 1));//进行位运算
	}
	//判断是否有毒
	if (drug == 0)
	{
		cout<<"没有有毒的"<<endl;
	}
	else{
		cout<<"有毒的是第"<<drug<<"瓶";
		return 0;
	}
}