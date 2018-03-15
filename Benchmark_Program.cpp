//  Fall-17 | CSC 675 [01] | Computer Performance Evaluation
//  Created by Jonas Vinter-Jensen

#include <iostream>
#include <cstdio>
#include <time.h>
#include <vector>

using namespace std;

int k_max = 30000; //Size of array to be sorted
int size = 500;

double v_int = 0, v_float = 0, avg_speed = 0;

//Pass by reference, so as to avoid copying the vectors
void initialize(vector< vector<float> > &m, int size)
{
    m.resize(size);
    for(int i = 0 ; i < size ; ++i)
    {
        //Grow Columns
        m[i].resize(size);
    }
    
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(i==j)
            {
                m[i][j] = 4.1234;
            }
            else
            {
                m[i][j] = 2.1234;
            }
        }
    }
    return;
}

//Debugging
void printArray(int a[], int size)
{
    for(int i=0; i<size; i++)
    {
        cout << "a[" << i << "] = " << a[i] << "\t";
    }
    
    return;
}

//Debugging
void printMatrix(vector< vector<float> > &m, int size) //pass by reference
{
    for (int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            cout << "m[" << i << "][" << j << "] = " << m[i][j] << "\t";
        }
    }
    return;
}

//Floating point Matrix multiplication benchmark function
unsigned long m_multiply (vector< vector<float> > &m1, vector< vector<float> > &m2, int size)
{
    unsigned long N_FLOAT = 0;
    vector< vector<float> > m3;
    m3.resize(size);
    
    for(int i = 0 ; i < size ; ++i)
    {
        //Grow Columns
        m3[i].resize(size);
    }
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            m3[i][j] = 0;
        }
    }
    
    float t = 0; //Time that the CPU was busy with the matrix multiplication
    clock_t ctick;
    ctick = clock(); //start measuring number of system-specific CPU clocks needed for process
    
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            float temp=0.0;
            for(int k=0; k<size; k++)
            {
                temp += m1[i][k] * m2[k][j];
                N_FLOAT++; //N_FLOAT: number of float multiplications performed
            }
            m3[i][j] = temp;
            
            if(m3[size-1][size-1] != 0)
            {
                ctick = clock() - ctick; //Number of clock ticks elapsed since start
                t = (float)ctick/CLOCKS_PER_SEC; //Time in secs
                //printMatrix(m3, size); //Debugging
                printf ("Clock ticks: %lu, time taken with clock() [sec]: %f seconds.\n",ctick,t);
            }
        }
    }
    
    cout << "N_FLOAT for this m_multiply() = " << N_FLOAT << "\n\n";
    return N_FLOAT;
}

//Integer select sort benchmark function
unsigned long SSORT (int a[], int n) //Pass by reference
{
    clock_t ctick;
    ctick = clock(); //start measuring number of system-specific CPU clocks needed for process
    float t = 0;
    
    static unsigned long N_INT = 0;
    
    
        for(int i=0 ; i<n-1 ; i++ )
        {
            for(int j=i+1 ; j<n ; j++ )
            {
                if( a[i] < a[j] ) //Sort in descending order from left to right
                {
                    int temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    //n_int: (number of integer comparisons, loads and stores) + (number of increments
                    //of counter i) + (number of increments of counter j).
                    N_INT++;
                }
            }
        }
    
    ctick = clock() - ctick; //Number of clock ticks elapsed since start
    t = (float)ctick/CLOCKS_PER_SEC; //Time in secs
    printf ("Clock ticks: %lu, elapsed time [sec]: %f seconds.\n",ctick,t);
    cout << "n_int for this SSORT() = " << N_INT << "\n\n";
    
    return N_INT;
}



int main(int argc, const char * argv[])
{
    //--Matrix multiplication Benchmarking--
    unsigned long N_FLOAT = 0;
    
    //Initialize two-dimensional matrix with x/y > 1, where x is a matrix entry
    //which is a diagonal and y is an entry which is a nondiagonal.
    vector< vector<float> > m1;
    initialize(m1, size); //Initialize m1[size][size] matrix with deterministic values
    
    vector< vector<float> > m2;
    initialize(m2, size);
    
    time_t start_time1 = time(NULL); //Start measuring according to real-time
    while(time(NULL) < start_time1 + 10) //Run for 10 seconds
    {
        N_FLOAT += m_multiply(m1, m2, size);
    }
    cout << "Total matrix multiplications = " << N_FLOAT << endl;

    
    //--Select Sort Benchmarking--
    int a[k_max];
    int M = 100;
    int n = 0;
    
    //1,2,...,M
    for(int k=0; k<k_max; k++)
    {
        n += 1 - (n/M)*M; //1, 2, ..., M sequence repeats k_max/M times in array
        a[k]=n;
    }
    
    unsigned long N_INT = 0;
    time_t start_time2 = time(NULL); //Start measuring according to real-time
    while(time(NULL) < start_time2 + 10) //Run for 10 seconds
    {
        N_INT += SSORT(a, k_max);
    }
    cout << "n_int (10 SEC TOTAL) = " << N_INT << endl;

    return 0;
}



