#include <iostream>
#include <future>


int AsyncFunc(int val, std::promise<int>& prms)
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	prms.set_value(45);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	prms.set_value(50);
	std::this_thread::sleep_for(std::chrono::seconds(3));
	prms.set_value(55);

	return 0;
}

void ideaOfFutureAndPromises()
{
	std::promise<int> promises;
	int localVal = 5;
	std::async(std::launch::async, AsyncFunc, localVal, std::ref(promises));

	std::future<int> f = promises.get_future();
	if (f.valid()) {
		std::cout << f.get() << std::endl;
	}

	//Below does not align with the intent
	/*while(f.valid()) {
		std::cout << f.get() << std::endl;
		f = promises.get_future();
	}*/
}