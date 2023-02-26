#pragma once
#include "Interfaces.hpp"
#include "StateIds.hpp"
#include "Hsm/StateMachineBase.hpp"
#include "Hsm/Function.hpp"

namespace
{
class StateBase : public hsm::StateBase, public IEvents
{
public:
    StateBase(IActions* _actions, IGuards* _guards)
        : actions(_actions)
        , guards(_guards)
    {}

    virtual ~StateBase(){}

protected:
    IActions* actions;
    IGuards* guards;
};

class FloHsmInitial_5OdpEA31BEcPrWrNx8u7 : public StateBase
{
public:
    FloHsmInitial_5OdpEA31BEcPrWrNx8u7(StateId fromState, StateId toState, IActions* _actions, IGuards* _guards)
        : StateBase(_actions, _guards)
    {
        if (MustCallEntry(Id, fromState, toState))
        {
            SetTransitionDetails(StateId_Sense, Function());
        }
    }

    virtual ~FloHsmInitial_5OdpEA31BEcPrWrNx8u7()
    {}

    StateId GetId() const override { return Id; }
    
private:
    static const StateId Id = StateId_FloHsmInitial_5OdpEA31BEcPrWrNx8u7;

};

class Sense : public StateBase
{
public:
    Sense(StateId, StateId, IActions* _actions, IGuards* _guards)
        : StateBase(_actions, _guards)
    {}

    virtual ~Sense()
    {}

    void SwitchPushed() override
    {
        SetTransitionDetails(StateId_Report, Function());
    }

    StateId GetId() const override { return Id; }
    
private:
    static const StateId Id = StateId_Sense;

};

class Report : public StateBase
{
public:
    Report(StateId fromState, StateId toState, IActions* _actions, IGuards* _guards)
        : StateBase(_actions, _guards)
    {
        if (MustCallEntry(Id, fromState, toState))
        {
            actions->NotifyAlexa();
        }
    }

    virtual ~Report()
    {}

    void NoAction() override
    {
        SetTransitionDetails(StateId_Delay, Function());
    }

    StateId GetId() const override { return Id; }
    
private:
    static const StateId Id = StateId_Report;

};

class Delay : public StateBase
{
public:
    Delay(StateId, StateId, IActions* _actions, IGuards* _guards)
        : StateBase(_actions, _guards)
    {}

    virtual ~Delay()
    {}

    void Complete() override
    {
        SetTransitionDetails(StateId_Sense, Function());
    }

    StateId GetId() const override { return Id; }
    
private:
    static const StateId Id = StateId_Delay;

};

}