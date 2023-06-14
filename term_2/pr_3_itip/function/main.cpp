#include <cstring>
#include <iostream>
#define SIZE 50
#define TOKEN 20

using namespace std;

template <class T> void swapArrHalf(T *arr, size_t size);

int main(int argc, char **argv) {
    int idx = 0, ch, *iarr;
    unsigned char *ucarr;
    char *buffer, *token;
    size_t ucarrLen, iarrLen;

    try {
        ucarr = new unsigned char[SIZE];
        iarr = new int[SIZE];
        token = new char[TOKEN];
        buffer = new char[SIZE];
    } catch (bad_alloc &xa) {
        cerr << "Memory allocationg error. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Enter int array: " << endl;
    while ((ch = getchar()) != '\n')
        buffer[idx++] = ch;
    buffer[idx] = '\0';
    idx = 0;
    token = strtok(buffer, " ");
    while (token != nullptr) {
        iarr[idx++] = atoi(token);
        token = strtok(NULL, " ");
    }
    iarrLen = idx;

    cout << "Ener unsigned char array: " << endl;
    idx = 0;
    while ((ch = getchar()) != '\n')
        ucarr[idx++] = ch;
    ucarr[idx] = '\0';
    ucarrLen = idx;

    swapArrHalf(ucarr, ucarrLen);
    swapArrHalf(iarr, iarrLen);

    cout << "Int array: " << endl;
    for (int i = 0; i < iarrLen; i++)
        cout << iarr[i] << ' ';
    cout << endl;

    cout << "Unsigned char array: " << endl;
    cout << ucarr << endl;

    delete[] ucarr;
    delete[] iarr;
    delete[] buffer;
    delete[] token;
    exit(EXIT_SUCCESS);
}

template <class T> void swapArrHalf(T *arr, size_t size) {
    int middle = (size / 2) - 1, temp;
    for (int i = 0; i <= middle / 2; i++) {
        temp = arr[i];
        arr[i] = arr[middle - i];
        arr[middle - i] = temp;
    }
}
