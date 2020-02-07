#include "tmp125_driver.h"
#include "gpio_lib.h"

#include <stdio.h>
#include <math.h>

/* Description: Provide any initialization of the library
   Paremeters: none
   Returns: int32_t indicating status of the init operation (0=success, anything else indicates an
            error code) */
int32_t tmp125_init(void) {
    uint32_t status = 0;

    // configure clock (pin 0) and chip select pins for 4 temp sensors (pins 1-4)
    uint8_t i;
    for(i=0; i < 5; i++) if((status = gpio_set_direction(0, i, OUTPUT_DIR)) != 0) goto out;
    
    // set clock to logic level high (idle)
    if((status = gpio_write_pin(PORT_ID, CLOCK_PIN, 1)) != LOGIC_LOW) goto out;

    // set chip select to logic level high (deselected)
    for(i=1; i < 5; i++) if((status = gpio_write_pin(0, i, LOGIC_HIGH)) != 0) goto out;
    
    // configure MOSI pin for master -> slave communication (pin 6)
    if((status = gpio_set_direction(PORT_ID, MOSI_PIN, OUTPUT_DIR)) != 0) goto out;

    // set MOSI to logic level low
    if((status = gpio_write_pin(PORT_ID, i, LOGIC_LOW)) != 0) goto out;

    // configure MISO pin for slave -> master communication (pin 7)
    if((status = gpio_set_direction(PORT_ID, MISO_PIN, INPUT_DIR)) != 0) goto out;

    printf("Info: successfully initialized driver to communicate with 4 TMP125 Temperature Sensors\r\n");

out:
    return(status);

}

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c){
    uint32_t status = 0;
    uint8_t pin_state[16];

    // use chip select to determine what temperature sensor to read data from
    if((status = select_chip(temp_sensor_id)) != 0) goto out;

    uint8_t i;
    for(i=0; i < 16; i++) {
        // set clock to logic low to prepare for read
        if((status = gpio_write_pin(PORT_ID, CLOCK_PIN, LOGIC_LOW)) != 0) goto out;

        // read bit from MISO pin
        if((status = gpio_read_pin(PORT_ID, MISO_PIN, &pin_state[i])) != 0) goto out;

        // reset clock to logic high to prepare for next read
        if((status = gpio_write_pin(PORT_ID, CLOCK_PIN, LOGIC_HIGH)) != 0) goto out;
    }

    // convert binary data from pin_state to a float value
    convert_binary_to_float(pin_state, p_temp_in_degrees_c);

    // deselect temperature sensor
    if((status = deselect_chip(temp_sensor_id)) != 0) goto out;

out:
    return(status);
}

/* Description: Select which temperature sensor to read data from
   Parameters: temp_sensor_id-the id of the temp sensor to select (from 1 to 4)
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t select_chip(uint8_t temp_sensor_id) {
    uint32_t status = 0;

    if(temp_sensor_id < 1 || temp_sensor_id > 4) {
        printf("Error: invalid temperature sensor number %d, select a sensor (1-4)\r\n", temp_sensor_id);
        status = -1;
        goto out;
    }

    if((status = gpio_write_pin(PORT_ID, temp_sensor_id, 0)) != 0) goto out;

    printf("Info: successfully selected temperature sensor %d to monitor\r\n", temp_sensor_id);

out:
    return(status);
}

/* Description: Deselect a temperature sensor
   Parameters: temp_sensor_id-the id of the temp sensor to deselect (from 1 to 4)
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t deselect_chip(uint8_t temp_sensor_id) {
    uint32_t status = 0;

    if(temp_sensor_id < 1 || temp_sensor_id > 4) {
        printf("Error: invalid temperature sensor number %d, select a sensor (1-4)\r\n", temp_sensor_id);
        status = -1;
        goto out;
    }

    if((status = gpio_write_pin(PORT_ID, temp_sensor_id, 1)) != 0) goto out;

    printf("Info: successfully deselected temperature sensor %d\r\n", temp_sensor_id);

out:
    return(status);
}

/* Description: Convert binary data from sensor to float value
   Parameters: pin_state-array of integer data, p_temp_in_degrees_c-apointerto a float
               where the temperature will be written
   Returns: None */
void convert_binary_to_float(uint8_t pin_state[16], float* p_temp_in_degrees_c) {
    uint8_t sign = pin_state[0];
    uint8_t i;
    int8_t exp = 7;
    float temp_val = 0;

    for(i=1; i < (exp+1); i++) {
        temp_val+=(pin_state[i]*(float)(pow(2, (exp-i))));
    }

    exp = -1;
    for(i=8; i<10; i++) {
        temp_val+=(pin_state[i]*(float)(pow(2, exp--)));
    }

    if(sign == 1) *p_temp_in_degrees_c = -128 + temp_val;
    else *p_temp_in_degrees_c = temp_val;
}