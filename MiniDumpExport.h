#ifndef MINIDUMPEXPORT_H
#define MINIDUMPEXPORT_H

#if not defined(LIBRARY_UNEXPORT)
    #include <QtCore/qglobal.h>
    #if defined(MINIDUMP_LIBRARY)
    #  define MINIDUMP_EXPORT Q_DECL_EXPORT
    #else
    #  define MINIDUMP_EXPORT Q_DECL_IMPORT
    #endif
#else
    #  define MINIDUMP_EXPORT
#endif

#endif // MINIDUMPEXPORT_H
