%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include"tree.h"

	#define YYSTYPE struct TreeNode
	
	#define STACKMAX 100

	struct TreeNode *root = NULL;
	
	//节点栈
	struct TreeNode *NodeStack[STACKMAX];
	static int stackTop = -1;
	
	//栈操作
	void push(TreeNode *node) {
		if (stackTop == STACKMAX-1) {
			printf("stack overflow!\n");
			return;
		}
		stackTop++;
		NodeStack[stackTop] = node;
	}

	TreeNode *pop() {
		if (stackTop == -1) {
			printf("Nothing to pop out in stack!\n");
			return;
		}
		TreeNode *p = NodeStack[stackTop];
		stackTop--;
		return p;
	}

	void Traverse(TreeNode *subtree, int depth) {
		if(subtree != NULL) {
		//	if(subtree->state != "empty") {
				int i = 0;
				for(; i < depth; i++)
					printf(" ");//缩进
				printf("%s ", subtree->state);
			//	printf("line:%d ", subtree->line);
				if(subtree->state == "INT")
					printf("%d ", subtree->value.intValue);
				else if(subtree->state == "FLOAT")
					printf("%f ", subtree->value.floatValue);
				else if(subtree->state == "ID")
					printf("%s ", subtree->value.idValue);

		//	}
			printf("(%d)\n",subtree->line);
			//printf("\n");
			depth++;
			Traverse(subtree->firstChild, depth);
			depth--;
			Traverse(subtree->rightBrother, depth);
			//printf("-----doProgram-----\n");
			//doProgram(root);
		}
	}


%}

%token INT 
%token FLOAT 
%token ID
%token SEMI COMMA
%token ASSIGNOP RELOP
%token PLUS MINUS STAR DIV
%token AND OR NOT
%token DOT
%token TYPE
%token LP RP LB RB LC RC
%token STRUCT
%token RETURN IF ELSE WHILE
%token FOR BREAK CONTINUE

%left ASSIGNOP RELOP
%left OR
%left AND
%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT
%left RC LC
%left LB RB
%left LP RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program	:	
	ExtDefList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "Program";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = p1->rightBrother = NULL;
		root = p;
		Traverse(root, 0);
		printf("-----semantic analysis-----\n");
		doProgram(root);
	}
;
ExtDefList :								
    {//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);						
	}		
	|ExtDef ExtDefList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDefList";
		p->line = p1->line;
		p->firstChild = p1;
		p1->rightBrother = p2;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
;
ExtDef :	
	Specifier ExtDecList SEMI {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->rightBrother = p3;
		p3->state = $3.state;
		p3->line = $3.line;
		p3->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
	|Specifier SEMI {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->rightBrother = NULL;
		p->productionRule = 2;
		push(p);		
	}
	|Specifier FunDec CompSt {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ExtDef";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->rightBrother = p3;
		p->productionRule = 3;
		push(p);		
	}
;
ExtDecList :	
	VarDec {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = pop();
		p->state = "ExtDecList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);			
	}
	|VarDec COMMA ExtDecList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "ExtDecList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p->productionRule = 2;
		push(p);		
	}
;
Specifier :	
	TYPE {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->value = $1.value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "Specifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
	|StructSpecifier {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = pop();
		p->state = "Specifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
//		p1->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
;
StructSpecifier : 
	STRUCT OptTag LC DefList RC {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p5 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p4 = pop();
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = pop();
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "StructSpecifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->rightBrother = p3;
		p3->state = $3.state;
		p3->line = $3.line;
		p3->firstChild = NULL;
		p3->rightBrother = p4;
		p4->rightBrother = p5;
		p5->state = $5.state;
		p5->line = $5.line;
		p5->firstChild = NULL;
		p5->rightBrother = NULL;
		p->productionRule = 1;
		push(p);					
	}
	|STRUCT Tag {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "StructSpecifier";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);					
	}
;
OptTag : 
	{//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);			
	}
	|ID {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->value = $1.value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "OptTag";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);					
	}
;
Tag :
	ID {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->value = $1.value;
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "Tag";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
;
VarDec : 
	ID {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		//printf("%s\n", $1.value.idValue);
		p1->value = $1.value;
		printf("%s\n", p1->value.idValue);
		p1->firstChild = p1->rightBrother = NULL;
		p->state = "VarDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
	|VarDec LB INT RB {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p4 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->state = $3.state;
		p3->line = $3.line;
		p3->value = $3.value;
		p3->firstChild = NULL;
		p3->rightBrother = p4;
		p4->state = $4.state;
		p4->line = $4.line;
		p4->firstChild = p4->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
;
FunDec : 
	ID LP VarList RP {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p4 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->value = $1.value;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "FunDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->rightBrother = p4;
		p4->state = $4.state;
		p4->line = $4.line;
		p4->firstChild = p4->rightBrother = NULL;		
		p->productionRule = 1;
		push(p);			 
	}
   	|ID LP RP {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = (TreeNode *)malloc(sizeof(TreeNode));
		p1->state = $1.state;
		p1->line = $1.line;
		p1->value = $1.value;
		p1->firstChild = NULL;
		p1->rightBrother = p2;
		p->state = "FunDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p3->state = $3.state;
		p3->line = $3.line;
		p3->firstChild = p3->rightBrother = NULL;
		p->productionRule = 2;
		push(p);					
	}
;
VarList	: 
	ParamDec COMMA VarList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p3 = pop();
		TreeNode *p2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		p2->state = $2.state;
		p2->line = $2.line;
		p2->firstChild = NULL;
		p2->rightBrother = p3;
		p->productionRule = 1;
		push(p);	
	}
	|ParamDec {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *p1 = pop();
		p->state = "VarList";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);
	}
;
ParamDec :  
	Specifier VarDec {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *p2 = pop();
		TreeNode *p1 = pop();
		p->state = "ParamDec";
		p->line = p1->line;
		p->firstChild = p1;
		p->rightBrother = NULL;
		p1->rightBrother = p2;
		//p2->rightBrother = NULL;?不需要吗
		p->productionRule = 1;
		push(p);	
	}
;
CompSt : LC DefList StmtList RC	{
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmtlist = pop();
		TreeNode *deflist = pop();
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		op1->state = $1.state;
		op1->line = $1.line;
		op1->rightBrother = deflist;
		deflist->rightBrother = stmtlist;
		stmtlist->rightBrother = op2;
		op2->state = $4.state;
		op2->line = $4.line;
		op2->rightBrother = p->rightBrother = NULL;
		p->firstChild = op1;
		p->state = "CompSt";
		p->line = op1->line;
		
		p->productionRule = 1;
		push(p);	
	}
;
StmtList : 
	Stmt StmtList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *stmtlist = pop();
		TreeNode *stmt = pop();
		p->state = "StmtList";
		p->line = stmt->line;
		p->firstChild = stmt;
		p->rightBrother = stmtlist->rightBrother = NULL;
		stmt->rightBrother = stmtlist;
		p->productionRule = 1;
		push(p);	
	}
	|{
		//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;
		p->productionRule = 2;
		push(p);	
	}
;
Stmt : 
	Exp SEMI {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *exp = pop();
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Stmt";
		p->line = exp->line;
		p->firstChild = exp;
		p->rightBrother = semi->rightBrother = NULL;
		exp->rightBrother = semi;
		semi->state = $2.state;
		semi->line = $2.line;

		p->productionRule = 1;
		push(p);	
	}
	|CompSt	{
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *compst = pop();
		p->state = "Stmt";
		p->line = compst->line;
		p->firstChild = compst;
		p->rightBrother = compst->rightBrother = NULL;

		p->productionRule = 2;
		push(p);				
	}
	|RETURN Exp SEMI {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *re = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		re->line = $1.line;
		re->state = $1.state;
		re->rightBrother = exp;
		exp->rightBrother = semi;
		semi->line = $3.line;
		semi->state = $3.state;
		semi->rightBrother = p->rightBrother = NULL;
		p->firstChild = re;
		p->line = re->line;
		p->state = "Stmt";

		p->productionRule = 3;
		push(p);				
	}
	|IF LP Exp RP Stmt {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *IF = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		IF->state = $1.state;
		IF->line = $1.line;
		IF->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->line = $4.line;
		op2->state = $4.state;
		op2->rightBrother = stmt;
		stmt->rightBrother = p->rightBrother = NULL;
		p->line = IF->line;
		p->state = "Stmt";
		p->firstChild = IF;

		p->productionRule = 4;
		push(p);				
	}
	|IF LP Exp RP Stmt ELSE Stmt {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *IF = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *ELSE = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt2 = pop();
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		IF->state = $1.state;
		IF->line = $1.line;
		IF->firstChild = NULL;
		IF->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->firstChild = NULL;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->state = $4.state;
		op2->line = $4.line;
		op2->firstChild = NULL;
		op2->rightBrother = stmt;
		stmt->rightBrother = ELSE;
		ELSE->state = $6.state;
		ELSE->line = $6.line;
		ELSE->firstChild = NULL;
		ELSE->rightBrother = stmt2;
		stmt2->rightBrother = p->rightBrother = NULL;
		p->state = "Stmt";
		p->line = IF->line;
		p->firstChild = IF;

		p->productionRule = 5;
		push(p);				
	}
	|WHILE LP Exp RP Stmt {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *WHILE = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *stmt = pop();
		TreeNode *exp = pop();
		WHILE->state = $1.state;
		WHILE->line = $1.line;
		WHILE->firstChild = NULL;
		WHILE->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->firstChild = NULL;
		op1->rightBrother = exp;
		exp->rightBrother = op2;
		op2->state = $4.state;
		op2->line = $4.line;
		op2->firstChild = NULL;
		op2->rightBrother = stmt;
		stmt->rightBrother = p->rightBrother = NULL;
		p->state = "Stmt";
		p->line = WHILE->line;
		p->firstChild = WHILE;

		p->productionRule = 6;
		push(p);				
	}
;
DefList	: 
	Def DefList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *deflist = pop();
		TreeNode *def = pop();
		p->state = "DefList";
		p->line = def->line;
		p->firstChild = def;
		p->rightBrother = deflist->rightBrother = NULL;
		def->rightBrother = deflist;

		p->productionRule = 1;
		push(p);	
	}
	| {
		//empty
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "empty";
		p->firstChild = p->rightBrother = NULL;

		p->productionRule = 2;
		push(p);				
	}
;
Def : 
	Specifier DecList SEMI {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *semi = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *declist = pop();
		TreeNode *specifier = pop();
		p->state = "Def";
		p->line = specifier->line;
		p->firstChild = specifier;
		p->rightBrother = semi->rightBrother = NULL;
		specifier->rightBrother = declist;
		declist->rightBrother = semi;
		semi->line = $3.line;
		semi->state = $3.state;
		semi->firstChild = NULL;
		p->productionRule = 1;
		push(p);	
	}
;
DecList	: 
	Dec {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *dec = pop();
		p->state = "DecList";
		p->line = dec->line;
		p->firstChild = dec;
		p->rightBrother = dec->rightBrother = NULL;

		p->productionRule = 1;
		push(p);	
	}
	| Dec COMMA DecList {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *comma = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *declist = pop();
		TreeNode *dec = pop();
		p->state = "DecList";
		p->line = dec->line;
		p->firstChild = dec;
		p->rightBrother = declist->rightBrother = NULL;
		dec->rightBrother = comma;
		comma->line = $2.line;
		comma->state = $2.state;
		comma->firstChild = NULL;
		comma->rightBrother = declist;
		
		p->productionRule = 2;
		push(p);	
	}
;
Dec : 
	VarDec {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *vardec = pop();
		p->state =  "Dec";
		p->line = vardec->line;
		p->firstChild = vardec;
		vardec->rightBrother = p->rightBrother = NULL;

		p->productionRule = 1;
		push(p);	
	}
	| VarDec ASSIGNOP Exp {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		//TreeNode *vardec = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		TreeNode *vardec = pop();
		vardec->rightBrother = op;
		op->state = $2.state;
		op->line = $2.line;
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->state = "Dec";
		p->line = vardec->line;
		p->firstChild = vardec;

		p->productionRule = 2;
		push(p);				
	}
;
Exp : 
	Exp ASSIGNOP Exp {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		p->productionRule = 1;
		push(p);	
	}
	|Exp AND Exp {	
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 2;
		push(p);		
	}
	|Exp OR Exp {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 3;
		push(p);	
	}
	|Exp RELOP Exp {	
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		
		p->productionRule = 4;
		push(p);	
	}
	|Exp PLUS Exp {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->state = "Exp";
		p->firstChild = exp1;
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;
		p->productionRule = 5;

		push(p);	
	}
	|Exp MINUS Exp {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 6;
		push(p);	
	}
	|Exp STAR Exp {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 7;
		push(p);	
	}
	|Exp DIV Exp {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		
		p->productionRule = 8;
		push(p);	
	}
	|LP Exp RP {
		
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;
		p->state = "Exp";
		exp1->rightBrother = op;
		op->rightBrother = exp2;
		p->rightBrother = exp2->rightBrother = NULL;

		p->productionRule = 9;
		push(p);	
	}
	|MINUS Exp {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = op;
		p->state = "Exp";
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->productionRule = 10;
		push(p);	
	}
	|NOT Exp {
			
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		op->state = $2.state;
		op->line = $2.line;
		op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = op;
		p->state = "Exp";
		op->rightBrother = exp;
		exp->rightBrother = p->rightBrother = NULL;
		p->productionRule = 11;
		push(p);	
	}
	|ID LP Args RP {

		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Exp";
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *args = pop();
		id->state = $1.state;
		id->line = $1.line;
		id->value = $1.value;
		id->firstChild = op1->firstChild = op2->firstChild = NULL;
		id->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->rightBrother = args;
		args->rightBrother = op2;
		op2->state = $4.state;
		op2->line = $4.line;
		p->rightBrother = op2->rightBrother = NULL;
		p->firstChild = id;
		p->line = id->line;
		p->productionRule = 12;
		push(p);		
	}
	|ID LP RP {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		id->state = $1.state;
		id->line = $1.line;
		id->value = $1.value;
		id->firstChild = op1->firstChild = op2->firstChild = NULL;
		id->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->rightBrother = op2;
		op2->state = $2.state;
		op2->line = $2.line;
		op2->rightBrother = p->rightBrother = NULL;
		p->firstChild = id;
		p->line = id->line;

		p->productionRule = 13;
		push(p);	
	}
	|Exp LB Exp RB {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *exp2 = pop();
		TreeNode *exp1 = pop();
		TreeNode *op1 = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *op2 = (TreeNode *)malloc(sizeof(TreeNode));
		exp1->rightBrother = op1;
		op1->state = $2.state;
		op1->line = $2.line;
		op1->rightBrother = exp2;
		exp2->rightBrother = op2;
		op2->state = $4.state;
		op2->line = $4.line;
		op2->rightBrother = p->rightBrother = NULL;
		op2->firstChild = op1->firstChild = NULL;
		p->line = exp1->line;
		p->firstChild = exp1;

		p->productionRule = 14;
		push(p);	
	}
	|Exp DOT ID {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		p->state = "Exp";
		TreeNode *exp = pop();
		TreeNode *op = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *id = (TreeNode *)malloc(sizeof(TreeNode));
		exp->rightBrother = op;
		op->state = $2.state;
		op->line = $2.line;
		op->rightBrother = id;
		id->state = $3.state;
		id->line = $3.line;
		id->value = $3.value;
		id->rightBrother = p->rightBrother = NULL;
		id->firstChild = op->firstChild = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		
		p->productionRule = 15;
		push(p);	
	}
	|ID {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = $1.value;
		temp->state = $1.state;
		temp->line = $1.line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 16;
		push(p);	
	}
	|INT {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = $1.value;
		temp->state = $1.state;
		temp->line = $1.line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 17;
		push(p);
	}
	|FLOAT {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));	
		TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
		temp->value = $1.value;
		temp->state = $1.state;
		temp->line = $1.line;
		temp->firstChild = NULL;
		p->state = "Exp";
		p->line = temp->line;
		p->firstChild = temp;
		p->rightBrother = temp->rightBrother = NULL;
		//temp->line = 0;
		p->productionRule = 18;
		push(p);	
	}
;
Args: 
	Exp COMMA Args {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Args";
		TreeNode *args = pop();
		TreeNode *comma = (TreeNode *)malloc(sizeof(TreeNode));
		TreeNode *exp = pop();
		exp->rightBrother = comma;
		comma->state = $2.state;
		comma->line = $2.line;
		comma->rightBrother = args;
		comma->firstChild = NULL;
		args->rightBrother = p->rightBrother = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		
		push(p);
	}
	|Exp {
		TreeNode *p = (TreeNode *)malloc(sizeof(TreeNode));
		p->state = "Args";
		TreeNode *exp = pop();
		exp->rightBrother = p->rightBrother = NULL;
		p->line = exp->line;
		p->firstChild = exp;
		
		push(p);	
	}
;
%%

#include "lex.yy.c"

yyerror(char* msg) {
	printf("Error type 2 at line %d:syntax error near '%s'\n",yylineno,yytext);
}
















