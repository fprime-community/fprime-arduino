# ATmegaInternalAdcDriver Component

## 1. Introduction

Reads the value from a register in the ATmega Internal ADC

## 2. Requirements

The requirements for `Drv::ATmegaInternalAdcDriverComponentImpl` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
AI-001 | The `Drv::ATmegaInternalAdcDriverComponentImpl` component returns adc count values | Functional Test

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Drv::ATmegaInternalAdcDriverComponentImpl` component has the following component diagram:

![`Drv::ATmegaInternalAdcDriverComponentImpl` Diagram](img/ATmegaInternalAdcDriverComponentImplBDD.jpg "Drv::ATmegaInternalAdcDriverComponentImpl")

#### 3.1.2 Ports

The `Drv::ATmegaInternalAdcDriverComponentImpl` component uses the following port types:

| Port Data Type | Name | Direction | Kind | Usage |
| --- | --- | --- | --- | --- |
| [`Drv::AdcRead`]() | Read_ADC | Input | Sync | Sends ADC reading to components which use them |

### 3.2 Functional Description

The ATmega Internal ADC component reads a channel of the ATmega ADC when polled and returns the counts from that channel. If the conversion takes too long, it will return a negative count value and an error code `Drv::AdcStatus::CONVERSION_TIMEOUT`

### 3.4 State

`Drv::ATmegaInternalAdcDriverComponentImpl` has no state machine.

### 3.5 Algorithms

`Drv::ATmegaInternalAdcDriverComponentImpl` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](ATmegaInternalAdcDriverComponentImpl.html) [MD](ATmegaInternalAdcDriver.md)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/DrvATmegaInternalAdcDriverComponentImpl_gcov.txt)

[Coverage Output - `Drv::ATmegaInternalAdcDriverComponentImpl.cpp`](../test/ut/output/ATmegaInternalAdcDriverComponentImpl.cpp.gcov)

[Coverage Output - `ATmegaInternalAdcDriverComponentAc.cpp`](../test/ut/output/ATmegaInternalAdcDriverComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
10/25/2020 | Initial Component Design



