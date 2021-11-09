#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "elevator.h"

// first version for scan algorithm

//#ifndef _elevator_cpp_
//#define _elevator_cpp_
//#include "elevator.h"
//
///*--------------------------------------------------------------------
//* 函数：Elevators()
//* 功能：构造函数
//* 初始值：电梯速度为1， 电梯状态为3，电梯楼层为1楼， 电梯乘客人数为0
//* --------------------------------------------------------------------
//*/
//Elevators::Elevators()
//{
//	ClimbSpeed = 1;
//	ElevatorStatus = 3;
//	preStatus = 3;
//	ElevatorFloorNum = 1;
//	ElevatorPassengerNum = 0;
//}
//
///*--------------------------------------------------------------------
//* 函数：GetClimbSpeed(), GetPassengerNum(), GetFloorNum(),GetStatus(),
//* GetGoalFloor()
//* 功能：获取电梯参数数据的函数
//* --------------------------------------------------------------------
//*/
//int Elevators::GetClimbSpeed()
//{
//	return ClimbSpeed;
//}
//
//int Elevators::GetPassengerNum()
//{
//	return ElevatorPassengerNum;
//}
//
//int Elevators::GetFloorNum()
//{
//	return ElevatorFloorNum;
//}
//
//int Elevators::GetStatus()
//{
//	return ElevatorStatus;
//}
//
//
//int Elevators::GetGoalFloor()
//{
//	// 如果电梯在上升的状态
//	if (GetStatus() == 1)
//	{
//		/*---------------------------------------------------------
//		* 重构日期：2021/5/28
//		* 功能：寻找并返回第一个大于电梯所处的楼层的请求楼层
//		for (int i = 0; i < Up_tasks.size(); i++)
//		{
//			if (Up_tasks[i] > GetFloorNum())
//			{
//				int temp = Up_tasks[i];
//				Up_tasks.erase(Up_tasks.begin() + i);
//				return temp;
//			}
//		}
//		* 使用二分的查找可以更快地解决：upper_bound(),前提是任务的列表要排好序
//		* -----------------------------------------------------------
//		*/
//		int cur = GetFloorNum();
//		// 找到第一个大于当前楼层的楼层数
//		vector<int>::iterator iter = upper_bound(Up_tasks.begin(), Up_tasks.end(), cur);
//		Up_tasks.erase(iter);
//		return *iter;
//	}
//	else if (GetStatus() == 2)
//	{
//		/*------------------------------------------------------------
//		* 重构代码：2021/5/28
//		for (int i = 0; i < Down_tasks.size(); i++)
//		{
//			if (Down_tasks[i] < GetFloorNum())
//			{
//				int temp = Down_tasks[i];
//				Down_tasks.erase(Down_tasks.begin() + i);
//				return temp;
//			}
//		}*/
//		int cur = GetFloorNum();
//		vector<int>::iterator iter = lower_bound(Down_tasks.begin(), Down_tasks.end(), cur);
//		// 找到第一个小于当前楼层的楼层
//		return *(iter - 1);
//	}
//}
//
///*--------------------------------------------------------------------
//* 函数：SetStatus(), SetClimbspeed(), SetFloorNum(), SetPassengerNum()
//* 功能：设置电梯参数数据的函数
//* --------------------------------------------------------------------
//*/
//void Elevators::SetStatus(int a)
//{
//	ElevatorStatus = a;
//}
//
//void Elevators::SetClimbspeed(int a)
//{
//	ClimbSpeed = a;
//}
//
//void Elevators::SetFloorNum(int floor)
//{
//	ElevatorFloorNum = floor;
//}
//
//void Elevators::SetPassengerNum(int num)
//{
//	ElevatorPassengerNum = num;
//}
//
///*--------------------------------------------------------------------
//* 函数：ShowElevator()
//* 功能：打印电梯的运行状态。
//* 重构日期：2021/5/28
//* --------------------------------------------------------------------
//*/
//void Elevators::ShowElevator()
//{
//	if (GetStatus() == 1)
//	{
//		// 电梯上升阶段。
//		printf("the elevator is going up to %d floor, now on the %d floor\n",
//			GetGoalFloor(), GetFloorNum());
//
//	}
//	else if (GetStatus() == 2)
//	{
//		// 电梯下降阶段。
//		printf("the elevator is going down to %d floor, now on the %d floor\n",
//			GetGoalFloor(), GetFloorNum());
//
//	}
//	// 此时电梯处于静止的状态
//	else
//	{
//		// 电梯在等待请求
//		printf("the elevator now is waiting for the tasks!\n");
//	}
//	return 0;
//}
//
///*--------------------------------------------------------------------
//* 函数：SCAN_Elevator()
//* 功能：扫描各个楼层的请求，并且处理请求
//* 内容：进行了大规模的调整，增加了请求的有序处理。
//* --------------------------------------------------------------------
//*/
//void Elevators::SCAN_Elevator(Queue queues[])
//{
//	// 电梯需要检查一栋楼的每一层楼
//	for (int i = 1; i < 11; i++)
//	{
//		// 检查第 i 层楼
//		for (auto& passenger : queues[i].passengerlist)
//		{
//			// 对于第i层楼的任务队列中的每一个乘客对象
//			int goal = passenger.GetGoalDirection();
//			int floor = passenger.GetGoalNum();
//			// 这是上升请求。
//			if (goal == 1)
//			{
//				vector<int>::iterator result = find(Up_tasks.begin(), Up_tasks.end(), floor);
//				// 防止上升任务列表中有重复的目标楼层
//				if (result == Up_tasks.end())
//					Up_tasks.push_back(floor);
//			}
//			else if (goal == 2)
//			{
//				vector<int>::iterator result = find(Down_tasks.begin(), Down_tasks.end(), floor);
//				// 防止下降任务列表中有重复的目标楼层
//				if (result == Down_tasks.end())
//					Down_tasks.push_back(floor);
//			}
//		}
//	}
//	// 将任务列表的顺序进行排序。
//	sort(Up_tasks.begin(), Up_tasks.end());
//	sort(Down_tasks.begin(), Down_tasks.end());
//	cout << "请求已经接收，处理完成。" << endl;
//}
//
///*--------------------------------------------------------------------
//* 函数：RUN()
//* 功能：运行电梯
//* 内容：优化了对楼层逻辑的管理。
//* --------------------------------------------------------------------
//*/
//void Elevators::RUN()
//{
//	// 如果处于上升状态
//	if (GetStatus() == 1)
//	{
//		// 一直上升到最顶层或者上升任务列表为空了。
//		while (GetFloorNum() < 10 && !Up_tasks.empty())
//		{
//			int nowfloor = GetFloorNum();
//			// 到达了这一层楼，所有的人都从电梯下来
//			remove(Up_tasks.begin(), Up_tasks.end(), nowfloor);
//			int goalfloor = GetGoalFloor();
//			ShowElevator();
//			// 重新设置电梯所处的楼层位置
//			SetFloorNum(nowfloor + GetClimbSpeed());
//			// 这里的每一次上升一层都要1秒
//			Sleep(1000);
//			// 判断有没有到达指定的楼层，到达了就删除任务列表的楼层
//			/*----------------------------------------------
//			* 根本不用这样做，只需要到达某一层，就删除某一层
//			if (nowfloor == goalfloor)
//			{
//				remove(Up_tasks.begin(), Up_tasks.end(), goalfloor);
//			}-----------------------------------------------*/
//			printf("已经到达第%d层楼\n", GetFloorNum());
//		}
//		// 此时电梯改变状态，变为静止模式，进行判断。
//		preStatus = 1;
//		SetStatus(3);
//	}
//	// 如果处于下降的模式
//	else if (GetStatus() == 2)
//	{
//		// 一直下降直到到达楼层1或者下降列表为空
//		while (GetFloorNum() > 1 && !Down_tasks.empty())
//		{
//			int nowfloor = GetFloorNum();
//			// 到达了这一层楼，所有的人都从电梯下来
//			remove(Down_tasks.begin(), Down_tasks.end(), nowfloor);
//			int goalfloor = GetGoalFloor();
//			ShowElevator();
//			SetFloorNum(nowfloor - GetClimbSpeed());
//			Sleep(1000);
//			printf("已经到达第%d层楼\n", GetFloorNum());
//		}
//		// 这是电梯完成了一次循环，处于静止的状态。
//		preStatus = 2;
//		SetStatus(3);
//	}
//	// 电梯处于静止的状态时。
//	else
//	{
//		/*-----------------------------------------------------------------------------------
//		* 新添加的功能：静止状态的变化的调整(个人觉得很复杂)
//		* 内容：
//		*	1.静止出现的情况只有三种：一开始初始化的时候，上升任务和下降任务执行完毕的时候。
//		*	2.由于下降的任务可能是在一楼（包括一开始）或者没办法继续执行下降
//		*  （因为请求的楼层大于电梯所在的楼层）情况停止、
//		*	或者是在最顶楼没有办法执行上升（请求的楼层在下面）、
//		*	3.调整状态：
//		*		(i)所有的任务列表都为空，此时必然处于静止状态。
//		*		(ii)此时处于顶层时，由于无法上升，只能为下降；处于底层，由于无法下降，只能为上升。
//		*	4.更加复杂的情况：此时上升结束了，但是不在顶层，如果上面有人要下去的话，这时要改为上升状态
//		*   预防饥饿效应（有可能他们一直下不来），同理，在下面的话，如果有人要上去，就要改为下降状态。
//		* ------------------------------------------------------------------------------------
//		*/
//		if (Up_tasks.empty() && Down_tasks.empty())
//		{
//			return;
//		}
//		// 后面的任务列表没有全为空
//		else if (GetFloorNum() == 10)
//		{
//			SetStatus(2);
//		}
//		else if (GetFloorNum() == 1)
//		{
//			SetStatus(1);
//		}
//		else if (GetFloorNum() < 10 && preStatus == 1 &&
//			*max_element(Down_tasks.begin(), Down_tasks.end()) >= GetFloorNum())
//		{
//			// 这时候的电梯要到达下降列表的最高的楼层
//			int maxfloor = *max_element(Down_tasks.begin(), Down_tasks.end());
//			while (GetFloorNum() < maxfloor)
//			{
//				SetFloorNum(GetFloorNum() + GetClimbSpeed());
//				Sleep(1000);
//				printf("the elevator is going up to %d floor, now on the %d floor\n",
//					maxfloor, GetFloorNum());
//			}
//			// 到达了最高的楼层后,模式改为下降。
//			SetStatus(2);
//		}
//		else if (GetFloorNum() > 1 && preStatus == 2 &&
//			*min_element(Up_tasks.begin(), Up_tasks.end()) <= GetFloorNum())
//		{
//			// 这时候电梯应该到达上升列表的最底层
//			int minfloor = *min_element(Up_tasks.begin(), Up_tasks.end());
//			while (GetFloorNum() > minfloor)
//			{
//				SetFloorNum(GetFloorNum() - GetClimbSpeed());
//				Sleep(1000);
//				printf("the elevator is going down to %d floor, now on the %d floor\n",
//					minfloor, GetFloorNum());
//			}
//			// 到达了最底层，模式改为上升。
//			SetStatus(1);
//		}
//		else if (preStatus == 1)
//		{
//			// 之前是上升的但是下降列表没有大于当前楼层的
//			SetStatus(2);
//		}
//		else if (preStatus == 2)
//		{
//			// 之前的状态是下降的但是上升列表没有小于当前楼层的
//			SetStatus(1);
//		}
//	}
//	return;
//}
//
//#endif

// 电梯的构造函数
Elevator::Elevator()
{
	// 电梯一开始是没有人的并且处于静止状态
	setMovestate(Elevator::STOPPED_NO_PASSENGERS);
	// 创建passengerlist和simulation的实例
	passengerListPtr = PassengerList::getInstance();
	simulationTimePtr = SimulationTime::getInstance();
	name = "";
	timeToNextFloor = Elevator::INVALID_VALUE;
	moveFloorTimer = Elevator::INVALID_VALUE;
	stopTimer = Elevator::INVALID_VALUE;
	setDestPassengerIndex(Elevator::INVALID_VALUE);
} 

Elevator::~Elevator() {}

// 加入索引为index的乘客
/*
	void Elevator::addpassengertoindex()
		printpassengeraction()
		passengersids.add <- id
		setpassengerstatus()
		if (elevator has no dest passenger)
			set this as the dest passenger
			check
		if (size > MAX_NUM) overload
		if (size == MAX_NUM but dest passenger is not on board)
			throw exception
*/
void Elevator::addPassengerToIndex(const int index) {
	printPassengerAction("搭乘", index);
	passengerIds.push_back(index);
	// 设置乘客的状态
	passengerListPtr->setPassengerStatus(
		this->getTime(), index, Passenger::RIDING
	);
	// 如果电梯里面没有目的地乘客，那么就把这个乘客设置为目的地乘客
	// 如果整个passengerlist的大小不等于1，那么表示有异常，因为这是我们的第一个乘客。
	if (destPassengerIndex == Elevator::INVALID_VALUE) {
		setDestPassengerIndex(index);
		if (passengerIds.size() != 1) {
			throw exception("这应该是我们的第一个乘客。");
		}
	}
	// 打印乘客的ID信息
	printPassengerID();
	// 超过了电梯的最大承载人数
	if (passengerIds.size() > Elevator::MAX_PASSENGERS) {
		throw exception("超载了！");
	}
	// 电梯满人了，但是目的地乘客却不在电梯中
	if (passengerIds.size() == Elevator::MAX_PASSENGERS &&
		!isDestPassengerOnBoard()) {
		throw exception("电梯满人, 但是目标乘客不在电梯中。");
	}
	return;
}

/*
	void elevator::removepassengeroutindex()
		printpassenger()
		remove()
		setpassengerstatus()
		if (this is the dest passenger)
			find a new dest passenger
		showID()
		if (elevator has no passenger)
			elevator.state <- stoped_no_passenger
*/
void Elevator::removePassengerOutIndex(const int index) {
	printPassengerAction(" 放下", index);
	passengerIds.remove(index);
	// 乘客已经到达了目的地，因此乘客应该状态设置为完成
	this->passengerListPtr->setPassengerStatus(
		this->getTime(), index, Passenger::COMPLETED
	);
	// 如果这是我们的目的地乘客，那么此时应该确定下一位目的地乘客
	if (index == destPassengerIndex) {
		setDestPassengerIndex(Elevator::INVALID_VALUE);
		determineNextDestinationPassenger();
	}
	printPassengerID();
	// 如果此时电梯没有乘客了，那么此时电梯处于空的状态
	if (passengerIds.empty())
	{
		setMovestate(Elevator::STOPPED_NO_PASSENGERS);
	}
	return;
}

/*
	void elevator::checkdropoffpassenger()
		for member in passengers:
			if (endfloor == current floor)
				droplist.add <- member.id
		if (droplist is not empty)
			elevator is stopping
*/
void Elevator::checkDropOffPassengers(const bool moveUp) {
	// 声明两个变量并初始化
	int curEndFloornumber = Elevator::INVALID_VALUE;
	int curId = Elevator::INVALID_VALUE;
	// 声明关于list<int>的迭代器，这是类似于指针的玩意，用于操作STL的各类模板
	list<int>::const_iterator iter;
	if (passengerIds.size() > 0) {
		for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++) {
			// 获取索引为*iter的member的目标楼层号和ID
			curEndFloornumber = this->passengerListPtr->getPassengerEndfloorNumber(*iter);
			curId = this->passengerListPtr->getPassengerID(*iter);
			// 如果当前的楼层和乘客的目标楼层是一样的话，就把它们的ID加入到下电梯的列表中
			if (curEndFloornumber == currFloor.getFloornumber()) {
				dropOffList.push_back(curId);
			}
		}
	}
	// 如果有人要下电梯，那么电梯就要从运动中变为静止
	if (!dropOffList.empty()) {
		this->setMoveStateToStopping(moveUp);
	}
	return;
}

/*
	void elevator::checkfornewdestpassenger()
		flag <- false
		if (elevator has no dest passenger)
			flag <- true
		status <- getmatchpassenger
		if (getnextdestpassenger is success)
			if (flag and the index is not invalid value)
				flag the passenger
				set the passenger as dest passenger
*/
void Elevator::checkForNewDestinationPassenger() {
	bool flag = false;
	int nextPassengerIndex = Elevator::INVALID_VALUE;
	Passenger::Status status = Passenger::NOT_SET;
	// 如果没有的destpassenger的话那么flag就为真
	if (destPassengerIndex == Elevator::INVALID_VALUE) {
		flag = true;
	}
	// 得到下一个符合条件的应该具有的状态
	status = getMatchingPassengerStatus();
	// 如果能找到下一个dest passenger并且flag为真那么就将其标记，并且设置为目的地乘客
	if (this->passengerListPtr->getNextPassengerIndex(
		this->getTime(), currFloor, destFloor,
		status, nextPassengerIndex
	)) {
		if (flag && nextPassengerIndex != Elevator::INVALID_VALUE) {
			setDestPassengerIndex(nextPassengerIndex);
			this->passengerListPtr->setPassengerStatus(
				this->getTime(), nextPassengerIndex,
				Passenger::QUEUED_WAITING_FLAGGED
				);
		}
	}
	return;
}

/*
	void elevator::checkpickuppassengers()
		status <- invalid
		if (elevator is moving up)
			status <- up
		else status <- down
		getqueuepassenegeratfloor()
		if (pickup list is not empty)
			elevator need to stop to pick up them
*/
void Elevator::checkPickupPassengers(const bool moveUp) {
	Passenger::Status status = Passenger::NOT_SET;
	// 如果电梯的状态时上升的，那么电梯就要搭载状态为QUEUEED_WAITING_UP的人
	// 否则就搭载状态为QUEUED_WAITING_DOWN的人
	if (moveUp) {
		status = Passenger::QUEUED_WAITING_UP;
	}
	else {
		status = Passenger::QUEUED_WAITING_DOWN;
	}
	// 让符合条件的乘客进电梯
	this->passengerListPtr->getQueuedPassengerAtFloor(
		this->getTime(),
		currFloor,
		destPassengerIndex,
		status,
		pickUpList
	);
	// 如果电梯的需要搭载的列表不为空，那么我们就需要搭载乘客，电梯要变为静止。
	if (!pickUpList.empty()) {
		setMoveStateToStopping(moveUp);
	}
	return;
}

/*
	void elevator::determinenextdestinationpassenger()
		determine the elevator is up or down
		if (up)
			keepup <- false
			for member in passengers:
				if member endfloor > current floor:
					keepup <- true
			if(keepup)
				find the max endfloor
			else
				find the min endfloor
		else
			keepdown <- false
			for member in passengers:
				if member endfloor < current floor:
					keepdown <- true
			if (keepdown)
				find the min endfloor
			else
				find the max endfloor
*/
void Elevator::determineNextDestinationPassenger() {
	list<int>::const_iterator iter;
	bool up = false;
	// 决定电梯的状态是向上还是向下
	switch (this->moveState)
	{
		case STOPPED_GOING_UP:
		case STOPPING_GOING_UP:
		case MOVING_UP:
		{
			up = true;
			break;
		}
		case STOPPED_GOING_DOWN:
		case STOPPING_GOING_DOWN:
		case MOVING_DOWN:
		{
			up = false;
			break;
		}
		default:
		{
			throw exception("存在不合法的运动状态！");
			break;
		}
	}// 处理向上的情况
	if (up) {
		bool keepUp = false;
		// 如果有乘客的目的楼层有大于现在的楼层，那么继续上升
		for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++) {
			if (this->passengerListPtr->getPassengerEndfloorNumber(*iter) > 
				currFloor.getFloornumber()) {
				keepUp = true;
				break;
			}
		}
		if (keepUp) {// 找到最大的endfloor
			setDestPassengerIndex(findMaxEndFloor());
		}
		else {// 如果不继续向上，找到最小的endfloor，开始向下
			setDestPassengerIndex(findMinEndFloor());
		}
	}
	else {
		bool keepdown = false;
		// 如果有乘客的目的楼层有小于现在的楼层，那么继续下降
		for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++) {
			if (this->passengerListPtr->getPassengerEndfloorNumber(*iter) < 
				currFloor.getFloornumber()) {
				keepdown = true;
				break;
			}
		}
		if (keepdown) {// 找到最小的endfloor
			setDestPassengerIndex(findMinEndFloor());
		}
		else {// 如果不继续向下，那么找到最大的maxfloor，开始向上
			setDestPassengerIndex(findMaxEndFloor());
		}
	}
	return;
}

/*
	int elevator::determinmaxfloor()
		firsttime <- true
		for member in passengers:
			if (endfloor > current floor or firstmember)
				maxfloor <- endfloor
				firsttime <- false
*/
int Elevator::findMaxEndFloor() const {
	list<int>::const_iterator iter;
	// 第一遍循环
	bool firstmember = true;
	int curID = Elevator::INVALID_VALUE;
	int curmaxfloor = Elevator::INVALID_VALUE;
	// 遍历所有的passenger成员
	for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++) {
		// 如果有乘客的目标楼层大于当前的最大楼层，更新最大楼层，更新乘客的ID
		if (this->passengerListPtr->getPassengerEndfloorNumber(*iter) > 
			curmaxfloor || firstmember) {
			curmaxfloor = this->passengerListPtr->getPassengerEndfloorNumber(*iter);
			curID = this->passengerListPtr->getPassengerID(*iter);
			firstmember = false;
		}
	}
	return curID;
}

/*
	int elevator::determinminfloor()
		firsttime <- true
		for member in passengers:
			if (endfloor < current floor)
				minfloor <- endfloor
				firsttime <- false
*/
int Elevator::findMinEndFloor() const {
	list<int>::const_iterator iter;
	// 第一遍循环
	bool firstmember = true;
	int curID = Elevator::INVALID_VALUE;
	int curminfloor = Elevator::INVALID_VALUE;
	// 遍历所有的passenger成员
	for (iter = this->passengerIds.begin(); iter != this->passengerIds.end(); iter++) {
		// 如果有乘客的目标楼层小于当前的楼层，更新最小楼层，更新乘客的ID
		if (this->passengerListPtr->getPassengerEndfloorNumber(*iter) <
			curminfloor || firstmember) {
			curminfloor = this->passengerListPtr->getPassengerEndfloorNumber(*iter);
			curID = this->passengerListPtr->getPassengerID(*iter);
			firstmember = false;
		}
	}
	return curID;
}

// 根据相应的状态执行相应的动作
void Elevator::PerformNextMove() {
	switch (this->moveState)
	{
		case STOPPED_NO_PASSENGERS:
		{
			this->checkForNewDestinationPassenger();
			this->moveToDestFloor();
			break;
		}
		case STOPPED_GOING_DOWN:
		case STOPPED_GOING_UP:
		{
			ElevatorStopped();
			break;
		}
		case STOPPING_GOING_DOWN:
		case STOPPING_GOING_UP:
		{
			ElevatorStopping();
			break;
		}
		case MOVING_DOWN:
		{
			bool moveup = false;
			ElevatorMove(moveup);
			break;
		}
		case MOVING_UP:
		{
			bool moveup = true;
			ElevatorMove(moveup);
			break;
		}
		default:
		{
			throw exception("不合法的电梯运行状态！");
			break;
		}
	}
	return;
}

/*
	void elevator::dropoffpassengers()
		size <- dropofflist.size()
		for member in dropofflist:
			remove member
		clear droplist
*/
void Elevator::dropOffPassengers() {
	int numofpassengers = dropOffList.size();
	for (int curpassenger = 0; curpassenger < numofpassengers; curpassenger++) {
		removePassengerOutIndex(dropOffList[curpassenger]);
	}
	dropOffList.clear();
	return;
}
/*
	passenger::status getmatching()
		status <- not_set
		if (elevator is stoped_no_passengers)
			status <- not_set
		else if (elevator is moving down)
			status <- queue_waiting_down
		else if (elevator is moving up)
			status <- queue_waiting_up
		else
			if (dest passenger is aboard)
				if (current floor > dest end floor)
					status <- queue_waiting_down
				else
					status <- queue_waiting_up
			else
				if (current floor > dest start floor)
					status <- queue_waiting_down
				else
					status <- queue_waiting_up
*/
Passenger::Status Elevator::getMatchingPassengerStatus() {
	Passenger::Status status = Passenger::NOT_SET;
	switch (moveState)
	{
		// 如果电梯是STOPED_NO_PASSENGERS,那么电梯可以搭载任何人
		case STOPPED_NO_PASSENGERS:
		{
			status = Passenger::NOT_SET;
			break;
		}// 如果电梯是停止的或者是正要停止的状态，就要讨论：
		case STOPPED_GOING_UP:
		case STOPPED_GOING_DOWN:
		case STOPPING_GOING_UP:
		case STOPPING_GOING_DOWN:
		{
			// 没有目的地乘客,这是不正常的情况
			if (destPassengerIndex == Elevator::INVALID_VALUE) {
				throw exception("电梯没有目的地的乘客！");
			}
			else {
				// 如果目的地乘客在电梯上，那么电梯的状态决定下一个上电梯的状态
				if (isDestPassengerOnBoard()) {
					// 如果电梯所在楼层高度小于目的地楼层，那么电梯会向上走
					// 乘客的状态应该是QUEUD_WAITING_UP
					if (currFloor.getFloornumber() < this->passengerListPtr
						->getPassengerEndfloorNumber(destPassengerIndex))
					{
						status = Passenger::QUEUED_WAITING_UP;
					}
					// 如果电梯所在的楼层高度大于目的楼层，那么电梯会向下走
					// 乘客的状态应该是QUEUED_WAITING_DOWN
					else if (currFloor.getFloornumber() > this->passengerListPtr
						->getPassengerEndfloorNumber(destPassengerIndex))
					{
						status = Passenger::QUEUED_WAITING_DOWN;
					}
					else {
						throw exception("不合法的目标楼层！");
					}
				}// 如果目的地乘客不在电梯上，那么电梯现在应该去接目的乘客
				else {
					// 此时状态就由目的地乘客的等待的楼层决定
					// 如果他所在的楼层大于电梯现在的楼层，那么电梯会向上走去接
					if (currFloor.getFloornumber() < this->passengerListPtr
						->getPassengerStartfloorNumber(this->destPassengerIndex))
					{
						status = Passenger::QUEUED_WAITING_UP;
					}
					// 如果电梯所在的楼层大于他所在的楼层，那么电梯会向下走去接
					else if (currFloor.getFloornumber() > this->passengerListPtr
						->getPassengerStartfloorNumber(destPassengerIndex))
					{
						status = Passenger::QUEUED_WAITING_DOWN;
					}
					else {
						throw exception("不合法的起始楼层！");
					}
				}
			}
			break;
		}
		case MOVING_DOWN:
		{
			// 如果电梯是向上走的，那么状态为QUEUED_WAITITNG_DOWN
			status = Passenger::QUEUED_WAITING_DOWN;
			break;
		}
		case MOVING_UP:
		{
			// 如果电梯是向下走的， 那么状态应该为QUEUED_WAITING_UP
			status = Passenger::QUEUED_WAITING_UP;
			break;
		}
		default:
		{
			throw exception("不合法的电梯运行状态！");
			break;
		}
	}
	return status;
}

/*
	void elevatormove()
		if (elevator arrive the dest)
			if (elevator is stopped)
				state <- stopped_going_up or down
			else
				wait within stoppped time
		else
			wait for dest
			if (catch a floor)
				add or sub current floornumber by speed
				pickup and drop off passenger
*/
void Elevator::ElevatorMove(const bool moveUp) {
	// 如果电梯到达了目的楼层
	if (0 == moveFloorTimer) {
		// 如果电梯已经停留了预定的时间，那么就调整运动状态
		if (0 == stopTimer) {
			if (moveUp) {
				setMovestate(Elevator::STOPPED_GOING_UP);
			}
			else {
				setMovestate(Elevator::STOPPED_GOING_DOWN);
			}
		}// 没停够的话，就停到预定时间
		else {
			stopTimer--;
		}
	}// 没有到达目的楼层，那么每到达一层楼，就更新当前楼的数据
	else {
		moveFloorTimer--;
		if (moveFloorTimer % timeToNextFloor == 0) {
			if (moveUp) {
				currFloor.upFloornumber();
			}
			else {
				currFloor.downFloornumber();
			}
			// 检查要不要搭载乘客或者放下乘客
			checkDropOffPassengers(moveUp);
			checkPickupPassengers(moveUp);
		}
	}
	return;
}

// 电梯停下来，那么此时电梯要放下乘客，搭载乘客然后继续向目的楼层运动
void Elevator::ElevatorStopped() {
	pickUpPassengers();
	dropOffPassengers();
	moveToDestFloor();
}

/*
	void elevator::elevatorstopping()
		stoptime -- 
		if (stoptime == 0)
			setstate <- stoped_going_ up or down
*/
void Elevator::ElevatorStopping() {
	stopTimer--;
	if (stopTimer == 0) {
		if (moveState == Elevator::STOPPING_GOING_DOWN) {
			setMovestate(Elevator::STOPPED_GOING_DOWN);
		}
		else if (moveState == Elevator::STOPPING_GOING_UP) {
			setMovestate(Elevator::STOPPED_GOING_UP);
		}
		else {
			throw exception("不合法的电梯运行状态！");
		}
	}
	return;
}

bool Elevator::isDestPassengerOnBoard() const {
	list<int>::const_iterator iter;
	bool flag = false;
	for (iter = passengerIds.begin(); iter != passengerIds.end(); iter++) {
		if (destPassengerIndex == this->passengerListPtr->
			getPassengerID(*iter))
		{
			flag = true;
			break;
		}
	}
	return flag;
}

/*
	void moveUpDown()
		setstate <- up or down
		movetime <- num * (interval + 1)
		stoptime <- stop_sec
*/
void Elevator::moveDown(const int floornumber) {
	setMovestate(Elevator::MOVING_DOWN);
	moveFloorTimer = (floornumber + 1) * timeToNextFloor;
	stopTimer = Elevator::SEC_STOP;
	return;
}

void Elevator::moveUp(const int floornumber) {
	setMovestate(Elevator::MOVING_UP);
	moveFloorTimer = (floornumber + 1) * timeToNextFloor;
	stopTimer = Elevator::SEC_STOP;
	return;
}

/*
	void movetodest()
		floor <- 1
		if (dest is aboard)
			floor <- dest end floor
		else
			floor <- dest start floor
		if floor > current floor
			moveup
		else
			movedown
*/
void Elevator::moveToDestFloor() {
	if (destPassengerIndex != Elevator::INVALID_VALUE) {
		int destfloornumber = Elevator::INVALID_VALUE;
		// 如果目的乘客在电梯上，我们就直接送乘客去到目的地
		if (isDestPassengerOnBoard()) {
			destfloornumber = this->passengerListPtr->
				getPassengerEndfloorNumber(destPassengerIndex);
		}// 如果乘客不在电梯上，我们就去乘客等待的楼层去接乘客
		else {
			destfloornumber = this->passengerListPtr->
				getPassengerStartfloorNumber(destPassengerIndex);
		}// 如果电梯的所处的楼层大于目标楼层，那么电梯下降
		if (currFloor.getFloornumber() > destfloornumber) {
			moveDown(currFloor.getFloornumber() - destfloornumber);
		}// 如果电梯所处的楼层小于目标楼层，那么电梯上升
		else {
			moveUp(destfloornumber - currFloor.getFloornumber());
		}
	}
	return;
}

/*
	void elevator::pickup()
		size <- pickuplist.size()
		for member in picklist
			if (val == max_num - 1 && dest passenger is not in elevator)
				if (member is dest passenger)
					pickup
			else if (val < max_num)
				pickup
		if (val > max_num)
			overload!
		clear picklist
*/
void Elevator::pickUpPassengers() {
	int numpassengers = pickUpList.size();
	// 如果电梯还剩下一个位置，并且目的地乘客不在电梯上，那么电梯应该让目的地乘客上
	for (int curpassenger = 0; curpassenger < numpassengers; curpassenger++) {
		if (passengerIds.size() == Elevator::MAX_PASSENGERS - 1 &&
			!isDestPassengerOnBoard())
		{
			if (destPassengerIndex == pickUpList[curpassenger]) {
				addPassengerToIndex(destPassengerIndex);
			}
		}
		// 如果电梯还有位置就上电梯
		else if (passengerIds.size() < Elevator::MAX_PASSENGERS) {
			addPassengerToIndex(pickUpList[curpassenger]);
		}
	}// 如果电梯人数大于最大人数，超载
	if (passengerIds.size() > Elevator::MAX_PASSENGERS) {
		throw exception("电梯搭载太多人了！");
	}
	pickUpList.clear();
	return;
}

// 打印状态
void Elevator::printStatus() const {
	ofstream fout;
	fout.open("D:\\homeworks\\homewoks_college\\cpp\\liu_shu_lin_last_elevator\\lastest_version_elevator\\filelog\\elevator_log.txt", ios::out);
	switch (this->moveState)
	{
		case STOPPED_GOING_DOWN:
		{
			fout << "STOPPED_GOING_DOWN";
			cout << "STOPPED_GOING_DOWN";
			break;
		}
		case STOPPED_GOING_UP:
		{
			fout << "STOPPED_GOING_UP";
			cout << "STOPPED_GOING_UP";
			break;
		}
		case STOPPING_GOING_DOWN:
		{
			fout << "STOPPING_GOING_DOWN";
			cout << "STOPPING_GOING_DOWN";
			break;
		}
		case STOPPING_GOING_UP:
		{
			fout << "STOPPING_GOING_UP";
			cout << "STOPPING_GOING_UP";
			break;
		}
		case MOVING_DOWN:
		{
			fout << "MOVING_DOWN";
			cout << "MOVING_DOWN";
			break;
		}
		case MOVING_UP:
		{
			fout << "MOVING_UP";
			cout << "MOVING_UP";
			break;
		}
		case STOPPED_NO_PASSENGERS:
		{
			fout << "STOPPED_NO_PASSENGERS";
			cout << "STOPPED_NO_PASSENGERS";
			break;
		}
		case INVALID_VALUE:
		{
			fout << "INVALID_VALUE";
			cout << "INVALID_VALUE";
			break;
		}
		default:
		{
			throw exception("不合法的电梯运行状态！");
			break;
		}
	}
	fout.close();
	return;
}

void Elevator::printPassengerAction(const string& action, const int index) const {
	ofstream fout;
	// 输出文件路径
	fout.open("D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\log.txt", ios::app);
	fout << name;
	fout << action;
	fout << " 乘客:" << index;
	fout << " 楼层:" << currFloor.getFloornumber();
	fout << " 时间:" << this->getTime() << " 秒";
	fout << endl;
	fout.close();
	cout << name;
	cout << action;
	cout << " 乘客:" << index + 1;
	cout << " 楼层:" << currFloor.getFloornumber();
	cout << " 时间:" << this->getTime() << " 秒";
	cout << endl;
	return;
}

void Elevator::printPassengerID() const {
	ofstream fout;
	fout.open("D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\_log.txt", ios::app);
	fout << "   " << this->name << " 乘客: [ ";
	cout << "   " << this->name << " 乘客: [ ";
	list<int>::const_iterator iter;
	for (iter = this->passengerIds.begin(); iter != this->passengerIds.end(); iter++) {
		fout << *iter + 1;
		cout << *iter + 1;
		if (*iter == this->destPassengerIndex) {
			fout << "*";
			cout << "*";
		}
		cout << " ";
		fout << " ";
	}
	cout << "]" << endl;
	fout << "]" << endl;
	fout.close();
	return;
}

// 设置电梯的状态，从运行转换为停止状态
void Elevator::setMoveStateToStopping(const bool moveUp) {
	if (moveUp) {
		setMovestate(Elevator::STOPPING_GOING_UP);
	}
	else {
		setMovestate(Elevator::STOPPING_GOING_DOWN);
	}
	return;
}

