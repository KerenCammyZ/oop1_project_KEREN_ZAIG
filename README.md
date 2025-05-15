OOP1 Final Project Bomberman Game

Student: Keren Zaig 

=======================ABOUT=======================
This project is a recreation of the retro game BOMBERMAN for the NES.
It's a retro style 2d game with a score function, the user can use the arrow
keys to move their character around and pass 3 levels.

====================HEADER FILES======================

Bomb.h - Header file for Bomb class
Door.h - Header file for Door class
GameManager.h - Header file for GameManager class
GameObject.h - Header file for GameObject class
GlobalSizes.h - Global sizes that are needed in both GameObject and GameManager
Guard.h - Header file for Guard class
MovingObject.h - - Header file for MovingObject class
Player.h - Header file for Player class
PowerUp.h - Header file for PowerUp class
ResourceManager.h - Header file for Resource class
Rock.h - Header file for Rock class
StaticObject.h - Header file for StaticObject class
Wall.h - Header file for Wall class

======================CPP FILES=======================

Bomb.cpp - Bomb is a StaticObject GameObject that has a countdown
		with function getCount to know when it time to "explode".

Door.cpp - Door is a StaticObject GameObject that has a a bool that
		represents if the door has been passed or not with a function
		getPassed.

GameManager.cpp - GameManager is the class that handles the runtime of the whole
			game, makes sure the windows and game events are updated properly
			and etc. More information about GameManager can be found under 
			the DESIGN header below.

GameObject.cpp - Base class for all the Objects in the game. It holds the position,
			sprite, texture, type. It has functions such as draw to draw the 
			sprite, setTexture to set the texture of the sprite, checkCollision
			to check collision between 2 GameObjects and multiple set get 
			for all the members (position, sprite, texture, type)

Guard.cpp - Guard is a MovingObject GameObject that can "kill" the player if
		they collide. It has their own move function with the algorithm explained
		more in depth under the header ALGORITHMS below. It also includes members
		as a m_alive, m_frozen, m_directionChangeClock to check when it should change
		what direction it's moving in and m_currentDirection to save what direction
		it's currently moving in.

MovingObject.cpp - MovingObject is a GameObject that has functions that allow movement
			 for the classes that inherit from it. The player uses the defualt movement
			and the guards have their own override movement function.

Player.cpp - Player is a MovingObject GameObject that represents the player the user can
		 play as. It inherits it's move function from MovingObject and has members
		 such as m_alive and m_lives to keep track of how many lives the player currently
		 has.

PowerUp.cpp - PowerUp is a StaticObject GameObject with no collision that gives the player
		  different powers depending on what type it is. There are 4 powerups: Dissapear,
		  time, freeze, and life. More information about each powerup can be found under
		  the DESIGN header below.

ResourceManager.cpp - ResourceManager is a class that handles all the loading of textures and 
			    music in the game. It has functions that also make sure they arent being
			    loaded multiple times to save memory.

Rock.cpp - Rock is a StaticObject GameObject that can be "blown up" by a Bomb, which is 
	     handled in the GameManager.

StaticObject.cpp - StaticObject is simaler to MovingObject only it doesnt contain functions
			 to move the GameObject.
Wall.cpp - Wall is a StaticObject GameObject that many of them create the border that 
		ensures the player cannot exit from the level.

====================RESOURCE FILES=====================

bomb1.png - first frame bomb animation
bomb2.png - second frame bomb animation
bomb3.png - third frame bomb animation
bomb4.png - fourth frame bomb animation
dead.ogg - sound that plays when player is hit by guard
dissapear.png - Dissapear Powerup texture
door.png - Door texture
EndScreen.png - Win or Lose Screen backround
explosion.ogg - explosion sound
explosion.png - explosion texture
freeze.png - Freeze powerup texture
gameBackround.png - backround that appears in all levels
guard.png - Guard texture
HELP SCREEN.png - instructions screen backround
inGameMusic.ogg - in game music during levels CREDIT: Joshua McLean - Mountain Trials
level1.txt - map of level1 that represents how the level1 is printed
level2.txt - map of level2 that represents how the level2 is printed
level3.txt - map of level3 that represents how the level3 is printed
levelup.ogg - sound that plays when you move on to a different level
life.png - Life powerup texture
mainMenuMusic.ogg - music that plays in the main menu CREDIT: Eric Skiff - A Night Of Dizzy Spells
Orange Kid.otf - Font for all the text in the game CREDIT: Orange Kid Font by 1001 Fonts 
player.png - Player texture
powerup.ogg - sound that plays when player collects a powerup
rock.png - rock texture
time.png - Time powerup texture
wall.png - wall texture

====================DATA STRUCTURES===================

GameObject: Class that represents all the objects in the game, it has a member
		m_position that represents the x and y of the object on the window,
		and a member m_sprite that holds the texture of the object.

MovingObject: Class that inherits from GameObject, with functions for moving the sprite.
		  has members such as direction which is a vector with an x and y value that
		  represents what direction the sprite is moving in with (0,0) being "standing still".	

StaticObject: Class that inherits from GameObject with no move functions. The classes
		  Wall, Rock, Bomb, PowerUp inherit from StaticObject.

======================ALGORITHMS======================

Guard Movement: Each guard rolls for a random number 0 or 1. If 0 is picked it uses the
		    findPlayerDirection function to follow the player for 6 seconds. If 1 is 
		    picked it moves in a random direction if it does not collide with a StaticObject.

Timed Level: Each time a level is drawn 4 random powerups are chosen to be drawn on the board.
		 If the powerup TIME is one of them then the user had 3 minutes to complete the level
		 otherwise they lose all their lives and the game restarts, if there is no TIME
		 powerup drawn then the user has as much time as they please to complete the level.

========================DESIGN=======================

GameManager: GameManager manages the game and decides when the game is in the main menu,
		 running a level or in the end screen. It has functions that are called based on
		 the GameStatus enum MAIN_MENU, IN_GAME, HELP_SCREEN, END_SCREEN. It holds the
		 information of the score, how the window is drawn, the current level, and calls
		 the relevent player, guard and object draw functions each frame of the game.
		 It listens based on the window open to events such as mouse clicks and keyboard
		 pressed if in the actual game and translates it to the relevent functions to run
		 the game frame.

ResourceManager: Loads all the png, font, and music files for the game. It holds all the 
		     textures and music files in different vectors and can be callled to load in
		     the GameManager when printing on to the screen.

Game Rules: The player starts with 3 lives and the goal is to reach level 3 by passing throgh
		doors. Player can lose a life from colliding with guards or bombs. The player
		has to use bombs to break rocks or kill guards in its path. There are powerups the
		player can collect:
		LIFE: adds one life
		DISSAPEAR: makes a guard dissapear
		FREEZE: makes guards dissapear for five seconds
		TIME: if the level is a timed level, it adds an extra 3 mins to complete the level.
		There are timed levels that require the player to complete the level in under 3 minutes,
		if they fail to do so they lose all their lives and its game over.
		The player can rank up their score based on the following conditions:
		killing a guard awards +5 points
		beating a level awards + (25 + howManyGuardsinLevel * 3) points


=========================BUGS========================
Guards can get stuck on walls sometimes, or not "killed properly" in radius of the bomb
The Bomb can sometimes not explode the objects above it.
The Door Object can sometimes delete the Wall object underneath it.
Player can sometimes get "out of bounds" if user is pressing up while respawning.

========================OTHER========================
original Bomberman created by Nintendo for NES
Textures ripped by users on spriters-resource.com
