#pragma once
#include <string>
#include <queue>
#include <map>

using namespace std;

struct Symbols
{
    const string s_numbers = "0123456789";
    const int numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector <int> signs_index; // индексы математ. знаков
    vector <int> brackets_index; // индексы скобок
    map <int, double> results; // результаты линейных вычислений ханятся в виде: индекс-результат
}c;