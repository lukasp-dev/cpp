#include <iostream>
using namespace std;

class User {
string first_name;
string last_name;
string ringStatus;

public:
    void setRingStatus(string ringStatus){
        if(ringStatus == "Gold" || ringStatus == "Silver" || ringStatus == "Bronze"){
            this->ringStatus = ringStatus;
        }else{
            this->ringStatus = "No Status";
        }
    }

    string getRingStatus(){
        return this->ringStatus;
    }
};

int main() {
    User user;
    user.setRingStatus("Taco");
    cout << user.getRingStatus() << "\n"; // No Status
    return 0;
}


