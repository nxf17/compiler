int main(){
	int a = 1;
	int b = 2;
	int c;
	/* 尝试这种注释 */
	c = a + b;
	while (1) {
		a + b = 5;	//左值错误
		t = a; 		//未定义
		break;		
	}
	return 1.5;	//返回类型不统一
}
