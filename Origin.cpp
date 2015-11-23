// Origin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Origin.h"
#include <excpt.h>
#include "SEHException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
_se_translator_function CSEHException::m_pPriHandler = NULL;


using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	HMODULE hModule = NULL;
	nRetCode = InitException();
	if(nRetCode!=0){
		return nRetCode;
	}
	try{
		hModule = ::GetModuleHandle(NULL);
	}catch(CSEHException e){
		_tprintf(_T("%s\n"),e.toString().c_str());
	}
	if (hModule == NULL) {
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
		return nRetCode;
	}
	try{
	// 初始化 MFC 并在失败时显示错误
	if (AfxWinInit(hModule, NULL, ::GetCommandLine(), 0) == FALSE)
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	}catch(CSEHException e){
		_tprintf(_T("%s\n"),e.toString().c_str());
		return nRetCode;
	}
	// TODO: 在此处为应用程序的行为编写代码。
	return nRetCode;
}

int InitException()
{
	CSEHException::m_pPriHandler = _set_se_translator(CSEHException::TranslateSEH2Obj);
	return -1;
}
