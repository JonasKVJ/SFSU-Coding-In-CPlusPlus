//  HW4_GGISimulator
//  CSC 675 [01] - Computer Performance Evaluation | Fall-17
//  Jonas Vinter-Jensen | ID 912941515

#include <iostream>
#include <stdio.h>

//The amount of random numbers to generate, exceeding this will cause undefined behavior
#define RAND_NUM_AMOUNT 2000000

/*Program structure
- Initialize EVENT and TIME to 0
- Get EMAX and TMAX from user as input
 - EMAX: Maximum number of events, TMAX: Maximum simulation time
- Initialize statistical indicators
 - IA_AVG: Average interarrival time during simulation
 - IA_SD: Standard deviation of the interarrival time during the simulation
 - J_SD: Standard deviation of the jobs in the system during the simulation
 - QLEN_AVG: Average number of jobs in queue during simulation
 - R_AVG: Average R during simulation
 - R_SD: Standard devation of R during simulation
 - S_AVG: Average service time during simulation
 - S_SD: Standard Devation of S during simulation
 - SERVER_TBUSY: Total amount of time server has been busy
 - U: Server utilization
 - U_AVG: Average utilization during simulation
 - U_SD: Standard deviation of U during simulation
 - X: Throughput, JOBS/TIME
- Initialize the master set of expected times T = {t1, t2, ..., tN}
- While (EVENT<EMAX AND TIME<TMAX)
 - Select EVENT which occurs at next t_i
 - EVENT += 1, TIME = TNEXT
 - Perform EVENT
 - Remove t_i of EVENT from T
 - If EVENT generated new events, add t_i for those events to T
- Print results
 */

using namespace std;

double EVENTMAX = 0, TMAX = 0; //Input parameters
double QA[RAND_NUM_AMOUNT], QS[RAND_NUM_AMOUNT]; //QA: Random arrival time of the ith job waiting in queue | QS: Random service time of ith job waiting in queue
int QSIZE = 500, QLEN = 0;
int JOB_DEP = 0, JOB_ARR = 0; //Number of job departures to simulate, JOB_ARR: Keep track of which ith job arrived

//IA: Interarrival time, EVENT: current event, S: Service time, TIME: current time U: Utilization, R: Response time
double IA, EVENT, S, TIME, R;

double IA_AVG, IA_SD, J_SD, QLEN_AVG, R_AVG, R_SD, S_AVG, S_SD, SERVER_TBUSY, U, U_AVG, U_SD, X; //Statistical indicators
void initialize();
void initMaster(int selectedDistrParam, int MIN, int MAX);
void simulate(); //Occurrence of EVENT such as arrival or departure
double urn(int MIN, int MAX);

int main(int argc, const char * argv[])
{
    string answer = "";
    double IA_DISTR = 0, IA_MIN = 0, IA_MAX = 0, S_DISTR = 0, S_MIN = 0, S_MAX = 0; //MIN AND MAX: Interval of a potential uniform distribution
    srand( (unsigned) time(NULL) ); //Random seed for urn()
    
    while(1)
    {
        cout << "Please input EMAX TMAX: ";
        cin >> EVENTMAX >> TMAX;
        if(EVENTMAX>RAND_NUM_AMOUNT)
        {
            cout << "EVENTMAX can be at most 2,000,000, please try again" << "\n\n";
            continue;
        }
        cout << "Select distribution for interarrival times: " << endl;
        cout << "1) Uniform" << endl;
        cout << "2) Exponential" << endl;
        cout << "Pick one: ";
        cin >> IA_DISTR;
        if(IA_DISTR==1)
        {
            cout << "Specify MIN MAX: ";
            cin >> IA_MIN >> IA_MAX;
        }
        
        cout << "\nSelect distribution for service times: " << endl;
        cout << "1) Uniform" << endl;
        cout << "2) Exponential" << endl;
        cout << "Pick one: ";
        cin >> S_DISTR;
        if(S_DISTR==1)
        {
            cout << "Specify MIN MAX: ";
            cin >> S_MIN >> S_MAX;
        }
        
        cout << "EMAX = " << EVENTMAX << " TMAX = " << TMAX << " Interarrival distribution = " << IA_DISTR;
        cout << " Service time distribution = " << S_DISTR << endl;
        cout << "Is this correct? (y/n): ";
        cin >> answer;
        if(answer=="y" || answer=="Y"){break;}
        cout << "Getting new values" << endl;
    }
    
    initialize(); //Initialize statistical indicators
    
    if(IA_DISTR==1)
    {
        initMaster(1, IA_MIN, IA_MAX); //Initialize master set T for uniform interarrival times
    }
    if(S_DISTR==1)
    {
        initMaster(2, S_MIN, S_MAX); //Initialize master set T for uniform service times
    }
    
    while(EVENT<EVENTMAX && TIME<TMAX)
    {
        simulate(); //Trigger next event
    }
    
    QLEN_AVG = QLEN_AVG/( (double)EVENT );
    cout << "QLEN_AVG = " << QLEN_AVG << endl;
    cout << "Number of finished events: " << EVENT << endl;
    
    return 0;
}

void initMaster(int selectedDistrParam, int MIN, int MAX)
{
    if(selectedDistrParam==1) //initialize master set T for uniform distribution of interarrival times
    {
        for(int i=0; i<RAND_NUM_AMOUNT; i++)
        {
            IA = urn(MIN, MAX); //Get a new interarrival time between [MIN, MAX]
            if(i==0)
            {
                QA[i] = IA;
            }
            else
            {
                QA[i] = IA + QA[i-1]; //The new arrival time must be the previous arrival time plus the newly generated interarrival time
            }
        }
    }
    else if(selectedDistrParam==2) //initialize master set T for uniform distribution of S
    {
        for(int i=0; i<RAND_NUM_AMOUNT; i++)
        {
            S = urn(MIN, MAX); //Get a new service time between [MIN, MAX]
            QS[i] = S;
        }
    }

}

void initialize()
{
    IA_AVG = 0;
    IA_SD = 0;
    J_SD = 0;
    QLEN_AVG = 0;
    R_AVG = 0;
    R_SD = 0;
    S_AVG = 0;
    S_SD = 0;
    SERVER_TBUSY = 0;
    U = 0;
    U_AVG = 0;
    U_SD = 0;
    X = 0;
    
    for(int i=0; i<RAND_NUM_AMOUNT; i++)
    {
        QA[i] = 0;
        QS[i] = 0;
    }
}

void simulate()
{
    EVENT += 1;
    
    //Two possible events:
    //1) Arrival of new job onto the queue which contains a random number of jobs between [0, QSIZE] waiting in line
    //2) Departure of 0th job in queue after finishing its service
    
    //Case 1: Server is not serving anyone, so the next event must be a job arrival. Therefore, select this new arrival time
    if(QLEN==0)
    {
        TIME = QA[JOB_ARR]; //TNEXT = arrival time of new job
        JOB_ARR++;
        QLEN++; //New job is being served but is also double-counted as a single unit in the queue
    }
    else if(QLEN>0 && QLEN != QSIZE)
    {
        //Case 2: Server is serving ith job, but it will finish before a new job arrives.
        //Compare S of currently served job to next arrival time and pick the soonest event
        if( (TIME + QS[JOB_DEP]) < QA[JOB_ARR] )
        {
            TIME += QS[JOB_DEP]; //Add the service time for the job that finished to the global time count
            JOB_DEP++; //Current job finishes with its service
            QLEN--;
        }
        //Case 3: Server is serving ith job, but a new job arrives before the served job has finished
        else if( (TIME + QS[JOB_DEP]) > QA[JOB_ARR] )
        {
            TIME = QA[JOB_ARR];
            JOB_ARR++;
            QLEN++;
        }
    }
    
    //Case 4: Queue is full and a new job arrives, but the job will have to leave unfinished and cannot be considered an event. This
    //must mean that the next event has to be a job departure
    else if(QLEN==QSIZE)
    {
        TIME += QS[JOB_DEP];
        JOB_DEP++;
        QLEN--;
    }
    
    QLEN_AVG += QLEN;

    return;
}

double urn(int MIN, int MAX)
{
    double r = (double) rand()/RAND_MAX;  //[0,1]
    r = r + rand()%MAX + (MIN-1); //interval [MIN, MAX], achieved by adding double [0,1] decimal part to an int falling in the
                                  //interval [MIN-1, MAX-1]
    
    return r;
}


