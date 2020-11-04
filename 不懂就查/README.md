# C++智能指针的enable_shared_from_this和shared_from_this机制

## 问题

> 当一个类存在一个函数返回指向该类this(实例的)的智能指针时，需要会生成一个**指向同一个实例**，但是**两个引用计数器**的智能指针。使得当前类在生命周期结束时，析构两次同一个实例。

```c++
#include <iostream>
using namespace std;
// 智能指针测试类
class A
{
public:
	A():mptr(new int) 
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
		delete mptr; 
		mptr = nullptr;
	}
private:
	int *mptr;
};
int main()
{
	A *p = new A(); // 裸指针指向堆上的对象

	shared_ptr<A> ptr1(p);// 用shared_ptr智能指针管理指针p指向的对象
	shared_ptr<A> ptr2(p);// 用shared_ptr智能指针管理指针p指向的对象
	// 下面两次打印都是1，因此同一个new A()被析构两次，逻辑错误
	cout << ptr1.use_count() << endl; 
	cout << ptr2.use_count() << endl;

	return 0;
}
```

## 解决方法

> 使得当前类继承自enable_shared_from_this这个原子类，使得其能够拥有一个shared_from_this()方法。能够返回一个**既能指向当前的this的智能指针，同时不会生成两个引用计数器**

```c++
#include <iostream>
using namespace std;
// 智能指针测试类，继承enable_shared_from_this类
class A : public enable_shared_from_this<A>
{
public:
	A() :mptr(new int)
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
		delete mptr;
		mptr = nullptr;
	}

	// A类提供了一个成员方法，返回指向自身对象的shared_ptr智能指针
	shared_ptr<A> getSharedPtr()
	{
		/*通过调用基类的shared_from_this方法得到一个指向当前对象的
		智能指针*/
		return shared_from_this();
	}
private:
	int *mptr;
};
int main()
{
	shared_ptr<A> ptr1(new A());
	shared_ptr<A> ptr2 = ptr1->getSharedPtr();

	// 引用计数打印为2
	cout << ptr1.use_count() << endl;
	cout << ptr2.use_count() << endl;

	return 0;
}
```

# __VA_ARGS__用法

> 宏定义是指**...**对应的其他参数

```c++
#define dLog(fmt, ...) printf(fmt, ##__VA_ARGS__) // 这里的##__VA_ARGS__就是...对应的其他参数
```

