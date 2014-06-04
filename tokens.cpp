//---------------------------------------------------------------------------

#pragma hdrstop

#include "tokens.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Tokens::Tokens()
{

}

Tokens::~Tokens()
{
	__vTokens.~vector();
}
//Добавление токена в вектор ------------------------------------------------
bool Tokens::addToken(const Operator op, double num)
{
	if (op!=OP_ERROR)    //оператор валидный
	{
		__vTokens.push_back(new Token(op,num));  //добавляем в массив
		return true;
	}
	else return false;  //иначе ошибка
}
//Удаление токена ----------------------------------------------------------
bool Tokens::deleteToken(const unsigned int id)
{
	if (id<__vTokens.size())
	{
		__vTokens.erase(&__vTokens.at(id));
		return true;
	}
	else return false;
}
//
int Tokens::getSize() const
{
	return __vTokens.size();
}
//
Token *Tokens::getToken(const int id) const
{
    return __vTokens[id];
}