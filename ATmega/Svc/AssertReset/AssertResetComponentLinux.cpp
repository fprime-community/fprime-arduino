// ======================================================================
// \title  AssertResetComponentLinux.cpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Reset the ATmega via the internal watchdog timer after a FW_ASSERT().
// ======================================================================

#include <ATmega/Svc/AssertReset/AssertResetComponent.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>
#include <Fw/Log/LogString.hpp>
#include <Fw/Logger/Logger.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

namespace ATmega {
  void AssertResetComponent::AssertReset::doAssert(void) {
        // for **nix, delay then exit with error code
        Fw::Logger::logMsg("A FATAL Assert Occurred.\n",0,0,0,0,0,0);
        (void)Os::Task::delay(1000);
        Fw::Logger::logMsg("Exiting.\n",0,0,0,0,0,0);
        (void)raise( SIGSEGV );
        exit(1);
  }

  void AssertResetComponent::reportAssert(
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


#if FW_ASSERT_LEVEL == FW_FILEID_ASSERT
      Fw::LogStringArg fileArg;
      fileArg.format("0x%08X",file);
#else
      Fw::LogStringArg fileArg((const char*)file);
#endif

      I8 msg[FW_ASSERT_TEXT_SIZE];
      Fw::defaultReportAssert(file,lineNo,numArgs,arg1,arg2,arg3,arg4,arg5,arg6,msg,sizeof(msg));
      fprintf(stderr, "%s\n",(const char*)msg);

      // switch (numArgs) {
      //     case 0:
      //         this->log_FATAL_AF_ASSERT_0(fileArg,lineNo);
      //         break;
      //     case 1:
      //         this->log_FATAL_AF_ASSERT_1(fileArg,lineNo,arg1);
      //         break;
      //     case 2:
      //         this->log_FATAL_AF_ASSERT_2(fileArg,lineNo,arg1,arg2);
      //         break;
      //     case 3:
      //         this->log_FATAL_AF_ASSERT_3(fileArg,lineNo,arg1,arg2,arg3);
      //         break;
      //     case 4:
      //         this->log_FATAL_AF_ASSERT_4(fileArg,lineNo,arg1,arg2,arg3,arg4);
      //         break;
      //     case 5:
      //         this->log_FATAL_AF_ASSERT_5(fileArg,lineNo,arg1,arg2,arg3,arg4,arg5);
      //         break;
      //     case 6:
      //         this->log_FATAL_AF_ASSERT_6(fileArg,lineNo,arg1,arg2,arg3,arg4,arg5,arg6);
      //         break;
      //     default:
      //         this->log_FATAL_AF_UNEXPECTED_ASSERT(fileArg,lineNo,numArgs);
      //         break;
      // }

  }

} // end namespace ATmega
