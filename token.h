//---------------------------------------------------------------------------

#ifndef tokenH
#define tokenH

#include "const.h"

/*
����� Token, � ��� ���������� ����������� ����� - ��������� � �����
*/
class Token
{
	public:
		Token(const Operator, double num=0);		//�����������
		~Token();       							//����������
		Operator getType() const;                   //��������� ���� ������
		double getNum() const;                      //��������� �����
		void setNum(double num);					//��������� ��������
	private:
		Operator __type;     				//��� ������, �� Operator
		double __num;   							//����� ���� ��� ����� �� ����
};

//---------------------------------------------------------------------------
#endif
