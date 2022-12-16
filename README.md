# SDL_Playground
Assignment "Performance-aware space shooter"

IMPORTANT: because of git trouble the master branch is not up to speed. See "Components" branch!


As usual, time passed a little bit too fast. A hospital visit with surgery that required pretty much
not eating for a week, and one of the kids getting an emergency appendix removal surgery, both during 
the project, probably didn't help... 


I started the project testing with a C array of floats, where every even float was the x position and 
the following uneven nr was the y position of an entity.
This seemed to be very performant. One lesson from this was, to have one loop to update the positions, 
and another loop to draw them is more performant. Even though computer has to cycle the array twice.

As a next step I was gonna add separate colliders. After fiddling with this for a bit I didn't really 
know which way to go, so I read a bunch of articles on data oriented programming/design. I got really 
inspired by this, so I started work on a component-based system that I think would be considered data 
oriented, which communicates between the different components with "component ID numbers".

At the time of writing this (and handing it in), I haven't had time to fix the last bugs and test 
performance, but I am very much looking forward to doing this. This kind of work is right up my alley
and I will probably keep developing this into some sort of game engine. There is no shortage of ideas.


More about how it works:
The game has a class called EntitySystem, which has an std::vector with entity data. It also has a 
bunch of sub-systems that each handle a separate part of an entity's possible functionalities, like
transform, movement, collider, sprite. 
The subsystems have their own std::vector of data for their respective area. Each system communicates 
with the entitysystem based on ID numbers, which are basically the indices of the components in the 
respective array. 
Each sub-/component-system handles it's own data and where things overlap, they communicate via the
parent entity system.
The Entity data is basically a collection of component ID's.





