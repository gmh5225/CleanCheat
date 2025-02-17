﻿#pragma once
#include <vector>
#include "Macros.h"
#include "FeatureBase.h"

template <typename TType>
ABSTRACT class RunnerBase
{
protected:
    std::vector<FeatureBase<TType, int8_t>*> _features;

public:
    virtual ~RunnerBase() = default;

private:
    void ExecuteBeforeFeaturesCallbacks() const
    {
        for (FeatureBase<void>* const& feature : _features)
            feature->BeforeExecute();
    }

    void ExecuteAfterFeaturesCallbacks() const
    {
        for (FeatureBase<void>* const& feature : _features)
            feature->AfterExecute();
    }

protected:
    virtual void OnExecute() = 0;

    /// <summary>
    /// Execute registered features
    /// </summary>
    void ExecuteFeatures(TType* item) const
    {
        for (FeatureBase<TType>* const& feature : _features)
        {
            if (feature->Settings->Enable && feature->Condition(item))
                feature->Execute(item);
        }
    }

public:
    /// <summary>
    /// Condition runner will use to determine will execute this feature or not
    /// </summary>
    virtual bool Condition() = 0;

    /// <summary>
    /// Called evey tick
    /// </summary>
    void Tick()
    {
        ExecuteBeforeFeaturesCallbacks();
        OnExecute();
        ExecuteAfterFeaturesCallbacks();
    }

    /// <summary>
    /// Register feature
    /// </summary>
    template <class T>
    bool RegisterFeature(FeatureBase<T>* feature)
    {
        if (!feature->IsInitialized())
            return false;

        _features.push_back(feature);

        return true;
    }

    /// <summary>
    /// Discard
    /// </summary>
    void Discard()
    {
        for (FeatureBase<void>* feature : _features)
            feature->Discard();
    
        _features.clear();
    }
};
