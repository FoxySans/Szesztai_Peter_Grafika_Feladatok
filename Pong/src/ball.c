#include "ball.h"

#include <GL/gl.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 200;
    ball->speed_y = 200;
    ball->angle = 0.0f;
    ball->rotation_speed = 100.0f;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->angle += ball->rotation_speed * time;
}

void set_ball_position(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void change_ball_radius(Ball* ball, float amount)
{
    ball->radius += amount;
    if (ball->radius < 5) {
        ball->radius = 5;
    }
    else if(ball->radius > 100){
        ball->radius = 100;
    }
}

void render_ball(Ball* ball)
{
    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->angle, 0, 0, 1);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    
    double step = 0.8;
    double current_a = 0;
    while (current_a < 2.0 * M_PI + 1) {
        if ((int)(current_a * 10) % 2 == 0) glColor3f(1.0, 0.5, 0.0);
        else glColor3f(1.0, 0.9, 0.8);

        float x = cos(current_a) * ball->radius;
        float y = sin(current_a) * ball->radius;
        glVertex2f(x, y);
        current_a += step;
    }
    glEnd();
    glPopMatrix();
}
