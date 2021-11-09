#include "stdafx.h"
#include "passengerlist.h"

// 初始化
PassengerList::PassengerList() {}
PassengerList::~PassengerList() {}
PassengerList* PassengerList::instancePtr = 0;

/*
	bool passengerlist::getNextPassengerIndex
		valid <- false
		for member in passenglist:
			if (elevator is empty or status matched)
				if (current time <= start time)
					if (currentfloor <= startfloor <= endfloor or elevator is empty)
						getpassengerindex;
						valid <- true;
					break;
*/
bool PassengerList::getNextPassengerIndex(
	const int time,
	const Floor& currentfloor,
	const Floor& endfloor,
	const Passenger::Status status,
	int& passengerIndex
) 
{
	// 检查passengerlist中所有的乘客中有没有符合条件的乘客
	bool valid = false;
	// numberpassengers是passengerlist的大小
	int numberPassengers = getPassengerListSize();
	// 遍历所有的passengerlist的所有成员
	for (int numberindex = 0; numberindex < numberPassengers; numberindex++) {
		Passenger curPassenger = Passengerlist[numberindex];
		// 如果该成员是已经被标记的，状态不合法，或者是已经在电梯上面的，已经完成的，就continue
		if (curPassenger.getStatus() == Passenger::NOT_SET ||
			curPassenger.getStatus() == Passenger::QUEUED_WAITING_FLAGGED ||
			curPassenger.getStatus() == Passenger::RIDING ||
			curPassenger.getStatus() == Passenger::COMPLETED)
		{
			continue;
		}
		if ((status == curPassenger.getStatus() || status == Passenger::NOT_SET)
			&& curPassenger.getStatus() != Passenger::QUEUED_WAITING_FLAGGED)
		{// 这里的QUEUED_WAITING_FLAGGED用来判断这个乘客有没有被其他的电梯标记过了
			// 这里的时间不会倒流，所以乘客的开始等待时间一定要比模拟进行的时间更早。
			if (time >= curPassenger.getStartTime())
			{
				Floor curStartFloor;
				// 获取乘客的开始等待的楼层
				curPassenger.getStartFloor(curStartFloor);
				// 乘客的等待的楼层必须在现在电梯的curfloor和endfloor之间，否则电梯无法接到人
				// 还有另外一种情况：电梯是空的。
				if (currentfloor.getFloornumber() <= curStartFloor.getFloornumber() &&
					endfloor.getFloornumber() >= curStartFloor.getFloornumber() ||
					status == Passenger::NOT_SET)
				{
					// 找到一位就退出。
					passengerIndex = curPassenger.getID();
					valid = true;
					break;
				}
			}
		}
	}
	return valid;
}

/*
	bool passengerlist::getqueuedpassengeratfloor()
		valid <- false
		for member in passengerlist:
			if (status matched or is the dest passenger)
				if (current time >= start time and start floor == current floor)
					nextpassengerindex.add(current passenger)
					valid <- true
*/
bool PassengerList::getQueuedPassengerAtFloor(
	const int time,
	const Floor& currentfloor,
	const int destPassengerIndex,
	const Passenger::Status status,
	vector<int>& nextPassengerIndex
)
{
	// 判断有没有找到符合条件的passenger
	bool valid = false;
	int numberPassengers = this->getPassengerListSize();
	// 遍历整个passengerlist
	for (int numberindex = 0; numberindex < numberPassengers; numberindex++) {
	    Passenger curPassenger = this->Passengerlist[numberindex];
		// 不考虑已经到达目的地的乘客
		if (curPassenger.getStatus() == Passenger::COMPLETED ||
			curPassenger.getStatus() == Passenger::RIDING)
			continue;
		// 如果和电梯的状态一致或者这是电梯搭载的目的地乘客
		if (status == curPassenger.getStatus() || destPassengerIndex == numberindex)
		{
			// 时间不会倒流，所以这里的开始时间必须要比模拟进行的时间要长
			if (time >= curPassenger.getStartTime())
			{
				Floor curStartFloor;
				curPassenger.getStartFloor(curStartFloor);
				// 如果这里的乘客的开始等待的楼层就是当前的楼层
				if (curStartFloor.getFloornumber() == currentfloor.getFloornumber())
				{
					nextPassengerIndex.push_back(curPassenger.getID());
					valid = true;
				}
			}
		}
	}
	return valid;
}

// 重置状态和上电梯，下电梯的时间
void PassengerList::resetPassengerStatusAndBoardExitTime(const int index) {
	this->Passengerlist[index].resetBoardTime();
	this->Passengerlist[index].resetExitTime();
	this->Passengerlist[index].resetStatus();
}
