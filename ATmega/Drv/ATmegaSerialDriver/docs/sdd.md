# ATmega Serial UART Driver Component

## 1. Introduction

UART driver for operating the hardware UARTs on an ATmega hardware platform (such as ATmega128).

## 2. Requirements

The requirements for `Drv::ATmegaSerialDriverComponentImpl` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
ATSD-001    | The `Drv::ATmegaSerialDriverComponentImpl` component shall recieve ``Fw:Buffer`` objects from other components and forward their contents over UART | Inspection
ATSD-002    | The `Drv::ATmegaSerialDriverComponentImpl` component shall collect character from the UART and pack them into ``Fw:Buffer`` objects available for query | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Drv::ATmegaSerialDriverComponentImpl` component has the following component diagram:

![`Drv::ATmegaSerialDriverComponentImpl` Diagram](img/ATmegaSerialDriverComponentImplBDD.jpg "Drv::ATmegaSerialDriverComponentImpl")

#### 3.1.2 Ports

The `Drv::ATmegaSerialDriverComponentImpl` component uses the following port types:

| Port Data Type                                            | Name            | Direction | Kind | Usage |
| --------------------------------------------------------- | --------------- | --------- | ---- | ----- |
| [`Svc::Sched`](../../../Svc/Sched/docs/sdd.md)            | reportTlm       | Input     | Sync | Dump telemetry about bytes transferred |
| [`Drv::SerialRead`](../../SerialDriverPorts/docs/sdd.md)  | serialRecv      | Input     | Sync | Recieve bytes from external device |
| [`Drv::SerialWrite`](../../SerialDriverPorts/docs/sdd.md) | serialSend      | Input     | Sync | Send bytes to external device |
| [`Fw::BufferSend`](../../../Buf/Buffer/docs/sdd.md)       | serialRecvFwBuf | Input     | Sync | Recieve bytes from external device |
| [`Fw::BufferSend`](../../../Buf/Buffer/docs/sdd.md)       | serialSendFwBuf | Input     | Sync | Send bytes to external device |

### 3.2 Functional Description

This component provides an F Prime interface for the hardware UARTs on the ATmega.
The component is passive, but the ports are also non-blocking.
This works because the outgoing byte buffer is copied into the component's local buffer, and an ISR pulls bytes from the buffer to be sent across the wire as the hardware completes the transaction.
Receive works similarly, also driven by an ISR and storing the bytes locally.
For operational simplicity, bytes must be polled by any component wishing to recieve from the UART, rather than "pushed" from this component.

### 3.3 Scenarios

Configuration for each UART requires a separate call to the ``open()`` method.
Unconfigured UARTs will not appear to work.

When building an ATmega deployment using this target for Linux (or Darwin), no adjustments are needed to the ``open()`` call.
You may want to specify the ``USART0`` and ``USART1`` device strings by overriding the default mappings.  You may do so by adding these lines to your deployment ``CMakeLists.txt`` file (which will not affect the ATmega target build):

```cmake
add_definitions(-DUSART0_LINUX_DEVICE="/dev/ttyUSB0")
add_definitions(-DUSART1_LINUX_DEVICE="/dev/ttyUSB1")
```

### 3.4 State

`Drv::ATmegaSerialDriverComponentImpl` has no state machines.

### 3.5 Algorithms

`Drv::ATmegaSerialDriverComponentImpl` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](ATmegaSerialDriverComponentImpl.html) [MD](ATmegaSerialDriver.md)

## 4. Module Checklists

Document            | Link
------------------- | ----
Design Checklist    | [Link](Checklist_Design.xlsx)
Code Checklist      | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/DrvATmegaSerialDriverComponentImpl_gcov.txt)

[Coverage Output - `Drv::ATmegaSerialDriverComponentImpl.cpp`](../test/ut/output/ATmegaSerialDriverComponentImpl.cpp.gcov)

[Coverage Output - `ATmegaSerialDriverComponentAc.cpp`](../test/ut/output/ATmegaSerialDriverComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
09/22/2020 | Initial Component Design



