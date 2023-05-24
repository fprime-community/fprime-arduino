#  ATmega I2C Driver Component

## 1. Introduction

I2C driver for operating the I2C bus on an ATmega hardware platform (such as ATmega128).

## 2. Requirements

The requirements for `Drv::ATmegaI2cDriverComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
AT-I2C-001 | The `Drv::ATmegaI2cDriverComponent` component accepts I2cReadWrite requests and performs an I2C transaction | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Drv::ATmegaI2cDriverComponent` component has the following component diagram:

![`Drv::ATmegaI2cDriverComponent` Diagram](img/ATmegaI2cDriverComponentBDD.jpg "Drv::ATmegaI2cDriverComponent")

#### 3.1.2 Ports

The `Drv::ATmegaI2cDriverComponent` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----
[`Drv::I2cWriteRead`](../I2cDriverPorts/docs/sdd.html) | i2cTransaction | Input | Sync | Transaction buffer pair for sending and recieving I2C data

### 3.2 Functional Description

This component takes the data in the I2C write buffer, and writes it to the I2C port.  Then data read back from the device is placed in the read buffer, and the component's work is done.

### 3.3 Scenarios

`Drv::ATmegaI2cDriverComponent` has no significant scenarios.

### 3.4 State

`Drv::ATmegaI2cDriverComponent` has no state machines (or does it?).

### 3.5 Algorithms

`Drv::ATmegaI2cDriverComponent` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](ATmegaI2cDriverComponent.html) [MD](ATmegaI2cDriverComponent.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/DrvATmegaI2cDriverComponent_gcov.txt)

[Coverage Output - `ATmegaI2cDriverComponent.cpp`](../test/ut/output/ATmegaI2cDriverComponent.cpp.gcov)

[Coverage Output - `ATmegaI2cDriverComponentComponentAc.cpp`](../test/ut/output/ATmegaI2cDriverComponentComponentAc.cpp.gcov)

## 6. Change Log

Date | Description
---- | -----------
08/17/2020 | Documentation updates and restructuring to better support ``fprime-util`` usage
12/20/2019 | Initial Component Design



