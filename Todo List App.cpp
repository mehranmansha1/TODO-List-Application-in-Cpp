#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
using namespace std;

// Structure used to store information for one task.
struct task
{
    string id;
    string title;
    string description;
    string duedate;
    string priority;
    string completed;
};

// Function declarations
void add();
void view_all();
void search();
void update();
void delete_task();
void view_completed();
void view_pending();
void mark();
void file(string);

int main()
{
    int choice;
    cout<<"====================================\n\tTODO LIST APPLICATION\n====================================\n";
    
    string name = "Tasks.csv";
    
    // Create the CSV file with a header if it doesn't exist.
    file(name);
    
    // Main program loop
    while (true)
    {
    cout<<"\n===== Main Menu =====\n";
    cout<<"\n1. Add Task\n2. View All Tasks\n3. Search Task\n4. Update Task\n5. Delete Task\n6. Mark Task as Completed\n7. View Completed Tasks\n8. View Pending Tasks\n9. Exit\n\nEnter Choice: ";
    cin>>choice;

    if(choice == 1) add();
    else if (choice == 2) view_all();
    else if (choice == 3) search();
    else if (choice == 4) update();
    else if (choice == 5) delete_task();
    else if (choice == 6) mark();
    else if (choice == 7) view_completed();
    else if (choice == 8) view_pending();
    else if (choice == 9) {cout<<"\nThank You For Using My App.\n"; break;}
    else  cout<<"\nInvalid Choice";

    }

}

// Creates the CSV header if the file is new.
void file(string name)
{
	string temp;
	
	ifstream wfile(name);
	
	getline(wfile, temp, ',');
	
	if(temp == "ID")
	{
		wfile.close();
	}
	else
	{
		ofstream wfile(name, ios::app);
		wfile<<"ID,Title,Description,Due Date,Priority,Completed"<<endl;
		wfile.close();
	}
	
	wfile.close();
	
}

// Adds a new task after checking for duplicate IDs.
void add()
{
	task t1,t2;
	bool duplicate = false;
	
	ifstream checkfile("Tasks.csv");
	
    cout<<"\nEnter Task ID: ";
    cin>>t1.id;
    
    while(getline(checkfile, t2.id, ','))
    {
    	if (t2.id == "")
    	{
    		break;
		}
		
		getline(checkfile, t2.title, ',');
		getline(checkfile, t2.description, ',');
		getline(checkfile, t2.duedate, ',');
		getline(checkfile, t2.priority, ',');
		getline(checkfile, t2.completed);
		
		if (t2.id == t1.id)
		{
			duplicate = true;
			break;
		}
	}
	
	checkfile.close();
	
	if(duplicate)
	{
		cout<<"\nTask ID Already Exist.\n";
		return;
	}
	
	cin.ignore();
	
	cout<<"Enter Task Title: ";
    getline(cin, t1.title);
    
    cout<<"Enter Task Description: ";
    getline(cin, t1.description);
    
    cout<<"Enter Task Due Date(dd/mm/yyyy): ";
    getline(cin, t1.duedate);
    
    cout<<"Enter Task Priority (High or Medium or Low): ";
    getline(cin, t1.priority);
    
    cout<<"Enter Task Complition (yes or no): ";
    getline(cin, t1.completed);
	
	ofstream file("Tasks.csv", ios::app);
    
    file<< t1.id<<","
    		<< t1.title<<","
    		<< t1.description<<","
    		<< t1.duedate<<","
    		<< t1.priority<<","
    		<< t1.completed<<endl;
    
    file.close();
    
    cout<<"\nTask Added Successfully.\n";
}

// Displays all tasks stored in the CSV file.
void view_all() 
{
	task t1,t2;
    string line;
    
    cout<<"\n===== Task List =====\n";
    
    ifstream file("Tasks.csv");
    
    getline(file, line);
    
    while(getline(file, t2.id, ','))
    {
    	getline(file, t2.title, ',');
    	getline(file, t2.description, ',');
    	getline(file, t2.duedate, ',');
    	getline(file, t2.priority, ',');
    	getline(file, t2.completed);
    
    	cout<<"\nTask ID: "<<t2.id;
    	cout<<"\nTask Title: "<<t2.title;
    	cout<<"\nTask Description: "<<t2.description;
    	cout<<"\nTask Due Date: "<<t2.duedate;
    	cout<<"\nTask Priority: "<<t2.priority;
    	cout<<"\nTask Complition: "<<t2.completed<<endl;
    	
    	if(t2.completed == "no" || t2.completed == "No")
    	{
    		cout<<"\nNOTE : Task Not Completed!\t\t\t<<=====\n";
		}
		
		cout<<"\n---------------------\n";
	}
	
	file.close();
}

// Searches for a task using its ID.
void search() 
{
    task t1,t2;
    string line;
    
    ifstream file("Tasks.csv");
    
    cout<<"\nEnter Task ID To Search: ";
    cin>>t1.id;
    
    getline(file, line);
    
    while(getline(file, t2.id, ','))
    {
    	getline(file, t2.title, ',');
		getline(file, t2.description, ',');
		getline(file, t2.duedate, ',');
		getline(file, t2.priority, ',');
		getline(file, t2.completed);
    	
    	if(t2.id == t1.id)
    	{
			cout<<"\nTask ID: "<<t2.id;
  			cout<<"\nTask Title: "<<t2.title;
		    cout<<"\nTask Description: "<<t2.description;
		    cout<<"\nTask Due Date: "<<t2.duedate;
		    cout<<"\nTask Priority: "<<t2.priority;
		    cout<<"\nTask Complition: "<<t2.completed<<endl;
		    break;
		}
	}
	
	if(t2.id != t1.id)
	{
		cout<<"\nTask ID Not Found.\n";
	}
    	
    if(t2.completed == "no" || t2.completed == "No")
    {
    	cout<<"\nNOTE : Task Not Completed!\t\t\t<<=====\n";
	}
		
	cout<<"\n---------------------\n";
	
	file.close();
	
}

// Updates one or more fields of an existing task.
void update() 
{
	task t1,t2,t3;
    string id,line;
    int choice;
    bool found = false;
    
    string name = "temp.csv";
    
    ifstream getfile("Tasks.csv");
    file(name);
    ofstream temp(name, ios::app);
    
    cout<<"\nEnter Task ID To Update: ";
    cin>>id;
    
    getline(getfile, line);
    
    while(getline(getfile, t1.id, ','))
    {
    	getline(getfile, t1.title, ',');
    	getline(getfile, t1.description, ',');
    	getline(getfile, t1.duedate, ',');
    	getline(getfile, t1.priority, ',');
    	getline(getfile, t1.completed);
    	
    	t2.id = t1.id;
    	t2.title = t1.title;
    	t2.description = t1.description;
    	t2.duedate = t1.duedate;
    	t2.priority = t1.priority;
    	t2.completed = t1.completed;
    	
    	if(t1.id == id)
    	{
    		found = true;
    		
    		while (true)
    		{
    			cout<<"\n==== Update Menu ====\n";
    		
    		cout<<"\n1. ID \n2. Title \n3. Description \n4. Due Date \n5. Priority \n6. Complition\n7. Exit\n";
    		cout<<"\nEnter Choice: ";
			cin>>choice;
		
			if (choice == 1)
			{
				while (true)
				{
					string line;
					bool check = false;
					cout<<"\nUpdate ID: ";
					cin.ignore();
					getline(cin, t2.id);
					
					ifstream file("Tasks.csv");
					
					getline(file, line);
					
					while(getline(file, t3.id, ','))
   					{
   						if(t3.id == "")
   						{
   							break;
						}
   						
    					getline(file, t3.title, ',');
    					getline(file, t3.description, ',');
    					getline(file, t3.duedate, ',');
    					getline(file, t3.priority, ',');
    					getline(file, t3.completed);
    					
    					if(t2.id == t3.id)
    					{
    						cout<<"\nTask ID Already Exist.\n";
    						check = true;
    						break;
						}
    					
					}
					
					if(!check)
    					{
    						cout<<"\nTask ID Updated Succesfully.\n";
    						break;
						}
				}
			}
			else if (choice == 2)
			{
				cout<<"\nUpdate Title: ";
				getline(cin, t2.title);
				cout<<"\nTask Title Updated Succesfully.\n";
			}
			else if (choice == 3)
			{
				cout<<"\nUpdate Descriprion: ";
				getline(cin, t2.description);
				cout<<"\nTask Description Updated Succesfully.\n";
			}
			else if (choice == 4)
			{
				cout<<"\nUpdate Due Date: ";
				getline(cin, t2.duedate);
				cout<<"\nTask Due Date Updated Succesfully.\n";
			}
			else if (choice == 5)
			{
				cout<<"\nUpdate Priority: ";
				getline(cin, t2.priority);
				cout<<"\nTask Priority Updated Succesfully.\n";
			}
			else if (choice == 6)
			{
				cout<<"\nUpdate Complition (yes or no): ";
				getline(cin, t2.completed);
				cout<<"\nTask Complition Updated Succesfully.\n";
			}
			else if (choice == 7)
			{
				cout<<"\nExiting...\n";
				break;
			}
			else
			{
				cout<<"\nInvalid Choice.\n";
			}
			}
		}
		
		temp<<t2.id<<","
			<<t2.title<<","
			<<t2.description<<","
			<<t2.duedate<<","
			<<t2.priority<<","
			<<t2.completed<<endl;
	}
	
	getfile.close();
	temp.close();
	
	remove("Tasks.csv");
	rename("temp.csv", "Tasks.csv");
	
	if(!found)
	{
		cout<<"\nTask ID Not Found.\n";
	}	
}

// Deletes a task by copying all other records to a temporary file.
void delete_task()
{
    task t1;
    string id, line;
    bool found = false;

    ifstream file("Tasks.csv");
    ofstream temp("temp.csv");

    getline(file, line);
    temp << line << endl;

    cout << "\nEnter Task ID To Delete: ";
    cin >> id;

    while(getline(file, t1.id, ','))
    {
        getline(file, t1.title, ',');
        getline(file, t1.description, ',');
        getline(file, t1.duedate, ',');
        getline(file, t1.priority, ',');
        getline(file, t1.completed);

        if(t1.id == id)
        {
            found = true;
            continue;
        }

        temp << t1.id << ","
             << t1.title << ","
             << t1.description << ","
             << t1.duedate << ","
             << t1.priority << ","
             << t1.completed << endl;
    }

    file.close();
    temp.close();

    remove("Tasks.csv");
    rename("temp.csv","Tasks.csv");

    if(found)
        cout << "\nTask Deleted Successfully.\n";
    else
        cout << "\nTask ID Not Found.\n";
}

// Displays only completed tasks.
void view_completed()
{
    task t1;
    string line;
    bool found = false;

    ifstream file("Tasks.csv");

    getline(file, line);

    cout << "\n===== Completed Tasks =====\n";

    while(getline(file, t1.id, ','))
    {
        getline(file, t1.title, ',');
        getline(file, t1.description, ',');
        getline(file, t1.duedate, ',');
        getline(file, t1.priority, ',');
        getline(file, t1.completed);

        if(t1.completed == "yes" || t1.completed == "Yes")
        {
            found = true;

            cout << "\nTask ID: " << t1.id;
            cout << "\nTask Title: " << t1.title;
            cout << "\nTask Description: " << t1.description;
            cout << "\nTask Due Date: " << t1.duedate;
            cout << "\nTask Priority: " << t1.priority;
            cout << "\nTask Completion: " << t1.completed;
            cout << "\n-------------------------\n";
        }
    }

    if(!found)
        cout << "\nNo Completed Tasks Found.\n";

    file.close();
}

// Displays only pending tasks.
void view_pending()
{
    task t1;
    string line;
    bool found = false;

    ifstream file("Tasks.csv");

    getline(file, line);

    cout << "\n===== Pending Tasks =====\n";

    while(getline(file, t1.id, ','))
    {
        getline(file, t1.title, ',');
        getline(file, t1.description, ',');
        getline(file, t1.duedate, ',');
        getline(file, t1.priority, ',');
        getline(file, t1.completed);

        if(t1.completed == "no" || t1.completed == "No")
        {
            found = true;

            cout << "\nTask ID: " << t1.id;
            cout << "\nTask Title: " << t1.title;
            cout << "\nTask Description: " << t1.description;
            cout << "\nTask Due Date: " << t1.duedate;
            cout << "\nTask Priority: " << t1.priority;
            cout << "\nTask Completion: " << t1.completed;
            cout << "\n-------------------------\n";
        }
    }

    if(!found)
        cout << "\nNo Pending Tasks Found.\n";

    file.close();
}

// Marks a task as completed.
void mark()
{
    task t1;
    string id, line;
    bool found = false;

    ifstream file("Tasks.csv");
    ofstream temp("temp.csv");

    if(!file)
    {
        cout << "\nUnable to open Tasks.csv\n";
        return;
    }

    // Copy header
    getline(file, line);
    temp << line << endl;

    cout << "\nEnter Task ID To Mark As Completed: ";
    cin >> id;

    while(getline(file, t1.id, ','))
    {
        getline(file, t1.title, ',');
        getline(file, t1.description, ',');
        getline(file, t1.duedate, ',');
        getline(file, t1.priority, ',');
        getline(file, t1.completed);

        if(t1.id == id)
        {
            found = true;

            if(t1.completed == "yes" || t1.completed == "Yes")
            {
                cout << "\nTask is already completed.\n";
            }
            else
            {
                t1.completed = "Yes";
                cout << "\nTask marked as completed successfully.\n";
            }
        }

        temp << t1.id << ","
             << t1.title << ","
             << t1.description << ","
             << t1.duedate << ","
             << t1.priority << ","
             << t1.completed << endl;
    }

    file.close();
    temp.close();

    if(found)
    {
        remove("Tasks.csv");
        rename("temp.csv", "Tasks.csv");
    }
    else
    {
        remove("temp.csv");
        cout << "\nTask ID Not Found.\n";
    }
}

