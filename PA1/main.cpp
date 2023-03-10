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
	std::unique_lock<std::mutex> lock(sharedResource.mtx);
	std::cout << "job1 is executed " << '\n';
	
}

void job2(SharedResource& sharedResource)
{

	/*
	
	std::defer_lock is a constant of type std::defer_lock_t that is used as a parameter when constructing
	a std::unique_lock object. It is used to specify that the lock should not be acquired immediately 
	when the std::unique_lock object is constructed. 
	Instead, the lock can be acquired later, using the lock or try_lock member functions of the std::unique_lock object.
	In this example, a std::unique_lock object is constructed with std::defer_lock as a parameter. 
	This means that the lock is not acquired immediately when the std::unique_lock object is constructed. 
	Instead, the lock is acquired later, using the lock member function. This allows you to do some work before
	acquiring the lock, and ensures that the lock is only acquired when it's actually needed.
	*/
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

