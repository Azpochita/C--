#include "a4_base.h"
#include "a4_sort_implementations.h"
#include "test.h"
#include <cassert>
#include <string>

#include <iostream>
#include <fstream>
int main( )
{
    int N = 2000;

    std::ofstream myfile;
    myfile.open ("OUTPUT.csv");
    myfile << "sort_name, vector_size, num_comparisons, cpu_running_time_sec\n";
    int temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsBubble = bubble_sort(v);
        myfile << statsBubble.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsInsertion = insertion_sort(v);
        myfile << statsInsertion.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsSelection = selection_sort(v);
        myfile << statsSelection.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsMerge = merge_sort(v);
        myfile << statsMerge.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsQuick = quick_sort(v);
        myfile << statsQuick.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsShell = shell_sort(v);
        myfile << statsShell.to_csv() << endl;
        temp += 2000;
    }
    //next loop
    temp = N;
    for(int ind = 0; ind < 25; ind++)
    {   
        vector<int> v = rand_vec(temp, 1, temp);
        SortStats statsStd = iquick_sort(v);
        myfile << statsStd.to_csv() << endl;
        temp += 2000;
    }

    myfile.close();
    cout << "Done!" << endl;
    return 0;
}