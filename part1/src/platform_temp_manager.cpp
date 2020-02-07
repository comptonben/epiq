#include "platform_temp_manager.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    dump_header();
    
    interval_interrupt(check_temps, 500);
    return(0);
}

void dump_header() {
    std::string welcome = "Starting Temperature Management Application\n";
    std::cout << welcome << std::string(welcome.length(),'=') << std::endl << std::endl;
}

void interval_interrupt(std::function<void(void)> func, int interval) {
    std::thread t([func, interval]() {
        while(true) {
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            func();
            std::this_thread::sleep_until(x);
        }
    });
    t.join();
}

void print_alarm(int sensor, std::string alarm_code, float temp) {
    time_t cur_dt = time(0);
    std::string dt = ctime(&cur_dt);
    std::cout << "ALARM - Temperature sensor " << sensor;
    if (alarm_code == "low") std::cout << " has a temperature below threshold at: ";
    else if (alarm_code == "high") std::cout << " has a temperature above threshold at: ";
    std::cout << temp << " C" << std::endl << "|\tAlarm datetime: " << dt << std::endl << std::endl;
}

void print_temp(int sensor, float temp) {
    time_t cur_dt = time(0);
    std::string dt = ctime(&cur_dt);
    post_alarm(sensor, temp, dt);
    std::cout << "INFO - Temperature sensor " << sensor << " has a temperature within threshold at: ";
    std::cout << temp << " C" << std::endl << "|\tAlarm datetime: " << dt << std::endl << std::endl;
}

uint32_t post_alarm(int sensor, float temp, std::string dt) {
    uint32_t status = 0;

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    else {
        status = -1;
    }
    return status;
}

uint32_t check_temps() {
    uint32_t status = 0;
    float temp;

    for(uint8_t i=1; i < 5; i++) {
        if((status = tmp125_read_temp(i, &temp)) != 0) goto out;
        else {
            if(temp < -40.0) {
                print_alarm(i, "low", temp);
            }
            else if(temp > 85.0) {
                print_alarm(i, "high", temp);
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
uint32_t PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees) {
    uint32_t status = 0;
    if((status = tmp125_read_temp(temp_sensor_id, p_temp_in_degrees)) != 0) goto out;
    else {
        if(*p_temp_in_degrees < -40.0) print_alarm(temp_sensor_id, "low", *p_temp_in_degrees);
        else if(*p_temp_in_degrees > 85.0) print_alarm(temp_sensor_id, "high", *p_temp_in_degrees);
        else print_temp(temp_sensor_id, *p_temp_in_degrees);
    }

out:
    return status;
}

/* Description: Read the temperature of the requested temp sensor in degrees C
   Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)
               p_temp_in_degrees_c-apointerto a float where the temperature will be written
   Returns: int32_t indicating status (0=success, any other value indicates an error code) */
uint32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c) {
    float mock_data[10] = {10.6, -89.3, -32.9, 50.7, 128.9, 12.4, 85.0, -40.0, 85.1, -40.1};
    *p_temp_in_degrees_c = mock_data[rand() % 10];
    return 0;
}