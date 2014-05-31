int foo(int x) {
	float y;
}

int main()
{
	int a[3][4], b[7][6][5];
	foo(3, 4);	//函数参数不匹配
	foo(1.5);	//同样
	a[3][2] = 5;
	b[7][6] = a[3];
	b[7] = a[3];	//数组不匹配
	return 1;
}

