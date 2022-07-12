//implementacja bibliotek
#include <time.h>
#include <string>
#include<GL/glew.h>
#include<GL/glut.h>
#include <iostream>

//varying vec3 normal;
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "opengl32.lib")

GLint loc;
GLuint v, f, f2, p;
float lpos[4] = { 0,0.0,1,0.0 };

double rotacja = 0;
bool rotate;
int wybor;
int wybor2;

GLUquadric* quadricobj;
// Vertex shader:
const char* ShaderVertSource =
"varying vec3 lightDir, normal;\n"\
"void main() {\n"\
"lightDir = normalize(vec3(gl_LightSource[0].position));\n"\
"normal = gl_NormalMatrix * gl_Normal;\n"\
"gl_Position = ftransform();\n"\
"}";
// Fragment shader:
const char* ShaderFragSource =
"varying vec3 lightDir,normal;\n"\
"void main() {\n"\
"float intensity;\n"\
"vec4 color;\n"\
"vec3 n = normalize(normal);\n"\
"intensity = dot(lightDir,n);\n"\
"if (intensity > 0.95)\n"\
"color = vec4(1.0,0.5,0.5,1.0);\n"\
"else if (intensity > 0.85)\n"\
"color = vec4(1,0.47,0.5,1.0);\n"\
"else if (intensity > 0.75)\n"\
"color = vec4(1,0.45,0.5,1.0);\n"\
"else if (intensity > 0.65)\n"\
"color = vec4(1,0.43,0.5,1.0);\n"\
"else if (intensity > 0.55)\n"\
"color = vec4(1,0.42,0.49,1.0);\n"\
"else if (intensity > 0.45)\n"\
"color = vec4(1,0.41,0.49,1.0);\n"\
"else if (intensity > 0.35)\n"\
"color = vec4(1,0.4,0.48,1.0);\n"\
"else if (intensity > 0.25)\n"\
"color = vec4(1,0.39,0.46,1.0);\n"\
"else if (intensity > 0.15)\n"\
"color = vec4(1,0.37,0.45,1.0);\n"\
"else\n"\
"color = vec4(1,0.34,0.42,1.0);\n"\
"gl_FragColor = color;\n"\
"}";

void trojkat(double x, double y, double z, double promien)
{
    double i;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, z);
    for (i = 0; i <= 60; i += 1)
        glVertex3f(x, y + promien * cos(i), z + promien * sin(i));
    glColor3f(0, 0, 0);
    glEnd();
}

void gora_auta(double x, double y) {
    //góra samochodu
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        //glNormal3f(0, 0, 1);
        glVertex3f(x - 5.5, 2, 32);
        glVertex3f(x + 9.5, 2, 32);
        glVertex3f(x + 9.5, 32, 32);
        glVertex3f(x - 5.5, 32, 32);
    }glEnd();
    // pomiędzy górą a przednią szybą
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        //glNormal3f(0, 0, 1);
        glVertex3f(x - 5.5, 32, 32);
        glVertex3f(x + 9.5, 32, 32);
        glVertex3f(x + 9.5, 34, 30);
        glVertex3f(x - 5.5, 34, 30);
    }glEnd();
    // pomiędzy górą a tylnią szybą
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 9.5, -1, 29);
        glVertex3f(x + 9.5, 2, 32);
        glVertex3f(x - 5.5, 2, 32);
        glVertex3f(x - 5.5, -1, 29);
    }glEnd();
    // antena
    glBegin(GL_POLYGON); {
        glColor3f(0, 0, 0);
        glVertex3f(x + 1.5, 33, 30);
        glVertex3f(x + 2.5, 33, 30);
        glVertex3f(x + 2.5, 26, 41);
        glVertex3f(x + 1.5, 26, 41);
    }glEnd();
    // prawe gorne ramy
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 5, 30, 31);
        glVertex3f(x - 4, 30, 31);
        glVertex3f(x - 4, 26, 33);
        glVertex3f(x - 5, 26, 33);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 5, 2, 31);
        glVertex3f(x - 4, 2, 31);
        glVertex3f(x - 4, 6, 33);
        glVertex3f(x - 5, 6, 33);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 5, 6, 33);
        glVertex3f(x - 4, 6, 33);
        glVertex3f(x - 4, 26, 33);
        glVertex3f(x - 5, 26, 33);
    }glEnd();

    // lewe gorne ramy
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 9, 30, 31);
        glVertex3f(x + 8, 30, 31);
        glVertex3f(x + 8, 26, 33);
        glVertex3f(x + 9, 26, 33);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 9, 2, 31);
        glVertex3f(x + 8, 2, 31);
        glVertex3f(x + 8, 6, 33);
        glVertex3f(x + 9, 6, 33);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 9, 6, 33);
        glVertex3f(x + 8, 6, 33);
        glVertex3f(x + 8, 26, 33);
        glVertex3f(x + 9, 26, 33);
    }glEnd();
}

void przod_auta(double x, double y)
{
    //rama miedzy maska a szyba
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 15.5, 42, 22);
        glVertex3f(x - 11.5, 42, 22);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x + 16.5, 42, 20);
    }glEnd();
    //przednia maska
    glBegin(GL_POLYGON); {
        glNormal3f(0.0, 0.0, 0.1);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x + 16.5, 42, 20);
        glVertex3f(x + 15.5, 54, 17);
        glVertex3f(x - 11.5, 54, 17);
    }glEnd();
    //gora przedniego zderzaka
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 11.5, 54, 17);
        glVertex3f(x + 15.5, 54, 17);
        glVertex3f(x + 15.5, 55, 14);
        glVertex3f(x - 11.5, 55, 14);
    }glEnd();
    //dol przedniego zderzaka
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 11.5, 55, 14);
        glVertex3f(x + 15.5, 55, 14);
        glVertex3f(x + 15.5, 56, 9);
        glVertex3f(x - 11.5, 56, 9);
    }glEnd();
    //listwa przedniego zderzaka
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 11.5, 55, 9);
        glVertex3f(x + 15.5, 55, 9);
        glVertex3f(x + 15.5, 56, 8);
        glVertex3f(x - 11.5, 56, 8);
    }glEnd();
    //prawy przedni blotnik
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 15.5, 56, 9);
        glVertex3f(x + 15.5, 55, 14);
        glVertex3f(x + 15.5, 54, 17);
        glVertex3f(x + 16.5, 42, 20);
        glVertex3f(x + 15.5, 42, 9);
    }glEnd();
    //listwa prawego przedniego blotniak
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 15.5, 56, 8);
        glVertex3f(x + 15.5, 55, 10);
        glVertex3f(x + 15.5, 54, 10);
        glVertex3f(x + 16.5, 40, 10);
        glVertex3f(x + 15.5, 40, 8);
    }glEnd();
    //lewy przedni blotnik
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 11.5, 56, 9);
        glVertex3f(x - 11.5, 55, 14);
        glVertex3f(x - 11.5, 54, 17);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x - 11.5, 42, 9);
    }glEnd();
    //listwa lewego przedniego blotnika
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 11.5, 56, 8);
        glVertex3f(x - 11.5, 55, 10);
        glVertex3f(x - 11.5, 54, 10);
        glVertex3f(x - 12.5, 40, 10);
        glVertex3f(x - 11.5, 40, 8);
    }glEnd();
    //lewe przednie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(x - 5, 54.1, 17);
        glVertex3f(x - 10.5, 54.1, 17);
        glVertex3f(x - 10.5, 55.1, 14);
        glVertex3f(x - 5, 55.1, 14);
    }glEnd();
    //prawe przednie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(x + 9, 54.1, 17);
        glVertex3f(x + 14.5, 54.1, 17);
        glVertex3f(x + 14.5, 55.1, 14);
        glVertex3f(x + 9, 55.1, 14);
    }glEnd();
    //rejestracja przod
    glBegin(GL_QUADS); {
        glColor3f(0, 0.500, 0.500);
        glVertex3f(x - 2, 54.1, 17);
        glVertex3f(x + 6, 54.1, 17);
        glVertex3f(x + 6, 55.1, 14);
        glVertex3f(x - 2, 55.1, 14);
    }glEnd();
}

void tyl_auta(double x, double y) {
    //rama pod tylnia szyba
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 15.5, -7, 22);
        glVertex3f(x - 11.5, -7, 22);
        glVertex3f(x - 12.5, -7, 20);
        glVertex3f(x + 16.5, -7, 20);
    }glEnd();
    //rama nad tylnimi swiatlami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.5, -7, 20);
        glVertex3f(x + 16.5, -7, 20);
        glVertex3f(x + 16.5, -8, 17);
        glVertex3f(x - 12.5, -8, 17);
    }glEnd();

    //lewe tylnie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(0.650, 0.150, 0.150);
        glVertex3f(x - 7, -8, 17);
        glVertex3f(x - 12.5, -8, 17);
        glVertex3f(x - 12.5, -8.2, 13.2);
        glVertex3f(x - 7, -8.2, 13.2);
    }glEnd();

    //prawe tylnie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(0.650, 0.150, 0.150);
        glVertex3f(x + 11, -8, 17);
        glVertex3f(x + 16.5, -8, 17);
        glVertex3f(x + 16.5, -8.2, 13.2);
        glVertex3f(x + 11, -8.2, 13.2);
    }glEnd();

    //rejestracja tyl
    glBegin(GL_QUADS); {
        glColor3f(0, 0.500, 0.500);
        glVertex3f(x - 2, -8.04, 17);
        glVertex3f(x + 6, -8.04, 17);
        glVertex3f(x + 6, -8.24, 13.2);
        glVertex3f(x - 2, -8.24, 13.2);
    }glEnd();

    //odstepy miedzy rejestracja a swiatlami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 11, -8, 17);
        glVertex3f(x - 7, -8, 17);
        glVertex3f(x - 7, -8.2, 13.2);
        glVertex3f(x + 11, -8.2, 13.2);
    }glEnd();

    //tylni zderzak
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 16.5, -8.2, 13.2);
        glVertex3f(x - 12.5, -8.2, 13.2);
        glVertex3f(x - 12.5, -8.5, 9);
        glVertex3f(x + 17, -8.5, 9);
    }glEnd();
    //listwa pod zderzakiem
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 16.5, -8.2, 10);
        glVertex3f(x - 12.5, -8.2, 10);
        glVertex3f(x - 12.5, -8.5, 8);
        glVertex3f(x + 17, -8.5, 8);
    }glEnd();

}

void tyl_auta_2(double x, double y) {
    //rama pod tylnia szyba
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 15.5, -12, 22);
        glVertex3f(x - 11.5, -12, 22);
        glVertex3f(x - 12.5, -12, 22);
        glVertex3f(x + 16.5, -12, 22);
    }glEnd();
    //rama nad tylnimi swiatlami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.5, -15, 20);
        glVertex3f(x + 16.5, -15, 20);
        glVertex3f(x + 16.5, -15, 17);
        glVertex3f(x - 12.5, -15, 17);
    }glEnd();
    //lewe tylnie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(0.650, 0.150, 0.150);
        glVertex3f(x - 7, -15, 17);
        glVertex3f(x - 12.5, -15, 17);
        glVertex3f(x - 12.5, -15.2, 13.2);
        glVertex3f(x - 7, -15.2, 13.2);
    }glEnd();
    //prawe tylnie swiatlo
    glBegin(GL_POLYGON); {
        glColor3f(0.650, 0.150, 0.150);
        glVertex3f(x + 11, -15, 17);
        glVertex3f(x + 16.5, -15, 17);
        glVertex3f(x + 16.5, -15.2, 13.2);
        glVertex3f(x + 11, -15.2, 13.2);
    }glEnd();
    //rejestracja
    glBegin(GL_QUADS); {
        glColor3f(0, 0.500, 0.500);
        glVertex3f(x - 2, -15.04, 17);
        glVertex3f(x + 6, -15.04, 17);
        glVertex3f(x + 6, -15.24, 13.2);
        glVertex3f(x - 2, -15.24, 13.2);
    }glEnd();
    //odstepy miedzy rejestracja a swiatlami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 11, -15, 17);
        glVertex3f(x - 7, -15, 17);
        glVertex3f(x - 7, -15.2, 13.2);
        glVertex3f(x + 11, -15.2, 13.2);
    }glEnd();
    //zderzak tylni auta
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 16.5, -15.2, 13.2);
        glVertex3f(x - 12.5, -15.2, 13.2);
        glVertex3f(x - 12.5, -15.5, 9);
        glVertex3f(x + 17, -15.5, 9);
    }glEnd();
    //gora bagażnika 
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.53, -15.2, 20);
        glVertex3f(x + 16.53, -15.2, 20);
        glVertex3f(x + 16.53, 2, 20);
        glVertex3f(x - 12.53, 2, 20);
    }glEnd();
    //dół bagażnika
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.53, -15.8, 9);
        glVertex3f(x + 16.53, -15.8, 9);
        glVertex3f(x + 16.53, 0, 9);
        glVertex3f(x - 12.53, 0, 9);
    }glEnd();
    //lista pod bagażnikiem
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 17, -15.7, 10);
        glVertex3f(x - 13, -15.7, 10);
        glVertex3f(x - 13, -15.7, 8);
        glVertex3f(x + 17, -15.7, 8);
    }glEnd();
}

void tyl_hb(double x, double y) {
    //prawe przednie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 16.5, 42, 20);
        glVertex3f(x + 16.5, 12, 20);
        glVertex3f(x + 15.5, 12, 9);
        glVertex3f(x + 15.5, 42, 9);
    }glEnd();
    //prawe tylnie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 16.5, 12, 20);
        glVertex3f(x + 16.5, -7, 20);
        glVertex3f(x + 16.5, -8, 17);
        glVertex3f(x + 16.5, -8.2, 13.2);
        glVertex3f(x + 17, -8.5, 9);
        glVertex3f(x + 15.5, 12, 9);
    }glEnd();
    //prawa listwa dolna
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 15.5, 42, 10);
        glVertex3f(x + 15.5, -8.5, 10);
        glVertex3f(x + 16.5, -8.5, 8);
        glVertex3f(x + 16.5, 42, 8);
    }glEnd();
    //lewe przednie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        //glNormal3f(0, 0, -1);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x - 12.5, 12, 20);
        glVertex3f(x - 11.5, 12, 9);
        glVertex3f(x - 11.5, 42, 9);
    }glEnd();
    //lewe tylnie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        //glNormal3f(0, 0.5, -0.55);
        glVertex3f(x - 12.5, 12, 20);
        glVertex3f(x - 12.5, -7, 20);
        glVertex3f(x - 12.5, -8, 17);
        glVertex3f(x - 12.5, -8.2, 13.2);
        glVertex3f(x - 12.5, -8.5, 9);
        glVertex3f(x - 11.5, 12, 9);
    }glEnd();
    //lewa listwa dolna
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 11.5, 42, 10);
        glVertex3f(x - 11.5, -8.5, 10);
        glVertex3f(x - 11.5, -8.5, 8);
        glVertex3f(x - 11.5, 42, 8);
    }glEnd();
}

void tyl_sedan(double x, double y) {
    //prawe przednie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        //glNormal3f(0, 1, 0);
        glVertex3f(x + 16.5, 42, 20);
        glVertex3f(x + 16.5, 12, 20);
        glVertex3f(x + 15.5, 12, 9);
        glVertex3f(x + 15.5, 42, 9);
    }glEnd();
    //prawe tylnie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 16.5, 12, 20);
        glVertex3f(x + 16.5, -15, 20);
        glVertex3f(x + 16.5, -15.2, 17);
        glVertex3f(x + 16.5, -15.2, 13.2);
        glVertex3f(x + 16.5, -15.2, 9);
        glVertex3f(x + 15.5, 12, 9);
    }glEnd();
    //prawa listwa dolna
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x + 15.5, 42, 10);
        glVertex3f(x + 17, -15.5, 10);
        glVertex3f(x + 17, -15.5, 8);
        glVertex3f(x + 16.5, 42, 8);
    }glEnd();
    //lewe przednie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x - 12.5, 12, 20);
        glVertex3f(x - 11.5, 12, 9);
        glVertex3f(x - 11.5, 42, 9);
    }glEnd();
    //lewe tylnie drzwi
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 12.5, 12, 20);
        glVertex3f(x - 12.5, -15, 20);
        glVertex3f(x - 12.5, -15.2, 17);
        glVertex3f(x - 12.5, -15.2, 13.2);
        glVertex3f(x - 12.5, -15.2, 9);
        glVertex3f(x - 11.5, 12, 9);
    }glEnd();
    //lewa listwa dolna
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(x - 11.5, 42, 10);
        glVertex3f(x - 12.8, -15.5, 10);
        glVertex3f(x - 12.8, -15.5, 8);
        glVertex3f(x - 11.5, 42, 8);
    }glEnd();
}

void prawa_czesc_auta(double x, double y) {
    //przednia szyba rama prawa
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 13.5, 42, 22);
        glVertex3f(x + 9.5, 34, 30);
        glVertex3f(x + 9.5, 32, 32);
        glVertex3f(x + 10, 32, 30);
        glVertex3f(x + 15.5, 42, 22);
    }glEnd();
    //rama nad drzwiami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 9.5, 32, 32);
        glVertex3f(x + 9.5, 2, 32);
        glVertex3f(x + 10, 2, 30);
        glVertex3f(x + 10, 32, 30);
    }glEnd();
    //tylnia szyba rama prawa
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 9.5, 2, 32);
        glVertex3f(x + 9.5, -1, 29);
        glVertex3f(x + 12.5, -7, 22);
        glVertex3f(x + 15.5, -7, 22);
        glVertex3f(x + 10, 2, 30);
        glVertex3f(x + 9.5, 2, 32);
    }glEnd();
    //dolna rama pod prawymi szybami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 15.5, -7, 22);
        glVertex3f(x + 16.5, -7, 20);
        glVertex3f(x + 16.5, 42, 20);
        glVertex3f(x + 15.5, 42, 22);
    }glEnd();
    //przednie okno prawej strony
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 15.5, 42, 22);
        glVertex3f(x + 10, 32, 30);
        glVertex3f(x + 15.5, 32, 22);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 10, 32, 30);
        glVertex3f(x + 15.5, 32, 22);
        glVertex3f(x + 15.5, 20, 22);
        glVertex3f(x + 10, 19.5, 30);
    }glEnd();
    //środkowe okno prawej stronie
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 10, 18.5, 30);
        glVertex3f(x + 15.5, 18.5, 22);
        glVertex3f(x + 15.5, 3, 22);
        glVertex3f(x + 10, 3.5, 30);
    }glEnd();
    //tylne okno prawej strony
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 15.5, 2, 22);
        glVertex3f(x + 10, 2.9, 30);
        glVertex3f(x + 10, 2, 30);
        glVertex3f(x + 15.5, -7, 22);
    }glEnd();
    //przednia prawa rama 
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 10, 19.5, 30);
        glVertex3f(x + 10, 18.5, 30);
        glVertex3f(x + 15.5, 18.5, 22);
        glVertex3f(x + 15.5, 20, 22);
    }glEnd();

    //tylnia prawa rama
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 10, 2.9, 30);
        glVertex3f(x + 10, 3.5, 30);
        glVertex3f(x + 15.5, 3, 22);
        glVertex3f(x + 15.5, 2, 22);
    }glEnd();
}

void lewa_czesc_auta(double x, double y) {
    //przednia szyba rama lewa
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 9.5, 42, 22);
        glVertex3f(x - 5.5, 34, 30);
        glVertex3f(x - 5.5, 32, 32);
        glVertex3f(x - 6, 32, 30);
        glVertex3f(x - 11.5, 42, 22);
    }glEnd();
    //rama nad drzwiami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 5.5, 32, 32);
        glVertex3f(x - 5.5, 2, 32);
        glVertex3f(x - 6, 2, 30);
        glVertex3f(x - 6, 32, 30);
    }glEnd();
    // tylnia szyba rama lewa
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 5.5, 2, 32);
        glVertex3f(x - 5.5, -1, 29);
        glVertex3f(x - 8.5, -7, 22);
        glVertex3f(x - 11.5, -7, 22);
        glVertex3f(x - 6, 2, 30);
        glVertex3f(x - 5.5, 2, 32);
    }glEnd();
    //dolna rama pod lewymi szybami
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 11.5, -7, 22);
        glVertex3f(x - 12.5, -7, 20);
        glVertex3f(x - 12.5, 42, 20);
        glVertex3f(x - 11.5, 42, 22);
    }glEnd();
    //przednie okno lewej strony
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 11.5, 42, 22);
        glVertex3f(x - 6, 32, 30);
        glVertex3f(x - 11.5, 32, 22);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 6, 32, 30);
        glVertex3f(x - 11.5, 32, 22);
        glVertex3f(x - 11.5, 20, 22);
        glVertex3f(x - 6, 19.5, 30);
    }glEnd();

    //środkowe okno lewej strony
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 6, 18.5, 30);
        glVertex3f(x - 11.5, 18.5, 22);
        glVertex3f(x - 11.5, 3, 22);
        glVertex3f(x - 6, 3.5, 30);
    }glEnd();

    //tylne okno lewej strony
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 11.5, 2, 22);
        glVertex3f(x - 6, 2.9, 30);
        glVertex3f(x - 6, 2, 30);
        glVertex3f(x - 11.5, -7, 22);
    }glEnd();
    //przednia lewa rama
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 6, 19.5, 30);
        glVertex3f(x - 6, 18.5, 30);
        glVertex3f(x - 11.5, 18.5, 22);
        glVertex3f(x - 11.5, 20, 22);
    }glEnd();

    //tylnia lewa rama
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x - 6, 2.9, 30);
        glVertex3f(x - 6, 3.5, 30);
        glVertex3f(x - 11.5, 3, 22);
        glVertex3f(x - 11.5, 2, 22);
    }glEnd();
}

void szyby(double x, double y) {
    // przednia szyba
    glBegin(GL_QUADS); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 5.5, 34, 30);
        glVertex3f(x + 9.5, 34, 30);
        glVertex3f(x + 13.5, 42, 22);
        glVertex3f(x - 9.5, 42, 22);
    }glEnd();
    // tylnia szyba
    glBegin(GL_QUADS); {
        glColor3f(1, 1, 1);
        glVertex3f(x - 5.5, -1, 29);
        glVertex3f(x + 9.5, -1, 29);
        glVertex3f(x + 12.5, -7, 22);
        glVertex3f(x - 8.5, -7, 22);
    }glEnd();
}

void motor(double x, double y) {
    //Podstawa motoru
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 12, 20.8, 20);
        glVertex3f(x + 17, 20.8, 20);
        glVertex3f(x + 17, -5, 20);
        glVertex3f(x + 12, -5, 20);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 12, 20.8, 23);
        glVertex3f(x + 17, 20.8, 23);
        glVertex3f(x + 17, -5, 23);
        glVertex3f(x + 12, -5, 23);
    }glEnd();
    //Bok obudowy
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 12, 20, 23);
        glVertex3f(x + 12, -5, 23);
        glVertex3f(x + 12, -5, 20);
        glVertex3f(x + 12, 20, 20);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + 17, 20, 23);
        glVertex3f(x + 17, -5, 23);
        glVertex3f(x + 17, -5, 20);
        glVertex3f(x + 17, 20, 20);
    }glEnd();
    //Siedzenie
    glBegin(GL_QUADS); {
        glColor3f(0, 0, 0);
        glVertex3f(x + 12, 10.8, 25);
        glVertex3f(x + 16.5, 10.8, 25);
        glVertex3f(x + 16.5, -3, 25);
        glVertex3f(x + 12, -3, 25);
    }glEnd();
    glBegin(GL_QUADS); {
        glColor3f(0, 0, 0);
        glVertex3f(x + 12, 10.8, 23.1);
        glVertex3f(x + 16.5, 10.8, 23.1);
        glVertex3f(x + 16.5, -3, 23.1);
        glVertex3f(x + 12, -3, 23.1);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(0, 0, 0);
        glVertex3f(x + 12, 10.8, 25);
        glVertex3f(x + 12, -3, 25);
        glVertex3f(x + 12, -3, 23.1);
        glVertex3f(x + 12, 10.8, 23.1);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(0, 0, 0);
        glVertex3f(x + 16.5, 10.8, 23.1);
        glVertex3f(x + 16.5, -3, 23.1);
        glVertex3f(x + 16.5, -3, 25);
        glVertex3f(x + 16.5, 10.8, 25);
    }glEnd();
    //mocowania do kół przód
    glBegin(GL_POLYGON); {
        glColor3f(0.5, 0.6, 0.5);
        glVertex3f(x + 12, 30, 7);
        glVertex3f(x + 12, 12, 20);
        glVertex3f(x + 12, 20, 20);
        glVertex3f(x + 12, 20, 18);
        glVertex3f(x + 12, 30, 7);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(0.5, 0.6, 0.5);
        glVertex3f(x + 17, 30, 7);
        glVertex3f(x + 17, 12, 20);
        glVertex3f(x + 17, 20, 20);
        glVertex3f(x + 17, 20, 18);
        glVertex3f(x + 17, 30, 7);
    }glEnd();
    //mocowania do kół tył
    glBegin(GL_POLYGON); {
        glColor3f(0.5, 0.6, 0.5);
        glVertex3f(x + 12, -12, 7);
        glVertex3f(x + 12, -5, 20);
        glVertex3f(x + 12, -3, 20);
        glVertex3f(x + 12, -3, 18);
        glVertex3f(x + 12, -12, 7);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(0.5, 0.6, 0.5);
        glVertex3f(x + 17, -12, 7);
        glVertex3f(x + 17, -5, 20);
        glVertex3f(x + 17, -3, 20);
        glVertex3f(x + 17, -3, 18);
        glVertex3f(x + 17, -12, 7);
    }glEnd();
    // przednia szyba
    glBegin(GL_QUADS); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 11.5, 15, 33);
        glVertex3f(x + 17, 15, 33);
        glVertex3f(x + 17, 20, 23);
        glVertex3f(x + 11.5, 20, 23);
    }glEnd();
    // światło tylnie
    glBegin(GL_POLYGON); {
        glColor3f(0.650, 0.150, 0.150);
        glVertex3f(x + 13, -5, 23);
        glVertex3f(x + 15.7, -5, 23);
        glVertex3f(x + 15.7, -5.2, 21.2);
        glVertex3f(x + 13, -5.2, 21.2);
    }glEnd();
    // swiatlo tylnie
    glBegin(GL_POLYGON); {
        glColor3f(1, 1, 1);
        glVertex3f(x + 13, 20, 23);
        glVertex3f(x + 15.7, 20, 23);
        glVertex3f(x + 15.7, 20.2, 21.2);
        glVertex3f(x + 13, 20.2, 21.2);
    }glEnd();
}

void opona(double x, double y, double z, double promien, double w) {
    glPushMatrix();
    {
        glColor3f(0, 0, 0);
        glTranslatef(x, y, z);
        glRotatef(90, 0, 1, 0);

        gluCylinder(quadricobj, promien, promien, w, 15, 2);
    }
    glPopMatrix();

    trojkat(x + w, y, z, promien);
    trojkat(x, y, z, promien);
}

void podpora(double x, double y, double z, double radius, double w) {
    glPushMatrix();
    {
        glNormal3f(0.0, 0.0, 1.0);
        glTranslatef(x, y, z);
        glRotatef(90, 0, 1, 0);

        gluCylinder(quadricobj, radius, radius, w, 15, 2);
    }
    glPopMatrix();

    trojkat(x + w, y, z, radius);
    trojkat(x, y, z, radius);
}

void ziemia() {
    //prawa łąka
    glBegin(GL_POLYGON); {
        glColor3f(0, 1, 0);
        glVertex3f(-50, -1000, 1);
        glVertex3f(-5, 1000, 1);

        glColor3f(0.3, 0.6, 0.3);
        glVertex3f(-800, 1000, 1);
        glVertex3f(-800, -1000, 1);
    }glEnd();
    //lewa łąka
    glBegin(GL_POLYGON); {
        glColor3f(0, 1, 0);
        glVertex3f(100, -1000, 1);
        glVertex3f(80, 1000, 1);
        glColor3f(0.3, 0.6, 0.3);
        glVertex3f(1000, 1000, 1);
        glVertex3f(1000, -1000, 1);
    }glEnd();
}

void droga() {
    //prawa krawedz jezdni
    glBegin(GL_POLYGON); {
        glColor3f(0, 0, 0);
        glVertex3f(-50, -1000, 1.15);
        glVertex3f(-50, 1000, 1.15);
        glVertex3f(-40, 1000, 1.15);
        glVertex3f(-40, -1000, 1.15);
    }glEnd();
    //lewa krawedz jezdni
    glBegin(GL_POLYGON); {
        glColor3f(0, 0, 0);
        glVertex3f(100, -1000, 1.15);
        glVertex3f(100, 1000, 1.15);
        glVertex3f(90, 1000, 1.15);
        glVertex3f(90, -1000, 1.15);
    }glEnd();
    //główna droga
    glBegin(GL_POLYGON); {
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(90.5, -1000, 1.1);
        glVertex3f(90.5, 1000, 1.1);
        glVertex3f(-40.5, 1000, 1.1);
        glVertex3f(-40.5, -1000, 1.1);
    }glEnd();
}

void niebo() {
    //Niebo
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 0.5, 0.3);
        glVertex3f(-1000, 1000, -10);
        glVertex3f(1000, 1000, -10);

        glColor3f(1.0, 0.5, 0.5);
        glVertex3f(1000, 1000, 5000);
        glVertex3f(-1000, 1000, 5000);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 0.5, 0.3);
        glVertex3f(-1000, -1000, -10);
        glVertex3f(1000, -1000, -10);

        glColor3f(1.0, 0.5, 0.5);
        glVertex3f(1000, -1000, 500);
        glVertex3f(-1000, -1000, 500);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 0.5, 0.3);
        glVertex3f(1000, 1000, -10);
        glVertex3f(1000, -1000, -10);

        glColor3f(1.0, 0.5, 0.5);
        glVertex3f(1000, -1000, 500);
        glVertex3f(1000, 1000, 500);
    }glEnd();
    glBegin(GL_POLYGON); {
        glColor3f(1.0, 0.5, 0.3);
        glVertex3f(-800, 1000, -10);
        glVertex3f(-800, -1000, -10);

        glColor3f(1.0, 0.5, 0.5);
        glVertex3f(-800, -1000, 500);
        glVertex3f(-800, 1000, 500);
    }glEnd();
}

void podpory(double x, double y) {
    podpora(x + 105.5, -34, 8, 10, 10);
    podpora(x + 105.5, -14, 8, 10, 10);
    podpora(x + 105.5, 6, 8, 10, 10);
    podpora(x + 105.5, 26, 8, 10, 10);
    podpora(x + 105.5, 46, 8, 10, 10);
    podpora(x + 105.5, 66, 8, 10, 10);
    podpora(x + 105.5, 86, 8, 10, 10);
    podpora(x + 105.5, 106, 8, 10, 10);
}

void pojazd(double x, double y) {
    if (wybor == 1) {
        opona(x + 12.5, 6, 8, 5, 4);
        opona(x - 12.5, 2, 8, 5, 4);

        opona(x + 12.5, 36, 8, 5, 4);
        opona(x - 12.5, 36, 8, 5, 4);

        gora_auta(x, y);
        przod_auta(x, y);
        tyl_hb(x, y);
        tyl_auta(x, y);
        prawa_czesc_auta(x, y);
        lewa_czesc_auta(x, y);
        szyby(x, y);
    }
    else if (wybor == 2) {
        opona(x + 12.5, 6, 7, 5.5, 4);
        opona(x - 12.5, 2, 7, 5.5, 4);

        opona(x + 12.5, 36, 7, 5.5, 4);
        opona(x - 12.5, 36, 7, 5.5, 4);

        gora_auta(x, y);
        przod_auta(x, y);
        tyl_sedan(x, y);
        tyl_auta_2(x, y);
        prawa_czesc_auta(x, y);
        lewa_czesc_auta(x, y);
        szyby(x, y);
    }
    else if (wybor == 3) {
        opona(x + 12.5, -10, 7, 5.5, 4);
        opona(x + 12.5, 30, 7, 5.5, 4);

        motor(x, y);
    }

}
void setShaders() {

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v, 1, &ShaderVertSource, NULL);
    glShaderSource(f, 1, &ShaderFragSource, NULL);

    glCompileShader(v);
    glCompileShader(f);

    p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);

    glLinkProgram(p);

    glUseProgram(p);
    loc = glGetUniformLocation(p, "time");
}
void kamera() {
    //obracanie kamery
    if (rotate) {
        rotacja += 0.0007;
    }
    glutPostRedisplay();
}
void display() {
    //funkcja odpowiedzialna za wyswietlanie poszczegolnych elementow
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(200 * cos(rotacja), 200 * sin(rotacja), 75, 0, 0, 0, 0, 0, 1);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    pojazd(7.5, 0);
    glUseProgram(p);
    podpory(0, 0);
    glUseProgram(0);
    niebo();
    droga();
    ziemia();


    glutSwapBuffers();
}
int main(int argc, char** argv) {

    clock_t t1, t2;
    std::cout << "Wybierz samochod:" << std::endl;
    std::cout << "1 - Hatchback" << std::endl;
    std::cout << "2 - Sedan" << std::endl;
    std::cout << "3 - Motor" << std::endl;
    std::cin >> wybor;
    if (wybor > 3) {
        std::cout << "Wprowadzono zla wartosc" << std::endl;
        return 0;
    }
    t1 = clock();
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Samochód");

    rotate = true;

    glClearColor(1, 1, 1, 0);

    quadricobj = gluNewQuadric();
    gluQuadricNormals(quadricobj, GLU_SMOOTH);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(70, 1, 0.1, 10000.0);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    setShaders();
    glutDisplayFunc(display);
    glutIdleFunc(kamera);
    t2 = clock();
    float diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
    std::cout << "Czas uruchamiania: " << diff << std::endl;


    glutMainLoop();

    gluDeleteQuadric(quadricobj);

    return 0;
}