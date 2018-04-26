#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <math.h.>
#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
and even seeding the random number generator.
*/
AngryBirdsGame::AngryBirdsGame()
{
	std::srand(time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
AngryBirdsGame::~AngryBirdsGame()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);
	this->inputs->unregisterCallback(mouse_move_callback_id);
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler and clickHandler
callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
#pragma region [initaliseFunctions]
bool AngryBirdsGame::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}
	fire = false;
	toggleFPS();
	renderer->setWindowTitle("Castle Siege");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	inputs->use_threads = false;


	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);

	mouse_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);

	mouse_move_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_MOVE, &AngryBirdsGame::moveHandler, this);


	if (!loadSprites())
	{
		return false;
	}

	if (!initalise_buildings())
	{
		return false;
	}


	in_menu = true;

	return true;
}
#pragma endregion

//load buildings
bool AngryBirdsGame::initalise_buildings()
{
	//initalise buildings
	for (int i = 0; i < max_buildings; i++)
	{
		//load brick sprite
		std::string building1_layer = "Resources\\images\\building_brick1.png";
		if (!building1[i].addSpriteComponent(renderer.get(), building1_layer))
		{
			return false;
		}

		//load roof sprite
		std::string building1_roof_layer = "Resources\\images\\building_brick1_roof.png";
		building1_roof[i].addSpriteComponent(renderer.get(), building1_roof_layer);

		//set visibility to true
		building1[i].visibility = true;
		building1_roof[i].visibility = true;

		//set col num to 0
		building1_roof[1].col_num = 0;

		//get sprites
		building1_sprite[i] = building1[i].spriteComponent()->getSprite();
		building1_roof_sprite[i] = building1_roof[i].spriteComponent()->getSprite();
	}

	reset_building_postiions();


}

//load sprites
bool AngryBirdsGame::loadSprites()
{
	//menu title
	std::string menu_title_layer = "Resources\\images\\menu_title.png";
	if (!menu_title.addSpriteComponent(renderer.get(), menu_title_layer))
	{
		return false;
	}

	//menu start
	std::string menu_start_layer = "Resources\\images\\menu_start.png";
	if (!menu_start.addSpriteComponent(renderer.get(), menu_start_layer))
	{
		return false;
	}

	//menu exit
	std::string menu_exit_layer = "Resources\\images\\menu_exit.png";
	if (!menu_exit.addSpriteComponent(renderer.get(), menu_exit_layer))
	{
		return false;
	}

	//gameover menu
	std::string gameover_layer = "Resources\\images\\gameover.png";
	if (!gameover_sign.addSpriteComponent(renderer.get(), gameover_layer))
	{
		return false;
	}

	//okay button
	std::string okay_layer = "Resources\\images\\okay.png";
	if (!okay.addSpriteComponent(renderer.get(), okay_layer))
	{
		return false;
	}

	//level start
	std::string level_start_layer = "Resources\\images\\level_start.png";
	if (!level_start.addSpriteComponent(renderer.get(), level_start_layer))
	{
		return false;
	}

	//level 1 intro
	std::string level1_intro_layer = "Resources\\images\\level1_intro.png";
	if (!level1_intro.addSpriteComponent(renderer.get(), level1_intro_layer))
	{
		return false;
	}

	//level 2 intro
	std::string level2_intro_layer = "Resources\\images\\level2_intro.png";
	if (!level2_intro.addSpriteComponent(renderer.get(), level2_intro_layer))
	{
		return false;
	}

	//level 3 intro
	std::string level3_intro_layer = "Resources\\images\\level3_intro.png";
	if (!level3_intro.addSpriteComponent(renderer.get(), level3_intro_layer))
	{
		return false;
	}

	//cursor
	std::string cursor_layer = "Resources\\images\\cursor.png";
	if (!cursor.addSpriteComponent(renderer.get(), cursor_layer))
	{
		return false;
	}

	//background
	std::string background_layer = "Resources\\images\\foreground.png";
	if (!background.addSpriteComponent(renderer.get(), background_layer))
	{
		return false;
	}

	//overlay
	std::string overlay_layer = "Resources\\images\\overlay.png";
	if (!overlay.addSpriteComponent(renderer.get(), overlay_layer))
	{
		return false;
	}

	//army
	std::string army_layer = "Resources\\images\\army.png";
	if (!army.addSpriteComponent(renderer.get(), army_layer))
	{
		return false;
	}
	army.visibility = true;
	army_sprite = army.spriteComponent()->getSprite();
	army_x_pos = army_sprite->xPos();
	army_y_pos = army_sprite->yPos();
	army_x_pos = 1200;
	army_y_pos = 650;
	army_sprite->xPos(army_x_pos);
	army_sprite->yPos(army_y_pos);

	//king
	std::string king_layer = "Resources\\images\\king.png";
	if (!king.addSpriteComponent(renderer.get(), king_layer))
	{
		return false;
	}
	king.visibility = true;
	king_sprite = king.spriteComponent()->getSprite();
	king_x_pos = king_sprite->xPos();
	king_y_pos = king_sprite->yPos();
	king_x_pos = 1350;
	king_y_pos = 650;
	king_sprite->xPos(king_x_pos);
	king_sprite->yPos(king_y_pos);


	//catapult
	std::string catapult_layer = "Resources\\images\\catapult.png";
	if (!catapult.addSpriteComponent(renderer.get(), catapult_layer))
	{
		return false;
	}

	catapult_sprite = catapult.spriteComponent()->getSprite();
	catapult_x_pos = catapult_sprite->xPos();
	catapult_y_pos = catapult_sprite->yPos();
	catapult_x_pos = 160;
	catapult_y_pos = 680;
	catapult_sprite->xPos(catapult_x_pos);
	catapult_sprite->yPos(catapult_y_pos);

	//fire limit
	std::string range_overlay = "Resources\\images\\fire_limit.png";
	if (!range.addSpriteComponent(renderer.get(), range_overlay))
	{
		return false;
	}

	range_sprite = range.spriteComponent()->getSprite();
	range_x_pos = catapult_sprite->xPos();
	range_y_pos = catapult_sprite->yPos();
	range_x_pos = 2;
	range_y_pos = 700;
	range_sprite->xPos(range_x_pos);
	range_sprite->yPos(range_y_pos);

	//rocks
	int x_cord = 1;
	int y_cord = 63;
	for (int i = 0; i < max_rocks; i++)
	{
		//assign sprite to each block
		if (!rocks[i].addSpriteComponent(renderer.get(), "Resources\\images\\rock1.png"))
		{
			return false;
		}

		//get sprite
		rocks_sprite[i] = rocks[i].spriteComponent()->getSprite();

		//assign position
		rocks_sprite[i]->xPos(x_cord * 25);
		rocks_sprite[i]->yPos(y_cord * 12);
		x_cord++;

		rocks[i].fired = false;
		rocks[i].selected = false;
		rocks[i].visibility = true;
	}

	return true;
}

//reset all buidling's positions
void AngryBirdsGame::reset_building_postiions()
{
	//level 1
		//set position
		float x_cord = 5.5;
		float y_cord = 2.6;
		for (int i = 0; i < max_buildings; i++)
		{
			//get sprites
			building1_sprite[i] = building1[i].spriteComponent()->getSprite();
			building1_roof_sprite[i] = building1_roof[i].spriteComponent()->getSprite();

			//assign house pos
			building1_sprite[i]->xPos(x_cord * house_width);
			building1_sprite[i]->yPos(y_cord * house_width);

			//assign roof pos
			building1_roof_sprite[i]->xPos(x_cord * house_width);
			building1_roof_sprite[i]->yPos(y_cord * house_width);

			x_cord++;
			if (i == 1 || i == 16 || i == 24 || i == 32)
			{
				x_cord = 5.5;
				y_cord = 1.8;
			}
		}

	//level 2
	if (level_2 == true)
	{
		//set position
		float x_cord = 5.5;
		float y_cord = 1.8;
		for (int i = 0; i < max_buildings; i++)
		{
			//get sprites
			building1_sprite[i] = building1[i].spriteComponent()->getSprite();
			building1_roof_sprite[i] = building1_roof[i].spriteComponent()->getSprite();

			//assign house pos
			building1_sprite[i]->xPos(x_cord * house_width);
			building1_sprite[i]->yPos(y_cord * house_width);

			//assign roof pos
			building1_roof_sprite[i]->xPos(x_cord * house_width);
			building1_roof_sprite[i]->yPos(y_cord * house_width);

			x_cord++;
			if (i == 0 || i == 16 || i == 24 || i == 32)
			{
				x_cord = 4.5;
				y_cord = 2.6;
			}
		}
	}

	//level 3
	if (level_3 == true)
	{
		//set position
		float x_cord = 5.5;
		float y_cord = 0.5;
		for (int i = 0; i < max_buildings; i++)
		{
			//get sprites
			building1_sprite[i] = building1[i].spriteComponent()->getSprite();
			building1_roof_sprite[i] = building1_roof[i].spriteComponent()->getSprite();

			//assign house pos
			building1_sprite[i]->xPos(x_cord * house_width);
			building1_sprite[i]->yPos(y_cord * house_width);

			//assign roof pos
			building1_roof_sprite[i]->xPos(x_cord * house_width);
			building1_roof_sprite[i]->yPos(y_cord * house_width);

			//x_cord++;
			y_cord++;
			if (i == 2)
			{
				x_cord = 4.5;
				y_cord = 2.6;
			}
		}
	}

}

//reset the rock positions
void AngryBirdsGame::reset_rock_postions()
{
	//rocks
	int x_cord = 1;
	int y_cord = 63;
	for (int i = 0; i < max_rocks; i++)
	{
		//get sprite
		rocks_sprite[i] = rocks[i].spriteComponent()->getSprite();

		//assign position
		rocks_sprite[i]->xPos(x_cord * 25);
		rocks_sprite[i]->yPos(y_cord * 12);
		x_cord++;

		rocks[i].selected = false;
		rocks[i].visibility = true;

	}
}

//reset army positions
void AngryBirdsGame::reset_army_positions()
{
	army.visibility = true;
	army_sprite = army.spriteComponent()->getSprite();
	army_x_pos = army_sprite->xPos();
	army_y_pos = army_sprite->yPos();
	army_x_pos = 1200;
	army_y_pos = 650;
	army_sprite->xPos(army_x_pos);
	army_sprite->yPos(army_y_pos);
}

//reset game states
void AngryBirdsGame::reset_game_states()
{
	in_menu = true;
	level_1 = false;
	level_1_intro_bool = true;
	level_2 = false;
	level_3 = false;
	gameover = false;
	freeze_cursor = false;

	for (int i = 0; i < max_buildings; i++)
	{
		//set visibility
		building1_roof->visibility = true;
		//reset collision numbers
		building1_roof[i].col_num = 0;
	}
}

/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any
aspect ratio scaling factors and safe zones to ensure the
game frames when resolutions are changed in size.
*   @return  void
*/
void AngryBirdsGame::setupResolution()
{
	// how will you calculate the game's resolution?
	// will it scale correctly in full screen? what AR will you use?
	// how will the game be framed in native 16:9 resolutions?
	// here are some abritrary values for you to adjust as you see fit
	// https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/Scaling_and_MultiResolution_in_2D_Games.php
	game_width = 1600;
	game_height = 800;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
keyboard input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void AngryBirdsGame::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		reset_game_states();
		reset_rock_postions();
		reset_building_postiions();
		reset_army_positions();
		loadSprites();
		distance = 0;
		spawner = true;
	}

	else if (key->key == ASGE::KEYS::KEY_ENTER &&
		key->action == ASGE::KEYS::KEY_PRESSED &&
		key->mods == 0x0004)
	{
		if (renderer->getWindowMode() == ASGE::Renderer::WindowMode::WINDOWED)
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::FULLSCREEN);
		}
		else
		{
			renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
		}
	}

	else if (in_menu)
	{
		if (key->key == ASGE::KEYS::KEY_SPACE)
		{
			in_menu = !in_menu;
		}
	}
}

/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
mouse button input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void AngryBirdsGame::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());
	double cursor_x_pos, cursor_y_pos;
	inputs->getCursorPos(cursor_x_pos, cursor_y_pos);

	//left mouse down
	if (click->button == 0)
	{
		leftMouseDown = true;
	}


	//right mouse down
	if (click->button == 1)
	{
		rightMosueDown = true;
	}

	//no action
	if (click->action == false)
	{
		leftMouseDown = false;
		rightMosueDown = false;
	}


}

//cursor movement
void AngryBirdsGame::moveHandler(const ASGE::SharedEventData data)
{
	auto move = static_cast<const ASGE::MoveEvent*>(data.get());
	inputs->setCursorMode(ASGE::CursorMode::HIDDEN);
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
current frame. Once the current frame is has finished
the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::update(const ASGE::GameTime& us)
{
	auto dt_sec = us.delta_time.count() / 1000.0;
	float distance = 0;
	double cursor_x_pos, cursor_y_pos;
	inputs->getCursorPos(cursor_x_pos, cursor_y_pos);
	static bool initialized;
	//assign custom cursor 
	cursor_sprite = cursor.spriteComponent()->getSprite();
	if (freeze_cursor == false)
	{
		cursor_sprite->xPos(cursor_x_pos);
		cursor_sprite->yPos(cursor_y_pos);
	}


	if (in_menu)
	{
		//start
		if (menu_start.spriteComponent()->getBoundingBox().isInside(cursor.spriteComponent()->getBoundingBox()) && leftMouseDown == true)
		{
			in_menu = false;
		}

		//exit
		if (menu_exit.spriteComponent()->getBoundingBox().isInside(cursor.spriteComponent()->getBoundingBox()) && leftMouseDown == true)
		{
			signalExit();
		}

	}

	if (!in_menu)
	{
		//level 1 intro
		if (level_1_intro_bool == true)
		{
			if (level_start.spriteComponent()->getBoundingBox().isInside(cursor.spriteComponent()->getBoundingBox()) && leftMouseDown == true)
			{
				level_1_intro_bool = false;
				begin = true;
			}
		}


		if (begin == true)
		{
			//level 1
			for (int i = 0; i < max_rocks; i++)
			{
				if (gameover == false)
				{
					//army movment
					army_x_pos -= min_speed * dt_sec;
					army_sprite->xPos(army_x_pos);

					//grab catapult x pos
					catapult_x_pos = catapult_sprite->xPos();
					if (army_x_pos < catapult_x_pos)
					{
						gameover = true;
					}


					//grab y & x pos
					float rock_y_pos = rocks_sprite[i]->yPos();
					float rock_x_pos = rocks_sprite[i]->xPos();

					for (int j = 0; j < max_buildings; j++)
					{
						//building 1 collision
						if (rocks[i].spriteComponent()->getBoundingBox().isInside(building1_roof[j].spriteComponent()->getBoundingBox()) && building1_roof[j].visibility == true)
						{
							//add to the roof's collision number
							building1_roof[j].col_num++;

							player_score += 5;

							//assign damaged roof sprite if the object has been collided with less than 1 time
							if (building1_roof[j].col_num <= 1)
							{
								std::string building1_roof_layer = "Resources\\images\\building_brick1_roof_dmg.png";
								building1_roof[j].addSpriteComponent(renderer.get(), building1_roof_layer);
								reset_building_postiions();
							}

							//else destroy the object
							else
							{
								building1_roof[j].visibility = false;
							}

							//set values accordingly
							current_lives--;
							rocks[i].fired = true;
							rocks[i].visibility = false;
							spawner = true;
							initialise_fire = false;
							fire = false;
						}
					}

					//king collision
					if (rocks[i].spriteComponent()->getBoundingBox().isInside(king.spriteComponent()->getBoundingBox()) && king.visibility == true)
					{
						king.visibility = false;

						//set values accordingly
						player_score = +35;
						current_lives--;
						rocks[i].fired = true;
						rocks[i].visibility = false;
						spawner = true;
						initialise_fire = false;
						fire = false;
					}

					//cursor selecting rock
					if (rocks[i].spriteComponent()->getBoundingBox().isInside(cursor.spriteComponent()->getBoundingBox()) && rocks[i].visibility == true && leftMouseDown == true && rocks[i].fired == false && freeze_cursor == false)
					{
						if (number_selected < 1)
						{
							number_selected = 1;
							rocks[i].selected = true;
						}

						if (rocks_sprite[i]->xPos() > 250)
						{
							rocks[i].selected = false;
							reset_rock_postions();
						}
						if (rocks[i].selected == true)
						{
							fire = false;
							initialise_fire = true;
							rocks_sprite[i]->xPos(cursor_x_pos - 15);
							rocks_sprite[i]->yPos(cursor_y_pos - 15);
							calculate_distance = true;
						}

					}

					//once player has released lmb enable fire
					if (leftMouseDown == false && initialise_fire == true)
					{
						fire = true;
						number_selected = 0;
					}

					//calculate distance
					if (calculate_distance == true)
					{
						//distance calculations
						double a_x = cursor_sprite->xPos();
						double a_y = cursor_sprite->yPos();
						double b_x = catapult_x_pos + 136;
						double b_y = catapult_sprite->yPos();
						double difference_x = a_x - b_x;
						double difference_y = a_y - b_y;

						//save result to distance
						distance = std::sqrt((difference_x * difference_x) + (difference_y * difference_y));
					}

					//if fire = true & a rock is visable fire that rock
					if (fire == true && rocks[i].visibility == true && rocks[i].selected == true && gameover == false)
					{
						//freeze cursor to prevent constant update while rock is in motion
						freeze_cursor = true;

						//grab x & y pos of rock
						float rock_y_pos = rocks_sprite[i]->yPos();
						float rock_x_pos = rocks_sprite[i]->xPos();

						//curve intensity
						float a = 0.25;
						//enable x movement
						rock_x_pos += distance * 3 * dt_sec;
						//calculate curve
						rock_y_pos = a * (rock_x_pos - 600)* (rock_x_pos - 600) / distance - (cursor_y_pos*-1) * dt_sec;

						//save distance
						rocks_sprite[i]->yPos(rock_y_pos);
						rocks_sprite[i]->xPos(rock_x_pos);

						//old equation: rock_y_pos = (a * (rock_x_pos - 800)*(rock_x_pos - 800)) / distance + -300;
					}

					//if rock is greater than game height
					if (rock_y_pos > game_height && rock_x_pos > 300)
					{
						rocks[i].selected = false;
						//boost x pos of army
						army_x_pos -= 100;
						army_sprite->xPos(army_x_pos);

						//deduct life
						current_lives--;

						//reset rock
						rocks[i].fired = true;
						correct_distance = false;
						rocks[i].visibility = false;
						spawner = true;
						initialise_fire = false;
						fire = false;
					}

					//spawner
					if (spawner == true)
					{
						freeze_cursor = false;
						spawn = +1;
						rocks[spawn].visibility = true;
						reset_rock_postions();
						spawner = false;
					}
				}

			}

			//game over
			if (current_lives == 0)
			{
				//save high score
				if (player_score > high_score)
				{
					high_score = player_score;
				}

				reset_army_positions();
				current_lives = max_lives;
				reset_rock_postions();
				initalise_buildings();
				//loadSprites();
				gameover = true;
			}

			if (gameover == true)
			{
				freeze_cursor = false;
				reset_army_positions();
				current_lives = max_lives;
				reset_rock_postions();
				initalise_buildings();
				//loadSprites();
			}
		}
	}

}




/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
Once the current frame is has finished the buffers are
swapped accordingly and the image shown.
*   @return  void
*/
void AngryBirdsGame::render(const ASGE::GameTime &)
{
	renderer->setFont(0);

	//background
	background_sprite = background.spriteComponent()->getSprite();
	renderer->renderSprite(*background_sprite);

	if (in_menu)
	{
		std::string high_scores = "YOUR CURRENT HIGHSCORE: " + std::to_string(high_score);
		renderer->renderText(high_scores.c_str(), 100, 750, 1.0, ASGE::COLOURS::GHOSTWHITE);

		//reset score
		player_score = 0;

		//reset rocks
		for (int i = 0; i < max_rocks; i++)
		{
			rocks[i].fired = false;
		}

		//get menu sprites
		menu_title_sprite = menu_title.spriteComponent()->getSprite();
		menu_start_sprite = menu_start.spriteComponent()->getSprite();
		menu_exit_sprite = menu_exit.spriteComponent()->getSprite();

		//set pos
		menu_title_sprite->xPos(game_width / 2 - 500);
		menu_title_sprite->yPos(100);
		menu_start_sprite->xPos(game_width / 2 - 230);
		menu_start_sprite->yPos(350);
		menu_exit_sprite->xPos(game_width / 2 - 230);
		menu_exit_sprite->yPos(500);

		//render sprites
		renderer->renderSprite(*menu_title_sprite);
		renderer->renderSprite(*menu_start_sprite);
		renderer->renderSprite(*menu_exit_sprite);
	}

	else if (!in_menu)
	{
		//catapult
		catapult_sprite = catapult.spriteComponent()->getSprite();
		renderer->renderSprite(*catapult_sprite);

		//render building
		for (int j = 0; j < max_buildings; j++)
		{
			//get sprites
			building1_sprite[j] = building1[j].spriteComponent()->getSprite();
			building1_roof_sprite[j] = building1_roof[j].spriteComponent()->getSprite();

			//building1
			building1_sprite[j] = building1[j].spriteComponent()->getSprite();
			if (building1[j].visibility == true)
			{
				renderer->renderSprite(*building1_sprite[j]);
			}

			//building1 roof
			building1_roof_sprite[j] = building1_roof[j].spriteComponent()->getSprite();
			if (building1_roof[j].visibility == true)
			{
				renderer->renderSprite(*building1_roof_sprite[j]);
			}
		}

		//army
		army_sprite = army.spriteComponent()->getSprite();
		renderer->renderSprite(*army_sprite);

		//king
		if (king.visibility == true)
		{
			king_sprite = king.spriteComponent()->getSprite();
			renderer->renderSprite(*king_sprite);
		}

		//rock array
		for (int i = 0; i < max_rocks; i++)
		{
			if (rocks[i].visibility == true)
			{
				if (rocks[i].fired == false)
				{
					renderer->renderSprite(*rocks_sprite[i]);
				}
			}
		}

		//level 1
		if (level_1_intro_bool == true)
		{
			//get menu sprites
			level1_intro_sprite = level1_intro.spriteComponent()->getSprite();
			level_start_sprite = level_start.spriteComponent()->getSprite();
			//set pos
			level1_intro_sprite->xPos(game_width / 2 - 200);
			level1_intro_sprite->yPos(100);
			level_start_sprite->xPos(game_width / 2 - 120);
			level_start_sprite->yPos(480);

			//render sprites
			renderer->renderSprite(*level1_intro_sprite);
			renderer->renderSprite(*level_start_sprite);
		}

		//level 2
		if (level_2_intro_bool == true)
		{
			//get menu sprites
			level2_intro_sprite = level2_intro.spriteComponent()->getSprite();
			level_start_sprite = level_start.spriteComponent()->getSprite();
			//set pos
			level2_intro_sprite->xPos(game_width / 2 - 200);
			level2_intro_sprite->yPos(100);
			level_start_sprite->xPos(game_width / 2 - 120);
			level_start_sprite->yPos(480);

			//render sprites
			renderer->renderSprite(*level2_intro_sprite);
			renderer->renderSprite(*level_start_sprite);
		}

		//level 3
		if (level_3_intro_bool == true)
		{
			//get menu sprites
			level3_intro_sprite = level3_intro.spriteComponent()->getSprite();
			level_start_sprite = level_start.spriteComponent()->getSprite();
			//set pos
			level3_intro_sprite->xPos(game_width / 2 - 200);
			level3_intro_sprite->yPos(100);
			level_start_sprite->xPos(game_width / 2 - 120);
			level_start_sprite->yPos(480);

			//render sprites
			renderer->renderSprite(*level3_intro_sprite);
			renderer->renderSprite(*level_start_sprite);
		}

		if (gameover == true)
		{
			//get gameover sprites
			gameover_sign_sprite = gameover_sign.spriteComponent()->getSprite();
			okay_sprite = okay.spriteComponent()->getSprite();

			//set pos
			gameover_sign_sprite->xPos(game_width / 2 - 300);
			gameover_sign_sprite->yPos(300);
			okay_sprite->xPos(game_width / 2 - 265);
			okay_sprite->yPos(470);

			//render sprites
			renderer->renderSprite(*gameover_sign_sprite);
			renderer->renderSprite(*okay_sprite);
		}

		//render score
		std::string score = "SCORE: " + std::to_string(player_score);
		renderer->renderText(score.c_str(), 100, 750, 1.0, ASGE::COLOURS::GHOSTWHITE);

	}
	//cursor
	cursor_sprite = cursor.spriteComponent()->getSprite();
	renderer->renderSprite(*cursor_sprite);

	//overlay
	overlay_sprite = overlay.spriteComponent()->getSprite();
	renderer->renderSprite(*overlay_sprite);
}