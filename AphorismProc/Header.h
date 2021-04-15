#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//������������� ������� ��������
enum Key {
    APHORISM,
    PROVERB,
    RIDDLE
};

//���������, ���������� ���������� � �������
struct Storehouse {
    Key K; //������������� �������
    string Content; //���������� �������
    void* Obj; //������ �� �������
    int Estimation; //������������ ������ ���������
};

//���������
struct Container {
    Container* Next; //��������� �� ����. ������� ����������
    Storehouse* Cont; //��������� �� �������
    int Len; //���������� ����������
};

//���������, ���������� ���������� �� ���������
struct Aphorism {
    Key K; //������������� �������
    string Content; //���������� ��������
    string Author; //������ ��������
    int Estimation;
};

//���������, ���������� ���������� � ���������� � ����������
struct Proverb {
    Key K; //������������� �������
    string Content; //���������� ��������� ��� ���������
    string Country; //������ ��������� ��� ���������
    int Estimation;
};

//���������, ���������� ���������� � ��������
struct Riddle {
    Key K;
    string Content;
    string Answer;
};

//������� ������������� ����������
Container* Init(Container* Head);

//������� ����� ��������� � ���������
void In(Container* Head, ifstream& ifst);

//������� ����� �������
Storehouse* In_Storehouse(ifstream& ifst);

//������� ����� ��������
void* In_Aphorism(ifstream& ifst);

//������� ����� ��������� ��� ���������
void* In_Proverb(ifstream& ifst);

void* In_Riddle(ifstream& ifst);

//������� ������ �������� ����������
void Out(Container* Head, ofstream& ofst);

//������� ������ �������
void Out_Storehouse(Storehouse* St, ofstream& ofst);

//������� ������ ��������
void Out_Aphorism(Aphorism* A, ofstream& ofst);

//������� ������ ��������� ��� ���������
void Out_Proverb(Proverb* P, ofstream& ofst);

void Out_Riddle(Riddle* R, ofstream& ofst);

//������� ������� ����������
Container* Clear(Container* Head);

int Amount(Storehouse* St);

int Amount_Storehouse(Storehouse* St);

bool Compare(Container* First, Container* Second);

void Sort(Container* Head);
#endif // HEADER_H
