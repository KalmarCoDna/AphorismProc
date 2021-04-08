#include "Header.h"

Container* Init(Container* Head) {
    Head = new Container(); //Выделяем память под новый узел 
    Head->Cont = NULL; //Пока кладезей нет 
    Head->Len = 0; //Контейнер пустой
    Head->Next = Head; //Указатель на след. элемент указывает на самый первый узел,
                        //т.к. это кольцевой список

    return Head;
}

void In(Container* Head, ifstream& ifst) {
    Container* Temp, * P; //Временные узлы, в которых будем фиксировать промежуточную информацию
    int Len = 0; //Сюда будем писать количество узлов
    while (!ifst.eof())
    {
        Temp = new Container();

        //Заполняем первый узел
        if (Len == 0)
        {
            if ((Head->Cont = In_Storehouse(ifst)) != 0) //Считываем информацию о кладези
            {
                Len++;
            }
        }
        else //Заполняем все остальные узлы
        {
            if ((Temp->Cont = In_Storehouse(ifst)) != 0)
            {
                P = Head->Next; //Фиксируем указатель на след. элемент (начало списка)
                Head->Next = Temp; //Текущий узел теперь указывает на новый
                Temp->Next = P; //Новый узел теперь указывает на начало списка
                Head = Temp; //Записываем новое начало списка
                Len++;
            }
        }
    }

    //Записываем размерность контейнера в каждом узле
    for (int i = 0; i < Len; i++)
    {
        Head->Len = Len;
        Head = Head->Next;
    }
}

Storehouse* In_Storehouse(ifstream& ifst) {
    Storehouse* St = new Storehouse; //Выделяем память под кладезь
    int K; //Идентификатор кладези
    ifst >> K; //Считываем из файла идентификатор кладези
    if (K == 1) //Если K == 1, то это афоризма
    {
        St->K = APHORISM; //Записывает то, что это афоризма
        St->Obj = In_Aphorism(ifst); //Считываем информацию об афоризма
        Aphorism* Temp_A = (Aphorism*)St->Obj; //Получаем данные об афоризма
        St->Content = Temp_A->Content; //Записываем в общий параметр содержание
        return St;
    }
    else if (K == 2) //Если K == 2, то это пословица или поговорка
    {
        St->K = PROVERB; //Записываем то, что это пословица или поговорка
        St->Obj = In_Proverb(ifst); //Считываем информацию о пословице или поговорке
        Proverb* Temb_P = (Proverb*)St->Obj; //Получаем информацию о пословице или поговорке
        St->Content = Temb_P->Content; //Записываем в общий параметр содержание
        return St;
    }
    else
    {
        return 0;
    }
}

void* In_Aphorism(ifstream& ifst) {
    Aphorism* A = new Aphorism; //Выделяем память под афоризма

    string Temp_El = ""; //Буфер для считывания строк

    //Считываем содержание афоризма
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        A->Content += Temp_El + " ";
    }

    A->Content += Temp_El;

    //Считываем автора афоризма
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        A->Author += Temp_El + " ";
    }

    A->Author += Temp_El;

    return A;
}

void* In_Proverb(ifstream& ifst) {
    Proverb* P = new Proverb; //Выделяем помать под пословицу или поговорку

    string Temp_El = ""; //Буфер для считывания строк

    //Считываем содержание
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        P->Content += Temp_El + " ";
    }

    P->Content += Temp_El;

    //Считываем страну
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        P->Country += Temp_El + " ";
    }

    P->Country += Temp_El;

    return P;
}

void Out(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl; //Выводим информацию о размерности контейнера

    for (int i = 0; i < Head->Len; i++)
    {
        ofst << i << ": "; //Выводим номер узла
        Out_Storehouse(Head->Cont, ofst); //Выводим информацию о кладези
        Head = Head->Next; //Переходим к след. узлу
    }
}

void Out_Storehouse(Storehouse* St, ofstream& ofst) {
    if (St->K == APHORISM)
    {
        Out_Aphorism((Aphorism*)St->Obj, ofst); //Выводим информацию об афоризма
    }
    else if (St->K == PROVERB)
    {
        Out_Proverb((Proverb*)St->Obj, ofst); //Выводим информацию о пословицах и поговорках
    }
    else
    {
        ofst << "Incorrect element!" << endl;
    }
}

void Out_Aphorism(Aphorism* A, ofstream& ofst) {
    ofst << "It's an Aphorism: " << A->Content << endl; //Выводим содержание
    ofst << "Aphorism's author is: " << A->Author << endl; //Выводим автора
}

void Out_Proverb(Proverb* P, ofstream& ofst) {
    ofst << "It's a Proverb: " << P->Content << endl; //Выводим содержание
    ofst << "Proverbs's country is: " << P->Country << endl; //Выводим страну
}

Container* Clear(Container* Head) {
    int Len = Head->Len; //Фиксируем размерность контейнера

    while (Len > 0) //Пока размерность контейнера не 0
    {
        free(Head->Cont); //Очищаем память, замнимаемую структурой информации о животном
        Head->Len = 0; //Указываем размерность контейнера для одного его узал 0
        Head = Head->Next; //Переходим к след. элементу контейнера
        Len--; //Уменьшаем зафиксированную длину
    }
    return Head;
}