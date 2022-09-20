#include "include.h"
#include <iostream> // take out before submit

int main()
{
    std::string arr[] = {"an", "the", "a"};
    std::string *data;
    process_data();
    int size = load_data(arr,&data);
    selectionsort(data, size);
    for(int i = 0; i < 20; i++)
    {
        std::cout << data[i] + " ";
    }

}
