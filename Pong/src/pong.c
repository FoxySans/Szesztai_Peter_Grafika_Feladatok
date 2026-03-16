#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void bounce_ball(Pong* pong)
{
    Ball* ball = &pong->ball;
    Pad* left = &pong->left_pad;
    Pad* right = &pong->right_pad;

    /* LEFT PAD COLLISION */
    if (ball->x - ball->radius <= left->x + left->width) {
        if (ball->y >= left->y && ball->y <= left->y + left->height) {
            ball->x = left->x + left->width + ball->radius;
            ball->speed_x *= -1;
        }
    }

    /* RIGHT PAD COLLISION */
    if (ball->x + ball->radius >= right->x) {
        if (ball->y >= right->y && ball->y <= right->y + right->height) {
            ball->x = right->x - ball->radius;
            ball->speed_x *= -1;
        }
    }

    /* TOP WALL */
    if (ball->y - ball->radius < 0) {
        ball->y = ball->radius;
        ball->speed_y *= -1;
    }

    /* BOTTOM WALL */
    if (ball->y + ball->radius > pong->height) {
        ball->y = pong->height - ball->radius;
        ball->speed_y *= -1;
    }
}

void set_ball_position_in_pong(Pong* pong, float x, float y)
{
    set_ball_position(&(pong->ball), x, y);
}