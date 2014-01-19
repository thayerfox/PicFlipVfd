#include "temperatureSensor.h"
#include "spi.h"

signed int convertTemperature(signed int temperature);

void initTemperatureSensor() {
    CS_TRIS = 0;
    DESELECT;
}

signed int readTemperature() {
    signed int temperature;
    SELECT;
    temperature = readSpi() << 8;
    temperature |= readSpi();
    DESELECT;
    return convertTemperature(temperature);
}

signed int convertTemperature(signed int temperature) {
    temperature = temperature >> 4;

    if (temperature & 0x0700) {
        temperature |= 0xF000;
    } else {
        temperature &= 0x0FFF;
    }
    temperature = temperature >> 3;
    return temperature;
}
