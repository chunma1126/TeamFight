#pragma once
#include <unordered_map>
#include "Stat.h"

class StatController
{
public:
    StatController();
    ~StatController();

public:
    void init();
    void update(float dt);

public:
    void setDefaultStat(STAT_TYPE stat, float amount);
    void addStat(STAT_TYPE stat, float amount);
    void removeStat(STAT_TYPE stat, float amount);
    float getValue(STAT_TYPE stat);

private:
    std::unordered_map<STAT_TYPE, Stat> _stats;
};