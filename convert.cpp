//---------------------------------------------------------------------------

#pragma hdrstop

#include "convert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//Конструктор класса  -------------------------------------------------------
Convert::Convert()
{

}
//Деструктор ----------------------------------------------------------------
Convert::~Convert()
{

}
//Переобразование операторов в перечисление Oprator -------------------------
Operator Convert::OpToConstOp(const char *op)
{
	if (strcmp(op,"-")==0)  return MINUS;
	else if (strcmp(op,"+")==0)  return PLUS;
	else if (strcmp(op,"sin")==0)  return SIN;
	else if (strcmp(op,"cos")==0)  return COS;
	else if (strcmp(op,"tg")==0)  return TG;
	else if (strcmp(op,"ctg")==0)  return CTG;
	else if (strcmp(op,"log")==0)  return LOG;
	else if (strcmp(op,"e^")==0)  return E;
	else if (strcmp(op,"^")==0)  return EXP;
	else if (strcmp(op,"*")==0)  return MUL;
	else if (strcmp(op,"/")==0)  return DIV;
	else if (strcmp(op,"|")==0)  return MOD;
	else if (strcmp(op,"(")==0)  return OPEN_BKT;
	else if (strcmp(op,")")==0)  return CLOSE_BKT;
	else if (strcmp(op,"pi")==0)  return PI;
	else return OP_ERROR;
}
//Проверка является ли символ числом ----------------------------------------
bool Convert::isDigit(const char s) const
{
	if ((s>='0' && s<='9') || s=='.') return true;
	else return false;
}
//Конвертируем строку в число -----------------------------------------------
double Convert::toDouble(const char *num)
{
	char* end_ptr;
	return strtod(num, &end_ptr);
	/*long val = strtol(num, &end_ptr, 10);
	if (*end_ptr)
	{
		// Сигнализируем об ошибке в строке
	}
	if ((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE)
	{
		// Сигнализируем о переполнении
	}*/
}
//Функция проверяет является ли символ буквой ------------------------------
bool Convert::isSymbol(const char s) const
{
	if (s>='a' && s<='z') return true;
	else return false;
}
//Конвертация константных значений операторов в строку ---------------------
char *Convert::ConstOpToOp(Operator op) const
{
	if (op==MINUS) return "-";
	else if (op==PLUS)  return "+";
	else if (op==SIN)  return "sin";
	else if (op==COS)  return "cos";
	else if (op==TG)  return "tg";
	else if (op==CTG)  return "ctg";
	else if (op==LOG)  return "log";
	else if (op==E)  return "e^";
	else if (op==EXP)  return "^";
	else if (op==MUL)  return "*";
	else if (op==DIV)  return "/";
	else if (op==MOD)  return "|";
	else if (op==OPEN_BKT)  return "(";
	else if (op==CLOSE_BKT)  return ")";
	else if (op==PI)  return "pi";
	else return NULL;
}
//Преобразование char в char*, т.к. приведение типов не корректно работает -
char *Convert::toChar(char s) const
{
	char *tmp=new char[2];
	tmp[0]=s;
	tmp[1]='\0';
	return tmp;
}
