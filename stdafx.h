#pragma once
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
/*
* 
*	名称的英文全称为：Standard Application Fram Extend
	所谓头文件预编译，就是把一个工程(Project)中使用的一些MFC标准头文件(如Windows.H、Afxwin.H)预先编译，
	以后该工程编译时，不再编译这部分头文件，仅仅使用预编译的结果。这样可以加快编译速度，节省时间。
	预编译头文件通过编译stdafx.cpp生成，以工程名命名，由于预编译的头文件的后缀是“pch”，所以编译结果文件是
	projectname.pch。
	编译器通过一个头文件stdafx.h来使用预编译头文件。stdafx.h这个头文件名是可以在project的编译设置里指定的。
	编译器认为，所有在指令#include "stdafx.h"前的代码都是预编译的，它跳过#include "stdafx. h"指令，
	使用projectname.pch编译这条指令之后的所有代码。
	因此，所有的MFC实现文件第一条语句都是：#include "stdafx.h"。

*	与一般的main函数不一样
	#include "stdafx.h"

	int _tmain(int argc, _TCHAR* argv[])
	{
		return 0;
	}

	就是为了加快编译的速度！！

*/