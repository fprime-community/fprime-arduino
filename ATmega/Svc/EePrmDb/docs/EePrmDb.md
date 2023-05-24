# ATmega Internal EEPROM Parameter Database Component Dictionary


## Command List

| Mnemonic | ID | Description | Arg Name | Arg Type | Comment |
| --- | --- | --- | --- | --- | --- |
| PARAMETER_FACTORY_RESET | 0 (0x0) | Reset all parameters to factory default values. |   |   |   |

## Telemetry Channel List

This component has no telemetry.

## Event List

| Event Name | ID | Description | Arg Name | Arg Type | Arg Size | Comment |
| --- | --- | --- | --- | --- | --- | --- |
| PrmIdNotFound | 0 (0x0) | Parameter ID not found in database. |   |   |   |   |
| PrmIdUpdated | 1 (0x1) | Parameter ID updated in database |   |   |   |   |
| PrmDbFull | 2 (0x2) | Parameter database is full |   |   |   |   |
| PrmIdAdded | 3 (0x3) | Parameter ID added to database |   |   |   |   |
| PrmFileWriteError | 4 (0x4) | Failed to write parameter file |   |   |   |   |
| PrmFileSaveComplete | 5 (0x5) | Save of parameter file completed |   |   |   |   |
| PrmFileReadError | 6 (0x6) | Failed to read parameter file |   |   |   |   |
| PrmFileLoadComplete | 7 (0x7) | Load of parameter file completed |   |   |   |   |
