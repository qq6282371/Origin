#pragma once
#include <excpt.h>
#include <winbase.h>
#include <eh.h>
#include <string>
#include <stdio.h>
#include <map>
class CSEHException
{
public:
	CSEHException(UINT nCode,_EXCEPTION_POINTERS* pExcept)
	{
		m_nCode = nCode;
		m_pExcept = pExcept;
	}

	CSEHException(const CSEHException& except)
	{
		m_nCode = except.m_nCode;
		m_pExcept = except.m_pExcept;
	}

	~CSEHException(void)
	{
	}
	CSEHException& operator=(const CSEHException& except)
	{
		if(this!=&except){
			m_nCode = except.m_nCode;
			m_pExcept = except.m_pExcept;
		}
		return *this;
	}

	static void __cdecl TranslateSEH2Obj(UINT nCode,struct _EXCEPTION_POINTERS* pExcept)
	{
		throw CSEHException(nCode,pExcept);
	}
	static void InitCodeMeaning(std::map<DWORD,std::wstring>& mapCodeMeaning)
	{
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_ACCESS_VIOLATION,
			std::wstring(L"�߳���ͼ��дһ��û����Ӧ����Ȩ�޵ĵ�ַ")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_DATATYPE_MISALIGNMENT,
			std::wstring(L"�߳���ͼ��дδ���������Ӳ��û���ṩ���������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_BREAKPOINT,
			std::wstring(L"������һ���ϵ�")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_SINGLE_STEP,
			std::wstring(L"��־�Ĵ�����TFλΪ1ʱ��ÿִ��һ��ָ��ͻ��������쳣����Ҫ���ڵ�������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_ARRAY_BOUNDS_EXCEEDED,
			std::wstring(L"�߳���ͼ����һ��Խ�������Ԫ�أ���Ӳ��֧�ֵı߽���������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_DENORMAL_OPERAND,
			std::wstring(L"���������е�һ���������Ƿ�������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_DIVIDE_BY_ZERO,
			std::wstring(L"�����������ĳ�����0")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_INEXACT_RESULT,
			std::wstring(L"��������Ľ�����ܾ�ȷ��ʾ��С��")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_INVALID_OPERATION,
			std::wstring(L"��Ч�ĸ�������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_OVERFLOW,
			std::wstring(L"������������ָ���������ܱ�ʾ�����ֵ")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_STACK_CHECK,
			std::wstring(L"���и���������ʱջ�������������")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_UNDERFLOW,
			std::wstring(L"������������ָ��С�����ܱ�ʾ����Сֵ")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INT_DIVIDE_BY_ZERO,
			std::wstring(L"�߳���ͼ��һ����������0")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INT_OVERFLOW,
			std::wstring(L"���������Ľ�����������ֵ")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_PRIV_INSTRUCTION,
			std::wstring(L"�߳���ͼִ��һ����ǰCPUģʽ�������ָ��")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_IN_PAGE_ERROR,
			std::wstring(L"�߳���ͼ����һ�������ڵ�ҳ��ϵͳ�޷����ش�ҳ")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_ILLEGAL_INSTRUCTION,
			std::wstring(L"�߳���ͼִ��һ����Ч��ָ��")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_NONCONTINUABLE_EXCEPTION,
			std::wstring(L"�߳���ͼ�ָ�һ�����ɻָ����쳣")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_STACK_OVERFLOW,
			std::wstring(L"�̵߳�ջ���")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INVALID_DISPOSITION,
			std::wstring(L"һ���쳣���������һ����Ч�����ø��ַ���")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_GUARD_PAGE,
			std::wstring(L"�̷߳��ʵ��ڴ���PAGE_GUARD��־")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INVALID_HANDLE,
			std::wstring(L"�߳�ʹ����һ����Ч��ָ���ں˶���ľ���������Ѿ����رգ�")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			STATUS_UNWIND_CONSOLIDATE,
			std::wstring(L"֡�ϲ��Ѿ���ִ��")));
	}

	static std::wstring getCodeMeaning(UINT nCode)
	{
		static std::map<DWORD,std::wstring> mapCodeMeaning;
		if(mapCodeMeaning.size()<=0){
			InitCodeMeaning(mapCodeMeaning);
		}
		if(mapCodeMeaning.find(nCode)==mapCodeMeaning.end()){
			wchar_t sLine[256] = L"";
			swprintf_s(sLine,sizeof(sLine)/sizeof(wchar_t),L"Unknown code:%d",nCode);
			return std::wstring(sLine);
		}
		return mapCodeMeaning[nCode];
	}

	std::wstring toString(){
		wchar_t sLine[1024] = L"";
		const wchar_t* fmt = 
			L"Exception[%d]:%s\nAt %p eax %08x ebx %08x ecx %08x edx %08x "\
			L"esp %08x esi %08x ebp %08x edi %08x eip %08x flags %08x\n";
		swprintf_s(sLine,sizeof(sLine)-1,fmt,
			m_nCode,getCodeMeaning(m_nCode).c_str(),
			m_pExcept->ExceptionRecord->ExceptionAddress,
			m_pExcept->ContextRecord->Eax,
			m_pExcept->ContextRecord->Ebx,
			m_pExcept->ContextRecord->Ecx,
			m_pExcept->ContextRecord->Edx,
			m_pExcept->ContextRecord->Esp,
			m_pExcept->ContextRecord->Esi,
			m_pExcept->ContextRecord->Ebp,
			m_pExcept->ContextRecord->Edi,
			m_pExcept->ContextRecord->Eip,
			m_pExcept->ContextRecord->EFlags);
	}

	int ExceptionDealFunc(){
		switch(m_nCode)
		{//EXCEPTION_EXECUTE_HANDLER�쳣�Ѿ����� EXCEPTION_CONTINUE_EXECUTION�ػ��쳣��ִ��
		case EXCEPTION_ACCESS_VIOLATION://�߳���ͼ��дһ��û����Ӧ����Ȩ�޵ĵ�ַ��
		case EXCEPTION_DATATYPE_MISALIGNMENT://�߳���ͼ��дδ���������Ӳ��û���ṩ��������ݡ�
			//16bitֵ����2�ֽڶ��� 32bitֵ����4�ֽڶ���
		case EXCEPTION_BREAKPOINT://������һ���ϵ�
		case EXCEPTION_SINGLE_STEP://��־�Ĵ�����TFλΪ1ʱ��ÿִ��һ��ָ��ͻ��������쳣����Ҫ���ڵ������ԡ�
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED://�߳���ͼ����һ��Խ�������Ԫ�أ���Ӳ��֧�ֵı߽��������¡�
		case EXCEPTION_FLT_DENORMAL_OPERAND://���������е�һ���������Ƿ������ġ���ν��������������ֵ̫С�����ڲ����ñ�׼��ʽ��ʾ������
		case EXCEPTION_FLT_DIVIDE_BY_ZERO://�����������ĳ�����0��
		case EXCEPTION_FLT_INEXACT_RESULT://��������Ľ�����ܾ�ȷ��ʾ��С����
		case EXCEPTION_FLT_INVALID_OPERATION://
		case EXCEPTION_FLT_OVERFLOW://������������ָ���������ܱ�ʾ�����ֵ��
		case EXCEPTION_FLT_STACK_CHECK://���и���������ʱջ������������硣
		case EXCEPTION_FLT_UNDERFLOW://������������ָ��С�����ܱ�ʾ����Сֵ��
		case EXCEPTION_INT_DIVIDE_BY_ZERO://�߳���ͼ��һ����������0��
		case EXCEPTION_INT_OVERFLOW://���������Ľ�����������ֵ��
		case EXCEPTION_PRIV_INSTRUCTION://�߳���ͼִ��һ����ǰCPUģʽ�������ָ�
		case EXCEPTION_IN_PAGE_ERROR://�߳���ͼ����һ�������ڵ�ҳ��ϵͳ�޷����ش�ҳ
		case EXCEPTION_ILLEGAL_INSTRUCTION://�߳���ͼִ��һ����Ч��ָ�
		case EXCEPTION_NONCONTINUABLE_EXCEPTION://�߳���ͼ�ָ�һ�����ɻָ����쳣��
		case EXCEPTION_STACK_OVERFLOW://�̵߳�ջ�����
		case EXCEPTION_INVALID_DISPOSITION://һ���쳣���������һ����Ч�����ø��ַ������߼����Բ���������
		case EXCEPTION_GUARD_PAGE://�̷߳��ʵ��ڴ���PAGE_GUARD��־
		case EXCEPTION_INVALID_HANDLE://�߳�ʹ����һ����Ч��ָ���ں˶���ľ���������Ѿ����رգ���
		//case EXCEPTION_POSSIBLE_DEADLOCK://EnterCriticalSection������΢���鲻Ҫ������쳣����õ��Գ�������Ӧ�ó��֣��϶��������߼��������ˣ�
		case STATUS_UNWIND_CONSOLIDATE://֡�ϲ��Ѿ���ִ��
		//case CONTROL_C_EXIT:
		default:
			break;
		}
		return EXCEPTION_CONTINUE_SEARCH;//δ�����쳣������Ѱ�������쳣����
	}
private:
	unsigned long m_nCode;
	LPEXCEPTION_POINTERS m_pExcept;
public:
	static _se_translator_function m_pPriHandler;
};

