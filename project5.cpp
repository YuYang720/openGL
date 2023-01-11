#include <cmath>
#include <ctime>
#include <iostream>

#include <GL/glut.h>

#define PI 3.141592653
#define TSIZE 64 // define texture dimension
#define ON 1
#define OFF 0

using namespace std;

int width = 600, height = 600;
int style = 0;
float robot_position[3] = {0.0, 0.0, 0.0};

/*------------------------------eye---------------------------------*/
float eye_position[3] = {10.0, 3.0, 10.0};
float Focus_position[3] = {0.0, 0.0, 0.0};
float Vup_vector[3] = {0.0, 1.0, 0.0};

float u[3] = {1.0, 0.0, 0.0};
float v[3] = {0.0, 1.0, 0.0};
float w[3] = {0.0, 0.0, 1.0}; //-w
float cv, sv;                 // cos(5.0), sin(5.0)轉5度
float view_degree = 5.0;

/*--------------------------------size----------------------------------*/
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

/*--------------------------------motion----------------------------------*/
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

/*---------------------------material properties---------------------------*/
GLfloat mat_green_ambient[] = {0.1, 0.3, 0.1, 1.0};
GLfloat mat_green_diffuse[] = {0.1, 0.9, 0.1, 1.0};
GLfloat mat_green_specular[] = {0.4, 0.4, 0.4, 1.0};
GLfloat mat_green_shininess = 100.0;

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

GLfloat floor_diffuse[] = {0.6, 0.6, 0.6, 1.0};
GLfloat floor_ambient[] = {0.3, 0.3, 0.3, 1.0};
GLfloat floor_specular[] = {0.0, 0.0, 0.0, 1.0};

GLfloat bill_obj_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat bill_obj_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat bill_obj_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};

/*------------------------light source properties ----------------------*/
// spot light (example)
float light0_diffuse[] = {0.8, 0.4, 0.4, 1.0};
float light0_specular[] = {0.7, 0.7, 0.7, 1.0};
float light0_ambient[] = {0.1, 0.1, 0.1, 1.0};

float light0_position[] = {10.0, 14.0, 10.0, 1.0};
float light0_direction[] = {-1.0, -1.0, -1.0, 0.0};
float light0_cutoff = 60.0;
float light0_exponent = 8.0;
float light0_angle = 0.0;

// point light located at a fixed position in the scene
float light1_position[] = {-0.5, 1.0, -2.0, 1.0};
float light1_diffuse[] = {0.95, 0.95, 0.95, 1.0};
float light1_specular[] = {0.5, 0.5, 0.5, 1.0};

// directional light
float light2_direction[] = {-2.0, -2.0, 1.0, 0.0};
float light2_diffuse[] = {0.95, 0.95, 0.95, 1.0};
float light2_specular[] = {0.5, 0.5, 0.5, 1.0};

// spot light
float light3_diffuse[] = {0.8, 0.4, 0.4, 1.0};
float light3_specular[] = {0.7, 0.7, 0.7, 1.0};
float light3_ambient[] = {0.1, 0.1, 0.1, 1.0};
float light3_position[] = {0.0, 0.0, 0.0, 1.0};
float light3_direction[] = {1.0, 1.0, 1.0, 0.0};
float light3_cutoff = 60.0;
float light3_exponent = 8.0;

double light_attenuation = 0.5;
float global_ambient[] = {0.2, 0.2, 0.2, 1.0};

/*----------------image space for textures -------------------------*/
unsigned int TextureID[6];
unsigned char circle[TSIZE][TSIZE][4];
unsigned char star[TSIZE][TSIZE][4];
unsigned char land[TSIZE][TSIZE][4];
unsigned char waterwave[TSIZE][TSIZE][4];
unsigned char arrow[TSIZE][TSIZE][4]; /* arrow textures */
unsigned char brick[TSIZE][TSIZE][4]; /* brick wall textures */

float ds = 0.0, dt = 0.0;
float textAng = 0.0;
int status = ON; // Texture mapping status

/*----------------billboard parameter-----------------*/
// float bill_axe_a[3], bill_axe_b[3];
float mdv_mtx[16]; // modelview matrix

/*--------------------------idle-------------------------------------*/
float fraction;
float x_in_idle_transition;
float z_in_idle_transition;

int frame_per_idle = 100;
int frame_count;

/*--------------------------------cube--------------------------------*/
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
    {0.0, 0.0, 1.0}};
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
void light3_attach_robot();
void rotate_light0_position();

void Create_Texture_Circle();
void Create_Texture_Star();
void Create_Texture_Land();
void Create_Texture_Waterwave();
void Create_Texture_Arrow();
void Create_Texture_Brick();
void Construct_billboard(float, float, float, float);
void draw_billboard();

void draw_cube();
void draw_environment();
void draw_head();
void draw_body();
void draw_upper_arm();
void draw_fore_arm();
void draw_thigh();
void draw_calf();
void draw_sence();
void walk_limbs_motion(float, float);
void walk_small_limbs_motion(float, float);


void Construct_billboard(float x, float z, float w, float h)
{
    /*--------------Define the a and b axes for billboards ------------*/
    float length = sqrt(mdv_mtx[2] * mdv_mtx[2] + mdv_mtx[10] * mdv_mtx[10]);

    float bill_axe_a[] = {mdv_mtx[10] / length, 0.0, -mdv_mtx[2] / length};
    float bill_axe_b[] = {0.0, 1.0, 0.0};

    /*--------draw a billboard, center=[x,z], width=w, height = h-------*/

    // float Vertex0[3], Vertex1[3], Vertex2[3], Vertex3[3];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    float Vertex0[] = {x - (w / 2) * bill_axe_a[0], 0.0, z - (w / 2) * bill_axe_a[2]};
    float Vertex1[] = {x + (w / 2) * bill_axe_a[0], 0.0, z + (w / 2) * bill_axe_a[2]};
    float Vertex2[] = {x + (w / 2) * bill_axe_a[0], h, z + (w / 2) * bill_axe_a[2]};
    float Vertex3[] = {x - (w / 2) * bill_axe_a[0], h, z - (w / 2) * bill_axe_a[2]};

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(Vertex0);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(Vertex1);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(Vertex2);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(Vertex3);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

void draw_billboard()
{
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // glEnable(GL_TEXTURE_2D);

    glGetFloatv(GL_MODELVIEW_MATRIX, mdv_mtx);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bill_obj_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bill_obj_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bill_obj_ambient);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[0]);
    Construct_billboard(5.0 * 4.0, 3.0 * 4.0, 5.0, 8.0);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);
    Construct_billboard(6.0 * 4.0, 5.0 * 4.0, 5.0, 8.0);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[3]);
    Construct_billboard(3.0 * 4.0, 6.0 * 4.0, 5.0, 8.0);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[4]);
    Construct_billboard(2.0 * 4.0, 7.0 * 4.0, 5.0, 8.0);
    Construct_billboard(7.0 * 4.0, 2.0 * 4.0, 5.0, 8.0);

    //glDisable(GL_TEXTURE_2D);
}

void Create_Texture_Circle()
{
    int y, x, i, temp;
    for (y = 0; y < 64; y++)
    {
        for (x = 0; x < 64; x++)
        {
            circle[y][x][0] = 100;
            circle[y][x][1] = 100;
            circle[y][x][2] = 100;
            circle[y][x][3] = 255;
        }
    }
    for (y = 16, x = 0; y < 48; y++)
    {
        if (y <= 20 && y >= 17)
            x = x + 2;
        else if (y == 22 || y == 25 || y == 31)
            x = x + 1;
        else if (y == 42 || y == 39 || y == 33)
            x = x - 1;
        else if (y <= 47 && y >= 44)
            x = x - 2;
        temp = x;
        for (x = 0; x < temp; x++)
        {
            circle[y][x][0] = 150;
            circle[y][x][1] = 150;
            circle[y][x][2] = 150;
            circle[y][x][3] = 255;
        }
        for (x = 64 - temp; x < 64; x++)
        {
            circle[y][x][0] = 150;
            circle[y][x][1] = 150;
            circle[y][x][2] = 150;
            circle[y][x][3] = 255;
        }
        x = temp;
    }

    for (x = 16, y = 0; x < 48; x++)
    {
        if (x <= 20 && x >= 17)
            y = y + 2;
        else if (x == 22 || x == 25 || x == 31)
            y = y + 1;
        else if (x == 42 || x == 39 || x == 33)
            y = y - 1;
        else if (x <= 47 && x >= 44)
            y = y - 2;
        temp = y;
        for (y = 0; y < temp; y++)
        {
            circle[y][x][0] = 200;
            circle[y][x][1] = 200;
            circle[y][x][2] = 200;
            circle[y][x][3] = 255;
        }
        for (y = 64 - temp; y < 64; y++)
        {
            circle[y][x][0] = 200;
            circle[y][x][1] = 200;
            circle[y][x][2] = 200;
            circle[y][x][3] = 255;
        }
        y = temp;
    }
    for (i = 0; i < 61; i++)
    {
        for (y = i; y < 4 + i; y++)
        {
            for (x = i; x < 4 + i; x++)
            {
                circle[y][x][0] = 255;
                circle[y][x][1] = 255;
                circle[y][x][2] = 255;
                circle[y][x][3] = 255;
            }
        }
    }
    for (i = 0; i < 61; i++)
    {
        for (y = i; y < 4 + i; y++)
        {
            for (x = 60 - i; x < 64 - i; x++)
            {
                circle[y][x][0] = 255;
                circle[y][x][1] = 255;
                circle[y][x][2] = 255;
                circle[y][x][3] = 255;
            }
        }
    }
}

void Create_Texture_Star()
{
    int x, y, i;
    for (x = 0; x < 64; x++)
    {
        for (y = 0; y < 64; y++)
        {
            star[x][y][0] = 255;
            star[x][y][1] = 255;
            star[x][y][2] = 255;
            star[x][y][3] = 0;
        }
    }
    x = 31;
    y = 60;

    while (x >= 12)
    {
        for (i = y; i > 4; i--)
        {
            star[x][i][0] = 100;
            star[x][i][1] = 100;
            star[x][i][2] = 255;
            star[x][i][3] = 255;
        }
        x--;
        y -= 3;
    }
    x = 31;
    y = 20;

    while (x >= 12)
    {
        for (i = y; i > 4; i--)
        {
            star[x][i][0] = 255;
            star[x][i][1] = 255;
            star[x][i][2] = 255;
            star[x][i][3] = 0;
        }
        x--;
        y -= 1;
    }
    x = 4;
    y = 40;

    while (y >= 18)
    {
        for (i = x; i < 32; i++)
        {
            star[i][y][0] = 100;
            star[i][y][1] = 100;
            star[i][y][2] = 255;
            star[i][y][3] = 255;
        }
        y -= 1;
        if ((y % 2) == 1)
            x += 2;
        else
            x++;
    }

    for (x = 63; x > 31; x--)
    {
        for (y = 0; y < 64; y++)
            for (i = 0; i < 4; i++)
                star[x][y][i] = star[63 - x][y][i];
    }
}

void Create_Texture_Land()
{
    int x, y, i;
    for (y = 0; y < 32; y++)
    {
        for (x = 0; x < 32; x++)
        {
            land[x][y][0] = 240;
            land[x][y][1] = 240;
            land[x][y][2] = 240;
            land[x][y][3] = 255;
        }
    }
    for (x = 24; x < 32; x++)
    {
        land[x][0][0] = 255;
        land[x][0][1] = 200;
        land[x][0][2] = 200;
        land[x][0][3] = 255;

        land[0][x][0] = 255;
        land[0][x][1] = 200;
        land[0][x][2] = 200;
        land[0][x][3] = 255;
    }
    for (x = 26; x < 32; x++)
    {
        land[x][1][0] = 255;
        land[x][1][1] = 200;
        land[x][1][2] = 200;
        land[x][1][3] = 255;

        land[1][x][0] = 255;
        land[1][x][1] = 200;
        land[1][x][2] = 200;
        land[1][x][3] = 255;
    }
    for (x = 27; x < 32; x++)
    {
        for (y = 2; y < 4; y++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 200;
            land[x][y][3] = 255;

            land[y][x][0] = 255;
            land[y][x][1] = 200;
            land[y][x][2] = 200;
            land[y][x][3] = 255;
        }
    }
    for (x = 28; x < 32; x++)
    {
        for (y = 4; y < 7; y++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 200;
            land[x][y][3] = 255;

            land[y][x][0] = 255;
            land[y][x][1] = 200;
            land[y][x][2] = 200;
            land[y][x][3] = 255;
        }
    }
    for (x = 29; x < 32; x++)
    {
        for (y = 7; y < 9; y++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 200;
            land[x][y][3] = 255;

            land[y][x][0] = 255;
            land[y][x][1] = 200;
            land[y][x][2] = 200;
            land[y][x][3] = 255;
        }
    }
    for (x = 30; x < 32; x++)
    {
        for (y = 9; y < 12; y++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 200;
            land[x][y][3] = 255;

            land[y][x][0] = 255;
            land[y][x][1] = 200;
            land[y][x][2] = 200;
            land[y][x][3] = 255;
        }
    }
    for (x = 31; x < 32; x++)
    {
        for (y = 12; y < 16; y++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 200;
            land[x][y][3] = 255;

            land[y][x][0] = 255;
            land[y][x][1] = 200;
            land[y][x][2] = 200;
            land[y][x][3] = 255;
        }
    }
    for (y = 16; y < 32; y++)
    {
        for (x = 16; x < 32; x++)
        {
            land[x][y][0] = 200;
            land[x][y][1] = 160;
            land[x][y][2] = 255;
            land[x][y][3] = 255;
        }
    }
    for (y = 20; y < 32; y++)
    {
        for (x = 20; x < 32; x++)
        {
            land[x][y][0] = 255;
            land[x][y][1] = 200;
            land[x][y][2] = 255;
            land[x][y][3] = 255;
        }
    }
    for (x = 63; x > 31; x--)
    {
        for (y = 0; y < 32; y++)
            for (i = 0; i < 4; i++)
                land[x][y][i] = land[63 - x][y][i];
    }

    /* Create the rest half part */
    for (y = 32; y < 64; y++)
    {
        for (x = 0; x < 64; x++)
            for (i = 0; i < 4; i++)
                land[x][y][i] = land[x][63 - y][i];
    }
}

void Create_Texture_Waterwave()
{
    int x, y, i;
    for (x = 0; x < 64; x++)
    {
        for (y = 0; y < 32; y++)
        {
            waterwave[x][y][0] = 0;
            waterwave[x][y][1] = 100;
            waterwave[x][y][2] = 255;
            waterwave[x][y][3] = 255;
        }
    }
    x = 0;
    y = 4;

    while (y <= 28)
    {
        for (i = x; i < 32; i++)
        {
            waterwave[i][y][0] = 200;
            waterwave[i][y][1] = 255;
            waterwave[i][y][2] = 255;
            waterwave[i][y][3] = 255;
        }
        y++;
        if (y < 9)
            x += 3;
        else if (y == 9)
            x++;
        else if (y == 10)
            x += 2;
        else if (y == 11)
            x++;
        else if (y == 12)
            x += 2;
        else if (y == 13)
            x++;
        else if (y == 14)
            x += 2;
        else if (y == 16)
            x++;
        else if (y == 19)
            x++;
        else if (y == 21)
            x++;
        else if (y == 23)
            x++;
        else if (y == 26)
            x++;
        else
            x++;
    }
    x = 0;
    y = 0;

    while (y <= 24)
    {
        for (i = x; i < 32; i++)
        {
            waterwave[i][y][0] = 0;
            waterwave[i][y][1] = 100;
            waterwave[i][y][2] = 255;
            waterwave[i][y][3] = 255;
        }
        y++;
        if (y < 5)
            x += 3;
        else if (y == 5)
            x++;
        else if (y == 6)
            x += 2;
        else if (y == 7)
            x++;
        else if (y == 8)
            x += 2;
        else if (y == 9)
            x++;
        else if (y == 10)
            x += 2;
        else if (y == 11)
            x++;
        else if (y == 14)
            x++;
        else if (y == 16)
            x++;
        else if (y == 18)
            x++;
        else if (y == 21)
            x++;
        else
            x++;
    }

    for (x = 63; x > 31; x--)
    {
        for (y = 0; y < 32; y++)
            for (i = 0; i < 4; i++)
                waterwave[x][y][i] = waterwave[63 - x][y][i];
    }

    for (y = 32; y < 64; y++)
    {
        for (x = 0; x < 64; x++)
            for (i = 0; i < 4; i++)
            {
                if (x >= 47)
                    waterwave[x][y][i] = waterwave[x - 47][y - 32][i];
                else
                    waterwave[x][y][i] = waterwave[x + 16][y - 32][i];
            }
    }
}

void Create_Texture_Arrow()
{
    int i, j, c;
    for (i = 0; i < TSIZE; i++)
    {
        for (j = 0; j < TSIZE; j++)
        {
            if (j > i / 2 && j <= 64 - i / 2)
                c = 255;
            else
                c = 0;
            arrow[i][j][0] = c / 8; // R
            arrow[i][j][1] = c / 2; // G
            arrow[i][j][2] = c / 4; // B
            if (c == 255)
                arrow[i][j][3] = 255;
            else
                arrow[i][j][3] = 0;
            /*arrow[i][j][3] = 255;*/ // A 透明度
        }
    }
    for (i = 0; i < TSIZE / 3; i++)
    {
        for (j = 0; j < TSIZE / 2 - 4; j++)
            arrow[i][j][3] = 0;
        for (j = TSIZE / 2 + 4; j < TSIZE; j++)
            arrow[i][j][3] = 0;
    }
}

void Create_Texture_Brick()
{
    int y, x, i;

    for (y = 0; y < 12; y++) /*----Create the first row of bricks----*/
    {
        for (x = 0; x < 2; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }
        for (x = 2; x < 30; x++)
        {
            brick[y][x][0] = 200;
            brick[y][x][1] = 0;
            brick[y][x][2] = 0;
            brick[y][x][3] = 255;
        }
        for (x = 30; x < 34; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }
        for (x = 34; x < 62; x++)
        {
            brick[y][x][0] = 200;
            brick[y][x][1] = 0;
            brick[y][x][2] = 0;
            brick[y][x][3] = 255;
        }
        for (x = 62; x < 64; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }
    }

    for (y = 12; y < 16; y++) /*--Create the cement between two breick layers */
    {
        for (x = 0; x < 64; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }
    }

    for (y = 16; y < 28; y++) /*--Create the 2nd layer of bricks---*/
    {
        for (x = 0; x < 14; x++)
        {
            brick[y][x][0] = 200;
            brick[y][x][1] = 0;
            brick[y][x][2] = 0;
            brick[y][x][3] = 255;
        }

        for (x = 14; x < 18; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }

        for (x = 18; x < 46; x++)
        {
            brick[y][x][0] = 200;
            brick[y][x][1] = 0;
            brick[y][x][2] = 0;
            brick[y][x][3] = 255;
        }

        for (x = 46; x < 50; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }

        for (x = 50; x < 64; x++)
        {
            brick[y][x][0] = 200;
            brick[y][x][1] = 0;
            brick[y][x][2] = 0;
            brick[y][x][3] = 255;
        }
    }

    for (y = 28; y < 32; y++) /*---Add another layer of cement----*/
    {
        for (x = 0; x < 64; x++)
        {
            brick[y][x][0] = 140;
            brick[y][x][1] = 140;
            brick[y][x][2] = 140;
            brick[y][x][3] = 255;
        }
    }

    for (y = 32; y < 64; y++)
    {
        for (x = 0; x < 64; x++)
            for (i = 0; i < 4; i++)
                brick[y][x][i] = brick[y - 32][x][i];
    }
}

void light1_fixed_in_eye()
{ /*------position light1 (fixed) in eye coord sys ------*/
    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glTranslatef(light1_position[0], light1_position[1], light1_position[2]);
    glDisable(GL_LIGHTING);
    glColor3f(0.80, 0.80, 0.0); // yellow
    glutSolidSphere(0.3, 12, 12);
    glPopMatrix();
}

void light2_fixed_in_world()
{
    glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);
}

void light3_attach_robot()
{
    glPushMatrix();
    glTranslatef(robot_position[0], robot_position[1], robot_position[2]);
    glTranslatef(x_in_idle_transition, 0, z_in_idle_transition);
    glTranslatef(0.5, 2 * head_radius + body_length + thigh_length + calf_length, 0.8);

    glPushMatrix();
    glTranslatef(light3_position[0], light3_position[1], light3_position[2]);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.2, 8, 8);
    glPopMatrix();

    glEnable(GL_LIGHTING);
    /*----Redefine position and direction of light3-----*/
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_direction);
    glPopMatrix();
}

void rotate_light0_position()
{
    glPushMatrix();
    glTranslatef(8.0, 0.0, 8.0);            /* Move to [8, 0, 8] */
    glRotatef(light0_angle, 0.0, 1.0, 0.0); /* Rotate about y-axis */
    /*-------Draw light source as a red cube----*/
    glPushMatrix();
    glTranslatef(light0_position[0], light0_position[1], light0_position[2]);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(0.5, 8, 8);
    glPopMatrix();

    glEnable(GL_LIGHTING); /* Turn on lighting */
    /*----Redefine position and direction of light0-----*/
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
    glPopMatrix();
}

void draw_cube()
{
    for (int i = 0; i < 6; i++)
    {
        glNormal3fv(normal[i]);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3fv(points[face[i][0]]);
        glTexCoord2f(0.0, 3.0);
        glVertex3fv(points[face[i][1]]);
        glTexCoord2f(5.0, 3.0);
        glVertex3fv(points[face[i][2]]);
        glTexCoord2f(5.0, 0.0);
        glVertex3fv(points[face[i][3]]);
        /*for (int j = 0; j < 4; j++)
            glVertex3fv(points[face[i][j]]);*/
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
    /*glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);*/
    glPushMatrix();

    /*glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);*/

    glTranslatef(0.5, head_radius + body_length + thigh_length + calf_length, 0.8);

    // glColor3f(0.0, 1.0, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pearl_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pearl_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pearl_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pearl_shininess);

    glutSolidSphere(head_radius, 200, 200);

    glPopMatrix();
    /*glDisable(GL_TEXTURE_2D);*/
}

void draw_body()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0, thigh_length + calf_length, 0);
    glScalef(1.0, body_length, 1.5);

    // glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);
    draw_cube();
    glPopMatrix();
}

void draw_upper_arm()
{
    glPushMatrix();
    glTranslatef(1, body_length + thigh_length + calf_length - upper_arm_length, 0.4);
    walk_limbs_motion(upper_arm_length, walk_upper_arm_degree); // 先往後擺 再往前擺

    // elbow
    // glColor3f(0.5, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, copper_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copper_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, copper_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, copper_shininess);
    glTranslatef(0.25, 0, 0.35);
    glutSolidSphere(elbow_radius, 200, 200);
    glTranslatef(-0.25, 0, -0.35);

    // arm
    // glColor3f(0.5, 0.0, 0.0); // brown
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
    walk_limbs_motion(upper_arm_length, -walk_upper_arm_degree); // 先往前擺 在往後擺

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
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree);              // 前臂單獨 永遠向前

    glScalef(0.3, fore_arm_length, 0.5);
    // glColor3f(0.0, 0.5, 0.0);
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
    walk_small_limbs_motion(fore_arm_length, -walk_fore_arm_degree);               // 前臂單獨 永遠向前
    glScalef(0.3, fore_arm_length, 0.5);
    // glColor3f(0.0, 0.5, 0.0);
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

void draw_environment()
{
    glEnable(GL_TEXTURE_2D);
    /*--------------------------draw floor----------------------*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[2]);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glNormal3f(0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floor_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floor_ambient);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(50.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glTexCoord2f(50.0, 50.0);
    glVertex3f(50.0, 0.0, 50.0);
    glTexCoord2f(0.0, 50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
    /*
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if ((i + j) % 2 == 0)
            {
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floor_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floor_ambient);
            }
            else
            {
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bill_obj_diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bill_obj_specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bill_obj_ambient);
            }
            glNormal3f(0.0, 1.0, 0.0);
            glBegin(GL_POLYGON);
            glVertex3f(i, 0.0, j);
            glVertex3f(i, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j + 1);
            glVertex3f(i + 1, 0.0, j);
            glEnd();
        }
    }
    */
    /*-------------------------draw axes-------------------------------------*/
    // original point
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[5]);

    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shininess);
    glutSolidSphere(0.7, 200, 200);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();

    // X-axis
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    gluCylinder(cylind, 0.3, 0.3, 12, 12, 3);
    glPopMatrix();
    /*
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, TextureID[2]);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glMatrixMode(GL_TEXTURE);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    */
    glPushMatrix();
    glTranslatef(4, 4, 4);
    glutWireSphere(0.7, 200, 200);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    /*------------------------draw obstacles----------------------------------*/
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
    draw_environment();
    // draw_billboard();

    fraction = (float)frame_count / frame_per_idle;
    x_in_idle_transition = walking * move_X_direction * fraction;
    z_in_idle_transition = walking * move_Z_direction * fraction;

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

    /*glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);*/
    /*glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);*/

    // texture star initial 在 draw_body
    draw_head();
    draw_body();
    draw_upper_arm();
    draw_fore_arm();
    draw_thigh();
    draw_calf();

    //draw_billboard();

    /*glDisable(GL_TEXTURE_2D);*/
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 512, 512);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /*----------------------------texture-------------------------------*/
    glEnable(GL_TEXTURE_2D);
    glGenTextures(6, TextureID);

    Create_Texture_Circle();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, TextureID[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, circle);

    Create_Texture_Star();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, TextureID[1]); /**/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, star);

    Create_Texture_Land();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /**/
    glBindTexture(GL_TEXTURE_2D, TextureID[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, land);

    Create_Texture_Waterwave();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /**/
    glBindTexture(GL_TEXTURE_2D, TextureID[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, waterwave);

    Create_Texture_Arrow();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /**/
    glBindTexture(GL_TEXTURE_2D, TextureID[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /**/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /**/
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, arrow);

    Create_Texture_Brick();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /**/
    glBindTexture(GL_TEXTURE_2D, TextureID[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick);

    /*----------------------------light-------------------------------*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    // example spot light0
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light0_cutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, light0_exponent);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light_attenuation);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // point light1
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light_attenuation);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    // directional light2
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    // glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);

    // spot light3
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, light3_cutoff);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, light3_exponent);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, light_attenuation);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
    // glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

    // global lighting status
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    /* local viewer */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/

    if (sphere == NULL)
    {
        sphere = gluNewQuadric();
        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluQuadricNormals(sphere, GLU_SMOOTH);
        gluQuadricTexture(sphere, GL_TRUE);
    }
    if (cylind == NULL)
    {
        cylind = gluNewQuadric();
        gluQuadricDrawStyle(cylind, GLU_FILL);
        gluQuadricNormals(cylind, GLU_SMOOTH);
        gluQuadricTexture(cylind, GL_TRUE);
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
    // int mod = glutGetModifiers();
    switch (key)
    {
    /*------change point light color/intensity (press alt+color)------ */
    case 'w':
    { // white
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.95;
            light1_diffuse[1] = 0.95;
            light1_diffuse[2] = 0.95;
            init();
        }
        break;
    }
    case 'r':
    { // red
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.95;
            light1_diffuse[1] = 0.05;
            light1_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'g':
    { // green
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT)
        {
            light1_diffuse[0] = 0.05;
            light1_diffuse[1] = 0.95;
            light1_diffuse[2] = 0.05;
            init();
        }
        break;
    }
    case 'b':
    { // blue
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT)
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
    case '9':
    { // white
        light2_diffuse[0] = 0.95;
        light2_diffuse[1] = 0.95;
        light2_diffuse[2] = 0.95;
        init();
        break;
    }
    case '8':
    { // red
        light2_diffuse[0] = 0.95;
        light2_diffuse[1] = 0.05;
        light2_diffuse[2] = 0.05;
        init();
        break;
    }
    case '7':
    { // green
        light2_diffuse[0] = 0.05;
        light2_diffuse[1] = 0.95;
        light2_diffuse[2] = 0.05;
        init();
        break;
    }
    case '6':
    { // blue
        light2_diffuse[0] = 0.05;
        light2_diffuse[1] = 0.05;
        light2_diffuse[2] = 0.95;
        init();
        break;
    }

    case 'F':
    {
        light2_direction[0] += 5.0;
        break;
    }
    case 'G':
    {
        light2_direction[0] -= 5.0;
        break;
    }
    case 'H':
    {
        light2_direction[1] += 5.0;
        break;
    }
    case 'J':
    {
        light2_direction[1] -= 5.0;
        break;
    }
    case 'K':
    {
        light2_direction[2] += 5.0;
        break;
    }
    case 'L':
    {
        light2_direction[2] -= 5.0;
        break;
    }
    default:
        break;
    }

    switch (key)
    {
    // move robot
    case 'a':
    {
        walking = 1;
        move_Z = -1;
        move_Z_direction = -1;
        move_X = 0;
        move_X_direction = 0;
        break;
    }
    case 'd':
    {
        walking = 1;
        move_Z = 1;
        move_Z_direction = 1;
        move_X = 0;
        move_X_direction = 0;
        break;
    }
    case 'w':
    {
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
        walking = 1;
        move_X = -1;
        move_X_direction = -1;
        move_Z = 0;
        move_Z_direction = 0;
        break;
    }
    case 's':
    {
        walking = 1;
        move_X = 1;
        move_X_direction = 1;
        move_Z = 0;
        move_Z_direction = 0;
        break;
    }
    case 'O':
    {
        robot_position[0] = 0;
        robot_position[1] = 0;
        robot_position[2] = 0;
        break;
    }

    // shift eye by xyz
    case 'Z':
    {
        eye_position[0] += 0.1;
        break;
    }
    case 'X':
    {
        eye_position[0] -= 0.1;
        break;
    }
    case 'C':
    {
        eye_position[1] += 0.1;
        break;
    }
    case 'V':
    {
        eye_position[1] -= 0.1;
        break;
    }
    case 'B':
    {
        eye_position[2] += 0.1;
        break;
    }
    case 'N':
    {
        eye_position[2] -= 0.1;
        break;
    }

    // shift eye uvw
    case 'z':
    { // up
        eye_position[0] -= 0.2 * v[0];
        eye_position[1] -= 0.2 * v[1];
        eye_position[2] -= 0.2 * v[2];
        break;
    }
    case 'x':
    { // down
        eye_position[0] += 0.2 * v[0];
        eye_position[1] += 0.2 * v[1];
        eye_position[2] += 0.2 * v[2];
        break;
    }
    case 'c':
    { // left
        eye_position[0] += 0.2 * u[0];
        eye_position[1] += 0.2 * u[1];
        eye_position[2] += 0.2 * u[2];
        break;
    }
    case 'v':
    { // right
        eye_position[0] -= 0.2 * u[0];
        eye_position[1] -= 0.2 * u[1];
        eye_position[2] -= 0.2 * u[2];
        break;
    }
    case 'b':
    { // foreward
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
        eye_position[0] -= 0.2 * w[0];
        eye_position[1] -= 0.2 * w[1];
        eye_position[2] -= 0.2 * w[2];
        break;
    }
    case 'n':
    { // backward
        eye_position[0] += 0.2 * w[0];
        eye_position[1] += 0.2 * w[1];
        eye_position[2] += 0.2 * w[2];
        break;
    }

    // rotate eye by uvw
    case 'f':
    { // pitch
        v[0] = v[0] * cv - w[0] * sv;
        v[1] = v[1] * cv - w[1] * sv;
        v[2] = v[2] * cv - w[2] * sv;

        w[0] = w[0] * cv + v[0] * sv;
        w[1] = w[1] * cv + v[1] * sv;
        w[2] = w[2] * cv + v[2] * sv;
        break;
    }
    case 'g':
    {
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT || mod == GLUT_ACTIVE_CTRL)
            break;
        v[0] = v[0] * cv + w[0] * sv;
        v[1] = v[1] * cv + w[1] * sv;
        v[2] = v[2] * cv + w[2] * sv;

        w[0] = w[0] * cv - v[0] * sv;
        w[1] = w[1] * cv - v[1] * sv;
        w[2] = w[2] * cv - v[2] * sv;
        break;
    }
    case 'h':
    { // head
        u[0] = u[0] * cv - w[0] * sv;
        u[1] = u[1] * cv - w[1] * sv;
        u[2] = u[2] * cv - w[2] * sv;

        w[0] = w[0] * cv + u[0] * sv;
        w[1] = w[1] * cv + u[1] * sv;
        w[2] = w[2] * cv + u[2] * sv;
        break;
    }
    case 'j':
    {
        u[0] = u[0] * cv + w[0] * sv;
        u[1] = u[1] * cv + w[1] * sv;
        u[2] = u[2] * cv + w[2] * sv;

        w[0] = w[0] * cv - u[0] * sv;
        w[1] = w[1] * cv - u[1] * sv;
        w[2] = w[2] * cv - u[2] * sv;
        break;
    }
    case 'k':
    { // roll
        u[0] = u[0] * cv - v[0] * sv;
        u[1] = u[1] * cv - v[1] * sv;
        u[2] = u[2] * cv - v[2] * sv;

        v[0] = v[0] * cv + u[0] * sv;
        v[1] = v[1] * cv + u[1] * sv;
        v[2] = v[2] * cv + u[2] * sv;
        break;
    }
    case 'l':
    {
        u[0] = u[0] * cv + v[0] * sv;
        u[1] = u[1] * cv + v[1] * sv;
        u[2] = u[2] * cv + v[2] * sv;

        v[0] = v[0] * cv - u[0] * sv;
        v[1] = v[1] * cv - u[1] * sv;
        v[2] = v[2] * cv - u[2] * sv;
        break;
    }

    // turn on off light
    case '!':
    { // on 0
        glEnable(GL_LIGHT0);
        break;
    }
    case '@':
    { // off 0
        glDisable(GL_LIGHT0);
        break;
    }
    case '#':
    { // on 1
        glEnable(GL_LIGHT1);
        break;
    }
    case '$':
    { // off 1
        glDisable(GL_LIGHT1);
        break;
    }
    case '%':
    { // on 2
        glEnable(GL_LIGHT2);
        break;
    }
    case '^':
    { // off 2
        glDisable(GL_LIGHT2);
        break;
    }
    case '&':
    { // on 3
        glEnable(GL_LIGHT3);
        break;
    }
    case '*':
    { // off 3
        glDisable(GL_LIGHT3);
        break;
    }

    // rotate light0 position
    case 'm':
    {
        light0_angle += 5.0;
        break;
    }

    // chang viewport
    case '0':
    {
        style = 0;
        break;
    }
    case '1':
    {
        style = 1;
        break;
    }
    case '2':
    {
        style = 2;
        break;
    }
    case '3':
    {
        style = 3;
        break;
    }
    case '4':
    {
        style = 4;
        break;
    }
    default:
        break;
    }
}

void special_key(int key, int x, int y)
{ /*
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
    case 4:;
        light1_fixed_in_eye();
        gluLookAt(eye_position[0], eye_position[1], eye_position[2],
                  eye_position[0] - w[0], eye_position[1] - w[1], eye_position[2] - w[2],
                  v[0], v[1], v[2]);
        light2_fixed_in_world();
        light3_attach_robot();
        rotate_light0_position();
        draw_billboard();
        break;
    case 1: /* X direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        light2_fixed_in_world();
        light3_attach_robot();
        rotate_light0_position();
        draw_billboard();
        break;
    case 2: /* Y direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
        light2_fixed_in_world();
        light3_attach_robot();
        rotate_light0_position();
        draw_billboard();
        break;
    case 3: /* Z direction parallel viewing */
        light1_fixed_in_eye();
        gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        light2_fixed_in_world();
        light3_attach_robot();
        rotate_light0_position();
        draw_billboard();
        break;
    }
}

void draw_eye_coordinate()
{
    glMatrixMode(GL_MODELVIEW);

    /*----Draw Eye position-----*/
    glPushMatrix();
    glTranslatef(eye_position[0], eye_position[1], eye_position[2]);
    // glColor3f(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_green_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_green_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_green_diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_green_shininess);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    /*-----Draw Xe----- */
    // glColor3f(1.0, 1.0, 0.0);
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
    // glColor3f(1.0, 0.0, 1.0);
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
    // glColor3f(0.0, 1.0, 1.0);
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
        make_projection(1);
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
    glutSwapBuffers();
    glFlush();
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
