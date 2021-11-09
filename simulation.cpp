#include "stdafx.h"
#include "simulation.h"
#include "setting.h"
#include <iostream>
#include <fstream>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
    // 使用c++的异常捕获机制
    try
    {   
        Simulation simulation;  
        int elevatornumber = 0;
        int fastesttime = 0;
        cout << "请输入电梯个数： \n";
        cin >> elevatornumber;
        cout << "请输入电梯的最快速度：\n";
        cin >> fastesttime;
        simulation.runDefaultSimulation(fastesttime, elevatornumber);
    }
    catch (const bad_alloc& e)// 内存空间异常
    {
        cout << e.what() << endl;
        cout << "Caught bad_alloc" << endl;
        cout << "Terminating program" << endl;
    }
    catch (const out_of_range& e)// 越界
    {
        cout << e.what() << endl;
        cout << "Caught out_of_range" << endl;
        cout << "Terminating program" << endl;
    }
    catch (const exception& e)// 不是以上两种的异常
    {
        cout << e.what() << endl;
        cout << "Caught exception" << endl;
        cout << "Terminating program" << endl;
    }
    cout << "End!" << endl;
    // 不让程序自己自动结束
    char pausep = ' '; 
    cin >> pausep;
    return 0;
}

// 构造函数
Simulation::Simulation() {
    // 初始化数据
    elevatordata = "";
    elevators.resize(Simulation::NUM_ELEVATORS);
    this->simulationtimeptr = SimulationTime::getInstance();
    this->passengerlistptr = PassengerList::getInstance();
}

Simulation::~Simulation() {}

// 将passenger实例的信息更新全，然后添加到列表中
void Simulation::addPassenger(const int time, const Floor& startfloor, const Floor& endfloor) {
    Passenger passenger;
    passenger.setID(this->passengerlistptr->getPassengerListSize());
    passenger.setStartTime(time);
    passenger.setStartFloor(startfloor);
    passenger.setEndFloor(endfloor);
    passenger.setStatus(Passenger::NOT_SET, time);
    this->passengerlistptr->addPassenger(passenger);
    return;
}

/*
    bool check()
        flag <- true
        for member in passengers:
            if member status != completed
                flag <- false
        return flag
*/
bool Simulation::checkPassengerAreCP() const {
    int numberpassengers = this->passengerlistptr->getPassengerListSize();
    bool flag = true;
    // 检查是否所有的乘客的状态都是completed
    for (int index = 0; index < numberpassengers; index++) {
        /*for (int j = 0; j < numberpassengers; j++)
            cout << this->passengerlistptr->getPassengerStatus(index) << " ";
        puts("");
        Sleep(3000);*/
        // 如果有乘客的状态不是，那么可以立即退出
        if (this->passengerlistptr->getPassengerStatus(index) != Passenger::COMPLETED)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

// 计算时间的函数
void Simulation::calTravelTimes() {
    double avwaitTime = 0;// 平均等待时间
    double avtravelTime = 0;// 平均坐电梯的时间
    int sumOfwaitTime = 0;// 等待时间的和
    int sumOftravelTime = 0;// 坐电梯时间的和
    int curBoardElevatorTime = 0; // 当前passenger的进入电梯的时间
    int curExitElevatorTime = 0;  // 当前passenger的离开电梯的时间
    int curStartTime = 0;  // 当前passenger的开始等待的时间
    int curTravelTime = 0; // 当前passenger的坐电梯的时间
    int curWaitTime = 0;  // 当前passenger的等待时间
    int numPassengers = 0;  // 当前passenger列表的大小
    
    int numpassengers = this->passengerlistptr->getPassengerListSize();
    // 遍历所有的乘客并且计算所有的乘客
    for (int index = 0; index < numpassengers; index++) {
        curStartTime = this->passengerlistptr->getPassengerStartTime(index);
        curBoardElevatorTime = this->passengerlistptr->getPassengerBoardElevatorTime(index);
        curExitElevatorTime = this->passengerlistptr->getPassengerExitElevatorTime(index);
        // 计算时间
        curWaitTime = curBoardElevatorTime - curStartTime;
        curTravelTime = curExitElevatorTime - curBoardElevatorTime;
        sumOftravelTime += curTravelTime;
        sumOfwaitTime += curWaitTime;
    }
    avwaitTime = (double)(sumOfwaitTime) / numpassengers;
    avtravelTime = (double)(sumOftravelTime) / numpassengers;
    waittimes.push_back(avwaitTime);
    traveltimes.push_back(avtravelTime);
    return;
}

// 模拟运行时间加一，并且把现在开始等待的乘客加入到队列中
void Simulation::addSimulationTime() {
    this->simulationtimeptr->incrementTime();
    queuePassenger();
    return;
}

// 处理数据文件的函数
void Simulation::loadData() {
    string curline = "";
    int startTime = 0;
    ifstream curfile(this->elevatordata.c_str(), ios::in);
    if (curfile) {
        getline(curfile, curline);
        while (!curfile.eof()) {
            getline(curfile, curline);
            if (curline != "") {
                Floor startfloor;
                Floor endfloor;
                this->parseLine(
                    curline,
                    startTime,
                    startfloor,
                    endfloor
                );
                this->addPassenger(startTime, startfloor, endfloor);
            }
        }
    }
    else {
        throw exception("文件加载失败！");
    }
    return;
}

// 打印函数
void Simulation::outputTimes() {
    ofstream fout;
    fout.open("D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\log.txt",ios::app);
    int len = this->waittimes.size();
    if (len != this->traveltimes.size()) {
        throw exception("等待时间和坐电梯的时间不匹配！");
    }
    for (int index = 0; index < len; index++) {
        cout << endl << "-------------------------------------------------------" << endl;
        printf("第%d次运行的结果：\n", index + 1);
        cout << "乘客的平均等待时间：";
        cout << this->waittimes[index] << "secs" << endl;
        cout << "乘客的平均搭乘时间：";
        cout << this->traveltimes[index] << "secs" << endl;
        cout << endl << "-------------------------------------------------------" << endl;
        // 文件输出
        fout << endl << "-------------------------------------------------------" << endl;
        fout << "第" << index + 1 << "次运行的结果：\n";
        fout << "乘客的平均等待时间：";
        fout << this->waittimes[index] << "secs" << endl;
        fout << "乘客的平均搭乘时间：";
        fout << this->traveltimes[index] << "secs" << endl;
        fout << endl << "-------------------------------------------------------" << endl;
    }
    fout.close();
    return;
}

// 使用标准库的string模板处理字符串
void Simulation::parseLine (
    const string& curline,
    int& startTime,
    Floor& startfloor,
    Floor& endfloor
) const {
    string endfloorstr;
    string startfloorstr;
    string timestr;
    int firstpos, secondpos;
    firstpos = curline.find(',');
    secondpos = curline.find(',', firstpos + 1);
    timestr = curline.substr(0, firstpos);
    startTime = atoi(timestr.c_str());
    startfloorstr = curline.substr(firstpos + 1, secondpos - firstpos - 1);
    startfloor.setFloornumber(atoi(startfloorstr.c_str()));
    endfloorstr = curline.substr(secondpos + 1);
    endfloor.setFloornumber(atoi(endfloorstr.c_str()));
    return;
}


void Simulation::queuePassenger() {
    int startfloornum, endfloornum;
    int numpassengers = this->passengerlistptr->getPassengerListSize();
    int time = this->getTime();
    for (int index = 0; index < numpassengers; index++) {
        // 如果和当前时间相等的话，就把当前的乘客加入到电梯列表中
		if (this->passengerlistptr->getPassengerStartTime(index) == time) {
			startfloornum = this->passengerlistptr->getPassengerStartfloorNumber(index);
			endfloornum = this->passengerlistptr->getPassengerEndfloorNumber(index);
			// 要上还是要下
            if (startfloornum < endfloornum) {
				this->passengerlistptr->setPassengerStatus(
					time, index, Passenger::QUEUED_WAITING_UP
				);
			}
			else {
				this->passengerlistptr->setPassengerStatus(
					time, index, Passenger::QUEUED_WAITING_DOWN
				);
			}
		}
    }
    return;
}

void Simulation::resetSimulation() {
    int numpassengers = this->passengerlistptr->getPassengerListSize();
    this->simulationtimeptr->setTime(0);
    for (int index = 0; index < numpassengers; index++) {
        this->passengerlistptr->resetPassengerStatusAndBoardExitTime(index);
    }
}

void Simulation::runDefaultSimulation(int fastest, int number) {
    static const int SEC_NEXT_FLOOR = 10;
    static const int SEC_NEXT_FLOOR_FAST = 2;
    cout << "运行开始..." << endl;
    // 设置数据文件的路径
    // D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\elevators.csv
    // D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\data.txt
    this->setElevatorDataFile("D:\\homeworks\\homewoks_college\\cpp\\202030481266刘树林\\elevators.csv");
    this->loadData();

    static const int elevator0 = 0;  
    static const int elevator1 = 1;  
    static const int elevator2 = 2;  
    static const int elevator3 = 3;  
    // 设置电梯的名字
    this->elevators[elevator0].setName("电梯1号");
    this->elevators[elevator1].setName("电梯2号");
    this->elevators[elevator2].setName("电梯3号");
    this->elevators[elevator3].setName("电梯4号");
    
    int countnum = 0;
    for (int i = 5; i >= fastest; i--) {
        printf("第%d次模拟开始：\n", ++countnum);
        this->runSimulation(i, number);
        this->resetSimulation();
        printf("第%d次模拟结束.\n", countnum);
    }
    // this->runSimulation(SEC_NEXT_FLOOR_FAST);
    this->outputTimes();
    return;
}

void Simulation::runSimulation(int interval, int number) {
    // 每一个电梯都要设置自己的运行时间
    for (int index = 0; index < Simulation::NUM_ELEVATORS; index++) {
        this->elevators[index].setTimeToNextFloor(interval);
    }
    while (true) {
        // 开始运行，每一个电梯开始根据自己的运动状态执行
        for (int index = 0; index < number; index++) {
            this->elevators[index].PerformNextMove();
        }
        this->addSimulationTime();// 增加时间
        if (this->checkPassengerAreCP()) {// 检查是不是所有的乘客都到达了目标楼层
            break;
        }
    }
    calTravelTimes();// 输出数据
    return;
}