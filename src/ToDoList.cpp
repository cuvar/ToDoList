//============================================================================
// Name        : ToDoList.cpp
// Author      : cuvar
// Version     : 2.0
// Description : Todo List application
//============================================================================



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../../helper.h"



using namespace std;



//Function prototypes
//
void showTask();
void createTask();
void deleteTask();
void editTask();
void shiftTask();
void interchangeTask();
void printHelp();

void getTasksFromFile();
void putTasksInFile();


//Global variables
//
vector<string> tasks;
int amount = 0;
string file = "Tasks.td";



//Main
//
int main()
{
    system("TITLE To Do");
    string input;

    getTasksFromFile();
    showTask();
    cout << "\nMode: ";

    cin >> input;

    //while not wanna quit
    while(input != "q"){
        //creating tasks
        if(input == "c"){
            createTask();
        }
        //deleting tasks
        else if (input == "d"){
            deleteTask();
        }
        //editing a task
        else if(input == "e"){
            editTask();
        }
        // shifting a task to another position
        else if(input == "s"){
            shiftTask();
        }
        // shifting a task to another position
        else if(input == "i"){
            interchangeTask();
        }
        // putting tasks into file
        else if(input == "p"){
            putTasksInFile();
        }
        // printing out help
        else if(input == "h"){
            printHelp();
        }

        showTask();
        cout << "\nmode: ";
        cin >> input;
    }

    putTasksInFile();

    return 0;

}



//Shows all tasks
//
void showTask(){

    system("CLS");
    cout << "-----------------------------TODO LIST-----------------------------" << endl;

    if(amount == 0){                                            //no tasks
        cout << " Nothing to do!" << endl;
    }
    else if (amount >= 1){
        int i = 1;                                              //more than 1 task

        for (string s : tasks){
            cout << " " << i << ": "<< s << endl;
            i++;
        }
    }

}



//Creates a task
//
void createTask(){

    string newTask;

    //Getting all information
    showTask();
    cout << endl << "\t\tCreating" << endl;

    cin.ignore();
    getline(cin, newTask);

    //Putting new task in vector
    tasks.push_back(newTask);
    amount++;

}



//Deletes a task
//
void deleteTask(){

	if(amount != 0){
		int num;

		//Getting all information
		showTask();
		cout << endl << "\t\tDeleting" << endl;

		cin >> num;
		cout << endl;

		//Is Task existing?
		if(num <= amount && num > 0){
		    //Deleting the task
		    tasks.erase(tasks.begin() + num -1);
		    amount--;
		}
		else if (num == -1){
		   	tasks.erase(tasks.begin(), tasks.end());
			amount = 0;
		}
	}

}



//Edits a tasks
//
void editTask(){

    int num;
    string newTask;

    //Getting all information
    showTask();
    cout << endl << "\t\tEditing" << endl;

    cin >> num;
    cout << endl;
    cin.ignore();
    getline(cin, newTask);

    //Is Task existing?
    if(num <= amount && num > 0){
        tasks[num - 1] = newTask;
    }
    else {}

}



//Shifts a task to another position
//
void shiftTask(){

    int num;
    int pos;

    //Getting all information
    showTask();
    cout << endl << "\t\tShifting" << endl;

    cin >> num;
    cin >> pos;
    cout << endl;

    //Is Task existing?
    if(num <= amount && num > 0){

        //if task no is > position
        if(num > pos){
            string s = tasks[num - 1];

            for(int i = num - 2; i >= pos - 1; i--){
                tasks[i + 1] = tasks[i];
            }
            tasks[pos - 1] = s;
        }

        //Wenn Task No. ist unter der Position
        if(num < pos){
            string s = tasks[num - 1];

            for(int i = num - 1; i <= pos - 2 ; i++){
                tasks[i] = tasks[i + 1];
            }
            tasks[pos - 1] = s;
        }

    }
    else {}

}



//Interchanges two tasks
//
void interchangeTask(){

    int num;
    int pos;

    showTask();
    cout << endl << "\t\tInterchanging" << endl;

    cin >> num;

    cin >> pos;
    cout << endl;

    //Is Task existing?
    if(num <= amount && num > 0){
        string s = tasks[pos - 1];
        tasks[pos - 1] = tasks[num - 1];
        tasks[num - 1] = s;
    }
    else {}

}



// Prints everything you've to know about the program
//
void printHelp(){

    system("CLS");
    cout << "-----------------------------TODO LIST-----------------------------" << endl;

    cout << "\t\tHelp" << endl;
    cout << "  h\t\t\t\t -\t" 					<< "Shows this Help - page." << endl;
    cout << "  c <new task>\t\t\t -\t" 			<< "Creates a task." << endl;
    cout << "  d <task no.>\t\t\t -\t" 			<< "Deletes a task." << endl;
    cout << "  e <task no.> <new task>\t -\t" 	<< "Edits a task." << endl;
    cout << "  s <task no.> <position>\t -\t" 	<< "Puts a task to a position." << endl;
    cout << "  i <task no.> <position>\t -\t" 	<< "Changes two tasks." << endl;
    cout << "  p\t\t\t\t -\t" 					<< "Puts tasks into file." << endl;


    char c;
    cout << "\nPress Enter! ";
    cin >> c;
}



//Gets tasks from File
//
void getTasksFromFile(){

    ifstream Input (file, ios::binary);
    string t = "";

    getline(Input, t);

    vector<string> fileTasks = split(t, '`');


    for (string i : fileTasks){
        if(i != ""){
            tasks.push_back(i);
        }
        else{}
    }

    amount = tasks.size();

}



//Puts tasks into File
//
void putTasksInFile(){

    ofstream Output (file, ios::binary | ios::trunc);

    for (string s : tasks){
        Output << s << "`";
    }
    Output.close();
}
