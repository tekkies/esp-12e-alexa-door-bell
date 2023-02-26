#pragma once
#include "Hsm/StateId.hpp"
#include <string>
#include <map>

namespace
{
const uint32_t CompositeStatesRegion = 10;

const StateId StateId_FloHsmInitial_5OdpEA31BEcPrWrNx8u7 = 1;
const StateId StateId_ConnectWiFi = 2;
const StateId StateId_Sense = 3;
const StateId StateId_Report = 4;
const StateId StateId_Delay = 5;

const std::map<StateId, std::string> StateNames = 
{
    { StateId_FloHsmInitial_5OdpEA31BEcPrWrNx8u7, "FloHsmInitial_5OdpEA31BEcPrWrNx8u7" },
    { StateId_ConnectWiFi, "ConnectWiFi" },
    { StateId_Sense, "Sense" },
    { StateId_Report, "Report" },
    { StateId_Delay, "Delay" },
};
}