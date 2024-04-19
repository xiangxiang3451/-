#pragma once
#include <iostream>
#include <string>

using namespace std;

enum OPSType
{
	IDE,			//переменная
	MAS,			//массив
	NUMBER,			//число
	SIGN,			//операция
	POINT,			//точка перехода
	IND,			//индексатор
	JUMPFALSE,		//метка для "ложь"
	JUMPTRUE,		//метка для безусловного перехода
	INP,			//метка чтения
	OUTP			//метка вывода
};

struct StackElem
{
	int value;				//ASCII-код символа для входного символа
	OPSType type;
};

struct OPSStruct
{	//запись в таблице символов и таблице переменных
	char* elem;
	OPSType type;
};

struct LexEntry
{	 // ключевое слово
	char* lexptr;
	int token;
};

struct ArrEntry
{	//запись в таблице массивов
	char* masptr;
	int* mas;
};

struct ElMas
{	//имя массива, значения элементов массива
	int mas;
	int elem;
};

const char EOS = '\0';					//конец строки
const int SIZE = 500;					//размер стека
const int NONE = -1;					//другой символ
const int BUFFER = 10;					//размер буфера
const int NUM = 101;					//число
const int VAR = 102;					//переменная
const int VARIEBLE = 103;				//для ключевого слова VAR
const int ARRAY = 104;					//массив
const int IF = 105;
const int ELSE = 106;
const int WHILE = 107;
const int DO = 108;
const int READ = 109;
const int WRITE = 110;
const int INT = 111;					//целочисленный тип переменной
const int IMAS = 112;					//целочисленный тип массива (определение типа)
const int INDEX = 113;					//метка массива для ОПС для индексации
const int MJFALSE = 114;				//метка перехода по "ложь" для ОПС
const int MJTRUE = 115;					//метка безусловного перехода для ОПС
const int LEXMAX = 1000;				//размер массива лексем
const int SYMMAX = 100;					//размер таблицы символов

bool OPSFlag = 0;					//флаг,указывающий было или не было объявление переменных
int spNumber;						//номер семантической программы
int OPScount = 0;					//счётчик элементов в ОПС
int last_char = -1;					//последняя использованная позиция в lexemes
int last_entry = 0;					//последняя использованная позиция в таблице символов
int lextype;						//тип лексемы
int CurrSym = -1;					//номер обозреваемого символа
int sym_numb_line = -1;				//номер символа в строке программы
int errorS = -1;					//ошибочные
int numb_line = 1;					//номер строки
int tokenval;						//значения токена
int x = 10;							//символьная длина элемента в ОПС 

int lex_Table[3][22] = {
	// 0  1  2    3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21
	//<б><ц> spa  :  =   /   *   +   -   [   ]   (    )   <    >  ;   ^    ?  ☺  ПC   ,   !
	{ 0,  2, 18,  4,  5,  6,  7,  8,  9, 20, 17, 10, 11, 12, 13, 26, 27, 28, 19, 24, 29, 30}, //0
	{ 1, 21, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 19, 25, 15, 15}, //1
	{ 21, 3, 16, 23, 16, 16, 16, 16, 16, 23, 16, 23, 16, 16, 16, 16, 16, 16, 19, 22, 23, 16}  //2
};

int ASCII_Table[128] = {
	//таблица переходов, по ASCI-коду символа получаем номер столбца в lexTab
	//номер столбца в лекстабле,
	//код символа есть индекс массива 
	18, 18, 18, 18, 18, 18, 18, 18, 18, 2,
	19, 18, 18, 18, 18, 18, 18, 18, 18, 18,	//10
	18, 18, 18, 18, 18, 18, 18, 17, 18, 18,	//20
	18, 18,  2, 21, 18, 24, 22, 18, 20, 18,	//30
	11, 12,  6,  7, 20,  8, 18, 5,  1,  1,	//40
	1,  1,  1,  1,  1,  1,  1,  1,  3, 15,	//50 
	13, 4, 14, 17, 18,  0,  0,  0,  0,  0,	//60
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//70
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//80
	0,  9, 18, 10, 16, 18, 18,  0,  0,  0,	//90
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//100
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//110
	0,  0,  0, 18, 18, 18, 18
};

char lexemes[LEXMAX];				//массив лексем
char lexbuf[BUFFER];				//буфер лексемы
char* Text_of_the_Program;


LexEntry  symtable[SYMMAX];			//таблица символов
LexEntry  number[SYMMAX];			//переменные и их значения
ArrEntry  massiv[SYMMAX];			//массивы и их содержимое
ElMas     passport[1000];			//паспорт массива
OPSStruct OPSarr[9999];



class Stack
{
	StackElem stck[SIZE];
	int StackSize;			 //текущий размер стека
public:
	Stack();
	~Stack() {};
	void push(StackElem i);
	StackElem pop();
};

Stack::Stack()
{
	StackSize = 0;
}

void Stack::push(StackElem i)
{
	if (StackSize == SIZE) {
		cout << "Stack is full \n";
		system("PAUSE");
		exit(0);
	}
	stck[StackSize] = i;
	StackSize++;
}

StackElem Stack::pop()
{
	if (StackSize == 0) {
		cout << "Stack is empty\n";
		system("PAUSE");
		exit(0);
	}
	StackSize--;
	return stck[StackSize];
}



int insert_the_Table(char s[], int tok)
{
	//добавляет новую лексему и возвращает положение в таблице символов для s
	int len;
	len = strlen(s);									//вычисляет длину строки
	if (last_entry + 1 >= SYMMAX)						//массив переполнен
	{
		cout << "Symbol table is overloaded";
		system("PAUSE");
		exit(0);
	}
	if (last_char + len + 1 >= LEXMAX)					//массив лексем переполнен
	{
		cout << "Array is overloaded";
		system("PAUSE");
		exit(0);
	}
	for (int i = 0; i < last_entry; i++) {				//если не объявлена переменая с таким именем-ошибка
		if (tok == symtable[i].token && numb_line != 1)
		{
			cout << "Error\n";
			cout << "String: " << numb_line << "  symbol: " << sym_numb_line << '\n';
			system("PAUSE");
			exit(0);
		}
	}

	last_entry++;												//переходим к следующей позиции под символ в таблице символов
	symtable[last_entry].token = tok;							//устанавливаем целое, описывающее хранимый токен
	symtable[last_entry].lexptr = &lexemes[last_char + 1];		//адрес начала лексемы в массиве лексем
	if (tok == VAR)
		number[last_entry].lexptr = &lexemes[last_char + 1];
	if (tok == ARRAY)
		massiv[last_entry].masptr = &lexemes[last_char + 1];
	last_char = last_char + len + 1;							//обновляем последнюю позицию в массиве лексем
	strcpy(symtable[last_entry].lexptr, s);						//заполняем массив лексем
	return last_entry;
}

void init()
{	//загрузка ключевых слов в таблицу символов
	LexEntry  KEYWORDS[] = {	//таблица ключевых слов
		(char*)"var", VARIEBLE,
		(char*)"if", IF,
		(char*)"else", ELSE,
		(char*)"while", WHILE,
		(char*)"input", READ,
		(char*)"output", WRITE,
		(char*)"int",  INT,
		(char*)"mas", IMAS,
		0, 0
	};
	LexEntry* p = KEYWORDS;
	for (; p->token; p++)
		insert_the_Table(p->lexptr, p->token); //токен - аски код ключевого слова.
}



class TXT_to_mass_char
{
public:
	TXT_to_mass_char();
	~TXT_to_mass_char() {};
	bool exist();
	void output();
	void choice();
private:
	bool empty = 0;
	bool record(FILE*);
};


inline TXT_to_mass_char::TXT_to_mass_char()
{
}

bool TXT_to_mass_char::exist()
{
	if (empty == 0)
		return false;
	return true;
}

inline void TXT_to_mass_char::output()
{
	int i = 0;
	while (Text_of_the_Program[i] != '.')
		cout << Text_of_the_Program[i++];
}

bool TXT_to_mass_char::record(FILE* fp)
{
	if (fp == NULL)
	{
		cout << "File Not Found";
		return false;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		if (fileSize == 0)
		{
			cout << "File is empty" << endl;
			fclose(fp);
			return false;
		}
		Text_of_the_Program = new char[fileSize];
		fseek(fp, 0, SEEK_SET);

		int i = -1;
		while (i < fileSize - 1)
			Text_of_the_Program[++i] = getc(fp);

		Text_of_the_Program[i] = '.';									//конечный символ - ограничитель
	}
	return true;
}

inline void TXT_to_mass_char::choice()
{
	FILE* fp;
	//fopen_s(&fp, choice[i - 1], "r");
	fopen_s(&fp, "operator.txt", "r");

	if (record(fp))
	{
		cout << "READ SUCCESSFUL" << endl;
		empty = 1;
		fclose(fp); 	//close file
		init();  		//заполнение  таблицы ключевыми словами	
	}
}



void init();													// инициализация таблицы лексем
int insert_the_Table(char s[], int tok);						// вставка значений

int LexicalAnalys();													//лексический анализатор
void OPS_accum(int sym, int tval);							//формирование опс
void Go_to_next(int sym);										//переходит к следующему токену

void NeterminalL();												//порождающее правило L
void Inside_Mult_Div();											//порождающее правило Z

void NeterminalU();												//порождающее правило U
void Inside_Plus_Minus();										//порождающее правило T

void NeterminalQ();												//синтаксис выражений. Порождающее правило E
void Program_body();											//"тело" программы. Порождающее правило S
void NeterminalA();											//объявление переменной. Правило А 
void NeterminalC();											//объявление массива. Правило C

void ProgExpr();												//часть программы, вспомогат. для S
char getsym();

void NeterminalD();												//условие. Порождающее правило D
void NeterminalJ();													//сравнение. Порождающее правило Q
void NeterminalS();													//исходная функция для синт.анализатора

void ops_count(OPSType vari, const char* sign);
int lookup_Table(char s[]);										//поиск в таблице символов
int insert_the_Table(char s[], int tok);						//добавление в таблицу
void setSize();													//устанавливает размер массива
void error(const char* er);										//вывод ошибок
void output_ops();												//вывод опс	
int operand(char, int, int);									//функция для выбора операнда + - * /

void OPS_Procession();											//обработка ОПС