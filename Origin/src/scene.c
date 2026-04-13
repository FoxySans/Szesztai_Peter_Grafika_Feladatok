#define _USE_MATH_DEFINES
#include "scene.h"
#include "math.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>


void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
glBegin(GL_QUADS);

glColor3f(1, 0, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glColor3f(0, 1, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glEnd();

glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.5f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.5f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, 1.0f, 0.5f);

glEnd();

glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.5f);
        
    glColor3f(0.5f, 0.5f, 0.5f);
        
    draw_sphere(0.3f, 20, 20);
    
    glPopMatrix();

glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.5f);
        
    float angle = (float)SDL_GetTicks() / 10.0f; 
    glRotatef(angle, 0.0f, 0.0f, 1.0f); 
        
    glColor3f(0.5f, 0.5f, 0.5f);
    draw_sphere(0.3f, 8, 8);
    glPopMatrix();

    draw_checkerboard();

    glPushMatrix();
        glTranslatef(0.5f, 0.5f, 0.5f);
        angle = (float)SDL_GetTicks() / 10.0f;
        glRotatef(angle, 0, 0, 1);
        glColor3f(0.5f, 0.5f, 0.5f);
        draw_sphere(0.2f, 8, 8);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.2f, 0.8f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        draw_cylinder(0.1f, 0.3f, 15);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.8f, 0.2f, 0.0f);
        glColor3f(1.0f, 0.5f, 0.0f);
        draw_cone(0.1f, 0.3f, 15);
    glPopMatrix();

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_sphere(float radius, int slices, int stacks) {
    int i, j;
    for (i = 0; i <= stacks; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / stacks);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / stacks);
        double z1  = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= slices; j++) {
            double lng = 2 * M_PI * (double)(j - 1) / slices;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);
        }
        glEnd();
    }
}

void draw_checkerboard() {
    int i, j;
    glBegin(GL_QUADS);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) glColor3f(0.2f, 0.2f, 0.2f);
            else glColor3f(0.8f, 0.8f, 0.8f);

            glVertex3f(i/8.0f, j/8.0f, 0.0f);
            glVertex3f((i+1)/8.0f, j/8.0f, 0.0f);
            glVertex3f((i+1)/8.0f, (j+1)/8.0f, 0.0f);
            glVertex3f(i/8.0f, (j+1)/8.0f, 0.0f);
        }
    }
    glEnd();
}

void draw_cylinder(float radius, float height, int nr_points) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= nr_points; i++) {
        float a = (float)i / nr_points * 2.0f * M_PI;
        float x = cos(a) * radius;
        float y = sin(a) * radius;
        glVertex3f(x, y, 0);
        glVertex3f(x, y, height);
    }
    glEnd();
}

void draw_cone(float radius, float height, int nr_points) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, height);
        for (int i = 0; i <= nr_points; i++) {
            float a = (float)i / nr_points * 2.0f * M_PI;
            glVertex3f(cos(a) * radius, sin(a) * radius, 0);
        }
    glEnd();
}