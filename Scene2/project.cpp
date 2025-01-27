#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

# define pi 3.1416

// Initial values of variables
bool day = true;
bool rain = false;
bool lantern = false;
char key;
struct Raindrop
{
    float x, y;
    float size;  // Size of the raindrop
    float speed; // Falling speed
};

vector<Raindrop> raindrops;
int maxRaindrops = 3000; // Maximum number of raindrops


// Methods

//keyboard-mouse
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

//shapes
void drawLines(float x1, float y1, float x2, float y2);
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void drawPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void drawCircle(float x1, float y1, float radius);

//sky elements
void drawSky(); //O21
void drawCloud(); 
void drawSunMoon(); //O23
void drawStar();
void drawFireflies();
void drawLightningFlash();

//field elements
void drawField(); //O22
void drawHut1(); //O25
void drawHut2(); //O26
void drawHut3(); //O27
void drawHut4(); //O28
void drawHut5(); //O29
void drawHut6(); //O30
void drawRiver();
void drawBoat();
void drawMountains();
void drawTrees();
void drawWindMill();

//weather elements
void drawRain(); //O24

//animations
void updateCloud(int value);
void updateRainCloud(int value);
void updateRain(int value);
void initializeRain();
void updateFireflies(int value);
void updateLightningFlash(int value);
void updateBoat(int value);
void updateWindMill(int value);

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        lantern = !lantern;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd' || key == 'D')
        day = true;

    else if (key == 'n' || key == 'N')
        day = false;

    else if (key == 'r' || key == 'R')
        rain = !rain;

    glutPostRedisplay();
}

void drawLines(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glVertex2f(x5, y5);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        float theta = 2.0f * pi * float(i) / float(100);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSky() // O21
{
    if (day)
        glColor3f(0.25, 0.95, 1.01);
    else
        glColor3ub(0, 0, 0);
    drawRectangle(-200.0, 28.75, 200.0, 27.67, 200.0, 200.0, -200.0, 200.0);
}

void drawField() //O22
{
    if (day)
        glColor3ub(38, 109, 5);
    else
        glColor3ub(33, 63, 26);
    drawRectangle(-200.0, -200.0, 200.0, -200.0, 200.0, 28.75, -200.0, 28.75);
}

void drawSunMoon() //O23
{
    if (day)
        glColor3f(0.97, 0.91, 0.39);
    else
        glColor3f(1.0, 1.0, 1.0);
    drawCircle(-11.25, 144.58, 18.0);
}

void drawRain() //O24
{
    if (rain)
    {
        for (int i = 0; i < raindrops.size(); i++)
        {
            glColor3ub(8, 119, 231); 
            // Adjusted length of raindrops for better visibility
            drawLines(raindrops[i].x, raindrops[i].y, raindrops[i].x, raindrops[i].y - 6.0);
        }
    }
}

void updateRain(int value)
{
    if (rain)
    {
        // Update position of each raindrop
        for (int i = 0; i < raindrops.size(); i++)
        {
            raindrops[i].y -= raindrops[i].speed; // Use initialized speed
            if (raindrops[i].y < -200) // Reset if below screen
            {
                raindrops[i].x = rand() % 400 - 200; // Random x position
                raindrops[i].y = 200; // Reset to top
            }
        }

        // Ensure we maintain the max raindrop count
        while (raindrops.size() < maxRaindrops)
        {
            Raindrop raindrop;
            raindrop.x = rand() % 400 - 200;
            raindrop.y = rand() % 400 - 200;
            raindrops.push_back(raindrop);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, updateRain, 0); // Faster update for smoother animation
}

void initializeRain()
{
    raindrops.clear(); // Clear existing raindrops
    for (int i = 0; i < maxRaindrops; i++) {
        Raindrop raindrop;
        raindrop.x = rand() % 400 - 200;       // Random x position
        raindrop.y = rand() % 400 - 200;       // Random y position
        raindrop.size = (rand() % 3 + 1) / 2.0; // Random size (0.5 to 2.0)
        raindrop.speed = raindrop.size * 5.0; // Speed proportional to size
        raindrops.push_back(raindrop);
    }
}

void drawHut1() //O25
{
    glColor3ub(255, 197, 62);
    drawRectangle(-183.89, 30.84, -144.28, 29.72, -116.35, 3.58, -157.64, 2.78);
    drawRectangle(-183.89, 30.84, -200.0, 16.26, -200.0, 12.18, -179.22, 26.95);

    glColor3ub(247, 141, 67);
    drawRectangle(-159.26, 4.51, -159.93, -15.72, -123.37, -12.16, -124.24, 3.42);
    drawTriangle(-179.22, 26.95, -200.0, 12.18, -159.26, 4.51);
    drawRectangle(-200.0, 12.18, -200.0, -10.0, -158.93, -15.72, -159.26, 4.51);

    //window
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    
    drawRectangle(-186.89, 8.39, -186.83, -0.56, -175.92, -1.47, -175.64, 7.49);

    //door
    drawRectangle(-147.43, 0.79, -147.01, -14.53, -137.39, -13.57, -138.33, 0.61);

    glColor3ub(175, 65, 56);
    drawRectangle(-200.0, -10.0, -200.0, -15.0, -159.12, -20.5, -158.93, -15.72);
    drawRectangle(-159.27, -17.55, -159.12, -20.5, -118.92, -16.6, -119.21, -13.74);
    glColor3ub(251, 165, 62);
    drawPolygon(-158.93, -15.72, -159.27, -17.55, -119.21, -13.74, -119.3, -12.92, -123.37, -12.16);
}

void drawHut2() //026
{
    glColor3ub(255, 197, 62);
    drawRectangle(-69.72, 29.65, -93.58, 6.17, -59.01, 5.31, -36.81, 30.16);
    drawRectangle(-36.81, 30.16, -39.34, 27.0, -20.98, 6.66, -15.62, 7.12);

    glColor3ub(247, 141, 67);
    drawRectangle(-86.0, 5.98, -85.65, -7.75, -59.46, -12.7, -59.29, 5.37);
    drawRectangle(-59.29, 5.37, -59.46, -12.7, -20.92, -7.47, -21.71, 7.47);
    drawTriangle(-59.29, 5.37, -21.71, 7.47, -39.56, 27.36);

    //window
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(-45.73, 7.37, -45.57, 0.34, -35.93, 0.72, -36.01, 7.58);

    //door
    drawRectangle(-76.71, 2.8, -77.08, -9.47, -69.41, -10.7, -69.29, 2.59);

    glColor3ub(175, 65, 56);
    drawRectangle(-88.77, -7.18, -88.96, -10.82, -58.95, -16.83, -59.46, -12.7);
    drawRectangle(-59.46, -12.7, -58.95, -16.83, -19.68, -10.85, -20.21, -7.48);
}

void drawHut3() //O27
{
    glColor3ub(255, 197, 62);
    drawRectangle(-2.02, 34.97, -11.22, 27.15, 3.66, 26.88, 12.98, 35.52);
    drawRectangle(12.98, 35.52, 10.77, 33.47, 18.15, 26.92, 21.98, 27.15);

    glColor3ub(247, 141, 67);
    drawRectangle(-6.69, 27.12, -6.72, 21.67, 3.88, 21.14, 3.66, 26.88);
    drawRectangle(3.66, 26.88, 3.88, 21.14, 17.48, 22.26, 17.17, 27.79);
    drawTriangle(3.66, 26.88, 17.17, 27.79, 10.77, 33.47);

    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(8.8, 27.05, 9.02, 21.53, 12.69, 21.97, 12.43, 27.14);
}

void drawHut4() //028
{
    glColor3ub(255, 197, 62);
    drawRectangle(55.26, 39.82, 46.65, 32.74, 73.32, 32.01, 65.99, 39.5);

    glColor3ub(247, 141, 67);
    drawRectangle(51.57, 32.6, 51.5, 28.09, 67.49, 28.09, 67.45, 32.17);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(58.05, 32.42, 58.05, 28.09, 60.76, 28.09, 60.66, 32.35);
}

void drawHut5() //029
{
    glColor3ub(247, 141, 67);
    drawRectangle(95.43, 8.77, 95.0, -5.68, 127.94, -7.6, 127.68, 10.42);
    drawTriangle(127.68, 10.42, 160.04, 12.05, 143.82, 24.68);
    drawRectangle(127.68, 10.42, 127.94, -7.6, 159.52, -2.83, 160.04, 12.05);

    glColor3ub(255, 197, 62);
    drawRectangle(111.45, 28.1, 90.47, 8.81, 125.51, 8.49, 147.68, 28.1);
    drawRectangle(143.82, 24.68, 160.04, 12.05, 167.8, 11.78, 147.68, 28.1);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(107.05, 4.73, 106.4, -6.35, 115.19, -6.86, 115.12, 4.23);
    //window
    drawRectangle(137.61, 10.13, 137.73, 3.54, 142.63, 3.63, 142.52, 10.11);
    drawRectangle(148.09, 10.68, 148.26, 4.11, 153.24, 4.1, 153.04, 10.67);
}

void drawHut6() //O30
{
    glColor3ub(247, 141, 67);
    drawRectangle(176.57, 24.16, 176.54, 19.61, 190.61, 19.65, 190.81, 24.25);
    drawTriangle(172.1, 30.52, 165.59, 25.89, 176.57, 24.16);
    drawRectangle(165.59, 25.89, 165.55, 20.24, 176.54, 19.61, 176.57, 24.16);

    glColor3ub(255, 197, 62);
    drawRectangle(170.58, 32.66, 176.57, 24.16, 192.02, 24.26, 184.0, 32.0);
    drawRectangle(170.58, 32.66, 172.1, 30.52, 164.93, 25.42, 162.86, 25.61);

    //door
    if (!lantern)
        glColor3ub(76, 5, 61);
    else
        glColor3f(0.97, 0.91, 0.39);
    drawRectangle(180.53, 23.84, 180.53, 19.62, 183.16, 19.63, 183.01, 23.82);
}

void scenery()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    // drawCloud();
    drawSunMoon();
    // drawStar();
    // drawFireflies();
    // drawLightningFlash();
    drawField();
    if (rain) drawRain();
    drawHut1(); //O25
    drawHut2(); //O26
    drawHut3(); //O27
    drawHut4(); //O28
    drawHut5(); //O29
    drawHut6(); //O30
    // drawPonds();
    // drawRiver();
    // drawBoat();
    // drawMountains();
    // drawTrees();
    // drawWindMill();
    // drawRain();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Season 2: Rainy Season in Rural Area");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
    initializeRain();
    glutDisplayFunc(scenery);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    // glutTimerFunc(80, updateCloud, 0);
    // glutTimerFunc(100, updateRainCloud, 0);
    glutTimerFunc(100, updateRain, 0);
    // glutTimerFunc(100, updateFireflies, 0);
    // glutTimerFunc(100, updateLightningFlash, 0);
    // glutTimerFunc(70, updateBoat, 0);
    // glutTimerFunc(50, updateWindMill, 0);
    glutMainLoop();
    return 0;
}



