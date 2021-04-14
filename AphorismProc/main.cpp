// 2lab_Sort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }
    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);
    cout << "Start" << endl;

    Container* Head = new Container();

    Head = Init(Head);

    In(Head, ifst);
    ofst << "Filled container. " << endl;

    Sort(Head);

    Out(Head, ofst);

    Head = Clear(Head);
    ofst << "Empty container. " << endl;
    Out(Head, ofst);

    cout << "Stop" << endl;
    system("pause");
    return 0;
}