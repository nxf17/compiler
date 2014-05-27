#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "symboltable.h"
#include "semantics.h"

extern bool type_equal(Type x, Type y);
//都先定义成void了，之后肯定要改几个的返回类型
/*extern void doProgram(TreeNode *p);
extern void doExtDefList(TreeNode *p);
extern void doExtDef(TreeNode *p);
extern varElement* doExtDecList(TreeNode *p);
extern Type doSpecifier(TreeNode *p);
extern void doStructSpecifier(TreeNode *p);
extern void doOptTag(TreeNode *p);
extern void doTag(TreeNode *p);
extern varElement* doVarDec(TreeNode *p);
extern void doFunDec(TreeNode *p);
extern void doVarList(TreeNode *p);
extern void doParamDec(TreeNode *p);
extern void doCompSt(TreeNode *p);
extern void doStmtList(TreeNode *p);
extern void doStmt(TreeNode *p);
extern void doDefList(TreeNode *p);
extern void doDef(TreeNode *p);
extern varElement* doDecList(TreeNode *p);
extern varElement* doDec(TreeNode *p);
extern Type doExp(TreeNode *p);*/


void doProgram(TreeNode *p) {
	//printf("---doProgram---\n");
	//printf("root->state:%s\n", p->state);
	TreeNode *p1 = p->firstChild;	
	doExtDefList(p1);
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
		//	printf("here!\n");
			Type type = doSpecifier(p1);
		//	printf("here!\n");
			varElement *elem = doExtDecList(p2);
		//	printf("here!\n");
			varElement *elemn = NULL;
			while (elem != NULL) {
		//		printf("here!\n");
				elem->type = type;	
				elemn = elem->layer_next;
				insert(elem);
				elem = elemn;
			}
			break;
			   }
		case 2:	{//待完成，用于只定义结构体的tag
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
	//printf("TreeNode->state:%s\n", p->state);
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
			elem1->layer_next = elem2;
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
			doStructSpecifier(p1);
			type->kind = STRUCTURE;
			break;
			   }
	}
	return type;
} 

void doStructSpecifier(TreeNode *p) {	//待完成
	//printf("doStructSpecifier\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:
			break;
		case 2:
			break;
	}
}

void doOptTag(TreeNode *p) {	//待完成
	//printf("doOptTag\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:
			break;
		case 2:
			break;
	}
}

void doTag(TreeNode *p) {	//待完成
	//printf("doTag\n");
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
			elem->layer_next = NULL;
			strcpy(elem->name, p1->value.idValue);
			return elem;
			break;
			   }
		case 2:
			//数组声明，待处理
			return NULL;
			break;
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
	doDefList(p2);
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
			TreeNode *p1 = p->firstChild;
			doCompSt(p1);
			break;
			   }
		case 3:	{//这块之后要做函数返回类型检查
			TreeNode *p2 = p->firstChild->rightBrother;
			doExp(p2);
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
			doExp(p3);
			doStmt(p5);
			break;
			   }
		case 7:
			break;
		case 8:
			break;
		case 9:{
			//the for loop,待完善，应该是中间那个要做个type检查。
			TreeNode *p3 = p->firstChild->rightBrother->rightBrother;
			TreeNode *p5 = p3->rightBrother->rightBrother;
			TreeNode *p7 = p5->rightBrother->rightBrother;
			TreeNode *p9 = p7->rightBrother->rightBrother;
			doOptExp(p3);
			doExp(p5);
			doOptExp(p7);
			doStmt(p9);
			   }
	}
}

void doDefList(TreeNode *p) {
	//printf("doDefList\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			TreeNode *p2 = p1->rightBrother;
			doDef(p1);
			doDefList(p2);
			break;
			   }
		case 2:
			break;
	}
}

void doDef(TreeNode *p) {
	//printf("doDef\n");
	//printf("TreeNode->state:%s\n", p->state);
	//将doDecList()返回的变量链表赋为doSpecifier()返回的Type,插入变量表
	TreeNode *p1 = p->firstChild;
	TreeNode *p2 = p1->rightBrother;
	Type type = doSpecifier(p1);
	//printf("doDef begin doDecList\n");
	varElement *elem = doDecList(p2);
	varElement *elemn = NULL;
	//判断初始化时类型是否匹配
	//printf("type:%d\n", type->u.basic);
//	printf("elem:%d\n", elem->type->u.basic);

	if(elem->type != NULL) {
		//type不为空，说明声明的同时初始化，需要判断类型是否匹配
		//printf("here\n");
		if(!type_equal(type, elem->type)) {
			printf("Error type 3 at line %d:'=' type mismatch\n", p->line);
		}
		else {
			while(elem != NULL) {
				elem->type = type;
				elemn = elem->layer_next;
				insert(elem);
				elem = elemn;
			}
		}
	}
	else{
		while (elem != NULL) {
			elem->type = type;	//相当不确定这句指针操作的正确性
			elemn = elem->layer_next;
			insert(elem);
			elem = elemn;
		}
	}
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
			elem1->layer_next = elem2;
			return elem1;
			break;
			   }
	}
}

varElement* doDec(TreeNode *p) {
	//printf("doDec\n");
	//printf("TreeNode->state:%s\n", p->state);
	switch (p->productionRule) {
		case 1:{
			TreeNode *p1 = p->firstChild;
			varElement *elem1 = doVarDec(p1);
			return elem1; 
			break;
			   }
		case 2:	{//先没有处理初始化
			TreeNode *p1 = p->firstChild;
			TreeNode *p3 = p1->rightBrother->rightBrother;
			//printf("p1->state:%s\n", p1->state);
			//printf("p3->state:%s\n", p3->state);
			varElement *elem1 = doVarDec(p1);//产生一个结点
			//判断初始化时类型是否匹配
			Type t3 = doExp(p3);
			elem1->type = t3;
			//将初始化时等号后面的变量类型赋给这个新结点
			return elem1;
			break;
				}
	}
	return NULL;
}

bool type_equal(Type x, Type y) {
	//待完善，之后要扩充成支持所有类型
	if(x->kind == BASIC && y->kind == BASIC) {
		if(x->u.basic == y->u.basic) {
			return true;
		}
	}//int或float类型匹配
	return false;
}//判断类型是否匹配

Type doOptExp(TreeNode *p) {
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
	//printf("doExp\n");
	//printf("TreeNode->state:%s\n", p->state);
	//printf("TreeNode->productionRule: %d\n", p->productionRule);
	if(strcmp(p->state, "Exp") == 0) {
		TreeNode *tempNode = p->firstChild;//产生式右边第一个符号
		switch (p->productionRule) {
			case 1:{TreeNode *temp2Node = tempNode->rightBrother->rightBrother;
				   Type type = (Type)malloc(sizeof(struct Type_));
				   Type t1 = doExp(tempNode);
				   Type t2 = doExp(temp2Node);
				   if(t1 != NULL && t2 != NULL) {
					   if(type_equal(t1, t2)) {
						   type = t1;//？这里不是只赋了地址吗
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '=' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '&&' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '||' type mismatch\n", p->line);//类型不匹配
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
						   printf("Error type 3 at line %d 'RELOP' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '+' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '-' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '*' type mismatch\n", p->line);//类型不匹配
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
						   return type;//类型匹配
					   }
					   else if(!type_equal(t1, t2)) {
						   printf("Error type 3 at line %d '/' type mismatch\n", p->line);//类型不匹配
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
						printf("Error type 4 at line %d:undefined function %s\n", p->line, tempNode->value.idValue);
						return NULL;
					}
					TreeNode *argNode = tempNode->rightBrother->rightBrother;
					argElement *args = doArgs(argNode);
                                        //if (args == NULL) printf("doArgs returns null!\n");
					if (compareArgs(func->argListHeader, args) == 0) {	//参数匹配有问题
						printf("Error type 9 at line %d:function var list not matched %s\n", p->line, tempNode->value.idValue);
						return func->type;
					}
					break;
					//ID LP Args RP
				}
			case 13:{funcTableElement *func = searchFunc(tempNode->value.idValue);
					if(func == NULL) {
						printf("Error type 4 at line %d:undefined function %s\n", p->line, tempNode->value.idValue);
						return NULL;
					}
					else if (func->argListHeader != NULL) {	//函数定义中有参数而调用没有
						printf("Error type 9 at line %d:function var list not matched %s\n", p->line, tempNode->value.idValue);
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
						if(t1->kind != ARRAY)
							printf("Error type 5 at line %d:'[]' unexcepted\n", p->line);
						else if(t2->u.basic != 0)
							printf("Error type 6 at line %d:int required\n", p->line);
						else {
							type = doExp(tempNode)->u.array.elem;
							return type;
						}
					}
					break;
					//Exp LB Exp RB
					}
			case 15:{Type type = (Type)malloc(sizeof(struct Type_));
					Type t = doExp(tempNode);
					FieldList field = t->u.structure;
					if(t != NULL) {
						if(t->kind != STRUCTURE) {
							printf("Error type 7 at line %d:'.'before %s unexpected\n", p->line, tempNode->value.idValue);
						}
						else {
							while(field != NULL) {
								if(strcmp(field->name, tempNode->rightBrother->rightBrother->value.idValue)) {
									type = field->type;
									return type;
								}
								field = field->tail;
							}
							printf("Error type 8 at line %d:struct item %s undefined\n", p->line, tempNode->rightBrother->rightBrother->value.idValue);
							//结构体成员未定义
						}
					}
					break;
					//Exp DOT ID
					}
			case 16:{Type type = (Type)malloc(sizeof(struct Type_));
					varElement *id =searchAll(tempNode->value.idValue);
					//在符号表中寻找是否定义
					if(id == NULL) {
						printf("Error type 4 at line %d:undefined variable %s\n", p->line, tempNode->value.idValue);
					}
					else {
						type = id->type;
						return type;
					}
				break;
				//ID
					}
			case 17:{Type type = (Type)malloc(sizeof(struct Type_));
					type->kind = BASIC;
					type->u.basic = 0;
					return type;
					//INT
					}
			case 18:{Type type = (Type)malloc(sizeof(struct Type_));
					type->kind = BASIC;
					type->u.basic = 1;
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
		printf("p1 %d\n", p1->type->u.basic);
		printf("p2 %d\n", p2->type->u.basic);
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


