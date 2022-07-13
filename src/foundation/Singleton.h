#pragma once
template<typename T>
class Singleton
{
private:
	Singleton() = delete;
	~Singleton() = delete;
public:
	inline static T& getInstance();
};

template<typename T>
inline static T& Singleton<T>::getInstance()
{
	static T instance;
	return instance;
}
