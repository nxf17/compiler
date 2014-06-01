int main(){
	float a;
	int i;
	a = 1.5;	
	for (i = 1; i < 0; i=i+1) {
		int a, b = 4;
		int a;	//上一句为定义局部变量不报错，这一句就重复定义了
		a = b;	
	}
	return 1.5;	//返回值不统一
}
