#pragma once

#include "cocos2d.h"

const float DISPLAY_TIME_SPLASH_SCENE = 2.5;
const float TRANSITION_TIME = 2.5;
const double PIPE_SPAWN_FREQUENCY = 0.003;//появление труб

const int PIPE_GAP = 3; //величена разрыва труб
const double UPPER_SCREEN_PIPE_THRESHOLD = 0.65;//длина трубы
const double LOWER_SCREEN_PIPE_THRESHOLD = 0.35;

const double PIPE_MOVEMENT_SPEED = 0.01;

const int BIRD_COLLISION_BITMASK = 1;//битовая маска для столкновений
const int OBSTACLE_COLLISION_BITMASK = 2;
const int POINT_COLLISION_BITMASK = 3;

const double BIRD_FALLING_SPEED = 0.0025;
const double BIRD_FLYING_SPEED = 0.00375;
const double BIRD_FLY_DURATION = 0.25;

const double SCORE_FONT_SIZE = 0.1;
