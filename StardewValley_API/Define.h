#pragma once
#include <iostream>
#include <Windows.h>
#include <list>
#include "Timer.h"
#include "Struct.h"

// �̱��� ����
#define MyCore(type)\
public:\
static type* GetInstance()\
{\
	static type mgr; \
	return &mgr; \
}\
private:\
	type(); \
	~type(); \