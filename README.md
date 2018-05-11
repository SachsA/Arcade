<h3>Arcade</h3>
<p>
Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.
</p>
<p>
  The main feature of this project is to being able to change of game and/or graphic library anytime you want.
  Two games and three graphical libraries are already implemented.
  If you want to build your own just refer to the documentation (located in the doc folder)
</p>
 
<h2>Graphical libraries implemented:</h2>
<ul style="list-style-type:none">
  <li>Ncurses.</li>
  <li>Allegro.</li>
  <li>SDL2.</li>
 </ul>
 
<h2>Game libraries implemented:</h2>
<ul style="list-style-type:none">
  <li>Pacman (not working completly)</li>
  <li>Nibbler</li>
  <li>SolarFox</li>
 </ul>
 
<h3>Program compilation:</h3>
<p>
  <ul style="list-style-type:none">
    <li>$ make -> Will commpile the entire project.</li>
  <li>$ make core -> Only compile the core of the program.</li>
  <li>$ make games -> Wil only compile the game libraries.</li>
  <li>$ make graphicals -> Will only compile the graphical libraries.</li>
    </ul>
  #All the lib_arcade_[NAME_OF_THE_LIB].so are located in the ./lib folder.
 
  #All the lib_arcade_[NAME_OF_THE_GAME].so are located in the ./games folder.
 
  The games and lib folder will be created at compile time and erase with the fclean rule.
</p>
 
<h3>Launch the Arcade</h3>
<p>
  $ ./arcade ./lib_arcade_[NAME_OF_THE_LIB].so
  The program need to be launch with a set graphical library of your choice.
  Don't worry if you don't really like it you can change it when your game is launch.
</p>
 
<h3>How to play:</h3>
<p>
  Up and down arrow key let you go through the different elements and the left and right key change the menu you're in.
  Once you've choose both your graphical and game library just press SPACE to start the game.
</p>
 
<h3>Global commands</h3>
<p>
  As i've said before, while you are playing, you can switch of game and graphical library whenever you want.
  To do so some keys are binded:
</p>
<ul style="list-style-type:none">
  <li>Switch between graphicals libraries:</li>
  <ul style="list-style-type:none">
    <li> 'E': Previous graphical library.</li>
    <li> 'Z': Next graphical library.</li>
  </ul>
  <li>Leaving the game and the program:</li>
  <ul style="list-style-type:none">
    <il> Press 'ESCAPE' (while in game): Return to the Selection Menu.</li>
    <il> 'Q' (while in game) or 'ESCAPE' (in the startup menu): Quit the program.</li>
  </ul>
</ul>
 
<h3>Game command</h3>
<ul style="list-style-type:none">
  <li>Arrow key: Move your character.</li>
  <li>'S': Restart your game.</li>
  <li>'SPACE': To pause the game.</li>
  <li>Switching game:</li>
  <ul style="list-style-type:none">
  <li>'A': Go to the previous game.</li>
  <li>'Z': Go to the next game.</li>
  </ul>
</ul>
 
<h3>Project realised by:</h3>
<ul style="list-style-type:none">
    <li>Alexandre Sachs : alexandre.sachs@epitech.eu</li>
    <li>Thomas Bleneau : thomas.bleneau@epitech.eu</li>
    <il>Antoine Pelletant : antoine.pelletant@epitech.eu</li>
  </ul>
  <br>
<p>
  One of the goal of the project was to be able to load libraries, whom had been coded by an other group of student.
  To do so we've worked with:
  <ul style="list-style-type:none">
    <li>Kellian Cipierre : kellian.cipierre@epitech.eu</li>
    <li>Martin Cotoni : martin.cotoni@epitech.eu</li>
    <li>Thomas Lombard : thomas.lombard@epitech.eu</li>
  </ul>
</p>
