//
// Created by Sergey on 02.03.2016.
//Хедер обьяви обьєкту

#ifndef NEWONE_RSA_H
#define NEWONE_RSA_H
#include <cstdlib>
#include <iostream>
//розмір масиву чисел,де кожна комірка 32 біта
const unsigned int N=64;
class RSA {
//private:
public:
    //масив чисел
    unsigned int A[N*2];
    //к-ть заповнених комірок масиву
    unsigned int n;
    // допоміжний прапорець розпізнавання додавання як суми, чи віднімання інвесіею
    bool f;
public:
    // конструктор обєкта
    RSA();
    // метод вводу обєкта
    RSA Input (int=0);
    // метод виводу обєкта
    void Output(char);
    // метод інверсії обєкту
    RSA Invert();
    // порівняння обєктів
    int operator>(RSA&);
    int operator<(RSA&);
    int operator==(RSA&);
    // операція додавання обєктів
    RSA operator+(RSA&);
    // операція віднімання обєктів
    RSA operator-(RSA&);
    // операція добутку обєктів
    RSA operator*(RSA&);
    // операція модуляції обєктів
    RSA operator%(RSA&);
    // метод зсуву обєктів на введене значення
    RSA Sl(int=1);
    // метод модулярного експоненціювання
    RSA PowMod(RSA,RSA);
};
// метод побудови таблиці зсунутого модуля, для редукції
RSA* Tab(RSA,RSA*);
#endif //NEWONE_RSA_H
