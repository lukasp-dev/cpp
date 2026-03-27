#include <iostream>
using namespace std;

class User {

static int userCount;
string ringStatus;

public:
    static int getUserCount(){
        return userCount;
    }
    string firstName;
    string lastName;
    void setRingStatus(string ringStatus){
        if(ringStatus == "Gold" || ringStatus == "Silver" || ringStatus == "Bronze"){
            this->ringStatus = ringStatus;
        }else{
            this->ringStatus = "No Status";
        }
    }

    User(){
        userCount++;
    }

    User(string firstName, string lastName, string ringStatus){
        this->firstName = firstName;
        this->lastName = lastName;
        this->ringStatus = ringStatus; 
        userCount++;
    }
    
    ~User(){
        userCount--;
    }

    string getRingStatus(){
        return this->ringStatus;
    }
};

int User::userCount = 0;

int main() {
    User user, user1, user2, user3, user4;
    user.~User();
    cout << User::getUserCount() << "\n"; // 4
    return 0;
}


