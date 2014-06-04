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
//���������� ������ � ������ ------------------------------------------------
bool Tokens::addToken(const Operator op, double num)
{
	if (op!=OP_ERROR)    //�������� ��������
	{
		__vTokens.push_back(new Token(op,num));  //��������� � ������
		return true;
	}
	else return false;  //����� ������
}
//�������� ������ ----------------------------------------------------------
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