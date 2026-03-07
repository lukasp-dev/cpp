#include <iostream>
#include <vector>

void work(std::vector<int>& data){
    for(int i = 0; i< data.size(); i++){
        data[i]++;
    }
    std::cout << &data << std::endl; // 0x16b21e6e0
}

int main(){
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::cout << &data << std::endl; // 0x16b21e6e0
    work(data);
    std::cout << &data << std::endl; // 0x16b21e6e0
    for (int x : data){
        std::cout << x << " "; // 2 3 4 5 6
    }

    return 0;
}