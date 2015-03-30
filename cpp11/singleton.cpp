#include <iostream>
#include <atomic>
#include <mutex>

class SingletonWithStatic
{
	public:
		static SingletonWithStatic& getInstance()
		{
			static SingletonWithStatic imp;
			return imp;
		}

		void test()
		{
			std::cout << " in SingletonWithStatic test(). " << std::endl;
		}
};


class SingletonWithDCLP
{
	public:
		
		static SingletonWithDCLP* getInstance() {
			SingletonWithDCLP* tmp = m_instance.load();
			if (tmp == nullptr) {
				std::lock_guard<std::mutex> lock(m_mutex);
				tmp = m_instance.load();
				if (tmp == nullptr) {
					tmp = new SingletonWithDCLP;
					m_instance.store(tmp);
				}
			}
			return tmp;
		}

		void test()
		{
			std::cout << " in SingletonWithDCLP test(). " << std::endl;
		}
	private:
		static std::atomic<SingletonWithDCLP*> m_instance;
		static std::mutex m_mutex;

};

int main()
{
	SingletonWithStatic& single = SingletonWithStatic::getInstance();
	single.test();

	SingletonWithDCLP* dclpSingleton = SingletonWithDCLP::getInstance();
	dclpSingleton->test();
	return 0;

}
