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
        return St;
    }
    else if (K == 2) //���� K == 2, �� ��� ��������� ��� ���������
    {
        St->K = PROVERB; //���������� ��, ��� ��� ��������� ��� ���������
        St->Obj = In_Proverb(ifst); //��������� ���������� � ��������� ��� ���������
        Proverb* Temb_P = (Proverb*)St->Obj; //�������� ���������� � ��������� ��� ���������
        St->Content = Temb_P->Content; //���������� � ����� �������� ����������
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

    return P;
}

void Out(Container* Head, ofstream& ofst) {
    ofst << "Container contains " << Head->Len
        << " elements." << endl; //������� ���������� � ����������� ����������

    for (int i = 0; i < Head->Len; i++)
    {
        ofst << i << ": "; //������� ����� ����
        Out_Storehouse(Head->Cont, ofst); //������� ���������� � �������
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
    else
    {
        ofst << "Incorrect element!" << endl;
    }
}

void Out_Aphorism(Aphorism* A, ofstream& ofst) {
    ofst << "It's an Aphorism: " << A->Content << endl; //������� ����������
    ofst << "Aphorism's author is: " << A->Author << endl; //������� ������
}

void Out_Proverb(Proverb* P, ofstream& ofst) {
    ofst << "It's a Proverb: " << P->Content << endl; //������� ����������
    ofst << "Proverbs's country is: " << P->Country << endl; //������� ������
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