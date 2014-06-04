#ifndef constH
#define constH

//������������ ������������ ����������
enum Operator
{
	MINUS,      //�����
	PLUS,       //����
	MUL,        //���������
	DIV,        //�������
	EXP,        //���������� � �������
	SIN,        //sin
	COS,        //cos
	TG,         //tg
	CTG,        //ctg
	LOG,        //��������
	E,          //����������
	MOD,        //������
	OPEN_BKT,   //�������� ������
	CLOSE_BKT,  //��������
	PI,			//��....
	NUM,		//�����
	OP_ERROR    //����� �����
};
//������ ����������� ��� ������ ���������
enum Errors
{
    OK,							//��� ������
	NOT_FOUND_CLOSE_BKT,        //����������� ����������� ������
	NOT_FOUND_OPEN_BKT,			//����������� ���������� ������
	DIV_NULL,                   //������� �� 0
	NOT_FOUND_OPERATOR,         //��� ����������� ���������
	EXP_NULL,                   //��������� ������
	NOT_CORRECT_SYMBOL,  		//�� ���������� ������
	NOT_FOUND_2_PARAM,			//�� ������ 2-� ��������
	NOT_FOUND_PARAM,			//�� ������ 1-� ��������
	ERROR_CALC,                 //������ ����������
	POW_2_PARAM_ERROR           //�� ���������� �������� ��� ���������� � �������
};

#endif
