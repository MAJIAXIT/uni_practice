#include "funcs.h"

fstream *open(char *path, bool mode, char *exc) {
    fstream *file;
    if (mode) {
        file = new fstream();
        file->open(path, ios_base::in);
    } else {
        file = new fstream();
        file->open(path, ios_base::out | ios_base::trunc);
    }
    if (!file->is_open())
        strcpy(exc, "File open error");
    return file;
}

void close(fstream *file) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("File not open");
    file->close();
    delete file;
}

bool read(fstream *file, int el, char *word) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("file not open");
    file->clear();
    file->seekg(0);
    
    if (el < 1 || el > wordsCount(file))
        return false;
    string res;
    int i = 0;
    while (i < el) {
        *file >> res;
        i++;
    }
    strcpy(word, res.c_str());
    file->clear();
    file->seekg(0);
    return true;
}

void write(fstream *file, char *text) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("File not open");
    *file << text << endl;
}

int wordsCount(fstream *file) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("File not open");
    int res = 0;
    string tmp;
    while (!file->eof()) {
        *file >> tmp;
        res++;
    }
    file->clear();
    file->seekg(0);
    return res;
}

void readAll(fstream *file, char *text) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("File not open");
    file->clear();
    file->seekg(0);

    string contents((istreambuf_iterator<char>(*file)),
                    istreambuf_iterator<char>());
    strcpy(text, contents.c_str());
    file->clear();
    file->seekg(0);
}

int symbCount(fstream *file) {
    // Should never happen. Cant handle with C# on unix
    if (!file->is_open())
        throw invalid_argument("File not open");
    file->seekg(0, ios_base::end);
    int ans = file->tellg();
    file->clear();
    file->seekg(0);
    return ans;
}
