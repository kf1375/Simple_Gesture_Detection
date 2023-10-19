#include "simple_gesture_detector.h"

float last_x = 0;
float last_y = 0;
float last_z = 0;


void init_gesture_detection(GestureDetectionStateTypeDef *state)
{
    state->state = 0;
    state->startTime = 0;
    state->endTime = 0;
    state->startOrientation.roll = 0;
    state->startOrientation.pitch = 0;
    state->startOrientation.yaw = 0;
}

uint8_t detect_gesture(GestureDetectionStateTypeDef *state, float x, float y, float z, uint32_t timestamp)
{
    switch (state->state)
    {
    case 0:
        // Check for starting point
        if(x + ANGLE_TOLERANCE > last_x && x - ANGLE_TOLERANCE > last_x &&
           y + ANGLE_TOLERANCE > last_y && x - ANGLE_TOLERANCE > last_y)
        {
            state->state = 1;
            state->startTime = timestamp;
            state->startOrientation.roll = x;
            state->startOrientation.pitch = y;
            state->startOrientation.yaw = z;
        }
        break;

    case 1:
        if(timestamp - state->startTime > DETECTION_DURATION_MAX_MS)
        {
            // Times up we should reset the state
            state->state = 0;
            break;
        }
        if(x + ANGLE_TOLERANCE < last_x && x - ANGLE_TOLERANCE < last_x &&
           y + ANGLE_TOLERANCE > last_y && x - ANGLE_TOLERANCE > last_y)
        {
            // We reach to the bottom and starting drawing the right side
            state->state = 2;
        }
        break;
    default:
        if(timestamp - state->startTime > DETECTION_DURATION_MAX_MS)
        {
            // Times up we should reset the state
            state->state = 0;
            break;
        }
        if(y > last_y + ANGLE_TOLERANCE && y > last_x - ANGLE_TOLERANCE &&
           x <= state->startOrientation.roll + ANGLE_TOLERANCE &&
           x >= state->startOrientation.roll - ANGLE_TOLERANCE)
        {
            state->endTime = timestamp;
            // Check if the gesture duration is within the desired range
            if(state->endTime - state->startTime >= DETECTION_DURATION_MIN_MS &&
               state->endTime - state->startTime <= DETECTION_DURATION_MAX_MS)
            {
                // The "V" gesture is detected
                return 1;
            }
            else
            {
                return 0;
            }
        }
        break;
    }

    last_x = x;
    last_y = y;
    last_z = z;

    return 0;
}