
#ifndef __CNATIVEXMLREADERCG_H__
#define __CNATIVEXMLREADERCG_H__

#ifndef __linux__
#include <wtypes.h>
#endif //__linux__

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"
#include "dllmain.h"

////////////////////////////////////////////////////////////////////////////////
//Переменные, установленные при генерации класса:                             //
//ИмяКлассаКомпоненты: "CNativeXMLReader"                                     //
//ИмяКомпоненты: "CNativeXMLReader"                                           //
//ИмяКласса: "QXmlStreamReader"                                               //
//ВерсияКомпоненты: 1001                                                      //
//Количество методов: 9                                                       //
//Количество свойств: 3                                                       //
//Постфикс Класса: CA                                                         //
////////////////////////////////////////////////////////////////////////////////
#define dfCompVersionCA 1001
#define dfComp1CNameCA L"CNativeXMLReader"
#define dfComp1CNameCALen 17
#define dfComp1CLocNameCA L"CNativeXMLReader"
#define dfComp1CLocNameCALen 17
#define dfCompMethodNumCA 9
#define dfCompPropNumCA 3

////////////////////////////////////////////////////////////////////////////////
//Подключаемые исходники                                                      //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//TODO: Свои подключаемые исходники                                           //
////////////////////////////////////////////////////////////////////////////////
#include <QXmlStreamReader>
#ifdef dfUSEBoost
#include "boost/bind.hpp"
#endif

////////////////////////////////////////////////////////////////////////////////
// <<<< TODO: Свои подключаемые исходники <<<<                                //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Объявления                                                                  //
////////////////////////////////////////////////////////////////////////////////

static wchar_t *g_PropNamesCA[dfCompPropNumCA] =
{
    L"Name",
    L"NodeType",
    L"Value"
};

//Чтобы не заморачиваться с кодировкой *.cpp
static wchar_t g_PropNamesLocCA[dfCompPropNumCA][9] =
{
    {1048, 1084, 1103, 0,    0,    0,    0,    0,    0},  //Имя
    {1058, 1080, 1087, 1059, 1079, 1083, 1072, 0,    0},  //ТипУзла
    {1047, 1085, 1072, 1095, 1077, 1085, 1080, 1077, 0}   //Значение
};


static wchar_t *g_MethodNamesCA[dfCompMethodNumCA] =
{
    L"OpenFile",
    L"Close",
    L"Read",
    L"AttributeValue",
    L"AttributeName",
    L"AttributeCount",
    L"GetAttribute",
    L"ReadAttribute",
    L"AttributeType"
};

//Чтобы не заморачиваться с кодировкой *.cpp
static wchar_t g_MethodNamesLocCA[dfCompMethodNumCA][20] =
{
    {1054, 1090, 1082, 1088, 1099, 1090, 1100, 1060, 1072, 1081, 1083, 0,    0,    0,    0,    0,    0,    0,    0,    0},   //ОткрытьФайл
    {1047, 1072, 1082, 1088, 1099, 1090, 1100, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},   //Закрыть
    {1055, 1088, 1086, 1095, 1080, 1090, 1072, 1090, 1100, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},   //Прочитать
    {1047, 1085, 1072, 1095, 1077, 1085, 1080, 1077, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 1072, 0,    0,    0,    0},   //ЗначениеАтрибута
    {1048, 1084, 1103, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 1072 ,0,    0,    0,    0,    0,    0,    0,    0,    0},   //ИмяАтрибута
    {1050, 1086, 1083, 1080, 1095, 1077, 1089, 1090, 1074, 1086, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 1086, 1074 ,0},   //КоличествоАтрибутов
    {1055, 1086, 1083, 1091, 1095, 1080, 1090, 1100, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 0,    0,    0,    0,    0},   //ПолучитьАтрибут
    {1055, 1088, 1086, 1095, 1080, 1090, 1072, 1090, 1100, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 0,    0,    0,    0},   //ПрочитатьАтрибут
    {1058, 1080, 1087, 1040, 1090, 1088, 1080, 1073, 1091, 1090, 1072, 0,    0,    0,    0,    0,    0,    0,    0,    0}    //ТипАтрибута
};

static const wchar_t* g_Comp1CLocNameCA = dfComp1CLocNameCA;

//Счетчик активных объектов
static int CompObjCntCA;

//Ссылки на корневые узлы деревьев
//static - это потому, что деревья создаются в 1
//экземпляре на все объекты одинаковых компонент
static stNmTreePoint* t_PropNamesCA = 0;
static stNmTreePoint* t_PropNamesLocCA = 0;

static stNmTreePoint* t_MethodNamesCA = 0;
static stNmTreePoint* t_MethodNamesLocCA = 0;

static stFuncInfo* funclistCA = 0;

static enArgTypes* proplistCA = 0;
static bool* propredablelistCA = 0;
static bool* propwritablelistCA = 0;

////////////////////////////////////////////////////////////////////////////////
//TODO: Свои объявления                                                       //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// <<<< TODO: Свои объявления <<<<                                            //
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// class CNativeXMLReader                                                     //
////////////////////////////////////////////////////////////////////////////////
class CNativeXMLReader : public IComponentBase
{
public:

    CNativeXMLReader(void);
    virtual ~CNativeXMLReader();
    // IInitDoneBase
    virtual bool ADDIN_API Init(void*);
    virtual bool ADDIN_API setMemManager(void* mem);
    virtual long ADDIN_API GetInfo();
    virtual void ADDIN_API Done();
    // ILanguageExtenderBase
    virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T** wsLanguageExt);
    virtual long ADDIN_API GetNProps();
    virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
    virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
    virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
    virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
    virtual bool ADDIN_API IsPropReadable(const long lPropNum);
    virtual bool ADDIN_API IsPropWritable(const long lPropNum);
    virtual long ADDIN_API GetNMethods();
    virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
    virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum, 
                            const long lMethodAlias);
    virtual long ADDIN_API GetNParams(const long lMethodNum);
    virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
                            tVariant *pvarParamDefValue);
    virtual bool ADDIN_API HasRetVal(const long lMethodNum);
    virtual bool ADDIN_API CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray);
    virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
    operator IComponentBase*() { return (IComponentBase*)this; }
    // LocaleBase
    virtual void ADDIN_API SetLocale(const WCHAR_T* loc);
	
	virtual void ADDIN_API Destroy();
	
private:
    // Attributes
	IAddInDefBase* m_iConnect;
	IMemoryManager* m_iMemory;

	void initStaticMembers();
	
	inline void initCompFuncNamesTree();
	inline void initCompFuncNamesTreeLoc();
	inline void initCompPropNamesTree();
	inline void initCompPropNamesTreeLoc();
	inline void initCompFuncInfo();
	inline void initCompPropInfo();
	
        //Объекты классов
        QXmlStreamReader Workobj;
	


private:
        inline int massfind(wchar_t* massSmb, uint massLen, wchar_t symb);

        inline bool RetStrTo1C(WCHAR_T** wsRetVal, const wchar_t* wsSendVal, uint SendValLen = 0);
        inline long FindNameFromTree(stNmTreePoint* curTree, const WCHAR_T* wsName, uint NameLen = 0);

        //Params variables for functions

        QString par_QString1;

	//TODO: Свой код стоит писать тут:
	
};

////////////////////////////////////////////////////////////////////////////////
//TODO: Свои классы и объявления                                              //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// <<<< TODO: Свои классы и объявления <<<<                                   //
////////////////////////////////////////////////////////////////////////////////

#endif //__CNATIVEXMLREADERCG_H__
