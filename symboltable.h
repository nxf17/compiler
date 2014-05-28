#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define HASH_SLOT 0x4000	//hash表槽数（还未理解hash_pjw要的槽数是这么多...）
#define LAYER_DEPTH 10	//层最大深度

typedef struct Type_ *Type;
typedef struct Fun_ *Fun;
typedef struct FieldList_ *FieldList;
typedef struct varElement varElement;
typedef struct structTableElement structTableElement;
typedef struct funcTableElement funcTableElement;
typedef struct argElement argElement;

static varElement* hashTable[HASH_SLOT];	//hash表项
static varElement* layerStack[LAYER_DEPTH];	//控制每层的栈
static int layer = 0;	//目前在第几层

static structTableElement *structTableHeader; 	//结构体表的表头

static funcTableElement *funcTableHeader;	//函数表的表头

/* 类型 */
struct Type_ {
	enum{BASIC, ARRAY, STRUCTURE} kind;
	union {
		int basic;	//基本类型:0-int, 1-float
		struct {	//数组类型
			int size;
			Type elem;	//一个指针，串起数组元素
		}array;
		//FieldList structure;	//结构体类型信息是一个链表
		varElement *var; 
	}u;
};

/* 域 */
struct FieldList_ {
	char *name;	//域名
	Type type;	//域类型
	FieldList tail;	//下一个域
};

/* 变量表项 */
struct varElement {	
	char *name;	//变量名
	Type type;	//变量类型
	int layer_no;	//在哪一层
	int slot_no;	//在哪个槽
	struct varElement *next;	//在函数表表示同一层的下一个，在结构体中就是下一个成员
	struct varElement *slot_next;	//同一槽的下一个
};

/* 结构体变量表项 */
struct structTableElement {	
	char *name;	//结构体的tag标签名
	Type type;
	structTableElement *next;
};

/* 函数表项 */
struct funcTableElement {
	char *name; //函数名
	Type type; 	//函数的返回类型
	argElement *argListHeader;
	funcTableElement *next;
};

/* 参数项 */
struct argElement {
	char *name;	//参数名
	Type type;	//参数类型
	argElement *next;
};

void init_all_table();	//初始化符号表
unsigned int hashpjw(char *);
void insert(varElement *);	//插入一个变量
varElement* searchAll(char *); 	//搜索一个变量最里层的定义
varElement* search(char *);	//搜索一个变量在此层的定义
void into_a_layer();	//进入一层
void out_of_a_layer();	//从一层中出来

void insertStruct(structTableElement *);
structTableElement* searchStruct(char *);

void insertFunc(funcTableElement *);	//向函数表插入一个函数项
funcTableElement* searchFunc(char *);	//在函数表查询函数



#endif
