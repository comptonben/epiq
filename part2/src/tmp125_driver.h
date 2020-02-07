#pragma once

#include <stdint.h>

#define OUTPUT_DIR 0
#define INPUT_DIR 1
#define LOGIC_LOW 0
#define LOGIC_HIGH 1
#define PORT_ID 0
#define CLOCK_PIN 0
#define MOSI_PIN 6
#define MISO_PIN 7

/* Description: Provide any initialization of the library
   Paremeters: none
   Returns: int32_t indicating status of the init operation (0=success, anything else indicates an
            error code) */
int32_t tmp125_init(void);

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);

/* Description: Select which temperature sensor to read data from
   Parameters: temp_sensor_id-the id of the temp sensor to select (from 1 to 4)
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t select_chip(uint8_t temp_sensor_id);

/* Description: Deselect a temperature sensor
   Parameters: temp_sensor_id-the id of the temp sensor to deselect (from 1 to 4)
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t deselect_chip(uint8_t temp_sensor_id);

/* Description: Convert binary data from sensor to float value
   Parameters: pin_state-array of integer data, p_temp_in_degrees_c-apointerto a float
               where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
void convert_binary_to_float(uint8_t pin_state[16], float* p_temp_in_degrees_c);