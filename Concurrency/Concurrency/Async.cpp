#include <iostream>
#include <future>

void AsyncFunc(int val, int& localVal)
{
	std::cout << "1 Async Thread Id:" << std::this_thread::get_id << std::endl;
	std::cout << "A1:From the other thread:" << val << std::endl;
	std::cout << "A1:Local Val:" << localVal << std::endl;
	localVal++;
}

int AsyncFunc2(int& val)
{
	std::cout << "2 Async Thread Id:" << std::this_thread::get_id << std::endl;
	return val + 200;
}

void ideaOfAsync()
{
	std::cout << "Main Thread Id:" << std::this_thread::get_id << std::endl;
	int localVal = 56;
	std::future<void> f = std::async(std::launch::async, AsyncFunc, 200, std::ref(localVal));

	if (f.valid())
		f.get();

	if (f.valid())
		f.get();

	std::future<int> f2 = std::async(std::launch::async, AsyncFunc2, std::ref(localVal));

	if (f2.valid())
		std::cout << "Returned value:" << f2.get() << std::endl;

	if (f2.valid())
		f2.get();


	std::cout << "M:Local Val:" << localVal << std::endl;
}