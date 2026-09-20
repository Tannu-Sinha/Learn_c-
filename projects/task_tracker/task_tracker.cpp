#include<iostream>
#include<string>
#include<vector>
struct Task {
    std::string description;
    bool done = false;
};
std::vector<Task> tasks;
void addtask() {
    Task t;
    std::cout<<"Enter task \n";
    std::cin.ignore();
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
    std::cout<<"enter task no. that is completed \n";
    std::cin>>x;
    if (x < 1 || x > (int)tasks.size()) {
        std::cout<<"invalid input";
    } else {
      tasks[x-1].done = true;
     std::cout<<"task marked done \n";
    }
}
void deletetask() {
  int y;
    std::cout<<"enter task no. to be deleted \n";
    std::cin>>y;
    if (y < 1 || y> (int)tasks.size()) {
      std::cout<<"invalid task number";
    } else {
      tasks.erase(tasks.begin() + (y - 1));
      std::cout<<"task deleted! \n";
    }
}
int main() {
    int choice;
    do{
      std::cout<<"choice1: add task \n";
      std::cout<<"choice2:list tasks \n";
      std::cout<<"choice3: mark task done \n";
      std::cout<<"choice4: delete task \n";
      std::cout<<"choice5:exit to-do list \n";
      std::cin>>choice;
      if (choice == 1) {
        addtask();
      } else if (choice == 2) {
        listtask();
      } else if (choice == 3) {
        markdone();
      } else if (choice == 4) {
        deletetask();
      } else if (choice == 5) {
        break;
      } else {
        std::cout<<"invalid input, please try again. \n";
      }
    } while (choice != 5);  
    return 0;
}