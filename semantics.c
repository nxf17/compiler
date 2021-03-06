#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "symboltable.h"
#include "semantics.h"

FILE *out_fp;
bool OUT = true;
int ADDR = 0, index_t = 0;//维护sp指针偏移量,寄存器号

void Index_Add() {
	if(index_t < 7)
		index_t++;
	else {
		printf("Reg spilling\n");
		exit(-1);
	}
}

void Index_Min() {
	if(index_t > 0)
		index_t--;
	else {
		printf("Reg error\n");
		exit(-1);
	}
}

bool type_equal(Type x, Type y) { //判断类型是否匹配
	if(x->kind == BASIC && y->kind == BASIC) {
		if(x->u.basic == y->u.basic) {
			return true;
		}
	} 
	else if (x->kind == ARRAY && y->kind == ARRAY) {
		if (type_equal(x->u.array.elem, y->u.array.elem))
			return true;
	}
	else if (x->kind == STRUCTURE && y->kind == STRUCTURE) {
		varElement *p = x->u.var;
		varElement *q = x->u.var;
		while (p != NULL) {
			if (q == NULL)
				return false;
			else if (strcmp(p->name, q->name)!=0)
				return false;
			else if (!type_equal(p->type, q->type))
				return false;
			else
				p = p->next;
				q = q->next;
		}
		if (q != NULL) return false;
		return true;
	}
	return false;
}


void showStructMember(Type type) {
	printf("--show struct member--\n");
	if (type->kind != STRUCTURE) {
		printf("this type is not a struct!\n");
		return;	
	}
	varElement *mem = type->u.var;
	while (mem != NULL) {
		if (mem->type->kind == BASIC) {
			if (mem->type->u.basic == 0) printf("int ");
			else printf("float ");		
		}
		else if (mem->type->kind == ARRAY)
			printf("array ");
		else 
			printf("struct ");
		printf("%s\n", mem->name);
		mem = mem->next;
	}
	printf("--end--\n");	 
}

void showBasicType(Type type) {
	if (type->u.basic == 0) printf("int\n");
	else printf("float\n");
}

static int loopNum = 0;	//用于记录循环在第几层

void doProgram(TreeNode *p) {
	//printf("---doProgram---\n");
	//printf("root->state:%s\n", p->state);
	out_fp = fopen("out.s", "w");
	if(out_fp == NULL) 
		perror("error in creating out.s\n");

	fprintf(out_fp,".data\n");
	fprintf(out_fp,"_prompt: .asciiz \"Enter an integer:\"\n");
	fprintf(out_fp,"_ret: .asciiz \"\\n\"\n");
	fprintf(out_fp,".globl main\n");
	fprintf(out_fp,".text\n");
	fprintf(out_fp,"read:\n");
	fprintf(out_fp,"\tli $v0,4\n");
	fprintf(out_fp,"\tla $a0,_prompt\n");
	fprintf(out_fp,"\tsyscall\n");
	fprintf(out_fp,"\tli $v0,5\n");
	fprintf(out_fp,"\tsyscall\n");
	fprintf(out_fp,"\tjr $ra\n");
	fprintf(out_fp,"\n");
	fprintf(out_fp,"write:\n");
	fprintf(out_fp,"\tli $v0,1\n");
	fprintf(out_fp,"\tsyscall\n");
	fprintf(out_fp,"\tli $v0,4\n");
	fprintf(out_fp,"\tla $a0,_ret\n");
	fprintf(out_fp,"\tsyscall\n");
	fprintf(out_fp,"\tmove $v0,$0\n");
	fprintf(out_fp,"\tjr $ra\n");
	fprintf(out_fp,"\n");
	fprintf(out_fp,"main:\n");

	TreeNode *p1 = p->firstChild;
	doExtDefList(p1);
	fprintf(out_fp,"\tmove $v0, $0\n");
	fprintf(out_fp,"\tjr $ra\n");//手动添加return 0，后续要进行修改
	fclose(out_fp);
	if(!OUT) 
		remove("out.s");
	else
		printf("Create out.s successfully\n");
}

void doExtDefList(TreeNode *p) {
	//printf("doExtDefList\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			doExtDef(p1);
			doExtDefList(p2);
			break;
			   }
		case 2:
			break;
	}
}

void doExtDef(TreeNode *p) {
	//printf("doExtDef\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	switch (p->productionRule) {
		case 1:{
			//将doExtDecList()返回的变量链表赋为doSpecifier()返回的Type,插入变量表
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			Type type = doSpecifier(p1);
			varElement *elem = doExtDecList(p2);
			varElement *elemn = NULL;
			while (elem != NULL) {
				Type t = elem->type;
				if (t->kind != BASIC) {
					while (t->kind == ARRAY || t->u.array.elem->kind != BASIC) {	//如果是数组要找到最底部的type节点赋为Specifier传回的Type
						t = t->u.array.elem;				
					}
					//free(t->u.array.elem);
					t->u.array.elem = type;	//在倒数第二个节点处改变Type
				} else {
					//free(elem->type);
					elem->type = type;
					if (search(elem->name) != NULL) {	//查找此层定义不为空，说明变量重复定义
						printf("error type 3 at line %d: variable %s redefined.\n", p->line, elem->name);
						elem = elem->next;
					} else {	
						elemn = elem->next;
						insert(elem);
						elem = elemn;
					}
				}
			}
			break;
			   }
		case 2:	{
			TreeNode *p1 = p->firstChild;
			doSpecifier(p1);
			break;
				}
		case 3:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			TreeNode *p3 = p2->rightBrother;
			Type type = doSpecifier(p1);
			doFunDec(type, p2);	//将返回类型传进去，在doFunDec中处理函数表
			doCompSt(p3);
			break;
			   }
	}
}

varElement* doExtDecList(TreeNode *p) {
	//printf("doExtDecList\n");
	//这个函数会把同一语句中出现的变量串起来
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			varElement *elem1 = doVarDec(p1);
			return elem1;
			break;
			   }
		case 2:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			varElement *elem1 = doVarDec(p1);
			varElement *elem2 = doExtDecList(p3);
			elem1->next = elem2;
			return elem1;
			break;
			   }
	}
}

Type doSpecifier(TreeNode *p) {
	//printf("doSpecifier\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	Type type = (Type)malloc(sizeof(struct Type_));
	switch (p->productionRule) {
		case 1:{
				   if(p->firstChild == NULL)
					   printf("NULL\n");
				   TreeNode *p1 = p->firstChild;
				   type->kind = BASIC;
				   //printf("p1->state: %s\n", p1->state);
				   if (strcmp(p1->state, "TYPE:int") == 0) {
					   type->u.basic = 0;
				   }
				   else
					   type->u.basic = 1;
				   break;
			   }
		case 2:{
				   TreeNode *p1 = p->firstChild;
				   type = doStructSpecifier(p1);
				   return type;
				   break;
			   }
	}
	return type;
}

Type doStructSpecifier(TreeNode *p) {	//待完成
	//printf("doStructSpecifier\n");
	//printf("production rule:%d\n", p->productionRule);
	switch (p->productionRule) {
		case 1: {
					TreeNode *p2 = p->firstChild->rightBrother;
					TreeNode *p4 = p2->rightBrother->rightBrother;
					char *tagname = doOptTag(p2);
					if (tagname != NULL) {	//有标签名，把它加入结构体表中
						if (searchStruct(tagname) != NULL || searchAll(tagname) != NULL) {
							printf("Error type 16 at line %d: struct tag %s is same as other struct tag or variable name\n", p->line, tagname);					
							return NULL;
						}
						structTableElement *str = (structTableElement *)malloc(sizeof(structTableElement));
						str->name = tagname;
						str->type = (Type)malloc(sizeof(struct Type_));
						str->type->kind = STRUCTURE;
						str->type->u.var = doDefList(p4, 1);
						insertStruct(str);
						return str->type;
					} else {
						Type temptype = (Type)malloc(sizeof(struct Type_));
						temptype->kind = STRUCTURE;
						temptype->u.var = doDefList(p4, 1);
						//showStructMember(temptype);
						return temptype;
					}
					break;
				}
		case 2: {
					//Tag要在之前定义过才能有效，去结构体表中查找
					TreeNode *p2 = p->firstChild->rightBrother;
					char *tagname = doTag(p2);
					structTableElement *str = searchStruct(tagname);
					if (str == NULL) {
						printf("Error type 17 at line %d: struct tag %s undefined\n", p->line, tagname);
						return NULL;
					} else {	//查找到，就将表中的type返回
						//showStructMember(str->type);
						return str->type;
					}
					break;
				}
	}
}

char* doOptTag(TreeNode *p) {	//返回一个含名字的字符串
	//printf("doOptTag\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1: {
			TreeNode *p1 = p->firstChild;
			char *id = (char *)malloc(sizeof(char*)*(strlen((p1->value).idValue)+1));
			strcpy(id, p1->value.idValue);
			return id;
			break;
			}
		case 2: {
			return NULL;
			break;
			}
	}
}

char* doTag(TreeNode *p) {
	TreeNode *p1 = p->firstChild;
	char *id = (char *)malloc(sizeof(char*)*(strlen((p1->value).idValue)+1));
	strcpy(id, p1->value.idValue);
	return id;
}

varElement* doVarDec(TreeNode *p) {
	//printf("doVarDec\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	switch (p->productionRule) {
		case 1:{
			//产生ID，产生一个varElement节点，value设为ID名称，返回
			TreeNode *p1 = p->firstChild;
			//printf("p1->state:%s\n", p1->state);
			varElement *elem = (varElement *)malloc(sizeof(struct varElement));
			//printf("p1->value.idValue:%s\n", p1->value.idValue);
			elem->name = (char *)malloc(sizeof(char*)*(strlen((p1->value).idValue)+1));
			elem->next = NULL;
			strcpy(elem->name, p1->value.idValue);
			Type type = (Type)malloc(sizeof(struct Type_));
			type->kind = BASIC;
			elem->type = type;

			ADDR -= 4;
			elem->addr_sp = ADDR;
			fprintf(out_fp, "\taddi $sp, $sp, -4\n");//定义变量时给变量分配栈区内存
			
			return elem;
			break;
			   }
		case 2: {
			//数组声明
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			varElement *elem = (varElement *)malloc(sizeof(struct varElement));
			Type type = (Type)malloc(sizeof(struct Type_));
			type->kind = BASIC;	//最下端的节点，BASIC标记
			Type type2 = (Type)malloc(sizeof(struct Type_));
			type2->kind = ARRAY;
			type2->u.array.size = p3->value.intValue;
			type2->u.array.elem = type;
			while (p1->productionRule != 1) {	//如果仍然是产生VarDec LB INT RB递推处理
				//printf("in while\n");
				type = type2;
				p1 = p1->firstChild;
				p3 = p1->rightBrother->rightBrother;
				type2 = (Type)malloc(sizeof(struct Type_));
				type2->kind = ARRAY;
				type2->u.array.size = p3->value.intValue;
				type2->u.array.elem = type;
				//printf("out while\n");
			}
			p1 = p1->firstChild;	//指向ID点
			elem->name = (char *)malloc(sizeof(char *)*(strlen(p1->value.idValue)+1));
			elem->next = NULL;
			strcpy(elem->name, p1->value.idValue);
			elem->type = type2;

			ADDR -= type2->u.array.size * 4;
			elem->addr_sp = ADDR;
			fprintf(out_fp, "\taddi $sp, $sp, -%d\n", type2->u.array.size * 4);//分配最简单的数组空间

			return elem;
			break;
				}
	}
}

void doFunDec(Type type, TreeNode *p) {
	//printf("doFunDec\n");
	//printf("TreeNode->state:%s\n", p->state);
	TreeNode *p1 = p->firstChild;
	char * funcname = (char *)malloc(sizeof(char*)*(strlen((p1->value).idValue)+1));
	strcpy(funcname, p1->value.idValue);	//得到函数名
	if (searchFunc(funcname) != NULL) {
		printf("Error type 4 at line %d '&&': function redefined\n", p->line);	//函数重复定义
		return;	
	}
	funcTableElement *elem = (funcTableElement *)malloc(sizeof(funcTableElement));
	elem->name = funcname;
	elem->type = type;
	elem->argListHeader = NULL;
	switch (p->productionRule) {
		case 1: {
			TreeNode *p3 = p1->rightBrother->rightBrother;
			elem->argListHeader = doVarList(p3);
			insertFunc(elem);
			//if (funcTableHeader == NULL) printf("null in doFunDec");
			break;
			}
		case 2: {
			insertFunc(elem);
			break;
			}
	}
}

argElement* doVarList(TreeNode *p) { //仍然用定义串联的方法返回参数列表
	//printf("doVarList\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1: {
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			argElement *arg1 = doParamDec(p1);
			argElement *arg2 = doVarList(p3);
			arg1->next = arg2;
			return arg1;
			break;
			}
		case 2: {
			TreeNode *p1 = p->firstChild;
			argElement *arg1 = doParamDec(p1);
			return arg1;
			break;
			}
	}
}

argElement* doParamDec(TreeNode *p) {	//这边有个参数为数组的处理，考虑是否好完成
	//printf("doParamDec\n");
	TreeNode *p1 = p->firstChild;
	TreeNode *p2 = p1->rightBrother;	
	argElement *arg = (argElement *)malloc(sizeof(argElement));
	arg->type = doSpecifier(p1);
	arg->next = NULL;
	return arg;
}

void doCompSt(TreeNode *p) {
	//printf("doCompSt\n");
	//printf("TreeNode->state:%s\n", p->state);
	into_a_layer();
	TreeNode *p2 = p->firstChild->rightBrother;
	TreeNode *p3 = p2->rightBrother;
	doDefList(p2, 0);
	doStmtList(p3);
	out_of_a_layer();
}

void doStmtList(TreeNode *p) {
	//printf("doStmtList\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			doStmt(p1);
			doStmtList(p2);
			break;
			   }
		case 2:
			break;
	}
}

void doStmt(TreeNode *p) {
	//printf("doStmt\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			doExp(p1);
			break;
			   }
		case 2:{
			TreeNode *p1 =	 p->firstChild;
			doCompSt(p1);
			break;
			   }
		case 3:	{
			//printf("in return\n");
			TreeNode *p2 = p->firstChild->rightBrother;
			Type type = doExp(p2);
			if (!type_equal(type, funcTableHeader->type)) {	//直接和函数表中第一项比较，一定是最近的函数
				printf("Error 8 at line %d: function return unexpected type\n", p->line);
			}
			//printf("out return\n");
			break;
				}
		case 4:	{
			//这块可以判断一下p3代表的exp是不是int。不过实验讲义假设一定是
			//后两个同理
			TreeNode *p3 = p->firstChild->rightBrother->rightBrother;
			TreeNode *p5 = p3->rightBrother->rightBrother;
			doExp(p3);
			doStmt(p5);
			break;
				}
		case 5:{
			TreeNode *p3 = p->firstChild->rightBrother->rightBrother;
			TreeNode *p5 = p3->rightBrother->rightBrother;
			TreeNode *p7 = p5->rightBrother->rightBrother;
			doExp(p3);
			doStmt(p5);
			doStmt(p7);
			break;
			   }
		case 6:{
			TreeNode *p3 = p->firstChild->rightBrother->rightBrother;
			TreeNode *p5 = p3->rightBrother->rightBrother;
			loopNum++;
			doExp(p3);
			doStmt(p5);
			loopNum--;
			break;
			   }
		case 7: {
			if (loopNum == 0)
				printf("Error 18 at line %d: use 'break' out of a loop\n", p->line);
			break;
			}
		case 8: {
			if (loopNum == 0)
				printf("Error 19 at line %d: use 'continue' out of a loop\n", p->line);
			break;
			}
		case 9:{
			//the for loop,待完善，应该是中间那个要做个type检查。
			TreeNode *p3 = p->firstChild->rightBrother->rightBrother;
			TreeNode *p5 = p3->rightBrother->rightBrother;
			TreeNode *p7 = p5->rightBrother->rightBrother;
			TreeNode *p9 = p7->rightBrother->rightBrother;
			loopNum++;
			doOptExp(p3);
			doExp(p5);
			doOptExp(p7);
			doStmt(p9);
			loopNum--;
			   }
	}
}

varElement* doDefList(TreeNode *p, int ifStruct) {
	//printf("doDefList\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			varElement *ele1 = doDef(p1, ifStruct);
			varElement *ele2 = doDefList(p2, ifStruct);
			if (ifStruct == 1) { 	//是结构体的成员处理
				while (ele1->next != NULL) {	//找到这个Def定义出的的最后一个varElement
					ele1 = ele1->next;				
				}
				ele1->next = ele2;	//和DefList的varElement链串联起来，返回
				return ele1;
			}
			break;
		}
		case 2:{
			return NULL;
			break;
		}
	}
}

varElement* doDef(TreeNode *p, int ifStruct) {
	//printf("doDef\n");
	//printf("TreeNode->state:%s\n", p->state);
	//将doDecList()返回的变量链表赋为doSpecifier()返回的Type,插入变量表
	TreeNode *p1 = p->firstChild;
	TreeNode *p2 = p1->rightBrother;
	Type type = doSpecifier(p1);
	//printf("doDef begin doDecList\n");
	varElement *elem = doDecList(p2);
	varElement *elemHead = elem;
	varElement *elemn = NULL;
	//判断初始化时类型是否匹配
	//printf("type:%d\n", type->u.basic);
//	printf("elem:%d\n", elem->type->u.basic);

	if(elem->initType != NULL) {
		//initType不为空，说明声明的同时初始化，需要判断类型是否匹配
		if (ifStruct == 1) {
			printf("Error type 15 at line %d: struct member initialization is denied\n", p->line);
		} 
		else if(!type_equal(type, elem->initType)) {
			printf("Error type 7 at line %d:'=' type mismatch\n", p->line);
		}
	}
	//printf("z\n");
	while(elem != NULL) {
		//printf("z2\n");
		Type t = elem->type;
		if (t->kind != BASIC) {
			//printf("z3\n");
			while (t->kind == ARRAY && t->u.array.elem->kind != BASIC) {	//如果是数组要找到最底部的type节点赋为Specifier传回的Type
				//printf("in loop\n");				
				t = t->u.array.elem;				
			}
			//printf("z4\n");
			//free(t->u.array.elem);
			t->u.array.elem = type;	//在倒数第二个节点处改变Type
			//printf("z5\n");
		} else {
			//free(elem->type);
			elem->type = type;
			//printf("type in doDef %d\n", type->u.basic);	
		}
		if (ifStruct != 1) {	//普通变量，插入变量表
			if (search(elem->name) != NULL) {	//查找此层定义不为空，说明变量重复定义
				printf("error type 3 at line %d: variable %s redefined.\n", p->line, elem->name);
				elem = elem->next;
			} else {
				elemn = elem->next;
				insert(elem);
				elem = elemn;
			}
		} else {	//结构体变量，保持链表结构
			elem = elem->next;
		}
	}
	//printf("out of doDef\n");
	return elemHead;
}

varElement* doDecList(TreeNode *p) {
	//printf("doDecList\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	//这个函数会把同一语句中出现的变量串起来
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			varElement *elem1 = doDec(p1);
			return elem1;
			break;
			   }
		case 2:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			varElement *elem1 = doDec(p1);
			varElement *elem2 = doDecList(p3);
			elem1->next = elem2;
			return elem1;
			break;
			   }
	}
}

varElement* doDec(TreeNode *p) {
	//printf("doDec\n");
	//printf("TreeNode->production rule: %d\n", p->productionRule);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			//printf("before doDec1\n");
			varElement *elem1 = doVarDec(p1);
			//printf("after doDec1\n");
			return elem1; 
			break;
		}
		case 2:	{
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			//printf("p1->state:%s\n", p1->state);
			//printf("p3->state:%s\n", p3->state);
			//printf("before doDec\n");
			varElement *elem1 = doVarDec(p1);//产生一个结点
			//判断初始化时类型是否匹配
			Type t3 = doExp(p3);
			elem1->initType = t3;
			//将初始化时等号后面的变量类型赋给这个结点的initType;
			fprintf(out_fp, "\tlw, $t0, 0($sp)\n");
			fprintf(out_fp, "\tsw, $t0, %d($sp)\n", elem1->addr_sp - ADDR);
			return elem1;
			break;
		}
	}
	return NULL;
}

Type doOptExp(TreeNode *p) {
	//printf("doOptExp\n");
	switch(p->productionRule) {
		case 1: {
			TreeNode *p1 = p->firstChild;
			return(doExp(p1));
			}	
		case 2: {
			break;
			return NULL;	//还不确定返回NULL正不正确
			}
	}
}

Type doExp(TreeNode *p) {
//	printf("doExp\n");
//	printf("TreeNode->state:%s\n", p->state);
//	printf("TreeNode->productionRule: %d\n", p->productionRule);
	if(strcmp(p->state, "Exp") == 0) {
		TreeNode *tempNode = p->firstChild;//产生式右边第一个符号
		switch (p->productionRule) {
			case 1:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   //Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);	
				   if (tempNode->productionRule > 16 || tempNode->productionRule < 14) {	//不符合唯一的三个能当右值的产生式
					   printf("Error type 6 at line %d: left expression illegal for assign\n", p->line);
				   }
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
//						   printf("Exp ASSIGNOP Exp\n");
//						   printf("tempNode->firstChild->addr_sp: %d\n", tempNode->firstChild->addr_sp);
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", temp2Node->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tsw $t0, %d($sp)\n", tempNode->firstChild->addr_sp - ADDR);
						   return t1;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '=' type mismatch\n", p->line);//类型不匹配
						   OUT = false;//表示语义分析错误，删除已生成的目标文件
					   }
				   }
				break;
				   //exp = exp
				   }
			case 2:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;
						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;//将表达式结果存在该地址处
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp);
						   fprintf(out_fp, "\tand $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '&&' type mismatch\n", p->line);//类型不匹配
						   OUT = false;
					   }
				   }
				break;
				//Exp AND Exp
				   }
			case 3:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;
						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;//将表达式结果存在该地址处
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp);
						   fprintf(out_fp, "\tor $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '||' type mismatch\n", p->line);//类型不匹配
						   OUT = false;
					   }
				   }
				break;
				//Exp OR Exp
				   }
			case 4:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d 'RELOP' type mismatch\n", p->line);//类型不匹配
					   }
				   }
				break;
				//Exp RELOP Exp
				   }
			case 5:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;
//						   printf("t1->u.basic: %d\n", t1->u.basic);
						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tadd $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '+' type mismatch\n", p->line);//类型不匹配
						   OUT = false;
					   }
				   }
				break;
				//Exp PLUS Exp
				   }
			case 6:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;

						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tsub $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
		
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '-' type mismatch\n", p->line);//类型不匹配
					   }
				   }
				break;
				//Exp MINUS Exp
				   }
			case 7:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;

						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tmul $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '*' type mismatch\n", p->line);//类型不匹配
					   }
				   }
				break;
				//Exp STAR Exp
				   }
			case 8:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;
						   ADDR -= 4;
						   p->firstChild->addr_sp = ADDR;
						   fprintf(out_fp, "\taddi $sp, $sp, -4\n");
						   fprintf(out_fp, "\tlw $t0, %d($sp)\n", tempNode->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tlw $t1, %d($sp)\n", temp2Node->firstChild->addr_sp - ADDR);
						   fprintf(out_fp, "\tdiv $t0, $t0, $t1\n");
						   fprintf(out_fp, "\tsw $t0, 0($sp)\n"); 
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 7 at line %d '/' type mismatch\n", p->line);//类型不匹配
					   }
				   }
				break;
				//Exp DIV Exp
				   }
			case 9:return doExp(tempNode->rightBrother);
				   //LP Exp RP
			case 10:return doExp(tempNode->rightBrother);
					//MINUS Exp
			case 11:return doExp(tempNode->rightBrother);
					//NOT Exp
				
			case 12:{funcTableElement *func = searchFunc(tempNode->value.idValue);
					if(func == NULL) {
						varElement *var = searchAll(tempNode->value.idValue);
						if (var != NULL) {
							printf("Error type 11 at line %d: normal variable %s uses '()'\n", p->line, tempNode->value.idValue);
						} else
							printf("Error type 4 at line %d: undefined function %s\n", p->line, tempNode->value.idValue);
						return NULL;
					}
					TreeNode *argNode = tempNode->rightBrother->rightBrother;
					argElement *args = doArgs(argNode);
					if (compareArgs(func->argListHeader, args) == 0) {	//参数匹配有问题
						printf("Error type 9 at line %d: function var list not matched %s\n", p->line, tempNode->value.idValue);
						return func->type;
					}
					break;
					//ID LP Args RP
				}
			case 13:{funcTableElement *func = searchFunc(tempNode->value.idValue);
					if(func == NULL) {
						varElement *var = searchAll(tempNode->value.idValue);
						if (var != NULL) {
							printf("Error type 11 at line %d: normal variable %s uses '()'\n", p->line, tempNode->value.idValue);
							OUT = false;
						} else {
							printf("Error type 4 at line %d:undefined function %s\n", p->line, tempNode->value.idValue);
							OUT = false;
						}
						return NULL;
					}
					else if (func->argListHeader != NULL) {	//函数定义中有参数而调用没有
						printf("Error type 9 at line %d:function var list not matched %s\n", p->line, tempNode->value.idValue);
						OUT = false;
						return func->type;
					}
					break;
					//ID LP RP
				}
			case 14:{Type type = (Type)malloc(sizeof(struct Type_));
					TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
					Type t1 = doExp(tempNode);
					Type t2 = doExp(temp2Node);
					if(tempNode != NULL && temp2Node != NULL) {
						if(t1->kind != ARRAY) {
							printf("Error type 10 at line %d: normal variable uses '[]'\n", p->line);
							OUT = false;
						}
						else if(t2->u.basic != 0) {
							printf("Error type 12 at line %d:int required\n", p->line);
							OUT = false;
						}
						else {
							type = doExp(tempNode)->u.array.elem;
//							printf("tempNode->firstChild->addr_sp: %d\n", tempNode->firstChild->addr_sp);
							tempNode->addr_sp = tempNode->firstChild->addr_sp - temp2Node->firstChild->value.intValue * 4;
							return type;
						}
					}
					break;
					//Exp LB Exp RB
					}
			case 15:{
					TreeNode *p3 = tempNode->rightBrother->rightBrother;
					Type t = doExp(tempNode);
					if(t != NULL) {
						if(t->kind != STRUCTURE) {
							printf("Error type 13 at line %d: error use of operator '.'\n", p->line);
						}
						else {
							//showStructMember(t);
;							varElement *field = t->u.var;
							while(field != NULL) {
								if(strcmp(field->name, p3->value.idValue) == 0) {
									return field->type;
								}
								field = field->next;
							}
							printf("Error type 14 at line %d:struct member %s undefined\n", p->line, tempNode->rightBrother->rightBrother->value.idValue);
							//结构体成员未定义
						}
					}
					break;
					//Exp DOT ID
					}
			case 16:{Type type = (Type)malloc(sizeof(struct Type_));
					varElement *id = searchAll(tempNode->value.idValue);
					//在符号表中寻找是否定义
					if(id == NULL) {
						printf("Error type 1 at line %d:undefined variable %s\n", p->line, tempNode->value.idValue);
						OUT = false;
					}
					else {
						type = id->type;
						tempNode->addr_sp = id->addr_sp;
						printf("tempNode->addr_sp: %d\n", id->addr_sp);
						return type;
					}
					break;
				//ID
					}
			case 17:{Type type = (Type)malloc(sizeof(struct Type_));
					type->kind = BASIC;
					type->u.basic = 0;
					ADDR -= 4;
					tempNode->addr_sp = ADDR;
					fprintf(out_fp, "\taddi $sp, $sp, -4\n");
					fprintf(out_fp, "\tli $t0, %d\n", tempNode->value.intValue);
					fprintf(out_fp, "\tsw $t0, 0($sp)\n");
					return type;
					//INT
					}
			case 18:{Type type = (Type)malloc(sizeof(struct Type_));
					type->kind = BASIC;
					type->u.basic = 1;
					ADDR -= 4;
					tempNode->addr_sp = ADDR;
					fprintf(out_fp, "\taddi $sp, $sp, -4\n");
					fprintf(out_fp, "\tli $t0, %f\n", tempNode->value.floatValue);
					fprintf(out_fp, "\tsw $t0, 0($sp)\n");
					return type;
					//FLOAT
					}
		}
	}
	return NULL;
}

argElement *doArgs(TreeNode *p) {
	//printf("doArgs\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1: {
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			argElement *arg1 = (argElement *)malloc(sizeof(argElement));
			arg1->type = doExp(p1);
			argElement *arg2 = doArgs(p3);
			arg1->next = arg2;
			return arg1;
			break;
			}
		case 2: {
			TreeNode *p1 = p->firstChild;
			argElement *arg1 = (argElement *)malloc(sizeof(argElement));
			arg1->type = doExp(p1);
			arg1->next = NULL;
			//if (arg1 == NULL) printf("wow...\n");
			return arg1;
			break;
			}
	}
}

int compareArgs (argElement *arg1, argElement *arg2) {
	argElement *p1 = arg1; 
	argElement *p2 = arg2;
	while (p1 != NULL) {
		//printf("p1 %d\n", p1->type->u.basic);
		//printf("p2 %d\n", p2->type->u.basic);
		if (p2 == NULL)
			return 0;
		if (!type_equal(p1->type, p2->type))
			return 0;
		p1 = p1->next;
		p2 = p2->next;		
	}
	if (p2 != NULL)
		return 0;
	return 1;
}


