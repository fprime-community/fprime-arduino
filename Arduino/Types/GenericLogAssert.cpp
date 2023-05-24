/*
 * GenericLogAssert.hpp:
 *
 * Header defining the generic assert handler that outputs the assert message to Os::Log. This can
 * be used by any system that has a functioning Os::Log implementation. This is the implementation function.
 *
 *  Created on: April 13th, 2019
 *      Author: mstarch
 */
#include <Fw/Types/Generic/GenericLogAssert.hpp>
#include <Os/Log.hpp>

#if FW_ASSERT_LEVEL == FW_NO_ASSERT
    // No asserts supported
#else

#if FW_ASSERT_LEVEL == FW_FILEID_ASSERT
    #define ASSERT_FORMAT "ASSERT: Hash %d: Line: %d"
#else
    #define ASSERT_FORMAT "ASSERT: \"%s\": Line: %d"
#endif


namespace Fw {
    // No-op constructor and destrctor
    LogAssertHook::LogAssertHook() {}
    LogAssertHook::~LogAssertHook() {}

    void LogAssertHook::reportAssert(
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
        // Assumption is that file (when string) goes back to static macro in the code and will persist
        POINTER_CAST pfile = reinterpret_cast<POINTER_CAST>(file);

        switch (numArgs) {
            case 0:
                Os::Log::logMsg(ASSERT_FORMAT "\n", pfile, lineNo, 0, 0, 0, 0);
                break;
            case 1:
                Os::Log::logMsg(ASSERT_FORMAT " %d\n", pfile, lineNo, arg1, 0, 0, 0);
                break;
            case 2:
                Os::Log::logMsg(ASSERT_FORMAT " %d %d\n", pfile, lineNo, arg1, arg2, 0, 0);
                break;
            case 3:
                Os::Log::logMsg(ASSERT_FORMAT " %d %d %d\n", pfile, lineNo, arg1, arg2, arg3, 0);
                break;
            case 4:
                Os::Log::logMsg(ASSERT_FORMAT " %d %d %d %d\n", pfile, lineNo, arg1, arg2, arg3,
                                arg4);
                break;
            default: // can't fit remainder of arguments in log message
                Os::Log::logMsg(ASSERT_FORMAT " %d %d %d %d ...\n", pfile, lineNo, arg1, arg2,
                                arg3, arg4);
                break;
        }

    }

    // No-op handles for printing and doing asserts.
    void LogAssertHook::printAssert(const I8* msg) {}
    void LogAssertHook::doAssert(void) {}

} // namespace Fw

#endif
