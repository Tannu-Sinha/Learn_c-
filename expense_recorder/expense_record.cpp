#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<limits>


struct expense {
    std::string spending;
    double cost;
    std::string category;
};

double readDouble(std::string const& prompt) {
    double value;
    std::cout<<prompt;
    std::cin>>value;

    while (true) {
        if (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          std::cout<<"not a valid no., please try again\n";
          std::cin>>value;
        } else {
          return value;
        }
    }
    
}

double readPositive(std::string const& prompt) {
    double value = readDouble(prompt);
    while (value<0)  {
        std::cout<<"kindly enter a positive value\n";
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
           std::cin.ignore(10000,'\n');
           std::cout<<"not a valid integer, try again!";
           std::cin>>value;
        } else if (value < 0) {
           std::cin.clear();
           std::cin.ignore(10000,'\n');
           std::cout<<"enter a positive no.";
           std::cin>>value;
        } else {
            return value;
        }
    }
}
std::string pickCategory() {
    std::cout<<"1. travel\n"
             <<"2. food\n"
             <<"3. stationary\n"
             <<"4. clothing\n"
             <<"5. others\n";
 int c;
 c= readInt("enter the category no.");
    switch (c) {
        case 1: return "travel";
        case 2: return "food";
        case 3: return "stationary";
        case 4: return "clothing";
        default: return "others";
    }
             

}
std::vector<expense> Expense_record;

std::string file_name = "record.txt";
void saveFile() {
    std::ofstream out(file_name);
    if (!out) {
        std::cout<<"could not open file for saving\n";
        return;
    }
    for (const auto& e: Expense_record) {
        out<< e.spending<<"\t"<<e.cost<<"\t"<<e.category<<"\n";
    }
    std::cout<<"total saved records - "<<Expense_record.size()<<"\t";
}

void loadFile() {
    std::ifstream in(file_name);
    if (!in) return;
    Expense_record.clear();
    std::string line;
    while (std::getline(in,line)) {
        std::stringstream ss(line);
        expense e;
        std::string costExpense;
        if (std::getline(ss, e.spending,'\t')&& 
             std::getline(ss, costExpense,'\t')&& 
             std::getline(ss, e.category,'\t')) {
           e.cost = std::stod(costExpense);
           Expense_record.push_back(e);
        } 
    }
    std::cout<<"loaded "<<Expense_record.size() <<"records from "<<file_name<<"\n";
}

expense e;
void addSpending() {
    std::cout<<"enter reason for spending";
    std::getline(std::cin>>std::ws, e.spending);
    e.cost = readPositive("enter the cost");
    e.category = pickCategory();
    Expense_record.push_back(e);
    std::cout<<"expense recorded successfully!\n";
}

void editSpending() {
    int a;
    a = readInt("enter expense no. to be edited");
    while (a> (int)Expense_record.size()) {
        std::cout<<"enter a valid record no., total no. of current expense records -"<<Expense_record.size();
        a = readInt("enter valid expense no. to be edited");
    }
    std::cout<<"current record "<<Expense_record[a-1].category << Expense_record[a-1].spending <<" - $ "<< Expense_record[a-1].cost;
    int c;
    std::cout<<"what to edit\n"
             <<"1. category\n"
             <<"2. cost \n"
             <<"3.  reason of expense\n"
             <<"4.  all\n";
    c = readInt("enter your choice no.");
    switch (c) {
        case 1: Expense_record[a-1].category = pickCategory(); break;
        case 2: Expense_record[a-1].cost = readPositive("enter the new cost"); break;
        case 3: std::getline(std::cin>> std::ws,Expense_record[a-1].spending); break;
        default: Expense_record[a-1].category = pickCategory();
                 Expense_record[a-1].cost = readPositive("enter the new cost");
                 std::getline(std::cin>> std::ws, Expense_record[a-1].spending); 
    }
    std::cout<<"new record "<<Expense_record[a-1].category << Expense_record[a-1].spending <<" - $ "<<Expense_record[a-1].cost;

}

void categorySummary() {
std::map<std::string, double> totals;

for (const expense& e: Expense_record) {
    totals[e.category] += e.cost;
}
std::cout<<"---------category summary------\n";
double grandTotal = 0;
for (const auto& pair : totals) {
    std::cout<<pair.first<<" - $ "<<pair.second;
    grandTotal += pair.second;
}
std::cout<<"total cost spent till now"<<grandTotal;
}

void deleteRecord() {
    int a = readInt("enter record no. to be deleted");
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet";
        return;
    } 
    while (a > (int)Expense_record.size()) { 
         std::cout<<"enter valid expense record no.\n";
         a = readInt("enter again");
    }

      Expense_record.erase(Expense_record.begin() + (a-1));
      std::cout<<"record deleted successfully\n";
    
    
} 

void showSpending() {
    if (Expense_record.empty()) {
        std::cout<<"no expenses recorded yet \n";
    } else {
      for (const auto& e : Expense_record) {
           std::cout<<"["<<e.category<<"]  "<<e.spending<<" - $ "<<e.cost<<"\n";
        }
    }
}

int main() {
  loadFile();
  int i;
  do{
      std::cout<<"1. add expense\n"
               <<"2. show recorded expenses\n"
               <<"3. delete expense\n"
               <<"4. summarize categories\n"
               <<"5. edit expense records\n"
               <<"6. exit\n";
    
      i = readInt("enter your choice no.\n");
      if (i == 1) {
          addSpending();
        } else if (i == 2) {
           showSpending();
       } else if (i == 3) {
           deleteRecord();
        } else if (i == 4) {
           categorySummary();
        } else if (i == 5) {
           editSpending();
        } else if (i == 6) {
           saveFile();
           std::cout<<"exiting expense recorder\n";
        } else{
            std::cout<<"not a valid choice no., try again!\n";
        }
    } while (i != 6);    
   return 0;           
            
}