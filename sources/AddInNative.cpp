#include "stdafx.h"

#ifdef __linux__
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#endif

#include "AddInNative.h"

//Методы класса компоненты
CNativeXMLReader::CNativeXMLReader()
{
    dfCompDebugMsg("CNativeXMLReader");

    initStaticMembers();
}

//---------------------------------------------------------------------------//
CNativeXMLReader::~CNativeXMLReader()
{
    dfCompDebugMsg("~CNativeXMLReader");

}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::RetStrTo1C(WCHAR_T** wsRetVal, const wchar_t* wsSendVal, uint SendValLen)
{
    dfCompDebugMsg("CNativeXMLReader::RetStrTo1C");
    if (m_iMemory)
    {
        if(m_iMemory->AllocMemory((void**)wsRetVal, SendValLen * sizeof(WCHAR_T)))
        {
            if (!SendValLen)
                SendValLen = ::wcslen(wsSendVal)+1;

            ::memset(*wsRetVal, 0, SendValLen * sizeof(WCHAR_T));

            WCHAR_T* tmpShort = *wsRetVal;
            wchar_t* tmpWChar = (wchar_t*)wsSendVal;
            uint32_t res = 0;
            do
            {
                *tmpShort++ = (WCHAR_T)*tmpWChar++;
                ++res;
            }
            while (SendValLen-- && *tmpWChar);

            return res;
        };
        return true;
    };

    return false;
}

//---------------------------------------------------------------------------//
//Поиск в отсортированном массиве
int CNativeXMLReader::massfind(wchar_t* massSmb, uint massLen, wchar_t symb)
{
    dfCompDebugMsg("    CNativeXMLReader::massfind");
    int i = 0;
    int n = massLen-1;
    int half;
    int middle;

    while (n > 0) {
        half = n >> 1;
        middle = i + half;
        if (massSmb[middle] < symb) {
            i = middle + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }

    if (massSmb[i] == symb)
        return i;

    return -1;
}

//---------------------------------------------------------------------------//
inline long CNativeXMLReader::FindNameFromTree(stNmTreePoint* curTree, const WCHAR_T* wsName, uint NameLen)
{
    dfCompDebugMsg("  CNativeXMLReader::FindNameFromTree");

    if ((!curTree) || (!wsName))
    {
        dfCompDebugMsg("Cur tree or wsName is NULL");
        return -1;
    };

    if (!NameLen)
        NameLen = ::wcslen(wsName)+1;

   dfCompDebugMsg((char *)QString("Name len: %1").arg(wsName[NameLen]).toLocal8Bit().data());

    uint curPos = 0;
    stNmTreePoint* curPoint = curTree;
    int rez = -1;
    uint cLen = (NameLen-1);
    dfCompDebugMsg((char *)QString("   clen: %1").arg(wsName[cLen]).toLocal8Bit().data());

    while(curPos < cLen)
    {
        dfCompDebugMsg((char *)QString("   %1").arg(wsName[curPos]).toLocal8Bit().data());

        if (!curPoint->childcnt)
        {
            uint nextind = massfind(curPoint->symbols, curPoint->childcnt, wsName[curPos]);
            if (nextind == -1)
            {
                curPos = NameLen + 1;
                curPoint = 0;
                break;
            };

            curPoint = &(curPoint->childrens[nextind]);

        }else
        {
            uint LenOst = cLen - curPos;
            wchar_t * tmpWChar = curPoint->symbols;
            if((*tmpWChar) && (curPoint->result != -1) && (LenOst > 0) )
            {
                do{
                    if (wsName[curPos] != *tmpWChar++)
                    {
                        curPos = NameLen + 1;
                        curPoint = 0;
                        break;
                    };

                    curPos++;
                }while (curPos < NameLen && *tmpWChar);

                if (!*tmpWChar && curPoint)
                    rez = curPoint->result;
            };
            curPoint = 0;

        };
        curPos++;
    };

    if (curPoint)
    {
        if (!curPoint->childcnt && !curPoint->symbols)
            rez = curPoint->result;
    };


    return rez;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::Init(void* pConnection)
{
    dfCompDebugMsg("Init");

    m_iConnect = (IAddInDefBase*)pConnection;
    return m_iConnect != NULL;
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::GetInfo()
{
    dfCompDebugMsg("GetInfo");

    return dfCompVersionCA;
}

//---------------------------------------------------------------------------//
void CNativeXMLReader::Done()
{
    dfCompDebugMsg("Done");

}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::RegisterExtensionAs(WCHAR_T** wsLanguageExt)
{
    dfCompDebugMsg("RegisterExtensionAs");

    return RetStrTo1C(wsLanguageExt, g_Comp1CLocNameCA, dfComp1CLocNameCALen);
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::GetNProps()
{
    dfCompDebugMsg("GetNProps");

    return dfCompPropNumCA;
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::FindProp(const WCHAR_T* wsPropName)
{
    dfCompDebugMsg("FindProp");

    if (!wsPropName)
    {
        dfCompDebugMsg("      wsPropName is NULL!!!");
        return -1;
    };

    if ((uint16_t)wsPropName[0] < dfSeparateSymb)
    {
        dfCompDebugMsg("      finding from eng names...");
        return FindNameFromTree(t_PropNamesCA, wsPropName);
    }else
    {
        dfCompDebugMsg("      finding from loc names...");
        return FindNameFromTree(t_PropNamesLocCA, wsPropName);
    };
}

//---------------------------------------------------------------------------//
const WCHAR_T* CNativeXMLReader::GetPropName(long lPropNum, long lPropAlias)
{
    dfCompDebugMsg("GetPropName");

    if (lPropNum >= dfCompPropNumCA)
        return 0;

    switch(lPropAlias)
    {
    case 0: // First language
        return g_PropNamesCA[lPropNum];
        break;
    case 1: // Second language
        return g_PropNamesLocCA[lPropNum];
        break;
    default:
        return 0;
    }

    return 0;    
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{
    dfCompDebugMsg("GetPropVal");

    return false;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::SetPropVal(const long lPropNum, tVariant* varPropVal)
{
    dfCompDebugMsg("SetPropVal");

    return false;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::IsPropReadable(const long lPropNum)
{
    dfCompDebugMsg("IsPropReadable");

    return true;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::IsPropWritable(const long lPropNum)
{
    dfCompDebugMsg("IsPropWritable");

    return false;
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::GetNMethods()
{
    dfCompDebugMsg("GetNMethods");

    return dfCompMethodNumCA;
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::FindMethod(const WCHAR_T* wsMethodName)
{
    dfCompDebugMsg("FindMethod");

    if (!wsMethodName)
    {
        dfCompDebugMsg("      wsMethodName is NULL!!!");
        return -1;
    };

    if ((uint16_t)wsMethodName[0] < dfSeparateSymb)
    {
        dfCompDebugMsg("      finding from eng names...");
        return FindNameFromTree(t_MethodNamesCA, wsMethodName);
    }else
    {
        dfCompDebugMsg("      finding from loc names...");
        return FindNameFromTree(t_MethodNamesLocCA, wsMethodName);
    }

    return -1;
}

//---------------------------------------------------------------------------//
const WCHAR_T* CNativeXMLReader::GetMethodName(const long lMethodNum, 
                            const long lMethodAlias)
{
    dfCompDebugMsg("GetMethodName");

    if (lMethodNum >= dfCompMethodNumCA)
        return 0;

    switch(lMethodAlias)
    {
    case 0: // First language
        return g_MethodNamesCA[lMethodNum];
        break;
    case 1: // Second language
        return g_MethodNamesLocCA[lMethodNum];
        break;
    default:
        return 0;
    }

    return 0;
}

//---------------------------------------------------------------------------//
long CNativeXMLReader::GetNParams(const long lMethodNum)
{
    dfCompDebugMsg("GetNParams");

    return 0;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::GetParamDefValue(const long lMethodNum, const long lParamNum,
                          tVariant *pvarParamDefValue)
{
    dfCompDebugMsg("GetParamDefValue");

    return false;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::HasRetVal(const long lMethodNum)
{
    dfCompDebugMsg("HasRetVal");

    return false;
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray)
{

    dfCompDebugMsg("CallAsProc");

    return true;

}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::CallAsFunc(const long lMethodNum,
                tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{
    dfCompDebugMsg("CallAsFunc");

    return true;

}

//---------------------------------------------------------------------------//
void CNativeXMLReader::SetLocale(const WCHAR_T* loc)
{
    dfCompDebugMsg("SetLocale");

#ifndef __linux__
    _wsetlocale(LC_ALL, loc);
#else
    int size = 0;
    char *mbstr = 0;
    wchar_t *tmpLoc = 0;
    convFromShortWchar(&tmpLoc, loc);
    size = wcstombs(0, tmpLoc, 0)+1;
    mbstr = new char[size];

    if (!mbstr)
    {
        delete[] tmpLoc;
        return;
    }

    memset(mbstr, 0, size);
    size = wcstombs(mbstr, tmpLoc, wcslen(tmpLoc));
    setlocale(LC_ALL, mbstr);
    delete[] tmpLoc;
    delete[] mbstr;
#endif
}

//---------------------------------------------------------------------------//
bool CNativeXMLReader::setMemManager(void* mem)
{
    dfCompDebugMsg("setMemManager");
    m_iMemory = (IMemoryManager*)mem;
    return m_iMemory != 0;
}

//---------------------------------------------------------------------------//
void CNativeXMLReader::Destroy()
{
    dfCompDebugMsg("Destroy");
    delete this;
}

//---------------------------------------------------------------------------//
void CNativeXMLReader::initStaticMembers()
{
    initCompPropNamesTree();
    initCompPropNamesTreeLoc();
    initCompPropInfo();

    initCompFuncNamesTree();
    initCompFuncNamesTreeLoc();
    initCompFuncInfo();
}

void CNativeXMLReader::initCompFuncNamesTree()
{
}

void CNativeXMLReader::initCompFuncNamesTreeLoc()
{
}

void CNativeXMLReader::initCompPropNamesTree()
{
}

void CNativeXMLReader::initCompPropNamesTreeLoc()
{
}

void CNativeXMLReader::initCompFuncInfo()
{
}

void CNativeXMLReader::initCompPropInfo()
{
}
