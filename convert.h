//---------------------------------------------------------------------------

#ifndef convertH
#define convertH

#include <string.h>
#include <stdlib.h>
#include "token.h"

//---------------------------------------------------------------------------
//����� ����������� ������
class Convert
{
	public:
		Convert();
		~Convert();
		Operator OpToConstOp(const char *op);        //�������������� ����������, �� Operator
		char *ConstOpToOp(Operator op) const;        //��������
		bool isDigit(const char s) const;            //�������� �� �����
		bool isSymbol(const char s) const;           //�������� �� ������
		double toDouble(const char *num);			 //�������������� ������ � double
		char *toChar(char s) const;                  //�������������� � char*
	private:
};

#endif
