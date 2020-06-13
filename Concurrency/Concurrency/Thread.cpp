#include <iostream>
#include <thread>

void ThreadFunc(int val, int& localVal)
{
	std::cout << "1:From the other thread:" << val << std::endl;
	std::cout << "1:Local Val:" << localVal << std::endl;
	localVal++;
}

void ideaOfThread()
{
	int localVal = 5;
	std::thread th(ThreadFunc, 9, std::ref(localVal));
	std::thread th2([&]() {localVal++;  std::cout << localVal << std::endl; });

	th.join();
	th2.join();
	std::cout << "M:Local Val:" << localVal << std::endl;

}