#include "simple_gesture_detector.h"

int main(void)
{
    // HAL_Init();
    // SystemClock_Config();
    // IMU_Init(&peripheralHandler);
    
    // Initialize the gesture detection state
    GestureDetectionStateTypeDef gestureState;
    init_gesture_detection(&gestureState);

    while (1)
    {
        // Get timestamp e.g. HAL_GetTick()
        uint32_t timestamp;

        // Read sensor data and calculate angles (replace with actual values)
        float x_angle, y_angle, z_angle;

        if(detect_gesture(&gestureState, x_angle, y_angle, z_angle, timestamp))
        {
            // Valid "V" gesture detected, Perform an action
        }
    }

    // delay 100ms
}