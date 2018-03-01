# CSL290
COP 290 - Assignment 1
Screensaver of N balls
Abhishek Gupta           Akshit Kansra
2016CSJ0012              2016CSJ0001

Our main code is in 2016CSJ0001_2016CSJ0012 folder in MASTER BRANCH


1 Implementation

In this app, we are implementing a ’3-D Screensaver’ consisting of N balls. In
the app, you can change the velocities of balls, move in front and back, enable
gravity, and increase the number of balls. The software required for running the
app are:
• g++
• Open-GL Libraries(Free-glut)
• p-threads library on C++

2

How to Use
2.1
Start the app
In order to run the Screensaver for first time, type the command make execute
num threads=n in Linux terminal after changing to project directory, where n *
denotes the number of balls.
* The maximum number of balls allowed is 30
If you want to execute it again, first remove execute and compile files
from the project, using rm execute compile and again run make execute
num thread=n.
2.2
Controls
During execution, various parameters can be controlled with the help of Key-
board Buttons. These include:
• ↑ and ↓ Keys – To cycle through the balls selected for controls. Initially
no ball is selected. The selected ball turns white in colour.
• ? key – To clear the selection of balls.
1•
← and → keys – To change the velocity of selected ball. ←key for in-
creasing and → key for decreasing velocity.
• w and s – To move front and back in box, i.e, in the Z direction.
• g -To enable gravity in the ball. Each ball will then experience an accel-
eration in downward direction.
• + – Inorder to increase the count of balls currently present on the screen.
The count can only be increased till 30.
• Space key – To pause the app. The balls and moving terrain will be
paused. Again pressing Space key will start the app again.
The app will open in Fullscreen. Pressing Esc button will exit the mode and
return to windowed mode.
