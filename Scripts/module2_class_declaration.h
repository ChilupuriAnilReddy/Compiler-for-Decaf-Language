#include <iostream>
#include <fstream>
#include <stdio.h>
#include <list>
#include <llvm/IR/Value.h>
using namespace std;
using namespace llvm;


class CodeGenContext;

class fielddeclaration
{
protected:
public:
	virtual void print()=0;
	virtual int type()=0;
	virtual int verify()=0;
	virtual Value* codeGen(CodeGenContext& context)=0;
private:
};



class intfielddeclaration : public fielddeclaration
{
protected:
	string variablename;
public:
	intfielddeclaration(string x);
	int type();
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class booleanfielddeclaration : public fielddeclaration
{
protected:
	string variablename;
public:
	booleanfielddeclaration(string x);
	void print();
	int type();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class intarrayfielddeclaration : public fielddeclaration
{
protected:
	string variablename;
	int sz;
public:
	intarrayfielddeclaration(string x,int n);
	void print();
	int type();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class booleanarrayfielddeclaration : public fielddeclaration
{
protected:
	string variablename;
	int sz;
public:
	booleanarrayfielddeclaration(string x,int n);
	void print();
	int type();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class statementdeclaration
{
protected:
public:
	virtual void print()=0;
	virtual int verify()=0;
	virtual Value* codeGen(CodeGenContext& context)=0;
private:
};

class exprdeclaration
{
protected:
	
public:
	float num;
	virtual void print() = 0;
	virtual int verify() = 0;
	virtual Value* codeGen(CodeGenContext& context)=0;
private:
};


class plusdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	plusdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class subtractiondeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	subtractiondeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class multiplicationdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	multiplicationdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class divisiondeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	divisiondeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class moddeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	moddeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class greaterthandeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	greaterthandeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class lessthandeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	lessthandeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class greaterthaneqdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	greaterthaneqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class lessthaneqdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	lessthaneqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class noteqdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	noteqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class eqeqdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	eqeqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class landdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	landdeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class lordeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
	exprdeclaration *R;
public:
	lordeclaration(exprdeclaration *expr1,exprdeclaration *expr2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class notdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
public:
	notdeclaration(exprdeclaration *expr1);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class uniminusdeclaration : public exprdeclaration
{
protected:
	exprdeclaration *L;
public:
	uniminusdeclaration(exprdeclaration *expr1);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class numdeclaration : public exprdeclaration
{
protected:
public:
	numdeclaration(int value);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class chardeclaration : public exprdeclaration
{
protected:
	string name;
public:
	chardeclaration(string value);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class stringdeclaration : public exprdeclaration
{
protected:
	string name;
public:
	stringdeclaration(string value);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class booleanassignment : public exprdeclaration
{
protected:
	string value;
public:
	booleanassignment(string v);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class charassignment : public exprdeclaration
{
protected:
	string value;
public:
	charassignment(string v);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class chararraydeclaration : public exprdeclaration
{
protected:
	string name;
	exprdeclaration *expr;
public:
	chararraydeclaration(string v,exprdeclaration *e);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class assignmentdeclaration : public statementdeclaration
{
protected:
	string assign;
	exprdeclaration *expr;
public:
	assignmentdeclaration(string x,exprdeclaration *expr1);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};




class calloutdeclaration1 : public exprdeclaration
{
protected:
	string name;
	list<exprdeclaration*> *args;
public:
	calloutdeclaration1(string value,list<exprdeclaration*> *givenargs);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class noncalloutdeclaration1 : public exprdeclaration
{
protected:
	string name;
	list<exprdeclaration*> *args;
public:
	noncalloutdeclaration1(string value,list<exprdeclaration*> *givenargs);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class calloutdeclaration : public statementdeclaration
{
protected:
	string name;
	list<exprdeclaration*> *args;
public:
	calloutdeclaration(string value,list<exprdeclaration*> *givenargs);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class noncalloutdeclaration : public statementdeclaration
{
protected:
	string name;
	list<exprdeclaration*> *args;
public:
	noncalloutdeclaration(string value,list<exprdeclaration*> *givenargs);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};




class vardeclaration
{
protected:
public:
	virtual void print()=0;
	virtual int verify()=0;
	virtual Value* codeGen(CodeGenContext& context)=0;
private:
};



class intvardeclaration : public vardeclaration
{
protected:
	list<string> *variablename;
public:
	intvardeclaration(list<string> *x);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class booleanvardeclaration : public vardeclaration
{
protected:
	list<string> *variablename;
public:
	booleanvardeclaration(list<string> *x);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};




class block	: public statementdeclaration
{
protected:
	list<vardeclaration*> *left;
	list<statementdeclaration*> *right;
public:
	block(list<vardeclaration*> *a,list<statementdeclaration*> *b);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};




class ifdeclaration1:public statementdeclaration
{
protected:
	exprdeclaration *condition;
	block	*blk;
public:
	ifdeclaration1(exprdeclaration *c,block *b);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class ifdeclaration2:public statementdeclaration
{
protected:
	exprdeclaration *condition;
	block	*blk1;
	block	*blk2;
public:
	ifdeclaration2(exprdeclaration *c,block *b1,block *b2);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class fordeclaration:public statementdeclaration
{
protected:
	string variable;
	exprdeclaration *start;
	exprdeclaration *end;
	block	*blk;
public:
	fordeclaration(string v,exprdeclaration *s,exprdeclaration *e,block *b);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class returndeclaration1:public statementdeclaration
{
protected:
	exprdeclaration *toreturn;
public:
	returndeclaration1(exprdeclaration *r);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class returndeclaration2:public statementdeclaration
{
protected:
	
public:
	
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class breakdeclaration:public statementdeclaration
{
protected:
public:
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class continuedeclaration:public statementdeclaration
{
protected:
public:
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};

class argdeclaration
{
protected:
public:
	string variablename;
	virtual void print()=0;
	virtual int type()=0;
	virtual int verify()=0;
	virtual Value* codeGen(CodeGenContext& context)=0;
private:
};



class intargdeclaration : public argdeclaration
{
protected:
	
public:
	intargdeclaration(string x);
	void print();
	int type();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};


class booleanargdeclaration : public argdeclaration
{
protected:
	
public:
	booleanargdeclaration(string x);
	void print();
	int type();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};




class methoddeclaration
{
protected:
	string type;
	string name;
	list<argdeclaration*> *args;
	block *blk;
public:
	methoddeclaration(string t,string  n,list<argdeclaration*> *a,block *b);
	void print();
	Value* codeGen(CodeGenContext& context);
	int verify();
private:
};






class program_node
{
protected:
	list<fielddeclaration*> left;
	list<methoddeclaration*> right;
public:
	program_node(list<fielddeclaration*> L,list<methoddeclaration*> R);
	void print();
	int verify();
	Value* codeGen(CodeGenContext& context);
private:
};