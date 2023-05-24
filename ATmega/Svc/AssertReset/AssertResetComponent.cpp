// ======================================================================
// \title  AssertResetComponent.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Reset the ATmega via the internal watchdog timer after a FW_ASSERT().
// ======================================================================

#include <ATmega/Svc/AssertReset/AssertResetComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>
#include <Fw/Logger/Logger.hpp>
#include <assert.h>
#include <stdio.h>

namespace ATmega {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  AssertResetComponent ::
#if FW_OBJECT_NAMES == 1
    AssertResetComponent(
        const char *const compName
    ) :
      AssertResetComponentBase(compName)
#else
    AssertResetComponent(void)
#endif
  {
      // register component with adapter
      this->m_reset.regAssertReporter(this);
      // register adapter
      this->m_reset.registerHook();
  }

  void AssertResetComponent ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    AssertResetComponentBase::init(instance);
  }

  AssertResetComponent ::
    ~AssertResetComponent(void)
  {

  }

  void AssertResetComponent::AssertReset::reportAssert(
          FILE_NAME_ARG file,
          NATIVE_UINT_TYPE lineNo,
          NATIVE_UINT_TYPE numArgs,
          AssertArg arg1,
          AssertArg arg2,
          AssertArg arg3,
          AssertArg arg4,
          AssertArg arg5,
          AssertArg arg6
          ) {

      if (m_compPtr) {
          m_compPtr->reportAssert(file,lineNo,numArgs,
                  arg1,arg2,arg3,arg4,arg5,arg6);
      } else {
          // Can't assert, what else can we do? Maybe somebody will see it.
          Fw::Logger::logMsg("ATmega::AssertReset not registered!\n");
          assert(0);
      }
  }

  void AssertResetComponent::AssertReset::regAssertReporter(AssertResetComponent* compPtr) {
      this->m_compPtr = compPtr;
  }

  AssertResetComponent::AssertReset::AssertReset() : m_compPtr(0) {
  }

  AssertResetComponent::AssertReset::~AssertReset() {
  }

} // end namespace ATmega
