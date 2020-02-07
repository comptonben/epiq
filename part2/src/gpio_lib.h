#pragma once

#include <stdint.h>

/* Description: set the GPIO direction for the specified GPIO pin pin_id on GPIO port port_id.
   Parameters: dir=0 indicates output, dir=1 indicates input.
   Returns: int32_t indicating status (0=success, otherwise an error code) */
int32_t gpio_set_direction(uint8_t port_id, uint8_t pin_id, uint8_t dir);

/* Description: reads the pin value for the specified GPIO pin pin_id on GPIO port port_id.
   Parameters: port_id is the ID of the GPIO port, pin_id is the value from 0-7, and pin_state=0 for a
               logic level low, pin_state=1 for a logic level high
   Returns: int32_t indicating status (0=success, otherwise an error code) */
int32_t gpio_read_pin(uint8_t port_id, uint8_t pin_id, uint8_t* p_pin_state);

/* Description: writes the pin value for the specified GPIO pin pin_id on GPIO port port_id.
   Parameters: port_id is the id of the GPIO port, pin_id is the value from 0-7, and pin_state=0 for a 
   logic level low, pin_state=1 for logic level high
   Returns: int32_t indicating status (0=success, otherswise an error code) */
int32_t gpio_write_pin(uint8_t port_id, uint8_t pin_id, uint8_t pin_state);