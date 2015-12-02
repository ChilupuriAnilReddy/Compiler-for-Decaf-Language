%{
#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;
#include "module2_class_declaration.h"
#include "module2_bison.tab.h"
FILE *yyout2;

#define YY_DECL extern "C" int yylex()
%}

%%
[ \t\n]         ;
[(] 						{ return BO;}
[)] 						{ return BC;}
[{] 						{ return CBO;}
[}]							{ return CBC;}
[[]							{ return SBO;}
[]]							{ return SBC;}
[,]							{ return COMMA;}
[>]							{ return GT;}
[<]							{ return LT;}
[<][=]						{ return LTEQ;}
[>][=]						{ return GTEQ;}
[=][=]						{ return EQEQ;}
[!][=]						{ return NTEQ;}
[";"]						{ return SC;}
[|][|] 						{ return LOR;}
[&][&] 						{ return LAND;}
if 							{ return IF;}
else						{ return ELSE;}
for							{ return FOR;}
return						{ return RETURN;}
break						{ return BREAK;}
continue					{ return CONTINUE;}
void 						{ return VOID;}
boolean      				{ fprintf(yyout2,"%s\n","BOOLEAN_DECLARATION"); return BOOLEAN;}
callout		 				{ fprintf(yyout2 , "%s\n" , "CALLOUT"); return CALLOUT;}
class		         		{ fprintf(yyout2 , "%s\n" , "CLASS"); return CLASS;}
false		         		{ yylval.sval = strdup(yytext); return FALSE;}
int                         { fprintf(yyout2 , "%s\n" , "INT_DECLARATION");return INT; }
true	                 	{ yylval.sval = strdup(yytext); return TRUE;}
[a-zA-Z_]+[a-zA-Z]*[0-9]*	{ fprintf(yyout2 , "ID: %s\n" ,yytext); yylval.sval = strdup(yytext); return ID;}
[1-9]+[0-9]*	 		    { fprintf(yyout2 , "INT: %s\n" , yytext); yylval.ival = atoi(yytext)  ; return NONZERONUM;}
[0]							{ fprintf(yyout2 , "INT: %s\n" , yytext); yylval.ival = atoi(yytext)  ; return ZERO;}
["\'"][a-zA-Z]["\'"]		{ fprintf(yyout2 , "CHAR: %s\n" , yytext); yylval.sval = strdup(yytext); return CHARACTER;}
["\""][%]*[,]*[a-zA-Z]*["\""]		{ fprintf(yyout2 , "STRING: %s\n",yytext); yylval.sval = strdup(yytext); return STRING;}
[+]							{ return ADD;}
[-]							{ return SUB;}
[*]							{ return MUL;}
[/]							{ return DIV;}
[%]							{ return MOD;}
[!]							{ return NOT;}
[=]							{ return EQ;}
[+][=]						{ return LO;}
[-][=]						{ return LO;}
.                			{return WRONG;}

%%

