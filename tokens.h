//---------------------------------------------------------------------------

#ifndef tokensH
#define tokensH

#include <vector>
#include "token.h"
//#include "convert.h"


using namespace std;
/*
����� ��� ������ � ��������
*/
class Tokens//: public Convert
{
	public:
		Tokens();                           		//�����������
		~Tokens();                                  //����������
		bool addToken(const Operator, double num=0); //���������� ������
		bool deleteToken(const unsigned int id);	 //�������� ������
		int getSize() const;						 //��������� ������� �������
		Token *getToken(const int id) const;		 //��������� ������
	private:
		vector<Token*> __vTokens;                   //������ �������
};

//---------------------------------------------------------------------------
#endif
