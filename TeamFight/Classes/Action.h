#pragma once
#include <functional>
#include <vector>
#include <algorithm>

template<typename ...Args>
class Action
{
public:
	~Action() 
	{
		callbacks.clear();
	}
public:
	using Callback = std::function<void(Args...)>;
	
	void add(Callback _callback) 
	{
		callbacks.push_back(_callback);
	}

	void remove(Callback _callback) 
	{
		auto it = std::find(callbacks.begin(), callbacks.end(), _callback);
		if (it != callbacks.end()) {
			callbacks.erase(it);
		}
	}

	void invoke(Args... args) 
	{
		for (const auto& cb : callbacks) 
		{
			cb(args...);
		}
	}

private:
	std::vector<Callback> callbacks;
};
