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
    virtual void NotifyAlexa() = 0;
};

class IEvents
{
public:
    virtual ~IEvents() {}
    virtual void SwitchPushed() {}
    virtual void ReportSuccessful() {}
    virtual void WiFiConnected() {}
};

}