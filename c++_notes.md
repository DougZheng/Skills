```cpp
// 理解复杂的声明，自右向左逐一分析
int *p1 = nullptr;
int *&p2 = p1; // 引用，引用指针，引用int类型的指针
int &*p3 = p1; // ❌ 引用本身不是对象，没有指向引用的指针
int *(&arry)[10] = ptrs; // 引用，引用一个大小为10的数组，数组元素类型为int*

int val = 33;
const int *const p4 = &val; // 常量，指针常量，指向const int类型的指针常量
constexpr int *p5 = &val; // constexpr指针，应该理解为：int *const p5，但是要求val地址固定不变（定义于函数体外）
```



```cpp
shared_ptr<string> p = make_shared<string>("hello");
```



考虑继承，一个基类有三种用户：基类及基类的友元、派生类和普通用户。

基类将接口成员声明 $\text{public}$ ，接口成员三种用户都可以访问。剩余的分为两组：一组仅由基类及基类的友元访问的声明为 $\text{private}$ ；另一组声明为 $\text{protected}$ ，可供派生类访问。

三种继承方式影响的是派生类的调用方的访问权限，$\text{protected}$ 继承相当于把基类的 $\text{public}$ 成员在（直接）派生类中变成 $\text{protected}$ 权限，$\text{private}$ 继承相当于把基类的 $\text{public}$ 成员和 $\text{protected}$ 成员在（直接）派生类中变成 $\text{private}$ 权限。



派生类向基类的类型转换，只有在转换前后可访问性不发生变化的情况下才合法。



```cpp
class Base {
public:
    int pub_mem;
protected:
    int prot_mem;
private:
    int priv_mem;
};

class Pub_Derv : public Base { 
public:
    int get_pub_mem() { return pub_mem; }    // 正确，派生类可以访问基类的public成员
    int get_prot_mem() { return prot_mem; }  // 正确，派生类可以访问基类的protected成员
    int get_priv_mem() { return priv_mem; }  // 错误，派生类不能访问基类的private成员
    void point_to_this() { Base *p = this; } // 正确，可访问性没有改变
};

class Prot_Derv : protected Base { 
public:
    int get_pub_mem() { return pub_mem; }    // 正确，派生类可以访问基类的public成员
    int get_prot_mem() { return prot_mem; }  // 正确，派生类可以访问基类的protected成员
    int get_priv_mem() { return priv_mem; }  // 错误，派生类不能访问基类的private成员
    void point_to_this() { Base *p = this; } // 正确，可访问性没有改变
};

class Priv_Derv : private Base { 
public:
    int get_pub_mem() { return pub_mem; }    // 正确，派生类可以访问基类的public成员
    int get_prot_mem() { return prot_mem; }  // 正确，派生类可以访问基类的protected成员
    int get_priv_mem() { return priv_mem; }  // 错误，派生类不能访问基类的private成员
    void point_to_this() { Base *p = this; } // 正确，可访问性没有改变
};

int main() {

    Base base;
    base.pub_mem = 0;  // 正确，普通用户可以访问类的public成员 
    base.prot_mem = 0; // 错误，普通用户不能访问类的protected成员
    base.priv_mem = 0; // 错误，普通用户不能访问类的private成员
    
    Pub_Derv pub_derv;
    pub_derv.pub_mem = 0;  // 正确，pub_mem在派生类中权限是public
    pub_derv.prot_mem = 0; // 错误，prot_mem在派生类中权限是protected
    pub_derv.priv_mem = 0; // 错误，priv_mem在派生类中权限是private

    Prot_Derv prot_derv;
    prot_derv.pub_mem = 0;  // 错误，pub_mem在派生类中权限是protected
    prot_derv.prot_mem = 0; // 错误，prot_mem在派生类中权限是protected
    prot_derv.priv_mem = 0; // 错误，priv_mem在派生类中权限是private

    Priv_Derv priv_derv;
    priv_derv.pub_mem = 0;  // 错误，pub_mem在派生类中权限是private
    priv_derv.prot_mem = 0; // 错误，prot_mem在派生类中权限是private
    priv_derv.priv_mem = 0; // 错误，priv_mem在派生类中权限是private

    Base *p_pub = &pub_derv;   // 正确，可访问性没有改变
    Base *p_prot = &prot_derv; // 错误，可访问base的pub_mem，不可访问prot_derv的pub_mem
    Base *p_priv = &priv_derv; // 错误，可访问base的pub_mem，不可访问priv_derv的pub_mem

    return 0;
}
```



调用 $\text{p->mem()}$ 时，首先确定 $\text{p}$ 的静态类型，在其作用域里依次向外查找 $\text{mem}$ ，找到后若 $\text{mem}$ 是虚函数则在运行时依据动态类型进行调用，否则在编译时期完成常规函数调用。



派生类的成员函数将隐藏所有基类的同名函数（所有重载版本），即便只重新定义了一个重载版本，其他在基类的重载版本也将被隐藏，若要使用，需要使用 ``` using``` 关键字来声明。



基类的析构函数定义为虚函数 ```virtual ~Base() = default;``` ，$\text{delete}$ 动态内存时才可以运行正确的析构函数。



通常情况下不能将右值引用绑定到一个左值上，例外：模板右值引用参数的推断。

将左值传递给模板右值引用参数 $\text{T}$，模板实参 $\text{T}$ 被推断为 $\text{T&}$ ，传递右值则被推断为 $\text{T&&}$ ，折叠后左值仍为左值、右值仍为右值。

```cpp
template <typename T>
void f(T &&x) {
    ++x;
}
int x = 0;
f(x); // 正确，x = 1
```

故一般使用这样的重载：

```cpp
template <typename T>
void f(T &&x); // 绑定非const右值
void f(const T &x); // 绑定左值和const右值
```


在调用时使用 ```std::forward``` 保持类型信息：

```cpp
void f(int &&x) {}
template <typename T>
void g(T &&x) {
    f(x); // 错误，函数参数x是左值，即便传递的实参是右值
}
g(42);
```

使用转发保持实参的左值/右值属性：

```cpp
void f(int &&x) {}
template <typename T>
void g(T &&x) {
    f(std::forward<T>(x));
}
g(42);
```