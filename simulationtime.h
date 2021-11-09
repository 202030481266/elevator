#pragma once
#ifndef stimulationtime_h
#define stimulationtime_h
/*===========================================================================*/
/*
	(1)本程序一切的运行遵循时间去完成各种任务，所以时间是本程序的核心。
	(2)Simulation实现的主要功能：
		1.获取时间，设置时间
		2.操作时间
	(3)没有依赖的类，是一个基类。
=============================================================================*/
class SimulationTime
{
public:
	// 只有当一个类被用来作为基类的时候，才会把析构函数写成虚函数
	// 可以避免内存泄漏S
	virtual ~SimulationTime();
	// 创建一个SimulationTime的实例，使用指针管理，为静态成员函数
	inline static SimulationTime* getInstance();

	// 获取时间
	inline int getTime() const;
	// 设置时间
	inline void setTime(const int time);
	// 操作时间，这里是让模拟运行的时间加上单位1
	inline void incrementTime();
private:
	// 构造函数
	SimulationTime();
	// 指向实例的指针
	static SimulationTime* instancePtr;
	// 时间数值
	int time;
};

// 如果instancePtr是空指针，那么就创建一个实例，instancePtr指向新创建的实例
inline SimulationTime* SimulationTime::getInstance() {
	if (!instancePtr) {
		instancePtr = new SimulationTime;
	}
	return instancePtr;
}

inline int SimulationTime::getTime() const {
	return time;
}

inline void SimulationTime::incrementTime() {
	this->time += 1;// 这里加上的是单位时间
	return;
}

inline void SimulationTime::setTime(const int time) {
	this->time = time;// 设置时间，this指针指向类成员
	return;
}

#endif // !simulationtime_h
