#include <iostream>
#include <string>

int main() {
  std::cout << "Hello from Jenkins CI/CD Pipeline!\n";
  std::cout << "C++ program built and executed successfully!\n";

  std::string name;
  std::cout << "Enter your name: ";
  std::getline(std::cin, name);

  std::cout << "Hello, " << name << "!\n";
  return 0;
}
