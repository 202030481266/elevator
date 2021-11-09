#pragma once
// 所有的头文件可以添加#pragma once来防止头文件被重复编译
// 也可以使用ifndef and define 的方法来防止头文件被重复编译
#ifndef Floor_h
#define Floor_h
// 使用std命名空间
using namespace std;
/*----------------------------------------------------------------------------*/
// Floor类没有依赖的类，是最简单的一个类
// 主要功能：实现楼层号的变化功能
/*----------------------------------------------------------------------------*/
class Floor
{
public:
	Floor();
	// 只有当一个类被用来作为基类的时候，才会把析构函数写成虚函数
	// 可以避免内存泄漏S
	virtual ~Floor();
	// 这里使用inline内联函数，因为函数的代码量很少。
	inline void downFloornumber();
	// 楼层号加一
	inline void upFloornumber();
	// 楼层号减一
	inline void setFloornumber(const int number);
	// 设置楼层的号数
	inline int getFloornumber() const;
	// 得到楼层号数的函数，因为是只读去数据的函数所以在后面const限定（考虑安全性）
	static const int START_FLOOR = 1;
	// 这里使用常量表示特定的值是参考了大佬的代码，真的特别有用。
	// 这里规定从一楼开始
private:
	int floornumber;
};

inline void Floor::downFloornumber() {
	floornumber -= 1;// 楼层号减一
	return;
}

inline void Floor::upFloornumber() {
	floornumber += 1;// 楼层号加一
	return;
}

inline void Floor::setFloornumber(const int number) {
	floornumber = number;// 设置floor的楼层号
	return;
}

inline int Floor::getFloornumber() const {
	return floornumber;// 返回floor楼层号
}


#endif

