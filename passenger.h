#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "floor.h"
using namespace std;
/*=======================================================================*/
//  passenger类依赖于floor类
/* 主要功能：
*           1.使用枚举类型表示乘客的状态。
*           2.获得乘客的各类信息数据。
*           3.对乘客的各类信息数据进行设置修改。
*           4.打印乘客的信息。
*/
/*=======================================================================*/
class Passenger 
{
public:
	Passenger();
    // 只有当一个类被用来作为基类的时候，才会把析构函数写成虚函数
    // 可以避免内存泄漏
    virtual ~Passenger();
    enum Status
    {
        NOT_SET = -1,// 相当于一个空值
        QUEUED_WAITING_FLAGGED,// 已经被标记
        QUEUED_WAITING_UP,// 等待上升
        QUEUED_WAITING_DOWN,// 等待下降
        RIDING,// 正在搭乘中
        COMPLETED // 已经到达了目的楼层
    };
    static const int INIT_TO_INVALID = -1;
    // 表示开始的初始值

    inline int getStartTime() const;
    // 得到乘客开始等待的时间戳
    inline int getboardElevatorTime() const;
    // 得到乘客登上电梯的时间戳
    inline int getExitElevatorTime() const;
    // 得到乘客离开电梯时间戳

    inline void getEndFloor(Floor& endfloor) const;
    // 得到乘客的最后到达的楼层（这里的没有返回值，这里采用引用的方法来进行获取）
    inline int getEndFloornumber() const;
    // 得到乘客的最后到达的楼层的楼层号码
    inline void getStartFloor(Floor& startfloor) const;
    // 得到乘客的开始的楼层
    inline int getStartFloornumber() const;
    // 得到乘客开始的楼层号码

    inline int getID() const;
    // 得到乘客的ID
    inline Passenger::Status getStatus() const;
    // 得到乘客的状态

    inline void resetBoardTime();
    // 重置乘客的登陆电梯的时间，重置为INIT_TO_VALUE
    inline void resetExitTime();
    // 重置乘客的离开电梯的时间， 重置为INIT_TO_VALUE
    inline void resetStatus();
    // 重置乘客的状态， 重置为NOT_SET

    inline void setID(const int id);
    // 设置乘客的ID
    inline void setStartTime(const int startTime);
    // 设置乘客的开始时间
    inline void setStartFloor(const Floor& startfloor);
    // 设置乘客的开始楼层
    inline void setEndFloor(const Floor& endFloor);
    // 设置乘客最后到达的楼层
    void setStatus(const Passenger::Status status, int time);
    // 设置乘客的状态，这里需要根据时间，状态来同时调整乘客的上电梯和下电梯的时间
    void printStatus() const;
    // 打印输出乘客的状态信息
private:
    inline void setBoardElevatorTime(const int boardelevatortime);
    inline void setExitElevatorTime(const int exitelevatortime);
    // 设置乘客的上电梯和下电梯的时间，但实际上好像是多余的。
    int id;
    int startTime;
    Floor startFloor;
    Floor endFloor;
    Status status;
    int boardElevatorTime;
    int exitElevatorTime;
};

inline int Passenger::getboardElevatorTime() const {
    return boardElevatorTime;
}

inline void Passenger::getEndFloor(Floor& endfloor) const {
    endfloor = this->endFloor;
    return;
}

inline int Passenger::getEndFloornumber() const {
    return endFloor.getFloornumber();// endFloor是Floor对象，要使用getfloornumber()
}

inline int Passenger::getExitElevatorTime() const {
    return exitElevatorTime;
}

inline int Passenger::getID() const {
    return id;
}

inline int Passenger::getStartTime() const {
    return startTime;
}

inline void Passenger::getStartFloor(Floor& startfloor) const {
    startfloor = this->startFloor;
    return;
}

inline int Passenger::getStartFloornumber() const {
    return this->startFloor.getFloornumber();
}

inline Passenger::Status Passenger::getStatus() const {
    return this->status;
}
// 回归原来最初始的状态
inline void Passenger::resetBoardTime() {
    this->boardElevatorTime = Passenger::INIT_TO_INVALID;
    return;
}

inline void Passenger::resetExitTime() {
    this->exitElevatorTime = Passenger::INIT_TO_INVALID;
    return;
}

inline void Passenger::resetStatus() {
    this->status = Passenger::NOT_SET;
    return;
}
// 由于变量名类似，这里使用this指针加以区分
inline void Passenger::setEndFloor(const Floor& endFloor) {
    this->endFloor = endFloor;
    return;
}

inline void Passenger::setStartFloor(const Floor& startFloor) {
    this->startFloor = startFloor;
    return;
}

inline void Passenger::setBoardElevatorTime(const int boardElevatorTime) {
    this->boardElevatorTime = boardElevatorTime;
    return;
}

inline void Passenger::setExitElevatorTime(const int exitElevatorTime) {
    this->exitElevatorTime = exitElevatorTime;
    return;
}

inline void Passenger::setID(const int id) {
    this->id = id;
    return;
}

inline void Passenger::setStartTime(const int starttime) {
    this->startTime = starttime;
    return;
}