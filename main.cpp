#include <vcl.h>
//#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "poliz.h"
#include "calc.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char *str=new char[2];
	do
	{
		cout<<"Input exp: ";
		cin.getline(str,255);
		cout<<endl;
		Poliz *p=new Poliz();
		p->setExpression(str);
		Errors err=p->Parser();
		if (err!=OK)
		{
			cout<<"Errors:";
			if (err==NOT_FOUND_CLOSE_BKT) cout<<"NOT_FOUND_CLOSE_BKT";   //Отсутствует закрывающая скобка
			else if (err==NOT_FOUND_OPEN_BKT) cout<<"NOT_FOUND_OPEN_BKT";			//Отсутствует отрывающая скобка
			else if (err==DIV_NULL) cout<<"DIV_NULL";                   //деление на 0
			else if (err==NOT_FOUND_OPERATOR) cout<<"NOT_FOUND_OPERATOR";         //Нет соотвествия оператору
			else if (err==EXP_NULL) cout<<"EXP_NULL";                   //выражение пустое
			else if (err==NOT_CORRECT_SYMBOL) cout<<"NOT_CORRECT_SYMBOL";			//не корректный символ
			else cout<<"SYNTAX_ERROR";
			cout<<endl;
		}
		cout<<"Poliz: ";
		Tokens *ptr=p->getOutExp();
		for(int i=0;i<ptr->getSize();i++)
		{
			if (ptr->getToken(i)->getType()!=NUM) cout<<p->ConstOpToOp(ptr->getToken(i)->getType());
			else cout<<ptr->getToken(i)->getNum();
			cout<<" ";
		}
		cout<<endl;
		if (err==OK)
		{
			Calc *cptr=new Calc(ptr);
			cptr->run();
			cout<<"Result: "<<cptr->getResult();
			delete cptr;
			cout<<endl;
		}
		delete ptr;
		cout<<"Press any key. Escape - exit"<<endl<<endl;
	}while(getch()!=VK_ESCAPE);
	return 0;
}
