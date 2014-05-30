#ifndef SEMANTICS_H
#define SEMANTICS_H

#include"symboltable.h"

extern void doProgram(TreeNode *p);
extern void doExtDefList(TreeNode *p);
extern void doExtDef(TreeNode *p);
extern varElement* doExtDecList(TreeNode *p);
extern Type doSpecifier(TreeNode *p);
extern Type doStructSpecifier(TreeNode *p);
extern char* doOptTag(TreeNode *p);
extern char* doTag(TreeNode *p);
extern varElement* doVarDec(TreeNode *p);
extern void doFunDec(Type type, TreeNode *p);
extern argElement* doVarList(TreeNode *p);
extern argElement* doParamDec(TreeNode *p);
extern void doCompSt(TreeNode *p);
extern void doStmtList(TreeNode *p);
extern void doStmt(TreeNode *p);
extern varElement* doDefList(TreeNode *p, int ifStruct);	//ifStruct这个参数表示是否在处理struct的成员
extern varElement* doDef(TreeNode *p, int ifStruct);
extern varElement* doDecList(TreeNode *p);
extern varElement* doDec(TreeNode *p);
extern Type doExp(TreeNode *p);
extern Type doOptExp(TreeNode *p);
extern argElement* doArgs(TreeNode *p);
extern int compareArgs(argElement *arg1, argElement *arg2);

#endif

