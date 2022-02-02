/*
Programme qui trie et affiche un tableau dans lordre d'apparation pair/impair
\fichier   exo5.cpp
\auteurs Sawka et Martin
\date   24 janvier 2022
Créé le 17 janvier 2022
*/



#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <array>
using namespace std;

const int length = 10;


int main()
{
    static int array[length] = { 1,2,3,4,5,6,7,8,9,0 };
    static int order[length];
    int cnt = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (array[j] % 2 == i)
            {
                order[cnt++] = array[j];
            }
        }
    }

    for (int i = 0; i < length; i++)
    {
        cout << order[i];
    }
}