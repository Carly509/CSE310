#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


class Task {
private:
    string name;
    bool completed;
public:
    Task(const string& n, bool c = false) : name(n), completed(c) {}
    string getName() const { return name; }
    bool isCompleted() const { return completed; }
    void setName(const string& n) { name = n; }
    void markCompleted() { completed = true; }
};

class ToDoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

    void load() {
        ifstream fin(filename);
        if (!fin.is_open()) return;
        string line;
        while (getline(fin, line)) {
            bool isDone = false;
            if (!line.empty() && line[0] == '*') {
                isDone = true;
                line = line.substr(1);
            }
            tasks.emplace_back(line, isDone);
        }
        fin.close();
    }

    // Save tasks to file
    void save() {
        ofstream fout(filename, ios::trunc);
        for (const auto& task : tasks)
            fout << (task.isCompleted() ? "*" : "") << task.getName() << endl;
        fout.close();
    }

public:
    ToDoList() { load(); }
    ~ToDoList() { save(); }

    void addTask() {
        cout << "Enter task name: ";
        cin.ignore();
        string name;
        getline(cin, name);
        tasks.emplace_back(name);
        cout << "Task added.\n";
    }

    void removeTask() {
        displayTasks();
        if (tasks.empty()) return;
        cout << "Enter task number to remove: ";
        int n; cin >> n;
        if (n > 0 && n <= tasks.size()) {
            tasks.erase(tasks.begin() + n - 1);
            cout << "Task removed.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void displayTasks() const {
        if (tasks.empty()) {
            cout << "No tasks to display.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i)
            cout << (i + 1) << ". [" << (tasks[i].isCompleted() ? "X" : " ")
                 << "] " << tasks[i].getName() << endl;
    }

    void markComplete() {
        displayTasks();
        if (tasks.empty()) return;
        cout << "Enter task number to mark complete: ";
        int n; cin >> n;
        if (n > 0 && n <= tasks.size()) {
            tasks[n - 1].markCompleted();
            cout << "Task marked complete.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void run() {
        int choice;
        do {
            cout << "\nTo-Do List Manager\n";
            cout << "1. Add Task\n2. Remove Task\n3. Display Tasks\n4. Mark Task Complete\n5. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: addTask(); break;
                case 2: removeTask(); break;
                case 3: displayTasks(); break;
                case 4: markComplete(); break;
                case 5: save(); cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ToDoList todo;
    todo.run();
    return 0;
}
