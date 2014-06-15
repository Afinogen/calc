//---------------------------------------------------------------------------

#ifndef polizH
#define polizH

#include "tokens.h"
#include "convert.h"
#include "const.h"
#include <vector>
#include <string>

//---------------------------------------------------------------------------
using namespace std;

//����� ����������� ��������� � �������� �������� ������
class Poliz: public Convert
{
	public:
		Poliz();
		~Poliz();
		void setExpression(char *exp);
		Errors Parser();
		Tokens *getOutExp() const;
	private:
		void clearTmp();			//������� ��������� ����������
		Errors addTmpToOutExp();		//������� ��� ������������ � __tmp � ��������� ��� � �������� ���������
		void addOpToOutExp(Operator op);
		Errors checkToken(Operator op);
		char *__exp;
		vector<Operator> __stack;
		Tokens *__outExp;
		char *__tmp;				//��������� ����������
		int __pos;
		bool __mod;
		Operator __lastToken;
};

#endif
