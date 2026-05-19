#include <iostream>

// the members in the struct is by default public.
struct User {
    std::string last_name;
    std::string first_name;
    std::string status;
    int getRingSize(){
        return  ringSize;
    }
private:
    int ringSize = 10;
};

int main(){
    User me;
    me.last_name = "Park";
    me.first_name = "Jewook";
    me.status = "Gold";

    // First Name: Jewook
    // Last Name: Park
    std::cout << "First Name: " << me.first_name << "\n" << "Last Name: " << me.last_name << "\n"; 
    /**
     * /Users/a/Desktop/cpp/basics/structs.cpp:8:17: note: declared private here
     *      std::string ringSize;
     *                   ^
     *   1 error generated.
     */
    // std::cout << "Ring Size(Failed): " << me.ringSize << "\n";
    // encapsulation
    std::cout<< "Ring SIze(Succeeded): " << me.getRingSize() << "\n"; //Ring SIze(Succeeded): 10
    return 0;
}