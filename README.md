# Curve-Line-Follower-bot

This bot works on the principles of computer vision and PID controller. It detects a black path (preferably over white background) using a smart phone camera and traverses on it. 
The path is captured using a smartphone camera (or any small camera module) and detected using the OpenCV library in Python whereas the PID controller is implemented using Arduino UNO.
The motors are made to work using an L298N motor driver.
The path is detected using contour detection method and deviation from the path is calculated as an error. This error is then worked upon to determine whether the bot should move straight, turn left or turn right.
