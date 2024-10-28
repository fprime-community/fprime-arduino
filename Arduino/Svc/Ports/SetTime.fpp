module Arduino {
    @ Port allowing a component to set the time
    port SetTime(
        year:  U32, @< The current year
        month: U8,  @< The current month (1-12)
        day: U8,    @< The current day (1-31)
        hour: U8,   @< The current hour (0-23)
        minute: U8, @< The current minute (0-59)
        second: U8, @< The current second (0-59)
    )
}