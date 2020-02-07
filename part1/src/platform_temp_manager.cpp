#include "platform_temp_manager.h"

#include <chrono>
#include <cstdint>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

int main(int argc, char* argv[]) {
    dump_header();
    
    uint8_t status = 0;
    status = interval_interrupt(check_temps, 500);

    return(status);
}

/* Description: Output platform temperature manager header
   Parameters: None
   Returns: None */
void dump_header() {
    std::string welcome = "Starting Temperature Management Application\n";
    std::cout << welcome << std::string(welcome.length(),'=') << std::endl << std::endl;
}

/* Description: Spawn an interval based thread to check temperature sensor
                for current alarming temoerature readings
   Parameters: func-a function pointer to check temperatures, interval-interval
               in which to call temperature checking function
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t interval_interrupt(std::function<int32_t(void)> func, int interval) {
    int32_t status = 0;
    std::thread t([func, interval, &status]() {
        while(true) {
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            if((status = func()) != 0) break;
            std::this_thread::sleep_until(x);
        }
    });
    t.join();
    return status;
}

/* Description: trigger alarms for temperatures outside of a standard range or
                if temperature is checked asynchronously.
   Parameters: sensor-sensor that triggered alarm (1-4), alarm_code-code that was
               triggered ("low", "high", "async"), temp-temperature that triggered
               the alarm
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t trigger_alarm(int sensor, std::string alarm_code, float temp) {
    int32_t status = 0;

    time_t cur_dt = time(0);
    std::string dt = ctime(&cur_dt);

    if((status = post_alarm(sensor, alarm_code, temp, dt)) != 0) goto out;

    std::cout << "ALARM - Temperature sensor " << sensor;
    if (alarm_code == "low") std::cout << " has a temperature below threshold at: ";
    else if (alarm_code == "high") std::cout << " has a temperature above threshold at: ";
    else if (alarm_code == "async") std::cout << " has a temperature within threshold at: ";
    std::cout << temp << " C" << std::endl << "|\tAlarm datetime: " << dt << std::endl << std::endl;

out:
    return status;
}

/* Description: post alarms to online alarms log
   Parameters: sensor-sensor that triggered alarm (1-4), alarm_code-code that was
               triggered ("low", "high", "async"), temp-temperature that triggered
               the alarm, dt-datetime stamp of when alarm was triggered
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t post_alarm(int sensor, std::string alarm_code, float temp, std::string dt) {
    int32_t status = 0;

    std::stringstream ss;
    ss << "[ALARM - Temperature sensor " << sensor;
    if (alarm_code == "low") ss << " has a temperature below threshold at: ";
    else if (alarm_code == "high") ss << " has a temperature above threshold at: ";
    else if (alarm_code == "async") ss << " has a temperature within threshold at: ";
    ss << temp << " C | Alarm datetime: " << dt.substr(0, (dt.length()-1)) << "]\r\n";
    std::string alarm = ss.str();

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/plain");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, "https://epiq-code-challenge.000webhostapp.com/api/post.php");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, alarm.c_str());

        res = curl_easy_perform(curl);
        if(res) {
            printf("Error: curl operation failed\r\n");
            status = -2;
        }
    }
    else {
        printf("Error: curl object initialization failed\r\n");
        status = -1;
    }
    curl_easy_cleanup(curl);

    return status;
}

/* Description: function to be used as a pointer for interval temperature sensor monitoring
   Parameters: None
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t check_temps() {
    int32_t status = 0;
    float temp;

    for(uint8_t i=1; i < 5; i++) {
        if((status = tmp125_read_temp(i, &temp)) != 0) goto out;
        else {
            if(temp < -40.0) {
                trigger_alarm(i, "low", temp);
            }
            else if(temp > 85.0) {
                trigger_alarm(i, "high", temp);
            }
        }
    }

out:
    return status;
}

/* Description: Asynchronously read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees) {
    int32_t status = 0;
    if((status = tmp125_read_temp(temp_sensor_id, p_temp_in_degrees)) != 0) goto out;
    else {
        if(*p_temp_in_degrees < -40.0) trigger_alarm(temp_sensor_id, "low", *p_temp_in_degrees);
        else if(*p_temp_in_degrees > 85.0) trigger_alarm(temp_sensor_id, "high", *p_temp_in_degrees);
        else trigger_alarm(temp_sensor_id, "async", *p_temp_in_degrees);
    }

out:
    return status;
}

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c) {
    float mock_data[10] = {10.6, -89.3, -32.9, 50.7, 128.9, 12.4, 85.0, -40.0, 85.1, -40.1};
    *p_temp_in_degrees_c = mock_data[rand() % 10];
    return 0;
}