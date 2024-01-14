#include "arr.h"

int countElments(int *arr, int len) {
    int count = 0;
    for (int i = 0; i < len; i++)
        if (arr[i] % 3 == 0)
            count++;
    return count;
}

int *inputIntArray(int len) {
    int *result = new int[len];
    for (int i = 0; i < len; i++) {
        cin >> result[i];
    }
    return result;
}

void outputIntArray(int *arr, int len) {
    for (int i = 0; i < len; i++)
        cout << arr[i] << '\t';
    cout << endl;
}
