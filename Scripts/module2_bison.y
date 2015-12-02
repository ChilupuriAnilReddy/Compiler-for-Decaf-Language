%{
#include <cstdio>
#include <iostream>
#include <list>
#include <stdio.h>
#include "module2_class_declaration.h"
#include "module2_codegen.cpp"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" FILE *yyout;
extern "C" FILE *yyout1;
extern "C" FILE *yyout2;

program_node *root;
list<fielddeclaration*> field;
list<methoddeclaration*> method;

string i = "Int";
string b = "Boolean";
string v = "Void";
 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	char *sval;
	int   ival;
	list<argdeclaration*> * f;
	list<vardeclaration*> * vd;
	list<string> *cd;
	list<statementdeclaration*> *sd;
	list<exprdeclaration*> *eld;
	exprdeclaration *ed;
	numdeclaration *nd;
	chardeclaration *ecd;
	statementdeclaration *ssd;
	block *b;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:

%token  CLASS
%token  CALLOUT
%token INT
%token  BOOLEAN
%token  IF
%token  ELSE
%token  FOR
%token  BREAK
%token  CONTINUE
%token  RETURN
%token  VOID
%token WRONG
%token <sval> ID
%token <ival> NONZERONUM
%token <ival> ZERO
%token <sval> CHARACTER
%token <sval> STRING
%token <sval> TRUE
%token <sval> FALSE
%token  ADD
%token  SUB
%token  MUL
%token  DIV
%token  NOT
%token  MOD
%token  LO
%token  EQ
%token  SC
%token  SBO
%token  SBC
%token  CBO
%token  CBC
%token  BO
%token  BC
%token  COMMA
%token GT
%token LT
%token GTEQ
%token LTEQ
%token EQEQ
%token NTEQ
%token LAND
%token LOR

%type <f> ARGS
%type <b> BLOCK
%type <vd> VAR_DEC
%type <vd> VAR_DEC1
%type <cd> IDDDS
%type <sd> STATEMENT1
%type <sd> STATEMENT
%type <ed> EXPR
%type <ed> EXPR1
%type <ed> M
%type <ed> N
%type <ed> O
%type <ed> P
%type <ed> P1
%type <ed> P2
%type <ed> METHOD_CALLLS
%type <nd> NUM
%type <sval> LOCATION1
%type <eld> EXPRARGS
%type <eld> CALLOUTARGS
%type <ssd> METHOD_CALL







%%
// this is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:

START		:	CLASS ID CBO FIELD_DEC METHOD_DEC CBC 	{fprintf(yyout, "PROGRAM ENCOUNTERED\n");
														 root = new program_node(field,method);}
				; 
FIELD_DEC	: 	FIELD_DEC FIELD_DEC1 
				| 
				;
FIELD_DEC1	: 	INT IDD  SC 							
				|BOOLEAN IDD1 SC
				;

IDD 		: 	IDD COMMA ID                           	{field.push_back(new intfielddeclaration($3));} 						
				|IDD COMMA ID SBO NONZERONUM SBC 		{field.push_back(new intarrayfielddeclaration($3,$5));}
				|ID 									{field.push_back(new intfielddeclaration($1));}
				|ID SBO NONZERONUM SBC  				{field.push_back(new intarrayfielddeclaration($1,$3));}
				;

IDD1		: 	IDD1 COMMA ID                           	{field.push_back(new booleanfielddeclaration($3));} 						
				|IDD1 COMMA ID SBO NONZERONUM SBC 		{field.push_back(new booleanarrayfielddeclaration($3,$5));}
				|ID 									{field.push_back(new booleanfielddeclaration($1));}
				|ID SBO NONZERONUM SBC  				{field.push_back(new booleanarrayfielddeclaration($1,$3));}
				;
	
	 					



METHOD_DEC 	:	METHOD_DEC1 METHOD_DEC2
				|
				;

METHOD_DEC1	:	INT ID BO ARGS BC BLOCK					{method.push_back(new methoddeclaration(i,$2,$4,$6));}
				| BOOLEAN ID BO ARGS BC BLOCK			{method.push_back(new methoddeclaration(b,$2,$4,$6));}
				| VOID ID BO ARGS BC BLOCK				{method.push_back(new methoddeclaration(v,$2,$4,$6));}
				;

METHOD_DEC2	:	METHOD_DEC2	INT ID BO ARGS BC BLOCK 				{method.push_back(new methoddeclaration(i,$3,$5,$7));}
				| METHOD_DEC2 BOOLEAN ID BO ARGS BC BLOCK 			{method.push_back(new methoddeclaration(b,$3,$5,$7));}
				| METHOD_DEC2 VOID ID BO ARGS BC BLOCK 				{method.push_back(new methoddeclaration(v,$3,$5,$7));}
				|
				;


ARGS		: 	INT ID 						{$$ = new list<argdeclaration*>;$$->push_back(new intargdeclaration($2));}
				| BOOLEAN ID 				{$$ = new list<argdeclaration*>;$$->push_back(new booleanargdeclaration($2));} 
				| ARGS COMMA INT ID 		{$$=$1;  						$$->push_back(new intargdeclaration($4));}
				| ARGS COMMA BOOLEAN ID 	{$$=$1;							$$->push_back(new booleanargdeclaration($4));}
				;



BLOCK		:   CBO VAR_DEC STATEMENT CBC	{$$=new block($2,$3);}
				;

VAR_DEC 	: 	INT IDDDS SC 				{$$=new list<vardeclaration*>;$$->push_back(new intvardeclaration($2));}
				| BOOLEAN IDDDS SC          {$$=new list<vardeclaration*>;$$->push_back(new booleanvardeclaration($2));}
				| VAR_DEC1 INT IDDDS SC		{$$=$1;						  $$->push_back(new intvardeclaration($3));}	
				| VAR_DEC1 BOOLEAN IDDDS SC {$$=$1;						  $$->push_back(new booleanvardeclaration($3));}
				| {$$=new list<vardeclaration*>;}
				;

VAR_DEC1 	: 	INT IDDDS SC 				{$$=new list<vardeclaration*>;$$->push_back(new intvardeclaration($2));}
				| BOOLEAN IDDDS SC          {$$=new list<vardeclaration*>;$$->push_back(new booleanvardeclaration($2));}
				| VAR_DEC1 INT IDDDS SC		{$$=$1;						  $$->push_back(new intvardeclaration($3));}	
				| VAR_DEC1 BOOLEAN IDDDS SC {$$=$1;						  $$->push_back(new booleanvardeclaration($3));}
				;



IDDDS		: 	ID 							{$$=new list<string>; 		$$->push_back($1);}
				|IDDDS COMMA ID 			{$$=$1; 					$$->push_back($3);}
				
				;

STATEMENT 	:	 LOCATION1 OPP EXPR SC 						{$$=new list<statementdeclaration*>;$$->push_back(new assignmentdeclaration($1,$3));}
				|METHOD_CALL SC 							{$$=new list<statementdeclaration*>;$$->push_back($1);}
				|IF BO EXPR BC BLOCK 						{$$=new list<statementdeclaration*>;$$->push_back(new ifdeclaration1($3,$5));}
				|IF BO EXPR BC BLOCK ELSE BLOCK 			{$$=new list<statementdeclaration*>;$$->push_back(new ifdeclaration2($3,$5,$7));}
				|FOR ID EQ EXPR COMMA EXPR BLOCK     		{$$=new list<statementdeclaration*>;$$->push_back(new fordeclaration($2,$4,$6,$7));}
				|RETURN SC                                  {$$=new list<statementdeclaration*>;$$->push_back(new returndeclaration2());}
				|RETURN EXPR SC 							{$$=new list<statementdeclaration*>;$$->push_back(new returndeclaration1($2));}
				|BREAK SC   								{$$=new list<statementdeclaration*>;$$->push_back(new breakdeclaration());}
				|CONTINUE SC 								{$$=new list<statementdeclaration*>;$$->push_back(new continuedeclaration());}
				|BLOCK  									{$$=new list<statementdeclaration*>;$$->push_back($1);}
				|STATEMENT1 LOCATION1 OPP EXPR SC 			{$$=$1;$$->push_back(new assignmentdeclaration($2,$4));}
				|STATEMENT1 METHOD_CALL SC 					{$$=$1;$$->push_back($2);}
				|STATEMENT1 IF BO EXPR BC BLOCK 			{$$=$1;$$->push_back(new ifdeclaration1($4,$6));}
				|STATEMENT1 IF BO EXPR BC BLOCK ELSE BLOCK  {$$=$1;$$->push_back(new ifdeclaration2($4,$6,$8));}
				|STATEMENT1 FOR ID EQ EXPR COMMA EXPR BLOCK {$$=$1;$$->push_back(new fordeclaration($3,$5,$7,$8));}
				|STATEMENT1 RETURN  SC 	 					{$$=$1;$$->push_back(new returndeclaration2());}
				|STATEMENT1 RETURN EXPR SC 					{$$=$1;$$->push_back(new returndeclaration1($3));}
				|STATEMENT1 BREAK SC   						{$$=$1;$$->push_back(new breakdeclaration());}
				|STATEMENT1 CONTINUE SC 					{$$=$1;$$->push_back(new continuedeclaration());}
				|STATEMENT1 BLOCK  							{$$=$1;$$->push_back($2);}
				| 											{$$=new list<statementdeclaration*>;}
				;
STATEMENT1 	:	 LOCATION1 OPP EXPR SC 						{$$=new list<statementdeclaration*>;$$->push_back(new assignmentdeclaration($1,$3));}
				|METHOD_CALL SC 							{$$=new list<statementdeclaration*>;$$->push_back($1);}
				|IF BO EXPR BC BLOCK 						{$$=new list<statementdeclaration*>;$$->push_back(new ifdeclaration1($3,$5));}
				|IF BO EXPR BC BLOCK ELSE BLOCK 			{$$=new list<statementdeclaration*>;$$->push_back(new ifdeclaration2($3,$5,$7));}
				|FOR ID EQ EXPR COMMA EXPR BLOCK     		{$$=new list<statementdeclaration*>;$$->push_back(new fordeclaration($2,$4,$6,$7));}
				|RETURN SC                                  {$$=new list<statementdeclaration*>;$$->push_back(new returndeclaration2());}
				|RETURN EXPR SC 							{$$=new list<statementdeclaration*>;$$->push_back(new returndeclaration1($2));}
				|BREAK SC   								{$$=new list<statementdeclaration*>;}
				|CONTINUE SC 								{$$=new list<statementdeclaration*>;}
				|BLOCK  									{$$=new list<statementdeclaration*>;$$->push_back($1);}
				|STATEMENT1 LOCATION1 OPP EXPR SC 			{$$=$1;$$->push_back(new assignmentdeclaration($2,$4));}
				|STATEMENT1 METHOD_CALL SC 					{$$=$1;$$->push_back($2);}
				|STATEMENT1 IF BO EXPR BC BLOCK 			{$$=$1;$$->push_back(new ifdeclaration1($4,$6));}
				|STATEMENT1 IF BO EXPR BC BLOCK ELSE BLOCK  {$$=$1;$$->push_back(new ifdeclaration2($4,$6,$8));}
				|STATEMENT1 FOR ID EQ EXPR COMMA EXPR BLOCK {$$=$1;$$->push_back(new fordeclaration($3,$5,$7,$8));}
				|STATEMENT1 RETURN  SC 	 					{$$=$1;$$->push_back(new returndeclaration2());}
				|STATEMENT1 RETURN EXPR SC 					{$$=$1;$$->push_back(new returndeclaration1($3));}
				|STATEMENT1 BREAK SC   						{$$=$1;$$->push_back(new breakdeclaration());}
				|STATEMENT1 CONTINUE SC 					{$$=$1;$$->push_back(new continuedeclaration());}
				|STATEMENT1 BLOCK  							{$$=$1;$$->push_back($2);}
				;

OPP			:	LO | EQ;

METHOD_CALL	:	ID BO EXPRARGS BC 						{$$=new noncalloutdeclaration($1,$3);}
				| CALLOUT BO STRING CALLOUTARGS BC 		{$$=new calloutdeclaration($3,$4);}
				;


EXPRARGS	:	EXPR 									{$$=new list<exprdeclaration*>;$$->push_back($1);}
				| EXPRARGS COMMA EXPR 					{$$=$1;$$->push_back($3);}
				;

CALLOUTARGS	:    COMMA EXPR               				{$$=new list<exprdeclaration*>;$$->push_back($2);}
				|COMMA STRING             				{$$=new list<exprdeclaration*>;$$->push_back(new stringdeclaration($2));}
				| CALLOUTARGS COMMA EXPR  				{$$=$1;$$->push_back($3);}
				| CALLOUTARGS COMMA STRING 				{$$=$1;$$->push_back(new stringdeclaration($3));} 
				;





EXPR 		: 	EXPR GT EXPR1							{fprintf(yyout,"GREATERTHAN  ENCOUNTERED\n");$$=new greaterthandeclaration($1,$3);}
	  			| EXPR LT EXPR1							{fprintf(yyout,"LESSTHAN ENCOUNTERED\n");$$=new lessthandeclaration($1,$3);}
	  			| EXPR GTEQ EXPR1   					{fprintf(yyout,"GREATERTHAN OR EQUALTO ENCOUNTERED\n");$$=new greaterthaneqdeclaration($1,$3);}
	  			| EXPR LTEQ EXPR1						{fprintf(yyout,"LESSTHAN OR EQUALTO ENCOUNTERED\n");$$=new lessthaneqdeclaration($1,$3);}
	  			| EXPR EQEQ EXPR1						{fprintf(yyout,"IS EQUAL ENCOUNTERED\n");$$=new eqeqdeclaration($1,$3);}
	  			| EXPR NTEQ EXPR1						{fprintf(yyout,"NOT EQUAL ENCOUNTERED\n");$$=new noteqdeclaration($1,$3);}
	  			| EXPR1									{$$=$1;}
	  			;

EXPR1: 			EXPR1 ADD M   							{fprintf(yyout,"ADDITION ENCOUNTERED\n");$$ = new plusdeclaration($1,$3);}
				| EXPR1 SUB M  							{fprintf(yyout,"SUBTRACTION ENCOUNTERED\n");$$=new subtractiondeclaration($1,$3);}
				| M 									{$$=$1;}
				;

M 			: 	M MUL N          						{fprintf(yyout,"MULTIPLICATION ENCOUNTERED\n");$$ = new multiplicationdeclaration($1,$3);}
				| M DIV N        						{fprintf(yyout,"DIVISION ENCOUNTERED\n");$$=new divisiondeclaration($1,$3);}
				| M MOD N 		 						{fprintf(yyout,"MOD ENCOUNTERED\n");$$=new moddeclaration($1,$3);}
 				| N 									{$$=$1;}
 				;

N 			: 	NOT O          							{fprintf(yyout,"NOT ENCOUNTERED\n");$$=new notdeclaration($2);}
				| O 									{$$=$1;}
				;

O 			: 	SUB P1 			 						{fprintf(yyout,"UNINARY MINUS ENCOUNTERED\n");$$ = new uniminusdeclaration($2);} 
				| P1 									{$$=$1;}
				;


P1			:    P1 LAND P2 							{$$=new landdeclaration($1,$3);}
				| P2 									{$$=$1;}
				;

P2 			:	P2 LOR P 								{$$=new lordeclaration($1,$3);}
				| P 									{$$=$1;}
				;


P 			: 	ID								        {$$=new chardeclaration($1);}
				| ID SBO EXPR SBC  						{fprintf(yyout, "LOCATION ENCOUNTERED=%s\n",$1);$$=new chararraydeclaration($1,$3);}
				| NUM 									{$$=$1;}
				| CHARACTER  							{fprintf(yyout, "CHAR ENCOUNTERED=%s\n" ,$1);  $$=new charassignment($1);}
				| TRUE									{fprintf(yyout, "BOOLEAN ENCOUNTERED=%s\n" ,$1);$$=new booleanassignment($1);}
				| FALSE									{fprintf(yyout, "BOOLEAN ENCOUNTERED=%s\n" ,$1);$$=new booleanassignment($1);}
				| BO EXPR BC 							{$$=$2;}
				| METHOD_CALLLS 						{$$=$1;}
				;

METHOD_CALLLS	: ID BO EXPRARGS BC 					{$$=new noncalloutdeclaration1($1,$3);}
				| CALLOUT BO STRING CALLOUTARGS BC 		{$$=new calloutdeclaration1($3,$4);}
				;


NUM 		: 	ZERO 									{fprintf(yyout, "INT ENCOUNTERED=%d\n",$1);$$=new numdeclaration($1);}
				| NONZERONUM							{fprintf(yyout, "INT ENCOUNTERED=%d\n",$1);$$=new numdeclaration($1);}
				;



LOCATION1 	:	ID 										{fprintf(yyout, "LOCATION ENCOUNTERED=%s\n",$1);$$=$1;}
				| ID SBO EXPR SBC  						{fprintf(yyout, "LOCATION ENCOUNTERED=%s\n",$1);$$=$1;}
				;









 




%%

int main(int argc, char** argv) {

	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		cout << "I can't open test_program!" << endl;
		cout << argv[0] << endl;
		return -1;
	}
	yyin = myfile;
	int errorvar = 0;
	
	FILE *myfile1 = fopen("bison_output.txt", "w");
	yyout = myfile1;
	
	FILE *myfile2 = fopen("flex_output.txt" , "w");
	yyout2 = myfile2;
	
	do {
	
		yyparse();
	} while (!feof(yyin) );

	//cout << "Success" << endl;
	int k = root->verify();
	if(k==-1)
	{
		cout << "Semantic Error" << endl;
		exit(-1);
	}

	root->print();

	CodeGenContext context;
    context.generateCode(root);

	
}

void yyerror(const char *s) {
		//cout << s << endl;

	cout << "Syntax Error" << endl;
	// might as well halt now:
	exit(-1);
}
