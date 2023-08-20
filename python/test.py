#!/usr/bin/python3

import libpico
import time

if __name__ == "__main__":
    picoboard = libpico.PicoBoard("/dev/ttyUSB0")
    while True:
        scratch_data = picoboard.read_scratch_data()
        print(scratch_data)
        time.sleep(0.1)
