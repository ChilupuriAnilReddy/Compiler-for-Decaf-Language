#include "module2_codegen.h"
#include <string.h>
#include <stdio.h>

static IRBuilder<> Builder(getGlobalContext());



void CodeGenContext::generateCode(program_node* root)
{

	
	
	/* Create the top level interpreter function to call as entry */
	vector<Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), (argTypes), false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "anil", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);
	
	/* Push a new variable/block context */
	pushBlock(bblock);
	root->codeGen(*this); /* emit bytecode for the toplevel block */
	ReturnInst::Create(getGlobalContext(), bblock);
	popBlock();
	
	/* Print the bytecode in a human-readable format 
	   to see if our program compiled properly
	 */
	PassManager pm;
	pm.add(createPrintModulePass(&outs()));
	pm.run(*module);


}

Value *program_node::codeGen(CodeGenContext& context)
{
	Value *last = NULL;
	list<fielddeclaration*>::iterator i;
    for( i = left.begin(); i != left.end(); ++i)
    {
    	last = (*i)->codeGen(context);
    }	

    list<methoddeclaration*>::iterator i1;
    for( i1 = right.begin(); i1 != right.end(); ++i1)
    {
    	last = (*i1)->codeGen(context);
    }

    return last;

}


Value *intfielddeclaration::codeGen(CodeGenContext& context)
{

	if (context.locals().find(variablename) != context.locals().end()) 
    {   
        std::cerr << "redeclaring variable in expression " << variablename << std::endl;
        return NULL;
    }   
	Value *v;
	AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}


Value *booleanfielddeclaration::codeGen(CodeGenContext& context)
{

	if (context.locals().find(variablename) != context.locals().end()) 
    {   
        std::cerr << "redeclared variable in expression " << variablename << std::endl;      
        return NULL;
    }   
  
	Value *v;
	AllocaInst *alloc = new AllocaInst( Type::getInt1Ty(getGlobalContext()) , variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}


Value *intarrayfielddeclaration::codeGen(CodeGenContext& context)
{
	if (context.locals().find(variablename) != context.locals().end()) 
    {   
        std::cerr << "redeclaring variable in expression " << variablename << std::endl;
        return NULL;
    }   
	Value *v;
	Value *szz;
	szz = ConstantInt::get(Type::getInt32Ty(getGlobalContext()),sz,true); 
	AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , szz ,variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}


Value *booleanarrayfielddeclaration::codeGen(CodeGenContext& context)
{
	if (context.locals().find(variablename) != context.locals().end()) 
    {   
        std::cerr << "redeclaring variable in expression " << variablename << std::endl;
        return NULL;
    }   
	Value *v;
	Value *szz;
	szz = ConstantInt::get(Type::getInt32Ty(getGlobalContext()),sz,true); 
	AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , szz ,variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}


Value *plusdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::Add, l,r, "", context.currentBlock());
	}
	return bin;

}

Value *subtractiondeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::Sub, l,r, "", context.currentBlock());
	}
	return bin;

}

Value *multiplicationdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::Mul, l,r, "", context.currentBlock());
	}
	return bin;

}

Value *divisiondeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::SDiv, l,r, "", context.currentBlock());
	}
	return bin;

}

Value *moddeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::SRem, l,r, "", context.currentBlock());
	}
	return bin;

}

Value *greaterthandeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, l, r,"",context.currentBlock());
	}
	return NULL;

}

Value *lessthandeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, l, r,"",context.currentBlock());
	}
	return NULL;
}


Value *greaterthaneqdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, l, r,"",context.currentBlock());
	}
	return NULL;

}

Value *lessthaneqdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, l, r,"",context.currentBlock());
	}
	return NULL;

}

Value *noteqdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::And, l,r, "", context.currentBlock());
	}
	return bin;
}

Value *eqeqdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		bin = BinaryOperator::Create(Instruction::Or, l,r, "", context.currentBlock());
	}
	return bin;

}


Value *notdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);

	
	return bin;

}

Value *uniminusdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	
	return bin;

}

Value *landdeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, L->codeGen(context), R->codeGen(context),"",context.currentBlock());
	}
	return NULL;

}

Value *lordeclaration::codeGen(CodeGenContext& context)
{
	
	Value *bin=NULL;

	Value *l = L->codeGen(context);
	Value *r = R->codeGen(context);

	if(l!=NULL && r!=NULL)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, L->codeGen(context), R->codeGen(context),"",context.currentBlock());
	}
	return NULL;

}

Value *numdeclaration::codeGen(CodeGenContext& context)
{
	return ConstantInt::get(Type::getInt32Ty(getGlobalContext()),num,true);
}


Value *chardeclaration::codeGen(CodeGenContext& context)
{

	if (context.locals().find(name) == context.locals().end()) 
    {   
        
        return NULL;
    }   
    return new LoadInst(context.locals()[name], "", false, context.currentBlock());
		
}

Value *chararraydeclaration::codeGen(CodeGenContext& context)
{

	if (context.locals().find(name) == context.locals().end()) 
    {   
        return NULL;
    }   
    return new LoadInst(context.locals()[name], "", false, context.currentBlock());
		
}

Value *stringdeclaration::codeGen(CodeGenContext& context)
{
		string temp=name.substr(1,name.length()-2);
		//cout << "***" << temp << "****" << endl;

		GlobalVariable* variable = new GlobalVariable(*(context.module), ArrayType::get(IntegerType::get(getGlobalContext(), 8), temp.size() + 1), true, GlobalValue::InternalLinkage, NULL, "string");
        
        variable->setInitializer(llvm::ConstantDataArray::getString(llvm::getGlobalContext(), temp, true));
        return variable;

}


Value *booleanassignment::codeGen(CodeGenContext& context)
{
	
}


Value *charassignment::codeGen(CodeGenContext& context)
{
	
}


Value *calloutdeclaration::codeGen(CodeGenContext& context)
{
	//cout << "*******" << name[0] << "*********" << endl;
	string temp=name.substr(1,name.length()-2);
	Function *function = context.module->getFunction(temp);

	//cout << "*******" << temp << "*********" << endl;
	if(function==NULL)
	{
		 FunctionType *ftype = FunctionType::get(Type::getInt32Ty(getGlobalContext()), true);
         function = Function::Create(ftype, GlobalValue::ExternalLinkage, temp, context.module);
	}
	
	list<exprdeclaration*>::iterator i;
    vector<Value*> genargs;
    
    for(i=args->begin();i!=args->end();++i)
    {
        genargs.push_back((*i)->codeGen(context)); 
    }
	
	CallInst *call = NULL;
	call = CallInst::Create(function,makeArrayRef(genargs),temp,context.currentBlock());
	return call;
}

Value *noncalloutdeclaration::codeGen(CodeGenContext& context)
{

	Function *function = context.module->getFunction(name);
	
	if(function==NULL)
	{
		
		return NULL;
	}
	
	list<exprdeclaration*>::iterator i;
    vector<Value*> genargs;
    
    for(i=args->begin();i!=args->end();++i)
    {
        genargs.push_back((*i)->codeGen(context)); 
    }
	
	CallInst *call = NULL;
	call = CallInst::Create(function,makeArrayRef(genargs),"",context.currentBlock());
	return call;
}


Value *calloutdeclaration1::codeGen(CodeGenContext& context)
{

	//cout << "*******" << name[0] << "*********" << endl;
	string temp=name.substr(1,name.length()-2);
	Function *function = context.module->getFunction(temp);

	//cout << "*******" << temp << "*********" << endl;
	if(function==NULL)
	{
		 FunctionType *ftype = FunctionType::get(Type::getInt32Ty(getGlobalContext()), true);
         function = Function::Create(ftype, GlobalValue::ExternalLinkage, temp, context.module);
	}
	
	list<exprdeclaration*>::iterator i;
    vector<Value*> genargs;
    
    for(i=args->begin();i!=args->end();++i)
    {
        genargs.push_back((*i)->codeGen(context)); 
    }
	
	CallInst *call = NULL;
	call = CallInst::Create(function,makeArrayRef(genargs),temp,context.currentBlock());
	return call;

}

Value *noncalloutdeclaration1::codeGen(CodeGenContext& context)
{

	Function *function = context.module->getFunction(name);
	
	if(function==NULL)
	{
		return NULL;
	}
	
	list<exprdeclaration*>::iterator i;
    vector<Value*> genargs;
    
    for(i=args->begin();i!=args->end();++i)
    {
    	//cout << "YES" << endl;
        genargs.push_back((*i)->codeGen(context)); 
    }
	
	CallInst *call = NULL;
	call = CallInst::Create(function,makeArrayRef(genargs),"",context.currentBlock());
	return call;
}

Value *ifdeclaration1::codeGen(CodeGenContext& context)
{

		

}

Value *ifdeclaration2::codeGen(CodeGenContext& context)
{
	
}

Value *fordeclaration::codeGen(CodeGenContext& context)
{
	
}


Value *returndeclaration1::codeGen(CodeGenContext& context)
{
		Value *val = toreturn -> codeGen(context);
		return ReturnInst::Create(getGlobalContext(),val,context.currentBlock());
}

Value *returndeclaration2::codeGen(CodeGenContext& context)
{
		
		return ReturnInst::Create(getGlobalContext(),context.currentBlock());
}

Value *breakdeclaration::codeGen(CodeGenContext& context)
{
	
}

Value *continuedeclaration::codeGen(CodeGenContext& context)
{
	
}


Value *assignmentdeclaration::codeGen(CodeGenContext& context)
{
	if(context.locals().find(assign) == context.locals().end())
	{
		return NULL;
	}
   
	Value *st = expr->codeGen(context);

	if(st!=NULL)
		st = new StoreInst(st, context.locals()[assign], context.currentBlock());

	return st;
}



Value *intvardeclaration::codeGen(CodeGenContext& context)
{
	Value *v;
	list<string>::iterator i;

    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
    	AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , (*i) , context.currentBlock());
		context.locals()[(*i)] = alloc;
		v=alloc;
    }

	return v;
}

Value *booleanvardeclaration::codeGen(CodeGenContext& context)
{
	Value *v;
	list<string>::iterator i;

    for( i = variablename->begin(); i != variablename->end(); ++i)
    {
    	AllocaInst *alloc = new AllocaInst( Type::getInt1Ty(getGlobalContext()) , (*i) , context.currentBlock());
		context.locals()[(*i)] = alloc;
		v=alloc;
    }

	return v;
}

Value *block::codeGen(CodeGenContext& context)
{
	
	Value *last = NULL;
	list<vardeclaration*>::iterator i;
    for( i = left->begin(); i != left->end(); ++i)
    {
    	last = (*i)->codeGen(context);
    }	

    list<statementdeclaration*>::iterator i1;
    for( i1 = right->begin(); i1 != right->end(); ++i1)
    {
    	last = (*i1)->codeGen(context);
    }

    return last;
}


Value *intargdeclaration::codeGen(CodeGenContext& context)
{
	Value *v;
	AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}

Value *booleanargdeclaration::codeGen(CodeGenContext& context)
{
	Value *v;
	AllocaInst *alloc = new AllocaInst( Type::getInt1Ty(getGlobalContext()) , variablename , context.currentBlock());
	context.locals()[variablename] = alloc;
	v=alloc;
	return v;
}



Value *methoddeclaration::codeGen(CodeGenContext& context)
{
	
	

	vector<Type*> argTypes;
	
	list<argdeclaration*>::iterator i;
	for (i = args->begin(); i != args->end(); i++) {
		if((*i)->type()==1)
		{
			argTypes.push_back(Type::getInt32Ty(getGlobalContext()));
		}
		else if((*i)->type()==2)
		{
			argTypes.push_back(Type::getInt1Ty(getGlobalContext()));
		}
	}	
	
	FunctionType *ftype;

	if(type.compare("Int")==0)
	{
			
		 ftype = FunctionType::get(Type::getInt32Ty(getGlobalContext()), makeArrayRef(argTypes), false);
	}
	else if(type.compare("Boolean")==0)
	{
		ftype = FunctionType::get(Type::getInt1Ty(getGlobalContext()), makeArrayRef(argTypes), false);
	}
	else if(type.compare("Void")==0)
	{
		ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), makeArrayRef(argTypes), false);
	}
	
	

	Function *function = Function::Create(ftype, GlobalValue::InternalLinkage, name , context.module);
	
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", function, 0);

	context.pushBlock(bblock);


	Function::arg_iterator argsValues = function->arg_begin();
    Value* argumentValue;
    	
	for (i = args->begin(); i != args->end(); i++) {
		(**i).codeGen(context);
		
		argumentValue = argsValues++;
		argumentValue->setName((*i)->variablename.c_str());
		StoreInst *inst = new StoreInst(argumentValue, context.locals()[(*i)->variablename], false, bblock);
	}



	/*for (i = args->begin(); i != args->end(); i++) {
		if((*i)->type()==1)
		{		
			AllocaInst *alloc = new AllocaInst( Type::getInt32Ty(getGlobalContext()) , (*i)->variablename , context.currentBlock());
			context.locals()[(*i)->variablename] = alloc;
		}
		else if((*i)->type()==2)
		{	
			AllocaInst *alloc = new AllocaInst( Type::getInt1Ty(getGlobalContext()) , (*i)->variablename , context.currentBlock());
			context.locals()[(*i)->variablename] = alloc;
		}
	}*/	

	blk->codeGen(context);
	context.popBlock();

	return function;


}

