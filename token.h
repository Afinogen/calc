//---------------------------------------------------------------------------

#ifndef tokenH
#define tokenH

#include "const.h"

/*
класс Token, в нем содержатся разобранные слова - операторы и числа
*/
class Token
{
	public:
		Token(const Operator, double num=0);		//конструктор
		~Token();       							//деструктор
		Operator getType() const;                   //получение типа токена
		double getNum() const;                      //получение числа
		void setNum(double num);					//установка значения
	private:
		Operator __type;     				//тип токена, см Operator
		double __num;   							//число если это число по типу
};

//---------------------------------------------------------------------------
#endif
