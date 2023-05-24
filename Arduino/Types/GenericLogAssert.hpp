/*
 * GenericLogAssert.hpp:
 *
 * Header defining the generic assert handler that outputs the assert message to Os::Log. This can
 * be used by any system that has a functioning Os::Log implementation.
 *
 *  Created on: April 13th, 2019
 *      Author: mstarch
 */
#ifndef GENERICLOGASSERT_HPP_
#define GENERICLOGASSERT_HPP_
#include <Fw/Types/Assert.hpp>
namespace Fw {
    /**
     * Assert handler that report to Os::Log the assertion message, and performs no other actions.
     */
    class LogAssertHook: public Fw::AssertHook {
        public:
            LogAssertHook();
            virtual ~LogAssertHook();
            /**
             * Report the assert message. Takes in arguments, and formats them given the format
             * string. The result is deferred to the Os::Log logging functions.
             * \param FILE_NAME_ARG file: file the assertion occurred in.
             * \param NATIVE_UINT_TYPE lineNo: line number of the assertion
             * \param NATIVE_UINT_TYPE numArgs: number of arguments used
             * \param AssertArg arg1-6: numbered arguments 1-6
             */
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
            /**
             * Prints the assertion. In this case, it does nothing.
             * \param const I8* msg: message to print
             */
            void printAssert(const I8* msg);
            /**
             * No-op when "handling" an assert.
             */
            void doAssert(void);
    };

}

#endif /* VXWORKSLOGASSERT_HPP_ */
