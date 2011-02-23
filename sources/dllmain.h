
#ifndef DLLMAIN_H_
#define DLLMAIN_H_

////////////////////////////////////////////////////////////////////////////////
//Переменные, установленные при генерации класса:                             //
//ИменаКлассов: "CNativeXMLReader"                                            //
//Кодовая страница: Windows-1251                                              //
////////////////////////////////////////////////////////////////////////////////
#define dfComp1CNames L"CNativeXMLReader"
#define dfLocalCodePage "Windows-1251"
//Символ для сравнения на Англ и пр. языки
#define dfSeparateSymb 0x036f

////////////////////////////////////////////////////////////////////////////////
//Определяем признак и структуры для отладки(записи лога)                     //
// в соответствии с ним будет строиться лог работы программы                  //
//#define dfCompDebug 1                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifdef dfCompDebug
#define dfCompDebugMsg(X) SetLog(X)
#else
#define dfCompDebugMsg(X)
#endif
////////////////////////////////////////////////////////////////////////////////
// <<<< Определяем признак и структуры для отладки(записи лога) <<<<          //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Признак интеграции с фрэймворком QT                                         //
// если ifndef, значить не используем типы и особенности фрэймворка           //
////////////////////////////////////////////////////////////////////////////////
#define dfUSEQT
#define dfUSEBoost


//Структура данных для поиска
//параметров и методов по именам
struct stNmTreePoint
{
    unsigned short childcnt;
    short result;
    stNmTreePoint* childrens;
    wchar_t* symbols;
};

//Поддерживаемые типы
enum enArgTypes
{
    ebool = 0,
    eint,
    euint,
    edouble,
    efloat
};

//Структура определения функции
struct stFuncInfo
{
    bool hasretval;
    enArgTypes retvaltype;
    unsigned char paramcnt;
    enArgTypes* paramtypes;
    unsigned char defparamcnt;
    unsigned char* defparams;
};

#endif
