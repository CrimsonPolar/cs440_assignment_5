/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  
/* This record_class.h contains the class Records, which can be used to store tuples form Emp.csv (stored
in the EmpRecords) and Dept.csv (Stored in DeptRecords) files.
*/
#include <bits/stdc++.h>

using namespace std;

class Records{
    public:
    
    struct EmpRecord {
        int eid;
        string ename;
        int age;
        double salary;
    }emp_record;

    struct DeptRecord {
        int did;
        string dname;
        double budget;
        int managerid;
    }dept_record;

    /*** You can add more variables if you want below ***/

    int no_values = 0; //You can use this to check if you've don't have any more tuples
    int number_of_emp_records = 0; // Tracks number of emp_records you have on the buffer
    int number_of_dept_records = 0; //Track number of dept_records you have on the buffer
};

// Grab a single block from the Emp.csv file and put it inside the EmpRecord structure of the Records Class
Records Grab_Emp_Record(fstream &empin) {
    string line, word;
    Records emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.emp_record.eid = stoi(word);
        getline(s, word, ',');
        emp.emp_record.ename = word;
        getline(s, word, ',');
        emp.emp_record.age = stoi(word);
        getline(s, word, ',');
        emp.emp_record.salary = stod(word);

        //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
        emp.dept_record.did = 0;
        emp.dept_record.dname = "";
        emp.dept_record.budget = 0;
        emp.dept_record.managerid = 0;

        return emp;
    } else {
        emp.no_values = -1;
        return emp;
    }
}

// Grab a single block from the Dept.csv file and put it inside the DeptRecord structure of the Records Class
Records Grab_Dept_Record(fstream &deptin) {
    string line, word;
    //DeptRecord dept;
    Records dept;
    if (getline(deptin, line, '\n')) {
        stringstream s(line);
        getline(s, word,',');
        dept.dept_record.did = stoi(word);
        getline(s, word, ',');
        dept.dept_record.dname = word;
        getline(s, word, ',');
        dept.dept_record.budget = stod(word);
        getline(s, word, ',');
        dept.dept_record.managerid = stoi(word);

        //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
        dept.emp_record.eid = 0;
        dept.emp_record.ename = "";
        dept.emp_record.age = 0;
        dept.emp_record.salary = 0;

        return dept;
    } else {
        dept.no_values = -1;
        return dept;
    }
}

// Open a sorted Emp.csv file and a Dept.csv file and merge them into a single file
// This is a standard sort-merge join, not the optimized version we discussed in class
// This mainly here as a reference for the optimized version
// Algorithm based on pseudocode from https://youtu.be/jiWCPJtDE2c

// void Sort_Merge_Join(string sorted_emp_file, string sorted_dept_file, string output_file) {
//     fstream empin(sorted_emp_file, ios::in),
//         deptin(sorted_dept_file, ios::in),
//         outfile(output_file, ios::out | ios::trunc);

//     Records emp = Grab_Emp_Record(empin);
//     Records dept = Grab_Emp_Record(deptin);

//     // Start of current dept partition.
//     // -1 is an error value from tellg, so we can't use it
//     streampos partition_marker = -2;

//     while (emp.no_values != -1 && dept.no_values != -1) {
//         if (partition_marker == -1) {
//             // Uhh, something went wrong
//             throw runtime_error("Error: tellg returned -1");
//         }

//         if (partition_marker == -2) {
//             while (emp.emp_record.eid < dept.dept_record.managerid) {
//                 emp = Grab_Emp_Record(empin);
//             }

//             while (emp.emp_record.eid > dept.dept_record.managerid) {
//                 dept = Grab_Emp_Record(deptin);
//             }

//             partition_marker = deptin.tellg();
//         }

//         if (emp.emp_record.eid == dept.dept_record.managerid) {
//             // Join the two records and write to output file
//             Write_Joined_Record(outfile, emp, dept);
//         } else {
//             emp = Grab_Emp_Record(empin);
//             deptin.seekg(partition_marker);
//             partition_marker == -2;
//         }
//     }
// }