//---------------------------------------------------------------------------

#pragma hdrstop

#include "poliz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//Конструктор ---------------------------------------------------------------
Poliz::Poliz()
{
	__outExp=new Tokens();
	__tmp=new char[32];
	__lastToken=NULL;
	//__exp=new char[1];
	//__exp[0]='\0';
}
//Деструктор ----------------------------------------------------------------
Poliz::~Poliz()
{
	delete __outExp;
	delete __tmp;
	delete __exp;
	__stack.~vector();
}
//Установка выражения -------------------------------------------------------
void Poliz::setExpression(char *exp)
{
	__exp=new char[strlen(exp)+1];
	strcpy(__exp,strlwr(exp));
	__exp[strlen(exp)+1]='\0';
}
//Разбор выражениея ---------------------------------------------------------
Errors Poliz::Parser()
{
	int LenStr;    //длина строки
	LenStr=strlen(__exp);
	__mod=false;
	for(__pos=0;__pos<LenStr;__pos++)
	{
		if (__exp[__pos]==' ')    //удаление пробелов
		{
			//i++;
			continue;
		}
		else if (__exp[__pos]=='|')
		{
            Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой
			if (__mod==false)
			{
				__stack.push_back(MOD);
				__outExp->addToken(MOD);
				__mod=true;
			}
			else
			{
				int j=__stack.size();                          //получаем разсер стека
				while(__stack[j]!=MOD)                    //ищем в стеке открытую скобку
				{
					j--;
				}
				__stack.erase(&__stack.at(j));                 //Если нащли удаляем ее из стека
				while(j<__stack.size())                        //Переписыааем из стека в выходное выражение операторы
				{
					__outExp->addToken(__stack[j]);
					__stack.erase(&__stack.at(j));
				}
				__outExp->addToken(MOD);
				__mod=false;
			}
			__lastToken=MOD;
			continue;
		}

		else if (OpToConstOp(toChar(__exp[__pos]))<=EXP)
		{
			if (__tmp[0]=='e' && __exp[__pos]=='^')
			{
				__tmp[1]='^';
				Errors err=addTmpToOutExp();                      	//добавляем из __tmp в выходное выражение
				if (err!=OK) return err;                        	//если не вышло выходим с ошибкой
				continue;
            }
			Errors err=addTmpToOutExp();                      	//добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        	//если не вышло выходим с ошибкой

			Operator op=OpToConstOp(toChar(__exp[__pos]));

			if (checkToken(op)!=OK) return checkToken(op);
			addOpToOutExp(op);
			__stack.push_back(op);   //Положили в стек
			__lastToken=op;
			continue;
        }
		else if (OpToConstOp(toChar(__exp[__pos]))==CLOSE_BKT)    //Найдена закрывающая скобка
		{
			Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой

			if (checkToken(CLOSE_BKT)!=OK) return checkToken(CLOSE_BKT);

			int j=__stack.size();                          //получаем разсер стека
			while(__stack[j]!=OPEN_BKT)                    //ищем в стеке открытую скобку
			{
				j--;
				if (j==-1) return NOT_FOUND_OPEN_BKT;      //Скобки в стеке нет, ошибка
			}
			__stack.erase(&__stack.at(j));                 //Если нащли удаляем ее из стека
			while(j<__stack.size())                        //Переписыааем из стека в выходное выражение операторы
			{
				__outExp->addToken(__stack[j]);
				__stack.erase(&__stack.at(j));
			}
			__lastToken=CLOSE_BKT;
			continue;
		}
		else if (OpToConstOp(toChar(__exp[__pos]))==OPEN_BKT)     //нашли открывающую скобку
		{
			Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой
			if (checkToken(OPEN_BKT)!=OK) return checkToken(OPEN_BKT);
			__stack.push_back(OPEN_BKT);            //Положили в стек
			__lastToken=OPEN_BKT;
			continue;
		}
		else if (isDigit(__exp[__pos]) || __exp[__pos]=='.' || isSymbol(__exp[__pos]) || __exp[__pos]=='^')       //символ цифра, точка, буква
		{
			__tmp[strlen(__tmp)]=__exp[__pos];     //записываем во временную переменную
			continue;
		}
		else if (__exp[__pos]==',')
		{
            Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой

			int j=__stack.size();                          //получаем разсер стека
			while(__stack[j]!=OPEN_BKT)                    //ищем в стеке открытую скобку
			{
				j--;
				if (j==-1) return NOT_FOUND_OPEN_BKT;      //Скобки в стеке нет, ошибка
			}
			j++;
			while(j<__stack.size())                        //Переписыааем из стека в выходное выражение операторы
			{
				__outExp->addToken(__stack[j]);
				__stack.erase(&__stack.at(j));
			}
			__lastToken=CLOSE_BKT;
			continue;
        }
		else return NOT_CORRECT_SYMBOL;
	}

    if (__mod) return NOT_FOUND_CLOSE_MOD;

	if (strlen(__tmp)>0)                  //в __tmp что-то есть
	{
        Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
		if (err!=OK) return err;                        //если не вышло выходим с ошибкой
    }

	while(__stack.size()>0) //выкидыаем все что осталось в стеке
	{
		if (__stack[__stack.size()-1]==OPEN_BKT) return NOT_FOUND_CLOSE_BKT; //если в стеке осталась открытая скобка возврат с ошибкой
		__outExp->addToken(__stack[__stack.size()-1]);
		__stack.erase(&__stack.at(__stack.size()-1));
	}

	return OK;      //все отлично)
}
//Очистка переменной __tmp --------------------------------------------------
void Poliz::clearTmp()
{
	for(int i=0;i<32;i++)
		__tmp[i]='\0';
}
//Добавление данных из __tmp в выходное выражение ---------------------------
Errors Poliz::addTmpToOutExp()
{
	if (strlen(__tmp)>0) //в переменной что-то есть
	{
		if (__tmp[0]=='e' && __exp[__pos]=='^') __tmp[1]='^';
		if (OpToConstOp(__tmp)!=OP_ERROR)     //если в переменной оператор
		{
			if (OpToConstOp(__tmp)==PI)
			{
				__outExp->addToken(NUM,3.14);   //записываем их в выходную строку
				__lastToken=PI;
			}
			else
			{
				addOpToOutExp(OpToConstOp(__tmp));
				__stack.push_back(OpToConstOp(__tmp));
				__lastToken=OpToConstOp(__tmp);
			}
		}
		else if (__tmp[0]=='0' && strlen(__tmp)==1)
		{
			__outExp->addToken(NUM,0);
			__lastToken=NUM;
        }
		else if (toDouble(__tmp))			  //если переменная число
		{
			__outExp->addToken(NUM,toDouble(__tmp));
			__lastToken=NUM;
		}
		else return NOT_FOUND_OPERATOR;
		clearTmp();
	}
	return OK;     //все отлично)
}
//
Tokens *Poliz::getOutExp() const
{
    return __outExp;
}
//
void Poliz::addOpToOutExp(Operator op)
{
	if (__stack.size()>0)     //в стека что-то есть
	{
		if (op==MINUS || op==PLUS)
		{
			while(__stack[__stack.size()-1]>=MINUS && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else if (op==DIV || op==MUL)
		{
			while(__stack[__stack.size()-1]>=MUL && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else
		{
			while(__stack[__stack.size()-1]>=EXP && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
        }
	 }
}
//
Errors Poliz::checkToken(Operator op)
{
	if (op==OPEN_BKT && __lastToken==NUM) return SYNTAX_ERROR;      //23(
	else if (op==MINUS && (__lastToken==OPEN_BKT || __lastToken==NULL))            //(-23   -2
	{
		__outExp->addToken(NUM,0);
		__lastToken=NUM;
		return OK;
    }
	else if (op==CLOSE_BKT && (__lastToken!=CLOSE_BKT && __lastToken!=NUM && __lastToken!=MOD)) return SYNTAX_ERROR; //+)
	else if (op<MOD && __lastToken<MOD) return  MANY_OPERATORS; //++-*
	else return OK;
}