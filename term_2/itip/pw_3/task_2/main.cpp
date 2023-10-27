#include "StackBase.hpp"
#include "StackList.hpp"
#include "StackVector.hpp"

int main(int argc, char **argv) {
    StackBase<int> *istck;
    StackBase<unsigned char> *ucstck;
    short int state; // 0 - vector; 1 - list

    if (argc == 1 || (strstr(*++argv, "-list") == nullptr &&
                      strstr(*argv, "-vector") == nullptr)) {
        cout << "Usage: ./a.out [-list | -vector]" << endl
             << "-list   - list   stack implementation" << endl
             << "-vector - vector stack implementation" << endl;
        exit(EXIT_SUCCESS);
    }
    state = strstr(*argv, "-list") == nullptr ? 0 : 1;

    try {
        if (state == 1) {
            istck = new StackList<int>;
            ucstck = new StackList<unsigned char>;
        } else {
            istck = new StackVector<int>;
            ucstck = new StackVector<unsigned char>;
        }
    } catch (bad_alloc &xa) {
        cerr << "Error while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    unsigned short int ans = 0;
    int ival;
    unsigned char ucval;
    while (ans < 4) {
        cout << endl
             << "Enter command" << endl
             << "1. Push to stacks" << endl
             << "2. Pop from stacks" << endl
             << "3. Peek from stacks" << endl
             << "4. Exit" << endl;
        cin >> ans;
        switch (ans) {
        case 1:
            if (!istck->isFull() && !ucstck->isFull()) {
                cout << "Enter int value: ";
                while (!(cin >> ival)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << endl << "Enter unsigned char value: ";
                while (!(cin >> ucval)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                istck->push(ival);
                ucstck->push(ucval);
                break;
            } else {
                cout << "Stacks are full." << endl;
            }
        case 2:
            if (!(istck->isEmpty() || ucstck->isEmpty())) {
                cout << "Int stack value:           " << istck->pop() << endl
                     << "Unsigned char stack value: " << ucstck->pop() << endl;
            } else
                cout << "Stacks are empty." << endl;
            break;
        case 3:
            if (!(istck->isEmpty() || ucstck->isEmpty())) {
                cout << "Int stack peek:           " << istck->peek() << endl
                     << "Unsigned char stack peek: " << ucstck->peek() << endl;
            } else
                cout << "Stacks are empty." << endl;
            break;
        }
    }

    delete istck;
    delete ucstck;
    exit(EXIT_SUCCESS);
}
