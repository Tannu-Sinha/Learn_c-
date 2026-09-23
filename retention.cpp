#include<iostream>
#include<string>
#include<fstream>
#include<vector>
struct Task{
  bool done = false;
  std::string description;
};
std::vector<Task> tasks;
void addTask() {
  Task t;
  std::cout<<"enter task to be added \n";
  std::cin.ignore();
  std::getline(std::cin, t.description);
  tasks.push_back(t);
  std::cout<<"task saved \n";
}
void listTask() {
  if (tasks.empty()) {
    std::cout<<"no tasks added \n";
  } else {
    for (int i = 0; i < (int)tasks.size(); i++) {
      std::cout<<i+1<< (tasks[i].done ? "X" : " ")<<tasks[i].description<<"\n";
    }
  }
}
void deleteTask() {
  std::cout<<"enter task number to be deleted \n";
  int i;
  std::cin>>i;
  if (i<1 || i > (int)tasks.size()) {
    std::cout<<"invalid task number \n";
  } else {
    tasks.erase(tasks.begin() + (i-1));
    std::cout<<"task deleted \n";
  }
}
void saveTask() {
  std::ofstream file("tasks.txt");
  if (!file.is_open()) {
    std::cout<<"no tasks saved \n";
  } else {
    for(const Task& t: tasks) {
      file<<t.done<<"|"<<t.description<<"\n";
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
    if (pos == std::string::npos)continue;
    Task t;
    t.done =(line.substr(0,pos) =="1");
    t.description = line.substr(pos+1);
    tasks.push_back(t);
  }
  file.close();
}
void markdone() {
  int a;
  std::cout<<"enter the task number that is done\n";
  std::cin>>a;
  if (a<1 || a>(int)tasks.size()) {
    std::cout<<"invalid task number\n";
  } else {
    tasks[a-1].done = true;
  }
}
int readint() {
  int value;
  while true {
    std::cout<<"prompt \n";
    std::cin>>value;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout<<"it's not a number, try again \n";
    } else{
      std::cin.ignore(10000, '\n');
      return value;
    }
  }
}
int main() {
  loadTask();
  int choice;
 do{
   std::cout<<"1.  add task \n";
   std::cout<<"2. list tasks \n";
   std::cout<<"3. mark task done\n";
   std::cout<<"4. delete task \n";
   std::cout<<"5. exit \n";
   std::cout<<"enter choice number\n";
   choice = readint("choice -");
   if (choice==1) {
      addTask();
    } else if (choice==2) {
      listTask();
    } else if (choice== 3) {
      markdone();
    } else if (choice==4) {
      deleteTask();
    }  else if (choice == 5) {
      saveTask();
      break;
    }  else {
      std::cout<<"invalid input! please try again \n";
    }
  } while (choice != 5);
  return 0;
}