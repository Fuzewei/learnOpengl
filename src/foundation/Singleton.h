#pragma once
template<typename T>
class Singleton
{
public:
	Singleton() {};
	~Singleton() {};
public:
	 static T& getInstance();
};

template<typename T>
 T& Singleton<T>::getInstance()
{
	static T instance;
	return instance;
}
