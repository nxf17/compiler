float x;

struct man {
	int age  = 22;	//初始化了域
	float height;
	int grade;
};

int main() {
	struct man MrPu;
	struct woman MrsPu;	//未定义过的结构体
	int b = 20;
	float f = 1.6;
	a = 8;	//未定义的变量
	MrPu.age = b;
	MrPu.height = x;
	MrPu.age = f;	//类型不匹配
	MrPu.weight = x;	//不存在的域
	b.age = 23;	//非结构体变量	
}

