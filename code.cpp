#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>

using namespace std;

struct Task {
    string name;
    int priority;
    int deadline;
    bool isDone;
};

struct Compare {
    bool operator()(const Task& a, const Task& b) {
        if (a.deadline == b.deadline) {
            return a.priority < b.priority;
        }
        return a.deadline > b.deadline;
    }
};

void printMenu() {
    cout << "1. Add Task" << endl;
    cout << "2. Delete Task" << endl;
    cout << "3. Update Task" << endl;
    cout << "4. Mark Task as Done" << endl;
    cout << "5. Show Tasks" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    priority_queue<Task, vector<Task>, Compare> tasks;
    int choice;
    priority_queue<Task, vector<Task>, Compare> tempTasks; // Declare tempTasks outside the switch statement

    while (true) {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                Task newTask;
                cout << "Enter task name: ";
                getline(cin, newTask.name);
                cout << "Enter priority (1-3): ";
                cin >> newTask.priority;
                cout << "Enter deadline (days): ";
                cin >> newTask.deadline;
                newTask.isDone = false;
                tasks.push(newTask);
                cout << "Task added successfully." << endl;
                break;
            }
            case 2: {
                string taskName;
                cout << "Enter task name to delete: ";
                getline(cin, taskName);
                bool found = false;

                while (!tasks.empty()) {
                    Task currentTask = tasks.top();
                    tasks.pop();

                    if (currentTask.name != taskName) {
                        tempTasks.push(currentTask);
                    } else {
                        found = true;
                    }
                }

                if (found) {
                    cout << "Task deleted successfully." << endl;
                } else {
                    cout << "Task not found." << endl;
                }

                while (!tempTasks.empty()) {
                    tasks.push(tempTasks.top());
                    tempTasks.pop();
                }

                break;
            }
            case 3: {
                string taskName;
                cout << "Enter task name to update: ";
                getline(cin, taskName);
                bool found = false;

                while (!tasks.empty()) {
                    Task currentTask = tasks.top();
                    tasks.pop();

                    if (currentTask.name == taskName) {
                        found = true;
                        cout << "Enter new priority (1-3): ";
                        cin >> currentTask.priority;
                        cout << "Enter new deadline (days): ";
                        cin >> currentTask.deadline;
                    }

                    tempTasks.push(currentTask);
                }

                if (found) {
                    cout << "Task updated successfully." << endl;
                } else {
                    cout << "Task not found." << endl;
                }

                while (!tempTasks.empty()) {
                    tasks.push(tempTasks.top());
                    tempTasks.pop();
                }

                break;
            }
            case 4: {
                string taskName;
                cout << "Enter task name to mark as done: ";
                getline(cin, taskName);
                bool found = false;

                while (!tasks.empty()) {
                    Task currentTask = tasks.top();
                    tasks.pop();

                    if (currentTask.name == taskName) {
                        found = true;
                        currentTask.isDone = true;
                    }

                    tempTasks.push(currentTask);
                }

                if (found) {
                    cout << "Task marked as done successfully." << endl;
                } else {
                    cout << "Task not found." << endl;
                }

                while (!tempTasks.empty()) {
                    tasks.push(tempTasks.top());
                    tempTasks.pop();
                }

                break;
            }
            case 5: {
                if (tasks.empty()) {
                    cout << "No tasks to display." << endl;
                } else {
                    cout << "Task Name | Priority | Deadline | Done" << endl;
                    cout << "------------------------------------" << endl;

                   
                    priority_queue<Task, vector<Task>, Compare> displayQueue = tasks;

                    while (!displayQueue.empty()) {
                        Task currentTask = displayQueue.top();
                        displayQueue.pop();
                        cout << currentTask.name << " | " << currentTask.priority << " | " << currentTask.deadline << " | " << (currentTask.isDone ? "Yes" : "No") << endl;
                    }
                }
                break;
            }
            case 6: {
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                break;
            }
        }
    }

    return 0;
}
