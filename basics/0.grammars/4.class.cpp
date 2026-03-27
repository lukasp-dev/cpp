#include <iostream>
#include <vector>

using namespace std; 


class User {
public:
    string id;
    string first_name;
    string last_name;
    string get_status(){
        return status;
    }
    User(string id, string first_name, string last_name){
        this->id = id;
        this->first_name = first_name;
        this->last_name = last_name;
    }
    ~User(){
        cout << "Destructor\n";
    }
// In cpp class, by default, the members are private
private:
    string status = "Gold";
};

int add_user_if_not_exists(vector<User> &users, User &user){
    for(int i=0; i<users.size(); i++){
        if(users[i].id == user.id){
            return i;
        }
    }
    
    users.push_back(user);
    return users.size()-1;
}

int main(){
    vector<User> users;
    users.reserve(10);

    users.emplace_back("1", "Jewook", "Park");
    users.push_back(User("2", "Issac", "Lee"));
    users.emplace_back(User("3", "David", "Yoo"));

}

/**
 * This code will call the Destructor 5 times. 
 * For more explanation, refer to the ./4.class.md.
 */