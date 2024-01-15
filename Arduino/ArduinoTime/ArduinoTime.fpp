module Arduino {
    @ A component for getting time
    passive component ArduinoTime {

        @ Port to retrieve time
        sync input port timeGetPort: Fw.Time

    }
}