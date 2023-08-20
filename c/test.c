#include <stdio.h>
#include "libpico.h"

int main(void)
{
    struct scratch_packet packet;
    request_scratch_packet("/dev/ttyUSB0", &packet);
    printf("ID: %d\n", packet.id.value);
    printf("RD: %d\n", packet.rd.value);
    printf("RC: %d\n", packet.rc.value);
    printf("RB: %d\n", packet.rb.value);
    printf("Button: %d\n", packet.button.value);
    printf("RA: %d\n", packet.ra.value);
    printf("Light: %d\n", packet.light.value);
    printf("Sound: %d\n", packet.sound.value);
    printf("Slider: %d\n", packet.slider.value);
}