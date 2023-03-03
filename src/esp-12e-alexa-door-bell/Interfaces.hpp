#pragma once

namespace
{
class IGuards
{
public:
    virtual ~IGuards() {}
};

class IActions
{
public:
    virtual ~IActions() {}
    virtual void Print_connected() = 0;
    virtual void PrintSwitchIsPushed() = 0;
    virtual void NotifyAlexa() = 0;
};

class IEvents
{
public:
    virtual ~IEvents() {}
    virtual void SwitchIsPushed() {}
    virtual void WiFi_is_connected() {}
    virtual void ReportSuccessful() {}
};

}