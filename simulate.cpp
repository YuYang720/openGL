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
GLfloat mat_green_ambient[] = {0.1, 0.3, 0.1, 1.0};
GLfloat mat_green_diffuse[] = {0.1, 0.9, 0.1, 1.0};
GLfloat mat_green_specular[] = {0.4, 0.4, 0.4, 1.0};
GLfloat mat_green_shininess = 64.0;

GLfloat obsidian_ambient[] = {0.05375f, 0.05000f, 0.06625f, 1.0f};
GLfloat obsidian_diffuse[] = {0.12875f, 0.17000f, 0.22525f, 1.0f};
GLfloat obsidian_specular[] = {0.332741f, 0.328634f, 0.346430f, 1.0f};
GLfloat obsidian_shininess = 38.4f;

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
GLfloat copper_shininess = 70.8f;

GLfloat gold_ambient[] = {0.24725f, 0.19950f, 0.07450f, 1.0f};
GLfloat gold_diffuse[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
GLfloat gold_specular[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
GLfloat gold_shininess = 100.2f;

GLfloat bronze_ambient[] = {0.21250f, 0.12750f, 0.05400f, 1.0f};
GLfloat bronze_diffuse[] = {0.71400f, 0.42840f, 0.18144f, 1.0f};
GLfloat bronze_specular[] = {0.393548f, 0.271906f, 0.166721f, 1.0f};
GLfloat bronze_shininess = 25.6f;

GLfloat ruby_ambient[] = {0.17450f, 0.01175f, 0.01175f, 0.55f};
GLfloat ruby_diffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f};
GLfloat ruby_specular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f};
GLfloat ruby_shininess = 76.8f;

GLfloat Black_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat Black_plastic_diffuse[] = {0.01f, 0.01f, 0.01f, 1.0f};
GLfloat Black_plastic_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat Black_plastic_shininess = 32.0f;

GLfloat G_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat G_plastic_diffuse[] = {0.1f, 0.35f, 0.1f, 1.0f};
GLfloat G_plastic_specular[] = {0.45f, 0.55f, 0.45f, 1.0f};
GLfloat G_plastic_shininess = 32.0f;

GLfloat W_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat W_plastic_diffuse[] = {0.55f, 0.55f, 0.55f, 1.0f};
GLfloat W_plastic_specular[] = {0.70f, 0.70f, 0.70f, 1.0f};
GLfloat W_plastic_shininess = 32.0f;

GLfloat R_plastic_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat R_plastic_diffuse[] = {0.5f, 0.0f, 0.0f, 1.0f};
GLfloat R_plastic_specular[] = {0.7f, 0.6f, 0.6f, 1.0f};
GLfloat R_plastic_shininess = 32.0f;

GLfloat cyan_plastic_ambient[] = {0.0f, 0.1f, 0.06f, 1.0f};
GLfloat cyan_plastic_diffuse[] = {0.0f, 0.50980392f, 0.5080392f, 1.0f};
GLfloat cyan_plastic_specular[] = {0.50196078f, 0.50196078f, 0.50196078f, 1.0f};
GLfloat cyan_plastic_shininess = 32.0f;

GLfloat rock_diffuse[] = {0.28, 0.28, 0.28, 1.0};
GLfloat rock_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat rock_specular[] = {0.0, 0.0, 0.0, 1.0};

GLfloat xfloor_diffuse[] = {0.6, 0.6, 0.6, 1.0};
GLfloat xfloor_ambient[] = {0.3, 0.3, 0.3, 1.0};
GLfloat xfloor_specular[] = {0.0, 0.0, 0.0, 1.0};

GLfloat yfloor_diffuse[] = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat yfloor_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat yfloor_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};

/*--------------light source properties ------------*/
float light_diffuse[] = {0.8, 0.4, 0.4, 1.0};
float light_specular[] = {0.7, 0.7, 0.7, 1.0};
float light_ambient[] = {0.1, 0.1, 0.1, 1.0};

// spot light
float light_position[] = {10.0, 14.0, 10.0, 1.0}; 
float light_direction[] = {-1.0, -1.0, -1.0, 0.0};
float light_cutoff = 60.0;
float light_exponent = 8.0;

// point light located at a fixed position in the scene
float light1_position[] = {-0.5, 1.0, -2.0, 1.0}; // (x,y,z,'1') positional light
float light1_diffuse[] = {0.95, 0.95, 0.95, 1.0}; // original:(0.7, 0.7, 0.0, 1.0);
float light1_specular[] = {0.5, 0.5, 0.5, 1.0};

// directional light
float light2_direction[] = {-2.0, -2.0, 1.0, 0.0};
float light2_diffuse[] = {0.95, 0.95, 0.95, 1.0};
float light2_specular[] = {0.5, 0.5, 0.5, 1.0};


float global_ambient[] = {0.2, 0.2, 0.2, 1.0};

float light0_angle = 0.0;

/*---------------motion---------------*/
float walk_upper_arm_degree = 40;
float walk_fore_arm_degree = 15;
float walk_thigh_degree = 30;
float walk_calf_degree = 20;
float total_degree = 0;

bool walking;
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
float normal[6][3] = {
    {0.0, -1.0, 0.0}, 
    {0.0, 1.0, 0.0}, 
    {-1.0, 0.0, 0.0}, 
    {1.0, 0.0, 0.0}, 
    {0.0, 0.0, -1.0}, 
    {0.0, 0.0, 1.0}
};
GLUquadricObj *sphere = NULL, *cylind = NULL, *disk;

void init();
void normal_key(unsigned char, int, int);
void special_key(int key, int x, int y);
void idle();
void reshape(int, int);
void display();

void make_view(int);
void make_projection(int);
void draw_eye_coordinate();

void light1_fixed_in_eye();
void light2_fixed_in_world();
void rotate_light0_position();

void draw_cube();
void draw_floor();
void draw_axes();
void draw_obstacles();
void draw_head();
void draw_body();
void draw_upper_arm();
void draw_fore_arm();
void draw_thigh();
void draw_calf();
void draw_sence();

void walk_limbs_motion(float, float);
void walk_small_limbs_motion(float, float);

void light1_fixed_in_eye()
{   /*------position light1 (fixed) in eye coord sys ------*/
    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glTranslatef(light1_position[0], light1_position[1], light1_position[2]);
    glDisable(GL_LIGHTING);
    glColor3f(0.80, 0.80, 0.0);//yellow
    glutSolidSphere(0.3, 12, 12);
    glPopMatrix();
}

void light2_fixed_in_world()
{
    glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);
}

void rotate_light0_position()
{
    glPushMatrix();
    glTranslatef(8.0, 0.0, 8.0);         /* Move to [8, 0, 8] */
    glRotatef(light0_angle, 0.0, 1.0, 0.0); /* Rotate about y-axis */
    /*-------Draw light source as a red cube----*/
    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(0.5, 8, 8);
    glPopMatrix();

    glEnable(GL_LIGHTING); /* Turn on lighting */
    /*----Redefine position and direction of light0-----*/
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
    glPopMatrix();
}

void draw_cube()
{
    for (int i = 0; i < 6; i++)
    {
        glNormal3fv(normal[i]);
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

    //glColor3f(0.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pearl_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pearl_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pearl_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pearl_shininess);

    glutSolidSphere(head_radius, 200, 200);
    glPopMatrix();
}

void draw_body()
{
    glPushMatrix();
    glTranslatef(0, thigh_length + calf_length, 0);
    glScalef(1.0, body_length, 1.5);

    //glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess);

    draw_cube();
    glPopMatrix();
}

void draw_upper_arm()
{
    glPushMatrix();
    glTranslatef(1, body_length + thigh_length + calf_length - upper_arm_length, 0.4);
    walk_limbs_motion(upper_arm_length, walk_upper_arm_degree);// 先往後擺 再往前擺
    
    // elbow
    //glColor3f(0.5, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copper_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copper_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copper_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copper_shininess);
    glTranslatef(0.25, 0, 0.35);
    glutSolidSphere(elbow_radius, 200, 200);
    glTranslatef(-0.25, 0, -0.35);

    // arm    
    //glColor3f(0.5, 0.0, 0.0); // brown
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copper_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copper_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copper_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copper_shininess);
    glScalef(0.5, upper_arm_length, 0.7);
    draw_cube();
    glPopMatrix();

    // another arm-----------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(-0.5, body_length + thigh_length + calf_length - upper_arm_length, 0.4);
    walk_limbs_motion(upper_arm_length, -walk_upper_arm_degree);// 先往前擺 在往後擺
    
    // elbow //glColor3f(0.5, 0.0, 0.0);
    glTranslatef(0.25, 0, 0.35);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copper_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copper_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copper_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copper_shininess);
    glutSolidSphere(elbow_radius, 200, 200);
    glTranslatef(-0.25, 0, -0.35);

    // arm //glColor3f(0.5, 0.0, 0.0);
    glScalef(0.5, upper_arm_length, 0.7);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copper_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copper_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copper_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copper_shininess);
    draw_cube();
    glPopMatrix();
}

void draw_fore_arm()
{
    glPushMatrix();
    glTranslatef(1 + 0.1, body_length + thigh_length + calf_length - upper_arm_length - fore_arm_length, 0.4 + 0.1);
    walk_limbs_motion(fore_arm_length + upper_arm_length, walk_upper_arm_degree); // 跟著上臂先往後擺 再往前擺
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree); // 前臂單獨 永遠向前

    glScalef(0.3, fore_arm_length, 0.5);
    //glColor3f(0.0, 0.5, 0.0); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_green_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_green_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_green_shininess);
    draw_cube();
    glPopMatrix();

    //-------------------------------------------------------------------
    
    glPushMatrix();
    glTranslatef(-0.3 - 0.1, body_length + thigh_length + calf_length - upper_arm_length - fore_arm_length, 0.4 + 0.1);
    walk_limbs_motion(fore_arm_length + upper_arm_length, -walk_upper_arm_degree); // 跟著上臂先往前擺 再往後擺
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree); // 前臂單獨 永遠向前
    glScalef(0.3, fore_arm_length, 0.5);
    //glColor3f(0.0, 0.5, 0.0); 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_green_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_green_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_green_shininess);
    draw_cube();
    glPopMatrix();
}

void draw_thigh()
{
    glPushMatrix();
    glTranslatef(0, calf_length, 0.5);

    // butt // glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.2, thigh_length + 0.1, 0.3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
    glutSolidSphere(butt_radius, 200, 200);
    glTranslatef(-0.2, -thigh_length - 0.1, -0.3);

    // thigh // glColor3f(0.5, 0.5, 0.0); // green yellow
    walk_limbs_motion(thigh_length, walk_thigh_degree);

    glScalef(0.4, thigh_length, 0.6);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
    draw_cube();
    glPopMatrix();

    // another thigh----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.6, calf_length, 0.5);

    // butt // glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.2, thigh_length, 0.3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
    glutSolidSphere(butt_radius, 200, 200);
    glTranslatef(-0.2, -thigh_length, -0.3);

    // thigh //glColor3f(0.5, 0.5, 0.0);
    walk_limbs_motion(thigh_length, -walk_thigh_degree);

    glScalef(0.4, thigh_length, 0.6);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gold_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gold_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, gold_shininess);
    draw_cube();
    glPopMatrix();
}

void draw_calf()
{
    glPushMatrix();
    glTranslatef(0.1, 0, 0.5);
    walk_limbs_motion(thigh_length + calf_length, walk_thigh_degree);
    walk_small_limbs_motion(calf_length, walk_calf_degree);

    // knee // glColor3f(0.5, 0.5, 0.0);
    glTranslatef(0.15, calf_length, 0.25);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidian_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidian_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidian_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidian_shininess);
    glutSolidSphere(knee_radius, 200, 200);
    glTranslatef(-0.15, -calf_length, -0.25);

    // calf //glColor3f(0.0, 0.0, 1.0);
    glScalef(0.3, calf_length, 0.5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidian_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidian_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidian_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidian_shininess);
    draw_cube();
    glPopMatrix();

    // another calf-----------------------------------------------------------------

    glPushMatrix();
    glTranslatef(0.6, 0, 0.5);
    walk_limbs_motion(thigh_length + calf_length, -walk_thigh_degree);
    walk_small_limbs_motion(calf_length, walk_calf_degree);

    // knee // glColor3f(0.5, 0.5, 0.0);
    glTranslatef(0.15, calf_length, 0.25);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidian_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidian_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidian_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidian_shininess);
    glutSolidSphere(knee_radius, 200, 200);
    glTranslatef(-0.15, -calf_length, -0.25);

    // calf // glColor3f(0.0, 0.0, 1.0);
    glScalef(0.3, calf_length, 0.5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obsidian_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obsidian_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obsidian_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, obsidian_shininess);
    draw_cube();
    glPopMatrix();
}

void draw_floor()
{
    /*
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, xfloor_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, xfloor_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, xfloor_ambient);
    glNormal3f(0.0, 1.0, 0.0);
    */
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            
            if ((i + j) % 2 == 0)
            {
                //glColor3f(0.0, 0.0, 0.0);
                
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, xfloor_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, xfloor_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, xfloor_ambient);
                glNormal3f(0.0, 1.0, 0.0);
                
            }    
            else
            {
                //glColor3f(1.0, 1.0, 1.0);
                
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yfloor_diffuse); 
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yfloor_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yfloor_ambient);
                glNormal3f(0.0, 1.0, 0.0);    
                
            }
            
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

void draw_obstacles()
{
    // rock
    glPushMatrix();
    glTranslatef(3.0, 0, 2.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rock_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rock_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rock_diffuse);
    glutSolidSphere(1.0, 200, 200);
    glPopMatrix();
    // obstacle
    glPushMatrix();
    glTranslatef(7.0, 0, 5.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Black_plastic_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Black_plastic_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Black_plastic_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Black_plastic_shininess);
    draw_cube();
    glPopMatrix();
    // obstacle
    glPushMatrix();
    glTranslatef(10.0, 0, 2.0);
    glRotatef(-90, 1, 0, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, W_plastic_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, W_plastic_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, W_plastic_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, W_plastic_shininess);
    gluCylinder(cylind, 1.0, 0.3, 2, 12, 3);
    glPopMatrix();
}

void draw_physical_scene()
{
    
    draw_floor();
    draw_axes();
    draw_obstacles();
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
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 25.0);
    */
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    /*----------------spotlight0-------------------*/
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, light_exponent);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /*---------------point light1-----------------------*/
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    /*---------------directional light1-----------------------*/
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    //glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);/**/

    /*--------------global lighting status--------*/
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    /* local viewer */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/

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

void normal_key(unsigned char key, int x, int y)
{
    //int mod = glutGetModifiers();
    switch (key)
    {
    /*------change point light color/intensity (press alt+color)------ */
    case 'w':{ // white
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.95;
            light1_diffuse[1] = 0.95;
            light1_diffuse[2] = 0.95;
            init();
        }
        break;
    }
    case 'r':{ // red
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.95;
            light1_diffuse[1] = 0.05;
            light1_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'g':{ // green
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.05;
            light1_diffuse[1] = 0.95;
            light1_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'b':{ // blue
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.05;
            light1_diffuse[1] = 0.05;
            light1_diffuse[2] = 0.95;
            init();
        }
        break;
    }
    default:
        break;
    }

    switch (key)
    {   
    /*------change directional light color/intensity/direction ------- */
    /*
    case 'i':{ // white
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_CTRL)
        {
            light2_diffuse[0] = 0.95;
            light2_diffuse[1] = 0.95;
            light2_diffuse[2] = 0.95;
            init();
        }
        break;
    }
    case 'e':{ // red
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_CTRL)
        {
            light2_diffuse[0] = 0.95;
            light2_diffuse[1] = 0.05;
            light2_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'n':{ // green
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_CTRL)
        {
            light2_diffuse[0] = 0.05;
            light2_diffuse[1] = 0.95;
            light2_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'l':{ // blue
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_CTRL)
        {
            light2_diffuse[0] = 0.05;
            light2_diffuse[1] = 0.05;
            light2_diffuse[2] = 0.95;
            init();
        }
        break;
    }*/
    
    case '9':{ // white
        light2_diffuse[0] = 0.95;
        light2_diffuse[1] = 0.95;
        light2_diffuse[2] = 0.95;
        init();
        break;
        }
    case '8':{ // red
        light2_diffuse[0] = 0.95;
        light2_diffuse[1] = 0.05;
        light2_diffuse[2] = 0.05;
        init();
        break;
        }
    case '7':{ // green
        light2_diffuse[0] = 0.05;
        light2_diffuse[1] = 0.95;
        light2_diffuse[2] = 0.05;
        init();
        break;
        }
    case '6':{ // blue
        light2_diffuse[0] = 0.05;
        light2_diffuse[1] = 0.05;
        light2_diffuse[2] = 0.95;
        init();
        break;
        }
    
    case 'F':{
        light2_direction[0] += 5.0;
        break;
        }
    case 'G':{
        light2_direction[0] -= 5.0;
        break;
        }
    case 'H':{
        light2_direction[1] += 5.0;
        break;
        }
    case 'J':{
        light2_direction[1] -= 5.0;
        break;
        }
    case 'K':{
        light2_direction[2] += 5.0;
        break;
        }
    case 'L':{
        light2_direction[2] -= 5.0;
        break;
        }
    default:
        break;
    }

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
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
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
    case 'Z':{
        eye_position[0] += 0.1;
        break;
        }
    case 'X':{
        eye_position[0] -= 0.1;
        break;
        }
    case 'C':{
        eye_position[1] += 0.1;
        break;
        }
    case 'V':{
        eye_position[1] -= 0.1;
        break;
        }
    case 'B':{
        eye_position[2] += 0.1;
        break;
        }
    case 'N':{
        eye_position[2] -= 0.1;
        break;
        }
    
    // shift eye uvw
    case 'z':{ // up
        eye_position[0] -= 0.2 * v[0];
        eye_position[1] -= 0.2 * v[1];
        eye_position[2] -= 0.2 * v[2];
        break;
        }
    case 'x':{ // down
        eye_position[0] += 0.2 * v[0];
        eye_position[1] += 0.2 * v[1];
        eye_position[2] += 0.2 * v[2];
        break;
        }
    case 'c':{ // left
        eye_position[0] += 0.2 * u[0];
        eye_position[1] += 0.2 * u[1];
        eye_position[2] += 0.2 * u[2];
        break;
        }
    case 'v':{ // right
        eye_position[0] -= 0.2 * u[0];
        eye_position[1] -= 0.2 * u[1];
        eye_position[2] -= 0.2 * u[2];
        break;
        }
    case 'b':{ // foreward
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
        eye_position[0] -= 0.2 * w[0];
        eye_position[1] -= 0.2 * w[1];
        eye_position[2] -= 0.2 * w[2];
        break;
        }
    case 'n':{ // backward
        eye_position[0] += 0.2 * w[0];
        eye_position[1] += 0.2 * w[1];
        eye_position[2] += 0.2 * w[2];
        break;
        }
    
    // rotate eye by uvw
    case 'f':{ // pitch
        v[0] = v[0] * cv - w[0] * sv;
        v[1] = v[1] * cv - w[1] * sv;
        v[2] = v[2] * cv - w[2] * sv;

        w[0] = w[0] * cv + v[0] * sv;
        w[1] = w[1] * cv + v[1] * sv;
        w[2] = w[2] * cv + v[2] * sv;
        break;
        }
    case 'g':{
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
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
    case 'j':{
        u[0] = u[0] * cv + w[0] * sv;
        u[1] = u[1] * cv + w[1] * sv;
        u[2] = u[2] * cv + w[2] * sv;

        w[0] = w[0] * cv - u[0] * sv;
        w[1] = w[1] * cv - u[1] * sv;
        w[2] = w[2] * cv - u[2] * sv;
        break;
        }
    case 'k':{ // roll
        u[0] = u[0] * cv - v[0] * sv;
        u[1] = u[1] * cv - v[1] * sv;
        u[2] = u[2] * cv - v[2] * sv;

        v[0] = v[0] * cv + u[0] * sv;
        v[1] = v[1] * cv + u[1] * sv;
        v[2] = v[2] * cv + u[2] * sv;
        break;
        }
    case 'l':{
        u[0] = u[0] * cv + v[0] * sv;
        u[1] = u[1] * cv + v[1] * sv;
        u[2] = u[2] * cv + v[2] * sv;

        v[0] = v[0] * cv - u[0] * sv;
        v[1] = v[1] * cv - u[1] * sv;
        v[2] = v[2] * cv - u[2] * sv;
        break;
        }

    // turn on off light
    case '!':{ // on 0
        glEnable(GL_LIGHT0);
        break;
        }
    case '@':{ // off 0
        glDisable(GL_LIGHT0);
        break;
        }
    case '#':{ // on 1
        glEnable(GL_LIGHT1);
        break;
        }
    case '$':{ // off 1
        glDisable(GL_LIGHT1);
        break;
        }
    case '%':{ // on 2
        glEnable(GL_LIGHT2);
        break;
        }
    case '^':{ // off 2
        glDisable(GL_LIGHT2);
        break;
        }

    // rotate light0 position
    case 'm':{
        light0_angle += 5.0;
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

void special_key(int key, int x, int y)
{/*
    int mod = glutGetModifiers();
    if(mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT))

    switch(key)
    {
    //-------change color/intensity of point light-------/
    case GLUT_KEY_F1:{ // white
        light1_diffuse[0] = 0.95;
        light1_diffuse[1] = 0.95;
        light1_diffuse[2] = 0.95;
        break;
        }
    case GLUT_KEY_F2:{ // red
        light1_diffuse[0] = 0.95;
        light1_diffuse[1] = 0.05;
        light1_diffuse[2] = 0.05;
        break;
        }
    case GLUT_KEY_F3:{ // green
        light1_diffuse[0] = 0.05;
        light1_diffuse[1] = 0.95;
        light1_diffuse[2] = 0.05;
        break;
        }
    case GLUT_KEY_F4:{ // blue
        light1_diffuse[0] = 0.05;
        light1_diffuse[1] = 0.05;
        light1_diffuse[2] = 0.95;
        break;
        }
    default:
        break;
    }
   */ 
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
        light1_fixed_in_eye();
        gluLookAt(eye_position[0], eye_position[1], eye_position[2],
                  eye_position[0] - w[0], eye_position[1] - w[1], eye_position[2] - w[2],
                  v[0], v[1], v[2]);
        light2_fixed_in_world();
        rotate_light0_position();
        break;
    case 1: /* X direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        light2_fixed_in_world();
        rotate_light0_position();
        break;
    case 2: /* Y direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        light2_fixed_in_world();
        rotate_light0_position();
        break;
    case 3: /* Z direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        light2_fixed_in_world();
        rotate_light0_position();
        break;
    }
}

void draw_eye_coordinate()
{
    glMatrixMode(GL_MODELVIEW);

    /*----Draw Eye position-----*/
    glPushMatrix();
    glTranslatef(eye_position[0], eye_position[1], eye_position[2]);
    //glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_green_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_green_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_green_shininess);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    /*-----Draw Xe----- */
    //glColor3f(1.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, W_plastic_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, W_plastic_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, W_plastic_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, W_plastic_shininess);
    glBegin(GL_LINES);
    glVertex3f(eye_position[0], eye_position[1], eye_position[2]);
    glVertex3f(eye_position[0] + 20.0 * u[0],
               eye_position[1] + 20.0 * u[1],
               eye_position[2] + 20.0 * u[2]);
    glEnd();

    /*----- Draw Ye -----*/
    //glColor3f(1.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, R_plastic_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, R_plastic_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, R_plastic_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, R_plastic_shininess);
    glBegin(GL_LINES);
    glVertex3f(eye_position[0], eye_position[1], eye_position[2]);
    glVertex3f(eye_position[0] + 20.0 * v[0],
               eye_position[1] + 20.0 * v[1],
               eye_position[2] + 20.0 * v[2]);
    glEnd();

    /*------ Draw Ze----- */
    //glColor3f(0.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cyan_plastic_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyan_plastic_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan_plastic_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cyan_plastic_shininess);
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
    case 0:{ // All
        
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
    case 1:{ // X direction parallel viewing
        
        make_view(1);
        make_projection(1);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(1);
        draw_eye_coordinate();
        break;
    }
    case 2:{ // Y direction parallel viewing **
        
        make_view(2);
        make_projection(2);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(2);
        draw_eye_coordinate();
        break;
    }
    case 3:{ // Z direction parallel viewing
        
        make_view(3);
        make_projection(3);
        glViewport(0, 0, width, height);
        draw_physical_scene();
        make_view(3);
        draw_eye_coordinate();
        break;
    }
    case 4:{ // Perspective **
        
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
    glutKeyboardFunc(normal_key);
    glutSpecialFunc(special_key);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}