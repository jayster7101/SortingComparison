#include "include.h"
#include <iostream> // take out before submit

int main()
{
    greet();
    bool dec = enter();
    double results1[20];
    double results2[20];

    while(dec)
    {
         run_algo(results1);
         std::cout << "Be sure to use the same algorithms you choose in the first step if your goal is to compare speed.\n";
         run_algo(results2);
         find_avg(results1,results2);
        std::cout << "Would you like to try the program again?\n-> ";
        dec = enter();
        
    }
    std::cout << "Have a great day. I hope you enjoyed my project";
        
    // std::string arr[] = {"an", "the", "a"};

    //     std::string *data;
    //     process_data();
        // int size = load_data(arr,&data);
        //  size = load_data(arr,&data);

    //run_algo();

//     int size = load_data(arr,&data);
//    std::cout << data[0];
     // std::string *copy = data;
    //std::cout << "Selection sort " << selectionsortTimer(data, size);
    // std::cout << "\n Insertion sort " << insertionsortTimer(data, size);
    // std::cout << "\n Insertion sort " << insertionsortTimer(data, size);
    // std::cout << "\n Bubble sort " << bubblesortTimer(data, size);
     //std::cout << "\n Bubble sort " << bubblesortTimer(data, size);
    //std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
    // std::cout << "\n quick sort #1 " << quicksortTimer(data, 0, size);
    // std::cout << "\n quick sort #2 " << quicksortTimer(data, 0, size);
    //int *n = pick_algo();

    //  std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
//     std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
//    std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
//       std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
//         std::cout << "\n merge sort " << mergesortTimer(data, 0, size);
    // for(int i = 0; i < 50; i++)
    // {
    //     std::cout << data[i] + " ";
    // }

}
