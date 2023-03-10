#pragma once
#include "Interfaces.hpp"
#include "StateIds.hpp"
#include "States.hpp"
#include "Hsm/StateMachineBase.hpp"

namespace
{
class StateMachine: public hsm::StateMachineBase, public IEvents, private IActions, public IGuards
{
public:
    StateMachine()
        : currentState(nullptr)
    {}

    void InitStateMachine()
    {
        ChangeState(StateId_Invalid, StateId_FloHsmInitial_5OdpEA31BEcPrWrNx8u7);
        ChangeStateIfNecessary();
    }

    StateId CurrentState() const override { return currentState->GetId(); }

    void SwitchIsPushed() override
    {
        currentState->SwitchIsPushed();
        ChangeStateIfNecessary();
    }
    
    void WiFi_is_connected() override
    {
        currentState->WiFi_is_connected();
        ChangeStateIfNecessary();
    }
    
    void ReportSuccessful() override
    {
        currentState->ReportSuccessful();
        ChangeStateIfNecessary();
    }
    

protected:
    StateBase* currentState;

private:
    StateBase* ChangeStateInternal(StateId fromState, StateId toState) override
    {
        const StateId previousStateId = fromState;

        switch (toState)
        {
        case StateId_FloHsmInitial_5OdpEA31BEcPrWrNx8u7:
            currentState = new (stateStorage)FloHsmInitial_5OdpEA31BEcPrWrNx8u7(previousStateId, toState, this, this);
            break;
        case StateId_ConnectWiFi:
            currentState = new (stateStorage)ConnectWiFi(previousStateId, toState, this, this);
            break;
        case StateId_Sense:
            currentState = new (stateStorage)Sense(previousStateId, toState, this, this);
            break;
        case StateId_Report:
            currentState = new (stateStorage)Report(previousStateId, toState, this, this);
            break;
        default:
            break;
        }

        return currentState;
    }

    uint8_t stateStorage[1000];
};
}