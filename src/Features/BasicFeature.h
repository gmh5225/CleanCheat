﻿#pragma once
#include "CleanCheat/FeatureBase.h"

class BasicSettings final : public FeatureSettings
{
public:
    bool Test = false;
};

class BasicFeature final : public FeatureBase<int, BasicSettings>
{
protected:
    void OnExecute(int* param) override;
    
public:
    bool Condition(int* param) override;
};
