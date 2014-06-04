//---------------------------------------------------------------------------

#ifndef calcH
#define calcH

#include "tokens.h"
#include <math.h>
//---------------------------------------------------------------------------
//����� ����������
class Calc
{
	public:
		Calc();                             //�����������
		Calc(Tokens *exp);                  //�� ��
		~Calc();                            //����������
		Errors run();                       //������ ����������
		double getResult() const;           //��������� ����������
	private:
		Errors minus();                     //�������� �����
		Errors plus();                      //�������� ����
		Errors mul();                       //�������� ���������
		Errors div();                       //�������� �������
		Errors sin();                       //���������� sin
		Errors cos();                       //���������� cos
		Errors tg();                        //���������� tg
		Errors ctg();                       //���������� ctg
		Errors exp();                       //���������� � �������
		Errors e();                         //����������
		Tokens *__Exp;                      //��������� ��� ����������
		Tokens *__stack;                    //����
		double __result;                    //���������
};

#endif
