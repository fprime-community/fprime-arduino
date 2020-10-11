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
Svc::RateGroupDriverImpl rateGroupDriverComp(FW_OPTIONAL_NAME("RGDRV"), rate_divisors, FW_NUM_ARRAY_ELEMENTS(rate_divisors));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in RPITopologyAi.xml
static NATIVE_UINT_TYPE rg10HzContext[] = {Arduino::CONTEXT_RPI_DEMO_10Hz, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup10HzComp(FW_OPTIONAL_NAME("RG10Hz"),rg10HzContext,FW_NUM_ARRAY_ELEMENTS(rg10HzContext));
static NATIVE_UINT_TYPE rg1HzContext[] = {0, 0, Arduino::CONTEXT_RPI_DEMO_1Hz, 0};
Svc::ActiveRateGroupImpl rateGroup1HzComp(FW_OPTIONAL_NAME("RG1Hz"),rg1HzContext,FW_NUM_ARRAY_ELEMENTS(rg1HzContext));

// Standard system components
Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("EventLogger"));
Svc::TlmChanImpl chanTlm(FW_OPTIONAL_NAME("Telemetry"));
Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("CmdDisp"));
Svc::HealthImpl health(FW_OPTIONAL_NAME("Health"));

Svc::GroundInterfaceComponentImpl groundInterface(FW_OPTIONAL_NAME("Ground"));

// Arduino specific components
Arduino::LedBlinkerComponentImpl ledBlinker(FW_OPTIONAL_NAME("LedBlinker"));
Arduino::HardwareRateDriver hardwareRateDriver(FW_OPTIONAL_NAME("HardDriver"), 100);
Arduino::SerialDriverComponentImpl comm(FW_OPTIONAL_NAME("Comm"), 1);
Svc::ArduinoTimeImpl time(FW_OPTIONAL_NAME("Time"));

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;

const char* getHealthName(Fw::ObjBase& comp) {
   #if FW_OBJECT_NAMES == 1
       return comp.getObjName();
   #else
      return "";
   #endif
}
/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp() {
    Fw::Logger::logMsg("[SETUP] Init block\n", 0, 0, 0, 0, 0, 0);
    time.init(0);
    // Initialize rate group driver
    rateGroupDriverComp.init();
    Fw::Logger::logMsg("[SETUP] RGs\n", 0, 0, 0, 0, 0, 0);

    // Initialize the rate groups
    rateGroup10HzComp.init(10, 0);
    rateGroup1HzComp.init(10, 1);

    Fw::Logger::logMsg("[SETUP] Data\n", 0, 0, 0, 0, 0, 0);
    // Initialize the core data handling components
    eventLogger.init(10, 0);
    Fw::Logger::logMsg("[SETUP] Chans\n", 0, 0, 0, 0, 0, 0);
    chanTlm.init(20, 0);
    Fw::Logger::logMsg("[SETUP] Cmd\n", 0, 0, 0, 0, 0, 0);
    cmdDisp.init(10,0);
    Fw::Logger::logMsg("[SETUP] Health\n", 0, 0, 0, 0, 0, 0);
    health.init(25,0);
    Fw::Logger::logMsg("[SETUP] If\n", 0, 0, 0, 0, 0, 0);
    groundInterface.init(0);
    Fw::Logger::logMsg("[SETUP] Blinker\n", 0, 0, 0, 0, 0, 0);
    ledBlinker.init(0);
    Fw::Logger::logMsg("[SETUP] Comm\n", 0, 0, 0, 0, 0, 0);
    comm.init(0, 115200);
    Fw::Logger::logMsg("[SETUP] Architecture\n", 0, 0, 0, 0, 0, 0);

    // Callback to initialize architecture, connect ports, etc.
    constructArduinoArchitecture();
    Fw::Logger::logMsg("[SETUP] Command reg\n", 0, 0, 0, 0, 0, 0);

    // Register all commands into the system
    cmdDisp.regCommands();
    eventLogger.regCommands();
    health.regCommands();

    // Setup the health an ping entries. These need to be in the same order as the
    // ports connected to the health component. Once the ping entry array is created
    // pass it into the ping-entries array.
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, getHealthName(rateGroup10HzComp)},
        {3, 5, getHealthName(rateGroup1HzComp)},
        {3, 5, getHealthName(cmdDisp)},
        {3, 5, getHealthName(chanTlm)},
        {3, 5, getHealthName(eventLogger)}
    };
    health.setPingEntries(pingEntries,FW_NUM_ARRAY_ELEMENTS(pingEntries),0x123);
    Fw::Logger::logMsg("[SETUP] Start\n", 0, 0, 0, 0, 0, 0);
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
