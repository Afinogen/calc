//---------------------------------------------------------------------------

#pragma hdrstop

#include "token.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Token::Token(const Operator op, double num)
{
	__type=op;
	__num=num;
}

Token::~Token()
{

}

Operator Token::getType() const
{
	return __type;
}

double Token::getNum() const
{
	return __num;
}
//
void Token::setNum(double num)
{
    __num=num;
}
