int main()
{
	float i = 3;
	int j = 0x24, k = 024;
	i = j;	//赋值左右不统一
	while (i < 10) {	//使用float做比较
		i = i * 2.0;
		break;
	}
	break;	//错误用break
	
	for (k=0; k<5; k=k+1) {
		if (k < 3) 
			continue;
		else 
			j = j + 1;
	}
	
	continue;	//错用continue
}
