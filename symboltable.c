#include "symboltable.h"

static int layer = 0;

unsigned int hash_pjw(char *name) {
	unsigned int val=0,i;
	for(;*name;++name)
	{
		val=(val<<2)+*name;
		if(i=val&~0x3fff) val=(val^(i>>12))&0x3fff;
	}
	return val;
} 

void init_table() {
	int i;
	for (i=0; i<HASH_SLOT; i++)
		hashTable[i] = NULL;
	for (i=0; i<LAYER_DEPTH; i++)
		layerStack[i] = NULL;
	layer = 0;

	funcTableHeader = NULL;
	structTableHeader = NULL;
}

//插入变量表，要求调用者在调用前处理好name和type
void insert(varElement* elem) {
	printf("in insert %s\n", elem->name);
	int index = hash_pjw(elem->name);
	printf("insert index %d\n", index);
	elem->slot_no = index;
	elem->layer_no = layer;
	elem->next = NULL;
	elem->slot_next = NULL;
	//varElement *p = hashTable[index];
	//varElement *q = layerStack[layer];
	
	//插入槽链表头——这样应该删除操作也方便些
	if (hashTable[index] == NULL) {
		hashTable[index] = elem;
		//printf("%s\n", hashTable[index]->name);
	}
	else {
		elem->slot_next = hashTable[index];
		hashTable[index] = elem;
	}

	//插入层链表头
	if (layerStack[layer] == NULL)
		layerStack[layer] = elem;
	else {
		elem->next = layerStack[layer];
		layerStack[layer] = elem;
	}
}

//查找任何最接近此层的定义
varElement *searchAll(char *name) {
	printf("in search all %s\n", name);
	int index = hash_pjw(name);
	printf("search index: %d\n", index);
	varElement *p = hashTable[index];
	while (p != NULL) {
		//因为每次都把越里层的插在前面，所以找到的第一个一定是最里层的定义
		if (strcmp(p->name, name) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

//查找此层的定义
varElement *search(char *name) {
	printf("in search %s\n", name);
	int index = hash_pjw(name);
	printf("search index: %d\n", index);
	varElement *p = hashTable[index];
	//if (p == NULL) printf("null\n");
	while (p != NULL) {
		if (strcmp(p->name, name)==0 && p->layer_no == layer)
			//名称和层数都相同，表示被定义过
			return p;
		p = p->next;
	}
	return NULL;
}

//进入更深的一层
void into_a_layer() {
	layer++;
}

//从较深的一层中出来，把这层中的所有变量都删除掉 
void out_of_a_layer() {
	varElement *p = layerStack[layer];
	if (p == NULL) {
		layer--;
		return;
	}
	varElement *q = NULL;	//指向同一层链表中p的下一个
	while (p != NULL) {
		q = p->next;
		int slotno = p->slot_no;
		hashTable[slotno] = p->slot_next;
		//free(p);
		p = q;
	}
	layer--;
}

// ！！为什么加了这两个函数就报错了我给跪了难道不是和下面两个一样嘛...wtf
//向结构体表插入一个结构体项
void insertStruct(structTableElement *struc) {
	printf("in insertStruct %s\n", struc->name);
	struc->next = structTableHeader;
	structTableHeader = struc;
}	

//查询一个结构体
structTableElement* searchStruct(char * strname) {
	printf("in searchStruct %s\n", strname);
	structTableElement *q = structTableHeader;
	//if (p == NULL) printf("null\n");
	while (q != NULL) {
		//printf("   now %s\n", p->name);
		if (strcmp(q->name, strname)==0)
			return q;
		q = q->next;
	}
	printf("return NULL in searchStruct\n");
	return NULL;
}

//向函数表插入一个函数项
void insertFunc(funcTableElement *func) {
	printf("in insertFunc %s\n", func->name);
	func->next = funcTableHeader;
	funcTableHeader = func;
	if (funcTableHeader == NULL) printf("null in insertFunc\n");
}	

//查询一个函数
funcTableElement* searchFunc(char * funcname) {
	printf("in searchFunc %s\n", funcname);
	funcTableElement *p = funcTableHeader;
	//if (funcTableHeader == NULL) printf("null func\n");
	//else printf("not null func\n");
	//if (p == NULL) printf("null\n");
	while (p != NULL) {
		//printf("   now %s\n", p->name);
		if (strcmp(p->name, funcname)==0)
			return p;
		p = p->next;
	}
	return NULL;
}



