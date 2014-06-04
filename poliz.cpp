//---------------------------------------------------------------------------

#pragma hdrstop

#include "poliz.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//����������� ---------------------------------------------------------------
Poliz::Poliz()
{
	__outExp=new Tokens();
	__tmp=new char[32];
	__exp=new char[1];
	__exp[0]='\0';
}
//���������� ----------------------------------------------------------------
Poliz::~Poliz()
{
	delete __outExp;
	delete __tmp;
	delete __exp;
	__stack.~vector();
}
//��������� ��������� -------------------------------------------------------
void Poliz::setExpression(char *exp)
{
	__exp=new char[strlen(exp)+1];
	strcpy(__exp,strlwr(exp));
}
//������ ���������� ---------------------------------------------------------
Errors Poliz::Parser()
{
	int LenStr;    //����� ������
	LenStr=strlen(__exp);
	for(int i=0;i<LenStr;i++)
	{
		if (__exp[i]==' ')    //�������� ��������
		{
			//i++;
			continue;
		}
		else if (OpToConstOp(toChar(__exp[i]))<=EXP)
		{
			Errors err=addTmpToOutExp();                      	//��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        	//���� �� ����� ������� � �������
			addOpToOutExp(OpToConstOp(toChar(__exp[i])));
			__stack.push_back(OpToConstOp(toChar(__exp[i])));   //�������� � ����
			continue;
        }
		else if (OpToConstOp(toChar(__exp[i]))==CLOSE_BKT)    //������� ����������� ������
		{
			Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������

			int j=__stack.size();                          //�������� ������ �����
			while(__stack[j]!=OPEN_BKT)                    //���� � ����� �������� ������
			{
				j--;
				if (j==-1) return NOT_FOUND_OPEN_BKT;      //������ � ����� ���, ������
			}
			__stack.erase(&__stack.at(j));                 //���� ����� ������� �� �� �����
			while(j<__stack.size())                        //������������ �� ����� � �������� ��������� ���������
			{
				__outExp->addToken(__stack[j]);
				__stack.erase(&__stack.at(j));
			}
			continue;
		}
		else if (OpToConstOp(toChar(__exp[i]))==OPEN_BKT)     //����� ����������� ������
		{
            Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������
			__stack.push_back(OPEN_BKT);            //�������� � ����
			continue;
		}
		else if (isDigit(__exp[i]) || __exp[i]=='.' || isSymbol(__exp[i]))       //������ �����, �����, �����
		{
			__tmp[strlen(__tmp)]=__exp[i];     //���������� �� ��������� ����������
			continue;
		}
		else return NOT_CORRECT_SYMBOL;
	}

	if (strlen(__tmp)>0)                  //� __tmp ���-�� ����
	{
        Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
		if (err!=OK) return err;                        //���� �� ����� ������� � �������
    }

	while(__stack.size()>0) //��������� ��� ��� �������� � �����
	{
		if (__stack[__stack.size()-1]==OPEN_BKT) return NOT_FOUND_CLOSE_BKT; //���� � ����� �������� �������� ������ ������� � �������
		__outExp->addToken(__stack[__stack.size()-1]);
		__stack.erase(&__stack.at(__stack.size()-1));
	}

	return OK;      //��� �������)
}
//������� ���������� __tmp --------------------------------------------------
void Poliz::clearTmp()
{
	for(int i=0;i<32;i++)
		__tmp[i]='\0';
}
//���������� ������ �� __tmp � �������� ��������� ---------------------------
Errors Poliz::addTmpToOutExp()
{
	if (strlen(__tmp)>0) //� ���������� ���-�� ����
	{
		if (OpToConstOp(__tmp)!=OP_ERROR)     //���� � ���������� ��������
		{
			if (OpToConstOp(__tmp)==PI)
			{
				__outExp->addToken(NUM,3.14);   //���������� �� � �������� ������
			}
			else
			{
				addOpToOutExp(OpToConstOp(__tmp));
				__stack.push_back(OpToConstOp(__tmp));
			}
		}
		else if (toDouble(__tmp))			  //���� ���������� �����
		{
			__outExp->addToken(NUM,toDouble(__tmp));
		}
		else return NOT_FOUND_OPERATOR;
		clearTmp();
	}
	return OK;     //��� �������)
}
//
Tokens *Poliz::getOutExp() const
{
    return __outExp;
}
//
void Poliz::addOpToOutExp(Operator op)
{
	if (__stack.size()>0)     //� ����� ���-�� ����
	{
		if (op==MINUS || op==PLUS)
		{
			while(__stack[__stack.size()-1]>=MINUS && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else if (op==DIV || op==MUL)
		{
			while(__stack[__stack.size()-1]>=MUL && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else
		{
            while(__stack[__stack.size()-1]>=EXP && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
        }
	 }
}