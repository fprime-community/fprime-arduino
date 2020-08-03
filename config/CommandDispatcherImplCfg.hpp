/*
 * CmdDispatcherImplCfg.hpp
 *
 *  Created on: May 6, 2015
 *      Author: tcanham
 */

#ifndef CMDDISPATCHER_COMMANDDISPATCHERIMPLCFG_HPP_
#define CMDDISPATCHER_COMMANDDISPATCHERIMPLCFG_HPP_

// Define configuration values for dispatcher

enum {
    CMD_DISPATCHER_DISPATCH_TABLE_SIZE = 15, // !< The size of the table holding opcodes to dispatch
    CMD_DISPATCHER_SEQUENCER_TABLE_SIZE = 10, // !< The size of the table holding commands in progress
};



#endif /* CMDDISPATCHER_COMMANDDISPATCHERIMPLCFG_HPP_ */
