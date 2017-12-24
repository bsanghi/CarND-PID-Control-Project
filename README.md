# CarND-PID-Control-Project

[image1]: ./images/ave_error.png "data1"

## Introduction

The purpose of this project was to "build a PID controller and tune the PID hyperparameters by applying the general processing flow as 
described in the lessons," and to "test your solution on the simulator!" The simulator provides cross-track error (CTE), speed, and 
steering angle data via local websocket. The PID (proportional/integral/differential) controller must respond with steering and throttle
 commands to drive the car reliably around the simulator track.

## Rubic Discussion Points

I have used PID controller with twiddle algorithm inside a state machine to optimize P,I, D parameters. The I part of the algorithm was 
ignored because there is no bias. But, i chose small value(0.001) for Ki. 

I lowered default throttle value to 0.2 and reduced more(0.1) when making turns so that it does not oversteer. 

I directly implemented the twiddle algorithm. But, I have to choose reasonable initial values for p and dp. 
Hyperparameters were tuned manually at first. This was necessary because the narrow track left little room for error.

I used 1260*3 steps(around 3 turns) for each iteration to calculate the average error because number of steps for one turns is not 
constant because each iteration has different parameters. By the comparing ave_error2=sum(cte*cte)/number of steps for each iteration, 
we calculated the optimial values. 
It takes almost hundred iterations to satisfy the condition(sum(dp) < 0.2 ) even we choose reasonable values for p.

![alt text][image1]

To run the twiddle optimization, you have to change the value of use_twiddle to True in PID.h. The default value is False.

The final values are :

Kp = 0.557702 , Ki=0.001 , Kd=2.86226

The video with the final parameter values :

[ pid video with the final parameters ](./final_video.mp4)

---

# **Original Udacity README**

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the
 appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v
0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

