#ifndef _SINGLETON_H
#define _SINGLETON_H

template <typename T>
class Singleton
{
	public:
		static T* getInstance()
		{
			if(!instance)
				instance = new T();
			return instance;
		}
		static T& getMe()
		{
			return *getInstance();
		}
		static void delMe()
		{
			if(instance)
			{
				delete instance;
				instance = NULL;
			}
		}
	protected:
		static T * instance;
		Singleton(){}
		~Singleton(){}
	private:
		Singleton(const Singleton&);
		const Singleton & operator = (const Singleton &);
};

template <typename T>
T * Singleton<T>::instance = NULL;

#endif
