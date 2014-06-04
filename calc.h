//---------------------------------------------------------------------------

#ifndef calcH
#define calcH

#include "tokens.h"
#include <math.h>
//---------------------------------------------------------------------------
// ласс вычислений
class Calc
{
	public:
		Calc();                             // онструктор
		Calc(Tokens *exp);                  //он же
		~Calc();                            //ƒеструктор
		Errors run();                       //запуск вычмслений
		double getResult() const;           //получение результата
	private:
		Errors minus();                     //операци€ минус
		Errors plus();                      //операци€ плюс
		Errors mul();                       //операци€ умножени€
		Errors div();                       //операци€ делени€
		Errors sin();                       //вычисление sin
		Errors cos();                       //вычисление cos
		Errors tg();                        //вычисление tg
		Errors ctg();                       //вычисление ctg
		Errors exp();                       //возведение в степень
		Errors e();                         //экспонента
		Tokens *__Exp;                      //выражение дл€ вычислени€
		Tokens *__stack;                    //стек
		double __result;                    //результат
};

#endif
