// collision detection

/*
 * NOTES:
 * goes forward 2m until collision is detected, then if sensor left is pressed spin to the right 90 degrees, if right is pressed spin 90 to the left.
 * if both sensors are pressed attempt to move right, then keep going for 2 meters
 *
 */
/*
 * part4.c
 *
 *  Created on: Sep 8, 2026
 *      Author: jackbyb
 */


#include "movement.h"
#include "open_interface.h"
#include <stdlib.h>

void turn(oi_t*sensor, int degrees) {
    

    int sum = 0;

    //left wheel, right wheel
    //left = forward ; right = backward
    if (degrees > 0) {
        oi_setWheels(-15, 15);
    }
    else {
    oi_setWheels(-15, 15);
    }

    while (abs(sum) < abs(degrees)){
        oi_update(sensor);
        sum+= sensor->angle;


    }
    oi_setWheels(0,0);
//    oi_free(0,0);
}


void move(oi_t*sensor,int centimeters){

    double sum = 0;
    oi_setWheels(250,250);
     //Creates a variable to keep track of how far the robot has traveled.

         //Tells both wheels to go forward at 500 mm/s.
         //positive = forward ; max = 500mm/s


           while (sum < centimeters){

               oi_update(sensor); // get current state of all sensors
                if (sensor->bumpRight || sensor->bumpLeft) {
                   // back up and turn left
                   int degrees = 0;
                  if (sensor->bumpLeft && sensor->bumpRight) {
                degrees = -90; 
            } 
            else if (sensor->bumpLeft) {
                degrees = -90; 
            } 
            else if (sensor->bumpRight) {
                degrees = 90;  
            }

            oi_setWheels(-15, -15);
            double back_sum = 0;
            while (abs(back_sum) < 150) {
                oi_update(sensor);
                back_sum += sensor->distance; 
            }
            turn(sensor, degrees);

          
            oi_setWheels(250, 250);
        }
        sum += sensor->distance;
    }
    oi_setWheels(0, 0);
}

