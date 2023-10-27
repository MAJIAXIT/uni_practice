#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#pragma once

using namespace std;

// exc - Exception message to handle in C#
extern "C" fstream *open(char *path, bool mode, char *exc);
extern "C" void close(fstream *file);
extern "C" bool read(fstream *file, int el, char *word);
extern "C" void write(fstream *file, char *text);
extern "C" int wordsCount(fstream *file);
extern "C" void readAll(fstream *file, char *text);
extern "C" int symbCount(fstream *file);