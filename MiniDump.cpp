#include "MiniDump.h"
#include "MiniDumpDefine.h"

#include <stdio.h>

#if defined(WIN32)
    #include <DbgHelp.h>
//    #pragma comment(lib, "dbghelp.lib")
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess,
                                         DWORD ProcessId,
                                         HANDLE hFile,
                                         MINIDUMP_TYPE DumpType,
                                         CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                         CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                         CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);
#endif

void MiniDump::SetAutoDumpEnable(bool vEnable)
{
    if(!vEnable)
        return;

    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashCallback);
}

LONG MiniDump::ApplicationCrashCallback(EXCEPTION_POINTERS *vExceptionInfoPTR)
{
    //获取当前本地时间
    SYSTEMTIME tSystemTime;
    memset(&tSystemTime, 0, sizeof(SYSTEMTIME));
    GetLocalTime(&tSystemTime);

    //获取当前路径
    char tDumpFileDIR[MAX_PATH] = { 0 };
    GetCurrentDirectoryA(MAX_PATH, tDumpFileDIR);

    //指定dump文件存储路径
    sprintf(tDumpFileDIR, "%s\\dump", tDumpFileDIR);

    //创建dump文件存储目录
    bool tIsFileExist = false;
    DWORD tFileAttributes = GetFileAttributesA(tDumpFileDIR);
    if(tFileAttributes != INVALID_FILE_ATTRIBUTES)
    {
        bool tBitValCheckRet = BitValChk(tFileAttributes, FILE_ATTRIBUTE_DIRECTORY);
        if(tBitValCheckRet)
            tIsFileExist = true;
    }

    if(!tIsFileExist)
    {
        BOOL tCreateRet = CreateDirectoryA(tDumpFileDIR, NULL);
        if(tCreateRet != TRUE)
        {
            printf("func: CreateDirectoryA, last error: %ld\n", GetLastError());
            return EXCEPTION_CONTINUE_SEARCH;
        }
    }

    //构建dump文件路径
    char tDumpFile[MAX_PATH] = { 0 };
    sprintf(tDumpFile, "%s\\%04d%02d%02d_%02d%02d%02d.dmp",
            tDumpFileDIR,
            tSystemTime.wYear, tSystemTime.wMonth, tSystemTime.wDay,
            tSystemTime.wHour, tSystemTime.wMinute, tSystemTime.wSecond);

    //创建dump文件
    CreateDumpFile(tDumpFile, vExceptionInfoPTR);

    //异常提示，并退出程序
    char tErrorMessage[MAX_PATH] = { 0 };
    sprintf(tErrorMessage, "the program crashed.\r\ndump file: %s", tDumpFile);
    FatalAppExitA(-1, tErrorMessage);

	return EXCEPTION_EXECUTE_HANDLER;
}

void MiniDump::CreateDumpFile(LPCSTR vDumpFilePath, EXCEPTION_POINTERS *vExceptionInfoPTR)
{
    //加载windows api dll
    HMODULE tDLLHandle = LoadLibraryA("DBGHELP.DLL");
    if(tDLLHandle == NULL)
    {
        printf("func: LoadLibraryA, last error: %ld\n", GetLastError());
        return;
    }

    do
    {
        //获取dll函数地址
        MINIDUMPWRITEDUMP tDumpWriteFuncPTR = (MINIDUMPWRITEDUMP)GetProcAddress(tDLLHandle, "MiniDumpWriteDump");
        if(tDumpWriteFuncPTR == NULL)
        {
            printf("func: GetProcAddress, last error: %ld\n", GetLastError());
            break;
        }

        //创建dump文件
        HANDLE tDumpFileHandle = CreateFileA(vDumpFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(tDumpFileHandle == INVALID_HANDLE_VALUE)
        {
            printf("func: CreateFileA, last error: %ld\n", GetLastError());
            break;
        }

        //填写dump信息
        MINIDUMP_EXCEPTION_INFORMATION tExceptionInfo;
        tExceptionInfo.ExceptionPointers = vExceptionInfoPTR;
        tExceptionInfo.ThreadId = GetCurrentThreadId();
        tExceptionInfo.ClientPointers = TRUE;

        //写入dump文件内容
        BOOL tResult = tDumpWriteFuncPTR(GetCurrentProcess(), GetCurrentProcessId(), tDumpFileHandle, MiniDumpNormal, &tExceptionInfo, NULL, NULL);
        if(tResult != TRUE)
        {
            printf("func: tDumpWriteFuncPTR, last error: %ld\n", GetLastError());
        }

        CloseHandle(tDumpFileHandle);

    }while(0);

    FreeLibrary(tDLLHandle);
}
