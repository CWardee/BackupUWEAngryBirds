#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

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
bool AngryBirdsGame::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}

	toggleFPS();
	renderer->setWindowTitle("Angry Birds!");
	renderer->setWindowedMode(ASGE::Renderer::WindowMode::WINDOWED);
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	inputs->use_threads = false;


	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &AngryBirdsGame::keyHandler, this);
	
	mouse_callback_id =inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &AngryBirdsGame::clickHandler, this);

	mouse_move_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_MOVE, &AngryBirdsGame::moveHandler, this);

	
	if (!loadBackgrounds())
	{
		return false;
	}

	if (!loadItems())
	{
		return false;
	}

	if (!menu_layer.addSpriteComponent(renderer.get(), "Resources\\Textures\\menu.jpg"))
	{
		return false;
	}

	in_menu = true;

	return true;
}



bool AngryBirdsGame::loadBackgrounds()
{
	std::string background_layer = "Resources\\images\\foreground.png";
	std::string midground_layer = "Resources\\images\\midground.png";
	std::string foreground_layer = "Resources\\images\\foreground.png";
	std::string sky_layer = "Resources\\images\\sky.png";
	std::string overlay_layer = "Resources\\images\\overlay.png";

	//background
	if (!background.addSpriteComponent(renderer.get(), background_layer))
	{
		return false;
	}
	//midground
	if (!midground.addSpriteComponent(renderer.get(), midground_layer))
	{
		return false;
	}
	//sky
	if (!sky.addSpriteComponent(renderer.get(), sky_layer))
	{
		return false;
	}
	//overlay
	if (!overlay.addSpriteComponent(renderer.get(), overlay_layer))
	{
		return false;
	}

	std::string catapult_layer = "Resources\\images\\catapult.png";


}



bool AngryBirdsGame::loadItems()
{
	std::string catapult_layer = "Resources\\images\\catapult.png";
	std::string rock_layer = "Resources\\images\\rock1.png";

	//catapult
	if (!catapult.addSpriteComponent(renderer.get(), catapult_layer))
	{
		return false;
	}

	//rock
	if (!rock.addSpriteComponent(renderer.get(), rock_layer))
	{
		return false;
	}

	return true;
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
	game_width = 1920;
	game_height = 1080;
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
		signalExit();
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
	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
}

//cursor movement
void AngryBirdsGame::moveHandler(const ASGE::SharedEventData data)
{
	auto move = static_cast<const ASGE::MoveEvent*>(data.get());
	//inputs->setCursorMode(ASGE::CursorMode::HIDDEN);
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

	if (!in_menu)
	{
		//rock sprite
		rock_sprite = rock.spriteComponent()->getSprite();

		//sky sprite
		sky_sprite = sky.spriteComponent()->getSprite();

		//catapult sprite
		catapult_sprite = catapult.spriteComponent()->getSprite();

		//overlay sprite
		overlay_sprite = overlay.spriteComponent()->getSprite();

		//foreground x_pos
		foreground_sprite = background.spriteComponent()->getSprite();
		foreground_x_pos = foreground_sprite->xPos();
		foreground_y_pos = foreground_sprite->yPos();

		//midground x_pos
		midground_sprite = midground.spriteComponent()->getSprite();
		midground_x_pos = midground_sprite->xPos();
		midground_y_pos = foreground_sprite->yPos();

		//catapult x_pos
		catapult_sprite = catapult.spriteComponent()->getSprite();
		catapult_x_pos = catapult_sprite->xPos();

		//midground_y_pos = 50;
		midground_sprite->yPos(midground_y_pos);

		//cursor
		double cursor_x_pos, cursor_y_pos;
		inputs->getCursorPos(cursor_x_pos, cursor_y_pos);
		/*
		//move background right
		if (cursor_x_pos > 1600)
		{
			//foreground
			foreground_x_pos -= average_speed *
			dt_sec;
			foreground_sprite->xPos(foreground_x_pos);

			//midground
			midground_x_pos -= min_speed * dt_sec;
			midground_sprite->xPos(midground_x_pos);

			//catapult
			catapult_x_pos -= average_speed * dt_sec;
			catapult_sprite->xPos(catapult_x_pos);

			//rock
			rock_x_pos -= average_speed * dt_sec;
			rock_sprite->xPos(rock_x_pos);
		}

		//move background left
		if (cursor_x_pos < 300)
		{
			//foreground
			foreground_x_pos += average_speed * dt_sec;
			foreground_sprite->xPos(foreground_x_pos);

			//midground
			midground_x_pos += min_speed * dt_sec;
			midground_sprite->xPos(midground_x_pos);

			//catapult
			catapult_x_pos += average_speed * dt_sec;
			catapult_sprite->xPos(catapult_x_pos);

			//rock
			rock_x_pos += average_speed * dt_sec;
			rock_sprite->xPos(rock_x_pos);
		}
		*/

		rock_x_pos += min_speed * dt_sec;
		int a = 3;
		//rock_y_pos = a * (rock_x_pos - 1000)*(rock_x_pos - 1000) / 2 / 1000;
		rock_y_pos = a * ((rock_x_pos - 600)*(rock_x_pos - 600) / 2 / 1000) + 800;
		//rock_y_pos += min_speed * dt_sec;
		rock_sprite->yPos(rock_y_pos);
		rock_sprite->xPos(rock_x_pos);
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
	
	if (in_menu)
	{
		renderer->renderSprite(*menu_layer.spriteComponent()->getSprite());

		catapult_sprite = catapult.spriteComponent()->getSprite();
		catapult_x_pos = catapult_sprite->xPos();
		catapult_x_pos = 600;
		catapult_sprite->xPos(catapult_x_pos);

		catapult_y_pos = catapult_sprite->yPos();
		catapult_y_pos = 800;
		catapult_sprite->yPos(catapult_y_pos);

		rock_sprite = rock.spriteComponent()->getSprite();
		rock_x_pos = rock_sprite->xPos();
		rock_x_pos = 400;
		rock_sprite->xPos(rock_x_pos);

	}

	else
	{

	//	renderer->renderSprite(*background_layer.spriteComponent()->getSprite());
		renderer->renderSprite(*sky_sprite);
		renderer->renderSprite(*midground_sprite);
		renderer->renderSprite(*foreground_sprite);
		//renderer->renderSprite(*catapult_sprite);
		renderer->renderSprite(*overlay_sprite);
		renderer->renderSprite(*rock_sprite);
	}
}


/*
filename += std::to_string(std::rand() % 3 + 1);
filename += ".png";
*/