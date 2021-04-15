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
    int K; //������������� �������
    ifst >> K; //��������� �� ����� ������������� �������
    if (K == 1) //���� K == 1, �� ��� ��������
    {
        St->K = APHORISM; //���������� ��, ��� ��� ��������
        St->Obj = In_Aphorism(ifst); //��������� ���������� �� ��������
        Aphorism* Temp_A = (Aphorism*)St->Obj; //�������� ������ �� ��������
        St->Content = Temp_A->Content; //���������� � ����� �������� ����������
        St->Estimation = Temp_A->Estimation;
        return St;
    }
    else if (K == 2) //���� K == 2, �� ��� ��������� ��� ���������
    {
        St->K = PROVERB; //���������� ��, ��� ��� ��������� ��� ���������
        St->Obj = In_Proverb(ifst); //��������� ���������� � ��������� ��� ���������
        Proverb* Temb_P = (Proverb*)St->Obj; //�������� ���������� � ��������� ��� ���������
        St->Content = Temb_P->Content; //���������� � ����� �������� ����������
        St->Estimation = Temb_P->Estimation;
        return St;
    }
    else if (K == 3)
    {
        St->K = RIDDLE;
        St->Obj = In_Riddle(ifst);
        Riddle* Temp_R = (Riddle*)St->Obj;
        St->Content = Temp_R->Content;
        St->Estimation = Temp_R->Estimation;
        return St;
    }
    else
    {
        return 0;
    }
}

void* In_Aphorism(ifstream& ifst) {
    Aphorism* A = new Aphorism; //�������� ������ ��� ��������

    string Temp_El = ""; //����� ��� ���������� �����

    //��������� ���������� ��������
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        A->Content += Temp_El + " ";
    }

    A->Content += Temp_El;

    //��������� ������ ��������
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        A->Author += Temp_El + " ";
    }

    A->Author += Temp_El;

    ifst >> A->Estimation;

    return A;
}

void* In_Proverb(ifstream& ifst) {
    Proverb* P = new Proverb; //�������� ������ ��� ��������� ��� ���������

    string Temp_El = ""; //����� ��� ���������� �����

    //��������� ����������
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        P->Content += Temp_El + " ";
    }

    P->Content += Temp_El;

    //��������� ������
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        P->Country += Temp_El + " ";
    }

    P->Country += Temp_El;

    ifst >> P->Estimation;

    return P;
}

void* In_Riddle(ifstream& ifst) {
    Riddle* R = new Riddle; //�������� ������ ��� �������

    string Temp_El = ""; //����� ��� ���������� �����

    //��������� ����������
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        R->Content += Temp_El + " ";
    }

    R->Content += Temp_El;

    //��������� �����
    while (!(ifst >> Temp_El) || (ifst.peek() != '\n'))
    {
        R->Answer += Temp_El + " ";
    }

    R->Answer += Temp_El;

    ifst >> R->Estimation;

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
        Out_Aphorism((Aphorism*)St->Obj, ofst); //������� ���������� �� ��������
    }
    else if (St->K == PROVERB)
    {
        Out_Proverb((Proverb*)St->Obj, ofst); //������� ���������� � ���������� � ����������
    }
    else if (St->K == RIDDLE)
    {
        Out_Riddle((Riddle*)St->Obj, ofst);
    }
    else
    {
        ofst << "Incorrect element!" << endl;
    }
}

void Out_Aphorism(Aphorism* A, ofstream& ofst) {
    ofst << "It's an Aphorism: " << A->Content << endl; //������� ����������
    ofst << "Aphorism's author is: " << A->Author << endl; //������� ������
    ofst << "Subjective estimation of the adage: " << A->Estimation << endl;
}

void Out_Proverb(Proverb* P, ofstream& ofst) {
    ofst << "It's a Proverb: " << P->Content << endl; //������� ����������
    ofst << "Proverbs's country is: " << P->Country << endl; //������� ������
    ofst << "Subjective estimation of the adage: " << P->Estimation << endl;
}

void Out_Riddle(Riddle* R, ofstream& ofst) {
    ofst << "It's a Riddle: " << R->Content << endl; //������� ����������
    ofst << "Riddle's answer is: " << R->Answer << endl; //������� �����
    ofst << "Subjective estimation of the adage: " << R->Estimation << endl;
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
        return Amount(St);
    }
    else
    {
        return -1;
    }
}

int Amount(Storehouse* St) {
    if (St->K == APHORISM || St->K == PROVERB || St->K == RIDDLE)
    {
        string Alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
        int Amount = 0;

        for (int i = 0; i < St->Content.size(); i++)
        {
            bool Check = false;

            for (int j = 0; j < Alph.size(); j++)
            {
                if (St->Content[i] == Alph[j])
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
    else
    {
        return -1;
    }
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