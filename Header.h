#pragma once
#include <vector>
#include <string>
#include "Material.h"

struct MaterialStatsSnapshot {
	std::string name;
	int entered = 0;
	int survived = 0;
};
