// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "AddInNative.h"
#include "dllmain.h"

#ifdef dfUSEQT
#include <QTextCodec>
#endif


//Имена всех классов компоненты
static const wchar_t g_kClassNames[] = dfComp1CNames;

#ifndef __linux__
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif //__linux__


//---------------------------------------------------------------------------//
long GetClassObject(const wchar_t* wsName, IComponentBase** pInterface)
{
    dfCompDebugMsg("GetClassObject");

#ifdef dfUSEQT
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(dfLocalCodePage));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(dfLocalCodePage));
    QTextCodec::setCodecForTr(QTextCodec::codecForName(dfLocalCodePage));
#endif

    if(!*pInterface)
    {
        *pInterface= new CNativeXMLReader();
        return (long)*pInterface;
    };
    return 0;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf)
{
    dfCompDebugMsg("DestroyObject");

   if(!*pIntf)
      return -1;

   delete *pIntf;
   *pIntf = 0;
   return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames()
{
    dfCompDebugMsg("GetClassNames");

    //Имена классов разделяются символом "|" без пробелов
    //Пока только 1
    return g_kClassNames;
}
//---------------------------------------------------------------------------//

