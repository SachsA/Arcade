# ARCADE

###### The Arcade is a project where we had to built a gaming platform on Linux, managing several games and several graphical libraries loaded dynamically.

[Arcade](https://en.wikipedia.org/wiki/Arcade_game) is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.


The **Bomberman** is composed with two main parts : the back developped in **C++** manage all the menus and the game engine; and the front developped with the **SFML (in C++ too)** display the game.

### Graphical libraries implemented:
  *Ncurses*
  *Allegro*
  *SDL2*

### Game libraries implemented:
  *Pacman (not working completly)*
  *Nibbler*
  *SolarFox* 


### Program compilation:
  ##### Linux:

  ```sh
        make
```
  >  Will commpile the entire project.

  ```sh
        make core
```
  >  Only compile the core of the program.

  ```sh
        make games
```
  >  Wil only compile the game libraries.

  ```sh
        make graphicals
```
  >  Will only compile the graphical libraries.

  
  >> All the lib_arcade_[NAME_OF_THE_LIB].so are located in the ./lib folder.
 
  >> All the lib_arcade_[NAME_OF_THE_GAME].so are located in the ./games folder.
 
  The games and lib folder will be created at compile time and erase with the fclean rule.
  
  ### Program compilation:
  ##### Linux:

  ```sh
        ./arcade ./lib_arcade_[NAME_OF_THE_LIB].so
```
  >  The program need to be launch with a set graphical library of your choice.
     Don't worry if you don't really like it you can change it when your game is launch.


## How to play:
  ***Up and down arrow keys*** let you go through the different elements.
  ***Left and right arrow keys*** change the menu you're in.
  
  Once you've choose both your graphical and game library just press ***SPACE*** to start the game.


### Aracade Usage
#### Global commands
  As i've said before, while you are playing, you can switch of game and graphical library whenever you want.
  To do so some keys are binded:

  ##### Switch between graphicals libraries:
   ***E***: Previous graphical library.
   ***Z***: Next graphical library.

  ##### Leaving the game and the program:
   ***ESCPAE***: (while in game): Return to the Selection Menu.
   ***Q***: (while in game) or ***ESCAPE*** (in the startup menu): Quit the program.

#### Game commands
  ***Arrow key***: Move your character.
  ***S***: Restart your game.
  ***SPACE***: To pause the game.
  
  ##### Switching game:
  ***A***: Go to the previous game.
  ***Z***: Go to the next game.



 #### Project realised by:
- **Alexandre Sachs : [alexandre.sachs@epitech.eu](https://github.com/SachsA)**
- **Antoine Pelletant : [antoine.pelletant@epitech.eu](https://github.com/yabou)**
- **Thomas Bleneau : [thomas.bleneau@epitech.eu](https://github.com/TBlenoX)**

  One of the goal of the project was to be able to load libraries, whom had been coded by an other group of student.
  #### To do so we've worked with:
 #### Project realised by:
- **Kellian Cipierre : [kellian.cipierre@cipierre.eu]()**
- **Martin Cotoni : [martin.cotoni@epitech.eu](https://github.com/cotonim)**
- **Thomas Lombard : [thomas.lombard@epitech.eu]()**
