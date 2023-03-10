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
void sortEmpBuffer(int runNumber, int n = buffer_size){
    // Sort the buffers in main memory based on 'emp_record.eid'
    sort(buffers, buffers + n, [](Records a, Records b)
         { return a.emp_record.eid < b.emp_record.eid; });
    return;
}

// Writes buffer to an employee runfile
// Param n: number of entries in buffer
void writeEmpBuffer(fstream &runfile, int n = buffer_size){
    for(int i = 0; i < n; i++){
        runfile << fixed << buffers[i].emp_record.eid << ","
            << buffers[i].emp_record.ename << ","
            << buffers[i].emp_record.age << "," 
            << buffers[i].emp_record.salary << endl;
    }
}

// Creates employee runs from input
int createEmpRuns(fstream &empin){
    int runNum = 0;
    int ind = 0;
    while(!empin.eof()){
        buffers[ind] = Grab_Emp_Record(empin);
        ind++;

        if(ind == buffer_size || buffers[ind - 1].no_values == -1){
            // if the runs end prematurely, ensure the buffer with the no_values = 1 value is not written to memory
            if(buffers[ind - 1].no_values == -1){
                ind--;
            }
            // sort + write run
            sortEmpBuffer(runNum, ind);

            if(ind != 0){
                fstream runFile;
                runFile.open("empRun" + std::to_string(runNum) + ".csv", ios::out | ios::trunc);
                writeEmpBuffer(runFile, ind);
                runFile.close();
                runNum++;
            }
            
            // reset ind
            ind = 0;
        }
    }
    return runNum;
}

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void sortDeptBuffer(int runNumber, int n = buffer_size){
    // Sort the buffers in main memory based on 'dept_record.managerid'
    sort(buffers, buffers + n, [](Records a, Records b)
         { return a.dept_record.managerid < b.dept_record.managerid; });
    return;
}

// Writes buffer to a department runfile
// Param n: number of entries in buffer
void writeDeptBuffer(fstream &runfile, int n = buffer_size){
    for(int i = 0; i < n; i++){
        runfile << fixed << buffers[i].dept_record.did << ","
            << buffers[i].dept_record.dname << ","
            << buffers[i].dept_record.budget << ","
            << buffers[i].dept_record.managerid << endl;
    }
}

// Creates dept runs from input
int createDeptRuns(fstream &deptin){
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
            sortDeptBuffer(runNum, ind);

            if(ind != 0){
                fstream runFile;
                runFile.open("deptRun" + std::to_string(runNum) + ".csv", ios::out | ios::trunc);
                writeDeptBuffer(runFile, ind);
                runFile.close();
                runNum++;
            }
            
            // reset ind
            ind = 0;
        }
    }
    return runNum;
}

// Removes all temporary run files
int cleanupRuns(int empRunNum, int deptRunNum){
    int ret = 0;
    for(int i = 0; i < empRunNum; i++){
        string filename = "empRun" + to_string(i) + ".csv";
        if(remove(filename.c_str()) != 0){
            cout << "\tError deleting file: " << filename << endl;
            ret = 1;
        }
    }

    for(int i = 0; i < deptRunNum; i++){
        string filename = "deptRun" + to_string(i) + ".csv";
        if(remove(filename.c_str()) != 0){
            cout << "\tError deleting file: " << filename << endl;
            ret = 1;
        }
    }
    return ret;
}

// Prints out the attributes from empRecord and deptRecord when a join condition is met 
// and puts it in file Join.csv
// params are by reference to not overstep the 22 block memory requirement
void PrintJoin(fstream &outfile, Records &emp, Records &dept)
{
    outfile << fixed << emp.emp_record.eid << ","
            << emp.emp_record.ename << ","
            << emp.emp_record.age << ","
            << emp.emp_record.salary << ","
            << dept.dept_record.did << ","
            << dept.dept_record.dname << ","
            << dept.dept_record.budget << endl;
    return;
}

int findNextEmpRecord(int empIndStart, int empIndEnd){
    int nextInd = empIndStart;
    for(int i = empIndStart + 1; i < empIndEnd; i++){
        if(buffers[i].no_values != -1){
            if(buffers[i].emp_record.eid < buffers[nextInd].emp_record.eid){
                nextInd = i;
            }
        }
    }
    if(buffers[nextInd].no_values == -1){
        nextInd = -1;
    }
    return nextInd;
}

int findNextDeptRecord(int deptIndStart, int deptIndEnd){
    int nextInd = deptIndStart;
    for(int i = deptIndStart + 1; i < deptIndEnd; i++){
        if(buffers[i].no_values != -1){
            if(buffers[i].dept_record.managerid < buffers[nextInd].dept_record.managerid){
                nextInd = i;
            }
        }
    }
    if(buffers[nextInd].no_values == -1){
        nextInd = -1;
    }
    return nextInd;
}

//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp
void Merge_Join_Runs(fstream &fileOut, int empNumRuns, int deptNumRuns) {
    if(empNumRuns + deptNumRuns > buffer_size){
        throw new runtime_error("\tdept and emp relations are too large for the memory restriction of sort-merge join. Aborting.");
    }
    fstream emp_input_files[empNumRuns];
    fstream dept_input_files[deptNumRuns];

    // indecies for tracking blocks in buffers
    //   indecies are inclusive of start, exclusive of end
    int empIndStart = 0;
    int empIndEnd = empNumRuns;
    int deptIndStart = empNumRuns;
    int deptIndEnd = empNumRuns + deptNumRuns;

    // Open all of the runs files and read entries to buffer
    for (int i = 0; i < empNumRuns; i++) {
        string filename = "empRun" + to_string(i) + ".csv";
        emp_input_files[i].open(filename, ios::in);

        buffers[empIndStart + i] = Grab_Emp_Record(emp_input_files[i]);
    }
    for (int i = 0; i < deptNumRuns; i++) {
        string filename = "deptRun" + to_string(i) + ".csv";
        dept_input_files[i].open(filename, ios::in);

        buffers[deptIndStart + i] = Grab_Dept_Record(dept_input_files[i]);
    }

    // Find initial states
    int nextEmp = findNextEmpRecord(empIndStart, empIndEnd);
    int nextDept = findNextDeptRecord(deptIndStart, deptIndEnd);

    // Until either relation is out of blocks
    while(nextEmp != -1 && nextDept != -1){
        if(buffers[nextEmp].emp_record.eid < buffers[nextDept].dept_record.managerid){
            buffers[nextEmp] = Grab_Emp_Record(emp_input_files[nextEmp - empIndStart]);
            nextEmp = findNextEmpRecord(empIndStart, empIndEnd);
        } else if(buffers[nextEmp].emp_record.eid > buffers[nextDept].dept_record.managerid){
            buffers[nextDept] = Grab_Dept_Record(dept_input_files[nextDept - deptIndStart]);
            nextDept = findNextDeptRecord(deptIndStart, deptIndEnd);
        } else {
            // loop to match identical dept managers
            // not doing the same for emp because eid is a key, managerid is not (did is)
            while(buffers[nextEmp].emp_record.eid == buffers[nextDept].dept_record.managerid) {
                PrintJoin(fileOut, buffers[nextEmp], buffers[nextDept]);

                buffers[nextDept] = Grab_Dept_Record(dept_input_files[nextDept - deptIndStart]);
                nextDept = findNextDeptRecord(deptIndStart, deptIndEnd);
            }
            buffers[nextEmp] = Grab_Emp_Record(emp_input_files[nextEmp - empIndStart]);
            nextEmp = findNextEmpRecord(empIndStart, empIndEnd);
        }
    }
    //and store the Joined new tuples using PrintJoin() 

    // close filestreams and cleanup
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
    joinout.open("Join.csv", ios::out | ios::trunc);

    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    int empRunNum = createEmpRuns(empin);
    int deptRunNum = createDeptRuns(deptin);


    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 
    Merge_Join_Runs(joinout, empRunNum, deptRunNum);

    // Deletes runs 
    return cleanupRuns(empRunNum, deptRunNum);
}
