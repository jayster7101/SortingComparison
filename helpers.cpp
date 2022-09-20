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
                        std::cout << "previous before " << ch << " was ( " << prev << " )" << std::endl;
                        out << ch;
                    }
                    if((ch == '-' ) && (in.peek() != ' ') && prev != ' ' && !isdigit(prev) && (!isdigit(in.peek())) ) //&&  !isdigit(prev) )// (prev != ' ' || !isdigit(prev) || prev != '\n'))
                    {
                        std::cout << "previous before " << ch << " was ( " << prev << " )" << std::endl;
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
int load_data(std::string dont_want[], std::string ** array)
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
                t++;
            }
        }
    };
    *array = temp; // changes address to array we created in function
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