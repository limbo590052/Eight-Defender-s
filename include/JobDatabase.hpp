#pragma once
#include <map>
#include <string>
#include <vector>

// 包含定義
#include "JobDefine.hpp"

// 使用 extern 宣告，告訴編譯器這個變數存在於別處
extern std::map<Job, JobStats> JobDatabase;

// 輔助函式宣告 (若其他地方需要計算速度)
float CalcSpeed(int frames);