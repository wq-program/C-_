#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

class Person {
public:
	virtual void BuyTicket() { cout << "成人买票-全价" << endl;  }
};
class child {
public:
	virtual void BuyTicket() { cout << "儿童买票-全价" << endl;  }
};
class Student : public Person ,public child {
public:
	virtual void BuyTicket() { cout << "学生买票-半价" << endl;  }
};

class Teacher :public Person
{
public:
	/*virtual void BuyTicket() { cout << "老师买票-半价" << endl; }*/
};


void Func(Person& p)
{
	p.BuyTicket();
}

//不能被拷贝的类
class Test
{
public:
	Test(){}
	Test& operator=(const Test& t) = delete;//C++11
	Test(const Test& tmp) = delete; //C++11
private:
	//Test& operator=(const Test& t);//C++98
	//Test(const Test& tmp);//C++98
};

//只能在堆上创建的类——方法一
class OnlyHeap1
{
public:
	static OnlyHeap1* GetOnlyheap()
	{
		return new OnlyHeap1();
	}
	OnlyHeap1(const OnlyHeap1&) = delete;
	void destroy()
	{
		delete this;
	}
	~OnlyHeap1()
	{
		cout << "~OnlyHeap1()" << endl;
	}
private:
	OnlyHeap1() {}
	int b = 100;
};

//方法二
//析构函数私有化，栈上的对象就不能自动销毁，进而不能在栈上创建对象
class OnlyHeap
{
public:
	OnlyHeap() {}
	OnlyHeap(const OnlyHeap& obj) = delete;
	void destroy()
	{
		delete this;
	}
private:
	~OnlyHeap()
	{
		cout << "~OnlyHeap()" << endl;
	}
};


//只能在栈上创建对象
//1.封死构造函数
//2.提供创建好的栈上对象返回
//拷贝构造和移动构造得保留一个，以便创建得对象可以返回
class OnlyStack
{
public:
	static OnlyStack GetOnlyStack()
	{
		return OnlyStack(10);
	}
	OnlyStack(OnlyStack&& obj)
	{
		swap(obj._x, _x);
	}
private:
	OnlyStack(int x):_x(x)
	{}
	OnlyStack& operator=(const OnlyStack& obj) = delete;
	OnlyStack(const OnlyStack& obj) = delete;
	int _x;
};

//单例模式——饿汉模式
class Config
{
public:
	static Config*  Getinstence()
	{
		return _config;
	}
	void print()
	{
		cout << "print() Config" << endl;
	}
	~Config()
	{
		cout << "~Config()" << endl;
	}
private:
	Config(){}
	Config operator=(const Config& obj) = delete;
	Config(const Config& obj) = delete;

	static Config* _config;
};
Config* Config::_config = new Config();

//单例模式——懒汉模式
#include<mutex>

class FileDate
{
public:
	static FileDate* Getinstence()
	{
		if (_pconfig == nullptr)
		{
			mu.lock();
			if (_pconfig == nullptr)
			{
				return new FileDate();
			}
			mu.unlock();
		}
		return _pconfig;
	}
	void print()
	{
		cout << "print() FileDate" << endl;
	}
	~FileDate()
	{
		cout << "~FileDate()" << endl;
	}
private:
	FileDate() {}
	FileDate operator=(const FileDate& obj) = delete;
	FileDate(const FileDate& obj) = delete;
	static mutex mu;
	static FileDate* _pconfig;
};
FileDate* FileDate::_pconfig = nullptr;

#include<vector>
//堆
//       6
//   1       2
//3     4 5    0 
class heap
{
public:
	heap(vector<int>& arr)
		:_arr(arr)
	{
		int end = _arr.size() - 1;
		for (int i = (end - 1) / 2; i >= 0; i--)
		{
			down_adjust(i,_arr.size());
		}
	}
	void push(int x)
	{
		_arr.push_back(x);
		up_adjust(_arr.size() - 1);
	}
	void pop()
	{
		swap(_arr[0], _arr[_arr.size() - 1]);
		_arr.pop_back();
		down_adjust(0, _arr.size());
	}
	void sort()
	{
		int end = _arr.size();
		for (int i = 0; i < _arr.size(); i++)
		{
			swap(_arr[end - 1], _arr[0]);
			end--;
			down_adjust(0, end);
		}
	}
	void print()
	{
		for (auto e : _arr)
		{
			cout << e << ' ';
		}
	}
private:
	//用于push
	void up_adjust(int child)
	{
		int parent = (child - 1) / 2;
		while (parent >= 0)
		{
			if (_arr[parent] < _arr[child])
			{
				swap(_arr[child], _arr[parent]);
			}
			else break;
			child = parent;
			parent = (child - 1) / 2;
		}
	}
	//用于建堆和堆pop
	void down_adjust(int parent,int end)
	{
		int child = parent * 2 + 1;
		
		while (child < end)
		{
			if (child + 1 < end && _arr[child] < _arr[child + 1])child++;
			if (_arr[child] > _arr[parent])
			{
				swap(_arr[child], _arr[parent]);
			}
			else break;
			parent = child;
			child = parent * 2 + 1;
		} 
	}
	vector<int>& _arr;
};

//快排
class Qsort
{
public:
	Qsort(vector<int>& arr)
		:_arr(arr)
	{
		sort(0, _arr.size() - 1);
	}
	void print()
	{
		for (auto e : _arr)
		{
			cout << e << ' ';
		}
	}

private:
	void sort(int begin,int end)
	{
		if (begin > end)return;
		int key = _arr[begin];
		int left = begin;
		int right = end;
		while (left < right)
		{
			while (left < right && _arr[right] >= key)
			{
				right--;
			}
			while (left < right && _arr[left] <= key)
			{
				left++;
			}
			swap(_arr[left], _arr[right]);
		}
		swap(_arr[left], _arr[begin]);
		sort(begin, left - 1);
		sort(left + 1, end);
	}
	vector<int>& _arr;
};

//归并排序
class MergeSort
{
public:
	MergeSort(vector<int>& arr)
		:_arr(arr)
	{
		tmp.resize(_arr.size());
		mergesort(0, _arr.size() - 1);
	}
	void print()
	{
		for (auto e : _arr)
		{
			cout << e << ' ';
		}
	}
private:
	void mergesort(int begin,int end)
	{
		if (begin >= end)return;
		int mid = (begin + end) / 2;
		mergesort(begin, mid);
		mergesort(mid + 1, end);
		int begin1 = begin; int end1 = mid;
		int begin2 = mid + 1; int end2 = end;
		int tmpbegin = begin1;
		while (begin1 <= end1 && begin2 <= end2)
		{
			if (_arr[begin1] < _arr[begin2])tmp[tmpbegin++] = _arr[begin1++];
			else tmp[tmpbegin++] = _arr[begin2++];
		}
		while(begin1<=end1)tmp[tmpbegin++] = _arr[begin1++];
		while (begin2 <=end2)tmp[tmpbegin++] = _arr[begin2++];
		for (int i = begin; i <= end; i++)
		{
			_arr[i] = tmp[i];
		}
	}
	vector<int> tmp;
	vector<int>& _arr;
};

int main()
{
	vector<int> arr = { 5,7,3,1,6,4,2,9,0,8 };
	MergeSort q(arr);
	q.print();
	return 0;
}