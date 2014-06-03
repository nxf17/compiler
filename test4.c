int foo(int x) {
	float y;
	y = 4.5;
}

int main()
{
	int a[3][4], b[7][6][5];
	int notArray, notFunc;
	foo(3, 4);	//函数参数不匹配
	foo(1.5);	//同样
	notArray[5] = 7;	//非数组型使用[]
	notFunc(6);	//非函数使用()
	a[3][2] = 5;
	b[7][6] = a[3];
	b[7] = a[3];	//数组不匹配
	return 1;
}

