# Head File

**Log.h**

> 函数声明（declaration）：是声明函数的头部，包括函数名，函数的参数、函数的返回值
>
> 头文件：一般存放函数声明，避免重复声明函数（pragma once）。
>
> **一般在cpp文件中需要声明函数，但是多个文件就需要声明多次，所以一般就只需要引用一个头文件就行。**

```c++
#pragma once
#ifndef _LOG_H
#define _LOG_H
void log(const char* message);

#endif // !_LOG_H
#ifndef _LOG_H
#define _LOG_H
void log(const char* message);

#endif // !_LOG_H
```

**log.cpp**

> 函数定义：定义函数的整体，包括头部和身体。

```c++
#include <iostream>
void log(const char* message)
{
	std::cout << message << std::endl;
}
```

**main.cpp**

> 主函数：程序的入口。

```c++
#include <iostream>
#include "Log.h"
int main() {
	int x = 6;
	bool camparionResult = x == 5;
	if (camparionResult) 
		log("HelloWold");
	std::cin.get();

}
```

# Linker and Complier()

> linker:连接器是用于cpp文件的数据交换，比如未定义的函数主体（一般一个函数只有一个主体），可以在另外一个函数主体中被linker。
>
> complier:编译器的作用是将cpp文件编译成机器码。

# Debug

## 进入debug

F5 进入debug，F11（step into），会一步一步进入函数的主体，F10（step over）一般会跳过函数的主体

## 查询内存

> 调出Memory1窗：debug-windows-Memory1
>
> 调出watch1窗：debug-windows-Watch1

watch1栏中，输入变量的名字即可查询变量的内存状态（值和类型）。

Memory1栏中，输入(&变量名）即可查询变量内存。

# Conditions and Branches(if statements)

> 右击-go to Disassembly转到汇编状态。

# Visual Studio 配置

> 右击项目-property-Output Directory 修改输出地址
>
> ```bash
> $(SolutionDir)bin\$(Platform)\$(Configuration)
> ```
>
> 右击项目-property-Intermediate Directory 修改中间地址
>
> ```bash
> $(SolutionDir)bin\intermediate\$(Platform)\$(Configuration)
> ```

> 右击-edit-mirror可以查看映射地址发现
>
> ```
> $(Solution) 的映射是带\的
> ```

# 过滤器和文件夹

> 过滤器是不存在于磁盘中的，只存在于解决方案中。
>
> 点击show all files 显示真实存在的文件夹，并且此时创建的文件夹是存在于磁盘中的。

#　指针（POINTERS）

##　一级指针

> 指针就是个保存变量地址的变量，一个地址对应是一个字节。

```C++
int main() {
	char* ptr = new char[8];
    //实例化一个8个字节的字符数组，返回的是数组的第一个数组的地址
    //char表示所指向地址的内容的类型是char类型的
	memset(ptr, 1, 8);//从第一个字节的数组开始填充数据1，往后填充8个字节
}
```

## 二级指针

> 指向指针的指针，保存的是指针的地址，可以用来修改一级指针的指向。

```c++
int main() {
	int* ptr;
	int a = 10;
	ptr = &a;
	int** pptr = &ptr;//二级指针指向的是一级指针的地址
}
```

# 引用

> 引用只是变量的别名，指向的是变量的地址，引用的使用使得代码更加简洁和易读。

## 指针形式定义函数参数

```c++
void Increment(int* value) {
	(*value)++;//必须要加括号，如果不加括号只是地址序号增加,而不是指针内容增加。
}
```

## 引用形式定义函数参数

```c++
void Increment(int& value) {
	value++;
}
```

# 类和结构体

##　类

> 类中的变量和函数默认都是私有的（private），外部无法访问。需要public关键词才能让外部访问。

```c++
#include <iostream>
class Player {
public:
	int x, y;
	void Move(int xa,int ya) {
		x += xa;
		y += ya;
	}
};
int main() {
	Player player;
	player.Move(1, 1);
	std::cin.get();
}
```

##　结构体

> 结构体的变量和函数默认是公有的（pubilc）。需要使用private变量私有化。
>
> 一般结构体适用于只有变量的，或者只有简单的功能的情况，或者以后都不会被继承的情况。如vector类，向量类。

```c++
#include <iostream>
struct Vec2
{
	float x, y;
};
int main() {
	Vec2 vec;
	vec.x = 1;
	vec.y = 1;
	std::cin.get();
}
```

# 类实例(Log类)

```c++
#include <iostream>
class Log {
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level) {
		m_LogLevel = level;
	}
	void Error(const char* message) {
		if (m_LogLevel >= LogLevelError)
			std::cout << "[ERROR]:" << message << std::endl;
	}
	void Warn(const char* message) {
		if (m_LogLevel >= LogLevelWarning)
			std::cout << "[WARNING]:" << message << std::endl;
	}
	void Info(const char* message) {
		if (m_LogLevel >= LogLevelInfo)
			std::cout << "[INFO]:" << message << std::endl;
	}

};
int main() {
	Log log;
	log.SetLevel(log.LogLevelWarning);
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");
	std::cin.get();
}
```

# 静态(static)

## 类（结构体）外静态变量

> 静态变量只在当前编译单元被连接器（linker）链接，不会从外部链接该变量。
>
> 同时外部编译单元（translation unit）申明的重复的变量，不会被连接器链接到该static 静态变量。

**source.cpp**

```c++
static int v_variable = 5;
```

**main.cpp**

```c++
#include <iostream>
int s_varibale = 5; //虽然重复申明，但是这里就不会报错，因为source.cpp中的v_varialb变量是静态变量，不会被linker（连接器）链接。
void main() {
	std::cout << s_varibale << std::endl;
}
```

##　类（结构体）内的静态变量

> 所有实例类共享一个静态变量，即所有实例的静态变量都指向同一个静态变量。
>
> 也就是该类的全局变量或者整个文件的全局变量。

```c++
#include <iostream>
struct Entity
{
	static int x, y;
	void Print() {
		std::cout << x << ',' << y << std::endl;
	}
};
int	Entity::x; //实例化静态变量
int	Entity::y;
void main() {
	Entity e1;
	e1.x = 5;
	e1.y = 2;
	Entity e2;
	e2.x = 8;
	e2.y = 10;
	e1.Print();//两个输出相同，因为都指向同一个地址
	e2.Print();
	std::cin.get();
}
```

> 静态方法只能访问静态变量，因为静态方法一开始就要被分配地址，所以其参数需要被实例化，或者地址要明确。

```c++
struct Entity
{
	static int x, y;
	static void Print() {
		std::cout << x << ',' << y << std::endl;
	}
};
```

> 可以直接以命名空间的形式访问静态变量和静态方法。

```c++
Entity::x = 1;
Entity::y = 2;
Entity::Print();
```

> 其实静态变量，相当于当前编译单元的局部变量。但是以这种形式定义，是为了使得其更具语义化，或者更具意义。

## 局部静态变量（local static）

### 变量的生命周期

> 这个变量i的生命周期在Function被执行完成后销毁。

```c++
void Function() {
	int i = 0;
	i++;
	std::cout << i << std::endl;
}
```

> 这个i变量在Function函数被执行完成后仍然保留

```c++
void Function() {
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}
```

### 变量的作用域

> 局部静态变量为函数提供了一个私有的局部静态变量，只有函数能够访问，并且**不会污染全局变量名**

```c++
#include <iostream>

void Function() {
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

void main() {
	Function();
	Function();
	Function();
	Function();
	Function();
	std::cin.get();
}
```

极其类似于

> 但以下方式会污染全局变量，作用域为全局。

```c++
#include <iostream>
int i = 0;
void Function() {
	i++;
	std::cout << i << std::endl;
}

void main() {
	Function();
	Function();
	Function();
	Function();
	Function();
	std::cin.get();
}
```

### 类中的局部静态变量

> 这里的s_Instaance在相当于在类中申请了一个全局变量。**会污染类的环境**
>
> 且需要实例化静态变量。

```c++
#include <iostream>
class Singleton {
private:
	static Singleton* s_Instance;
public:
	static Singleton& Get() {
		return *s_Instance;
	}
	void Hello() {
		std::cout << "Hello World" << std::endl;
	}
};
Singleton* Singleton::s_Instance = nullptr;//空指针保证指针不指向任何地址。
int main() {
	Singleton::Get().Hello();
	std::cin.get();
}
```

> 实际上在静态方法中声明一个静态变量更加简洁，且不污染类的环境。

```c++
#include <iostream>
class Singleton {
public:
	static Singleton& Get() {
		static Singleton instance;
		return instance;
	}
	void Hello() {
		std::cout << "Hello World" << std::endl;
	}
};
int main() {
	Singleton::Get().Hello();
	std::cin.get();
}
```

# 枚举（ENUM）

> 并且枚举中的变量已经被赋值。
>
> 枚举类型中只能访问自己的变量，无法访问其他枚举类的变量

```c++
#include <iostream>
enum Example1:int
{
	A,B,C
};
enum Example2:int
{
	A1,B,C
};
int main() {
	Example1 i = A;//枚举类型中只能访问自己的变量，无法访问其他枚举类的变量。
	int j = A;//A=0
	std::cout << A << std::endl;
	std::cout << typeid(i).name()<< std::endl;
	std::cin.get();
}
```

## 枚举类重写Log类

> 枚举使得代码更加简洁，且自动运算。
>
> **类的命名空间变量和函数会重名，此时访问相同名字的变量或者函数，会报错**

```c++
#include <iostream>
class Log {
public:
	enum Level
	{
		LevelError,
		LevelWarning,
		LevelInfo
	};
private:
	int m_LogLevel = LevelInfo;
public:
	void SetLevel(int level) {
		m_LogLevel = level;
	}
	void Error(const char* message) {
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]:" << message << std::endl;
	}
	void Warn(const char* message) {
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]:" << message << std::endl;
	}
	void Info(const char* message) {
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO]:" << message << std::endl;
	}

};
int main() {
	Log log;
	log.SetLevel(Log::LevelError);//类的命名空间变量和函数会重名，此时访问相同名字的变量或者函数，会报错
	log.Error("Hello");
	log.Warn("Hello");
	log.Info("Hello");
	std::cin.get();
}
```

# 构造函数

> 每个类都有一个默认的构造函数，构造函数可以用于初始化类的参数

## 无参的构造函数

```c++
#include <iostream>
class Entity {
public:
	Entity() {
		X = 0.0f;
		Y = 0.0f;
	}
	int X, Y;
	void Print() {
		std::cout << X << ',' << Y << std::endl;
	}
};
int main() {
	Entity e;
	e.Print();
}
```

## 有参数的构造函数

```c++
#include <iostream>
class Entity {
public:
	Entity(float x,float y) {
		X = x;
		Y = y;
	}

	int X, Y;
	void Print() {
		std::cout << X << ',' << Y << std::endl;
	}
};
int main() {
	Entity e1(1, 1);
	e1.Print();
	Entity e2(1, 1);
	e2.Print();
}
```

## 将构造函数私有化防止类被实例化

> 通过private关键字声明构造函数。

```c++
#include <iostream>
class Log {
private:
	Log(){}
public:
	static void write(const char* message) {
		std::cout << message << std::endl;
	}
};
int main() {
	Log log;//无法构造Log类，因为构造函数无法访问
}
```

> 通过delet关键字

```c++
#include <iostream>
class Log {
public:
	Log() = delete;
	static void write(const char* message) {
		std::cout << message << std::endl;
	}
};
int main() {
	Log log;
}
```

# 销毁器

> 销毁函数会在类被销毁时执行。

```c++
#include <iostream>
class Entity {
public:
	int X, Y;
	Entity() {
		X = 0;
		Y = 0;
		std::cout << X << ',' << Y << std::endl;
		std::cout << "Create Entity"<< std::endl;
	}
	~Entity()
	{
		std::cout << "Destroy Entity" << std::endl;
	}
};
void Function() {
	Entity e;
}
int main() {
	Function();
}
```

# 继承

```c++
#include <iostream>
class Entity {
public:
	int X, Y;
	void Move(float xa, float ya) {
		X += xa;
		Y += ya;
	}
};
class Player :public Entity {
public:
	const char* Name;
	void PrintNmae() {
		std::cout << Name << std::endl;
	}
};

int main() {
	std::cout << sizeof(Entity) << std::endl;//8 两个成员变量
	std::cout << sizeof(Player) << std::endl;//12 三个成员变量，因为继承了Entity类的2个成员变量
	Player player;
	player.Move(1, 1);
}
```

# 虚函数（virtual function）

> 添加虚拟函数，在父类指针指向子类时，父类指针会指向子类的方法。
>
> 若父类方法不设置为虚函数，则父类指针始终指向父类方法

```c++
#include <iostream>
#include <string>
class Entity {
public:
	virtual std::string GetName() { return "Entity"; }//添加虚拟函数，在父类指针指向子类时，父类指针会指向子类的方法。
};//若父类方法不设置为虚函数，则父类指针始终指向父类方法。
class Player :public Entity {
private:
	std::string m_Name;
public:
	Player(const std::string& name) : m_Name(name) {

	}
	std::string	GetName() { return m_Name; }
};

int main() {
	Entity* e = new Entity();
	std::cout << e->GetName() << std::endl;
	Player* player = new Player("guleixin");
	std::cout << player->GetName() << std::endl;

	Entity* entity = player;
	std::cout << entity->GetName() << std::endl;
	
}
```

> 编译器在静态联编时做了以下转换
>
> a->bark    --->       Animal::bark(a)
>
> **静态编联时，程序编译时，就决定了那个类调用了这个函数。**
>
> 当bark函数被设置为虚函数时，就不会进行那个转换了，而是转化为
> a->bark    ----》     (a->vtpl[1])(a) 
>
> **动态编联时，需要程序运行时，才能决定那个类调用这个函数**
>
> **先通过a指针找到对象，再找到对象中的虚表，再在虚表里面找到该调用的那个函数的函数指针**
>
> 因为必须要在a指向的对象里面找，所以   必须等到a被创建出来，所以必须是运行时
> 所以这就是动态联编 运行时决定调用哪个函数
>
> 
>
> 作者：乌索普
> 链接：https://www.zhihu.com/question/23971699/answer/84332610
> 来源：知乎
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

# 接口（interface (pure virtual function纯虚函数)）

> * 接口在父类中不被定义，但是子类中必须实现。
> * 在c++中，接口就是一个类。
> * 继承接口的类必须实现纯虚方法，不然无法实例化。

```c++
#include <iostream>
#include <string>
class Printable {
	virtual std::string PrintClassName() = 0;
};
class Entity:Printable {
public:
	std::string PrintClassName() override { return "Entity"; }
	virtual std::string GetName() { return "Entity"; }
};
class Player :public Entity,Printable {
private:
	std::string m_Name;
public:
	std::string PrintClassName() override { return "Player"; }
	Player(const std::string& name) : m_Name(name) {

	}
	std::string	GetName() { return m_Name; }
};

int main() {
	Entity* e = new Entity();
	std::cout << e->GetName() << std::endl;
	Player* player = new Player("guleixin");
	std::cout << player->GetName() << std::endl;

	Entity* entity = player;
	std::cout << entity->GetName() << std::endl;
	
}
```

# 权限修饰符（Visibility ）

> * public: 允许类内（子类父类），和类外其他函数中。
> * private:  只允许当前类内访问修改。
> * protect: 允许类内（子类和父类），其他函数不允许访问和修改。

# 数组（Array）

> 原始数组元素
>
> * 数组就是指针
> * char*指针的大小为1个字节
> * int* 指针的大小为4个字节

```c++
#include <iostream>

int main() {
	int example[5];
	int* ptr = example;
	int* another = new int[5];
	example[2] = 5;
	std::cout << *(ptr + 2) << std::endl;//int* 指针的大小为4个字节
	std::cout << *(int*)((char*)ptr + 8) << std::endl;//char*指针的大小为1个字节
	std::cin.get();
}
```

## 标准数组

```c++
#include <iostream>
#include <array>
int main() {
	std::array<int, 5> a;
}
```

## 求数组的大小

```c++
#include <iostream>
#include <array>
int main() {
	std::array<int, 5> a;
	int count = sizeof(a) / sizeof(int);//计算数组的大小，a数组的总的字节数除以int类型字节数
	std::cout << "数组a的大小为：" << count << std::endl;
	std::cin.get();
}
```

# 字符串（string）

```c++
#include <iostream>
int main() {
	const char* name = "Chrome";
	char a[7] = { 'C','h','r','o','m','e','\0' };//字符串的结尾必须包含一个'\n'和0
	std::cout << name << std::endl;
	std::cout << a << std::endl;
}
```

## 标准string

```c++
#include <iostream>
#include <string>
int main() {
	std::string name1 = "Cherno";
	name1 += "Hello";

	std::string name2 = std::string("Cherno") + "Hello";
	std::cout << name1 << std::endl;
	std::cout << name2 << std::endl;
}
```

> 通过const 和 char&引用来提升代码速度，因为复制太慢了。

```c++
#include <iostream>
#include <string>
//通过const 和 char&引用来提升代码速度，因为复制太慢了。
void PrintString(const std::string& string) {
	std::cout << string << std::endl;
}
int main() {
	std::string name1 = "Cherno";
	name1 += "Hello";
	
	std::string name2 = std::string("Cherno") + "Hello";
	std::cout << name1 << std::endl;
	std::cout << name2 << std::endl;
	PrintString("Hello World!");
}
```

# 字符串字面值（String Literals）

## 修改字符串字面值

> c++中，string literals是只读的变量，是编译在内存中的。用指针的方法无法修改。
>
> 可以利用字符串数组复制一份可修改的。

```c++
#include <iostream>
#include <string>
int main() {
	char name[] = "cherno";//这里是新建了一个变量，并且赋值了"cherno"的数值。
	name[2] = 'a';//这里的name不是"cherno"只读变量
	std::cout << name << std::endl;
}
```

## 不同类型的string

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
int main() {
	using namespace std::string_literals;
	std::string name0 = "cherno"s + "hello!";//这里的s是一个将string_literals类型转化成std::string
	//这里的"hello"相当于函数输入数值。

	std::cout << name0 << std::endl;
	const char* name = u8"Cherno";
	const wchar_t* name = L"Cherno";
	const char16_t* name = u"Cherno";
	const char32_t* name = U"Cherno";
}
```

## 输出换行和空格

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
int main() {
	using namespace std::string_literals;
	std::string string = R"(a 
		a
		a)";//这里的空格和换行都可以输出。
	std::cout << string << std::endl;
}
```

# const

> const 关键字：只读

## 只读变量

> 只读变量无法被修改。

```c++
#include <iostream>
int main() {
	const int a = 0;
	a = 1;//c此处的a无法被修改，因为是const变量。
}
```

## const指针

> 在指针（*）前，表示无法修改指针数据。

```c++
#include <iostream>
int main() {
	const int* a = 1;
	*a = 1;//不能修改指针所指的内容
	int b = 2;
	a = &b;//能重新分配指针地址
}
```

两个一样

```c++
#include <iostream>
int main() {
	int const* a = 1;
	*a = 1;//不能修改指针所指的内容
	int b = 2;
	a = &b;//能重新分配指针地址
}
```

> 在指针后面，表示无法重新分配指针地址。

```c++
#include <iostream>
int main() {
	int* const a = 1;
	*a = 1;//能修改指针所指的内容
	int b = 2;
	a = &b;//不能重新分配指针地址
}
```

## const 方法

> const方法不能修修改类中的变量。
>
> 不过能通修改mutalbe变量。

```c++
#include <iostream>
class Entity {
private:
	int m_X, m_Y;
	mutable int a;
public:
	int GetX() const {
		a = 2;//可以修改mutable变量。
		m_X = 2;//无法修改类中的变量。
		return m_X;
	}
};
int main() {
	int* const a = 1;
	*a = 1;//能修改指针所指的内容
	int b = 2;
	a = &b;//不能重新分配指针地址
}
```

## 通过const Entity引用的实体，无法调用非const变量

```c++
#include <iostream>
class Entity {
private:
	int m_X, m_Y;
	mutable int a;
public:
	int GetX()  {
		a = 2;//可以修改mutable变量。
		m_X = 2;//无法修改类中的变量。
		return m_X;
	}
};
void getX(const Entity& e) {
	e.GetX();//报错，因为调用了非const方法。
}
int main() {
	int* const a = 1;
	*a = 1;//能修改指针所指的内容
	int b = 2;
	a = &b;//不能重新分配指针地址
}
```

# mutalbe关键字

> 通过在Lambda表达式中，添加mutable就可以修改函数外的变量了。

```c++
#include <iostream>

int main() {
	int x = 0;
	auto f = [=]() mutable//添加mutable，可以使得f()可以访问外部的变量
	{
		x++;
		std::cout << x << std::endl;
	};
	f();
	//这里的x=0，因为f函数中只是复制了一份x的数据;
}
```

# 成员初始化表

> 在构造函数中，添加成员初始化表，可以初始化成员变量。
>
> 如果在构造方法中给成员赋值，则成员变量会**被赋值两次**

```c++
#include <iostream>
class Example {
public:
	Example() {
		std::cout << "Create Entity" << std::endl;
	}
	Example(const int& a) {
		std::cout << "Create Entity with"<< a << std::endl;
	}
};
class Entity {
private:
	Example e;
public:
	Entity()
		:e(8)//这里只实例化了一次
	{

	}

};
int main() {
	Entity aaa;
}
```

> 一下情况，e就被构造了两次

```c++
#include <iostream>
class Example {
public:
	Example() {
		std::cout << "Create Entity" << std::endl;
	}
	Example(const int& a) {
		std::cout << "Create Entity with"<< a << std::endl;
	}
};
class Entity {
private:
	Example e;
public:
	Entity()
	{
		e = Example(9);//这里e就构造了两次
	}

};
int main() {
	Entity aaa;
}
```



# 三元运算符（Ternary Operators）条件赋值(Conditional Assignment)

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
int main() {
	static int s_Level = 15;
	static int speed = 5;
	
	speed = s_Level > 15 ? 15 :1;//判断前面的条件，若满足返回第一个值，若不满足返回第二个值

	std::cout << speed << std::endl;
}
```

# 实例化类的两种方式

 ## 在栈（Stack）上实例化

> 使用这种方式实例化的类会在栈上开辟内存，并且会自动在最近的}上释放内存，

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
using String = std::string;
class Entity {
private:
	String m_name;
public:
	Entity() : m_name("Unknow") {
	}
	Entity(const String& name) :m_name(name) {
		
	}
	const String& GetName() { return m_name; }
};
int main() {
	Entity* e;//e指向空地址。
	{
		Entity entity("Cherno");
		e = &entity;//指向entity
		std::cout << entity.GetName() << std::endl;
	}
    //这里的entity的内存被释放，e指向空地址。
}
```

## 使用new关键字在堆（Heap）上实例化类

> 在堆上实例化的类不会自动释放内存，需要配合delet释放内存。

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
using String = std::string;
class Entity {
private:
	String m_name;
public:
	Entity() :m_name("Unknow") {
	}
	Entity(const String& name) :m_name(name) {

	}
	const String& GetName() { return m_name; }
};
int main() {
	Entity* e;
	{
		Entity* entity = new Entity("Cherno");
		e = entity;
		std::cout << entity->GetName() << std::endl;
	}

	delete e;//在此处释放new创建的Entity内存。
}
```

# new关键字

> 有new 就必须有delete。
>
> 通过new申请的类的内存空间大小，依据成员变量来订。
>
> array数组的空间大小，是单个的size倍。

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
using String = std::string;
class Entity {
private:
	String m_name;
public:
	Entity() :m_name("Unknow") {
	}
	Entity(const String& name) :m_name(name) {

	}
	const String& GetName() { return m_name; }
};
int main() {
	Entity* e = new Entity("Cherno");
	int* b = new int[50];// 200 byes

	delete[] b;//释放内存
	delete e;
}
```

# 隐式构造函数和显式构造函数（Implicit Conversion and the Explicit Keyword in C++）

## 隐式构造函数运行如下形式构造类

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
class Entity {
private:
	std::string m_name;
	int m_age;
public:
	Entity(const std::string& name) 
		:m_name(name), m_age(-1) {
	}
	Entity(int age) 
		:m_name("Unkonw"), m_age(age) {
	}
};
int main() {
	Entity e1 = 24;
	Entity e2 = std::string("gulei");
}
```

## 显式构造函数，不允许使用隐式构造规则，必须使用正常的方式构造类

> 在构造函数前添加explicit关键字。

```c++
#include <iostream>
#include <string>
#include <stdlib.h>
class Entity {
private:
	std::string m_name;
	int m_age;
public:
	explicit Entity(const std::string& name) 
		:m_name(name), m_age(-1) {
	}
	explicit Entity(int age)
		:m_name("Unkonw"), m_age(age) {
	}
};
int main() {
	Entity e1 = 24;//报错
	Entity e(24);
	Entity e2 = std::string("gulei");//报错
}
```

# 重写操作符（operator）

> c++允许重写如+、-、x、÷之类的操作符。

```c++
#include <iostream>
#include <string>

struct Vector2
{
	float x, y;
	Vector2(float x, float y)
		:x(x), y(y) {}
	Vector2 Add(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator+(const Vector2& other) const {
		return Add(other);
	}
	
};
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
	stream << other.x << ',' << other.y;
	return stream;
};
int main() {
	Vector2 position(4.0f, 4.0f);
	Vector2 speed(0.5f, 4.5f);
	Vector2 aaa1 = position.Add(speed);
	Vector2 aaa2 = position+speed;//重写了操作符
	std::cout << aaa1 << std::endl;
	std::cout << aaa2 << std::endl;
}
```

# this 关键字

> this关键字就是指向类的指针。

```c++
#include <iostream>
#include <string>

class Entity {
public:
	int x, y;
	int GetX() const {
		return this->x;
		PrintEntity(*this);
	}

};
void PrintEntity(const Entity& e) {

}
int main() {
	
}
```

# 堆栈的生命周期（Object Lifetime in C++ (Stack/Scope Lifetimes)）

> 堆的生命周期式程序到delete为止，如果没有delet，则堆将保留到程序结束。
>
> 栈的生命周期为代码段{}最后一个中括号为止。

```c++
#include <iostream>
#include <string>

class Entity {
private:
	std::string m_name;
public:
	Entity()
		:m_name("UnKnow") {
		std::cout << "Create "<<m_name<< std::endl;
	}
	Entity(std::string name)
		:m_name(name) {
		std::cout << "Create " << m_name << std::endl;
	}
	~Entity() {
		std::cout << "Destory " << m_name << std::endl;
	}
};
int main() {
	{
		Entity e1("e1");//e1会在中括号结束时被清除
		Entity* e2 = new Entity("e2");//e2不会被被清除
	}
}
```

> 使用智能指针实现自动释放内存。

```c++
#include <iostream>
#include <string>

class Entity {
private:
	std::string m_name;
public:
	Entity()
		:m_name("UnKnow") {
		std::cout << "Create "<<m_name<< std::endl;
	}
	Entity(std::string name)
		:m_name(name) {
		std::cout << "Create " << m_name << std::endl;
	}
	~Entity() {
		std::cout << "Destory " << m_name << std::endl;
	}
};
class ScopedPtr {
private:
	Entity* m_Ptr;
public:
	ScopedPtr(Entity* ptr)
		:m_Ptr(ptr){
	}
	~ScopedPtr() {
		delete m_Ptr;
	}
};
int main() {
	{
		ScopedPtr e1 = new Entity("e1");//在堆上生成了一个Entity，但是ScopedPtr指针在结束时，释放了Entity的内存。
	}
}
```

# 智能指针(std::unique_ptr, std::shared_ptr, std::weak_ptr)

> 智能指针就是管理堆上指针内存的指针。

## auto_ptr

> auto_ptr指针使用不当，会造成内存崩溃，所以在C++17中被移除。

### 测试实例

```c++
class Example
{
public:
    Example(int param = 0)
    {
        number = param;
        cout << "Example: " << number << endl;
    }

    ~Example() { cout << "~Example: " << number << endl; }

    void test_print() { cout << "in test print: number = " << number << endl; }

    void set_number(int num) { number = num; }

private:
    int number;
};
```

### get()函数、operator*（解引用）、operator->

```c++
void test1()
{
 auto_ptr<Example> ptr1(new Example(6));     // Example: 6(输出内容)
 if (ptr1.get())                             // 判断内部指针的有效性
 {
     // 以下为访问成员的3种方法
     ptr1.get()->test_print();               // in test print: number = 6(输出内容)
     ptr1->set_number(8);
     (*ptr1).test_print();                   // in test print: number = 8(输出内容)
 }
}                                               // ~Example: 8(输出内容) // 出作用域被析构

```

### release函数

> release函数是用来释放堆原始指针的控制权，但不释放原始指针的内存。释放后需要用delete来释放原始指针。

```c++
void test2()
{
 //auto_ptr<Example> ptr2 = new Example(6);  // 编译错误，不支持不同指针到智能指针的隐式转换
 auto_ptr<Example> ptr2(new Example(6));     // Example: 6(输出内容)
 if (ptr2.get())                             // 判断内部指针的有效性
 {
     ptr2.release();                         // 调用release之后会释放内存所有权，但是不会析构，造成内存泄漏
     if (!ptr2.get())
         cout << "ptr2 is invalid" << endl;  // ptr2 is invalid(输出内容)

     ptr2.release();                         // 多写一遍没有任何作用
 }
}   
```

### reset函数

```c++
void test4()
{
 auto_ptr<Example> ptr4(new Example(4));     // Example: 4(输出内容)
 cout << "after declare ptr4" << endl;       // after declare ptr4 
 ptr4.reset(new Example(5));                 // Example: 5
                                             // ~Example: 4 
 cout << "after function reset" << endl;     // after function reset
}   
```

### operator=

> operator=只是转移堆原始指针的控制所有权，等号两边的变量完全不相同。

```c++
void test5()
{
 auto_ptr<Example> ptr5(new Example(5));     // Example: 5(输出内容)
 auto_ptr<Example> ptr6 = ptr5;              // 没有输出

 if (ptr5.get())
     cout << "ptr5 is valid" << endl;        // 没有输出，说明ptr5已经无效，如果再调用就会崩溃

 if (ptr6.get())
     cout << "ptr6 is valid" << endl;        // ptr6 is valid(输出内容)

 ptr6->test_print();                         // in test print: number = 5(输出内容)
 //ptr5->test_print();                       // 直接崩溃 
}
```



## unique_ptr 详解与示例

> unique_ptr指针独享原始指针的所有权。无法复制，智能移动。
>
> 将堆上的指针关联到unique_ptr，而unique_ptr指针是普通对象，是在栈上的，所以超出作用域时会自动调用析构函数，unique_ptr的析构函数会自动delete关联的原始指针。

### unique_ptr指针的创建方法（2种）

```c++
//C++11: 
std::unique_ptr<Task> taskPtr(new Task(23));
//C++14: 
std::unique_ptr<Task> taskPtr = std::make_unique<Task>(34);
```

| 成员变量  | 作用                                                         |
| --------- | ------------------------------------------------------------ |
| reset()   | 重置表格为空，delet关联的指针。                              |
| release() | 不delet关联的指针，并返回关联的指针，释放关联指针的所有权，unique_ptr为空。 |
| get()     | 仅返回关联指针。                                             |

## 完整实例

```c++
#include <iostream>
#include <memory>

struct Task {
    int mId;
    Task(int id ) :mId(id) {
        std::cout<<"Task::Constructor"<<std::endl;
    }
    ~Task() {
        std::cout<<"Task::Destructor"<<std::endl;
    }
};

int main()
{
    // 空对象 unique_ptr
    std::unique_ptr<int> ptr1;

    // 检查 ptr1 是否为空
    if(!ptr1)
        std::cout<<"ptr1 is empty"<<std::endl;

    // 检查 ptr1 是否为空
    if(ptr1 == nullptr)
        std::cout<<"ptr1 is empty"<<std::endl;

    // 不能通过赋值初始化unique_ptr
    // std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error

    // 通过原始指针创建 unique_ptr
    std::unique_ptr<Task> taskPtr(new Task(23));

    // 检查 taskPtr 是否为空
    if(taskPtr != nullptr)
        std::cout<<"taskPtr is  not empty"<<std::endl;

    // 访问 unique_ptr关联指针的成员
    std::cout<<taskPtr->mId<<std::endl;

    std::cout<<"Reset the taskPtr"<<std::endl;
    // 重置 unique_ptr 为空，将删除关联的原始指针
    taskPtr.reset();

    // 检查是否为空 / 检查有没有关联的原始指针
    if(taskPtr == nullptr)
        std::cout<<"taskPtr is  empty"<<std::endl;

    // 通过原始指针创建 unique_ptr
    std::unique_ptr<Task> taskPtr2(new Task(55));

    if(taskPtr2 != nullptr)
        std::cout<<"taskPtr2 is  not empty"<<std::endl;

    // unique_ptr 对象不能复制
    //taskPtr = taskPtr2; //compile error
    //std::unique_ptr<Task> taskPtr3 = taskPtr2;

    {
        // 转移所有权（把unique_ptr中的指针转移到另一个unique_ptr中）
        std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
        // 转移后为空
        if(taskPtr2 == nullptr)
            std::cout << "taskPtr2 is  empty" << std::endl;
        // 转进来后非空
        if(taskPtr4 != nullptr)
            std::cout<<"taskPtr4 is not empty"<<std::endl;

        std::cout << taskPtr4->mId << std::endl;

        //taskPtr4 超出下面这个括号的作用于将delete其关联的指针
    }

    std::unique_ptr<Task> taskPtr5(new Task(66));

    if(taskPtr5 != nullptr)
        std::cout << "taskPtr5 is not empty" << std::endl;

    // 释放所有权
    Task * ptr = taskPtr5.release();

    if(taskPtr5 == nullptr)
        std::cout << "taskPtr5 is empty" << std::endl;

    std::cout << ptr->mId << std::endl;

    delete ptr;

    return 0;
}
```

## shared_ptr指针

> share_ptr指针可以运行共享统一个原始指针，利用引用计数来释放原始对象。

### get reset operator* operator->

```c++
void test1()
{
 //error C2440: “初始化”: 无法从“Example *”转换为“std::shared_ptr<Example>”
 //shared_ptr<Example> ptr1 = new Example(1);

 shared_ptr<Example> ptr1(new Example(1));   // Example: 1（输出内容）
 if (ptr1.get())                             // 调用函数get，获取原始指针，判断有效性
 {
     cout << "ptr1 is valid" << endl;        // 原始指针有效
 }
 ptr1->test_print();         // in test print: number = 1（输出内容），调用operator->

 ptr1.reset();               // ~Example: 1（输出内容）,调用函数reset，设置为空，释放原内部对象

 ptr1.reset(new Example(2)); // Example: 2（输出内容）,重新申请对象并设置

 (*ptr1).test_print();       // in test print: number = 1（输出内容），调用operator*
}                               // ~Example: 1（输出内容）,出定义域，释放内部对象
```

### operator bool 判断对象是否有效

```c++
void test2()
{
 shared_ptr<Example> ptr2(new Example(2));   // Example: 2（输出内容）
 if (ptr2)                                   // 调用operator bool
     cout << "ptr2 is valid" << endl;        // ptr2 is valid（输出内容），说明ptr2是有效的

 ptr2.reset();                               // ~Example: 2（输出内容），设置内部对象为空

 if (ptr2)                                   // 调用operator bool
     cout << "ptr2 is valid" << endl;        // 没有输出，说明ptr2已经无效
} 
```

### swap交换原始对象的操作权

```c++
void test3()
{
 shared_ptr<Example> ptr3(new Example(3));   // Example: 3（输出内容）
 shared_ptr<Example> ptr4(new Example(4));   // Example: 4（输出内容）
 ptr3->test_print();             // in test print: number = 3（输出内容）
 ptr4->test_print();             // in test print: number = 4（输出内容）

 ptr3.swap(ptr4);                // 调用函数swap

 ptr3->test_print();             // in test print: number = 4（输出内容）
 ptr4->test_print();             // in test print: number = 3（输出内容）
}                                   // ~Example: 3（输出内容）,出定义域，释放内部对象
                                 // ~Example: 4（输出内容）,出定义域，释放内部对象
```

## 函数`unique use_count operator=`用法

```c++
void test4()
{
 shared_ptr<Example> ptr4(new Example(4));   // Example: 4（输出内容）
 if (ptr4.unique())
 {
     cout << "ptr4 is unique" << endl;       // ptr4 is unique（输出内容）
     cout << "ptr4 use count : " << ptr4.use_count() << endl;// ptr4 use count : 1（输出内容）
 }

 shared_ptr<Example> ptr5 = ptr4;
 if (ptr4)
     cout << "ptr4 is valid" << endl;// ptr4 is valid(输出内容）说明赋值之后两个智能指针对象都有效

 if (ptr5)
     cout << "ptr5 is valid" << endl;// ptr5 is valid(输出内容）说明赋值之后两个智能指针对象都有效

 if (ptr4.unique())//判断指针是否唯一使用。
     cout << "ptr4 is unique" << endl;   // 没有输出，说明ptr4不是唯一管理内部对象的智能指针了

 cout << "ptr4 use count : " << ptr4.use_count() << endl;    // ptr4 use count : 2（输出内容）
 cout << "ptr5 use count : " << ptr5.use_count() << endl;    // ptr4 use count : 2（输出内容）
}                                                 // ~Example: 4（输出内容）,出定义域，释放内部对象

```

## weak_ptr指针，解决share_ptr循环引用问题

> weak_ptr 指针不会计数。

[参考](https://blog.csdn.net/albertsh/article/details/82286999)

```c++
class CB;
class CA
{
public:
    CA() { cout << "CA() called! " << endl; }
    ~CA() { cout << "~CA() called! " << endl; }
    void set_ptr(shared_ptr<CB>& ptr) { m_ptr_b = ptr; }
    void b_use_count() { cout << "b use count : " << m_ptr_b.use_count() << endl; }
    void show() { cout << "this is class CA!" << endl; }
private:
    shared_ptr<CB> m_ptr_b;
};

class CB
{
public:
    CB() { cout << "CB() called! " << endl; }
    ~CB() { cout << "~CB() called! " << endl; }
    void set_ptr(shared_ptr<CA>& ptr) { m_ptr_a = ptr; }
    void a_use_count() { cout << "a use count : " << m_ptr_a.use_count() << endl; }
    void show() { cout << "this is class CB!" << endl; }
private:
    shared_ptr<CA> m_ptr_a;
};

void test_refer_to_each_other()
{
    shared_ptr<CA> ptr_a(new CA());
    shared_ptr<CB> ptr_b(new CB());

    cout << "a use count : " << ptr_a.use_count() << endl;
    cout << "b use count : " << ptr_b.use_count() << endl;

    ptr_a->set_ptr(ptr_b);
    ptr_b->set_ptr(ptr_a);

    cout << "a use count : " << ptr_a.use_count() << endl;
    cout << "b use count : " << ptr_b.use_count() << endl;
}

```

# 复制和复制构造函数（Copying and Copy Constructors in C++）

## 浅层复制的成员变量地址相同。

```c++
#include <iostream>
#include <string>
class String {
private:
	char* m_Buffer;
	unsigned int m_size;
public:
	String(const char* string) {
		m_size = strlen(string);
		m_Buffer = new char[m_size+1];
		memcpy(m_Buffer, string, m_size+1);
	}
	~String() {
		delete[] m_Buffer;//会在析构时，释放两次m_Buffer
	}
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};
std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream << string.m_Buffer;
	return stream;
}
int main() {
	String string = "Cherno";
	String second = string;
	std::cout << string << std::endl;
	std::cout << second << std::endl;
	std::cin.get();
}
```

## 深层Copy（deep Copy）

```c++
#include <iostream>
#include <string>
class String {
private:
	char* m_Buffer;
	unsigned int m_size;
public:
	String(const char* string) {
		m_size = strlen(string);
		m_Buffer = new char[m_size+1];
		memcpy(m_Buffer, string, m_size+1);
	}
	//这里的m_Buffer时新申请的m_Buffer,所以在析构时不会析构同一个m_Buffer.
	String(const String& other)
		:m_size(other.m_size)
	{
		m_Buffer = new char[m_size+1];
		memcpy(m_Buffer, other.m_Buffer, m_size + 1);
	}
	~String() {
		delete[] m_Buffer;
	}
	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};
std::ostream& operator<<(std::ostream& stream, const String& string) {
	stream << string.m_Buffer;
	return stream;
}
int main() {
	String string = "Cherno";
	String second = string;
	std::cout << string << std::endl;
	std::cout << second << std::endl;
	std::cin.get();
}
```

# 箭头操作符

```c++
#include <iostream>
#include <string>
class Entity {
public:
	int x;
public:
	void Print() const { std::cout << "Hello!" << std::endl; }
};
class ScopedPtr
{
public:
	ScopedPtr(Entity* entity) 
		:m_Obj(entity)
	{
		
	};
	~ScopedPtr() {
		delete m_Obj;
	};
	Entity* operator->() {
		return m_Obj;
	}
private:
	Entity* m_Obj;
};
int main() {
	ScopedPtr entity = new Entity();
	entity->Print();
}
```

# 动态数组（Dynamic Array in c++）

```c++
#include <iostream>
#include <string>
#include <vector>
struct Vertex
{
    float x, y, z;
};
std::ostream &operator<<(std::ostream &stream, const Vertex &vertex)
{
    stream << vertex.x << "," << vertex.y << "," << vertex.z;
    return stream;
}
int main()
{
    std::vector<Vertex> Vertices;//将泛型指定为Vertex类
    Vertices.push_back({1, 2, 3});
    Vertices.push_back({4, 5, 6});
    Vertices.push_back({7, 8, 9});//在数组最后添加数据
    for (int i = 0; i < Vertices.size(); i++)
    {
        std::cout << Vertices[i] << std::endl;
    }
    for (Vertex &v : Vertices)
    {
        std::cout << v << std::endl;
    }
    std::cin.get();
    Vertices.erase(Vertices.begin() + 1);//删除序号元素对于的数组
    for (Vertex &v : Vertices)
    {
        std::cout << v << std::endl;
    }
}
```

# 优化动态数组

```c++
#include <iostream>
#include <string>
#include <vector>
struct Vertex
{
    float x, y, z;
    Vertex(float x, float y, float z)
        :x(x),y(y),z(z)
    {
        
    }
    Vertex(const Vertex &vertex)
        : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout << "Copied" << std::endl;
    }
};
std::ostream &operator<<(std::ostream &stream, const Vertex &vertex)
{
    stream << vertex.x << "," << vertex.y << "," << vertex.z;
    return stream;
}
int main()
{
    std::vector<Vertex> Vertices;
    Vertices.reserve(4);//预留4个空间，如果空间不足，会摧毁原来的vector，创建一个新的。
    Vertices.emplace_back(1, 2, 3);//在函数内部构造vertex
    Vertices.emplace_back(4, 5, 6);//push_back会复制vertex
    Vertices.emplace_back(7, 8, 9);
    for (Vertex& v : Vertices)
    {
        std::cout << v << std::endl;
    }
}
```

# 如何使用静态库文件

## 添加额外的include文件夹

> 右击解决方案-properties-c/c++-Generl-Additional Include Directories: $(SolutionDir)Denpendencies\GLFW\include

## 连接额外的库文件

> 右击解决方案-properties-Linker-Output File:glfw.lb
>
> 右击解决方案-properties-Linker-$(SolutionDir)Dependenceies\GLFW\lib-vc2019

# vs中多项目处理

## 项目输出配置

> 右击解决方案-properties-configuration type- Application(.exe)编辑为可执行文件。
>
> 头文件库如上
>
> 右击解决方案-add-reference 选择另外一个项目，编译后自动关联。

# 多返回值

> 返回一个结构体就行

```c++
#include <iostream>
struct Output
{
	std::string a1;
	std::string a2;
};
Output Function() {
	std::string b1 = "sdsd";
	std::string b2 = "sddsad";
	return { b1, b2 };
}
int main() {
	Output a = Function();
	std::cout << a.a1 << std::endl;
	std::cin.get();
}
```

# 模板(template)

```c++
#include <iostream>
template<typename T>

void Print(T value) {
	std::cout << value << std::endl;
}

int main() {
	Print("aaaa");
	std::cin.get();
}
```

```c++
#include <iostream>
template<typename T, int N>
class Array
{
public:
	int GetSize() const {
		return N;
	}
private:
	T m_Arrray[N];
};

int main() {
	Array<std::string, 50> array;
	std::cin.get();
}
```

# Stack vs Heap

> 在栈上开辟内存就是一句CPU命令
>
> 而在堆上开辟内存就是一个很复杂的过程。

# 宏定义（Macros）

```c++
#include <iostream>
#define Wait std::cin.get()
int main() {
	Wait;
}
```

```c++
#include <iostream>
#define Log(x) std::cout<<x<<std::endl
int main() {
	Log("aaa");
}
```

# auto 关键词

```c++
#include <iostream>
int main() {
	int a = 10;
	auto b = a;
}
```

# Function Pointer

## 使用auto指针定义函数指针

```c++
#include <iostream>
void HelloWorld() {
	std::cout << "Hello World" << std::endl;
}
int main() {
	auto aaa = HelloWorld;
	aaa();
}
```

## 使用tpyedef来定义函数指针类

```c++
#include <iostream>
void HelloWorld() {
	std::cout << "Hello World" << std::endl;
}
int main() {
	typedef void(*HelloWorldFunction)();
	HelloWorldFunction aaa = HelloWorld;
	aaa();
}
```

## 匿名函数

### 直接使用函数指针呼叫匿名函数作为函数的参数

```c++
#include <iostream>
#include <vector>
void PrintValue(int a) {
	std::cout << a << std::endl;
}
void ForEach(std::vector<int>& values, void(*Func)(int)) {
	for (int value : values) {
		Func(value);
	}
}
int main() {
	std::vector<int> values = { 1,2,3,4,6 };
	ForEach(values, PrintValue);
	std::cin.get();
}
```

### 在参数里直接定义一个Lambdas表达式

```c++
#include <iostream>
#include <vector>

void ForEach(std::vector<int>& values, void(*Func)(int)) {
	for (int value : values) {
		Func(value);
	}
}
int main() {
	std::vector<int> values = { 1,2,3,4,6 };
	ForEach(values, 
		[](int value) {
		std::cout << value << std::endl; 
		}
	);
	std::cin.get();
}
```

# Lambdas表达式

```c++
#include <iostream>
#include <vector>

void ForEach(std::vector<int>& values, void(*Func)(int)) {
	for (int value : values) {
		Func(value);
	}
}
int main() {
	std::vector<int> values = { 1,2,3,4,6 };
	auto lambdas = [](int value) {
		std::cout << value << std::endl;
	};
	ForEach(values, lambdas);
	std::cin.get();
}
```

# thread

> 并发：就是将一个线程划分成多个小段，先执行一小段再转换到另一个线程执行一小段，实现多个线程同时运行的效果。
>
> join()是对应主体会等待这个线程结束，再运行后面的程序。
>
> detach()是对应主题函数运行结束后，该线程会交给后台继续运行。
>
> **main()**函数也是一个独立的线程。

```c++
#include <iostream>
#include <thread>
void function1() {
	std::this_thread::sleep_for(std::chrono::microseconds(500));
	std::cout << "I'm function1" << std::endl;
}

void test() {
	std::thread t1(function1);
	
	t1.detach();
	//先出现test() is finish,再出现I'm function1。
	//t1.join();//这里是test()函数会等待t1的结束。
	//先出现I'm function,再出现test() is finish。
	std::cout << "test() is finish" << std::endl;
	
}
int main() {
	test();
	//test运行结束，t1被析构，但是t1被交给后台运行。
	//此时处于的是并发状态，先执行一小断main，再执行一小段function1。
	std::this_thread::sleep_for(std::chrono::microseconds(1000));
	return 0;
}
```

# timing

## 简单的用于程序计时的程序

```c++
#include <iostream>
#include <chrono>
#include <thread>

int main() {
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();//记录开始时间
	std::this_thread::sleep_for(1s);
	auto end = std::chrono::high_resolution_clock::now();//记录结束时间
	std::chrono::duration<float> duration = end - start;//持续时间
	std::cout << duration.count() << "s" << std::endl;
	std::cin.get();
}
```

## 使用结构体的构造和析构堆程序进行计时

```c++
#include <iostream>
#include <chrono>
#include <thread>
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()//在函数析构时，记录持续时间
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Timer took " << ms << "ms" << std::endl;

	}
};
void Function() {
	Timer timer;
	for (int i = 0; i < 100; i++)
	{
		//std::cout << i << "\n";
		std::cout << i << std::endl;
	}
}

int main() {
	Function();
	std::cin.get();
}

```

# 多维数组（Multidimensional Arrays in C++ (2D arrays)）

## 使用多级指针创建多维数组

```c++
#include <iostream>
//多维数组
int main() {
	int** a2d = new int* [50];//每个数组储存的是对应的指针
	for (int i = 0; i < 50; i++) {
		a2d[i] = new int[50];//此时生成的就是50*50的二维数组
	}
	//遍历数组
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			a2d[i][j] = 2;
		}
	}
	//delete多维数组
	for (int i = 0; i < 50; i++)
	{
		delete[] a2d[i];
	}
	delete[] a2d;
}

```

## 连续内存空间的多维数组

```c++
#include <iostream>
//多维数组
int main() {
	int* a2d = new int[50 * 50];
	//在连续内存空间上的多维数组。
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			a2d[i + 50 * j] = 2;
		}
	}
	delete[] a2d;
}
```

# 排序（Sorting）

> 默认是升序排序

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
	std::vector<int> values = { 3,5,4,1,2 };
	std::sort(values.begin(), values.end());
	for (int value : values) {
		std::cout << value << std::endl;
	}
	std::cin.get();
}
```

## 使用函数参数

> 后一个要比前一个能满足函数返回为true。

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
	std::vector<int> values = { 3,5,4,1,2 };
	std::sort(values.begin(), values.end(),std::greater<int>());
	for (int value : values) {
		std::cout << value << std::endl;
	}
	std::cin.get();
}
```

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
	std::vector<int> values = { 3,5,4,1,2 };
	std::sort(values.begin(), values.end(), [](int a, int b) {
		return a > b;
		});
	for (int value : values) {
		std::cout << value << std::endl;
	}
	std::cin.get();
}
```

# 类型双关（Type Punning ）

> 用其他类型来引用。

```c++
#include <iostream>
struct Entity {
	int x, y;
	int* GetPosition() {
		return &x;
	}
	Entity(const int& x, const int& y)
		:x(x),y(y){}

};

int main() {
	Entity e(3, 2);
	int* x = e.GetPosition();
	std::cout << x[0] << std::endl;
	std::cout << x[1] << std::endl;
	x[0] = 1;//用数组类型来访问Entity的成员变量，因为地址连续，所以可以成功访问
	x[1] = 1;
	std::cout << x[0] << std::endl;
	std::cout << x[1] << std::endl;
	std::cin.get();
}
```

```c++
#include <iostream>


int main() {
	int a = 2;
	double& value = *(double*)&a;
	std::cout << value << std::endl;//用double指针来解引用int指针所以由于double是8个字节，而int是4个字节，所以后前4个字节是cc未初始化，所以会出现奇怪的结果
	std::cin.get();
}
```

# union

> 将两个结构体绑定到同一款内存中。

```c++
#include <iostream>
struct vector2
{
	float x, y;
};
struct vector4
{
	union {
		struct 
		{
			float x, y, z, w;
		};
		struct 
		{
			vector2 a, b;
		};
	};//两个struct的内存长度相同，但是是同一块内存。
};
void PrintVector2(vector2 v) {
	std::cout << v.x << "," << v.y << std::endl;
}
int main() {
	vector4 v4 = { 1.0f,2.0f,3.0f,4.0f };
	PrintVector2(v4.a);
	PrintVector2(v4.b);
	std::cout << "----------------------------" << std::endl;
	v4.z = 500;
	PrintVector2(v4.a);
	PrintVector2(v4.b);
	std::cin.get();
}
```

# 虚拟析构函数（Virtual Destructors in C++）

> c++中，如果不使用虚拟析构函数，则当父类指针指向子类时，始终调用父类的析构函数，所以需要再父类中定义一个虚拟析构函数以在父类指针指向子类时，能够调用子类的析构函数，防止内存泄漏。

```c++
#include <iostream>
class Base
{
public:
	Base() {
		std::cout << "Base Constructor\n";
	};
	~Base() { std::cout << "Base Destructor\n"; };

private:

};

class Derived : public Base
{
public:
	Derived() { m_Arrray = new int[5]; std::cout << "Derived Constructor\n"; }
	~Derived() { delete m_Arrray; std::cout <<"Derived Destructor\n"; }

private:
	int* m_Arrray;
};
int main() {
	Base* base = new Base();
	delete base;
	std::cout << "----------------------------" << std::endl;
	Derived* derived = new Derived();
	delete derived;
	std::cout << "----------------------------" << std::endl;
	Base* poly = new Derived();
	delete poly;//这里只析构了父类的析构函数，而子类的析构函数未被调用，所以内存泄漏了。
}
```

> 在父类中把析构函数设置未虚函数，在动态编译时，才指定析构函数。

```c++
#include <iostream>
class Base
{
public:
	Base() {
		std::cout << "Base Constructor\n";
	};
	virtual ~Base() { std::cout << "Base Destructor\n"; };

private:

};

class Derived : public Base
{
public:
	Derived() { m_Arrray = new int[5]; std::cout << "Derived Constructor\n"; }
	~Derived() { delete m_Arrray; std::cout <<"Derived Destructor\n"; }

private:
	int* m_Arrray;
};
int main() {
	Base* base = new Base();
	delete base;
	std::cout << "----------------------------" << std::endl;
	Derived* derived = new Derived();
	delete derived;
	std::cout << "----------------------------" << std::endl;
	Base* poly = new Derived();
	delete poly;
}


```

# 类型转换（Casting in C++）

> ***\*static_cast\****是不安全的，不能再运行时检测。
>
> **dynamic_cast** 是安全的，能够再运行时检测，如果无法转换，则返回Null。

```c++
#include <iostream>
class Base
{
public:
	Base() {
		std::cout << "Base Constructor\n";
	};
	virtual ~Base() { std::cout << "Base Destructor\n"; };

private:

};

class Derived : public Base
{
public:
	Derived() { m_Arrray = new int[5]; std::cout << "Derived Constructor\n"; }
	~Derived() { delete m_Arrray; std::cout <<"Derived Destructor\n"; }

private:
	int* m_Arrray;
};
class AnotherClass {
public:
	AnotherClass(){}
	~AnotherClass(){}
};
int main() {
	Base* base = new Base();
	Derived* derived = new Derived();
	AnotherClass* ac = new AnotherClass();
	ac = dynamic_cast<AnotherClass*>(base);//返回null
}

```

# 条件断点和断点行为（Conditional and Action Breakpoints in C++）

> 右击断点，就可以添加条件和行为了。

# 动态投射

```c++
#include <iostream>
class Entity {

public: 
	virtual void PrintName() {}
};

class Player : public Entity {

};
class Enemy : public Entity {

};

int main() {
	Player* player = new Player();

	Entity* actualPlayer = player;
	Entity* actualEnemy = new Enemy();

	Player* p0 = dynamic_cast<Player*>(actualPlayer);

}

```

# 测试程序速度

```c++
#include <iostream>
#include <memory>
#include <chrono>
class Timer {
public:
	Timer() {
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		Stop();
	}
	void Stop() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
		
		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << duration << "us(" << ms << " ms)\n";
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

int main() {
	int value = 0;
	{
		Timer timer;
		for (int i = 0; i < 10000; i++) {
			value++;
		}
	}

	std::cout << value << std::endl;

	__debugbreak();
}
```

# C++ 17结构化绑定（STRUCTURED BINDINGS in C++）

> 需要再properties-C++ Language Standard -设置成C++17

```c++
#include <iostream>
#include <tuple>
#include <string>
std::tuple<std::string, int> CreatePerson()
{
	return { "cherno" , 24 };
}
int main() {

	auto[name, age] = CreatePerson();
	std::cout << name << std::endl;
	std::cin.get();
	return 0;
}
```

# 可选数据（数据无法打开时的默认数值）

```c++
#include <iostream>
#include <fstream>
#include <optional>

std::optional<std::string> ReadFileAsString(const std::string& filepath)
{
	std::ifstream stream(filepath);
	if (stream)
	{
		std::string result;
		stream.close();
		return result;
	}
	return {};
}

int main() {
	auto data = ReadFileAsString("data.txt");
	auto value = data.value_or("Not present");//数据无法打开时的默认值
	std::cout << value << std::endl;
	if (data.has_value())
	{
		std::cout << data.value() << std::endl;
		std::cout << "File read successfully!\n";
	}
	else
	{
		std::cout << "File could not be opened!\n";
	}
}

```

