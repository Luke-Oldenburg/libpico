// C headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

// libpico headers
#include "libpico.h"

char SCRATCH_DATA_REQUEST = 0x01;

int request_scratch_packet(char *port, struct scratch_packet *packet)
{
    // open serial port
    int serial_port = open(port, O_RDWR);
    if (serial_port < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }

    // set baud rate
    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }
    cfsetspeed(&tty, B38400);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    // send request
    write(serial_port, &SCRATCH_DATA_REQUEST, 1);

    // read response
    char read_buf[RESPONSE_LENGTH];
    read(serial_port, &read_buf, RESPONSE_LENGTH);

    // parse packets
    for (int i = 0; i < RESPONSE_LENGTH; i += 2)
    {
        int channel = (read_buf[i] >> 3) - 16;
        int value = ((read_buf[i] & 7) << 7) | read_buf[i + 1];
        switch (channel)
        {
        case 15:
            packet->id.channel = channel;
            packet->id.value = value;
            break;
        case 0:
            packet->rd.channel = channel;
            packet->rd.value = value;
            break;
        case 1:
            packet->rc.channel = channel;
            packet->rc.value = value;
            break;
        case 2:
            packet->rb.channel = channel;
            packet->rb.value = value;
            break;
        case 3:
            packet->button.channel = channel;
            packet->button.value = value;
            break;
        case 4:
            packet->ra.channel = channel;
            packet->ra.value = value;
            break;
        case 5:
            packet->light.channel = channel;
            packet->light.value = value;
            break;
        case 6:
            packet->sound.channel = channel;
            packet->sound.value = value;
            break;
        case 7:
            packet->slider.channel = channel;
            packet->slider.value = value;
            break;
        }
    }

    // close serial port
    close(serial_port);
    return 0;
}