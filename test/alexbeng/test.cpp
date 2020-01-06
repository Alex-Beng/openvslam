#include <iostream>
#include <thread>
#include <chrono>
 
void foo()
{
    std::cout << "foo is started\n";
    // 模拟昂贵操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "foo is done\n";
}
 
void bar()
{
    std::cout << "bar is started\n";
    // 模拟昂贵操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "bar is done\n";
}
 
int main()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);
 
    std::cout << "starting second helper...\n";
    std::thread helper2(bar);
 
    std::cout << "waiting for helpers to finish...\n" << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}