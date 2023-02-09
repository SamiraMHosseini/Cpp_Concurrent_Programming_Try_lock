#include <iostream>
#include <mutex>
#include <thread>
struct SharedResource
{
	SharedResource() :
		mtx(), counter(0)

	{

	}
	std::mutex mtx;
	int counter;
};

void job1(SharedResource& sharedResource)
{

	
	/*std::unique_lock<std::mutex> lock(sharedResource.mtx, std::defer_lock);
	if (lock.try_lock())
	{
		std::cout << "job1 is executed " << '\n';
	}
	else
	{
		std::cout << "job1 coulnd't get executed " << '\n';
	}*/


	std::unique_lock<std::mutex> lock(sharedResource.mtx);
	std::cout << "job1 is executed " << '\n';
	
}

void job2(SharedResource& sharedResource)
{

	std::unique_lock<std::mutex> lock(sharedResource.mtx, std::defer_lock);
	if (lock.try_lock())
	{

		std::cout << "job2 is executed " << '\n';
	}
	else
	{
		std::cout << "job2 couldn't get executed " << '\n';
	}
}
int main()
{
	SharedResource sharedReference;
	std::thread th1(job1, std::ref(sharedReference));
	std::thread th2(job2, std::ref(sharedReference));
	th1.join();
	th2.join();
}

