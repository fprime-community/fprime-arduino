# ATmega Assert Reset Component

## 1. Introduction

Reset the ATmega via the internal watchdog timer after a FW_ASSERT().

## 2. Requirements

The requirements for `ATmega::AssertResetComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
AR-001 | The `ATmega::AssertResetComponent` component shall capture ``FW_ASSERT()`` calls | Inspection
AR-002 | The `ATmega::AssertResetComponent` component shall reset the ATmega upon recieving ``FW_ASSERT`` | Inspection
AR-003 | The `ATmega::AssertResetComponent` component shall print the file (or hash) and line number before the reset | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `ATmega::AssertResetComponent` component has the following component diagram:

![`ATmega::AssertResetComponent` Diagram](img/AssertResetComponentBDD.jpg "ATmega::AssertResetComponent")

#### 3.1.2 Ports

The `ATmega::AssertResetComponent` component has no ports.

### 3.2 Functional Description

This component registers itself as the ``FW_ASSERT()`` handler.
When an ``FW_ASSERT()`` occurs, it will print the line number and the file where the assert occured.

### 3.3 Scenarios

#### 3.3.1 FATAL Notification

The `ATmega::AssertResetComponent` handles FATAL notifications from the framework, triggering a system watchdog reset.

### 3.4 State

`ATmega::AssertResetComponent` has no state machines.

### 3.5 Algorithms

The time `ATmega::AssertResetComponent` it takes for the internal ATmega watchdog to expire can be adjusted.
By default, the timer will expire in 500 milliseconds.
Defining ``FATAL_WD_TIME`` as a compilation symbol will override this time, just be sure to choose a valid time from ``<avr/wdt.h>``.
Flight projects may want this to expire very fast, or may want to leave enough time for some radio packet to get out.

## 4. Dictionary

Dictionaries: [HTML](AssertResetComponent.html) [MD](AssertReset.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/ATmegaAssertResetComponent_gcov.txt)

[Coverage Output - `ATmega::AssertResetComponent.cpp`](../test/ut/output/AssertResetComponent.cpp.gcov)

[Coverage Output - `AssertResetComponentAc.cpp`](../test/ut/output/AssertResetComponentAc.cpp.gcov)

## 6. Change Log

Date | Description
---- | -----------
10/05/2020 | Component Update from cookiecutter template.
09/05/2020 | Initial component design.



