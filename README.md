!!! Arcade !!!

Epitech's Second Year Project:

The goal of this project is to let the user choose between few libraries of games and graphics.
The Arcade is a gaming platform which contains some games that you can play with. It allows the user to keep his high score for each game of this Arcade.
One of the main feature is that you can, dynamically, change between graphicals libraries and games libraries.

The games and the graphics must be dynamic libraries ! That means : they are loaded at run-time, and that they are shared libraries, and nothing in our program is a reference to one of this lib.
So, if someone wants to build a game lib or a graphical lib, he can do it and it will be loaded by our Arcade ! The only thing to know is that, when you do a lib, YOU MUST build your library exactly like ours.

If you want to build a library of a game or a graphical lib, please refer to our ./doc folder, which contains all you have to know.



GRAPHIC LIBRARIES ALREADY IMPLEMENTED :
Ncurses.
Allegro.
SDL2.

Some ideas of graphic libraries :
SFML, OpenGL, GTK+, Vulkan, NDK++... (And many more !)
!!! Enjoy !!!



GAMES ALREADY IMPLEMENTED :
Pacman.
Nibbler.
SolarFox.

Some ideas of  games:
Qix, Centipede... (And many more !)
!!! Enjoy !!!



USAGE of the Arcade :

1) MAKE

!!! You have to make the Arcade !!!

-> To make all the libs and the core of the arcade just type :
$ make

-> To remake all the lib :
$ make re

-> To make just the core :
$ make core

-> To make just the games :
$ make games

-> To make just the graphicals libraries :
$ make graphicals

#All the lib_arcade_[NAME_OF_THE_LIB].so are located in the ./lib folder (you have to compile them before, obviously).
#All the lib_arcade_[NAME_OF_THE_GAME].so are located in the ./games folder (you have to compile them before, obviously).

2) LAUNCH the Arcade

$ ./arcade ./lib_arcade_[NAME_OF_THE_LIB].so

The program must take as a start up argument the graphics library to use initially !
That means that this lib will load the menu of the arcade !
Example : ./arcade ./lib_arcade_sdl2.so    -->    Will load the Arcade Menu with the SDL2.



HOW TO PLAY:

When you have launched it, you will load the Selection Menu:
-> Choose your lib graphic and your game by moving with the 'ARROW UP' and the 'ARROW DOWN'.
-> To change between games and libs just press 'RIGHT ARROW' or 'LEFT ARROW'.
-> Once you have choose them, just press 'SPACE' to launch the game.

-> Then, follow the instruction !


!! GLOBALS COMMANDS !!
In the Selection Menu :
-> Press 'ARROW UP' : select the previous lib.
-> Press 'ARROW DOWN' : select the next lib.
-> Press 'ARROW LEFT' : select the other lib's category.
-> Press 'ARROW RIGHT' : select the other lib's category.
-> Press 'SPACE' : to confirm.

In the Pause Menu :
-> Press 'ARROW UP' : select the previous option.
-> Press 'ARROW DOWN' : select the next option.
-> Press 'SPACE' : to confirm.

Switch between graphicals libraries :
-> Press 'E' : Previous graphicals lib.
-> Press 'Z' : Next graphicals lib.

Return to the Selection Menu :
-> Press 'ESCAPE'.

Quit the Arcade :
-> Press 'Q' / Press 'ESCAPE' when you are on the Selection Menu


!! GAME'S COMMANDS !!
On the Game :
-> Press 'S' : restart the game.
-> Press 'SPACE' : pause the game.
-> Press 'ARROW UP' : move up.
-> Press 'ARROW DOWN' : move down.
-> Press 'ARROW LEFT' : move left.
-> Press 'ARROW RIGHT' : move right.

Switch between games libraries :
-> Press 'A' : Previous game.
-> Press 'Z' : Next game.



Documentation :
If you want to know anything about : the structure of the Arcade, the Interface of our Games and our Graphics libraries, or even : how to make a lib ? (Games or Graphics) :
We strongly suggest you to go to the ./doc folder, you will find a "Doc.pdf" file :
-> This a document explaining how to implement new graphics libraries or game libraries compatible with our system !

Furthermore you will also find :
-> A class diagram for your program (Arcade_archi.mdj), featuring the relationships between classes and their public member functions (and some privates).
-> An explanatory manual that accompanies our diagram and describes how procedures are linked in the program.



DEVELOPERS of the project (Epitech's second year students):

Alexandre Sachs : alexandre.sachs@epitech.eu
Antoine Pelletant : antoine.pelletant@epitech.eu (The GROUP LEADER for our repository !)
Thomas Bleneau : thomas.bleneau@epitech.eu


Collaboration :

We have made this project in collaboration with an other Epitech group, composed by :

Kellian Cipierre : kellian.cipierre@epitech.eu (The GROUP LEADER for their repository !)
Martin Cotoni : martin.cotoni@epitech.eu
Thomas Lombard : thomas.lombard@epitech.eu

That collaboration, allowed us to make a common interface with them ! That means that our Arcade can launch their games and graphicals libraries, and vice versa.