// definitions
#define RESPONSE_LENGTH 18

// constants
extern char SCRATCH_DATA_REQUEST;

// structs
struct scratch_data_field
{
    int channel;
    int value;
};

struct scratch_packet
{
    struct scratch_data_field id;
    struct scratch_data_field rd;
    struct scratch_data_field rc;
    struct scratch_data_field rb;
    struct scratch_data_field button;
    struct scratch_data_field ra;
    struct scratch_data_field light;
    struct scratch_data_field sound;
    struct scratch_data_field slider;
};

// function prototypes
int request_scratch_packet(char *port, struct scratch_packet *packet);