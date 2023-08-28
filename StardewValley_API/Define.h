#pragma once
#include <iostream>
#include <Windows.h>
#include <list>
#include <vector>
#include "Timer.h"
#include "Struct.h"

using namespace std;

// ΩÃ±€≈Ê ∆–≈œ
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