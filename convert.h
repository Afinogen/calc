//---------------------------------------------------------------------------

#ifndef convertH
#define convertH

#include <string.h>
#include <stdlib.h>
#include "token.h"

//---------------------------------------------------------------------------
//Класс конвертации данных
class Convert
{
	public:
		Convert();
		~Convert();
		Operator OpToConstOp(const char *op);        //преобразование операторов, см Operator
		char *ConstOpToOp(Operator op) const;        //Обратная
		bool isDigit(const char s) const;            //проверка на число
		bool isSymbol(const char s) const;           //проверка на символ
		double toDouble(const char *num);			 //преобразование строки в double
		char *toChar(char s) const;                  //преобразование в char*
	private:
};

#endif
