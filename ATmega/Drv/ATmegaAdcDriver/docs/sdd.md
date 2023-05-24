# ATMega ADC Driver Component

## 1. Introduction

Reads multiple ADC channels from an ATmega microcontroller.

## 2. Requirements

The requirements for `Drv::ATMegaAdcDriverComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
CC-001 | The `Drv::ATMegaAdcDriverComponent` configures ATMega ADC registers. | Run on hardware MCU
CC-002 | The `Drv::ATMegaAdcDriverComponent` reads multiple ADC channels and multiplies them each by a gain specified at init. | Run on hardware MCU
CC-003 | The `Drv::ATMegaAdcDriverComponent` reports both the raw and gained ADC channel values in telemetry. | Unit test
CC-004 | The `Drv::ATMegaAdcDriverComponent` outputs the gained ADC channel values to another component. | Unit test

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Drv::ATMegaAdcDriverComponent` component has no component diagram.

#### 3.1.2 Ports

The `Drv::ATMegaAdcDriverComponent` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
[`Svc::Sched`](../../Svc/Sched/docs/sdd.html) | tlmSched | Input | Synch | Call to read channels and update telemetry
[`Drv::U16Array`] | Report | Output | | Output port for ADC channel gained readings

### 3.2 Functional Description

The component may be initialized with any number of ADC channels, each with a specified integer gain. At each call to
tlmSched, all channels are read, gains are applied, telemetry fields are updated, and the channels are output to the
Report port. 

### 3.3 Scenarios

`Drv::ATMegaAdcDriverComponent` has no scenarios.

### 3.4 State

`Drv::ATMegaAdcDriverComponent` has no state machines.

### 3.5 Algorithms

`Drv::ATMegaAdcDriverComponent` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](ATMegaAdcDriverComponent.html) [MD](ATMegaAdcDriverComponent.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/DrvATMegaAdcDriverComponent_gcov.txt)

[Coverage Output - `ATMegaAdcDriverComponentImpl.cpp`](../test/ut/output/ATMegaAdcDriverComponentImpl.cpp.gcov)

[Coverage Output - `ATMegaAdcDriverComponentComponentAc.cpp`](../test/ut/output/ATMegaAdcDriverComponentComponentAc.cpp.gcov)

## 6. Change Log

Date | Description
---- | -----------
09/06/2020 | Initial Component Design



