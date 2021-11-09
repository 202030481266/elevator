#include "stdafx.h"
#include "SimulationTime.h"

SimulationTime* SimulationTime::instancePtr = 0;

SimulationTime::SimulationTime() {
	this->time = 0;// 初始化时间为0
}
// 析构函数
SimulationTime::~SimulationTime() {}