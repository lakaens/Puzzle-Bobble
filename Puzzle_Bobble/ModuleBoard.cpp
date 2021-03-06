#include"ModuleBoard.h"
#include "ModuleAudio.h"
#include <time.h>
#include <stdlib.h> 
#include <math.h>
ModuleBoard::ModuleBoard()
{
	int x, y;
	int i = 0;
	int j = 0;
	counter_left = 0;
	counter_right = 0;
	//LEFT
	for (y = 32 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = 24 * SCREEN_SIZE - 16; x < 136 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
			{
				board_left.push_back(new iPoint(x, y));
				j++;
			}
		}
		else
		{
			for (x = 32 * SCREEN_SIZE - 16; x < 128 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
			{
				board_left.push_back(new iPoint(x, y));
				j++;
				
			}
		}
		i++;
	}

	j = 0;
	//RIGHT
	for (y = 32 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = 184 * SCREEN_SIZE - 16; x < 296 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
			{
				board_right.push_back(new iPoint(x, y));
				j++;
			}
		}
		else
		{
			for (x = 192 * SCREEN_SIZE - 16 ; x < 288 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
			{
				board_right.push_back(new iPoint(x, y));
				j++;

			}
		}
		i++;
	}
	boardDone = true;
}



ModuleBoard::~ModuleBoard(){};

bool ModuleBoard::Start(){ 
	

 	if (boardDone != true){
		int x, y;
		int i = 0;
		int j = 0;
		counter_left = 0;
		counter_right = 0;
		//LEFT

		for (y = 32 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
		{
			if (i % 2 == 0)
			{
				for (x = 24 * SCREEN_SIZE - 16; x < 136 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
				{
					board_left.push_back(new iPoint(x, y));
					j++;
				}
			}
			else
			{
				for (x = 32 * SCREEN_SIZE - 16; x < 128 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
				{
					board_left.push_back(new iPoint(x, y));
					j++;

				}
			}
			i++;
		}

		j = 0;
		//RIGHT
		for (y = 32 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
		{
			if (i % 2 == 0)
			{
				for (x = 184 * SCREEN_SIZE - 16; x < 296 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
				{
					board_right.push_back(new iPoint(x, y));
					j++;
				}
			}
			else
			{
				for (x = 192 * SCREEN_SIZE - 16; x < 288 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
				{
					board_right.push_back(new iPoint(x, y));
					j++;

				}
			}
			i++;
		}
		boardDone = true;
	}
	return true; };


bool ModuleBoard::CleanUp()
{
	int i;
	
	for (i = 0; i < board_left.size(); i++)
	{
		if (board_left[i] != nullptr){
			delete board_left[i];
			board_left[i] = nullptr;

		}	
	}
	for (i = 0; i < board_right.size(); i++)
	{
		if (board_right[i] != nullptr){
			delete board_right[i];
			board_right[i] = nullptr;
		}
	}
	boardDone = false;
	board_left.clear();
	board_right.clear();
	return true;
}

void ModuleBoard::CheckPositionLeft(Sphere* actual_sphere)
{
	int i = 0;
	int min_distance;
	int square_index = 0;
	
	min_distance = 100;//Fixes corner bug

	for (i = 0;i< NUM_SQUARES; i++)
	{
		if (board_left[i]->Empty == true)
		{
			if (board_left[i]->DistanceTo(actual_sphere->position) < min_distance)
			{
				min_distance = board_left[i]->DistanceTo(actual_sphere->position);
				square_index = i;
			}
		}
	}
	actual_sphere->position.x = board_left[square_index]->x;
	actual_sphere->position.y = board_left[square_index]->y;
	actual_sphere->pos_board.x = board_left[square_index]->x;
	actual_sphere->pos_board.y = board_left[square_index]->y;
	board_left[square_index]->Empty = false;
	actual_sphere->board_index = square_index;	
}

void ModuleBoard::CheckPositionRight(Sphere* actual_sphere)
{
	int i = 0;
	int min_distance;
	int square_index = 0;

	min_distance = 100;//Fixes corner bug

	for (i = 0; i< NUM_SQUARES; i++)
	{
		if (board_right[i]->Empty == true)
		{
			if (board_right[i]->DistanceTo(actual_sphere->position) < min_distance)
			{
				min_distance = board_right[i]->DistanceTo(actual_sphere->position);
				square_index = i;
			}
		}
	}
	actual_sphere->position.x = board_right[square_index]->x;
	actual_sphere->position.y = board_right[square_index]->y;
	actual_sphere->pos_board.x = board_right[square_index]->x;
	actual_sphere->pos_board.y = board_right[square_index]->y;
	board_right[square_index]->Empty = false;
	actual_sphere->board_index = square_index;
}

void ModuleBoard::CreateMap1_Left(int number[]){

	int i = 0;
	for (i= 0 ; i < NUM_SQUARES;i++)
	{
		if (number[i] >= 0 && number[i] < 8){
			App->spheres->SetSphere(App->spheres->spheres[number[i]], board_left[i]->x, board_left[i]->y, i, COLLIDER_SPHERE_LEFT);
			board_left[i]->Empty = false;
			}				
		}
}

void ModuleBoard::CreateMap1_Right(int number[]){

	int i = 0;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (number[i] >= 0 && number[i] < 8){
			App->spheres->SetSphere(App->spheres->spheres[number[i]], board_right[i]->x, board_right[i]->y, i, COLLIDER_SPHERE_RIGHT);
			board_right[i]->Empty = false;
		}
	}
}

void ModuleBoard::BoardDownLeft(int &counter){
	Mix_PlayChannel(-1, App->audio->roof_fall, 0);
	srand(time(NULL));
	int random = 0;
	int i;
	int x, y;
	y = 32 * SCREEN_SIZE - 16;
	for (i = 0; i < board_left.size(); i++){
		board_left[i]->y += 14 * SCREEN_SIZE;
	}

	for (i = 0; i < App->spheres->last_sphere_left; i++){
		if (App->spheres->active_left[i] != nullptr){
			App->spheres->active_left[i]->position.y += 14 * SCREEN_SIZE;
		}
	}
	if (counter % 2 == 0){
		x = 128 * SCREEN_SIZE - 16;//96
		for (i = 0; i < 7; i++){
			board_left.push_front(new iPoint(x, y));
			x -= 16 * SCREEN_SIZE;
		}
		for (i = 0; i < 7; i++)
		{
			 random = rand() % 8;

			App->spheres->SetSphere(App->spheres->spheres[random], board_left[i]->x, board_left[i]->y, i, COLLIDER_SPHERE_LEFT);
			board_left[i]->Empty = false;
		}
	}
	else{
		x = 136 * SCREEN_SIZE - 16;//112
		for (i = 0; i < 8; i++){
			board_left.push_front(new iPoint(x, y));
			x -= 16 * SCREEN_SIZE;

		}
		for (i = 0; i < 8; i++)
		{
			 random = rand() % 8;
			App->spheres->SetSphere(App->spheres->spheres[random], board_left[i]->x, board_left[i]->y, i, COLLIDER_SPHERE_LEFT);
			board_left[i]->Empty = false;
		}
	}
	counter++;
	for (i = 0; i < board_left.size(); i++){

		if (board_left[i]->Empty == false){
			for (int j = 0; j < App->spheres->last_sphere_left; j++){
				if (App->spheres->active_left[j] != nullptr&& App->spheres->active_left[j]->position.x == board_left[i]->x&& App->spheres->active_left[j]->position.y == board_left[i]->y){
					App->spheres->active_left[j]->board_index = i;
				}
			}
		}
	}
	

}

void ModuleBoard::BoardDownRight(int &counter)
{
	Mix_PlayChannel(-1, App->audio->roof_fall, 0);
	srand(time(NULL));
	int random = 0;
	int i;
	int x, y;
	y = 32 * SCREEN_SIZE - 16;
	for (i = 0; i < board_right.size(); i++){
		board_right[i]->y += 14 * SCREEN_SIZE;
	}

	for (i = 0; i < App->spheres->last_sphere_right; i++){
		if (App->spheres->active_right[i] != nullptr){
			App->spheres->active_right[i]->position.y += 14 * SCREEN_SIZE;
		}
	}
	if (counter % 2 == 0){
		x = 128 + 224 * SCREEN_SIZE - 16;
		for (i = 0; i < 7; i++){
			board_right.push_front(new iPoint(x, y));
			x -= 16 * SCREEN_SIZE;
		}
		for (i = 0; i < 7; i++)
		{
			random = rand() % 8;

			App->spheres->SetSphere(App->spheres->spheres[random], board_right[i]->x, board_right[i]->y, i, COLLIDER_SPHERE_RIGHT);
			board_right[i]->Empty = false;
		}
	}
	else{
		x = 136+ 228 * SCREEN_SIZE  - 16;
		for (i = 0; i < 8; i++){
			board_right.push_front(new iPoint(x, y));
			x -= 16 * SCREEN_SIZE;

		}
		for (i = 0; i < 8; i++)
		{
			random = rand() % 8;
			App->spheres->SetSphere(App->spheres->spheres[random], board_right[i]->x, board_right[i]->y, i, COLLIDER_SPHERE_RIGHT);
			board_right[i]->Empty = false;
		}
	}
	counter++;
	for (i = 0; i < board_right.size(); i++){

		if (board_right[i]->Empty == false){
			for (int j = 0; j < App->spheres->last_sphere_right; j++){
				if (App->spheres->active_right[j] != nullptr&& App->spheres->active_right[j]->position.x == board_right[i]->x&& App->spheres->active_right[j]->position.y == board_right[i]->y){
					App->spheres->active_right[j]->board_index = i;
				}
			}
		}
	}
}


bool ModuleBoard::CheckWinR()
{
	int i = 0;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (board_right[i]->Empty != true)
			return false;
	}


	return true;
}

bool ModuleBoard::CheckWinL()
{
	int i = 0;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (board_left[i]->Empty != true)
			return false;
	}


	return true;
}
