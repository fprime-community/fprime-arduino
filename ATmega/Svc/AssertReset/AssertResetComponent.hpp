// ======================================================================
// \title  AssertResetComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Reset the ATmega via the internal watchdog timer after a FW_ASSERT().
// ======================================================================

#ifndef AssertReset_HPP
#define AssertReset_HPP

#include "ATmega/Svc/AssertReset/AssertResetComponentAc.hpp"
#include <Fw/Types/Assert.hpp>

namespace Fw {
    void defaultReportAssert
            (
            FILE_NAME_ARG file,
            NATIVE_UINT_TYPE lineNo,
            NATIVE_UINT_TYPE numArgs,
            AssertArg arg1,
            AssertArg arg2,
            AssertArg arg3,
            AssertArg arg4,
            AssertArg arg5,
            AssertArg arg6,
            I8* destBuffer,
            NATIVE_INT_TYPE buffSize
            );

}

namespace ATmega {

  const U32 assertFlagTrue = 0xdeadbeef;

  #ifdef __AVR__
  extern volatile U32 assertFlag __attribute__ ((section(".noinit")));
  extern volatile FILE_NAME_ARG prevAssertFile __attribute__ ((section(".noinit")));
  extern volatile NATIVE_UINT_TYPE prevAssertLineNo __attribute__ ((section(".noinit")));
  extern volatile NATIVE_UINT_TYPE prevAssertNumArgs __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg1 __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg2 __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg3 __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg4 __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg5 __attribute__ ((section(".noinit")));
  extern volatile AssertArg prevAssertArg6 __attribute__ ((section(".noinit")));
  #else
  extern volatile U32 assertFlag;
  extern volatile FILE_NAME_ARG prevAssertFile;
  extern volatile NATIVE_UINT_TYPE prevAssertLineNo;
  extern volatile NATIVE_UINT_TYPE prevAssertNumArgs;
  extern volatile AssertArg prevAssertArg1;
  extern volatile AssertArg prevAssertArg2;
  extern volatile AssertArg prevAssertArg3;
  extern volatile AssertArg prevAssertArg4;
  extern volatile AssertArg prevAssertArg5;
  extern volatile AssertArg prevAssertArg6;
  #endif

  class AssertResetComponent :
    public AssertResetComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object AssertReset
      //!
      AssertResetComponent(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object AssertReset
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object AssertReset
      //!
      ~AssertResetComponent(void);

      //! Report the assert as a FATAL
      void reportAssert(
          FILE_NAME_ARG file,
          NATIVE_UINT_TYPE lineNo,
          NATIVE_UINT_TYPE numArgs,
          AssertArg arg1,
          AssertArg arg2,
          AssertArg arg3,
          AssertArg arg4,
          AssertArg arg5,
          AssertArg arg6
          );

    private:

      class AssertReset : public Fw::AssertHook {
          public:
              AssertReset();
              ~AssertReset();
              void regAssertReporter(AssertResetComponent* compPtr);
          private:
              void reportAssert(
                  FILE_NAME_ARG file,
                  NATIVE_UINT_TYPE lineNo,
                  NATIVE_UINT_TYPE numArgs,
                  AssertArg arg1,
                  AssertArg arg2,
                  AssertArg arg3,
                  AssertArg arg4,
                  AssertArg arg5,
                  AssertArg arg6
                  );

              // Prevent actual assert since we want something more specific
              void doAssert(void);

              AssertResetComponent* m_compPtr;
      };

        AssertReset m_reset;

    };

} // end namespace ATmega

#endif
