#pragma once
#include <string>
#include <Engine/OGLGame.h>

#include "GameObject.h"
#include "Rect.h"


/**
*  An OpenGL Game based on ASGE.
*/
class AngryBirdsGame :
	public ASGE::OGLGame
{
	public:
		AngryBirdsGame();
		~AngryBirdsGame();
		virtual bool init() override;
	

	private:
		//OTHER
		void keyHandler(const ASGE::SharedEventData data);
		void clickHandler(const ASGE::SharedEventData data);
		void moveHandler(const ASGE::SharedEventData data);
		void setupResolution();
		virtual void update(const ASGE::GameTime &) override;
		virtual void render(const ASGE::GameTime &) override;

		//USEFUL FUNCTIONS
		void reset_values();
		bool initalise_buildings();
		void reset_rock_postions();
		void reset_building_postiions();
		void reset_army_positions();
		void reset_game_states();
		void initalise_rocks();
		void reset_king_positions();
		bool loadSprites();
		bool victory_bool = false;

		//INTS
		int key_callback_id = -1;	     
		int mouse_callback_id = -1;   
		int mouse_move_callback_id = -1; 
		int max_rocks = 8;
		int max_buildings = 4;
		int spawn = 1;
		int house_width = 200;
		int max_lives = 8;
		int current_lives = 8;
		int number_selected = 0;
		int number_rocks = 0;
		int player_score = 0;
		int high_score = 0;
		int current_level = 1;
		//backgrounds
		float foreground_x_pos;
		float midground_x_pos;
		float background_x_pos;
		float foreground_y_pos;
		float midground_y_pos;
		float background_y_pos;
		float overlay_y_pos;
		//items
		float catapult_x_pos;
		float catapult_y_pos;
		float range_x_pos;
		float range_y_pos;
		float building1_roof_x_pos;
		float building1_roof_y_pos;
		float building1_x_pos;
		float building1_y_pos;
		float rock_x_pos;
		float rock_y_pos;
		float army_x_pos;
		float army_y_pos;
		float king_x_pos;
		float king_y_pos;
		//OTHER
		float min_speed = 2;
		float average_speed = 300;
		float max_speed = 600;
		float distance = 0;

		//BOOLS
		bool correct_distance = false;
		bool fire = false;
		bool initialise_fire = false;
		bool spawner = false;
		bool calculate_distance;
		bool freeze_cursor = false;
		//BOOLS GAME STATES
		bool in_menu = true;
		bool begin = false;
		bool level_1 = true;
		bool level_1_intro_bool = true;
		bool level_2 = false;
		bool level_2_intro_bool = false;
		bool level_3 = false;
		bool level_3_intro_bool = false;
		bool gameover = false;
		bool level_reload = false;

		//GAMEOBJECTS
		GameObject cursor;
		GameObject background;
		GameObject catapult;
		GameObject overlay;
		GameObject range;
		GameObject army;
		GameObject king;
		//GAMEOBJECTS ARRAY
		GameObject rocks[8] = {};
		GameObject building1[4] = {};
		GameObject building1_roof[4] = {};
		//GAMEOBJECTS MENU
		GameObject menu_title;
		GameObject menu_start;
		GameObject menu_exit;
		//GAMEOBJECTS GAMEOVER
		GameObject gameover_sign;
		GameObject okay;
		//GAMEOBJECTS LEVEL START
		GameObject level_start;
		//GAMEOBJECTS LEVEL INTROS
		GameObject level1_intro;
		GameObject level2_intro;
		GameObject level3_intro;
		//VICTORY
		GameObject victory;

		//SPRITES
		ASGE::Sprite* cursor_sprite;
		ASGE::Sprite* background_sprite;
		ASGE::Sprite* overlay_sprite;
		ASGE::Sprite* catapult_sprite;
		ASGE::Sprite* range_sprite;
		ASGE::Sprite* army_sprite;
		ASGE::Sprite* king_sprite;
		//SPRITES ARRAY
		ASGE::Sprite* building1_sprite[4] = {};
		ASGE::Sprite* building1_roof_sprite[4] = {};
		ASGE::Sprite* rocks_sprite[8] = {};
		//SPRITES MENU
		ASGE::Sprite* menu_title_sprite;
		ASGE::Sprite* menu_start_sprite;
		ASGE::Sprite* menu_exit_sprite;
		//SPRITES GAMEOVER
		ASGE::Sprite* gameover_sign_sprite;
		ASGE::Sprite* okay_sprite;
		//SPRITES START
		ASGE::Sprite* level_start_sprite;
		//SPRITES INTRO
		ASGE::Sprite* level1_intro_sprite;
		ASGE::Sprite* level2_intro_sprite;
		ASGE::Sprite* level3_intro_sprite;
		//SPRITES
		ASGE::Sprite* victory_sprite;


		//PLAYER INTERACTIONS
		bool leftMouseDown = false;
		bool rightMosueDown = false;
		bool leftMouseUp = true;
		bool rightMouseUp = true;

};