/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include <stdio.h>
#include "record_class.h"

using namespace std;

//defines how many blocks are available in the Main Memory 
#define buffer_size 22

Records buffers[buffer_size]; //use this class object of size 22 as your main memory

/***You can change return type and arguments as you want.***/



//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void Sort_Emp_Buffer(int runNumber, int n = buffer_size){
    // Sort the buffers in main memory based on 'emp_record.eid'
    sort(buffers, buffers + n, [](Records a, Records b)
         { return a.emp_record.eid < b.emp_record.eid; });
    return;
}

void Write_Emp_Buffer(fstream &runfile, int n = buffer_size){
    for(int i = 0; i < n; i++){
        runfile << fixed << buffers[i].emp_record.eid << ","
            << buffers[i].emp_record.ename << ","
            << buffers[i].emp_record.age << "," 
            << buffers[i].emp_record.salary << endl;
    }
}

int Create_Emp_Runs(fstream &empin){
    int runNum = 0;
    int ind = 0;
    while(!empin.eof()){
        buffers[ind] = Grab_Emp_Record(empin);
        ind++;

        if(ind == buffer_size || buffers[ind - 1].no_values == -1){
            if(buffers[ind - 1].no_values == -1){
                ind--;
            }
            // sort + write run
            Sort_Emp_Buffer(runNum, ind);

            fstream runFile;
            runFile.open("empRun" + std::to_string(runNum) + ".csv", ios::out | ios::trunc);
            Write_Emp_Buffer(runFile, ind);
            runFile.close();
            runNum++;
            // reset ind
            ind = 0;
        }
    }
    return runNum;
}

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void Sort_Dept_Buffer(int runNumber, int n = buffer_size){
    // Sort the buffers in main memory based on 'dept_record.managerid'
    sort(buffers, buffers + n, [](Records a, Records b)
         { return a.dept_record.managerid < b.dept_record.managerid; });
    return;
}

void Write_Dept_Buffer(fstream &runfile, int n = buffer_size){
    for(int i = 0; i < n; i++){
        runfile << fixed << buffers[i].dept_record.did << ","
            << buffers[i].dept_record.dname << ","
            << buffers[i].dept_record.budget << ","
            << buffers[i].dept_record.managerid << endl;
    }
}

int Create_Dept_Runs(fstream &deptin){
    int runNum = 0;
    int ind = 0;
    while(!deptin.eof()){
        buffers[ind] = Grab_Dept_Record(deptin);
        ind++;

        if(ind == buffer_size || buffers[ind - 1].no_values == -1){
            if(buffers[ind - 1].no_values == -1){
                ind--;
            }
            // sort + write run
            Sort_Dept_Buffer(runNum, ind);

            fstream runFile;
            runFile.open("deptRun" + std::to_string(runNum) + ".csv", ios::out | ios::trunc);
            Write_Dept_Buffer(runFile, ind);
            runFile.close();
            runNum++;
            // reset ind
            ind = 0;
        }
    }
    return runNum;
}

//Prints out the attributes from empRecord and deptRecord when a join condition is met 
//and puts it in file Join.csv
void PrintJoin() {
    
    return;
}

//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
void Merge_Join_Runs(){
   

    //and store the Joined new tuples using PrintJoin() 
    return;
}

int main() {

    //Open file streams to read and write
    //Opening out two relations Emp.csv and Dept.csv which we want to join
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
   
    //Creating the Join.csv file where we will store our joined results
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);

    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    int empRunNum = Create_Emp_Runs(empin);
    int deptRunNum = Create_Dept_Runs(deptin);


    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 


    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv

    return 0;
}
