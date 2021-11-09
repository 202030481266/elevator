#include "setting.h"
#include <iostream>
using namespace std;

Setting::Setting() {
	int interval = 0;
	int max_passenger = 0;
	int stop_sec = 0;
	int max_floor = 0;
	int max_elevators = 0;

	// 输入电梯的个数
	cout << "请输入电梯的个数： ";
	cin >> max_elevators;
	if (max_elevators >= 1)
		cout << endl << "输入成功！";
	else {
		throw exception("输入有错误！");
	}

	// 输入电梯的最大承载的人数
	cout << "请输入电梯的最大装载人数（整数个）： ";
	cin >> max_passenger;
	if (max_passenger > 0)
		cout << endl << "输入成功！";
	else {
		throw exception("输入的人数有误！");
	}

	// 输入电梯最大的上升高度（建筑物的高度）
	cout << "请输入电梯的最大上升高度（楼的高度）： ";
	cin >> max_floor;
	if (max_floor >= 1)
		cout << endl << "输入成功！";
	else {
		throw exception("输入的楼层高度有问题！");
	}

	// 输入电梯在楼与楼之间运行的时间
	cout << "请输入电梯在楼与楼之间运行的时间： ";
	cin >> interval;
	if (interval > 0)
		cout << endl << "输入成功！";
	else {
		throw exception("输入的运行时间有错误！");
	}

	// 输入电梯在每一层楼等待的时间
	cout << "请输入电梯在每一楼等待停留的时间：";
FLAG:
	cin >> stop_sec;
	if (stop_sec < 0)
		throw exception("输入的时间错误！");
	else if (stop_sec < 2) {
		cout << endl << "输入的时间太短了！请重新输入： ";
		goto FLAG;
	}
	else {
		cout << endl << "输入成功！";
	}

	this->MAX_FLOORS = max_floor;
	this->MAX_PASSENGER_NUM = max_passenger;
	this->STOP_SECS = stop_sec;
	this->TIME_INTERVAL = interval;
	this->MAX_ELEVATOR_NUM = max_elevators;
}

Setting::~Setting() {}