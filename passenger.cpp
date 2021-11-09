#include "stdafx.h"
#include "passenger.h"

// 乘客类的构造函数
Passenger::Passenger() {
	this->id = Passenger::INIT_TO_INVALID;
	this->startTime = Passenger::INIT_TO_INVALID;
	this->setStatus(Passenger::NOT_SET, Passenger::INIT_TO_INVALID);
	this->setBoardElevatorTime(Passenger::INIT_TO_INVALID);
	this->setExitElevatorTime(Passenger::INIT_TO_INVALID);
}
// 析构函数
Passenger::~Passenger() {}

// 打印乘客的状态信息
void Passenger::printStatus() const {
	switch (this->status)
	{
	case NOT_SET:
	{
		cout << "NOT_SET!";
		break;
	}
	case QUEUED_WAITING_FLAGGED:
	{
		cout << "QUEUED_WAITING_FLAGGED!";
		break;
	}
	case QUEUED_WAITING_DOWN:
	{
		cout << "QUEUED_WAITING_DOWN!";
		break;
	}
	case QUEUED_WAITING_UP:
	{
		cout << "QUEUED_WAITING_UP!";
		break;
	}
	case RIDING:
	{
		cout << "RIDING!";
		break;
	}
	case COMPLETED:
	{
		cout << "COMPLETED!";
		break;
	}
	}
	return;
}

// 设置乘客的电梯的状态，使用this指针表明是类成员
void Passenger::setStatus(const Passenger::Status status, int time) {
	this->status = status;
	// 这里的乘客的如果不是初始空值，那么有两种情况
	// 如果乘客的状态变为RIDING，那么表示乘客上了电梯，更新数据
	// 如果乘客的状态变为COMOLETED，显然乘客下了电梯，更新数据
	if (status != Passenger::NOT_SET) {
		if (status == Passenger::RIDING)
			boardElevatorTime = time;
		else if (status == Passenger::COMPLETED)
			exitElevatorTime = time;
	}
	return;
}

