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
	__lastToken=NULL;
	//__exp=new char[1];
	//__exp[0]='\0';
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
	__exp[strlen(exp)+1]='\0';
}
//������ ���������� ---------------------------------------------------------
Errors Poliz::Parser()
{
	int LenStr;    //����� ������
	LenStr=strlen(__exp);
	__mod=false;
	for(__pos=0;__pos<LenStr;__pos++)
	{
		if (__exp[__pos]==' ')    //�������� ��������
		{
			//i++;
			continue;
		}
		else if (__exp[__pos]=='|')
		{
            Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������
			if (__mod==false)
			{
				__stack.push_back(MOD);
				__outExp->addToken(MOD);
				__mod=true;
			}
			else
			{
				int j=__stack.size();                          //�������� ������ �����
				while(__stack[j]!=MOD)                    //���� � ����� �������� ������
				{
					j--;
				}
				__stack.erase(&__stack.at(j));                 //���� ����� ������� �� �� �����
				while(j<__stack.size())                        //������������ �� ����� � �������� ��������� ���������
				{
					__outExp->addToken(__stack[j]);
					__stack.erase(&__stack.at(j));
				}
				__outExp->addToken(MOD);
				__mod=false;
			}
			__lastToken=MOD;
			continue;
		}

		else if (OpToConstOp(toChar(__exp[__pos]))<=EXP)
		{
			if (__tmp[0]=='e' && __exp[__pos]=='^')
			{
				__tmp[1]='^';
				Errors err=addTmpToOutExp();                      	//��������� �� __tmp � �������� ���������
				if (err!=OK) return err;                        	//���� �� ����� ������� � �������
				continue;
            }
			Errors err=addTmpToOutExp();                      	//��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        	//���� �� ����� ������� � �������

			Operator op=OpToConstOp(toChar(__exp[__pos]));

			if (checkToken(op)!=OK) return checkToken(op);
			addOpToOutExp(op);
			__stack.push_back(op);   //�������� � ����
			__lastToken=op;
			continue;
        }
		else if (OpToConstOp(toChar(__exp[__pos]))==CLOSE_BKT)    //������� ����������� ������
		{
			Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������

			if (checkToken(CLOSE_BKT)!=OK) return checkToken(CLOSE_BKT);

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
			__lastToken=CLOSE_BKT;
			continue;
		}
		else if (OpToConstOp(toChar(__exp[__pos]))==OPEN_BKT)     //����� ����������� ������
		{
			Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������
			if (checkToken(OPEN_BKT)!=OK) return checkToken(OPEN_BKT);
			__stack.push_back(OPEN_BKT);            //�������� � ����
			__lastToken=OPEN_BKT;
			continue;
		}
		else if (isDigit(__exp[__pos]) || __exp[__pos]=='.' || isSymbol(__exp[__pos]) || __exp[__pos]=='^')       //������ �����, �����, �����
		{
			__tmp[strlen(__tmp)]=__exp[__pos];     //���������� �� ��������� ����������
			continue;
		}
		else if (__exp[__pos]==',')
		{
            Errors err=addTmpToOutExp();                       //��������� �� __tmp � �������� ���������
			if (err!=OK) return err;                        //���� �� ����� ������� � �������

			int j=__stack.size();                          //�������� ������ �����
			while(__stack[j]!=OPEN_BKT)                    //���� � ����� �������� ������
			{
				j--;
				if (j==-1) return NOT_FOUND_OPEN_BKT;      //������ � ����� ���, ������
			}
			j++;
			while(j<__stack.size())                        //������������ �� ����� � �������� ��������� ���������
			{
				__outExp->addToken(__stack[j]);
				__stack.erase(&__stack.at(j));
			}
			__lastToken=CLOSE_BKT;
			continue;
        }
		else return NOT_CORRECT_SYMBOL;
	}

    if (__mod) return NOT_FOUND_CLOSE_MOD;

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
		if (__tmp[0]=='e' && __exp[__pos]=='^') __tmp[1]='^';
		if (OpToConstOp(__tmp)!=OP_ERROR)     //���� � ���������� ��������
		{
			if (OpToConstOp(__tmp)==PI)
			{
				__outExp->addToken(NUM,3.14);   //���������� �� � �������� ������
				__lastToken=PI;
			}
			else
			{
				addOpToOutExp(OpToConstOp(__tmp));
				__stack.push_back(OpToConstOp(__tmp));
				__lastToken=OpToConstOp(__tmp);
			}
		}
		else if (__tmp[0]=='0' && strlen(__tmp)==1)
		{
			__outExp->addToken(NUM,0);
			__lastToken=NUM;
        }
		else if (toDouble(__tmp))			  //���� ���������� �����
		{
			__outExp->addToken(NUM,toDouble(__tmp));
			__lastToken=NUM;
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
			while(__stack[__stack.size()-1]>=MINUS && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else if (op==DIV || op==MUL)
		{
			while(__stack[__stack.size()-1]>=MUL && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
		}
		else
		{
			while(__stack[__stack.size()-1]>=EXP && __stack.size()>0 && __stack[__stack.size()-1]!=OPEN_BKT && __stack[__stack.size()-1]!=MOD) //����������� �� ����� ��������
			{
				__outExp->addToken(__stack[__stack.size()-1]);   //���������� �� � �������� ������
				__stack.erase(&__stack.at(__stack.size()-1));
			}
        }
	 }
}
//
Errors Poliz::checkToken(Operator op)
{
	if (op==OPEN_BKT && __lastToken==NUM) return SYNTAX_ERROR;      //23(
	else if (op==MINUS && (__lastToken==OPEN_BKT || __lastToken==NULL))            //(-23   -2
	{
		__outExp->addToken(NUM,0);
		__lastToken=NUM;
		return OK;
    }
	else if (op==CLOSE_BKT && (__lastToken!=CLOSE_BKT && __lastToken!=NUM && __lastToken!=MOD)) return SYNTAX_ERROR; //+)
	else if (op<MOD && __lastToken<MOD) return  MANY_OPERATORS; //++-*
	else return OK;
}