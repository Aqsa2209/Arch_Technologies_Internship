#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_TASKS = 100;

struct Task {
    char description[100];
    char category[50];
    bool done;
};

Task taskList[MAX_TASKS];
int taskCount = 0;

// Load tasks from file if it exists
void loadTasks() {
    ifstream file("todo.txt");
    if (!file) return;

    while (!file.eof() && taskCount < MAX_TASKS) {
        file.getline(taskList[taskCount].description, 100, '|');
        file.getline(taskList[taskCount].category, 50, '|');
        char status[2];
        file.getline(status, 2);
        taskList[taskCount].done = (status[0] == '1');
        taskCount++;
    }

    file.close();
}

// Save current tasks to file
void saveTasks() {
    ofstream file("todo.txt");
    for (int i = 0; i < taskCount; i++) {
        file << taskList[i].description << "|"
             << taskList[i].category << "|"
             << (taskList[i].done ? "1" : "0") << endl;
    }
    file.close();
}

// Add new task to the list
void addTask() {
    if (taskCount >= MAX_TASKS) {
        cout << "Task limit reached. Cannot add more.\n";
        return;
    }

    cin.ignore(); // clear input buffer
    cout << "Enter task description: ";
    cin.getline(taskList[taskCount].description, 100);

    cout << "Enter task category (e.g. Work, Personal): ";
    cin.getline(taskList[taskCount].category, 50);

    taskList[taskCount].done = false;
    taskCount++;

    cout << "Task added successfully.\n";
}

// Show tasks (pending or completed), optional category filter
void showTasks(bool completed, const char* filterCategory = "") {
    cout << "\n--- Task List ---\n";
    int shown = 0;
    for (int i = 0; i < taskCount; i++) {
        if (taskList[i].done != completed) continue;

        if (strlen(filterCategory) > 0 && strcmp(taskList[i].category, filterCategory) != 0)
            continue;

        cout << (i + 1) << ". [" << (taskList[i].done ? "X" : " ") << "] "
             << taskList[i].description << " (" << taskList[i].category << ")\n";
        shown++;
    }

    if (shown == 0) {
        cout << "No tasks found.\n";
    }
    cout << "------------------\n";
}

// Mark a task as completed
void completeTask() {
    showTasks(false);
    cout << "Enter task number to mark as completed: ";
    int num;
    cin >> num;

    if (num >= 1 && num <= taskCount && !taskList[num - 1].done) {
        taskList[num - 1].done = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Remove task from the list
void removeTask() {
    cout << "\nAll Tasks:\n";
    for (int i = 0; i < taskCount; i++) {
        cout << (i + 1) << ". [" << (taskList[i].done ? "X" : " ") << "] "
             << taskList[i].description << " (" << taskList[i].category << ")\n";
    }

    cout << "Enter task number to remove: ";
    int num;
    cin >> num;

    if (num >= 1 && num <= taskCount) {
        for (int i = num - 1; i < taskCount - 1; i++) {
            taskList[i] = taskList[i + 1];
        }
        taskCount--;
        cout << "Task removed.\n";
    } else {
        cout << "Invalid number.\n";
    }
}

// Show only tasks from a specific category
void filterByCategory() {
    char cat[50];
    cin.ignore();
    cout << "Enter category to filter: ";
    cin.getline(cat, 50);

    showTasks(false, cat);
}

int main() {
    loadTasks();

    int choice;

    do {
        cout << "\n===== To-Do List Menu =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Pending Tasks\n";
        cout << "3. View Completed Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Remove a Task\n";
        cout << "6. Filter Tasks by Category\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: showTasks(false); break;
            case 3: showTasks(true); break;
            case 4: completeTask(); break;
            case 5: removeTask(); break;
            case 6: filterByCategory(); break;
            case 7: saveTasks(); cout << "Goodbye! Tasks saved.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

