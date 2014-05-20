%option yylineno
%{

#include "syntax.tab.h"

extern float installFLOAT();
/*	int yycolumn = 1;
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; yycolumn += yyleng;
*/

/*
#define INT 1
#define FLOAT 2
#define ID 3

#define SEMI 101
#define COMMA 102
#define ASSIGNOP 103
#define RELOP 104
#define PLUS 105
#define MINUS 106
#define STAR 107
#define DIV 108
#define AND 109
#define OR 110
#define DOT 111
#define NOT 112
#define TYPE 113
#define LP 114
#define RP 115
#define LB 116
#define RB 117
#define LC 118
#define RC 119

#define STRUCT 200
#define RETURN 201
#define IF 202
#define ELSE 203
#define WHILE 204
*/
%}

/*regular definitions*/
TYPE int|float
ID [a-zA-Z_][a-zA-Z_0-9]*
delim [ \t\n]
ws {delim}+
int 0|([1-9][0-9]*)
oct_int 0(0|([1-7][0-7]*))
hex_int (0x|0X)(0|[1-9A-Fa-f][0-9A-Fa-f]*)
float [0-9]*(\.[0-9]+)?
efloat ((0|[1-9][0-9]*)\.[0-9]+)(E|e)-?[0-9]+
letter [A-Za-z]
digit [0-9]
id [a-zA-Z_][a-zA-Z_0-9]*
note1 \/\/.*\n
note2 \/\*(.*\n?)*\*\/

%%
if {//printf("IF\n"); 
	yylval.state = "IF"; yylval.line = yylineno;
	return(IF);}
else {//printf("ELSE\n"); 
	yylval.state = "ELSE"; yylval.line = yylineno;
	return(ELSE);}
return {//printf("RETURN\n"); 
	yylval.state = "RETURN"; yylval.line = yylineno;
	return(RETURN);}
while {//printf("WHILE\n"); 
	yylval.state = "WHILE"; yylval.line = yylineno;
	return(WHILE);}
struct {//printf("STRUCT\n"); 
	yylval.state = "STRUCT"; yylval.line = yylineno;
	return(STRUCT);}
int {//printf("TYPE:%s\n", yytext); 
	char *temp = (char *)malloc(sizeof(char) * yyleng);
	strcpy(temp, yytext);
	yylval.state = "TYPE:int"; yylval.line = yylineno;
	yylval.value.idValue=temp;
	return(TYPE);}
float {//printf("TYPE:%s\n", yytext); 
	char *temp = (char *)malloc(sizeof(char) * yyleng);
	strcpy(temp, yytext);
	yylval.state = "TYPE:float"; yylval.line = yylineno;
	yylval.value.idValue=temp;
	return(TYPE);}

{id} {char *temp = (char *)malloc(sizeof(char) * yyleng);
	strcpy(temp, yytext);
	yylval.value.idValue = temp;
	yylval.state = "ID"; yylval.line = yylineno;
	//printf("ID:%s\n", yytext); 
	return ID;}

{int} {yylval.value.intValue = installINT(); 
	yylval.state = "INT"; yylval.line = yylineno;
	//printf("INT:%s\n", yytext); 
	return INT;}
{oct_int} {yylval.value.intValue = installINT(); 
	yylval.state = "INT"; yylval.line = yylineno;
	//printf("OCTAL INT:%s\n", yytext); 
	return INT;}
{hex_int} {yylval.value.intValue = installINT(); 
	yylval.state = "INT"; yylval.line = yylineno;
	//printf("HEXADECIMAL INT:%s\n", yytext); 
	return INT;}
{float} {yylval.value.floatValue = installFLOAT(); 
	yylval.state = "FLOAT"; yylval.line = yylineno;
	//printf("FLOAT:%s\n", yytext); 
	return FLOAT;}
{efloat} {yylval.value.floatValue = installFLOAT();
	yylval.state = "FLOAT"; yylval.line = yylineno;
	//printf("EFLOAT:%s\n", yytext); 
	return FLOAT;}
"<" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
"<=" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
"==" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
"<>" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
">" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
">=" {yylval.state = "RELOP";
	yylval.line = yylineno;
	//printf("RELOP:%s\n", yytext); 
	return(RELOP);}
";" {yylval.state = "SEMI";
	yylval.line = yylineno;
	//printf("SEMI:%s\n", yytext); 
	return(SEMI);}
"," {yylval.state = "COMMA";
	yylval.line = yylineno;
	//printf("COMMA:%s\n", yytext); 
	return(COMMA);}
\+ {yylval.state = "PLUS";
	yylval.line = yylineno;
	//printf("PLUS:%s\n", yytext); 
	return(PLUS);}
\- {yylval.state = "MINUS";
	yylval.line = yylineno;
	//printf("MINUS:%s\n", yytext); 
	return(MINUS);}
\* {yylval.state = "STAR";
	yylval.line = yylineno;
	//printf("STAR:%s\n", yytext); 
	return(STAR);}
\/ {yylval.state = "DIV";
	yylval.line = yylineno;
	//printf("DIV:%s\n", yytext); 
	return(DIV);}
"&&" {yylval.state = "AND";
	yylval.line = yylineno;
	//printf("AND:%s\n", yytext); 
	return(AND);}
"||" {yylval.state = "OR";
	yylval.line = yylineno;
	//printf("OR:%s\n", yytext); 
	return(OR);}
"." {yylval.state = "DOT";
	yylval.line = yylineno;
	//printf("DOT:%s\n", yytext); 
	return(DOT);}
"!" {yylval.state = "NOT";
	yylval.line = yylineno;
	//printf("NOT:%s\n", yytext); 
	return(NOT);}
"(" {yylval.state = "LP";
	yylval.line = yylineno;
	//printf("LP:%s\n", yytext); 
	return(LP);}
")" {yylval.state = "RP";
	yylval.line = yylineno;
	//printf("RP:%s\n", yytext); 
	return(RP);}
"[" {yylval.state = "LB";
	yylval.line = yylineno;
	//printf("LB:%s\n", yytext); 
	return(LB);}
"]" {yylval.state = "RB";
	yylval.line = yylineno;
	//printf("RB:%s\n", yytext); 
	return(RB);}
"{" {yylval.state = "LC";
	yylval.line = yylineno;
	//printf("LC:%s\n", yytext); 
	return(LC);}
"}" {yylval.state = "RC";
	yylval.line = yylineno;
	//printf("RC:%s\n", yytext); 
	return(RC);}
"=" {yylval.state = "ASSIGNOP";
	yylval.line = yylineno;
	//printf("ASSIGNOP:%s\n", yytext); 
	return(ASSIGNOP);}
{note1} {}
{note2} {}
"\t" {//yycolumn += 4;
}
" "  {//yycolumn++;
}
"\n" {//yycolumn = 1;
}
. {printf("error type 1 at line %d, unknown word \'%s\'\n", yylineno, yytext);
}


%%
int installID() {
	//char *s="";
	//char *temp=(char*)malloc(sizeof(char*)*(yyleng+strlen(s)+1));
	//temp=strcpy(temp,s);
	//temp=strncat(temp,yytext,yyleng);
	//	return temp;
	return atoi(yytext);
}

int installINT() {

	/*int sum = 0, num = yyleng;
	char *p = yytext;
	for(; num > 0; num--) {
		printf("----------%d\n", (int)((*p))&0x0f);
		sum += (int)((*p)&0x0f) * pow(10, num-1);
		p++;
	}
	printf("sum:%d\n", sum);
	return sum;*/
	return atoi(yytext);
}

float installFLOAT() {
	return atof(yytext);
}


