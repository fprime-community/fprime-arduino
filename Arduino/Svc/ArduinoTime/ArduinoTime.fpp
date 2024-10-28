module Arduino {
    @ A component for getting time
    passive component ArduinoTime {

        @ Port to retrieve time
        sync input port getTime: Fw.Time

        @ Port to set the time
        sync input port setTime: Arduino.SetTime

        @ Command to set the time
        sync command SET_TIME(
                year:  U32, @< The current year
                month: U8,  @< The current month (1-12)
                day: U8,    @< The current day (1-31)
                hour: U8,   @< The current hour (0-23)
                minute: U8, @< The current minute (0-59)
                second: U8, @< The current second (0-59)
            )

        @ Command to set the time
        event TimeUpdate(
                original_seconds:      U32  @< The seconds before the time update
                original_microseconds: U32  @< The microseconds before the time update
                original_base:          U8  @< The time base before the update
                new_seconds:           U32  @< The seconds after the time update
                new_microseconds:      U32  @< The microseconds after the time update
                new_base:               U8  @< The time base adter the update
            ) severity activity high format "Time updated from {}.{} ({}) to {}.{} ({})"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################

        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut
    }
}