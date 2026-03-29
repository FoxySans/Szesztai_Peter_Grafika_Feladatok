#include "pong.h"
#include <GL/gl.h>
#include <stdbool.h>

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    pong->left_score = 0;
    pong->right_score = 0;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void draw_segment(float x, float y, bool horizontal) {
    float width = horizontal ? 40 : 10;
    float height = horizontal ? 10 : 40;
    
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void draw_digit(float x, float y, int digit) {
    glColor3f(1.0, 1.0, 1.0); // Fehér számok

    // Felső (a)
    if (digit != 1 && digit != 4) draw_segment(x + 5, y, true);
    // Középső (g)
    if (digit > 1 && digit != 7) draw_segment(x + 5, y + 45, true);
    // Alsó (d)
    if (digit != 1 && digit != 4 && digit != 7) draw_segment(x + 5, y + 90, true);
    
    // Bal felső (f)
    if (digit == 0 || digit > 3 && digit != 7) draw_segment(x, y + 5, false);
    // Jobb felső (b)
    if (digit != 5 && digit != 6) draw_segment(x + 45, y + 5, false);
    // Bal alsó (e)
    if (digit == 0 || digit == 2 || digit == 6 || digit == 8) draw_segment(x, y + 50, false);
    // Jobb alsó (c)
    if (digit != 2) draw_segment(x + 45, y + 50, false);
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
    draw_digit(pong->width / 2 - 100, 50, pong->left_score % 10);
    draw_digit(pong->width / 2 + 50, 50, pong->right_score % 10);

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
            ball->rotation_speed *= -1;
        }
    }

    /* RIGHT PAD COLLISION */
    if (ball->x + ball->radius >= right->x) {
        if (ball->y >= right->y && ball->y <= right->y + right->height) {
            ball->x = right->x - ball->radius;
            ball->speed_x *= -1;
            ball->rotation_speed *= 1;
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

    if (ball->x + ball->radius < 0) {
        pong->right_score++;
        init_ball(ball, pong->width / 2, pong->height / 2);
    }

    if (ball->x - ball->radius > pong->width) {
        pong->left_score++;
        init_ball(ball, pong->width / 2, pong->height / 2); 
    }
}

void set_ball_position_in_pong(Pong* pong, float x, float y)
{
    set_ball_position(&(pong->ball), x, y);
}