# ATmega Internal EEPROM Parameter Database Component

## 1. Introduction

Parameter database for storing changes that persist across reboots, in the ATmega internal EEPROM.

This component saves parameters for use between reboots.
It implements the GetPrm and SetPrm ports, which are exposed by the autocoded parameter interface in F Prime.
For the ATmega platform, the values are saved in a database that is constructed within the onboard EEPROM.

## 2. Requirements

The requirements for `ATmega::EePrmDbComponentImpl` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
EPD-001 | The `ATmega::EePrmDbComponentImpl` component shall store parameters in the ATmega's onboard EEPROM | Inspection
EPD-002 | The `ATmega::EePrmDbComponentImpl` component shall store parameter values of size 4 bytes or smaller | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `ATmega::EePrmDbComponentImpl` component has the following component diagram (Diagram not available yet):

![`ATmega::EePrmDbComponentImpl` Diagram](img/EePrmDbComponentImplBDD.jpg "ATmega::EePrmDbComponentImpl")

#### 3.1.2 Ports

The `ATmega::EePrmDbComponentImpl` component uses the following port types:

| Port Data Type | Name | Direction | Kind | Usage |
| --- | --- | --- | --- | --- |
| [`Fw::PrmGet`](../../Fw/Prm/docs/sdd.md) | getPrm | Input | Guarded | Port to get parameter values |
| [`Fw::PrmSet`](../../Fw/Prm/docs/sdd.md) | setPrm | Input | Sync | Port to update parameters |

### 3.2 Functional Description

The EEPROM on the ATmega is logicially divided up (by the component, not some hardware construct) into slots.
These slots are of length 8 by default.
The first 3 bytes are used as metadata to denote the parameter ID stored in the slot, and the length of the data stored in the slot.

If the parameter that is requesting storage in the DB is bigger than the slot size, an assert will be triggered.

Parameters are stored at the begining of the allocated EEPROM range, and in sequentially larger slot addresses until the allocated range is full.
The storage order is determined by the relative order of when a calling component asks for a parameter to be saved.
This means that loading parameters from the database is order O(N), and loading all parameters is O(N^2/2), where N is the number of parameters stored in the database.
This should not be problematic, because N will always be bounded by the physical EEPROM size, which is rather small.

### 3.3 Scenarios

`ATmega::EePrmDbComponentImpl` has no significant scenarios.

### 3.4 State

`ATmega::EePrmDbComponentImpl` has no state machines.

### 3.5 Algorithms

`ATmega::EePrmDbComponentImpl` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](EePrmDbComponentImpl.html) [MD](EePrmDb.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/ATmegaEePrmDbComponentImpl_gcov.txt)

[Coverage Output - `ATmega::EePrmDbComponentImpl.cpp`](../test/ut/output/EePrmDbComponentImpl.cpp.gcov)

[Coverage Output - `EePrmDbComponentAc.cpp`](../test/ut/output/EePrmDbComponentAc.cpp.gcov)

## 6. Change Log

Date | Description
---- | -----------
09/01/2020 | Initial Component Design



