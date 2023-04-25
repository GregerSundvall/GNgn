# GNgn
My game engine sand box, sorta.

Started out as a performance testing ground with massive amounts of objects flying around on screen simltaneously and seeing which type of system layout worked the best. To quickly get going with this part I used SDL for input/output.
I then created an entity system with optional components. The entities and components all manage their own part and communication is done with the aid of ID numbers.
Most recently I added a physics system. This is at the moment not plugged into the entity system.

I'm really just playing around trying interesting ideas and concepts, to learn more about C++ and engine design. But I guess somewhere in the back of my head I have words like performance, ease-of-use, options...


Stuff I want to do next, other than just fixing things;

Creating an event system. 

Reworking the entity system and integrating it with the physics system.

Adding the option to use point physics. 

Create a C array wrapper and replace std::vectors with it.

Ditching SDL and creating my own stuff for input and output.
