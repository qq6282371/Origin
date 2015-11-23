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
			std::wstring(L"线程企图读写一个没有相应访问权限的地址")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_DATATYPE_MISALIGNMENT,
			std::wstring(L"线程试图读写未经对齐或者硬件没有提供对齐的数据")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_BREAKPOINT,
			std::wstring(L"触发了一个断点")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_SINGLE_STEP,
			std::wstring(L"标志寄存器的TF位为1时，每执行一条指令就会引发该异常。主要用于单步调试")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_ARRAY_BOUNDS_EXCEEDED,
			std::wstring(L"线程试图访问一个越界的数组元素，在硬件支持的边界检测条件下")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_DENORMAL_OPERAND,
			std::wstring(L"浮点运算中的一个操作数是非正常的")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_DIVIDE_BY_ZERO,
			std::wstring(L"浮点数除法的除数是0")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_INEXACT_RESULT,
			std::wstring(L"浮点运算的结果不能精确表示成小数")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_INVALID_OPERATION,
			std::wstring(L"无效的浮点运算")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_OVERFLOW,
			std::wstring(L"浮点运算结果的指数超过所能表示的最大值")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_STACK_CHECK,
			std::wstring(L"进行浮点数运算时栈发生溢出或下溢")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_FLT_UNDERFLOW,
			std::wstring(L"浮点运算结果的指数小于所能表示的最小值")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INT_DIVIDE_BY_ZERO,
			std::wstring(L"线程试图用一个整数除以0")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INT_OVERFLOW,
			std::wstring(L"整数操作的结果超出了最大值")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_PRIV_INSTRUCTION,
			std::wstring(L"线程试图执行一条当前CPU模式不允许的指令")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_IN_PAGE_ERROR,
			std::wstring(L"线程试图访问一个不存在的页，系统无法加载此页")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_ILLEGAL_INSTRUCTION,
			std::wstring(L"线程试图执行一个无效的指令")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_NONCONTINUABLE_EXCEPTION,
			std::wstring(L"线程试图恢复一个不可恢复的异常")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_STACK_OVERFLOW,
			std::wstring(L"线程的栈溢出")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INVALID_DISPOSITION,
			std::wstring(L"一个异常句柄返回了一个无效的配置给分发器")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_GUARD_PAGE,
			std::wstring(L"线程访问的内存有PAGE_GUARD标志")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			EXCEPTION_INVALID_HANDLE,
			std::wstring(L"线程使用了一个无效的指向内核对象的句柄（可能已经被关闭）")));
		mapCodeMeaning.insert(
			std::pair<DWORD,std::wstring>(
			STATUS_UNWIND_CONSOLIDATE,
			std::wstring(L"帧合并已经被执行")));
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
		{//EXCEPTION_EXECUTE_HANDLER异常已经处理 EXCEPTION_CONTINUE_EXECUTION重回异常处执行
		case EXCEPTION_ACCESS_VIOLATION://线程企图读写一个没有相应访问权限的地址。
		case EXCEPTION_DATATYPE_MISALIGNMENT://线程试图读写未经对齐或者硬件没有提供对齐的数据。
			//16bit值必须2字节对齐 32bit值必须4字节对齐
		case EXCEPTION_BREAKPOINT://触发了一个断点
		case EXCEPTION_SINGLE_STEP://标志寄存器的TF位为1时，每执行一条指令就会引发该异常。主要用于单步调试。
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED://线程试图访问一个越界的数组元素，在硬件支持的边界检测条件下。
		case EXCEPTION_FLT_DENORMAL_OPERAND://浮点运算中的一个操作数是非正常的。所谓非正常，即它的值太小以至于不能用标准格式表示出来。
		case EXCEPTION_FLT_DIVIDE_BY_ZERO://浮点数除法的除数是0。
		case EXCEPTION_FLT_INEXACT_RESULT://浮点运算的结果不能精确表示成小数。
		case EXCEPTION_FLT_INVALID_OPERATION://
		case EXCEPTION_FLT_OVERFLOW://浮点运算结果的指数超过所能表示的最大值。
		case EXCEPTION_FLT_STACK_CHECK://进行浮点数运算时栈发生溢出或下溢。
		case EXCEPTION_FLT_UNDERFLOW://浮点运算结果的指数小于所能表示的最小值。
		case EXCEPTION_INT_DIVIDE_BY_ZERO://线程试图用一个整数除以0。
		case EXCEPTION_INT_OVERFLOW://整数操作的结果超出了最大值。
		case EXCEPTION_PRIV_INSTRUCTION://线程试图执行一条当前CPU模式不允许的指令。
		case EXCEPTION_IN_PAGE_ERROR://线程试图访问一个不存在的页，系统无法加载此页
		case EXCEPTION_ILLEGAL_INSTRUCTION://线程试图执行一个无效的指令。
		case EXCEPTION_NONCONTINUABLE_EXCEPTION://线程试图恢复一个不可恢复的异常。
		case EXCEPTION_STACK_OVERFLOW://线程的栈溢出。
		case EXCEPTION_INVALID_DISPOSITION://一个异常句柄返回了一个无效的配置给分发器。高级语言不会遇到。
		case EXCEPTION_GUARD_PAGE://线程访问的内存有PAGE_GUARD标志
		case EXCEPTION_INVALID_HANDLE://线程使用了一个无效的指向内核对象的句柄（可能已经被关闭）。
		//case EXCEPTION_POSSIBLE_DEADLOCK://EnterCriticalSection触发。微软建议不要处理该异常，最好调试程序（它不应该出现，肯定是上锁逻辑有问题了）
		case STATUS_UNWIND_CONSOLIDATE://帧合并已经被执行
		//case CONTROL_C_EXIT:
		default:
			break;
		}
		return EXCEPTION_CONTINUE_SEARCH;//未处理异常，继续寻找其他异常处理
	}
private:
	unsigned long m_nCode;
	LPEXCEPTION_POINTERS m_pExcept;
public:
	static _se_translator_function m_pPriHandler;
};

