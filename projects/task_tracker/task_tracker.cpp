#include<iostream>
#include<string>
#include<vector>
#include<fstream>
struct Task {
    std::string description;
    bool done = false;
};
std::vector<Task> tasks;
int readint(const std::string& prompt) {
  int value;
  while (true) {
    std::cout<<prompt;
    std::cin>>value;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout<<"it's not a number \n please try again \n";
    } else {
      std::cin.ignore(10000, '\n');
      return value;
    }
  }
}
void saveTask() {
  std::ofstream file("tasks.txt");
  if (!file.is_open())  {
    std::cout<<"error! tasks not saved";
  } else {
    for (const Task& t : tasks) {
      file<< t.done<<"|"<< t.description<<"\n";
    }
  }
  file.close();
}
void loadTask() {
  std::ifstream file("tasks.txt");
  if (!file.is_open()) {
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
   size_t pos = line.find('|');
   if (pos == std::string::npos) continue;
   Task t;
   t.done = (line.substr(0, pos) == "1");
   t.description = line.substr(pos + 1);
   tasks.push_back(t);
  }
  file.close();
}
void addtask() {
    Task t;
    std::cout<<"enter task \n";
    std::getline(std::cin, t.description);
    tasks.push_back(t);
    std::cout<<"task saved \n";
}
void listtask() {
    if (tasks.empty()) {
        std::cout<<"no tasks yet \n";
    } else {
        for (int i = 0; i < (int)tasks.size(); i++) {
            std::cout<<i+1 << tasks[i].description <<(tasks[i].done ? "X" : " ") <<"\n";
        }
      }
}
void markdone() {
  int x;
    x = readint("enter task no. to marked done");
    if (x < 1 || x > (int)tasks.size()) {
        std::cout<<"invalid input";
    } else {
      tasks[x-1].done = true;
     std::cout<<"task marked done \n";
    }
}
void deletetask() {
  int y;
    y = readint("enter task no. to be deleted");
    if (y < 1 || y> (int)tasks.size()) {
      std::cout<<"invalid task number";
    } else {
      tasks.erase(tasks.begin() + (y - 1));
      std::cout<<"task deleted! \n";
    }
}
int main() {
    loadTask();
    int choice;
    do{
      std::cout<<"choice1: add task \n";
      std::cout<<"choice2:list tasks \n";
      std::cout<<"choice3: mark task done \n";
      std::cout<<"choice4: delete task \n";
      std::cout<<"choice5:exit to-do list \n";
      choice = readint("enter choice number \n");
      if (choice == 1) {
        addtask();
      } else if (choice == 2) {
        listtask();
      } else if (choice == 3) {
        markdone();
      } else if (choice == 4) {
        deletetask();
      } else if (choice == 5) {
        saveTask();
        break;
      } else {
        std::cout<<"invalid input, please try again. \n";
        std::cin.ignore();
        std::cin.clear();
      }
    } while (choice != 5);  
    return 0;
}