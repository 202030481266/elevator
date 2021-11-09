#pragma once
#ifndef elevator_h
#define elevator_h
/*==================================================================================
    (1)核心类：elevator，是电梯的类
    (2)功能：实现模拟的电梯操作，根据passengers的数据来进行上下，暂停等操作。
    (3)笔记：功能非常复杂，重构次数很多。
    (4)依赖：passengerlist, passenger, floor, simulationtime
====================================================================================*/
#include "passenger.h"
#include "passengerlist.h"
#include "simulationtime.h"
#include <list>

using namespace std;
class Elevator
{
public:
    // 构造函数和析构函数
	Elevator();
    virtual ~Elevator();

    // 运动状态的描述
    enum MoveState
    {
        INVALID_MOVE_STATE = -1,// 不合法的运动状态
        STOPPED_NO_PASSENGERS,// 已经停止，但是电梯里面没有乘客了
        STOPPED_GOING_UP,// 在上升的过程中停止
        STOPPED_GOING_DOWN,// 在下降的过程中停止
        STOPPING_GOING_UP,// 在上升的过程中即将停止
        STOPPING_GOING_DOWN,// 在下降的过程中即将停止（因为电梯停下来需要时间）
        MOVING_UP,// 电梯处于上升的状态中
        MOVING_DOWN// 电梯处于下降的状态中
    };
    // 加入索引为index的乘客
    void addPassengerToIndex(const int index);

    // 移除索引为index的乘客
    void removePassengerOutIndex(const int index);

    // 检查是否有乘客下电梯
    void checkDropOffPassengers(const bool movedUp);

    // 寻找新的目的地乘客
    void checkForNewDestinationPassenger();

    // 检查是否需要搭载乘客
    void checkPickupPassengers(const bool movedUp);

    // 决定电梯是向上还是向下的问题
    void determineNextDestinationPassenger();

    // 寻找最大目的地楼层
    int findMaxEndFloor() const;

    // 寻找最小目的地楼层
    int findMinEndFloor() const;

    // 放下乘客
    void dropOffPassengers();

    // 搭载乘客
    void pickUpPassengers();

    // 决定并执行下一个动作依据电梯的运动状态的描述
    void PerformNextMove();

    // 决定匹配符合条件的状态
    Passenger::Status getMatchingPassengerStatus();

    // 获取电梯的名字
    inline void getName(string& name) const;

    // 获取时间戳
    inline int getTime() const;

    // 电梯的运行函数
    void ElevatorMove(const bool movedUp);
    void ElevatorStopped();
    void ElevatorStopping();
    void moveDown(const int floornumber);
    void moveUp(const int floornumber);
    void moveToDestFloor();

    // 判断目的地乘客是否在电梯上面
    bool isDestPassengerOnBoard() const;

    // 打印电梯的状态，乘客的状态，乘客的ID
    void printStatus() const;
    void printPassengerAction(const string& action, const int index) const;
    void printPassengerID() const;

    // 设置电梯的目的地乘客，运动状态，运行速度
    inline void setDestPassengerIndex(const int index);
    inline void setMovestate(const Elevator::MoveState state);
    inline void setName(const string& name);
    inline void setTimeToNextFloor(const int timeToNextFloor);
    void setMoveStateToStopping(const bool movedUp);
private:
    static const int INVALID_VALUE = -1;  
    // 最大的乘客数量
    static const int MAX_PASSENGERS = 8;  
    // 电梯停滞的时间
    static const int SEC_STOP = 2;
    Floor             currFloor;           
    Floor             destFloor;           
    vector<int>       pickUpList;
    vector<int>       dropOffList;  
    int               destPassengerIndex;
    int               moveFloorTimer; 
    int               stopTimer;
    int               timeToNextFloor;
    MoveState         moveState;           
    string            name;                
    list<int>         passengerIds;    // 使用list是因为list非常高效，删除添加操作都很快    
    PassengerList* passengerListPtr;    
    SimulationTime* simulationTimePtr;   
};

inline void Elevator::getName(string& name) const {
    name = this->name;
    return;
}

inline int Elevator::getTime() const {
    return this->simulationTimePtr->getTime();
}

inline void Elevator::setDestPassengerIndex(const int index) {
    this->destPassengerIndex = index;
    return;
}

inline void Elevator::setMovestate(const Elevator::MoveState state) {
    this->moveState = state;
    return;
}

inline void Elevator::setName(const string& name) {
    this->name = name;
    return;
}

inline void Elevator::setTimeToNextFloor(const int timeToNextFloor) {
    this->timeToNextFloor = timeToNextFloor;
    return;
}

#endif // !elevator_h
