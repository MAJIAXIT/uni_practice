#if defined(__APPLE__)

#include "load.h"

void LoadRun(const char *const s) {
    void *lib;
    void (*func)(void);

    lib = dlopen(s, RTLD_LAZY);
    if (!lib) {
        printf("cannot open library '%s'\n", s);
        return;
    }
    func = (void (*)(void))dlsym(lib, "main");

    if (func == NULL)
        printf("cannot load funcction funcc\n");
    else
        func();

    dlclose(lib);
}

#elif defined(_WIN32)
#include "fun.h"
#include "load.h"
#include <stdio.h>
#include <windows.h>
void LoadRun(const char *const s) {
    void *lib;
    void (*fun)(void);
    lib = LoadLibrary(s) if (!lib) {
        printf("cannot open library '%s'\n", s);
        return;
    }
    fun = (void (*)(void))GetProcAddress((HINSTANCE)lib, "func")

        if (fun == NULL) {
        printf("cannot load function func\n");
    }
    else {
        fun();
    }
    FreeLibrary((HINSTANCE)lib) // выгрузка библиотеки;
}
#endif