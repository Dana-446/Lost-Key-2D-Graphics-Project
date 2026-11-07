#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

int scene = 1;

float studentX = 0.0f;
float studentY = -0.38f;
float idleT = 0.0f;

bool standUp = false;
bool searching = false;

float searchT = 0.0f;

float minuteAngle = 90.0f;
float hourAngle = 30.0f;

float friendX = 0.15f;
float friendY = -0.25f;

int dialogueState = 0;
float talkTimer = 0.0f;

bool keyFound = false;
int scene3State = 0; 
float scene3Timer = 0.0f;

bool scene4Init = false;
float scene4StartX_student = 0.0f;
float scene4StartX_friend  = 0.1f;

bool scene4Active = false;
int lastScene = 1;

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// student
void drawStudent(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    // head
    glColor3f(1.0f, 0.85f, 0.7f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 2 * 3.1416f * i / 100;
        glVertex2f(0.05f * cos(a), 0.05f * sin(a));
    }
    glEnd();

    // hair
    glColor3f(0.1f, 0.05f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 3.1416f * i / 100;
        glVertex2f(0.06f * cos(a), 0.06f * sin(a) + 0.02f);
    }
    glEnd();

    // eyes
    glColor3f(0, 0, 0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(-0.015f, 0.01f);
    glVertex2f(0.015f, 0.01f);
    glEnd();

    // dress
    glColor3f(0.9f, 0.2f, 0.5f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.0f, -0.2f);
    glEnd();

    glLineWidth(4.0f);

    // arms
    glColor3f(1.0f, 0.85f, 0.7f);
    glBegin(GL_LINES);
    glVertex2f(-0.05f, -0.1f);
    glVertex2f(-0.1f, -0.15f);
    glVertex2f(0.05f, -0.1f);
    glVertex2f(0.1f, -0.15f);
    glEnd();

    // legs
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-0.02f, -0.2f);
    glVertex2f(-0.02f, -0.32f);
    glVertex2f(0.02f, -0.2f);
    glVertex2f(0.02f, -0.32f);
    glEnd();
    glLineWidth(1.0f);
    
    glPopMatrix();
}

void drawFriend(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    // head
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 2 * 3.1416f * i / 100;
        glVertex2f(0.04f * cos(a), 0.04f * sin(a));
    }
    glEnd();

    // hair
    glColor3f(0.2f, 0.1f, 0.05f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 3.1416f * i / 100;
        glVertex2f(0.05f * cos(a), 0.05f * sin(a) + 0.02f);
    }
    glEnd();

    // body
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.04f, -0.05f);
    glVertex2f(0.04f, -0.05f);
    glVertex2f(0.0f, -0.18f);
    glEnd();

    // arms
    glColor3f(1.0f, 0.8f, 0.6f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    glVertex2f(-0.04f, -0.08f);
    glVertex2f(-0.09f, -0.12f);

    glVertex2f(0.04f, -0.08f);
    glVertex2f(0.09f, -0.12f);

    glEnd();

    // legs
    glBegin(GL_LINES);

    glVertex2f(-0.015f, -0.18f);
    glVertex2f(-0.02f, -0.32f);

    glVertex2f(0.015f, -0.18f);
    glVertex2f(0.02f, -0.32f);

    glEnd();

    glLineWidth(1.0f);

        glPopMatrix();
}

void drawSpeech(float x, float y, const char* text) {
    glColor3f(0, 0, 0);
    drawText(x, y + 0.15f, text);
}

void drawDesk(float x, float y, float s) {

    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);


    glColor3f(0.55f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(0.15f, 0.05f);
    glVertex2f(0.15f, -0.05f);
    glVertex2f(-0.15f, -0.05f);
    glEnd();

    glColor3f(0.2f, 0.1f, 0.05f); 
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(0.15f, 0.05f);
    glVertex2f(0.15f, -0.05f);
    glVertex2f(-0.15f, -0.05f);
    glEnd();

    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_LINES);

    glVertex2f(-0.12f, -0.05f);
    glVertex2f(-0.12f, -0.2f);

    glVertex2f(0.12f, -0.05f);
    glVertex2f(0.12f, -0.2f);

    glVertex2f(-0.12f, -0.2f);
    glVertex2f(0.12f, -0.2f);

    glEnd();

    glPopMatrix();
}

// scene1
void drawScene1() {

    // wall
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    // floor
    glColor3f(0.78f, 0.78f, 0.78f);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, -0.3f);
    glVertex2f(-1, -0.3f);
    glEnd();

    // blackboard
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.70f, -0.10f);
    glVertex2f(0.50f, -0.10f);
    glVertex2f(0.50f, 0.45f);
    glVertex2f(-0.70f, 0.45f);
    glEnd();

    glColor3f(0.05f, 0.35f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-0.67f, -0.05f);
    glVertex2f(0.47f, -0.05f);
    glVertex2f(0.47f, 0.42f);
    glVertex2f(-0.67f, 0.42f);
    glEnd();

    glColor3f(1, 1, 1);
    drawText(-0.6f, 0.20f, "2026 / 05 / 03");
    drawText(-0.6f, 0.13f, "Computer Graphics Basics");


    // clock
    glColor3f(0.4f, 0.25f, 0.1f);   
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 2 * 3.1416f * i / 100;
        glVertex2f(0.6f + 0.10f * cos(a), 0.75f + 0.10f * sin(a));
    }
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float a = 2 * 3.1416f * i / 100;
        glVertex2f(0.6f + 0.085f * cos(a), 0.75f + 0.085f * sin(a));
    }
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++) {
        float a = 2 * 3.1416f * i / 50;
        glVertex2f(0.6f + 0.01f * cos(a), 0.75f + 0.01f * sin(a));
    }
    glEnd();

    float cx = 0.6f;
    float cy = 0.75f;

    // clock hands
    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + 0.07f * cos(minuteAngle * 3.1416f / 180.0f),
               cy + 0.07f * sin(minuteAngle * 3.1416f / 180.0f));
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx + 0.05f * cos(hourAngle * 3.1416f / 180.0f),
               cy + 0.05f * sin(hourAngle * 3.1416f / 180.0f));
    glEnd();

    glLineWidth(1.0f);

    // door
    glColor3f(0.45f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0.65f, -0.3f);
    glVertex2f(0.95f, -0.3f);
    glVertex2f(0.95f, 0.35f);
    glVertex2f(0.65f, 0.35f);
    glEnd();

    // knob
    glColor3f(1, 0.8f, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++) {
        float a = 2 * 3.1416f * i / 50;
        glVertex2f(0.88f + 0.01f * cos(a), 0.0f + 0.01f * sin(a));
    }
    glEnd();

    drawDesk(-0.45f, -0.25f, 1.5f);
    drawDesk(0.35f, -0.25f, 1.5f);

    drawStudent(studentX, studentY);

    drawDesk(-0.5f, -0.5f, 2.3f);
    drawDesk(0.5f, -0.5f, 2.3f);

    if (!standUp)
        drawSpeech(studentX, studentY, "Where is my key...");
    else
        drawSpeech(studentX, studentY, "I need to find it!");
}

void drawScene2() {

    // floor
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);      
    glVertex2f(1.0f, -1.0f);       
    glVertex2f(0.16f, 0.26f);      
    glVertex2f(-0.16f, 0.26f);
    glEnd();

    // ceiling
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, 0.48f);
    glVertex2f(0.2f, 0.48f);
    glVertex2f(1.0f, 1.0f); 
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // walls
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.16f, 0.26f);
    glVertex2f(-0.2f, 0.48f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.16f, 0.26f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.2f, 0.48f);
    glEnd();

    
    

    // windows
    glColor3f(0.25f, 0.25f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.9f, 0.60f);
    glVertex2f(-0.28f, 0.45f);
    glVertex2f(-0.28f, 0.32f);
    glVertex2f(-0.90f, -0.30f);
    glEnd();

    glColor3f(0.70f, 0.85f, 0.95f);

    glBegin(GL_QUADS);

    glVertex2f(-0.88f, 0.57f);
    glVertex2f(-0.29f, 0.43f);
    glVertex2f(-0.29f, 0.33f);
    glVertex2f(-0.88f, -0.26f);
    glEnd();

    glColor3f(0.85f, 0.95f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.75f, 0.50f);
    glVertex2f(-0.55f, 0.10f);
    glEnd();

    glLineWidth(1.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    glVertex2f(-0.65f, 0.52f);
    glVertex2f(-0.65f, -0.03f);

    glVertex2f(-0.49f, 0.48f);
    glVertex2f(-0.49f, 0.12f);

    glVertex2f(-0.39f, 0.45f);
    glVertex2f(-0.39f, 0.21f);

    glEnd();

    glLineWidth(1.0f);


    // lockers
    glColor3f(0.55f, 0.55f, 0.60f);
    glBegin(GL_QUADS);
    glVertex2f(-0.90f, -0.38f);
    glVertex2f(-0.90f, -0.85f);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.75f, -0.38f);
    glEnd();

    glColor3f(0.50f, 0.50f, 0.55f);
    glBegin(GL_QUADS);
    glVertex2f(-0.90f, -0.38f);
    glVertex2f(-0.29f, 0.31f);
    glVertex2f(-0.26f, 0.31f);
    glVertex2f(-0.75f, -0.38f);
    glEnd();
    glColor3f(0.45f, 0.45f, 0.50f);
    glBegin(GL_QUADS);
    glVertex2f(-0.75f, -0.85f);
    glVertex2f(-0.26f, 0.11f);
    glVertex2f(-0.26f, 0.31f);
    glVertex2f(-0.75f, -0.38f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(1.5f);

    glBegin(GL_LINES);

    glVertex2f(-0.65f, -0.25f);
    glVertex2f(-0.65f, -0.64f);

    glVertex2f(-0.54f, -0.12f);
    glVertex2f(-0.54f, -0.43f);

    glVertex2f(-0.46f, -0.25f);
    glVertex2f(-0.46f, -0.00f);

    glVertex2f(-0.38f, 0.12f);
    glVertex2f(-0.38f, -0.11f);

    glVertex2f(-0.31f, 0.220f);
    glVertex2f(-0.31f, 0.03f);

    glEnd();

    glLineWidth(1.0f);


    // door
    glColor3f(0.45f, 0.25f, 0.12f);
    glBegin(GL_QUADS);
    glVertex2f(0.50f, -0.25f);
    glVertex2f(0.50f, 0.35f);
    glVertex2f(0.70f, 0.44f);
    glVertex2f(0.70f, -0.55f);
    glEnd();

    glColor3f(0.55f, 0.30f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(0.52f, -0.23f);
    glVertex2f(0.52f, 0.33f);
    glVertex2f(0.67f, 0.40f);
    glVertex2f(0.67f, -0.45f);
    glEnd();

    glColor3f(0.9f, 0.75f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++) {
        float a = 2 * 3.1416f * i / 50;
        glVertex2f(0.63f + 0.01f * cos(a),
                   0.05f + 0.01f * sin(a));
    }
    glEnd();

    glColor3f(0.8f, 0.8f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-0.16f, 0.26f);
    glVertex2f(0.16f, 0.26f);
    glVertex2f(0.2f, 0.48f);
    glVertex2f(-0.2f, 0.48f);
    glEnd();

    drawStudent(studentX, studentY);
    drawFriend(0.1f, -0.3f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.3f, 0.8f, "School Corridor");


    if (dialogueState == 1) {
        drawSpeech(studentX, studentY, "Hey, have you seen my key?");
    }

    if (dialogueState == 2) {
        drawSpeech(0.1f, -0.3f, "I will help you searching.");
    }

}

void drawScene3() {

    // sky
    glColor3f(0.55f, 0.80f, 1.0f); 
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    // grass
    glColor3f(0.25f, 0.65f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 0.25f);
    glVertex2f(-1, 0.25f);
    glEnd();


    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.25f);
    glVertex2f(1.0f, 0.25f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();

    // trees

    glColor3f(0.45f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7443f, 0.4473f);
    glVertex2f(-0.7443f, 0.0038f);
    glVertex2f(-0.6879f, 0.0038f);
    glVertex2f(-0.6879f, 0.4473f);
    glEnd();

    glColor3f(0.1f, 0.6f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i++) {
        float a = 2 * 3.1416f * i / 8;
        glVertex2f(-0.72f + 0.25f * cos(a),
                   0.57f + 0.20f * sin(a));
    }
    glEnd();

    glColor3f(0.45f, 0.25f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0.7029f, 0.0038f);
    glVertex2f(0.7029f, 0.4736f);
    glVertex2f(0.7781f, 0.4736f);
    glVertex2f(0.7781f, 0.0038f);
    glEnd();

    glColor3f(0.1f, 0.6f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; i++) {
        float a = 2 * 3.1416f * i / 8;
        glVertex2f(0.73f + 0.25f * cos(a),
                   0.65f + 0.20f * sin(a));
    }
    glEnd();

    // bnch
    glColor3f(0.55f, 0.35f, 0.15f);

    glBegin(GL_QUADS);
    glVertex2f(-0.3233f, 0.2368f);
    glVertex2f(0.2894f, 0.2368f);
    glVertex2f(0.2894f, 0.2857f);
    glVertex2f(-0.3233f, 0.2857f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.3233f, 0.1579f);
    glVertex2f(0.2857f, 0.1579f);
    glVertex2f(0.2857f, 0.2105f);
    glVertex2f(-0.3233f, 0.2105f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.3157f, 0.0827f);
    glVertex2f(0.29f, 0.0827f);
    glVertex2f(0.29f, 0.1052f);
    glVertex2f(-0.3157f, 0.1052f);
    glEnd();
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.30f, 0.08f); glVertex2f(-0.30f, -0.023f);
    glVertex2f(0.0f, 0.08f);  glVertex2f(0.0f, -0.023f);
    glVertex2f(0.27f, 0.08f); glVertex2f(0.27f, -0.023f);
    glEnd();
    glLineWidth(1.0f);


    glColor3f(1.0f, 0.85f, 0.1f);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 10; i++) {
        float a = 2 * 3.1416f * i / 10;
        glVertex2f(-0.02f + 0.017f * cos(a),
                   0.12f + 0.019f * sin(a));
    }
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.01f, 0.13f);
    glVertex2f(0.06f, 0.13f);
    glVertex2f(0.06f, 0.12f);
    glVertex2f(-0.01f, 0.12f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.03f, 0.12f);
    glVertex2f(0.05f, 0.12f);
    glVertex2f(0.05f, 0.10f);
    glVertex2f(0.03f, 0.10f);
    glEnd();

    drawStudent(-0.2f, -0.3f);
    drawFriend(0.2f, -0.3f);

if (scene3State == 0) {
    drawText(-0.2f, 0.7f, "...");
}

if (scene3State == 1) {
    drawSpeech(-0.2f, -0.3f, "There it is!");
}

if (scene3State == 2) {
    drawSpeech(-0.2f, -0.3f, "Thank you!");
    drawSpeech(0.2f, -0.3f, "Good job!");
}

}

void drawScene4() {
    // sky
    glColor3f(0.55f, 0.80f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.75f);
    glVertex2f(1.0f, 0.75f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // wall
    glColor3f(0.4f, 0.4f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.50f);
    glVertex2f(1.0f, 0.50f);
    glVertex2f(1.0f, 0.75f);
    glVertex2f(-1.0f, 0.75f);
    glEnd();


    // road and sidewalks
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.3533f);
    glVertex2f(1.0f, 0.3533f);
    glVertex2f(1.0f, 0.5074f);
    glVertex2f(-1.0f, 0.5074f);
    glEnd();

    glColor3f(0.70f, 0.70f, 0.70f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.2518f);
    glVertex2f(1.0f, -0.2518f);
    glVertex2f(1.0f, -0.0038f);
    glVertex2f(-1.0f, -0.0038f);
    glEnd();

    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4924f, -1.0f);
    glVertex2f(0.4924f, -1.0f);
    glVertex2f(0.4924f, -0.2669f);
    glVertex2f(-0.4924f, -0.2669f);
    glEnd();


    // grass
    glColor3f(0.25f, 0.65f, 0.25f);

    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.4999f, -1.0f);
    glVertex2f(-0.4999f, -0.2518f);
    glVertex2f(-1.0f, -0.2518f);
    glEnd();

    glBegin(GL_QUADS); 
    glVertex2f(0.5037f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.2631f);
    glVertex2f(0.5037f, -0.2631f);
    glEnd();


 
    glLineWidth(1.0f);

    drawStudent(studentX, studentY);
    drawFriend(friendX, friendY);

    drawSpeech(studentX, studentY,
        "I'll make sure to check for it every day.");


    // gate
    glColor3f(0.4f, 0.4f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.25f);
    glVertex2f(-0.5f, -0.25f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(-1.0f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.5f, -0.25f);
    glVertex2f(1.0f, -0.25f);
    glVertex2f(1.0f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glEnd();

    glColor3f(0.4f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.25f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(-0.75f, 0.0f);
    glVertex2f(-0.75f, -0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(0.0000f, -0.25f);
    glVertex2f(0.0000f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glVertex2f(0.5f, -0.25f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(3.0f);

    glBegin(GL_LINES);

    glVertex2f(-0.7f, 0.05f); glVertex2f(-0.7f, -0.45f);
    glVertex2f(-0.64f, 0.1f); glVertex2f(-0.64f, -0.40f);
    glVertex2f(-0.57f, 0.16f); glVertex2f(-0.57f, -0.30f);
    glVertex2f(-0.5f, 0.25f); glVertex2f(-0.5f, -0.25f);

    glVertex2f(0.4f, 0.25f); glVertex2f(0.4f, -0.25f);
    glVertex2f(0.3f, 0.25f); glVertex2f(0.3f, -0.25f);
    glVertex2f(0.2f, 0.25f); glVertex2f(0.2f, -0.25f);
    glVertex2f(0.1f, 0.25f); glVertex2f(0.1f, -0.25f);

    glEnd();


}


void enterScene4() {
    studentX = -0.35f;
    friendX  = -0.4f;
    
    studentY = 0.25f;
    friendY  = 0.1f;

    scene4Active = true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (scene == 1) drawScene1();
    else if (scene == 2) drawScene2();
    else if (scene == 3) drawScene3();
    else if (scene == 4) drawScene4();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {

    if (key == 'n' && scene < 4) scene++;
    if (key == 'b' && scene > 1) scene--;

    if (key == 's') {
        standUp = true;
    }
    if (key == 'p') {
        searching = false;
        standUp = false;
    }

    if (scene == 3) {
        scene3State = 0;
        scene3Timer = 0.0f;
    }

    glutPostRedisplay();
}

void update(int value) {

    idleT += 0.05f;

    if (!standUp) {
        studentY = -0.38f + 0.01f * sin(idleT);
        studentX = 0;
    }

    else {
        if (studentY < -0.1f)
            studentY += 0.01f;
        else if (!searching)
            searching = true;
    }

    if (scene == 2 && searching) {
        talkTimer += 0.016f;

        if (talkTimer > 2.0f && dialogueState == 0) {
            dialogueState = 1;
        }
        if (talkTimer > 5.0f && dialogueState == 1) {
            dialogueState = 2;
        }
    }

    if (searching && scene != 4) {
        searchT += 0.05f;
        studentX = 0.2f * sin(searchT);
    }

    if (scene == 3) {

        scene3Timer += 0.016f;

        if (scene3Timer > 1.5f) scene3State = 1;
        if (scene3Timer > 4.0f) scene3State = 2;
    }

    if (scene == 4) {

        standUp = true;
        searching = false;

        if (!scene4Active) {
            scene4Active = true;
        }

        float speed = 0.006f;

        studentX += speed;
        friendX  += speed;
    }
    if (scene != lastScene) {

        if (scene == 4) {
            enterScene4();
        }

        lastScene = scene;
    }


    minuteAngle -= 0.5f;
    hourAngle -= 0.02f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CG Project - Story");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}