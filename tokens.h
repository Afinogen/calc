//---------------------------------------------------------------------------

#ifndef tokensH
#define tokensH

#include <vector>
#include "token.h"
//#include "convert.h"


using namespace std;
/*
класс для работы с токенами
*/
class Tokens//: public Convert
{
	public:
		Tokens();                           		//конструктор
		~Tokens();                                  //деструктор
		bool addToken(const Operator, double num=0); //добавление токена
		bool deleteToken(const unsigned int id);	 //удаление токена
		int getSize() const;						 //получение размера массива
		Token *getToken(const int id) const;		 //получение токена
	private:
		vector<Token*> __vTokens;                   //вектор токенов
};

//---------------------------------------------------------------------------
#endif
