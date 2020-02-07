#include <functional>
#include <string>
#include <stdint.h>

/* Description: Output platform temperature manager header
   Parameters: None
   Returns: None */
void dump_header();

/* Description: Spawn an interval based thread to check temperature sensor
                for current alarming temoerature readings
   Parameters: func-a function pointer to check temperatures, interval-interval
               in which to call temperature checking function
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t interval_interrupt(std::function<int32_t(void)> func, int interval);

/* Description: trigger alarms for temperatures outside of a standard range or
                if temperature is checked asynchronously.
   Parameters: sensor-sensor that triggered alarm (1-4), alarm_code-code that was
               triggered ("low", "high", "async"), temp-temperature that triggered
               the alarm
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t trigger_alarm(int sensor, std::string alarm_code, float temp);

/* Description: post alarms to online alarms log
   Parameters: sensor-sensor that triggered alarm (1-4), alarm_code-code that was
               triggered ("low", "high", "async"), temp-temperature that triggered
               the alarm, dt-datetime stamp of when alarm was triggered
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t post_alarm(int sensor, std::string alarm_code, float temp, std::string dt);

/* Description: function to be used as a pointer for interval temperature sensor monitoring
   Parameters: None
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t check_temps();

/* Description: Asynchronously read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees);

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);