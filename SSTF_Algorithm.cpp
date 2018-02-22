//  Homework2
//  Jonas Vinter-Jensen | ID 912941515
//  CSC 675[01]
//  FALL-17 / San Francisco State University

#include <algorithm>
#include <array>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double T_seek(double x);
int r(void);

int main(int argc, const char * argv[])
{
    double T = 0;
    float X = 0; float newCylinder = 0;
    int DISK_ACCESSES = 2000000; //10^6 will ensure results with reliability of 3 significant digits
    int Q = 20;
    vector<double> seek_distance; //Used to find average seek distance
    vector<float> dq; //Disk queue with Q number of pending read/write request between disk and CPU
    
    
    for(int i=0; i<Q; i++) //Initialize dq with 20 numbers from [0,256]
    {
        dq.push_back( (float) r() ); //Cast here, since no information is lost
    }
    X = (float) r(); //Set initial position of head to a random position
    
    int SSTF_Index = -1;
    double min = fabs(dq[0]-X); //Initialize min to some value before the loop
    for(int i=0; i<DISK_ACCESSES; i++)
    {
        for(int j=0; j<Q; j++) //Find the index of the closest possible cylinder to move the head to
        {
            if(fabs(dq[j]-X)<min)
            {
                min = fabs(dq[i]-X);
                SSTF_Index = j;
            }
        }
        newCylinder = dq[SSTF_Index]; //The new cylinder to move the head to is the one with SST
        seek_distance.push_back( fabs(newCylinder-X) );
        T += T_seek(fabs(newCylinder-X)); //Find mean seek distance
        X = newCylinder; //Move head to the closest possible cylinder
        dq[SSTF_Index] = r(); //Replace the cylinder just found with a new random cylinder number [0, 256]
    }
    
    double avg_seek_distance = 0;
    for(int i=0; i<seek_distance.size(); i++)
    {
        avg_seek_distance += seek_distance[i];
    }
    avg_seek_distance /= seek_distance.size();
    
    cout << "Mean seek time = " << T << endl;
    cout << "Mean access time = " << T/( (double)DISK_ACCESSES ) + 3000/7200 << " ms" << endl; //Multiply by 1000 to get result in ms
    cout << "Average seek distance = " << avg_seek_distance << " cylinders" << endl;
    
    return 0;
}

int r(void)
{
    //static double mu = double(rand()/RAND_MAX);
    static int c = 55; //c odd integer approx. equal to 0.211*M
    static int a = 5;
    static int M = 256; //Upper bound of [0, M] random numbers generated
    static int N; //N: Random number generated
    
    N = (a*N+c)%M;
    return N;
}

//Disk seek time formulae, with parameters specific to Quantum Atlas III
double T_seek(double x) //[ms]
{
    double x_max = 8057; //[cylinders]
    double C = 9.1; //[GB]
    double N = 7200; //[rpm]
    double x_asterisk = 1686;
    double t=1.5455; //[ms]
    double c = 0.3197; //[ms]
    double r=0.3868;
    
    return x==0?0:t+c*pow(x-1, r); //x: # of cylinders from X to newCylinder [cylinder]
}
