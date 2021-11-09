#pragma once
#include "simulation.h"
/*============================================================================
	(1)setting类：主要是调控电梯的一些参数
	(2)主要功能就是调整电梯的一些重要参数
============================================================================*/
class Setting
{
public:
	Setting();
	virtual ~Setting();
	inline void setElevatorMaxPassengers(const int num);
	inline void setElevatorNumbers(const int num);
	inline void setFloorNumbers(const int num);
	inline void setTimeToNextFloor(const int num);
	inline void setStopTime(const int num);
private:
	int TIME_INTERVAL;
	int MAX_FLOORS;
	int MAX_PASSENGER_NUM;
	int STOP_SECS;
	int MAX_ELEVATOR_NUM;
	friend Simulation;
};

inline void Setting::setElevatorNumbers(const int num) {
	MAX_ELEVATOR_NUM = num;
	return;
}

inline void Setting::setElevatorMaxPassengers(const int num) {
	MAX_PASSENGER_NUM = num;
	return;
}

inline void Setting::setFloorNumbers(const int num) {
	MAX_FLOORS = num;
	return;
}

inline void Setting::setTimeToNextFloor(const int num) {
	TIME_INTERVAL = num;
	return;
}

inline void Setting::setStopTime(const int num) {
	STOP_SECS = num;
	return;
}