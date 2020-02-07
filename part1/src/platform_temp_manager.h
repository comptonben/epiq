#include <functional>
#include <string>
#include <stdint.h>

void dump_header();
void interval_interrupt(std::function<void(void)> func, int interval);
void print_alarm(int sensor, std::string alarm_code, float temp);
uint32_t post_alarm(int sensor, float temp, std::string dt);
void sig_handler(int signal);
uint32_t check_temps();

/* Description: Asynchronously read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
uint32_t PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees);

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
uint32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);