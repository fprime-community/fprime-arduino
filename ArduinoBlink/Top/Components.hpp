#ifndef __ARD_COMPONENTS_HEADER__
#define __ARD_COMPONENTS_HEADER__

void constructArduinoArchitecture(void);
void exitTasks(void);
void constructApp();

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
//#include <Svc/PassiveConsoleTextLogger/ConsoleTextLoggerImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
//#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>
#include <Svc/PrmDb/PrmDbImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <Svc/Health/HealthComponentImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Svc/AssertFatalAdapter/AssertFatalAdapterComponentImpl.hpp>
#include <Svc/FatalHandler/FatalHandlerComponentImpl.hpp>

#include <ArduinoBlink/LedBlinker/LedBlinker.hpp>
#include <fprime-arduino/ArduinoDrv/HardwareRateDriver/HardwareRateDriver.hpp>
#include <fprime-arduino/ArduinoDrv/SerialDriver/SerialDriver.hpp>
#include <fprime-arduino/ArduinoTime/ArduinoTimeImpl.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>

//Core components. Gotta run them all
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Svc::ActiveRateGroupImpl rateGroup1HzComp;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::TlmChanImpl chanTlm;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::GroundInterfaceComponentImpl groundInterface;
extern Svc::AssertFatalAdapterComponentImpl fatalAdapter;
extern Svc::FatalHandlerComponentImpl fatalHandler;
extern Svc::HealthImpl health;
extern Arduino::LedBlinkerComponentImpl ledBlinker;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern Arduino::SerialDriverComponentImpl comm;
extern Svc::ArduinoTimeImpl time;
// Scheduler definition
extern Os::TaskRunner taskRunner;
#endif
