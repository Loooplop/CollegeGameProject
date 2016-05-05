#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int a = 640455691;
	int b = 6;
	for (int i = 0; i < 30; i++)
	{
		int c = a / b;
		b = (b + c) / 2;
		cout << b << endl;
	}
	cin.get();
	return 0;
}