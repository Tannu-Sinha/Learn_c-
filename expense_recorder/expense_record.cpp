#include<iostream>
#include<string>
#include<vector>
#include<map>


struct expense {
    std::string spending;
    double cost;
    std::string category;
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

std::string pickcategory() {
    std::cout<<"1. food\n"
             <<"2. travel\n"
             <<"3. clothes\n"
             <<"4. stationay\n"
             <<"5. others\n";
    int c = readInt("pick the category your expense falls under");
    while (c<1 || c>5) {
        std::cout<<"invalid category no. try again!\n";
        c = readInt("pick your category");
    }
    switch (c) {
        case 1: return "food";
        case 2: return "travel";
        case 3: return "clothes";
        case 4: return "stationary";
        default: return "others";
    }
}
void editSpending() {
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet\n";
        return;
    }
    int a = readInt("enter expense no. to be edited");
    if (a<1 || a > (int)Expense_record.size()) {
        std::cout<<"not a valid record no., try again\n";
        a = readInt("enter expense record no.");
    }

    expense& e = Expense_record[a-1];
    std::cout<<"current ["<<e.category<<"]"<< e.spending <<"  $ - "<< e.cost<<"\n";
    std::cout<<"New reason ["<< e.spending <<"] :";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) e.spending = input;
    std::cout<<"New cost ["<<e.cost<<"] :";
    std::getline(std::cin, input);
    if (!input.empty()) e.cost = std::stod(input);
    std::cout<<"Change category? (y/n): ";
    std::getline(std::cin, input);
    if (input == "y" || input == "Y") e.category = pickcategory();
    std::cout<<"expense updated \n";

}
void categorySummary() {
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded \n";
        return;
    } 
    std::map<std::string, double> totals;

    for (const expense& e : Expense_record) {
        totals[e.category] += e.cost;
    }
    double grand = 0;
    std::cout<<"\n========CategorySummary=========\n";
    for (const auto& pair : totals) {
        std::cout<<pair.first<<":  $"<<pair.second<<"\n";
        grand += pair.second;
    }
    std::cout<<"=========================\n";
    std::cout<<"grand total = $"<<grand<<"\n";

}

void addSpending() {
    expense e;
    std::cout<<"enter the reason for expense \n";
    std::getline(std::cin, e.spending);
    e.cost = readpositive("enter the cost price ");
    e.category = pickcategory();
    Expense_record.push_back(e);
    std::cout<<"expense succesfully recorded!\n";
}

void showSpending() {
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet\n";
    } else {
       for (int i = 0; i < (int)Expense_record.size(); i++) {
           std::cout<<"["<<Expense_record[i].category<<"]"<<i+1 <<"|" <<Expense_record[i].spending <<" - "<<Expense_record[i].cost<<"\n";
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
      std::cout<<"\n1. add expenses \n2. show expenses \n3. delete expense record \n4. edit record \n5. show categories \n6. exit \n";
      choice = readInt("enter choice no.");
      if (choice == 1) {
             addSpending();
        }  else if (choice == 2) {
              showSpending();
        }  else if (choice == 3) {
              deleteSpending();
        }  else if (choice == 4)  {
              editSpending();
        }   else if (choice == 5) {
             categorySummary();      
        }  else if (choice == 6) {
              break;
        }  else {
              std::cout<<"invalid choice no. , please try again!\n";
        }
    } while(choice!= 6);
  return 0;
}
