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

//Класс преобразует выражение в обратную польскую запись
class Poliz: public Convert
{
	public:
		Poliz();
		~Poliz();
		void setExpression(char *exp);
		Errors Parser();
		Tokens *getOutExp() const;
	private:
		void clearTmp();			//очистка временной переменной
		Errors addTmpToOutExp();		//смотрим что насобиралось в __tmp и добавляем это в выходное выражение
		void addOpToOutExp(Operator op);
		Errors checkToken(Operator op);
		char *__exp;
		vector<Operator> __stack;
		Tokens *__outExp;
		char *__tmp;				//временная переменная
		int __pos;
		bool __mod;
		Operator __lastToken;
};

#endif
