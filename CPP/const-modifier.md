# CONST 修饰符

c++中的const修饰符视作常量，可以修饰在变量前，但是在类中的const 成员函数的用法又不太一致。

## const成员函数

```cpp
struct A {
    int val;
    mutable int mval;
    void print() const {
        ...
    }
    void print() {
        
    }
};
```

上述两个print函数是重载的，const修饰的成员函数本质上是在this指针上加上了const。

```cpp
void A::print(A* this, args...);
void A::print(const A* this, args...); // 无法修改成员变量
```

对于需要在const成员函数中修改的值，可以使用mutable来修饰，const成员函数本质上就是this指针变成了const，那么使用const_cast进行转换后完全可以修改。

```cpp
void print() const {
    auto *rcthis = const_cast<A*>(this);
    (*rcthis).val = 0;
}
```

## 函数重载中的const

函数重载的判断准则就是能否查找到一个符合的函数进行调用（决议）

```cpp
int foo(int a, int b);
int foo(const int a, const int b);
int goo(const int a, const int b);
```

foo 函数只是增加了const，无法进行重载的，编译器会报出函数重复定义的问题。从函数签名可以理解为什么。

```dump
_Z3fooii
_Z3gooii
```

const 修饰非指针，引用时，生成的函数签名是一致的。

### const 修饰指针和引用

```cpp
void test(char *p);          // _Z4testPc
void test(const char *p);    // _Z4testPKc
void test(char &p);          // _Z4testRc
void test(const char &p);    // _Z4testRKc
```

签名完全不一致，所以能够重载！

指针常量 和 常量指针

```cpp
const char * p0;
char * const p1;

void test(char * p);
void test(char * const p);   // 无法重载
```

## const 变量的修改

在cpp中，const属性就是代表常量，而修改常量是**未定义行为**！

```cpp
const int val = 0;
const int *pcval = &val;
int *pval = const_cast<int *>(pcval);

*pval = 1;  // modify

// ouput
printf("%d, %p", val, &val);				// 0   0xaddr
printf("%d, %p", *pcval, &pcval);			// 1 0xaddr
printf("%d, %p", *pval, &pval);              // 1 0xaddr
```

为什么同一个地址却输出不同的值？

通过汇编代码发现，编译器生成的代码将所有`val`都替换成立即数。所以修改是无法直接通过val体现，从地址可以判断，值实际上是修改的！

解决方法是加上`volatile`关键字这样能够每次都从内存中获取新值。

```cpp
volatile const int val = 0;
```









