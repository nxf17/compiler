#ifndef SEMANTICS_H
#define SEMANTICS_H

#include"symboltable.h"

extern void doProgram(TreeNode *p);
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
extern Type doExp(TreeNode *p);

#endif

