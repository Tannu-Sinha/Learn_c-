#include<iostream>
#include<string>
#include<vector>

struct expense {
    std::string spending;
    double cost;
};

std::vector<expense> Expense_record;
double readDouble(std::string const& prompt) {
    double value;
    while (true) {
        std::cout<<prompt;
        std::cin>>value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout<<"not a number, try again!\n";
        }  else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}
double readpositive(std::string const& prompt) {
    double value = readDouble(prompt);
    while (value < 0) {
        std::cout<<"enter positive value \n";
        value = readDouble(prompt);
    }
    return value;
}

int readInt(std::string const& prompt) {
    int value;
    while (true) {
        std::cout<<prompt;
        std::cin>>value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout<<"not a number, try again!";
        }  else {
            std::cin.ignore(10000,'\n');
            return value;
        }
    }
}

void addSpending() {
    expense e;
    std::cout<<"enter the reason for expense \n";
    std::getline(std::cin, e.spending);
    e.cost = readpositive("enter the cost price ");
    Expense_record.push_back(e);
    std::cout<<"expense succesfully recorded!\n";
}

void showSpending() {
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet\n";
    } else {
       for (int i = 0; i < (int)Expense_record.size(); i++) {
           std::cout<<i+1 <<"|" <<Expense_record[i].spending <<" - "<<Expense_record[i].cost<<"\n";
        }
    }    
}
void deleteSpending()  {
    int a;
    a = readInt("enter expense no. to be deleted ");
    if (a < 1 || a > (int)Expense_record.size()) {
        std::cout<<"enter a valid expense no. \n";
    } else if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet.\n";
    } else {
        Expense_record.erase(Expense_record.begin() + (a - 1));
        std::cout<<"record successfully deleted!\n";
    }
}
int main() {
    int choice;
 do{    
      std::cout<<"1. add expenses \n 2. show expenses \n 3. delete expense record\n 4. exit \n";
      choice = readInt("enter choice no.");
      if (choice == 1) {
           addSpending();
        }  else if (choice == 2) {
           showSpending();
        }  else if (choice == 3) {
           deleteSpending();
        }  else if (choice == 4) {
            break;
        }  else {
           std::cout<<"invalid choice no. , please try again!\n";
        }
    } while(choice!= 4);
  return 0;
}
