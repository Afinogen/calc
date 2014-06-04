//---------------------------------------------------------------------------

#pragma hdrstop

#include "calc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//����������
Calc::Calc()
{
}
//�����������
Calc::Calc(Tokens *exp)
{
	__Exp=exp;               //��������� ��������� ��� ����������
	__stack=new Tokens();    //������� ����
	__result=0;
}
//����������
Calc::~Calc()
{
	delete __stack;           //����������� �����
}
//��������� ����������
double Calc::getResult() const
{
	return __result;
}
//������ ����������
Errors Calc::run()
{
	if (__Exp->getSize()>0)     //���� ��� �������
	{
		Errors err;             //���������� ��� ������
		for(int i=0;i<__Exp->getSize();i++)   //������ � ����� �� ���������
		{
			if (__Exp->getToken(i)->getType()==NUM) __stack->addToken(NUM,__Exp->getToken(i)->getNum());  //���� ������� ��������� ����� - ������� ��� � ����
			else if (__Exp->getToken(i)->getType()==MINUS)   //����� �������� �����
			{
				err=minus();                                //��������� ��
				if (err!=OK) return err;                    //�������� ������
			}
			else if (__Exp->getToken(i)->getType()==PLUS)
			{
				err=plus();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==MUL)
			{
				err=mul();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==DIV)
			{
				err=div();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==SIN)
			{
				err=this->sin();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==EXP)
			{
				err=exp();
				if (err!=OK) return err;
			}
			else if (__Exp->getToken(i)->getType()==E)
			{
				err=e();
				if (err!=OK) return err;
			}
		}
	}
	if (__stack->getSize()==1)                         //��������� ���������, � ����� ������ ���� 1 ����� - ���������
	{
		__result=__stack->getToken(0)->getNum();
		return OK;
	}
	else return ERROR_CALC;                         //����� ������, �� ��������� �������� (
}
//�������� �����
Errors Calc::minus()
{
	int StackSize=__stack->getSize();   //��������� ������� �����
	if (StackSize>=2)                  //���� 2 ��������
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()-__stack->getToken(StackSize-1)->getNum();   //����������
		__stack->getToken(StackSize-2)->setNum(tmp);        //���������� ���������
		__stack->deleteToken(StackSize-1);                  //������� �� ������ �������
	}
	else return NOT_FOUND_2_PARAM;                       //����� ������
	return OK;
}
//�������� ����
Errors Calc::plus()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()+__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//���������
Errors Calc::mul()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
		double tmp=__stack->getToken(StackSize-2)->getNum()*__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//�������
Errors Calc::div()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
        if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=__stack->getToken(StackSize-2)->getNum()/__stack->getToken(StackSize-1)->getNum();
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);	
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//�����
Errors Calc::sin()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::sin(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//�������
Errors Calc::cos()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::cos(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//�������
Errors Calc::tg()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::tan(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//���������
Errors Calc::ctg()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
		//if (__stack->getToken(StackSize-1)->getNum()==0) return DIV_NULL;
		double tmp=std::cos(__stack->getToken(StackSize-1)->getNum())/std::sin(__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-1)->setNum(tmp);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
//���������� � �������
Errors Calc::exp()
{
	int StackSize=__stack->getSize();
	if (StackSize>=2)
	{
        if (__stack->getToken(StackSize-1)->getNum()<0) return POW_2_PARAM_ERROR;
		double tmp=pow(__stack->getToken(StackSize-2)->getNum(),__stack->getToken(StackSize-1)->getNum());
		__stack->getToken(StackSize-2)->setNum(tmp);
		__stack->deleteToken(StackSize-1);
	}
	else return NOT_FOUND_2_PARAM;
	return OK;
}
//����������
Errors Calc::e()
{
	int StackSize=__stack->getSize();
	if (StackSize>=1)
	{
        if (__stack->getToken(StackSize-1)->getNum()<0) return POW_2_PARAM_ERROR;
		double tmp=std::exp(__stack->getToken(StackSize-1)->getNum());
		__stack->deleteToken(StackSize-1);
	}
	else return NOT_FOUND_PARAM;
	return OK;
}
