#ifndef BTNGROUP_GLOBAL_H
#define BTNGROUP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BTNGROUP_LIBRARY)
#define BTNGROUP_EXPORT Q_DECL_EXPORT
#else
#define BTNGROUP_EXPORT Q_DECL_IMPORT
#endif

#endif // BTNGROUP_GLOBAL_H
