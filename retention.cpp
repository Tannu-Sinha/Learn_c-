#include <iostream>
#include <vector>
std::vector<int> nums;
int main() {
    int choice;
  do {
     std::cout<<"choice 1 :enter the desired numbers \n";
     std::cout<<"choice 2: exit array \n";
     std::cin>>choice;
     if (choice == 1) {
         int x;
         std::cin>>x;
         nums.push_back(x);
        }   else {
          break;
        }
    } while (choice == 1);


 for (const auto& i : nums) {
      std::cout<< i <<" ";
      std::cout<< i <<" ";
    }
    return 0;
}