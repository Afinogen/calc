//---------------------------------------------------------------------------

#pragma hdrstop

#include "calc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// онструтор
Calc::Calc()
{
}
// онструктор
Calc::Calc(Tokens *exp)
{
	__Exp=exp;               //сохран€ем выражение дл€ вычислени€
	__stack=new Tokens();    //создаем стек
	__result=0;
}
//ƒеструктор
Calc::~Calc()
{
	delete __stack;           //уничтожение стека
}
//ѕолучение результата
double Calc::getResult() const
{
	return __result;
}
//«ыпуск вычислени€
Errors Calc::run()
{
	if (__Exp->getSize()>0)     //есть что считать
	{
		Errors err;             //переменна€ дл€ ошибок
		for(int i=0;i<__Exp->getSize();i++)   //проход в цикле по выражению
		{
			if (__Exp->getToken(i)->getType()==NUM) __stack->addToken(NUM,__Exp->getToken(i)->getNum());  //если элемент выражени€ число - заносим его в стек
			else if (__Exp->getToken(i)->getType()==MINUS)   //нашли операцию минус
			{
				err=minus();                                //выполн€ем ее
				if (err!=OK) return err;                    //проверка ошибки
			}
			else if (__Exp->getToken(i)->getType()==PLUS)
			{
				err=plus();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==MUL)
			{
				err=mul();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==DIV)
			{
				err=div();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==SIN)
			{
				err=this->sin();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==EXP)
			{
				err=exp();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==E)
			{
				err=e();
				if (err!=OK) return err;
			}
		}
	}
	if (__stack->getSize()==1)                         //выражение вычислено, в стеке должно быть 1 число - редультат
	{
		__result=__stack->getToken(0)->getNum();
		return OK;
	}
	else return ERROR_CALC;                         //иначе ошибка, не правильно посчитал (
}
//ќпераци€ минус
Errors Calc::minus()
{
	int StackSize=__stack->getSize();   //получение размера стека
	if (StackSize>=2)                  //есть 2 операнда
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()-__stack->getToken(StackSize-1)->getNum();   //вычисление
		__stack->getToken(StackSize-2)->setNum(tmp);        //записываем результат
		__stack->deleteToken(StackSize-1);                  //удал€ем не нужный операнд
	}
	else return NOT_FOUND_2_PARAM;                       //иначе ошибка
	return OK;
}
//ќпераци€ плюс
Errors Calc::plus()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()+__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//умножение
Errors Calc::mul()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()*__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//деление
Errors Calc::div()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
        if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=__stack->getToken(StackSize-2)->getNum()/__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//синус
Errors Calc::sin()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::sin(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//косинус
Errors Calc::cos()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::cos(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//тангенс
Errors Calc::tg()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::tan(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//котангенс
Errors Calc::ctg()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::cos(__stack->getToken(StackSize-1)->getNum())/std::sin(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//возведение в степень
Errors Calc::exp()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
        if (__stack->getToken(StackSize-1)->getNum()<0) return POW_2_PARAM_ERROR;
		double tmp=pow(__stack->getToken(StackSize-2)->getNum(),__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//экспонента
Errors Calc::e()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
        if (__stack->getToken(StackSize-1)->getNum()<0) return POW_2_PARAM_ERROR;
		double tmp=std::exp(__stack->getToken(StackSize-1)->getNum());
		__stack->deleteToken(StackSize-1);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
