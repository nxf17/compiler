float x;

struct man {
	int age  = 22;	//初始化了域
	float height;
};

int main() {
	struct man Pu;
	struct woman MrsPu;	//未定义过的结构体
	int b = 20;
	float f = 1.6;
	a = 8;	//未定义的变量
	x = a;
	Pu.age = b;
	Pu.height = x;
	Pu.age = f;	//类型不匹配
	Pu.weight = x;	//不存在的域
	b.age = 23;	//非结构体变量	
}

