#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

bool isWireframe = false;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
    
    // Better depth testing setup
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void drawTriangle1() {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  // Red
    glVertex3f(0.0, 0.3, 0.2);
    glVertex3f(0.3, 0.3, 0.0);
    glVertex3f(0.0, 0.0, 0.7);
    glEnd();
    glPopMatrix();
}

void drawQuad() {
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 1.0);  // Cyan
    glVertex3f(-0.5, 0.5, 0.3);
    glVertex3f(-0.5, -0.5, 0.3);
    glVertex3f(0.5, -0.5, 0.3);
    glVertex3f(0.5, 0.5, 0.3);
    glEnd();
    glPopMatrix();
}

void drawTriangle2() {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);  // Blue
    glVertex3f(0.0, 0.0, 0.3);
    glVertex3f(0.4, 0.0, 0.5);
    glVertex3f(-0.5, 0.5, -1.0);
    glEnd();
    glPopMatrix();
}

void drawCube() {
    float size = 0.5f;  // Smaller cube size
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);  // Move cube back a bit
    
    if (isWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    // Front face (red)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
    
    // Similar for other faces...
    // Back face (green)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);
    // ... (rest of the cube faces)
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Adjust camera position
    glTranslatef(0.0f, 0.0f, -3.0f);  // Move everything back
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);  // Rotate around X
    glRotatef(70.0f, 0.0f, 1.0f, 0.0f);  // Rotate around Y
    
    // Draw shapes
    drawTriangle1();
    drawQuad();
    drawTriangle2();
    drawCube();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)w / (float)h;
    if (isWireframe) {
        // Better perspective settings
        gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    } else {
        // Adjusted orthographic settings
        glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 0.1, 100.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        isWireframe = !isWireframe;
        reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        glutPostRedisplay();
    } else if (key == 27) {  // ESC key
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Shapes");
    
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}