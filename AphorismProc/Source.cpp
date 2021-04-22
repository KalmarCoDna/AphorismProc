#include "Header.h"

Container* Init(Container* Head) {
    Head = new Container(); //�������� ������ ��� ����� ���� 
    Head->Cont = NULL; //���� �������� ��� 
    Head->Len = 0; //��������� ������
    Head->Next = Head; //��������� �� ����. ������� ��������� �� ����� ������ ����,
                        //�.�. ��� ��������� ������

    return Head;
}

void In(Container* Head, ifstream& ifst) {
    Container* Temp, * P; //��������� ����, � ������� ����� ����������� ������������� ����������
    int Len = 0; //���� ����� ������ ���������� �����
    while (!ifst.eof())
    {
        Temp = new Container();

        //��������� ������ ����
        if (Len == 0)
        {
            if ((Head->Cont = In_Storehouse(ifst)) != 0) //��������� ���������� � �������
            {
                Len++;
            }
        }
        else //��������� ��� ��������� ����
        {
            if ((Temp->Cont = In_Storehouse(ifst)) != 0)
            {
                P = Head->Next; //��������� ��������� �� ����. ������� (������ ������)
                Head->Next = Temp; //������� ���� ������ ��������� �� �����
                Temp->Next = P; //����� ���� ������ ��������� �� ������ ������
                Head = Temp; //���������� ����� ������ ������
                Len++;
            }
        }
    }

    //���������� ����������� ���������� � ������ ����
    for (int i = 0; i < Len; i++)
    {
        Head->Len = Len;
        Head = Head->Next;
    }
}

Storehouse* In_Storehouse(ifstream& ifst) {
    Storehouse* St = new Storehouse; //�������� ������ ��� �������

    string Temp = "";

    getline(ifst, Temp);

    int K = atoi(Temp.c_str());

    if (K == 1) //���� K == 1, �� ��� ��������
    {
        St->K = APHORISM; //���������� ��, ��� ��� ��������

        getline(ifst, St->Content);

        St->Obj = In_Aphorism(ifst); //��������� ���������� �� ��������
        Aphorism* Temp_A = (Aphorism*)St->Obj; //�������� ������ �� ��������

        getline(ifst, Temp);

        St->Estimation = atoi(Temp.c_str());

        return St;
    }
    else if (K == 2) //���� K == 2, �� ��� ��������� ��� ���������
    {
        St->K = PROVERB; //���������� ��, ��� ��� ��������� ��� ���������

        getline(ifst, St->Content);

        St->Obj = In_Proverb(ifst); //��������� ���������� � ��������� ��� ���������
        Proverb* Temb_P = (Proverb*)St->Obj; //�������� ���������� � ��������� ��� ���������

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
    Aphorism* A = new Aphorism; //�������� ������ ��� ��������

    getline(ifst, A->Author);

    return A;
}

void* In_Proverb(ifstream& ifst) {
    Proverb* P = new Proverb; //�������� ������ ��� ��������� ��� ���������

    getline(ifst, P->Country);

    return P;
}

void* In_Riddle(ifstream& ifst) {
    Riddle* R = new Riddle; //�������� ������ ��� �������

    getline(ifst, R->Answer);

    return R;
}

void Out(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl << endl; //������� ���������� � ����������� ����������

    for (int i = 0; i < Head->Len; i++)
    {
        ofst << i << ": "; //������� ����� ����
        Out_Storehouse(Head->Cont, ofst); //������� ���������� � �������
        ofst << "Amount of punctuation marks in the content of storehouse = " << Amount_Storehouse(Head->Cont) << endl;
        Head = Head->Next; //��������� � ����. ����
    }
}

void Out_Storehouse(Storehouse* St, ofstream& ofst) {
    if (St->K == APHORISM)
    {
        Out_Aphorism((Aphorism*)St->Obj, St->Content, St->Estimation, ofst); //������� ���������� �� ��������
    }
    else if (St->K == PROVERB)
    {
        Out_Proverb((Proverb*)St->Obj, St->Content, St->Estimation, ofst); //������� ���������� � ���������� � ����������
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
    ofst << "It's an Aphorism: " << Content << endl; //������� ����������
    ofst << "Aphorism's author is: " << A->Author << endl; //������� ������
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
}

void Out_Proverb(Proverb* P, string Content, int Estimation, ofstream& ofst) {
    ofst << "It's a Proverb: " << Content << endl; //������� ����������
    ofst << "Proverbs's country is: " << P->Country << endl; //������� ������
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
}

void Out_Riddle(Riddle* R, string Content, int Estimation, ofstream& ofst) {
    ofst << "It's a Riddle: " << Content << endl; //������� ����������
    ofst << "Riddle's answer is: " << R->Answer << endl; //������� �����
    ofst << "Subjective estimation of the adage: " << Estimation << endl;
}

Container* Clear(Container* Head) {
    int Len = Head->Len; //��������� ����������� ����������

    while (Len > 0) //���� ����������� ���������� �� 0
    {
        free(Head->Cont); //������� ������, ����������� ���������� ���������� � ��������
        Head->Len = 0; //��������� ����������� ���������� ��� ������ ��� ���� 0
        Head = Head->Next; //��������� � ����. �������� ����������
        Len--; //��������� ��������������� �����
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