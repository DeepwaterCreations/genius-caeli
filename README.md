# genius-caeli
A perlin noise generator/visualizer

My college capstone project was meant to include a perlin noise generator. 
I never really got it working properly. Now that I'm older and wiser,
I've decided it's time to take another stab at it. (It really shouldn't be very hard, I think.)
This time it's in C++ and OpenGL instead of Java and whatever the built-in Java thing I was using was.
Actually, I think I'm going to try to write it so that the OpenGL component is only for the visualizer.
Generating noise shouldn't require any external anything.

If you, o stranger, have a desire to use this code to make your own procedural noise,
do so with my blessing - assuming you're following the terms in whatever it says in the license file. 
(The license file supercedes this, but in essence, I'm pretty sure I'm fine with whatever you want to do so long as
you give me credit and, I dunno, refrain from committing moral atrocities.)


BUILD:
Dependencies: glew, glfw, glm, soil
Build Dependencies: make, gcc
Instructions: 
-Clone this repository from github
-Read the makefile and assure yourself that it doesn't do anything terrible to your computer. (Or take my word for it that it doesn't.)
-Type 'make'
-Alternately, compile it with 
	g++ main.cpp OpenGLHelper.cpp GeniusCaeli.cpp -lGL -lGLEW -lglfw -lSOIL -std=c++11 -Wall -g

USAGE:
Run a.out. A window will open showing some perlin noise in blue and black.
You can marvel at it for a while, or if you have better things to be getting on with in your life, you can close the window.
More features to come. 
