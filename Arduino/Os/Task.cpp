// ======================================================================
// \title Arduino/Os/Task.cpp
// \brief Arduino implementations for Os::Task
// ======================================================================
#include "Arduino/Os/Task.hpp"
#include <new>
#include <Fw/Logger/Logger.hpp>

namespace Os {
namespace Arduino {
namespace Task {

ArduinoTask::~ArduinoTask() {
    if (this->m_handle) {
        delete this->m_handle;
    }
}

void ArduinoTask::onStart() {}

Os::TaskInterface::Status ArduinoTask::join() {
    return Os::TaskInterface::Status::OP_OK;
}

void ArduinoTask::suspend(Os::TaskInterface::SuspensionType suspensionType) {
    FW_ASSERT(this->m_handle != nullptr);
    this->m_handle->m_enabled = false;
}

void ArduinoTask::resume() {
    FW_ASSERT(this->m_handle != nullptr);
    this->m_handle->m_enabled = true;
}

Os::TaskHandle* ArduinoTask::getHandle() {
    return this->m_handle;
}

Os::TaskInterface::Status ArduinoTask::start(const Os::TaskInterface::Arguments& arguments) {
    FW_ASSERT(arguments.m_routine != nullptr);

    //Get a task handle, and set it up
    ArduinoTaskHandle* handle = new(std::nothrow) ArduinoTaskHandle();
    if (handle == nullptr) {
       return Os::TaskInterface::Status::INVALID_HANDLE;
    }

    // Set handle member variables
    handle->m_enabled = true;
    handle->m_priority = arguments.m_priority;
    handle->m_routine = arguments.m_routine;
    handle->m_argument = arguments.m_routine_argument;
    // Register this task using our custom task handle
    this->m_handle = handle;

    // Running the task the first time allows setup activities for the task
    handle->m_routine(handle->m_argument);

    return Os::TaskInterface::Status::OP_OK;
}

bool ArduinoTask::isCooperative() {
    return true;
}

Os::Task::Status ArduinoTask::_delay(Fw::TimeInterval interval) {
    return Os::Task::Status::DELAY_ERROR;
}

TaskRunner::TaskRunner() :
    m_index(0),
    m_cont(true)
{
    for (U32 i = 0; i < TASK_REGISTRY_CAP; i++) {
        this->m_task_table[i] = 0;
    }
    Os::Task::registerTaskRegistry(this);
}
TaskRunner::~TaskRunner() {}

void TaskRunner::addTask(Os::Task* task) {
    FW_ASSERT(m_index < TASK_REGISTRY_CAP);
    this->m_task_table[m_index] = task;
    m_index++;
}

void TaskRunner::removeTask(Os::Task* task) {
    bool found = false;
    // Squash that existing task
    for (U32 i = 0; i < TASK_REGISTRY_CAP; i++) {
        found = found | (task == this->m_task_table[i]);
        // If not found, keep looking
        if (!found) {
            continue;
        }
        // If we are less than the end of the array, shift variables over
        else if (i < TASK_REGISTRY_CAP - 1) {
            this->m_task_table[i] = this->m_task_table[i+1];
        }
        // If the last element, mark NULL
        else {
            this->m_task_table[i] = nullptr;
        }
    }
}

void TaskRunner::stop() {
    m_cont = false;
}

void TaskRunner::run() {
    U32 i = 0;
    if (!m_cont) {
        return;
    }
    // Loop through full table
    for (i = 0; i < TASK_REGISTRY_CAP; i++) {
        // Break at end of table
        if (m_task_table[i] == nullptr) {
            break;
        }
        // Get Arduino task or break
        ArduinoTaskHandle* handle = reinterpret_cast<ArduinoTaskHandle*>(m_task_table[i]->getHandle());
        if (handle == nullptr || handle->m_routine == nullptr || !handle->m_enabled) {
            continue;
        }
        // Run-it!
        handle->m_routine(handle->m_argument);
        // Disable tasks that have "exited" or stopped
        Os::TaskInterface::State state = m_task_table[i]->getState();
        handle->m_enabled = (state == Os::TaskInterface::State::EXITED) ? false : true;
    }
    // Check if no tasks, and stop
    if (i == 0) {
        m_cont = false;
    }
}


}  // namespace Task
}  // namespace Arduino
}  // namespace Os
