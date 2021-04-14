#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//Идентификатор кладези мудрости
enum Key {
    APHORISM,
    PROVERB
};

//Структура, содержащая информацию о кладези
struct Storehouse {
    Key K; //Идентификатор кладези
    string Content; //Содержание кладези
    void* Obj; //Ссылка на кладезь
};

//Контейнер
struct Container {
    Container* Next; //Указатель на след. элемент контейнера
    Storehouse* Cont; //Указатель на кладезь
    int Len; //Разменость контейнера
};

//Структура, содержащая информацию об афоризмах
struct Aphorism {
    Key K; //Идентификатор кладези
    string Content; //Содержание афоризма
    string Author; //Автора афоризма
};

//Структура, содержащая информацию о пословицах и поговорках
struct Proverb {
    Key K; //Идентификатор кладези
    string Content; //Содержание пословицы или поговорки
    string Country; //Страна пословицы или поговорки
};

//Функция инициализации контейнера
Container* Init(Container* Head);

//Функция ввода элементов в контейнер
void In(Container* Head, ifstream& ifst);

//Функция ввода кладези
Storehouse* In_Storehouse(ifstream& ifst);

//Функция ввода афоризма
void* In_Aphorism(ifstream& ifst);

//Функция ввода пословицы или поговорки
void* In_Proverb(ifstream& ifst);

//Функция вывода элемента контейнера
void Out(Container* Head, ofstream& ofst);

//Функция вывода кладези
void Out_Storehouse(Storehouse* St, ofstream& ofst);

//Функция вывода афоризма
void Out_Aphorism(Aphorism* A, ofstream& ofst);

//Функция вывода пословицы или поговорки
void Out_Proverb(Proverb* P, ofstream& ofst);

//Функция очистки контейнера
Container* Clear(Container* Head);

int Amount(Storehouse* St);

int Amount_Storehouse(Storehouse* St);

#endif // HEADER_H
