#ifndef MINIDUMP_H
#define MINIDUMP_H

#include "MiniDumpExport.h"

#if defined(WIN32)
    #include <Windows.h>
#endif // WIN32

class MINIDUMP_EXPORT MiniDump
{
public:
    /**
     * @brief SetAutoDumpEnable         使能软件崩溃转存
     * @param vEnable
     */
    static void SetAutoDumpEnable(bool vEnable = true);

private:
    /**
     * @brief ApplicationCrashCallback  软件崩溃回调
     * @param vExceptionInfoPTR
     * @return
     */
    static LONG WINAPI ApplicationCrashCallback(EXCEPTION_POINTERS* vExceptionInfoPTR);

    /**
     * @brief CreateDumpFile            创建dump文件，崩溃转存
     * @param vDumpFilePath
     * @param vExceptionInfoPTR
     */
    static void CreateDumpFile(LPCSTR vDumpFilePath, EXCEPTION_POINTERS* vExceptionInfoPTR);

private:
    MiniDump(){};
    ~MiniDump(){};
};

#endif // MINIDUMP_H
