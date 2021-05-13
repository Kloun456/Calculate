#include "Solution.h"
#include "Symbols.h"
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Solution(string& s)
{
    int i, i1, i2;
    double a, b;
    queue<int> q_signs, q_brackets;
   
    Find_sings_and_brackets(s);
    Check_on_Negative(s);
    for (int l = 0; l < c.signs_index.size(); l++)
        q_signs.push(c.signs_index[l]);
    for (int l = 0; l < c.brackets_index.size();l++)
        q_brackets.push(c.brackets_index[l]);
    while (!q_signs.empty())
    {
        i = q_signs.front();
        q_signs.pop();
        i1 = i - 1;
        i2 = i + 1;
        while (s[i1] >= '0' && s[i1] <= '9' || s[i1] == '.' || s[i1] == 'r'|| s[i1] =='(')
        {
            if (!i1)
            {
                i1 = -1;
                break;
            }
            i1--;
        }
        i1++;
       
        while (s[i2] >= '0' && s[i2] <= '9' && i2 < s.size() - 1 || s[i2] == '.' || s[i2] == ')')
            i2++;
        
        if (c.results.find(i2) != c.results.end() && c.results.find(i1) != c.results.end())
        {
            a = c.results.find(i1)->second;
            b = c.results.find(i2)->second;
            Operations(s[i], i1, a, b);
            
            for (i1; i1 < i2; i1++)
                s[i1] = 'r';
        }
        else if (c.results.find(i2) != c.results.end())
        {
            a = Convert_in_number(s, i1, i);
            b = c.results.find(i2)->second;
            Operations(s[i], i1, a, b);
            
            for (i1; i1 < i2; i1++)
                s[i1] = 'r';
        }
        else if (c.results.find(i1) != c.results.end())
        {
            a = c.results.find(i1)->second;
            b = Convert_in_number(s, i, i2);
            Operations(s[i], i1, a, b);
            
            for (i1; i1 < i2; i1++)
                s[i1] = 'r';
        }
        else
        {
            a = Convert_in_number(s, i1, i);
            b = Convert_in_number(s, i, i2);
            Operations(s[i], i1, a, b);
            
            for (i1; i1 < i2; i1++)
                s[i1] = 'r';
        }
    }
    cout << " \n" << c.results.find(0)->second;
}

void Operations(char s, int i1, double a, double b)
{
    if (c.results.find(i1) != c.results.end())
        c.results.erase(i1);
    if (s == '*')
        c.results.insert(make_pair(i1, a * b));
    else if (s == '/')
        c.results.insert(make_pair(i1, a / b));
    else if (s == '+')
        c.results.insert(make_pair(i1, a + b));
    else if (s == '-')
        c.results.insert(make_pair(i1, a - b));
    else if (s == '^')
        c.results.insert(make_pair(i1, pow(a, b)));
}

float Convert_in_number(string& s, int index1, int index2) // преобразует строку в число 
{
    int i, j, b = 0;
    double x = 0;
    for (i = index1; i <= index2; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (s[i] == '.')
            {
                if (index2 == s.size()-1)
                    b = index2 - i;
                else
                    b = index2 - i - 1;
            }
            else if (s[i] == c.s_numbers[j])
            {
                if (x == 0)
                    x = c.numbers[j];
                else
                    x = x * 10 + c.numbers[j];
            }
        }
    }
    if (b) // если число дробное
        return x / pow(10, b);
    else
        return x;
}

void Find_brackets(string& s) // поиск скобок записывает индексы в массив
{
    // запись скобок настроена как приоритетная
    int i, i1;
    vector<char> brackets;
    vector<int> index;
    for (i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            brackets.push_back(s[i]);
            index.push_back(i);
        }
    }
    for (int i = 0; i < brackets.size(); i++)
    {
        if (brackets[i] == '(')
            i1 = i;
        else
        {
            brackets.erase(brackets.begin() + i1);
            brackets.erase(brackets.begin() + i - 1);
            c.brackets_index.push_back(index[i1]);
            c.brackets_index.push_back(index[i]);
            index.erase(index.begin() + i1);
            index.erase(index.begin() + i - 1);
            i = -1;
        }
    }
}

void Find_signs(string& s, int begin, int end) // поиск мат.знаков записывает индексы в массив
{
    // запись знаков в приоритетности
    for (int i = begin; i < end; i++)
        if (s[i] == '^')
            c.signs_index.push_back(i);
    for (int i = begin; i < end; i++)
        if (s[i] == '*' || s[i] == '/')
            c.signs_index.push_back(i);
    for (int i = begin; i < end; i++)
        if (s[i] == '+' || s[i] == '-')
            c.signs_index.push_back(i);
}

void Find_sings_and_brackets(string& s) // переделать поиск знаков
{
    int i = 0, i1 = 0, temp = 0;
    vector<int> indexs;
    Find_brackets(s);
    string copy_s;
    copy_s = s.substr(0, s.size() - 1);
    for (int j = 0; j < c.brackets_index.size(); j++)
        indexs.push_back(c.brackets_index[j]);
    // поиск знаков в скобках
    if (!c.brackets_index.empty())
    {
        auto it = indexs.begin();
        while (!indexs.empty())
        {
            Find_signs(copy_s, indexs[i], indexs[i + 1]);
            for (indexs[i]; indexs[i] < indexs[i + 1]; indexs[i]++)
                copy_s[indexs[i]] = 'r';
            if (indexs.size() == 2)
                indexs.clear();
            else
            {
                it = indexs.begin();
                indexs.erase(it);
                it = indexs.begin();
                indexs.erase(it);
            }
        }
    }
    Find_signs(copy_s, 0, copy_s.size());
}

void Check_on_Negative(string &s)
{
    int i1, i2, j;
    double x;
    auto it_sign = c.signs_index.begin();
    if (!c.signs_index.empty())
    {
        for (int i = 0; i < c.signs_index.size(); i++)
        {
            if (s[c.signs_index[i]] == '-')
            {
                if (c.signs_index[i] == 0)
                {
                    if (c.results.find(1) != c.results.end())
                    {
                        x = -c.results.find(1)->second;
                        c.results.erase(1);
                        c.results.insert(make_pair(1,x));
                    }
                    else
                    {
                        i2 = i1 = 1;
                        while (s[i2] >= '0' && s[i2] <= '9' && i2 < s.size() - 1 || s[i2] == '.')
                            i2++;
                        x = Convert_in_number(s, i1, i2);
                        i1 = 0;

                        c.results.insert(make_pair(i1, -x));
                        it_sign = c.signs_index.begin();
                        it_sign += i;
                        c.signs_index.erase(it_sign);
                        for (i1; i1 < i2; i1++)
                            s[i1] = 'r';
                        i--;
                    }
                    
                }
                else if (s[c.signs_index[i] - 1] == '(')
                {
                    i1 = c.signs_index[i] + 1;
                    i2 = i1;
                    while (s[i2] >= '0' && s[i2] <= '9' && i2 < s.size() - 1 || s[i2] == '.' || s[i2] == ')')
                        i2++;
                    if (i2 == s.size())
                        i2--;
                    x = Convert_in_number(s, i1, i2);
                    
                    i1 = c.signs_index[i] - 1;
                    if (s[i2 - 1] == ')')
                    {
                        j = 0;
                        while (c.brackets_index[j] != i1)
                            j++;
                        auto it_bracket = c.brackets_index.begin();
                        c.brackets_index.erase(it_bracket + j);

                        j = 0;
                        while (c.brackets_index[j] != i2 - 1)
                            j++;
                        it_bracket = c.brackets_index.begin();
                        c.brackets_index.erase(it_bracket + j);
                        
                    }
                    
                    c.results.insert(make_pair(i1, -x));
                    it_sign += i;
                    c.signs_index.erase(it_sign);
                    
                    for (i1; i1 < i2; i1++)
                        s[i1] = 'r';
                    i--;
                }
            }
        }
    }
}