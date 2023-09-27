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
