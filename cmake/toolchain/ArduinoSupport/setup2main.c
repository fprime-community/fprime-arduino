/**
 * setup2main.c:
 *
 * This file unwraps Arduino's setup and loop functions and calls the main function instead. This fixes the undefined
 * errors with teensyduino teensy4 as it does not call main.
 */
void setup() {
    main();
}
void loop() {}