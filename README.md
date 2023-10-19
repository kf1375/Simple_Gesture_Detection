# Simple State Machine to detect "V" gesture

Assume:
    - rotation around X is Roll
    - rotation around Y is Pitch
    - rotation around Z is Yaw
    - CCW Rotation is posiive

According to the below frames for drawing a "V" we have a significant change
around X (Roll) and a little change around Y (Pitch). and the rotation around
Z (Yaw) actually does not matter in this scenario.

## Note: Rotational Center is the position on the pen that we grab from there.
                
C = [whatever X, whatever Y, h]

Z        

|            Y
|          /   . C (Rotational Center)
|        /    __ __ 
|      /    /     /
|    /    /  P  /
|  /    /__ __/
|/__ __ __ __ __ __  X

Y
        
|    ____________________
|   |   2-3 cm          |
|   |  \      /         | 
|   |   \   /  4-10 cm  | 
|   |    \/             |
|   ---------------------
|__ __ __ __ __ __ __  X

        
To have displacement in Y, we should rotate around X and to have displacement
in X, we should rotate around Y.

For drawing "V" the pen has the following orientation:
    - Step 1: At the beginning the roll and pitch both start to increase untilwe reach the lowest part of "V"
    - Step 2: Then for drawing the right side of "V"  the pitch still increases
            but the roll begins to orient in the opposite direction until we
            reach the ending point and the roll returns to the value of the
            angle at the starting point;
    - ## Note: the drawing duration is between 500ms to 2000ms.

Now we can implement the following rules with a state machine to detect "V" gestures.