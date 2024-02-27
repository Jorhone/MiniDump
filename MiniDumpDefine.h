#ifndef MINIDUMPDEFINE_H
#define MINIDUMPDEFINE_H

/**
 * 数据类型定义
 */

// Cross Platform

#ifndef BitPosChk
    #define BitPosChk(_Value, _Pos) (0 != ((_Value)&(1<<_Pos)))
#endif

#ifndef BitValChk
    #define BitValChk(_Value, _Val) (_Val == ((_Value)&(_Val)))
#endif

#ifdef UNICODE
    #define CP_SPRINTF wsprintf
#else
    #define CP_SPRINTF sprintf
#endif

#endif // MINIDUMPDEFINE_H
