#include <cmath>
#include <ctime>
#include <iostream>

#include <GL/glut.h>

#define PI 3.141592653

using namespace std;

int width = 512, height = 512;
int style = 0;
float robot_position[3] = {0.0, 0.0, 0.0};

/*---------------eye---------------*/
float eye_position[3] = {10.0, 3.0, 10.0};
float Focus_position[3] = {0.0, 0.0, 0.0};
float Vup_vector[3] = {0.0, 1.0, 0.0};

float u[3] = {1.0, 0.0, 0.0};
float v[3] = {0.0, 1.0, 0.0};
float w[3] = {0.0, 0.0, 1.0}; //-w
float cv, sv;                 // cos(5.0), sin(5.0)轉5度
float view_degree = 5.0;

/*---------------size---------------*/
float body_length = 4;
float fore_arm_length = 2;
float upper_arm_length = 2.5;
float thigh_length = 2;
float calf_length = 2;
// X方向寬度皆設為1 Z為1.5

float head_radius = 0.9;
float elbow_radius = 0.35;
float butt_radius = 0.35;
float knee_radius = 0.3;

/*---------------material properties---------------*/
GLfloat pearl_ambient[] = {0.250000f, 0.207250f, 0.207250f, 1.0f};
GLfloat pearl_diffuse[] = {1.000000f, 0.829000f, 0.829000f, 1.0f};
GLfloat pearl_specular[] = {0.296648f, 0.296648f, 0.296648f, 1.0f};
GLfloat pearl_shininess = 11.264f;

GLfloat silver_ambient[] = {0.231250f, 0.231250f, 0.231250f, 1.0f};
GLfloat silver_diffuse[] = {0.277500f, 0.277500f, 0.277500f, 1.0f};
GLfloat silver_specular[] = {0.773911f, 0.773911f, 0.773911f, 1.0f};
GLfloat silver_shininess = 89.6f;

GLfloat copper_ambient[] = {0.191250f, 0.073500f, 0.022500f, 1.0f};
GLfloat copper_diffuse[] = {0.703800f, 0.270480f, 0.082800f, 1.0f};
GLfloat copper_specular[] = {0.256777f, 0.137622f, 0.086014f, 1.0f};
GLfloat copper_shininess = 12.8f;

GLfloat gold_ambient[] = {0.24725f, 0.19950f, 0.07450f, 1.0f};
GLfloat gold_diffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
GLfloat gold_specular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
GLfloat gold_shininess = 51.2f;

GLfloat bronze_ambient[] = {0.21250f, 0.12750f, 0.05400f, 1.0f};
GLfloat bronze_diffuse[] = {0.71400f, 0.42840f, 0.18144f, 1.0f};
GLfloat bronze_specular[] = {0.393548f, 0.271906f, 0.166721f, 1.0f};
GLfloat bronze_shininess = 25.6f;

GLfloat ruby_ambient[] = {0.17450f, 0.01175f, 0.01175f, 0.55f};
GLfloat ruby_diffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f};
GLfloat ruby_specular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f};
GLfloat ruby_shininess = 76.8f;

GLfloat G_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat G_plastic_diffuse[] = {0.1f, 0.35f, 0.1f, 1.0f};
GLfloat G_plastic_specular[] = {0.45f, 0.55f, 0.45f, 1.0f};
GLfloat G_plastic_shininess = 32.0f;

GLfloat R_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat R_plastic_diffuse[] = {0.5f, 0.0f, 0.0f, 1.0f};
GLfloat R_plastic_specular[] = {0.7f, 0.6f, 0.6f, 1.0f};
GLfloat R_plastic_shininess = 32.0f;

GLfloat xfloor_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat xfloor_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat xfloor_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat yfloor_diffuse[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat yfloor_ambient[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat yfloor_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};

/*---------light source properties -------*/
float light_position[] = {10.0, 14.0, 10.0, 1.0};
float light_direction[] = {-1.0, -1.0, -1.0, 0.0};
float light_diffuse[] = {0.8, 0.4, 0.4, 1.0};
float light_specular[] = {0.7, 0.7, 0.7, 1.0};
float light_cutoff = 60.0;
float light_exponent = 8.0;

/*
float light1_position[] = {-0.5, 1.0, -2.0, 1.0};
float light1_diffuse[] = {0.7, 0.7, 0.0, 1.0};

float global_ambient[] = {0.2, 0.2, 0.2, 1.0};
*/

/*---------------motion---------------*/
float walk_upper_arm_degree = 40;
float walk_fore_arm_degree = 15;
float walk_thigh_degree = 30;
float walk_calf_degree = 20;
float total_degree = 0;

bool walking;
bool isWaving;
bool isJumping;
bool isRunning;
int move_X = 0;
int move_Z = 0;
int move_X_direction = 0;
int move_Z_direction = 0;

/*---------------idle---------------*/
float fraction;
int frame_per_idle = 100;
int frame_count;

/*---------------cube---------------*/
float points[8][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {1, 0, 1},
    {0, 0, 1},
    {0, 1, 0},
    {1, 1, 0},
    {1, 1, 1},
    {0, 1, 1},
};
int face[6][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {0, 3, 7, 4},
    {1, 2, 6, 5},
    {0, 1, 5, 4},
    {3, 2, 6, 7},
}; // 6 faces,each consist of 4 index of points
float normals[6][3] = {
    {0.0, -1.0, 0.0}, 
    {0.0, 1.0, 0.0}, 
    {-1.0, 0.0, 0.0}, 
    {1.0, 0.0, 0.0}, 
    {0.0, 0.0, -1.0}, 
    {0.0, 0.0, 1.0}
};
GLUquadricObj *sphere = NULL, *cylind = NULL, *disk;

void init();
void keyboard(unsigned char, int, int);
void idle();
void reshape(int, int);
void display();

void make_view(int);
void make_projection(int);
void draw_eye_coordinate();

void draw_cube();
void draw_floor();
void draw_axes();
void draw_head();
void draw_body();
void draw_upper_arm();
void draw_fore_arm();
void draw_thigh();
void draw_calf();
void draw_sence();

void walk_limbs_motion(float, float);
void walk_small_limbs_motion(float, float);
// state_1 state_2 state_3 state_4

void draw_cube()
{
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++)
            glVertex3fv(points[face[i][j]]);
        glEnd();
    }
}

void walk_limbs_motion(float limbs_length, float limbs_degree)
{
    if (walking)
    {
        glTranslatef(0, limbs_length, 0);
        if (fraction <= 0.25)
            glRotatef(limbs_degree * fraction * 4, 1, 0, 0);
        else if (fraction > 0.25 && fraction <= 0.5)
            glRotatef(limbs_degree * (0.5 - fraction) * 4, 1, 0, 0);
        else if (fraction > 0.5 && fraction <= 0.75)
            glRotatef(-limbs_degree * (fraction - 0.5) * 4, 1, 0, 0);
        else
            glRotatef(-limbs_degree * (1 - fraction) * 4, 1, 0, 0);
        glTranslatef(0, -limbs_length, 0);
    }
}

void walk_small_limbs_motion(float limbs_length, float limbs_degree)
{
    if (walking)
    {
        glTranslatef(0, limbs_length, 0);
        if (fraction <= 0.25)
            glRotatef(limbs_degree * fraction * 4, 1, 0, 0);
        else if (fraction > 0.25 && fraction <= 0.5)
            glRotatef(limbs_degree * (0.5 - fraction) * 4, 1, 0, 0);
        else if (fraction > 0.5 && fraction <= 0.75)
            glRotatef(limbs_degree * (fraction - 0.5) * 4, 1, 0, 0);
        else
            glRotatef(limbs_degree * (1 - fraction) * 4, 1, 0, 0);
        glTranslatef(0, -limbs_length, 0);
    }
}

void draw_head()
{
    glPushMatrix();
    glTranslatef(0.5, head_radius + body_length + thigh_length + calf_length, 0.8);
    glColor3f(0.0, 1.0, 1.0);
    glutSolidSphere(head_radius, 200, 200);
    glPopMatrix();
}

void draw_body()
{
    glPushMatrix();
    glTranslatef(0, thigh_length + calf_length, 0);
    glScalef(1.0, body_length, 1.5);
    glColor3f(1.0, 0.0, 0.0); // red
    draw_cube();
    glPopMatrix();
}

void draw_upper_arm()
{
    glPushMatrix();
    glTranslatef(1, body_length + thigh_length + calf_length - upper_arm_length, 0.4);

    walk_limbs_motion(upper_arm_length, walk_upper_arm_degree);
    // 先往後擺 再往前擺
    // elbow
    glTranslatef(0.25, 0, 0.35);
    glColor3f(0.5, 0.0, 0.0);
    glutSolidSphere(elbow_radius, 200, 200);
    glTranslatef(-0.25, 0, -0.35);
    // arm
    glScalef(0.5, upper_arm_length, 0.7);
    glColor3f(0.5, 0.0, 0.0); // brown
    draw_cube();
    glPopMatrix();

    // another arm-----------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-0.5, body_length + thigh_length + calf_length - upper_arm_length, 0.4);

    walk_limbs_motion(upper_arm_length, -walk_upper_arm_degree);
    // 先往前擺 在往後擺
    // elbow
    glTranslatef(0.25, 0, 0.35);
    glColor3f(0.5, 0.0, 0.0);
    glutSolidSphere(elbow_radius, 200, 200);
    glTranslatef(-0.25, 0, -0.35);
    // arm
    glScalef(0.5, upper_arm_length, 0.7);
    glColor3f(0.5, 0.0, 0.0);
    draw_cube();
    glPopMatrix();
}

void draw_fore_arm()
{
    glPushMatrix();
    glTranslatef(1 + 0.1, body_length + thigh_length + calf_length - upper_arm_length - fore_arm_length, 0.4 + 0.1);

    walk_limbs_motion(fore_arm_length + upper_arm_length, walk_upper_arm_degree);
    // 跟著上臂先往後擺 再往前擺
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree);
    // 前臂單獨 永遠向前

    glScalef(0.3, fore_arm_length, 0.5);
    glColor3f(0.0, 0.5, 0.0); // dark green
    draw_cube();
    glPopMatrix();
    //-------------------------------------------------------------------
    glPushMatrix();
    glTranslatef(-0.3 - 0.1, body_length + thigh_length + calf_length - upper_arm_length - fore_arm_length, 0.4 + 0.1);

    walk_limbs_motion(fore_arm_length + upper_arm_length, -walk_upper_arm_degree);
    // 跟著上臂先往前擺 再往後擺
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree);
    // 前臂單獨 永遠向前
    glScalef(0.3, fore_arm_length, 0.5);
    glColor3f(0.0, 0.5, 0.0); // dark green
    draw_cube();
    glPopMatrix();
}

void draw_thigh()
{
    glPushMatrix();
    glTranslatef(0, calf_length, 0.5);

    // butt
    glTranslatef(0.2, thigh_length + 0.1, 0.3);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(butt_radius, 200, 200);
    glTranslatef(-0.2, -thigh_length - 0.1, -0.3);

    // thigh
    walk_limbs_motion(thigh_length, walk_thigh_degree);

    glScalef(0.4, thigh_length, 0.6);
    glColor3f(0.5, 0.5, 0.0); // green yellow
    draw_cube();
    glPopMatrix();

    // another thigh----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.6, calf_length, 0.5);

    // butt
    glTranslatef(0.2, thigh_length, 0.3);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(butt_radius, 200, 200);
    glTranslatef(-0.2, -thigh_length, -0.3);

    // thigh
    walk_limbs_motion(thigh_length, -walk_thigh_degree);

    glScalef(0.4, thigh_length, 0.6);
    glColor3f(0.5, 0.5, 0.0);
    draw_cube();
    glPopMatrix();
}

void draw_calf()
{
    glPushMatrix();
    glTranslatef(0.1, 0, 0.5);
    walk_limbs_motion(thigh_length + calf_length, walk_thigh_degree);
    walk_small_limbs_motion(calf_length, walk_calf_degree);

    // knee
    glTranslatef(0.15, calf_length, 0.25);
    glColor3f(0.5, 0.5, 0.0);
    glutSolidSphere(knee_radius, 200, 200);
    glTranslatef(-0.15, -calf_length, -0.25);

    // calf
    glScalef(0.3, calf_length, 0.5);
    glColor3f(0.0, 0.0, 1.0); // blue
    draw_cube();
    glPopMatrix();

    // another calf-----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.6, 0, 0.5);
    walk_limbs_motion(thigh_length + calf_length, -walk_thigh_degree);
    walk_small_limbs_motion(calf_length, walk_calf_degree);

    // knee
    glTranslatef(0.15, calf_length, 0.25);
    glColor3f(0.5, 0.5, 0.0);
    glutSolidSphere(knee_radius, 200, 200);
    glTranslatef(-0.15, -calf_length, -0.25);

    // calf
    glScalef(0.3, calf_length, 0.5);
    glColor3f(0.0, 0.0, 1.0);
    draw_cube();
    glPopMatrix();
}

void draw_floor()
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if ((i + j) % 2 == 0)
                glColor3f(0.0, 0.0, 0.0);
            else
                glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_POLYGON);
            glVertex3f(i, 0.0, j);
            glVertex3f(i, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j);
            glEnd();
        }
    }
}

void draw_axes()
{
    // original point
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glutSolidSphere(0.7, 200, 200);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glColor3f(1.0, 0.0, 1.0);
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();

    // X-axis
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();
}

void draw_physical_scene()
{
    draw_floor();
    draw_axes();

    fraction = (float)frame_count / frame_per_idle;
    float x_in_idle_transition = walking * move_X_direction * fraction;
    float z_in_idle_transition = walking * move_Z_direction * fraction;

    glTranslatef(robot_position[0], robot_position[1], robot_position[2]);
    glTranslatef(x_in_idle_transition, 0, z_in_idle_transition);

    if (move_X_direction == 1)
    {
        glTranslatef(0, 0, 1);
        glRotatef(90, 0, 1, 0);
    }
    else if (move_X_direction == -1)
    {
        glRotatef(-90, 0, 1, 0);
    }
    else if (move_Z_direction == -1)
    {
        glRotatef(180, 0, 1, 0);
    }

    /*
    if (move_X_direction == -1) //轉到90
    {
        glTranslatef(0, 0, 1);
        if((total_degree % 360) == 0)
        {
            glRotatef(90, 0, 1, 0);
            total_degree += 90;
        }
        else if((total_degree % 360) == 180)
        {
            glRotatef(270, 0, 1, 0);
            total_degree += 270;
        }
        else if((total_degree % 360) == 270)
        {
            glRotatef(180, 0, 1, 0);
            total_degree += 180;
        }
    }
    else if (move_X_direction == 1)//轉到270
    {
        if((total_degree % 360) == 0)
        {
            glRotatef(270, 0, 1, 0);
            total_degree += 270;
        }
        else if((total_degree % 360) == 180)
        {
            glRotatef(90, 0, 1, 0);
            total_degree += 90;
        }
        else if((total_degree % 360) == 90)
        {
            glRotatef(180, 0, 1, 0);
            total_degree += 180;
        }
    }
    else if (move_Z_direction == -1) //轉到180
    {
        if((total_degree % 360) == 0)
        {
            glRotatef(180, 0, 1, 0);
            total_degree += 180;
        }
        else if((total_degree % 360) == 90)
        {
            glRotatef(90, 0, 1, 0);
            total_degree += 90;
        }
        else if((total_degree % 360) == 270)
        {
            glRotatef(270, 0, 1, 0);
            total_degree += 270;
        }
    }
    else if (move_Z_direction == 1)//轉到0
    {
        if((total_degree % 360) == 90)
        {
            glRotatef(270, 0, 1, 0);
            total_degree += 270;
        }
        else if((total_degree % 360) == 180)
        {
            glRotatef(180, 0, 1, 0);
            total_degree += 180;
        }
        else if((total_degree % 360) == 270)
        {
            glRotatef(90, 0, 1, 0);
            total_degree += 90;
        }
    }
    */

    draw_head();
    draw_body();
    draw_upper_arm();
    draw_fore_arm();
    draw_thigh();
    draw_calf();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 512, 512);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 25.0);

    glEnable(GL_DEPTH_TEST);

    if (sphere == NULL)
    {
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricNormals(sphere, GLU_SMOOTH);
    }
    if (cylind == NULL)
    {
        cylind = gluNewQuadric();
        gluQuadricDrawStyle(cylind, GLU_FILL);
        gluQuadricNormals(cylind, GLU_SMOOTH);
    }
    if (disk == NULL)
    {
        disk = gluNewQuadric();
        gluQuadricDrawStyle(disk, GLU_FILL);
        gluQuadricNormals(disk, GLU_SMOOTH);
    }

    cv = cos(view_degree * PI / 180.0);
    sv = sin(view_degree * PI / 180.0);

    eye_position[0] = 10;
    eye_position[1] = 3;
    eye_position[2] = 10;

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // move robot
    case 'a':{
        walking = 1;
        move_Z = -1;
        move_Z_direction = -1;
        move_X = 0;
        move_X_direction = 0;
        break;
        }
    case 'd':{
        walking = 1;
        move_Z = 1;
        move_Z_direction = 1;
        move_X = 0;
        move_X_direction = 0;
        break;
        }
    case 'w':{
        walking = 1;
        move_X = -1;
        move_X_direction = -1;
        move_Z = 0;
        move_Z_direction = 0;
        break;
        }
    case 's':{
        walking = 1;
        move_X = 1;
        move_X_direction = 1;
        move_Z = 0;
        move_Z_direction = 0;
        break;
        }
    case 'O':{
        robot_position[0] = 0;
        robot_position[1] = 0;
        robot_position[2] = 0;
        break;
        }

    // shift eye by xyz
    case 'x':{
        eye_position[0] += 0.1;
        break;
        }
    case 'X':{
        eye_position[0] -= 0.1;
        break;
        }
    case 'y':{
        eye_position[1] += 0.1;
        break;
        }
    case 'Y':{
        eye_position[1] -= 0.1;
        break;
        }
    case 'z':{
        eye_position[2] += 0.1;
        break;
        }
    case 'Z':{
        eye_position[2] -= 0.1;
        break;
        }
    
    // shift eye uvw
    case 'U':{ // up
        eye_position[0] -= 0.2 * v[0];
        eye_position[1] -= 0.2 * v[1];
        eye_position[2] -= 0.2 * v[2];
        break;
        }
    case 'D':{ // down
        eye_position[0] += 0.2 * v[0];
        eye_position[1] += 0.2 * v[1];
        eye_position[2] += 0.2 * v[2];
        break;
        }
    case 'L':{ // left
        eye_position[0] += 0.2 * u[0];
        eye_position[1] += 0.2 * u[1];
        eye_position[2] += 0.2 * u[2];
        break;
        }
    case 'E':{ // right
        eye_position[0] -= 0.2 * u[0];
        eye_position[1] -= 0.2 * u[1];
        eye_position[2] -= 0.2 * u[2];
        break;
        }
    case 'F':{ // foreward
        eye_position[0] -= 0.2 * w[0];
        eye_position[1] -= 0.2 * w[1];
        eye_position[2] -= 0.2 * w[2];
        break;
        }
    case 'B':{ // backward
        eye_position[0] += 0.2 * w[0];
        eye_position[1] += 0.2 * w[1];
        eye_position[2] += 0.2 * w[2];
        break;
        }
    
    // rotate eye by uvw
    case 'p':{ // pitch
        v[0] = v[0] * cv - w[0] * sv;
        v[1] = v[1] * cv - w[1] * sv;
        v[2] = v[2] * cv - w[2] * sv;

        w[0] = w[0] * cv + v[0] * sv;
        w[1] = w[1] * cv + v[1] * sv;
        w[2] = w[2] * cv + v[2] * sv;
        break;
        }
    case 'P':{
        v[0] = v[0] * cv + w[0] * sv;
        v[1] = v[1] * cv + w[1] * sv;
        v[2] = v[2] * cv + w[2] * sv;

        w[0] = w[0] * cv - v[0] * sv;
        w[1] = w[1] * cv - v[1] * sv;
        w[2] = w[2] * cv - v[2] * sv;
        break;
        }
    case 'h':{ // head
        u[0] = u[0] * cv - w[0] * sv;
        u[1] = u[1] * cv - w[1] * sv;
        u[2] = u[2] * cv - w[2] * sv;

        w[0] = w[0] * cv + u[0] * sv;
        w[1] = w[1] * cv + u[1] * sv;
        w[2] = w[2] * cv + u[2] * sv;
        break;
        }
    case 'H':{
        u[0] = u[0] * cv + w[0] * sv;
        u[1] = u[1] * cv + w[1] * sv;
        u[2] = u[2] * cv + w[2] * sv;

        w[0] = w[0] * cv - u[0] * sv;
        w[1] = w[1] * cv - u[1] * sv;
        w[2] = w[2] * cv - u[2] * sv;
        break;
        }
    case 'r':{ // roll
        u[0] = u[0] * cv - v[0] * sv;
        u[1] = u[1] * cv - v[1] * sv;
        u[2] = u[2] * cv - v[2] * sv;

        v[0] = v[0] * cv + u[0] * sv;
        v[1] = v[1] * cv + u[1] * sv;
        v[2] = v[2] * cv + u[2] * sv;
        break;
        }
    case 'R':{
        u[0] = u[0] * cv + v[0] * sv;
        u[1] = u[1] * cv + v[1] * sv;
        u[2] = u[2] * cv + v[2] * sv;

        v[0] = v[0] * cv - u[0] * sv;
        v[1] = v[1] * cv - u[1] * sv;
        v[2] = v[2] * cv - u[2] * sv;
        break;
        }

    // chang viewport
    case '0':{
        style = 0;
        break;
        }
    case '1':{
        style = 1;
        break;
        }
    case '2':{
        style = 2;
        break;
        }
    case '3':{
        style = 3;
        break;
        }
    case '4':{
        style = 4;
        break;
        }
    default:
        break;
    }
}

void idle()
{
    if (walking)
        frame_count++;
    if (frame_count >= frame_per_idle)
    {
        if (walking)
        {
            if (move_X != 0)
            {
                robot_position[0] += move_X;
                move_Z = 0;
                move_X = 0;
            }
            else
            {
                robot_position[2] += move_Z;
                move_X = 0;
                move_Z = 0;
            }
        }
        frame_count = 0;
        walking = 0;
    }
    display();
}

void make_projection(int k)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (k == 4)
        gluPerspective(120.0, (double)width / (double)height, 1, 50.0);
    else
    {
        if (width > height)
            glOrtho(-15.0, 15.0, -15.0 * (float)height / (float)width, 15.0 * (float)height / (float)width, 0.50, 15.0);
        else
            glOrtho(-15.0 * (float)width / (float)height, 15.0 * (float)width / (float)height, -15.0, 15.0, 0.50, 15.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void make_view(int k)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (k) // 視角
    {
    case 4:
        gluLookAt(eye_position[0], eye_position[1], eye_position[2],
                  eye_position[0] - w[0], eye_position[1] - w[1], eye_position[2] - w[2],
                  v[0], v[1], v[2]);
        break;
    case 1: /* X direction parallel viewing */
        gluLookAt(15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    case 2: /* Y direction parallel viewing */
        gluLookAt(0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        break;
    case 3: /* Z direction parallel viewing */
        gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    }
}

void draw_eye_coordinate()
{
    glMatrixMode(GL_MODELVIEW);

    /*----Draw Eye position-----*/
    glPushMatrix();
    glTranslatef(eye_position[0], eye_position[1], eye_position[2]);
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(1.0, 10, 10);
    glPopMatrix();

    /*----Draw eye coord. axes -----*/
    /* Draw Xe */
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(eye_position[0], eye_position[1], eye_position[2]);
    glVertex3f(eye_position[0] + 20.0 * u[0],
               eye_position[1] + 20.0 * u[1],
               eye_position[2] + 20.0 * u[2]);
    glEnd();

    /* Draw Ye */
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(eye_position[0], eye_position[1], eye_position[2]);
    glVertex3f(eye_position[0] + 20.0 * v[0],
               eye_position[1] + 20.0 * v[1],
               eye_position[2] + 20.0 * v[2]);
    glEnd();

    /* Draw Ze */
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(eye_position[0], eye_position[1], eye_position[2]);
    glVertex3f(eye_position[0] + 20.0 * w[0],
               eye_position[1] + 20.0 * w[1],
               eye_position[2] + 20.0 * w[2]);
    glEnd();
}

void reshape(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
    if (width > height)
        glOrtho(-15.0, 15.0, -15.0 * (float)height / (float)width, 15.0 * (float)height / (float)width, 0.50, 15.0);
    else
        glOrtho(-15.0 * (float)width / (float)height, 15.0 * (float)width / (float)height, -15.0, 15.0, 0.50, 15.0);
    */
    // 1 3只會顯示0.1秒 24不影響

    gluPerspective(120.0, (double)w / (double)h, 1, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    switch (style)
    {
    case 0:
    { // All
        make_view(4);
        make_projection(4);
        glViewport(width / 2, 0, width / 2, height / 2); // 右下**
        draw_physical_scene();

        make_view(1);
        make_projection(1);
        glViewport(0, height / 2, width / 2, height / 2); // 左上
        draw_physical_scene();
        make_view(1);
        draw_eye_coordinate();

        make_view(2);
        glViewport(width / 2, height / 2, width / 2, height / 2); // 右上**
        draw_physical_scene();
        make_view(2);
        draw_eye_coordinate();

        make_view(3);
        glViewport(0, 0, width / 2, height / 2); // 左下
        draw_physical_scene();
        make_view(3);
        draw_eye_coordinate();
        break;
    }
    case 1:
    { // X direction parallel viewing
        make_view(1);
        // make_projection(1);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(1);
        draw_eye_coordinate();
        break;
    }
    case 2:
    { // Y direction parallel viewing **
        make_view(2);
        make_projection(2);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(2);
        draw_eye_coordinate();
        break;
    }
    case 3:
    { // Z direction parallel viewing
        make_view(3);
        make_projection(3);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(3);
        draw_eye_coordinate();
        break;
    }
    case 4:
    { // Perspective **
        make_view(4);
        make_projection(4);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        break;
    }
    }
    /*
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye_position[0], eye_position[1], eye_position[2],
                  robot_position[0], robot_position[1], robot_position[2],
                   0.0, 1.0, 0.0);
        draw_physical_scene();
    */
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("MovingRobot");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}