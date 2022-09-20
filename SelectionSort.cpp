#include "include.h"
void selectionsort(std::string a[], int to)
{
    for(int i = 0;i < to; i++)
    {
        int min = min_pos(a, i, to);
        swap(a[min],a[i]);
    }
}

int min_pos(std::string a[], int from , int to)
{
    int min_pos = from;
    std::string b;
    std::string c;
    for(int i = from+1; i <= to; i++)
    {


        if ( lower(a[min_pos]) > lower(a[i])) min_pos = i;
    }
    return min_pos;
}

std::string lower(std::string s )
{
    std::string temp;
    for(int i = 0; i < s.length(); i++)
    {
        temp += tolower(s[i]);
    }
    return temp;
    // change string to lower 
    // return string thats all lower case 

}