#pragma once
#include <string>
#include <vector>
#include "elevator.h"
#include "floor.h"
#include "passenger.h"
using namespace std;
/*=======================================================================================
	(1)Simulation类：实现模拟的类
	(2)主要功能：载入文件数据，实现电梯的运行调度
========================================================================================*/
class Simulation
{
private:
	SimulationTime* simulationtimeptr;
	PassengerList* passengerlistptr;
	string elevatordata;
	vector<Elevator> elevators;
	vector<double> waittimes;
	vector<double> traveltimes;
public:
	// 构造函数和析构函数
	Simulation();
	virtual ~Simulation();

	// 把乘客加入到乘客的列表中
	void addPassenger(
		const int time,
		const Floor& startfloor,
		const Floor& endfloor
	);

	// 检查乘客是否都到达了目标楼层
	bool checkPassengerAreCP() const;

	// 计算时间的函数
	void calTravelTimes();
	void outputTimes();// 输出相关数据信息

	// 以单位时间的方式增加模拟运行时间
	void addSimulationTime();

	// 从文件中载入数据的函数
	void loadData();

	void resetSimulation();

	// 把开始等待时间和模拟运行时间相同的乘客添加到队列中
	void queuePassenger();

	// 运行电梯（按照默认参数运行）
	void runDefaultSimulation(int fastest, int number);

	// 开始模拟
	void runSimulation(int elevatorTimeToNextFloor, int elevatornumber);

	// 设置数据文件的路径
	inline void setElevatorDataFile(const string& elevatordatas);

	// 解析文件字符串并且提取数据的函数
	void parseLine(
		const string& currLine,
		int& startTime,
		Floor& startFloor,
		Floor& endFloor
	) const;

	// 获得时间戳
	inline int getTime() const;

	static const int NUM_ELEVATORS = 4;       
	static const int NUM_FLOORS = 100;
};

inline int Simulation::getTime() const {
	return this->simulationtimeptr->getTime();
}

inline void Simulation::setElevatorDataFile(const string& elevatordatas) {
	this->elevatordata = elevatordatas;
	return;
}