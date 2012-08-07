#pragma once
#include  <conio.h>
#include "stdafx.h"
#include "CConfigManager.h"

//
//如果指定的CPU核数小于实际，以实际为准，否则反之
int GetCPUNumberOf();

//
//截取ctrl+c，设定退出条件
void GetQuitCommand();
