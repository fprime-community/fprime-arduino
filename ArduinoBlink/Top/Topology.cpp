#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>
#include <Os/Log.hpp>
#include <Os/File.hpp>
#include <Fw/Types/MallocAllocator.hpp>
#include <ArduinoBlink/Top/ArduinoSchedContexts.hpp>
#include "ArduinoBlink/Top/Components.hpp"

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rate_divisors[] = {1, 10};
Svc::RateGroupDriverImpl rateGroupDriverComp("RGDRV", rate_divisors, FW_NUM_ARRAY_ELEMENTS(rate_divisors));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in RPITopologyAi.xml
static NATIVE_UINT_TYPE rg10HzContext[] = {Arduino::CONTEXT_RPI_DEMO_10Hz, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup10HzComp("RG10Hz",rg10HzContext,FW_NUM_ARRAY_ELEMENTS(rg10HzContext));
static NATIVE_UINT_TYPE rg1HzContext[] = {0, 0, Arduino::CONTEXT_RPI_DEMO_1Hz, 0};
Svc::ActiveRateGroupImpl rateGroup1HzComp("RG1Hz",rg1HzContext,FW_NUM_ARRAY_ELEMENTS(rg1HzContext));

// Standard system components
Svc::ActiveLoggerImpl eventLogger("ELOG");
Svc::TlmChanImpl chanTlm("TLM");
Svc::CommandDispatcherImpl cmdDisp("CMDDISP");
Svc::HealthImpl health("health");

Svc::GroundInterfaceComponentImpl groundInterface("GIF");

// Arduino specific components
Arduino::LedBlinkerComponentImpl ledBlinker("Blinker");
Arduino::HardwareRateDriver hardwareRateDriver("RateDr", 100);
Arduino::SerialDriverComponentImpl comm("COMM", 1);

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;
/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp() {
    // Initialize rate group driver
    rateGroupDriverComp.init();

    // Initialize the rate groups
    rateGroup10HzComp.init(10, 0);
    rateGroup1HzComp.init(10, 1);

    // Initialize the core data handling components
    eventLogger.init(10, 0);
    chanTlm.init(20, 0);
    cmdDisp.init(10,0);
    health.init(25,0);
    groundInterface.init(0);
    ledBlinker.init(0);
    comm.init(0, 115200);

    // Callback to initialize architecture, connect ports, etc.
    constructArduinoArchitecture();

    // Register all commands into the system
    cmdDisp.regCommands();
    eventLogger.regCommands();
    health.regCommands();

    // Setup the health an ping entries. These need to be in the same order as the
    // ports connected to the health component. Once the ping entry array is created
    // pass it into the ping-entries array.
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, rateGroup10HzComp.getObjName()},
        {3, 5, rateGroup1HzComp.getObjName()},
        {3, 5, cmdDisp.getObjName()},
        {3, 5, chanTlm.getObjName()},
        {3, 5, eventLogger.getObjName()}
    };
    health.setPingEntries(pingEntries,FW_NUM_ARRAY_ELEMENTS(pingEntries),0x123);
    hardwareRateDriver.start();
    // Start all active components' tasks thus finishing the setup portion of this code
    rateGroup10HzComp.start(0, 120, 10 * 1024);
    rateGroup1HzComp.start(0, 119, 10 * 1024);
    cmdDisp.start(0, 101, 10 * 1024);
    eventLogger.start(0, 98, 10 * 1024);
    chanTlm.start(0, 97, 10 * 1024);
}
/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software. This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.
 */
void exitTasks(void) {
    rateGroup1HzComp.exit();
    rateGroup10HzComp.exit();
    cmdDisp.exit();
    eventLogger.exit();
    chanTlm.exit();
}
