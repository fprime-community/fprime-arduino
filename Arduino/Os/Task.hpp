// ======================================================================
// \title Arduino/Os/Task.hpp
// \brief Arduino definitions for Os::Task
// ======================================================================
#include "Os/Task.hpp"

#ifndef OS_ARDUINO_TASK_HPP
#define OS_ARDUINO_TASK_HPP

#define TASK_REGISTRY_CAP 100

namespace Os {
namespace Arduino {
namespace Task {

//! Arduino task handle
class ArduinoTaskHandle : public TaskHandle {
  public:
    //!< Constructor sets enabled to false
    ArduinoTaskHandle() : m_enabled(false), m_priority(0), m_routine(nullptr) {}
    //!< Is this task enabled or not
    bool m_enabled;
    //!< Save the priority
    NATIVE_INT_TYPE m_priority;
    //!< Function passed into the task
    Os::TaskInterface::taskRoutine m_routine;
    //!< Argument input pointer
    void* m_argument;
};

//! Implementation of task
class ArduinoTask : public TaskInterface {
  public:
    //! Constructor
    ArduinoTask() = default;

    //! Destructor
    ~ArduinoTask() override;

    //! \brief perform required task start actions
    void onStart() override;

    //! \brief block until the task has ended
    //!
    //! Blocks the current (calling) task until this task execution has ended. Callers should ensure that any
    //! signals required to stop this task have already been emitted or will be emitted by another task.
    //!
    //! \return status of the block
    Status join() override;

    //! \brief suspend the task given the suspension type
    //!
    //! Suspends the task. Some implementations track if the suspension of a task was intentional or
    //! unintentional. The supplied `suspensionType` parameter indicates that this was intentional or
    //! unintentional. The type of suspension is also returned when calling `isSuspended`.
    //!
    //! \param suspensionType intentionality of the suspension
    void suspend(SuspensionType suspensionType) override;

    //! \brief resume a suspended task
    //!
    //! Resumes this task. Not started, running, and exited tasks take no action.
    //!
    void resume() override;

    //! \brief delay the current task
    //!
    //! Delays, or sleeps, the current task by the supplied time interval. In non-preempting os implementations
    //! the task will resume no earlier than expected but an exact wake-up time is not guaranteed.
    //!
    //! \param interval: delay time
    //! \return status of the delay
    Status _delay(Fw::TimeInterval interval) override;

    //! \brief return the underlying task handle (implementation specific)
    //! \return internal task handle representation
    TaskHandle* getHandle() override;

    //! \brief determine if the task requires cooperative multitasking
    //!
    //! Some task implementations require cooperative multitasking where the task execution is run by a user
    //! defined task scheduler and not the operating system task scheduler. These tasks cooperatively on
    //! multitask by doing one unit of work and return from the function.
    //!
    //! This function indicates if the task requires cooperative support.
    //! The default implementation returns false.
    //!
    //! \return true when the task expects cooperation, false otherwise
    bool isCooperative() override;

    //! \brief start the task
    //!
    //! Starts the task given the supplied arguments.
    //!
    //! \param arguments: arguments supplied to the task start call
    //! \return status of the task start
    Status start(const Arguments& arguments) override;

    ArduinoTaskHandle* m_handle;  //!< Arduino task tracking
};

/**
 * Combination TaskRegistry and task runner. This does the "heavy lifting" for
 * baremetal running of tasks.
 */
class TaskRunner : TaskRegistry {
  public:
    //!< Nothing constructor
    TaskRunner();
    //!< Nothing destructor
    ~TaskRunner();
    /**
     * Add a task to the registry. These tasks will be run on a bare-metal
     * loop. The function used in this task may be overridden.
     * \param task: task to be added
     */
    void addTask(Os::Task* task);
    /**
     * Remove a task to the registry. These tasks will no-longer be run.
     * \param task: task to be removed
     */
    void removeTask(Os::Task* task);
    /**
     * Stop this task registry
     */
    void stop();
    /**
     * Run once function call, used to run one pass over tasks
     */
    void run();

  private:
    U32 m_index;
    Os::Task* m_task_table[TASK_REGISTRY_CAP];
    bool m_cont;
};

}  // namespace Task
}  // namespace Arduino
}  // namespace Os
#endif  // End OS_ARDUINO_TASK_HPP
