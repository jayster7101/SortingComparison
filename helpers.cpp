#include "helpers.h"
#include "include.h"


std::string get_file_name()
{
    std::string file;
    bool failed = true;
    std::cout << "What is the name of the file you would like to use\n-> ";
    while(failed || std::cin.fail())
    {
        std::ifstream in;
        std::cin >> file;
        if(file.length() > 4 && file.substr(file.length() - 4,file.length()) == ".txt"){} // checks for .txt and adds if needed
        else file = file += ".txt"; 
       
        in.open(file);
        if(!in.fail())
        {
            failed = false;
            std::cout << "file accepted!\n";
            return file;
        }
        else std::cout << "Sorry that file didnt work, please try another \n-> ";


        std::cin.clear();
        std::cin.ignore();
    };


}

/**
 * @brief parses through all data and formats it to only allow (abcdefghijklmnopqrstuvwxyz-) and a single (')
 * opens temp 
 * 
 */
void process_data()
{
    std::ifstream in;
    std::ofstream out;
    out.open("temp.txt");
    std::string file = get_file_name(); // gets file name 
    in.open(file); // file will always open reason: already checked
    // bool good = true;
    char ch;
    bool previously_endl = false;
    int count = 0;
    bool previously_digit = false;
    char prev = -1;
    std::string list = "abcdefghijklmnopqrstuvwxyz- "; // suite of accepted chars
    while( count < 2) // account for any non normal file structures and allows for only 2 in.fail before stopping
    {
        in.get(ch);
        if(in.fail()) count ++;
        else 
        {
            count = 0; // reset fail safe count
            bool print = false; // auto set to not print and change if value is worth it
            if(!isdigit(ch)) // no digits allowed 
            {
                if(ispunct(ch) || ch == '-') // only allow to print '\'' and sets print to false as its already printed 
                {
                    if((ch == '\'' ) && (in.peek() != ' ') && prev != ' ' &&  !isdigit(prev) )// (prev != ' ' || !isdigit(prev) || prev != '\n'))
                    {
                        //std::cout << "previous before " << ch << " was ( " << prev << " )" << std::endl;
                        out << ch;
                    }
                    if((ch == '-' ) && (in.peek() != ' ') && prev != ' ' && !isdigit(prev) && (!isdigit(in.peek())) ) //&&  !isdigit(prev) )// (prev != ' ' || !isdigit(prev) || prev != '\n'))
                    {

                        out << ch;
                    }
                    print = false;
                }
                else
                {
                    for(int i = 0; i < list.length();i++) // checks to see if char should be accepted 
                    {
                        if(tolower(ch) == list[i]) 
                        {
                            print = true;
                            previously_endl = false; // next interation knows that current iteration wasnt endl
                            break;
                        } else if(ch == '\n') // if endline
                        { 
                            if(!previously_endl) // of previous iteration wasnt endl
                            {
                                if(in.peek() == ' '){} else out << " "; // & next line isnt a space then print space 
                                
                            }
                            previously_endl = true; // change to previously endl 
                        }
                    }
                }
                if(previously_digit && ch != ' ') // if previous was a digit and current isnt a space dont print
                {
                    print = false;
                }
                if(print)
                {
                     
                     out << ch;
                     previously_digit = false;
                }
                print = false;
            }
            if(isdigit(ch))
            {
                previously_digit = true;
            }
        }
        prev = ch;
    }
}
// int load_data(std::string dont_want[], std::string ** array)
// {
//     int size =  ( sizeof(dont_want[0]) / (sizeof(dont_want)));
//     std:: ifstream in;
//     in.open("temp.txt");
//     std::string line;
//     std::string current;
//     int count;
//     while(getline(in,line))
//     {   
//         std::stringstream ss(line);
//         while (ss >> current)
//         {
//             bool good = true;
//             for(int i = 0; i < size; i++)
//             {
//                 if(lower(current) == dont_want[i])
//                 {
//                     good = false;
//                     break;
//                 }
//             }
//             if(good) count ++;
//         }
//     };
//     in.close();
//     in.open("temp.txt");
//     std::string *temp = new std::string[count];
//     int t;
//     while(getline(in,line))
//     {   
//         std::stringstream ss(line);
//         while (ss >> current)
//         {

//             bool good = true;
//             for(int i = 0; i < size; i++)
//             {
//                 if(lower(current) == dont_want[i])
//                 {
//                     good = false;
//                     break;
//                 }
//             }
//             if(good)
//             {    
//                 temp[t] = current;
//                 t++;
//             }
//         }
//     };
//     *array = temp; // changes address to array we created in function
//     return count;
// }

int load_data(std::string dont_want[], std::string** array)
{
    int size =  ( sizeof(dont_want[0]) / (sizeof(dont_want)));
    std:: ifstream in;
    in.open("temp.txt");
    std::string line;
    std::string current;
    int count;
    while(getline(in,line))
    {   
        std::stringstream ss(line);
        while (ss >> current)
        {
            bool good = true;
            for(int i = 0; i < size; i++)
            {
                if(lower(current) == dont_want[i])
                {
                    good = false;
                    break;
                }
            }
            if(good) count ++;
        }
    };
    in.close();
    in.open("temp.txt");
    std::string *temp = new std::string[count];
   
    int t;
    while(getline(in,line))
    {   
        std::stringstream ss(line);
        while (ss >> current)
        {

            bool good = true;
            for(int i = 0; i < size; i++)
            {
                if(lower(current) == dont_want[i])
                {
                    good = false;
                    break;
                }
            }
            if(good)
            {    
               temp[t] = current;
                //std::cout << array[t];
                t++;
            }
        }
        
         *array = temp;
         
    };
    //array = temp; // changes address to array we created in function
    return count;
}
/**
 * @brief Swaps two strings 
 * 
 * @param a 
 * @param b 
 */
void swap(std::string& a, std::string& b)
{
    std::string temp = b;
    b = a;
    a = temp;
}

int* pick_algo()
{
    int one,two = 0;
    std::cout << "Please pick a n^2 algorithm to test:\n";
    display_list(0);
    std::cout << "-> ";
    std::cin >> one;
    while( one > 3  || one < 1 || std::cin.fail())
    {
        std:: cout << "That doesn't appear to be on the current list. Please try again\n";
        display_list(0);
        std::cout << "-> ";
        std::cin >> one;
    }
    std::cout << "Please pick an log(n) algorithm to test\n";
    display_list(1);
    std::cout << "-> ";
    std::cin >> two;
    while( two > 2  || two < 1 || std::cin.fail())
    {
        std:: cout << "That doesn't appear to be on the current list. Please try again\n";
        display_list(1);
        std::cout << "-> ";
        std::cin >> two;
    }
    if(two == 1) two = 4;
    if(two == 2) two = 5;
    int *temp = new int[2];
    temp[0] = one;
    temp[1] = two;
    return temp;
    //std::cout << "Great, we will start working on running " << 


}

void display_list(int list)
{
    if(list == 0)
    {
        std::cout << "[1] Selection Sort"  << std::endl;
        std::cout << "[2] Insertion Sort"  << std::endl;
        std::cout << "[3] Optimized Bubble Sort"  << std::endl;
    }
    if(list == 1)
    {
        std::cout << "[1] Merge Sort"  << std::endl;
        std::cout << "[2] Quick Sort"  << std::endl;
    }

}

void run_time_call(std::string wrong_words[], std::string **data, bool sorted, double address[])
{
    int *n = pick_algo();
    int first = n[0];
    int second = n[1];
    int size = load_data(wrong_words,data);
    double algo1[5];
    double algo2[5];
    if(sorted)mergesortTimer(*data,0,size);
    for(int i = 0; i < 5; i++)
    {
        std::string runner[size];
        copy(runner,*data,size);
        switch (first)
        {
        case 1:
            if(sorted) {algo1[i] = selectionsortTimer(*data,size); break;}
            else {algo1[i] = selectionsortTimer(runner,size); break;}
        case 2:
            if(sorted) {algo1[i] = insertionsortTimer(*data,size); break;}
            else {algo1[i] = insertionsortTimer(runner,size); break;}
        case 3:
            if(sorted) {algo1[i] = bubblesortTimer(*data, size); break;}
            else {algo1[i] = bubblesortTimer(runner,size); break;}
        }
    }
    for(int i = 0; i < 5; i++)
    {
    std::string runner[size];
    copy(runner,*data,size);
        switch (second)
        {
        case 4:
        if(sorted) {algo2[i] = mergesortTimer(*data, 0 , size); break;}
        else {algo2[i] = mergesortTimer(runner, 0 , size); break;}
        case 5:
        if(sorted) {algo2[i] = quicksortTimer(*data, 0 , size); break;}
        else {algo2[i] = quicksortTimer(runner, 0 , size); break;}
        } 
    }
    double first_total = 0;
    double second_total = 0;
    //double send[10];
    for(int i = 0; i < 5; i++)
    {
        address[i] = algo1[i];
        address[i+5] = algo2[i];
    }



    // std::cout << "Total avg for algo 1 is " << first_total/5 << std::endl;
    // std::cout << "Total avg for algo 2 is " << second_total/5 << std::endl;
}
/**
 * @brief Takes in array and a pointer to make sure data persists and copys values from pointer to array
 * 
 * @param from 
 * @param to 
 * @param length 
 */

    void copy(std::string from[], std::string *to, int length) 
    {
        for(int i = 0; i < length; i++)
        {
            from[i] = to[i];
        }
    }
/**
 * greet user
 * repeat
 * call and analysie print
 * 
 */

void run_algo()
{
    bool same_file = false;
    //while()
    {    
        std::string arr[] = {"an", "the", "a"};
        std::string *data;
        process_data();
        bool sorted = true;
        double unsorted_data[10];
        run_time_call(arr, &data, !sorted, unsorted_data);
        std::cout << unsorted_data[0];

        double sorted_data[10];
        run_time_call(arr, &data, sorted, sorted_data);

    }
}