#include "../src/tmp125_driver.h"
#include <gtest/gtest.h>
#include <stdio.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(tmp125_driver, test_init_is_successful) {
    testing::internal::CaptureStdout();
    uint32_t result = tmp125_init();
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
}

TEST(tmp125_driver, test_read_temp_fails_when_sensor_value_out_of_bounds) {
    uint8_t sensor = 6;
    float value = 0;
    testing::internal::CaptureStdout();
    uint32_t result = tmp125_read_temp(sensor, &value);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, -1);
}

TEST(tmp125_driver, test_read_temp_is_successful) {
    uint8_t sensor = 2;
    float value = 0;
    testing::internal::CaptureStdout();
    uint32_t result = tmp125_read_temp(sensor, &value);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
}

TEST(tmp125_driver, test_select_chip_fails_when_sensor_value_out_of_bounds) {
    uint8_t sensor = 6;
    testing::internal::CaptureStdout();
    uint32_t result = select_chip(sensor);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, -1);
}

TEST(tmp125_driver, test_select_chip_is_successful) {
    uint8_t sensor = 2;
    testing::internal::CaptureStdout();
    uint32_t result = select_chip(sensor);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
}

TEST(tmp125_driver, test_deselect_chip_fails_when_sensor_value_out_of_bounds) {
    uint8_t sensor = 6;
    testing::internal::CaptureStdout();
    uint32_t result = deselect_chip(sensor);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, -1);
}

TEST(tmp125_driver, test_deselect_chip_is_successful) {
    uint8_t sensor = 2;
    testing::internal::CaptureStdout();
    uint32_t result = deselect_chip(sensor);
    testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
}

TEST(tmp125_driver, test_binary_converter_can_convert_negative_number) {
    uint8_t pin_state[16] = {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    float temp_in_c;
    
    convert_binary_to_float(pin_state, &temp_in_c);

    EXPECT_FLOAT_EQ(temp_in_c, -85.75F);
}

TEST(tmp125_driver, test_binary_converter_can_convert_positive_number) {
    uint8_t pin_state[16] = {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};
    float temp_in_c;

    convert_binary_to_float(pin_state, &temp_in_c);

    EXPECT_FLOAT_EQ(temp_in_c, 102.75F);
}