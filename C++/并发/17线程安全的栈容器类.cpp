#include<iostream>
#include<memory>
#include<stack>
#include<mutex>
#include<exception>

struct empty_stack :std::exception
{
	const char* what()const throw() { return " "; }
};
template<typename T>
class threadsfe_stack {
private:
	std::stack<T>data;
	mutable std::mutex m;
public:
	threadsfe_stack(){}
	threadsfe_stack(const threadsfe_stack& other)
	{
		std::lock_guard<std::mutex>lock(other.m);
		data = other.data;
	}
	threadsfe_stack& operator=(const threadsfe_stack&) = delete;
	void push(T new_value)
	{
		std::lock_guard<std::mutex>lock(m);
		data.push(std::move(new_value));
	}
	std::shared_ptr<T>pop()
	{
		std::lock_guard<std::mutex>lock(m);
		if (data.empty())throw empty_stack();
		std::shared_ptr<T>const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex>lock(m);
		if (data.empty())throw empty_stack();
		value = data.top();
		data.pop();
	}
	bool empty()const
	{
		std::lock_guard<std::mutex>lock(m);
		return data.empty();
	}
};
int main() {
	threadsfe_stack<int> a;
	a.push(10);
	std::cout << *a.pop();
}
/*����һ�ַ�ǿ���Եı�׼�������û����Զ����쳣�̳�std::exception������catch���ܲ����û��Զ�����쳣��*/