#pragma once
#include <string>
#include <queue>
#include <map>

using namespace std;

struct Symbols
{
    const string s_numbers = "0123456789";
    const int numbers[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    vector <int> signs_index;
    vector <int> brackets_index; 
    map <int, double> results;
}c;
