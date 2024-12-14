#include <iostream>
#include <thread>

void sayHello()
{
    std::cout << "Hello there!!" << std::endl;
}

void add(int a, int b)
{
    std::cout << "The result of " << a << " + " << b << " = " << a + b << std::endl;
}

int main()
{
    std::thread t1(sayHello);
    std::thread t2(add, 3, 4);

    t1.join();
    t2.join();
}
