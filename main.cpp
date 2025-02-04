#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>
#include <windows.h>

// Global variables for truck and boat positions
float tx = 10, bx = 10, rx = 10, sx = 10, hx = 0;
float shift = 0;
float boat1X = -60.0f;  // Boat1 starting from left
float boat2X = 500.0f;  // Boat2 starting from right
float carSpeed = 0.1f;  // Initial car speed
float truckSpeed = 0.07f;  // Initial truck speed
float boat1Speed = 0.06f;  // Initial boat speed
float boat2Speed = 0.06f;  // Initial boat2 speed

// Global variables to animate the rain's diagonal translation
// These are used in the normalized rain coordinate system.
float rainOffsetX = 0.0f;
float rainOffsetY = 0.0f;
bool isDayMode = true;

// Function declarations
void display1();
void display2();
void update(int value);
void display();
void rain();
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
void round(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);
void init(void);
void buildings1();
void buildings2();
void road();
void sun();
void sun2();
void tree();
void little_tree();
void clouds();
void clouds2();
void car();
void truck();
void drawBoat();
void boat1();
void boat2();
void idle(void);
void key(int key, int x, int y);



void update(int value)
{
    isDayMode = !isDayMode;  // Toggle mode
    glutPostRedisplay();  // Refresh display
    glutTimerFunc(5000, update, 0);  // Toggle every 5 seconds
}

// Sample rain function (using normalized coordinates)

void rain(){
    glBegin(GL_LINES);

    glVertex2f(-0.85f, 1.9f); glVertex2f(-0.8f, 1.8f);
    glVertex2f(-0.55f, 1.9f); glVertex2f(-0.5f, 1.8f);
    glVertex2f(-0.25f, 1.9f); glVertex2f(-0.2f, 1.8f);
    glVertex2f( 0.05f, 1.9f); glVertex2f( 0.1f, 1.8f);
    glVertex2f( 0.35f, 1.9f); glVertex2f( 0.4f, 1.8f);
    glVertex2f( 0.65f, 1.9f); glVertex2f( 0.7f, 1.8f);
    glVertex2f( 0.95f, 1.9f); glVertex2f( 1.0f, 1.8f);

    glVertex2f(-1.0f, 1.6f); glVertex2f(-0.95f, 1.5f);
    glVertex2f(-0.7f, 1.6f);  glVertex2f(-0.65f, 1.5f);
    glVertex2f(-0.4f, 1.6f);  glVertex2f(-0.35f, 1.5f);
    glVertex2f(-0.1f, 1.6f);  glVertex2f(-0.05f, 1.5f);
    glVertex2f( 0.2f, 1.6f);  glVertex2f( 0.25f, 1.5f);
    glVertex2f( 0.5f, 1.6f);  glVertex2f( 0.55f, 1.5f);
    glVertex2f( 0.8f, 1.6f);  glVertex2f( 0.85f, 1.5f);

    glVertex2f(-0.85f, 1.3f); glVertex2f(-0.8f, 1.2f);
    glVertex2f(-0.55f, 1.3f); glVertex2f(-0.5f, 1.2f);
    glVertex2f(-0.25f, 1.3f); glVertex2f(-0.2f, 1.2f);
    glVertex2f( 0.05f, 1.3f); glVertex2f( 0.1f, 1.2f);
    glVertex2f( 0.35f, 1.3f); glVertex2f( 0.4f, 1.2f);
    glVertex2f( 0.65f, 1.3f); glVertex2f( 0.7f, 1.2f);
    glVertex2f( 0.95f, 1.3f); glVertex2f( 1.0f, 1.2f);

    glVertex2f(-1.0f, 1.0f); glVertex2f(-0.95f, 0.9f);
    glVertex2f(-0.7f, 1.0f);  glVertex2f(-0.65f, 0.9f);
    glVertex2f(-0.4f, 1.0f);  glVertex2f(-0.35f, 0.9f);
    glVertex2f(-0.1f, 1.0f);  glVertex2f(-0.05f, 0.9f);
    glVertex2f( 0.2f, 1.0f);  glVertex2f( 0.25f, 0.9f);
    glVertex2f( 0.5f, 1.0f);  glVertex2f( 0.55f, 0.9f);
    glVertex2f( 0.8f, 1.0f);  glVertex2f( 0.85f, 0.9f);

    glVertex2f(-0.85f, 0.7f); glVertex2f(-0.8f, 0.6f);
    glVertex2f(-0.55f, 0.7f); glVertex2f(-0.5f, 0.6f);
    glVertex2f(-0.25f, 0.7f); glVertex2f(-0.2f, 0.6f);
    glVertex2f( 0.05f, 0.7f); glVertex2f( 0.1f, 0.6f);
    glVertex2f( 0.35f, 0.7f); glVertex2f( 0.4f, 0.6f);
    glVertex2f( 0.65f, 0.7f); glVertex2f( 0.7f, 0.6f);
    glVertex2f( 0.95f, 0.7f); glVertex2f( 1.0f, 0.6f);

    glVertex2f(-1.0f, 0.4f); glVertex2f(-0.95f, 0.3f);
    glVertex2f(-0.7f, 0.4f);  glVertex2f(-0.65f, 0.3f);
    glVertex2f(-0.4f, 0.4f);  glVertex2f(-0.35f, 0.3f);
    glVertex2f(-0.1f, 0.4f);  glVertex2f(-0.05f, 0.3f);
    glVertex2f( 0.2f, 0.4f);  glVertex2f( 0.25f, 0.3f);
    glVertex2f( 0.5f, 0.4f);  glVertex2f( 0.55f, 0.3f);
    glVertex2f( 0.8f, 0.4f);  glVertex2f( 0.85f, 0.3f);

    glVertex2f(-0.85f, 0.1f); glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.55f, 0.1f); glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.25f, 0.1f); glVertex2f(-0.2f, 0.0f);
    glVertex2f( 0.05f, 0.1f); glVertex2f( 0.1f, 0.0f);
    glVertex2f( 0.35f, 0.1f); glVertex2f( 0.4f, 0.0f);
    glVertex2f( 0.65f, 0.1f); glVertex2f( 0.7f, 0.0f);
    glVertex2f( 0.95f, 0.1f); glVertex2f( 1.0f, 0.0f);

    glVertex2f(-1.0f, -0.2f); glVertex2f(-0.95f, -0.3f);
    glVertex2f(-0.7f, -0.2f);  glVertex2f(-0.65f, -0.3f);
    glVertex2f(-0.4f, -0.2f);  glVertex2f(-0.35f, -0.3f);
    glVertex2f(-0.1f, -0.2f);  glVertex2f(-0.05f, -0.3f);
    glVertex2f( 0.2f, -0.2f);  glVertex2f( 0.25f, -0.3f);
    glVertex2f( 0.5f, -0.2f);  glVertex2f( 0.55f, -0.3f);
    glVertex2f( 0.8f, -0.2f);  glVertex2f( 0.85f, -0.3f);

    glVertex2f(-0.85f, -0.5f); glVertex2f(-0.8f, -0.6f);
    glVertex2f(-0.55f, -0.5f); glVertex2f(-0.5f, -0.6f);
    glVertex2f(-0.25f, -0.5f); glVertex2f(-0.2f, -0.6f);
    glVertex2f( 0.05f, -0.5f); glVertex2f( 0.1f, -0.6f);
    glVertex2f( 0.35f, -0.5f); glVertex2f( 0.4f, -0.6f);
    glVertex2f( 0.65f, -0.5f); glVertex2f( 0.7f, -0.6f);
    glVertex2f( 0.95f, -0.5f); glVertex2f( 1.0f, -0.6f);

    glVertex2f(-0.85f, -0.8f); glVertex2f(-0.95f, -0.9f);
    glVertex2f(-0.7f, -0.8f);  glVertex2f(-0.65f, -0.9f);
    glVertex2f(-0.4f, -0.8f);  glVertex2f(-0.35f, -0.9f);
    glVertex2f(-0.1f, -0.8f);  glVertex2f(-0.05f, -0.9f);
    glVertex2f( 0.2f, -0.8f);  glVertex2f( 0.25f, -0.9f);
    glVertex2f( 0.5f, -0.8f);  glVertex2f( 0.55f, -0.9f);
    glVertex2f( 0.8f, -0.8f);  glVertex2f( 0.85f, -0.9f);

    glVertex2f(-0.85f, -1.1f); glVertex2f(-0.8f, -1.2f);
    glVertex2f(-0.55f, -1.1f); glVertex2f(-0.5f, -1.2f);
    glVertex2f(-0.25f, -1.1f); glVertex2f(-0.2f, -1.2f);
    glVertex2f( 0.05f, -1.1f); glVertex2f( 0.1f, -1.2f);
    glVertex2f( 0.35f, -1.1f); glVertex2f( 0.4f, -1.2f);
    glVertex2f( 0.65f, -1.1f); glVertex2f( 0.7f, -1.2f);
    glVertex2f( 0.95f, -1.1f); glVertex2f( 1.0f, -1.2f);

    glVertex2f(-1.0f, -1.4f); glVertex2f(-0.95f, -1.5f);
    glVertex2f(-0.7f, -1.4f);  glVertex2f(-0.65f, -1.5f);
    glVertex2f(-0.4f, -1.4f);  glVertex2f(-0.35f, -1.5f);
    glVertex2f(-0.1f, -1.4f);  glVertex2f(-0.05f, -1.5f);
    glVertex2f( 0.2f, -1.4f);  glVertex2f( 0.25f, -1.5f);
    glVertex2f( 0.5f, -1.4f);  glVertex2f( 0.55f, -1.5f);
    glVertex2f( 0.8f, -1.4f);  glVertex2f( 0.85f, -1.5f);

    glEnd();
}


// Draw a filled circle
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++){
        float angle = i * 3.1416f / 180.0f;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void round(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    circle(rx, ry, cx, cy);
}

void init(void)
{
    glClearColor(0, 0.9f, 0.9f, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void buildings1()
{
    // Building 1
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(50.0f, 180.0f);
    glVertex2f(120.0f, 180.0f);
    glVertex2f(120.0f, 320.0f);
    glVertex2f(50.0f, 320.0f);
    glEnd();

    // Windows for Building 1
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float y = 190.0f; y < 300.0f; y += 30.0f) {
        for (float x = 50.0f; x < 120.0f; x += 25.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 15.0f, y);
            glVertex2f(x + 15.0f, y + 20.0f);
            glVertex2f(x, y + 20.0f);
            glEnd();
        }
    }

    // Building 2
    glColor3f(0.7f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(140.0f, 180.0f);
    glVertex2f(210.0f, 180.0f);
    glVertex2f(210.0f, 300.0f);
    glVertex2f(140.0f, 300.0f);
    glEnd();

    // Windows for Building 2
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float y = 180.0f; y < 300.0f; y += 40.0f) {
        for (float x = 150.0f; x < 200.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 3
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(230.0f, 180.0f);
    glVertex2f(300.0f, 180.0f);
    glVertex2f(300.0f, 350.0f);
    glVertex2f(230.0f, 350.0f);
    glEnd();

    // Windows for Building 3
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float y = 190.0f; y < 350.0f; y += 40.0f) {
        for (float x = 240.0f; x < 290.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 4
    glColor3f(0.7f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(320.0f, 180.0f);
    glVertex2f(400.0f, 180.0f);
    glVertex2f(400.0f, 270.0f);
    glVertex2f(320.0f, 270.0f);
    glEnd();

    // Windows for Building 4
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float y = 190.0f; y < 270.0f; y += 40.0f) {
        for (float x = 330.0f; x < 390.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 5
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(420.0f, 180.0f);
    glVertex2f(490.0f, 180.0f);
    glVertex2f(490.0f, 310.0f);
    glVertex2f(420.0f, 310.0f);
    glEnd();

    // Windows for Building 5
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float y = 190.0f; y < 310.0f; y += 40.0f) {
        for (float x = 430.0f; x < 470.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    glFlush();
}
void buildings2()
{
    // Building 1
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(50.0f, 180.0f);
    glVertex2f(120.0f, 180.0f);
    glVertex2f(120.0f, 320.0f);
    glVertex2f(50.0f, 320.0f);
    glEnd();

    // Windows for Building 1
    glColor3f(1.0f, 1.0f, 0.6f);
    for (float y = 190.0f; y < 300.0f; y += 30.0f) {
        for (float x = 50.0f; x < 120.0f; x += 25.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 15.0f, y);
            glVertex2f(x + 15.0f, y + 20.0f);
            glVertex2f(x, y + 20.0f);
            glEnd();
        }
    }

    // Building 2
    glColor3f(0.7f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(140.0f, 180.0f);
    glVertex2f(210.0f, 180.0f);
    glVertex2f(210.0f, 300.0f);
    glVertex2f(140.0f, 300.0f);
    glEnd();

    // Windows for Building 2
    glColor3f(1.0f, 1.0f, 0.6f);
    for (float y = 180.0f; y < 300.0f; y += 40.0f) {
        for (float x = 150.0f; x < 200.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 3
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(230.0f, 180.0f);
    glVertex2f(300.0f, 180.0f);
    glVertex2f(300.0f, 350.0f);
    glVertex2f(230.0f, 350.0f);
    glEnd();

    // Windows for Building 3
    glColor3f(1.0f, 1.0f, 0.6f);
    for (float y = 190.0f; y < 350.0f; y += 40.0f) {
        for (float x = 240.0f; x < 290.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 4
    glColor3f(0.7f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(320.0f, 180.0f);
    glVertex2f(400.0f, 180.0f);
    glVertex2f(400.0f, 270.0f);
    glVertex2f(320.0f, 270.0f);
    glEnd();

    // Windows for Building 4
    glColor3f(1.0f, 1.0f, 0.6f);
    for (float y = 190.0f; y < 270.0f; y += 40.0f) {
        for (float x = 330.0f; x < 390.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    // Building 5
    glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(420.0f, 180.0f);
    glVertex2f(490.0f, 180.0f);
    glVertex2f(490.0f, 310.0f);
    glVertex2f(420.0f, 310.0f);
    glEnd();

    // Windows for Building 5
    glColor3f(1.0f, 1.0f, 0.6f);
    for (float y = 190.0f; y < 310.0f; y += 40.0f) {
        for (float x = 430.0f; x < 470.0f; x += 30.0f) {
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + 20.0f, y);
            glVertex2f(x + 20.0f, y + 30.0f);
            glVertex2f(x, y + 30.0f);
            glEnd();
        }
    }

    glFlush();
}
void road()
{
    // Base of the road (area under the stripes)
    glColor3f(0.0f, 0.502f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 75.0f);
    glVertex2f(0.0f, 75.0f);
    glEnd();

    // White stripe below the road's top
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();

    // Road surface (gray part)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 50.0f);
    glVertex2f(0.0f, 50.0f);
    glEnd();

    // Road markings (dashes)
    glColor3f(1.0f, 1.0f, 1.0f);
    float startX[] = {15.0f, 65.0f, 115.0f, 165.0f, 215.0f, 265.0f, 315.0f, 365.0f, 415.0f, 465.0f};
    for (int i = 0; i < 10; i++){
        glBegin(GL_POLYGON);
        glVertex2f(startX[i], 20.0f);
        glVertex2f(startX[i] + 35.0f, 20.0f);
        glVertex2f(startX[i] + 35.0f, 30.0f);
        glVertex2f(startX[i], 30.0f);
        glEnd();
    }
}
void sun()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    circle(20.0f, 30.0f, 450.0f, 450.0f);
}

void sun2()
{
    glColor3f(0.7f, 0.7f, 0.4f);  // Cloudy sun, dimmed yellow-gray
    circle(20.0f, 30.0f, 450.0f, 450.0f);
}
void tree()
{
    // Tree trunk
    glColor3f(0.5f, 0.2f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(75.0f, 180.0f);
    glVertex2f(85.0f, 180.0f);
    glVertex2f(85.0f, 350.0f);
    glVertex2f(75.0f, 350.0f);
    glEnd();

    // Tree foliage (using circles)
    glColor3f(0.0f, 0.5f, 0.0f);
    circle(30.0f, 40.0f, 85.0f, 370.0f);
    circle(20.0f, 30.0f, 90.0f, 340.0f);
    circle(20.0f, 30.0f, 65.0f, 395.0f);

    glColor3f(0.0f, 0.3f, 0.0f);
    circle(40.0f, 50.0f, 45.0f, 360.0f);
    glColor3f(0.0f, 0.392f, 0.0f);
    circle(30.0f, 30.0f, 60.0f, 330.0f);
    circle(20.0f, 30.0f, 30.0f, 300.0f);
    circle(20.0f, 30.0f, 60.0f, 300.0f);

    glColor3f(0.5f, 0.2f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(40.0f, 180.0f);
    glVertex2f(50.0f, 180.0f);
    glVertex2f(50.0f, 296.0f);
    glVertex2f(60.0f, 320.0f);
    glVertex2f(55.0f, 326.0f);
    glVertex2f(50.0f, 300.0f);
    glVertex2f(50.0f, 350.0f);
    glVertex2f(45.0f, 350.0f);
    glVertex2f(45.0f, 310.0f);
    glEnd();
}
void little_tree()
{
    // 2nd tree
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(65.0f, 60.0f);
    glVertex2f(75.0f, 60.0f);
    glVertex2f(75.0f, 100.0f);
    glVertex2f(65.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 65.0f, 110.0f);
    circle(15.0f, 20.0f, 75.0f, 110.0f);
    circle(15.0f, 20.0f, 70.0f, 130.0f);

    // 1st tree
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 60.0f);
    glVertex2f(10.0f, 60.0f);
    glVertex2f(10.0f, 100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 0.0f, 110.0f);
    circle(15.0f, 20.0f, 10.0f, 110.0f);
    circle(15.0f, 20.0f, 5.0f, 130.0f);

    // 3rd tree
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(125.0f, 60.0f);
    glVertex2f(135.0f, 60.0f);
    glVertex2f(135.0f, 100.0f);
    glVertex2f(125.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 125.0f, 110.0f);
    circle(15.0f, 20.0f, 135.0f, 110.0f);
    circle(15.0f, 20.0f, 130.0f, 130.0f);

    // 4th tree
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(190.0f, 60.0f);
    glVertex2f(200.0f, 60.0f);
    glVertex2f(200.0f, 100.0f);
    glVertex2f(190.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 190.0f, 110.0f);
    circle(15.0f, 20.0f, 200.0f, 110.0f);
    circle(15.0f, 20.0f, 195.0f, 130.0f);

    // Tree 5
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(300.0f, 60.0f);
    glVertex2f(310.0f, 60.0f);
    glVertex2f(310.0f, 100.0f);
    glVertex2f(300.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 300.0f, 110.0f);
    circle(15.0f, 20.0f, 310.0f, 110.0f);
    circle(15.0f, 20.0f, 305.0f, 130.0f);

    // Tree 6
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(365.0f, 60.0f);
    glVertex2f(375.0f, 60.0f);
    glVertex2f(375.0f, 100.0f);
    glVertex2f(365.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 365.0f, 110.0f);
    circle(15.0f, 20.0f, 375.0f, 110.0f);
    circle(15.0f, 20.0f, 370.0f, 130.0f);

    // Tree 7
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(425.0f, 60.0f);
    glVertex2f(435.0f, 60.0f);
    glVertex2f(435.0f, 100.0f);
    glVertex2f(425.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 425.0f, 110.0f);
    circle(15.0f, 20.0f, 435.0f, 110.0f);
    circle(15.0f, 20.0f, 430.0f, 130.0f);

    // Tree 8
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(490.0f, 60.0f);
    glVertex2f(500.0f, 60.0f);
    glVertex2f(500.0f, 100.0f);
    glVertex2f(490.0f, 100.0f);
    glEnd();

    glColor3ub(0, 100, 0);
    circle(15.0f, 20.0f, 490.0f, 110.0f);
    circle(15.0f, 20.0f, 500.0f, 110.0f);
    circle(15.0f, 20.0f, 495.0f, 130.0f);
}
void clouds()
{
    glPushMatrix();
    glTranslatef(shift, 0.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    // Cloud 1
    round(20.0f, 30.0f, 90.0f, 460.0f);
    round(15.0f, 20.0f, 110.0f, 460.0f);
    round(15.0f, 20.0f, 70.0f, 460.0f);

    // Cloud 2
    round(20.0f, 30.0f, 185.0f, 430.0f);
    round(15.0f, 20.0f, 205.0f, 430.0f);
    round(15.0f, 20.0f, 165.0f, 430.0f);

    glPopMatrix();

    shift -= 0.02f;
    if (shift < -0.0f)
        shift = 400.0f;

    glutPostRedisplay();
}
void clouds2()
{
    glPushMatrix();
    glTranslatef(shift, 0.0f, 0.0f);

    glColor3f(0.3f, 0.3f, 0.3f);
    // Cloud 1
    round(20.0f, 30.0f, 90.0f, 460.0f);
    round(15.0f, 20.0f, 110.0f, 460.0f);
    round(15.0f, 20.0f, 70.0f, 460.0f);

    // Cloud 2
    round(20.0f, 30.0f, 185.0f, 430.0f);
    round(15.0f, 20.0f, 205.0f, 430.0f);
    round(15.0f, 20.0f, 165.0f, 430.0f);

    glPopMatrix();

    shift -= 0.01f;
    if (shift < -0.0f)
        shift = 400.0f;

    glutPostRedisplay();
}

void car() {
    glPushMatrix();
    glTranslatef(tx, 0.0f, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(410.0f, 40.0f);
    glVertex2f(490.0f, 40.0f);
    glVertex2f(485.0f, 70.0f);
    glVertex2f(410.0f, 70.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(420.0f, 70.0f);
    glVertex2f(475.0f, 70.0f);
    glVertex2f(465.0f, 100.0f);
    glVertex2f(430.0f, 100.0f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(425.0f, 70.0f);
    glVertex2f(445.0f, 70.0f);
    glVertex2f(445.0f, 90.0f);
    glVertex2f(430.0f, 90.0f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(450.0f, 70.0f);
    glVertex2f(470.0f, 70.0f);
    glVertex2f(465.0f, 90.0f);
    glVertex2f(450.0f, 90.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    circle(10.0f, 14.0f, 435.0f, 40.0f);
    circle(10.0f, 14.0f, 465.0f, 40.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    circle(6.0f, 10.0f, 435.0f, 40.0f);
    circle(6.0f, 10.0f, 465.0f, 40.0f);

    glPopMatrix();

    tx += carSpeed;  // Move the car using the updated speed
    if (tx > 100.0f)
        tx = -610.0f;

    glutPostRedisplay();
}

void truck() {
    glPushMatrix();
    glTranslatef(bx, 0, 0);
    glColor3f(0.4f, 1.0f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2d(450, 40);
    glVertex2d(505, 40);
    glVertex2d(505, 110);
    glVertex2d(450, 110);
    glEnd();

    glColor3f(0.8f, 0.07f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2d(505, 40);
    glVertex2d(535, 40);
    glVertex2d(535, 70);
    glVertex2d(505, 70);
    glEnd();

    glColor3f(0.8f, 0.07f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2d(505, 70);
    glVertex2d(525, 70);
    glVertex2d(515, 90);
    glVertex2d(505, 90);
    glEnd();

    // Truck window
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2d(505, 70);
    glVertex2d(520, 70);
    glVertex2d(515, 85);
    glVertex2d(505, 85);
    glEnd();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    circle(10, 14, 460, 40);
    circle(10, 14, 510, 40);

    glColor3f(0.9f, 0.9f, 0.9f);
    circle(6, 10, 460, 40);
    circle(6, 10, 510, 40);

    glPopMatrix();

    bx += truckSpeed;   // Move the truck using the updated speed
    if (bx > 60)
        bx = -610;
    glutPostRedisplay();
}

void drawBoat()
{
    // Boat base (hull)
    glColor3f(0.545f, 0.271f, 0.075f);  // Brownish color
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(60.0f, 0.0f);
    glVertex2f(55.0f, 15.0f);
    glVertex2f(5.0f, 15.0f);
    glEnd();

    // Boat top
    glColor3f(0.627f, 0.322f, 0.176f);
    glBegin(GL_POLYGON);
    glVertex2f(5.0f, 15.0f);
    glVertex2f(55.0f, 15.0f);
    glVertex2f(30.0f, 25.0f);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f, 15.0f);
    glVertex2f(30.0f, 50.0f);
    glVertex2f(45.0f, 15.0f);
    glEnd();
}

void boat1()
{
    glPushMatrix();
    glTranslatef(boat1X, 100.0f, 0.0f);
    drawBoat();
    glPopMatrix();

    boat1X += boat1Speed;  // Move boat using new speed
    if (boat1X > 810.0f)
        boat1X = -60.0f;
}

void boat2()
{
    glPushMatrix();
    glTranslatef(boat2X, 150.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    drawBoat();
    glPopMatrix();

    boat2X -= boat2Speed;  // Move boat using updated speed
    if (boat2X < -60.0f)
        boat2X = 810.0f;
}

void display()
{
    if (isDayMode) {
        display1();
    } else {
        display2();
    }
}
void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // day Sky background
    glColor3f(0.1f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 500.0f);
    glVertex2f(0.0f, 500.0f);
    glEnd();

    // Draw river
    glColor3f(0.0f, 0.3f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 75.0f);
    glVertex2f(500.0f, 75.0f);
    glVertex2f(500.0f, 170.0f);
    glVertex2f(0.0f, 170.0f);
    glEnd();

    // Grass bank
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 170.0f);
    glVertex2f(50.0f, 175.0f);
    glVertex2f(100.0f, 170.0f);
    glVertex2f(150.0f, 175.0f);
    glVertex2f(200.0f, 170.0f);
    glVertex2f(250.0f, 175.0f);
    glVertex2f(300.0f, 170.0f);
    glVertex2f(350.0f, 175.0f);
    glVertex2f(400.0f, 170.0f);
    glVertex2f(450.0f, 175.0f);
    glVertex2f(500.0f, 170.0f);
    glVertex2f(500.0f, 180.0f);
    glVertex2f(0.0f, 180.0f);
    glEnd();

    buildings1();
    road();
    sun();
    clouds();
    tree();
    boat1();
    boat2();
    little_tree();
    car();
    truck();

    glFlush();
    glutSwapBuffers();
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Rainy sky background
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(500.0f, 0.0f);
    glVertex2f(500.0f, 500.0f);
    glVertex2f(0.0f, 500.0f);
    glEnd();

    // River
    glColor3f(0.0f, 0.1f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 75.0f);
    glVertex2f(500.0f, 75.0f);
    glVertex2f(500.0f, 170.0f);
    glVertex2f(0.0f, 170.0f);
    glEnd();

    // Grass bank
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 170.0f);
    glVertex2f(50.0f, 175.0f);
    glVertex2f(100.0f, 170.0f);
    glVertex2f(150.0f, 175.0f);
    glVertex2f(200.0f, 170.0f);
    glVertex2f(250.0f, 175.0f);
    glVertex2f(300.0f, 170.0f);
    glVertex2f(350.0f, 175.0f);
    glVertex2f(400.0f, 170.0f);
    glVertex2f(450.0f, 175.0f);
    glVertex2f(500.0f, 170.0f);
    glVertex2f(500.0f, 180.0f);
    glVertex2f(0.0f, 180.0f);
    glEnd();

    buildings2();
    road();
    sun2();
    clouds2();
    tree();
    boat1();
    boat2();
    little_tree();
    car();
    truck();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(rainOffsetX, rainOffsetY, 0.0f);
    rain();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glFlush();
    glutSwapBuffers();
}
void idle(void)
{

   rainOffsetX += 0.0025f;
    rainOffsetY -= 0.008f;

    if (rainOffsetY < -1.0f) {
        rainOffsetX = 0.0f;
        rainOffsetY = 0.0f;
    }

    tx += 0.1;
    if (tx > 500) tx = -100; // Reset car position

    bx += 0.07f;
    if (bx > 500) bx = -100; // Reset truck position

    boat1X += 0.06f;
    if (boat1X > 500) boat1X = -60;

    boat2X -= 0.06f;
    if (boat2X < -60) boat2X = 500;

    shift -= 0.02f;
    if (shift < -10) shift = 500;


    glutPostRedisplay();
}

void key(int key, int x, int y)
{
    if (isDayMode) {  // If in day mode (display1 )
    switch (key) {
    case GLUT_KEY_LEFT:
         carSpeed += 0.07f;  // Increase car speed
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        truckSpeed += 0.03f;  // Increase truck speed
        break;
    case GLUT_KEY_UP:
        if (carSpeed > 0.09f)
            carSpeed -= 0.09f;  // Decrease car speed
        break;
    case GLUT_KEY_DOWN:
        if (truckSpeed > 0.05f)
            truckSpeed -= 0.05f;  // Decrease truck speed
        break;
    default:
        break;
    }
}

if (!isDayMode) {  // Only in rainy mode (display2)
        switch (key) {
        case GLUT_KEY_LEFT:
            boat1Speed += 0.03f;  // Increase boat1 speed
            break;
        case GLUT_KEY_UP:
            if (boat1Speed > 0.03f)
                boat1Speed -= 0.03f;  // Decrease boat1 speed
            break;
        case GLUT_KEY_RIGHT:
            boat2Speed += 0.03f;  // Increase boat2 speed
            break;
        case GLUT_KEY_DOWN:
            if (boat2Speed > 0.03f)
                boat2Speed -= 0.03f;  // Decrease boat2 speed
            break;
        default:
            break;
        }
    }
}

void keyboard(unsigned char key, int x, int y)  // New keyboard function
{
    switch (key) {
    case 'r':  // If 'r' or 'R' is pressed
    case 'R':
        isDayMode = false; // Switch to rainy mode
        glutPostRedisplay();
        break;
    case 'd': // If 'd' or 'D' is pressed
    case 'D':
        isDayMode = true; // Switch to day mode
        glutPostRedisplay();
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (isDayMode) {  // If day mode (display1)
            carSpeed = 0.0f;    // back initial speed car
            truckSpeed = 0.0f;  // back initial speed truck
        } else {  // If rainy mode (display2)
            boat1Speed = 0.0f;  // back initial speed boat1
            boat2Speed = 0.0f;  // back initial speed boat2
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("City View Project with Rainy Day");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutSpecialFunc(key);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
