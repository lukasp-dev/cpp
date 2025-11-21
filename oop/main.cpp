#include <iostream>
#include "AbstractEmployee.hpp"
using namespace std;

class Employee:AbstractEmployee {
protected:
    string name;
    string company;
    int age;
public:
    Employee(){}

    Employee(string name, string company, int age){
        this->name = name; 
        this->company = company;
        this->age = age;
    }

    // setters
    void setName(string name){
        this->name = name;
    }

    void setCompany(string company){
        this->company = company;
    }

    void setAge(int age){
        // you can also add some logics like
        // if(age > 18)
        this->age = age;
    }

    // getters 
    string getName(){
        return this->name;
    }
    
    string getCompany(){
        return this->company;
    }

    int getAge(){
        return this->age;
    }

    // member functions
    void introduce(){
        cout << "Hello I am " << this->name << " and I go to " << this->company << "\n";
    }

    void askForPromotion() override {
        if(this->age > 30){
            cout << this->name << " got promoted!" << "\n";
        }else{
            cout << "Sorry, no promotion for you, " << this->name << "\n";
        }
    }

    virtual void work(){
        cout << this->name << " is working\n";
    }
};

class Developer: public Employee {
public:
    string favProgrammingLanguage;
    Developer(string name, string company, int age, string favProgrammingLanguage)
    :Employee(name, company, age){
        this->favProgrammingLanguage = favProgrammingLanguage;
    }
    void fixBug(){
        cout << this->name << " fixed bug using " << this->favProgrammingLanguage << "\n";
    }

    void work(){
        cout << this->name << " is coding in " << this->favProgrammingLanguage << "\n";
    }
};

class Teacher: public Employee {
public:
    string subject;
    void prepareLesson() {
        cout << this->name << " is preparing " << subject << " lesson" << "\n"; 
    }
    Teacher(string name, string company, int age, string subject)
    :Employee(name, company, age){
        this->subject = subject;   
    }
};

int main(){
    int number;
    Employee employee1;
    employee1.setName("Jewook");
    employee1.setCompany("Microsoft");
    employee1.setAge(22);
    employee1.introduce();
    employee1.askForPromotion();

    Employee employee2 = Employee("Jehoon", "Google", 22);
    employee2.introduce();
    employee2.askForPromotion();

    Developer d = Developer("Lukas", "Microsoft", 22, "C++");
    d.fixBug();
    d.askForPromotion();

    Teacher t = Teacher("Jack", "Cool School", 35, "History");
    t.prepareLesson();
    t.askForPromotion();
    
    Employee* t2 = new Teacher("Josh", "Rich hill highschool", 37, "Math");
    t2->work(); // the most derived is Employee's implementation

    Employee* d2 = new Developer("James", "Atlassian", 40, "Python");
    d2->askForPromotion();
    d2->work(); // the most derived is Developer's implementation

    return 0;
}