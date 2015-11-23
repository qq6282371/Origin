// Origin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Origin.h"
#include <excpt.h>
#include "SEHException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

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
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
		return nRetCode;
	}
	try{
	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (AfxWinInit(hModule, NULL, ::GetCommandLine(), 0) == FALSE)
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
	}
	}catch(CSEHException e){
		_tprintf(_T("%s\n"),e.toString().c_str());
		return nRetCode;
	}
	// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	return nRetCode;
}

int InitException()
{
	CSEHException::m_pPriHandler = _set_se_translator(CSEHException::TranslateSEH2Obj);
	return -1;
}
