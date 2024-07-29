module Arduino {
    @ LED indicating software life.
    passive component LifeLed {
        @ LED period in units of rate group ticks
        param LED_PERIOD: U16 default 10

        @ Rate group port 
        guarded input port run: Svc.Sched  

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

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
