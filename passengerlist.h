#pragma once
#ifndef passengerlist_h
#define passengerlist_h
#include "passenger.h"
#include <vector>
#include <list>
using namespace std;
/*===============================================================================
	(1)passengerlist是人流类,相当于控制所有乘客的信息的数据结构(所以很复杂)
	(2)功能：管理乘客的各类信息。
	(3)依赖的类：Floor, passenger.
================================================================================*/
class PassengerList
{
public:
	virtual ~PassengerList();

	// 添加乘客passenger
	inline void addPassenger(const Passenger& passenger);

	// 创建一个passengerlist的实例，使用指针管理，为静态成员函数
	inline static PassengerList* getInstance();

	// 找到下一位符合条件的乘客的索引
	bool getNextPassengerIndex(
		const int time,
		const Floor& currentfloor,
		const Floor& endfloor,
		const Passenger::Status status,
		int& passengerIndex
	);

	// 获取passengerlist中索引为index的passenger的上电梯的时间
	inline int getPassengerBoardElevatorTime(const int index) const;

	// 获取passengerlist中索引为index的passenger的下电梯的楼层号
	inline int getPassengerEndfloorNumber(const int index) const;

	// 获取passengerlist中索引为index的passenger的下电梯的时间
	inline int getPassengerExitElevatorTime(const int index) const;

	// 获取passengerlist中索引为index的passenger的ID
	inline int getPassengerID(const int index) const;

	// 获取passengerlist中索引为index的passenger的上电梯的楼层号
	inline int getPassengerStartfloorNumber(const int index) const;

	// 获取passengerlist中索引为index的passenger的开始等待的时间
	inline int getPassengerStartTime(const int index) const;

	// 获取passengerlist的大小，就是里面有多少个passenger
	inline int getPassengerListSize() const;

	// 获取passengerlist中索引为index的passenger的状态
	inline Passenger::Status getPassengerStatus(const int index) const;

	// 把某一楼层的正在等待的符合条件的乘客都加入到passengerlist中直到额定人数
	bool getQueuedPassengerAtFloor(
		const int time,
		const Floor& currentfloor,
		const int destPassengerIndex,
		const Passenger::Status status,
		vector<int>& nextPassengerIndex
	);

	// 重置passengerlist中索引为index的passenger的状态和上电梯，下电梯的时间
	void resetPassengerStatusAndBoardExitTime(const int index);

	// 设置passengerlist中索引为index的passenger的状态
	inline void setPassengerStatus(
		const int time,
		const int index,
		Passenger::Status status
	);
private:
	// 构造函数
	PassengerList();
	// 静态成员，指向一个passengerlis实例的指针
	static PassengerList* instancePtr;
	// passengerlist用标准库的vector来实现
	vector<Passenger> Passengerlist;
};

inline void PassengerList::addPassenger(const Passenger& passenger) {
	this->Passengerlist.push_back(passenger);
	return;
}

inline PassengerList* PassengerList::getInstance() {
	if (!instancePtr) {
		instancePtr = new PassengerList;
	}
	return instancePtr;
}

inline int PassengerList::getPassengerBoardElevatorTime(const int index) const {
	return this->Passengerlist.at(index).getboardElevatorTime();
}

inline int PassengerList::getPassengerEndfloorNumber(const int index) const {
	return this->Passengerlist.at(index).getEndFloornumber();
}

inline int PassengerList::getPassengerExitElevatorTime(const int index) const {
	return this->Passengerlist.at(index).getExitElevatorTime();
}

inline int PassengerList::getPassengerID(const int index) const {
	return this->Passengerlist.at(index).getID();
}

inline int PassengerList::getPassengerListSize() const {
	return this->Passengerlist.size();
}

inline int PassengerList::getPassengerStartfloorNumber(const int index) const {
	return this->Passengerlist.at(index).getStartFloornumber();
}

inline int PassengerList::getPassengerStartTime(const int index) const {
	return this->Passengerlist.at(index).getStartTime();
}

inline Passenger::Status PassengerList::getPassengerStatus(const int index) const {
	return this->Passengerlist.at(index).getStatus();
}

inline void PassengerList::setPassengerStatus(const int time, const int index, Passenger::Status status) {
	this->Passengerlist.at(index).setStatus(status, time);
	return;
}

#endif
