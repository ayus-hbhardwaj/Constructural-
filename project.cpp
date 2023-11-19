#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <String>

using namespace std;

class Task {
public:
    string description;
    int priority;
    string deadline;

    Task(string desc, int prio, string ddl) : description(desc), priority(prio), deadline(ddl) {}
};

class Project {
public:
    string name;
    string location;
    double budget;
    unordered_map<string, vector<Task>> tasks; 

    Project(string n, string loc, double b) : name(n), location(loc), budget(b) {}

    void addTask(string worker, string description, int priority, string deadline) {
        Task newTask(description, priority, deadline);
        tasks[worker].push_back(newTask); 
    }
    unordered_map<string, int> rawMaterials;

 

    void addRawMaterial(string material, int quantity) {
        rawMaterials[material] += quantity; 
    }

    void displayRawMaterials() const {
        cout << "Raw Materials:\n";
        for (const auto& pair : rawMaterials) {
            cout << pair.first << ": " << pair.second << " units\n";
        }
    }

    void completeTask(string worker, int taskIndex) {
        if (tasks.find(worker) != tasks.end() && taskIndex >= 0 && taskIndex < tasks[worker].size()) {
            cout << "Worker " << worker << " completed task: " << tasks[worker][taskIndex].description << endl;
            tasks[worker].erase(tasks[worker].begin() + taskIndex); 
        }
        else {
            cout << "Invalid task index or no tasks left for worker " << worker << " in this project." << endl;
        }
    }

    double calculateBudgetUsage() const {
        double totalSpent = 0;
        for (const auto& pair : tasks) {
            for (const auto& task : pair.second) {
                totalSpent += task.priority;
            }
        }
        return totalSpent;
    }
};

vector<Project> projects;

void addProject() {
    string name, location;
    double budget;

    cout << "Enter project name: ";
    cin >> name;
    cout << "Enter project location: ";
    cin >> location;
    cout << "Enter project budget: ";
    cin >> budget;

    Project newProject(name, location, budget);
    projects.push_back(newProject);

    cout << "Project added successfully!\n";
}

void displayProjects() {
    cout << "Projects:\n";
    for (const auto& project : projects) {
        cout << "Name: " << project.name << "\n";
        cout << "Location: " << project.location << "\n";
        cout << "Budget: $" << project.budget << "\n";
        cout << "Budget Usage: $" << project.calculateBudgetUsage() << "\n";
        cout << "Tasks:\n";
        for (const auto& pair : project.tasks) {
            cout << "Worker " << pair.first << " Tasks:\n";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                cout << i << ". " << pair.second[i].description << " (Priority: " << pair.second[i].priority << ", Deadline: " << pair.second[i].deadline << ")\n";
            }
        }
        cout << "------------------------\n";
    }
}

int main() {
    int choice;
    do {
        cout << "Construction Project Management System\n";
        cout << "1. Add Project\n";
        cout << "2. Add Task\n";
        cout << "3. Complete Task\n";
        cout << "4. Display Projects\n";
        cout << "5. add raw matrerial\n";
        cout << "6. Display rawmaterial\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProject();
            break;
        case 2:
            if (!projects.empty()) {
                string worker, description, deadline;
                int priority;
                cout << "Enter worker name: ";
                cin >> worker;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter task priority (cost): ";
                cin >> priority;
                cout << "Enter task deadline: ";
                cin >> deadline;
                projects.back().addTask(worker, description, priority, deadline);
                cout << "Task added successfully!\n";
            }
            else {
                cout << "No projects available. Please add a project first.\n";
            }
            break;
        case 3:
            if (!projects.empty()) {
                string worker;
                int taskIndex;
                cout << "Enter worker name: ";
                cin >> worker;
                cout << "Enter task index to complete: ";
                cin >> taskIndex;
                projects.back().completeTask(worker, taskIndex);
            }
            else {
                cout << "No projects available. Please add a project first.\n";
            }
            break;
        case 4:
            displayProjects();
            break;
        case 5:
            if (!projects.empty()) {
                string material;
                int quantity;
                cout << "Enter raw material name: ";
                cin >> material;
                cout << "Enter quantity needed: ";
                cin >> quantity;
                projects.back().addRawMaterial(material, quantity);
                cout << "Raw material added successfully!\n";
            }
            else {
                cout << "No projects available. Please add a project first.\n";
            }
            break;
        case 6:
            if (!projects.empty()) {
                projects.back().displayRawMaterials();
            }
            else {
                cout << "No projects available. Please add a project first.\n";
            }
            break;
        case 7:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
