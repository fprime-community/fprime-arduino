# ATmega Time Component

## 1. Introduction

Provides Time reference via Arduino time functions.

## 2. Requirements

The requirements for `Svc::ATmegaTimeComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
CC-001 | The `Svc::ATmegaTimeComponent` component provides time reference | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Svc::ATmegaTimeComponent` component has the following component diagram:

![`Svc::ATmegaTimeComponent` Diagram](img/ATmegaTimeComponentBDD.jpg "Svc::ATmegaTimeComponent")

#### 3.1.2 Ports

The `Svc::ATmegaTimeComponent` component uses the following port types:

Port Data Type | Name | Direction | Kind | Usage
-------------- | ---- | --------- | ---- | -----

### 3.2 Functional Description

This component provides the deployment time reference, sometimes referred to
as Spacecraft Time.  It does so by using the build in Arduino Millis/Micros
functions, and thus will roll over over 49 days.

## 4. Dictionary

Dictionaries: [HTML](ATmegaTimeComponent.html) [MD](ATmegaTime.md)

## 4. Module Checklists

Document            | Link
------------------- | ----
Design Checklist    | [Link](Checklist_Design.xlsx)
Code Checklist      | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/SvcATmegaTimeComponent_gcov.txt)

[Coverage Output - `Svc::ATmegaTimeComponent.cpp`](../test/ut/output/ATmegaTimeComponent.cpp.gcov)

[Coverage Output - `ATmegaTimeComponentAc.cpp`](../test/ut/output/ATmegaTimeComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
10/13/2021 | Initial Component Design



