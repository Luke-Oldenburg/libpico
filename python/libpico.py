import serial
import struct

_BAUDRATE = 38400
_SCRATCH_DATA_REQUEST = 0x01
_RESPONSE_LENGTH = 18
_CHANNEL_NAMES = {
    15: "ID",
    0: "RD",
    1: "RC",
    2: "RB",
    3: "BUTTON",
    4: "RA",
    5: "LIGHT",
    6: "SOUND",
    7: "SLIDER"
}


class PicoBoard:
    def __init__(self, port):
        self.serial_port = serial.Serial(port, _BAUDRATE)

    def request_scratch_data(self):
        self.serial_port.write(struct.pack('B', _SCRATCH_DATA_REQUEST))

    def read_scratch_data(self):
        self.request_scratch_data()
        # default values in case the board has an error
        scratch_data = {
            "ID": 0x04,
            "RD": 1023,
            "RC": 1023,
            "RB": 1023,
            "BUTTON": False,
            "RA": 1023,
            "LIGHT": 1023,
            "SOUND": 1023,
            "SLIDER": 1023
        }
        raw_data = b''
        raw_data = self.serial_port.read(_RESPONSE_LENGTH)

        for x in range(0, len(raw_data), 2):
            # parse packet
            channel = (raw_data[x] >> 3) - 16
            value = (raw_data[x] & 7) << 7 | raw_data[x + 1]

            # handle button state
            if channel == 3:
                value = value_to_bool(value)

            try:
                scratch_data[_CHANNEL_NAMES[channel]] = value

            except KeyError:
                print("Board error.")

        return scratch_data

    def close(self):
        self.serial_port.close()


def value_to_bool(value):
    if value == 1023:
        return False

    elif value == 0:
        return True

    else:
        return None
