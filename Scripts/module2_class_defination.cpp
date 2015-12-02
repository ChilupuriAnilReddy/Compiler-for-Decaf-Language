#include "module2_class_declaration.h"
#include <map>
#include <string.h>

ofstream myfile3;
int level = 0;
string space = "  ";

map<string,int> symboltable;
map<string,int> symboltablelocal;
map<string,int> symboltablelocalarg;
map<string,int> functionnames;

void printspaces()
{
	for(int i=0;i<level;i++)
  	{
   		myfile3 << space;
  	}
}

intfielddeclaration::intfielddeclaration(string x)
{
    variablename = x;
    
	
}

void intfielddeclaration::print()
{
	printspaces();
	myfile3 << "<declaration name=\"" << variablename << "\" type=\"" << "integer"<<"\"/>" << endl;
}

int intfielddeclaration::verify()
{
    if(symboltable.find(variablename)==symboltable.end())
    {
        symboltable[variablename]=1;
        return 1;
    }
    else
    {
        return -1;
    }
}

int intfielddeclaration::type()
{
    return 1;
}

booleanfielddeclaration::booleanfielddeclaration(string x)
{
 	variablename = x;

}

int booleanfielddeclaration::verify()
{
    if(symboltable.find(variablename)==symboltable.end())
    {
        symboltable[variablename]=2;
        return 1;
    }
    else
    {
        return -1;
    }
}

void booleanfielddeclaration::print()
{
	printspaces();
	myfile3 << "<declaration name=\"" << variablename << "\" type=\"" << "boolean"<<"\"/>" << endl;
}

int booleanfielddeclaration::type()
{
    return 2;
}

intarrayfielddeclaration::intarrayfielddeclaration(string x,int n)
{
	variablename = x;
	sz = n;
   
}

int intarrayfielddeclaration::verify()
{
    if(symboltable.find(variablename)==symboltable.end())
    {
        symboltable[variablename]=1;
        return 1;
    }
    else
    {
        return -1;
    }
}

void intarrayfielddeclaration::print()
{
  	printspaces();
	myfile3 << "<declaration name=\"" << variablename << "\" count=\"" << sz << "\" type=\"" << "integer"<<"\"/>" << endl;

}

int intarrayfielddeclaration::type()
{
    return 1;
}


booleanarrayfielddeclaration::booleanarrayfielddeclaration(string x,int n)
{
	variablename = x;
	sz = n;
    
}

void booleanarrayfielddeclaration::print()
{
  	printspaces();
	myfile3 << "<declaration name=\"" << variablename << "\" count=\"" << sz << "\" type=\"" << "boolean"<<"\"/>" << endl;
}

int booleanarrayfielddeclaration::type()
{
    return 2;
}
int booleanarrayfielddeclaration::verify()
{
    if(symboltable.find(variablename)==symboltable.end())
    {
        symboltable[variablename]=2;
        return 1;
    }
    else
    {
        return -1;
    }
}


plusdeclaration::plusdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void plusdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "addition" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int plusdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}


subtractiondeclaration::subtractiondeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void subtractiondeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "subtraction" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int subtractiondeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

multiplicationdeclaration::multiplicationdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void multiplicationdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "multiplication" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int multiplicationdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}


divisiondeclaration::divisiondeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void divisiondeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "division" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int divisiondeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

moddeclaration::moddeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void moddeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "mod" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int moddeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}


greaterthandeclaration::greaterthandeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void greaterthandeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "greaterthan" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int greaterthandeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

lessthandeclaration::lessthandeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void lessthandeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "lessthan" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int lessthandeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

greaterthaneqdeclaration::greaterthaneqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void greaterthaneqdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "greaterthaneq" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int greaterthaneqdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

lessthaneqdeclaration::lessthaneqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void lessthaneqdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "lessthaneq" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int lessthaneqdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}



noteqdeclaration::noteqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void noteqdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "noteq" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int noteqdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

eqeqdeclaration::eqeqdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void eqeqdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "eqeq" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int eqeqdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}


landdeclaration::landdeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void landdeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "land" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int landdeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

lordeclaration::lordeclaration(exprdeclaration *expr1,exprdeclaration *expr2)
{
    L=expr1;
    R=expr2;
}
void lordeclaration::print()
{
    printspaces();
    myfile3 << "<binary_expression type=\"" << "lor" << "\">" << endl;
    level++;
    L->print();
    R->print();
    level--;
    printspaces();
    myfile3 << "<binary_expression>" << endl;

}

int lordeclaration::verify()
{
    int x = L->verify();
    int y = R->verify();
    if(x==-1 || y==-1)
    {
        return -1;
    }
    else if(x==y)
    {
        return x;
    }
    else
    {
        return -1;
    }
}

notdeclaration::notdeclaration(exprdeclaration *expr1)
{
    L=expr1;
}
void notdeclaration::print()
{
    printspaces();
    myfile3 << "<uninary_expression type=\"" << "not" << "\">" << endl;
    level++;
    L->print();
    level--;
    printspaces();
    myfile3 << "<uninary_expression>" << endl;

}

int notdeclaration::verify()
{
    int x = L->verify();
    if(x==-1)
    {
        return -1;
    }
    
    else
    {
        return x;
    }
}


uniminusdeclaration::uniminusdeclaration(exprdeclaration *expr1)
{
    L=expr1;
}
void uniminusdeclaration::print()
{
    printspaces();
    myfile3 << "<uninary_expression type=\"" << "not" << "\">" << endl;
    level++;
    L->print();
    level--;
    printspaces();
    myfile3 << "<uninary_expression>" << endl;

}

int uniminusdeclaration::verify()
{
    int x = L->verify();
    if(x==-1)
    {
        return -1;
    }
    
    else
    {
        return x;
    }
}


numdeclaration::numdeclaration(int value)
{
    num = value;
}
void numdeclaration::print()
{
    printspaces();
    myfile3 << "<integer value =\"" << num << "\"/>" << endl;
}

int numdeclaration::verify()
{
    return 1;
}


chardeclaration::chardeclaration(string value)
{
    name = value;
}
void chardeclaration::print()
{
    printspaces();
    myfile3 << "<location id=\"" << name << "\"/>" <<endl;
}

int chardeclaration::verify()
{
    if(symboltable.find(name)!=symboltable.end())
    {
        return symboltable[name];
    }
    else if(symboltablelocal.find(name)!=symboltablelocal.end())
    {
        return symboltablelocal[name];
    }
    else if(symboltablelocalarg.find(name)!=symboltablelocalarg.end())
    {
        return symboltablelocalarg[name];   
    }
    else
    {
        return -1;
    }
}



chararraydeclaration::chararraydeclaration(string value,exprdeclaration* e)
{
    name = value;
    expr = e;
}
void chararraydeclaration::print()
{
    printspaces();
    myfile3 << "<location id=\"" << name << "\"/>" <<endl;
}

int chararraydeclaration::verify()
{
    if(symboltable.find(name)!=symboltable.end())
    {
        return symboltable[name];
    }
    else if(symboltablelocal.find(name)!=symboltablelocal.end())
    {
        return symboltablelocal[name];
    }
    else if(symboltablelocalarg.find(name)!=symboltablelocalarg.end())
    {
        return symboltablelocalarg[name];   
    }
    else
    {
        return -1;
    }
}


stringdeclaration::stringdeclaration(string value)
{
    name = value;
}
void stringdeclaration::print()
{
    printspaces();
    myfile3 << "<string value=\"" << name << "\"/>" <<endl;
}
int stringdeclaration::verify()
{
    return 3;
} 


booleanassignment::booleanassignment(string v)
{
    value = v;
}
void booleanassignment::print()
{
    printspaces();
    myfile3 << "<boolean value=\"" << value << "\"/>" <<endl;
}
int booleanassignment::verify()
{
    return 2;
}

charassignment::charassignment(string v)
{
    value = v;
}
void charassignment::print()
{
    printspaces();
    myfile3 << "<char value=\"" << value << "\"/>" <<endl;
}
int charassignment::verify()
{
    return 4;
}




calloutdeclaration::calloutdeclaration(string value,list<exprdeclaration*> *givenargs)
{
    name=value;
    args=givenargs;
}
void calloutdeclaration::print()
{
    printspaces();
    myfile3 << "<callout function=" << name << ">" << endl;
    level++;
    list<exprdeclaration*>::iterator i;
    for(i=args->begin();i!=args->end();++i)
    {
        (*i)->print(); 
    }
    level--;
    printspaces();
    myfile3 << "</callout>" << endl;
}

int calloutdeclaration::verify()
{
    return 0;
}

noncalloutdeclaration::noncalloutdeclaration(string value,list<exprdeclaration*> *givenargs)
{
    name=value;
    args=givenargs;
}
void noncalloutdeclaration::print()
{
    printspaces();
    myfile3 << "<noncallout function=\"" << name << "\">" << endl;
    level++;
    list<exprdeclaration*>::iterator i;
    for(i=args->begin();i!=args->end();++i)
    {
        (*i)->print(); 
    }
    level--;
    printspaces();
    myfile3 << "</noncallout>" << endl;
}

int noncalloutdeclaration::verify()
{
     if(functionnames.find(name)==functionnames.end())
    {
        return -1;
    } 
    else
    {
        return 1;
    }
}


ifdeclaration1::ifdeclaration1(exprdeclaration *c,block *b)
{
    condition = c;
    blk = b;
}
void ifdeclaration1::print()
{
    printspaces();
    myfile3 << "<if>" << endl;
    level++;
    printspaces();
    myfile3 << "<condition>" << endl;
    level++;
    condition->print();
    level--;
    printspaces();
    myfile3 << "</condition>" << endl;
    printspaces();
    myfile3 << "<if_block>" << endl;
    level++;
    blk->print();
    level--;
    printspaces();
    myfile3 << "</if_block>" << endl;
    level--;
    printspaces();
    myfile3 << "</if>" << endl;
}

int ifdeclaration1::verify()
{
    int l = condition->verify();
    if(l==4 || l==3)
    {
        return -1;
    }
    return 1;
}

ifdeclaration2::ifdeclaration2(exprdeclaration *c,block *b1,block *b2)
{
    condition = c;
    blk1 = b1;
    blk2 = b2;
}
void ifdeclaration2::print()
{
    printspaces();
    myfile3 << "<if>" << endl;
    level++;
    printspaces();
    myfile3 << "<condition>" << endl;
    level++;
    condition->print();
    level--;
    printspaces();
    myfile3 << "</condition>" << endl;
    printspaces();
    myfile3 << "<if_block>" << endl;
    level++;
    blk1->print();
    level--;
    printspaces();
    myfile3 << "</if_block>" << endl;
    printspaces();
    myfile3 << "<else_block>" << endl;
    level++;
    blk2->print();
    level--;
    printspaces();
    myfile3 << "</else_block>" << endl;
    level--;
    printspaces();
    myfile3 << "</if>" << endl;
}

int ifdeclaration2::verify()
{
    int l = condition->verify();
    if(l==4 || l==3)
    {
        return -1;
    }
    return 1;
}

fordeclaration::fordeclaration(string v,exprdeclaration *s,exprdeclaration *e,block *b)
{
    variable=v;
    start=s;
    end=e;
    blk=b;
    
}
void fordeclaration::print()
{
    printspaces();
    myfile3 << "<for>" << endl;
    level++;
    printspaces();
    myfile3 << "<id =" << variable << "/>" << endl;
    printspaces();
    myfile3 << "<start_condition>" << endl;
    level++;
    start->print();
    level--;
    printspaces();
    myfile3 << "</start_condition>" << endl;
    printspaces();
    myfile3 << "<end_condition>" << endl;
    level++;
    end->print();
    level--;
    printspaces();
    myfile3 << "</end_condition>" << endl;
    printspaces();
    myfile3 << "<for_block>" << endl;
    level++;
    blk->print();
    level--;
    printspaces();
    myfile3 << "<for_block>" << endl;
    level--;
    printspaces();
    myfile3 << "<for>" << endl;
}

int fordeclaration::verify()
{
    int l,r;
    if(symboltable.find(variable)!=symboltable.end())
    {
        l = symboltable[variable];
        
    }
    else if(symboltablelocal.find(variable)!=symboltablelocal.end())
    {
        l = symboltablelocal[variable];
           
    }
    else if(symboltablelocalarg.find(variable)!=symboltablelocalarg.end())
    {
        l = symboltablelocalarg[variable];
           
    }
    else
    {
        return -1;
    }
    r = start->verify();
    l = end->verify();
    if(r==1&&l==1)
    {
        return 1;
    }
    return -1;
}

returndeclaration1::returndeclaration1(exprdeclaration *r)
{
    toreturn = r;
}
void returndeclaration1::print()
{
    printspaces();
    myfile3 << "<return_statement>" << endl;
    level++;
    toreturn->print();
    level--;
    printspaces();
    myfile3 << "</return_statement>" << endl;
}

int returndeclaration1::verify()
{
    return 0;
}

void returndeclaration2::print()
{
    printspaces();
    myfile3 << "<return_statement>" << endl;
    level++;
    level--;
    printspaces();
    myfile3 << "</return_statement>" << endl;
}


int returndeclaration2::verify()
{
    return 0;
}


void breakdeclaration::print()
{
    printspaces();
    myfile3 << "</break_statement>" << endl;
}

int breakdeclaration::verify()
{
    return 0;
}

void continuedeclaration::print()
{
    printspaces();
    myfile3 << "</continue_statement>" << endl;
}

int continuedeclaration::verify()
{
    return 0;
}

assignmentdeclaration::assignmentdeclaration(string x,exprdeclaration *expr1)
{
    assign=x;
    expr=expr1;
}
void assignmentdeclaration::print()
{
    printspaces();
    myfile3 << "<assignment>" << endl;
    level++;
    printspaces();
    myfile3 << "<location" << assign << "/>" << endl;
   
    expr->print();
    level--;
    printspaces();
    myfile3 << "</assignment>" << endl;
}






calloutdeclaration1::calloutdeclaration1(string value,list<exprdeclaration*> *givenargs)
{
    name=value;
    args=givenargs;
}
void calloutdeclaration1::print()
{
    printspaces();
    myfile3 << "<callout function=" << name << ">" << endl;
    level++;
    list<exprdeclaration*>::iterator i;
    for(i=args->begin();i!=args->end();++i)
    {
        (*i)->print(); 
    }
    level--;
    printspaces();
    myfile3 << "</callout>" << endl;
}

int calloutdeclaration1::verify()
{
    return 0;
}

noncalloutdeclaration1::noncalloutdeclaration1(string value,list<exprdeclaration*> *givenargs)
{
    name=value;
    args=givenargs;
}
void noncalloutdeclaration1::print()
{
    printspaces();
    myfile3 << "<noncallout function=\"" << name << "\">" << endl;
    level++;
    list<exprdeclaration*>::iterator i;
    for(i=args->begin();i!=args->end();++i)
    {
        (*i)->print(); 
    }
    level--;
    printspaces();
    myfile3 << "</noncallout>" << endl;
}

int noncalloutdeclaration1::verify()
{
    if(functionnames.find(name)==functionnames.end())
    {
        return -1;
    } 
    else
    {
        return functionnames[name];
    }
}




int assignmentdeclaration::verify()
{

    int l,r;
    if(symboltable.find(assign)!=symboltable.end())
    {
        l = symboltable[assign];
    }
    else if(symboltablelocal.find(assign)!=symboltablelocal.end())
    {
        l = symboltablelocal[assign];
    }
    else if(symboltablelocalarg.find(assign)!=symboltablelocalarg.end())
    {
        l = symboltablelocalarg[assign];   
    }
    else
    {

        return -1;
    }

    r = expr->verify();
    if(l==r)
    {
        return r;
    }
    else
    {
        return -1;
    }

}

intvardeclaration::intvardeclaration(list<string> *x)
{
    variablename = x;
}

void intvardeclaration::print()
{
    
    list<string>::iterator i;
    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
       printspaces();
       myfile3 << "<declaration name=\"" << *i << "\" type=\"" << "integer"<<"\"/>" << endl;
    }
    
}


int intvardeclaration::verify()
{

    
    list<string>::iterator i;
    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
        if(symboltable.find(*i)==symboltable.end())
        {
            if(symboltablelocalarg.find(*i)==symboltablelocalarg.end())
            {
                if(symboltablelocal.find(*i)==symboltablelocal.end())
                {
                    symboltablelocal[*i]=1;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    return 1;
}


booleanvardeclaration::booleanvardeclaration(list<string > *x)
{
    variablename = x;
}

void booleanvardeclaration::print()
{
    
    list<string>::iterator i;
    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
        printspaces();
       myfile3 << "<declaration name=\"" << *i << "\" type=\"" << "boolean"<<"\"/>" << endl;
    }
    
}
int booleanvardeclaration::verify()
{
  list<string>::iterator i;
    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
        if(symboltable.find(*i)==symboltable.end())
        {
            if(symboltablelocalarg.find(*i)==symboltablelocalarg.end())
            {
                if(symboltablelocal.find(*i)==symboltablelocal.end())
                {
                    symboltablelocal[*i]=2;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    return 1;
}



block::block(list<vardeclaration*> *a,list<statementdeclaration*> *b)
{
    left = a;
    right = b;

}
void block::print()
{
    printspaces();
    myfile3 <<"<var_declarations>" << endl;
    level++;
    list<vardeclaration*>::iterator i;
    for( i = left->begin(); i != left->end(); ++i)
    {
       (*i)->print();
    }
    level--;
    printspaces();
    myfile3 <<"</var_declaration>" << endl;
    printspaces();
    myfile3 <<"<statement_declarations>" << endl;
    level++;
    list<statementdeclaration*>::iterator i1;
    for( i1 = right->begin(); i1 != right->end(); ++i1)
    {
       (*i1)->print();
    }
    level--;
    printspaces();
    myfile3 <<"</statement_declaration>" << endl;

}

int block::verify()
{
    int z;

    list<vardeclaration*>::iterator i;
    for( i = left->begin(); i != left->end(); ++i)
    {
       z = (*i)->verify();
       if(z==-1)
       {
            (*i)->print();
            return -1;
        }

    }

    list<statementdeclaration*>::iterator i1;
    for( i1 = right->begin(); i1 != right->end(); ++i1)
    {
       z = (*i1)->verify();
       if(z==-1)
       {
            (*i1)->print();
            return -1;
        }
    }
    return 1;
}


intargdeclaration::intargdeclaration(string x)
{
    variablename = x;
}

void intargdeclaration::print()
{
    printspaces();
    myfile3 << "<argument name=\"" << variablename << "\" type=\"" << "integer"<<"\"/>" << endl;
}

int intargdeclaration::type()
{
    return 1;
}

int intargdeclaration::verify()
{
    int l;
    if(symboltable.find(variablename)==symboltable.end())
    {
        if(symboltablelocalarg.find(variablename)==symboltablelocalarg.end())
        {
            symboltablelocalarg[variablename]=1;
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

booleanargdeclaration::booleanargdeclaration(string x)
{
    variablename = x;
}

void booleanargdeclaration::print()
{
    printspaces();
    myfile3 << "<argument name=\"" << variablename << "\" type=\"" << "boolean"<<"\"/>" << endl;
}

int booleanargdeclaration::type()
{
    return 2;
}

int booleanargdeclaration::verify()
{
    int l;
    if(symboltable.find(variablename)==symboltable.end())
    {
        if(symboltablelocalarg.find(variablename)==symboltablelocalarg.end())
        {
            symboltablelocalarg[variablename]=2;
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}


methoddeclaration::methoddeclaration(string t,string  n,list<argdeclaration*> *a,block *b)
{
    type=t;
    name=n;
    args=a;
    blk=b;
}
void methoddeclaration::print()
{
    printspaces();
    myfile3 <<"<method_declarations>" << endl ;
    level++;
    printspaces();
    myfile3 << "<declaration type=\"" << type <<  "\" name=\"" << name <<"\"/>" << endl;
    printspaces();
    myfile3 <<"<arguments>" << endl;
    level++;
    list<argdeclaration*>::iterator i;
    for( i = args->begin(); i != args->end(); ++i)
    {
       (*i)->print();
    }
    level--;
    printspaces();
    myfile3 <<"</arguments>" << endl;
    blk->print();
    level--;
    printspaces();
    myfile3 <<"</method_declarations>" << endl ; 

}

int methoddeclaration::verify()
{
    symboltablelocalarg.clear();
    symboltablelocal.clear();

     if(symboltable.find(name)!=symboltable.end())
        {
            return -1;

    }
    if(functionnames.find(name)==functionnames.end())
    {
        if(type.compare("Int")==0)
        {
            functionnames[name]=1;
        }
        if(type.compare("Boolean")==0)
        {
            functionnames[name]=2;
        }
        if(type.compare("Void")==0)
        {
            functionnames[name]=10;
        }
    }
    else
    {
        return -1;
    }


    int y;
    list<argdeclaration*>::iterator i;
    for( i = args->begin(); i != args->end(); ++i)
    {
        y = (*i)->verify();
        if(y==-1)
        {

            return -1;
        }
    }
    int z = blk->verify();
    return z;
}





program_node::program_node(list<fielddeclaration*> L,list<methoddeclaration*> R)
{
    left=L;
    right=R;
}

void program_node::print()
{
    myfile3.open("ast.xml");
    myfile3 << "<program>" << endl;
    level++;
    printspaces();
    myfile3 << "<field_declarations count=\"" << left.size() << "\">" << endl;
    level++;
    list<fielddeclaration*>::iterator i;
    for( i = left.begin(); i != left.end(); ++i)
    {
       (*i)->print();
    }
    level--;
    printspaces();
    myfile3 <<"</field_declarations>" << endl << endl;
    printspaces();
    myfile3 << "<method_declarations count=\"" << right.size() << "\">" << endl;
    level++;
    list<methoddeclaration*>::iterator i1;
    for( i1 = right.begin(); i1 != right.end(); ++i1)
    {
       (*i1)->print();
    }
    level--;
    printspaces();
    myfile3 <<"</method_declarations>" << endl;;
    level--;
    printspaces();
    myfile3 << "</program>"<< endl;
    myfile3.close();
}

int program_node::verify()
{
    myfile3.open("error.xml");
    int z;
    list<fielddeclaration*>::iterator i;
    for( i = left.begin(); i != left.end(); ++i)
    {
        z =  (*i)->verify();
        if(z==-1)
        {
            //cout <<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee2" << endl;;
            (*i)->print();
            return -1;
        }
    }
    

    list<methoddeclaration*>::iterator i1;
    for( i1 = right.begin(); i1 != right.end(); ++i1)
    {
       z = (*i1)->verify();
       if(z==-1)
       {
            //cout <<"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee1" << endl;;
          //  (*i1)->print();
            return -1;
       }
    }
    myfile3.close();

    return 1;
}
