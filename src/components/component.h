#pragma once

struct Component
{
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual void Init() = 0;
};