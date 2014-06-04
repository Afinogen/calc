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
	__exp=new char[1];
	__exp[0]='\0';
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
}
//Разбор выражениея ---------------------------------------------------------
Errors Poliz::Parser()
{
	int LenStr;    //длина строки
	LenStr=strlen(__exp);
	for(int i=0;i<LenStr;i++)
	{
		if (__exp[i]==' ')    //удаление пробелов
		{
			//i++;
			continue;
		}
		else if (OpToConstOp(toChar(__exp[i]))<=EXP)
		{
			Errors err=addTmpToOutExp();                      	//добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        	//если не вышло выходим с ошибкой
			addOpToOutExp(OpToConstOp(toChar(__exp[i])));
			__stack.push_back(OpToConstOp(toChar(__exp[i])));   //Положили в стек
			continue;
        }
		else if (OpToConstOp(toChar(__exp[i]))==CLOSE_BKT)    //Найдена закрывающая скобка
		{
			Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой

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
			continue;
		}
		else if (OpToConstOp(toChar(__exp[i]))==OPEN_BKT)     //нашли открывающую скобку
		{
            Errors err=addTmpToOutExp();                       //добавляем из __tmp в выходное выражение
			if (err!=OK) return err;                        //если не вышло выходим с ошибкой
			__stack.push_back(OPEN_BKT);            //Положили в стек
			continue;
		}
		else if (isDigit(__exp[i]) || __exp[i]=='.' || isSymbol(__exp[i]))       //символ цифра, точка, буква
		{
			__tmp[strlen(__tmp)]=__exp[i];     //записываем во временную переменную
			continue;
		}
		else return NOT_CORRECT_SYMBOL;
	}

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
		if (OpToConstOp(__tmp)!=OP_ERROR)     //если в переменной оператор
		{
			if (OpToConstOp(__tmp)==PI)
			{
				__outExp->addToken(NUM,3.14);   //записываем их в выходную строку
			}
			else
			{
				addOpToOutExp(OpToConstOp(__tmp));
				__stack.push_back(OpToConstOp(__tmp));
			}
		}
		else if (toDouble(__tmp))			  //если переменная число
		{
			__outExp->addToken(NUM,toDouble(__tmp));
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
			while(__stack[__stack.size()-1]>=MINUS && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else if (op==DIV || op==MUL)
		{
			while(__stack[__stack.size()-1]>=MUL && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else
		{
            while(__stack[__stack.size()-1]>=EXP && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //выталкиваем из стека операции
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //записываем их в выходную строку
				__stack.erase(&__stack.at(__stack.size()-1));
			}
        }
	 }
}