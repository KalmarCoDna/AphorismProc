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

    string Temp = "";

    getline(ifst, Temp);

    int K = atoi(Temp.c_str());

    if (K == 1) //Если K == 1, то это афоризма
    {
        St->K = APHORISM; //Записывает то, что это афоризма

        getline(ifst, St->Content);

        St->Obj = In_Aphorism(ifst); //Считываем информацию об афоризма
        Aphorism* Temp_A = (Aphorism*)St->Obj; //Получаем данные об афоризма

        getline(ifst, Temp);

        St->Estimation = atoi(Temp.c_str());

        return St;
    }
    else if (K == 2) //Если K == 2, то это пословица или поговорка
    {
        St->K = PROVERB; //Записываем то, что это пословица или поговорка

        getline(ifst, St->Content);

        St->Obj = In_Proverb(ifst); //Считываем информацию о пословице или поговорке
        Proverb* Temb_P = (Proverb*)St->Obj; //Получаем информацию о пословице или поговорке

        getline(ifst, Temp);

        St->Estimation = atoi(Temp.c_str());

        return St;
    }
    else if (K == 3)
    {
        St->K = RIDDLE;

        getline(ifst, St->Content);

        St->Obj = In_Riddle(ifst);
        Riddle* Temp_R = (Riddle*)St->Obj;

        getline(ifst, Temp);

        St->Estimation = atoi(Temp.c_str());

        return St;
    }
    else
    {
        return 0;
    }
}

void* In_Aphorism(ifstream& ifst) {
    Aphorism* A = new Aphorism; //Выделяем память под афоризма

    getline(ifst, A->Author);

    return A;
}

void* In_Proverb(ifstream& ifst) {
    Proverb* P = new Proverb; //Выделяем помать под пословицу или поговорку

    getline(ifst, P->Country);

    return P;
}

void* In_Riddle(ifstream& ifst) {
    Riddle* R = new Riddle; //Выделяем помать под загадку

    getline(ifst, R->Answer);

    return R;
}

void Out(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl << endl; //Выводим информацию о размерности контейнера

    for (int i = 0; i < Head->Len; i++)
    {
        ofst << i << ": "; //Выводим номер узла
        Out_Storehouse(Head->Cont, ofst); //Выводим информацию о кладези
        ofst << "Amount of punctuation marks in the content of storehouse = " << Amount_Storehouse(Head->Cont) << endl;
        Head = Head->Next; //Переходим к след. узлу
    }
}

void Out_Storehouse(Storehouse* St, ofstream& ofst) {
    if (St->K == APHORISM)
    {
        Out_Aphorism((Aphorism*)St->Obj, St->Content, St->Estimation, ofst); //Выводим информацию об афоризма
    }
    else if (St->K == PROVERB)
    {
        Out_Proverb((Proverb*)St->Obj, St->Content, St->Estimation, ofst); //Выводим информацию о пословицах и поговорках
    }
    else if (St->K == RIDDLE)
    {
        Out_Riddle((Riddle*)St->Obj, St->Content, St->Estimation, ofst);
    }
    else
    {
        ofst << "Incorrect element!" << endl;
    }
}

void Out_Aphorism(Aphorism* A, string Content, int Estimation, ofstream& ofst) {
    ofst << "It's an Aphorism: " << Content << endl; //Выводим содержание
    ofst << "Aphorism's author is: " << A->Author << endl; //Выводим автора
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
}

void Out_Proverb(Proverb* P, string Content, int Estimation, ofstream& ofst) {
    ofst << "It's a Proverb: " << Content << endl; //Выводим содержание
    ofst << "Proverbs's country is: " << P->Country << endl; //Выводим страну
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
}

void Out_Riddle(Riddle* R, string Content, int Estimation, ofstream& ofst) {
    ofst << "It's a Riddle: " << Content << endl; //Выводим содержание
    ofst << "Riddle's answer is: " << R->Answer << endl; //Выводим ответ
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
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

int Amount_Storehouse(Storehouse* St) {
    if (St->K == APHORISM || St->K == PROVERB || St->K == RIDDLE)
    {
        return Amount(St->Content);
    }
    else
    {
        return -1;
    }
}

int Amount(string Content) {
    string Alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    int Amount = 0;

    for (int i = 0; i < Content.size(); i++)
    {
        bool Check = false;

        for (int j = 0; j < Alph.size(); j++)
        {
            if (Content[i] == Alph[j])
            {
                Check = true;
                break;
            }
        }

        if (!Check)
        {
            Amount++;
        }
    }

    return Amount;
}

bool Compare(Container* First, Container* Second)
{
    return Amount_Storehouse(First->Cont) > Amount_Storehouse(Second->Cont);
}

void Sort(Container* Head) {
    if (Head->Len > 1)
    {
        Container* First = Head;
        Container* Second = Head->Next;

        Container* Temp = new Container;

        for (int i = 0; i < Head->Len - 1; i++)
        {
            for (int j = 0; j < Head->Len - i - 1; j++)
            {
                if (Compare(First, Second))
                {
                    Temp->Cont = First->Cont;
                    First->Cont = Second->Cont;
                    Second->Cont = Temp->Cont;
                }

                Second = Second->Next;
            }

            First = First->Next;
            Second = First->Next;
        }
    }
}

void Out_Only_Aphorism(Container* Head, ofstream& ofst) {
    ofst << endl << "Only Aphorisms." << endl;

    for (int i = 0; i < Head->Len; i++)
    {
        if (Head->Cont->K == APHORISM)
        {
            ofst << i << ": ";
            Out_Storehouse(Head->Cont, ofst);
            Head = Head->Next;
        }
        else
        {
            Head = Head->Next;
        }
    }
}