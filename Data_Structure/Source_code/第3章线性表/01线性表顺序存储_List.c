#include<iostream>
using namespace std;
int main(void)
{
	char chexing;
	int lucheng;
	cout << "请输入车型 (x表示夏利,f表示富康,s表示桑塔纳): ";
	cin >> chexing;
	cout << "请输入行车公里数:  ";
	cin >> lucheng; 
	if (lucheng > 0)
	{
		switch (chexing)
		{
		case'x':
			cout << "你乘坐的是夏利,路费为:" << (lucheng <= 3) ? 7 : (7 + (lucheng - 3)*2.1) << "元。" << endl;  break;
		case 'f':
			cout << "你乘坐的是富康,路费为:" << (lucheng <= 3) ? 8 : (8 + (lucheng - 3)*2.4) << "元。 " << endl;  break;
		case's':
			cout << "你乘坐的是桑塔纳,路费为:" << (lucheng <= 3) ? 9 : (9 + (lucheng - 3)*2.7) << "元。 " << endl; break;
		default:  cout << "无此车! " << endl;
		}
	}
	else
		cout << "路程数错误!" << endl;
	return 0;
}
