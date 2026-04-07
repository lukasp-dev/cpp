# implement `atoi` 
atoi enables the conversion from string to int

```cpp
#include <iostream>

int myAtoi(char* str){
    int res = 0;
    int sign = 1;
    if (str == nullptr) return -1;
    
    std::size_t i = 0;
    if(str[i] == '-') {
        sign = -1;
        i++;
    }
    
    for(; str[i] != '\0'; ++i){
        res = res*10 + str[i]-'0';
    }
    
    return res*sign;
}

int main(){
    char str[] = "-12321";
    std::cout << myAtoi(str) << "\n";
    
    return 0;
}
```