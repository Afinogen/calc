#ifndef constH
#define constH

//перечисление используемых операторов
enum Operator
{
	MINUS,      //минус
	PLUS,       //плюс
	MUL,        //умножение
	DIV,        //деление
	EXP,        //возведение в степень
	SIN,        //sin
	COS,        //cos
	TG,         //tg
	CTG,        //ctg
	LOG,        //логарифм
	E,          //экспонента
	MOD,        //модуль
	OPEN_BKT,   //открытая скобка
	CLOSE_BKT,  //закрытая
	PI,			//пи....
	NUM,		//число
	OP_ERROR    //левак пошел
};
//Ошибки возникающие при работе программы
enum Errors
{
    OK,							//без ошибок
	NOT_FOUND_CLOSE_BKT,        //Отсутствует закрывающая скобка
	NOT_FOUND_OPEN_BKT,			//Отсутствует отрывающая скобка
	DIV_NULL,                   //деление на 0
	NOT_FOUND_OPERATOR,         //Нет соотвествия оператору
	EXP_NULL,                   //выражение пустое
	NOT_CORRECT_SYMBOL,  		//не корректный символ
	NOT_FOUND_2_PARAM,			//не найден 2-й параметр
	NOT_FOUND_PARAM,			//не найден 1-й параметр
	ERROR_CALC,                 //ошибка вычисления
	POW_2_PARAM_ERROR           //не корректный параметр для возведения в степень
};

#endif
