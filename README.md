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

USAGE: Er, nothing. It's not really at a place where it does anything. 
I mean, you can compile it with make, I guess, so there's that. But that's basically it. At the time
of this writing, if you run it, it'll just show a window of solid blue. Also, you need
OpenGL and GLFW and... lessee, SOIL, even though I'm not actually using SOIL. And I think that's it? Oh, and GLEW.
Personally, I wouldn't bother.
I'll update this file when the code is more mature.
