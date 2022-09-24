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


int load_data(std::string dont_want[], std::string** array)
{
    int size =  ( sizeof(dont_want[0]) / (sizeof(dont_want)));
    std:: ifstream in;
    in.open("temp.txt");
    std::string line = "";
    std::string current = "";
    int count = 0;
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
    // std::cout << "Before in.close" << std::endl;
    in.close();
    in.open("temp.txt");
    std::string *temp = new std::string[count];
    // std::cout << "after new is called " << std::endl;
   
    int t = 0;
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
                // std::cout << "before temp[t] = current" << std::endl; 
               temp[t] = current;
            //    std::cout << "after temp[t] = current" << std::endl; 
                //std::cout << array[t];
                t++;
            }
        }
        // std::cout << "before array = temp" << std::endl;
        *array = temp;
        // std::cout << "after array = temp" << std::endl;
        //delete []temp;
        // std::cout << "after delete temp" << std::endl;
         
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
    std::cout << "Great, we will get that started. This could take a minute...\n";
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

int run_time_call(std::string wrong_words[], std::string **data, double address[], int first, int second)
{
    

    int size = load_data(wrong_words,data);
    double algo1[5];
    double algo2[5]; 
    for(int k  =  0; k < 2 ; k++)
{        
    if(k == 1) {mergesortTimer(*data,0,size);}
    for(int i = 0; i < 5; i++)
        {
            std::string runner[size];
            copy(runner,*data,size);
            switch (first)
            {
            case 1:
                if(k > 1) {algo1[i] = selectionsortTimer(*data,size); break;}
                else {algo1[i] = selectionsortTimer(runner,size); break;}
            case 2:
                if(k > 1) {algo1[i] = insertionsortTimer(*data,size); break;}
                else {algo1[i] = insertionsortTimer(runner,size); break;}
            case 3:
                if(k > 1) {algo1[i] = bubblesortTimer(*data, size); break;}
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
                if(k > 1) {algo2[i] = mergesortTimer(*data, 0 , size); break;}
                else {algo2[i] = mergesortTimer(runner, 0 , size); break;}
            case 5:
                if(k > 1) {algo2[i] = quicksortTimer(*data, 0 , size); break;}
                else {algo2[i] = quicksortTimer(runner, 0 , size); break;}
            } 
        }
    for(int i = 0; i < 5; i++)
    {
        if(k == 0 ) // unsorted times
        {
            address[i] = algo1[i]; // unsorted n^2 0 - 4 
            address[i + 5] = algo2[i]; // unsorted n log(n) = 5 - 9
        }
        if(k == 1)
        {
            address[i+10] = algo1[i]; // sorted n^2 10 - 14 
            address[i + 15] = algo2[i];  // sorted n log(n) = 15 - 19
        }
    }
        
}
    //double send[10];


return size;

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

void run_algo(double results[])
{
    {    
        std::string arr[] = {"an", "the", "a"};
        std::string *data;
        process_data();
        int *n = pick_algo();
        int first = n[0];
        int second = n[1];
        int a[] = {first,second};
    
        double short_file[20];
        int size = run_time_call(arr, &data, short_file, first, second);
        print_time(short_file,20, a);
        print_last(data,size);
        copy_results(results,short_file,20);
        //delete data;
        delete n;
    }
}

void print_time(double values[], int size , int algo[])
{
    std::string Algo1 = "Algorithm 1 (n^2)";
    std::string Algo2 = "Algorithm 2 (nlog(n))";
    std::string algo1 = "";
    std::string algo2  ="";
    std::string algo1_type ="";
    std::string algo2_type  ="";
    for(int i = 0; i < 2; i++){
    switch(algo[i])
    {
    case 1:
    algo1 = "Selection Sort";
    algo1_type= "n^2";
        break;
    case 2:
        algo1 = "Insertion Sort";
        algo1_type= "n^2";
        break;
    case 3:
        algo1 = "Optimized Bubble Sort";
        algo1_type= "n^2";
        break;
    case 4:
        algo2 = "Merge Sort";
        algo2_type ="nlog(n)";
        break;
    case 5:
        Algo2 = "Quick Sort";
        algo2_type ="nlog(n)";
        break;
    default:
        break;
    }
    }


    // values for controlling format
    const std::string sep = " |" ;

    std::cout << " |-------------------------------------------------------------------------------------|" << '\n' << sep << 
              std::left << std::setw(algo1.length()) << "Algorithm" << sep << std::setw(18) << "Complexity" << sep
              << std::setw(18) << "Realized run time" << sep << std::setw(21) << "Sorted/un-sorted" << sep << std::endl;
    std::cout << " |-------------------------------------------------------------------------------------|" << std::endl;

    for( int i = 0 ; i < 5 ; ++i )
    {
        std::cout << sep << std::setw(algo1.length()) << algo1 << sep << std::setw(18) << algo1_type << sep << std::setw(18)<<std::setprecision(8) <<  values[i] << sep << std::setw(21) <<  "Un-Sorted "<< sep   <<std::endl;
    }
    for( int i = 10 ; i < 15 ; ++i )
    {
        std::cout << sep << std::setw(algo1.length()) << algo1 << sep << std::setw(18) << algo1_type << sep << std::setw(18) <<std::setprecision(8) <<  values[i] << sep << std::setw(21) <<  "Sorted "<< sep  <<std::endl;
    }



        for( int i = 5 ; i < 10 ; ++i )
    {
        std::cout << sep << std::setw(algo1.length()) << algo2 << sep << std::setw(18) <<  algo2_type << sep << std::setw(18) << std::setprecision(8) << values[i] << sep << std::setw(21) <<   "Un-Sorted "<< sep <<std::endl;
//       << std::setw(dbl_width) << netpay << sep << '\n' ;
    }
            for( int i = 15 ; i < 20 ; ++i )
    {
        std::cout << sep << std::setw(algo1.length()) << algo2 << sep << std::setw(18) <<  algo2_type << sep << std::setw(18) <<std::setprecision(8) <<  values[i] << sep << std::setw(21)  <<  "Sorted "<< sep <<std::endl;
//       << std::setw(dbl_width) << netpay << sep << '\n' 
    }
    std::cout << " |-------------------------------------------------------------------------------------|" << std::endl;
    //std::cout << std::cout << "|--------------------------------------------------------------------------------------|" << '\n' << sep << '\n' ;

    std::cout << "ASSESSMENT of Algorithm 1:\n" << "    Algorithm 1 would be classified as n^2. Meaning that as the data set get larger, the time taken to complete an operation would be that squared."  << std::endl << std::endl;
    std::cout << "ASSESSMENT of Algorithm 2:\n" << "    Algorithm 2 would be classified as n log(n). Meaning that its generally more efficient because the growth rate is negligible compared to n^2. To accomplish this, a halving method is applied to quickly sort less and less items." <<  std::endl <<  std::endl;
}

// void handle_offset(double [], double [])
// {
// }


   void greet()
   {
        std::cout << "Hello Welcome to my algorithm comparison project! You will be able to run a handful of popular algorithms against each other.\n";
        std::cout << "Would you like to enter the program?\n";
        std::cout<< "Please enter yes or no?\n> ";
   }
 
/**
* @brief gets the users responce to yes or no questions
* @param  NONE
* @return bool true if the answer is yes, false if the answer is no
*/
bool enter()
{
   bool return_value;
   std::string yes_no;
   bool reprompt = false;
       while(!reprompt) // this is the first instance of input validation which only accepts yes or Yes or No or no and will keep prompting until valid
       {
           if(std::cin.fail()) std::cin.ignore(100,'\n'); // ignores the flag on the error
           std::cin >> yes_no;
           if(yes_no =="yes" || yes_no =="Yes")// the logic below compares the string to the 4 possible values, and then returns true or false to either enter the if statement or skip to the else statement in the main function
           {
               reprompt = true;
               return_value = true;
           }
           else if (yes_no =="no" || yes_no =="No")
           {
               reprompt = true;
               return_value = false;
           }
           else
           {
               std::cout<<"Please enter yes or no only\n> ";
           }
       }
   return return_value;
}

void print_last(std::string a[], int s)
{
    int l = 0;
    int total_l = 0;
    std::cout << "_____________________________________________________" << std::endl;
    std::cout << std::setw(52) << "|Here are the First 50 words from the sorted list" << "|" << std::endl;
    std::cout << "|___________________________________________________|" << std::endl;
    std::cout << "|";
    for (int i = 0; i < 50; i++) 
    {
        if(l == 5)
        {
            std::cout << std::setw(51 - total_l) << " " << "|";
            std::cout << std::endl;
            std::cout << "|";
            l = 0;
            total_l = 0;
        }
        std::cout << a[i] << " ";
        total_l += a[i].length() + 1;
        l++;
    }
    std::cout << std::setw(21) << " " << "|"<< std::endl;
    std::cout << "_____________________________________________________" << std::endl;
    l = 0;
    total_l = 0;
    std::cout << std::endl;
    std::cout << "|___________________________________________________|" << std::endl;
    std::cout << std::setw(52) << "|Here are the Last 50 words from the sorted list" << "|" << std::endl;
    std::cout << "|___________________________________________________|" << std::endl;
    std::cout << "|";
    for (int i = s-50; i < s; i++)
    {
        if(l == 5)
        {
            std::cout << std::setw(51 - total_l) << " " << "|";
            std::cout << std::endl;
            std::cout << "|";
            l = 0;
            total_l = 0;
        }
        std::cout << a[i] << " ";
        l++;
        total_l += a[i].length() + 1; 
    }
    std::cout << std::setw(21) << " " << "|" << std::endl;
    std::cout << "|___________________________________________________|" << std::endl;
    std::cout << std::endl;

}


void copy_results(double a[], double b[], int size)
{
    for(int i = 0; i < size; i++)
    {
        a[i] = b[i];
    }
}

void find_avg(double first[], double second[])
{
    double file_s[20];
    double file_l[20];

    double run1A1UN = 0;
    double run1A1S = 0;
    double run1A2UN  = 0;
    double run1A2S = 0;
    double run2A1UN = 0;
    double run2A1S = 0;
    double run2A2UN = 0;
    double run2A2S = 0;
    // for(int i = 0; i < 5; i++)
    //     {
    //         avg += first[i]; // unsorted n^2 0 - 4 
    //         run1UN[i] = first[i+10]; // unsorted n^2 0 - 4 

    //         file_s[i+10] = first[i]; // sorted n^2 10 - 14 
    //     }
    for (int i = 0; i < 20; i++)
    {
        if(i < 5) run1A1UN += first[i];
        if(i > 4 && i  < 10) run1A2UN += first[i];
        if(i > 9 && i < 15) run1A1S += first[i];
        if(i > 14 && i < 20) run1A2S += first[i];
    }

        for (int i = 0; i < 20; i++)
    {
        if(i < 5) run2A1UN += second[i];
        if(i > 4 && i  < 10) run2A2UN += second[i];
        if(i > 9 && i < 15) run2A1S += second[i];
        if(i > 14 && i < 20) run2A2S += second[i];
    }
    std ::cout << "The average run for n^2 algo on short file un-sorted is " << run1A1UN/5 << std::endl;
    std ::cout << "The average run for n^2 algo on short file sorted is " << run1A1S/5 << std::endl;
    std ::cout << "The average run for n^2 algo on Long file un-sorted is " << run2A1UN/5 << std::endl; 
    std ::cout << "The average run for n^2 algo on long file sorted is " << run2A1S/5 << std::endl;
    //<<std::setprecision(8) 
    std ::cout << "The average run for n log(n) algo on short file un-sorted is " << run1A2UN/5 << std::endl;
    std ::cout << "The average run for n log(n) algo on short file sorted is " << run1A2S/5 << std::endl;
    std ::cout << "The average run for n log(n) algo on Long file un-sorted is " << run2A2UN/5 << std::endl;
    std ::cout << "The average run for n log(n) algo on long file sorted is " << run2A2S/5 << std::endl;

    //     double t = 0;

    // std::cout << t/5 << std::endl;







    // for(int k = 0; k < 2; k++)
    // {    
    //     for(int i = 0; i < 5; i++)
    //     {
    //         if(k == 0 ) 
    //         {
    //             file_s[i] = first[i]; // unsorted n^2 0 - 4 
    //             file_s[i + 5] = first[i]; // unsorted n log(n) = 5 - 9
    //         }
    //         if(k == 1)
    //         {
    //             file_s[i+10] = first[i]; // sorted n^2 10 - 14 
    //             file_s[i + 15] = first[i];  // sorted n log(n) = 15 - 19
    //         }
    //     }
    // }

    //     for(int k = 0; k < 2; k++)
    // {    
    //     for(int i = 0; i < 5; i++)
    //     {
    //         if(k == 0 ) 
    //         {
    //             file_l[i] = first[i]; // unsorted n^2 0 - 4 
    //             file_l[i + 5] = second[i]; // unsorted n log(n) = 5 - 9
    //             file_l[i+10] = first[i]; // sorted n^2 10 - 14 
    //             file_l[i + 15] = algo2[i];  // sorted n log(n) = 15 - 19
    //         }
    //         if(k == 1)
    //         {
    //             file_l[i+10] = first[i]; // sorted n^2 10 - 14 
    //             file_l[i + 15] = algo2[i];  // sorted n log(n) = 15 - 19
    //         }
    //     }
    // }
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