#include <iostream>
#include <cstdlib>
#include <ctime>

//1
class Array {
private:
    int* data;
    size_t size;
public:
    Array() : data(nullptr), size(0) {}
    Array(size_t size) : size(size) {
        data = new int[size];
    }
    Array(const Array& other) : size(other.size) {
        data = new int[other.size];
        for (size_t i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }
    }
    void initialize(size_t newSize, int minVal, int maxVal) {
        delete[] data;
        size = newSize;
        data = new int[size];
        srand(time(0)); 
        for (size_t i = 0; i < size; ++i) {
            data[i] = minVal + std::rand() % (maxVal - minVal + 1);
        }
    }
    void initialize(int minVal, int maxVal) {
        srand(time(0));  
        for (size_t i = 0; i < size; ++i) {
            data[i] = minVal + std::rand() % (maxVal - minVal + 1);
        }
    }
    void initialize(int minVal, int maxVal, int(*func)()) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = minVal + func() % (maxVal - minVal + 1);
        }
    }
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    ~Array() {
        delete[] data;
    }
};
//2
class String {
private:
    char* data;
    size_t length;

    size_t getLength(const char* str) const {
        size_t len = 0;
        while (str[len] != '\0') {
            ++len;
        }
        return len;
    }
    void copyString(char* dest, const char* src) const {
        while (*src) {
            *dest++ = *src++;
        }
        *dest = '\0';
    }
public:
    String() : data(new char[1] { '\0' }), length(0) {}
    String(const char* str) {
        if (str) {
            length = getLength(str);
            data = new char[length + 1];
            copyString(data, str);
        }
        else {
            data = new char[1] { '\0' };
            length = 0;
        }
    }
    String(const String& other) : length(other.length) {
        data = new char[length + 1];
        copyString(data, other.data);
    }

    ~String() {
        delete[] data;
    }
    size_t getLength() const {
        return length;
    }
    bool isEqual(const String& other) const {
        if (length != other.length) {
            return false;
        }
        for (size_t i = 0; i < length; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }
    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        copyString(data, other.data);
        return *this;
    }
    void print() const {
        std::cout << data;
    }
};

int main() {
    //1
    Array arr1(10);
    arr1.initialize(1, 100);
    std::cout << "arr1: ";
    arr1.print();
    Array arr2;
    arr2.initialize(5, 1, 50);
    std::cout << "arr2: ";
    arr2.print();
    Array arr3 = arr2;
    std::cout << "arr3 (copy arr2): ";
    arr3.print();
    //2
    String str1("Hello");
    String str2("World");
    String str3(str1);
    std::cout << "str1: "; str1.print(); std::cout << ", length: " << str1.getLength() << std::endl;
    std::cout << "str2: "; str2.print(); std::cout << ", length: " << str2.getLength() << std::endl;
    std::cout << "str3: "; str3.print(); std::cout << ", length: " << str3.getLength() << std::endl;
    std::cout << "str1 is equal to str2: " << (str1.isEqual(str2) ? "true" : "false") << std::endl;
    std::cout << "str1 is equal to str3: " << (str1.isEqual(str3) ? "true" : "false") << std::endl;
}
