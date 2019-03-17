/*
 * shape01.c
 *
 *  Created on: Mar 17, 2019
 *      Author: madona
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>



Display *dpy;
XWindowAttributes winattr;
Window win;


void DrawCube(void){

float  vertsCoords[] = {
         0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
};

GLubyte indices [] = {
        0,1,2,3, //front
        5,0,3,4, //right
        5,6,7,4, //back
        5,6,1,0, //upper
        1,6,7,2, //left
        7,4,3,2, //bottom


};
GLubyte colors[]={
        255,0,0,
        0,255,0,
        0,0,255,
        255,255,0,
        0,255,255,
        255,0,255,
        255,255,255,
        0,0,0,


};


static int angle = 0;
        XGetWindowAttributes(dpy,win, &winattr);
        glViewport(0,0,winattr.width,winattr.height);

        glClearColor(0.7f,0.7f,0.7f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(0.0f,0.9f,1.0f);

        glPushMatrix();
        glRotatef(angle,0.5,1.0,0.0);
#if 0

        glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,-0.2f,0.5f);
        glVertex3f(-0.5f,0.3f,0.5f);
        glVertex3f(0.5f,0.6f,0.5f);
glEnd();

#endif

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3,GL_UNSIGNED_BYTE,0,colors);
        glVertexPointer(3,GL_FLOAT,0,vertsCoords);

        glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indices);

        glPopMatrix();
        glXSwapBuffers(dpy,win);
        usleep(5000);
        angle += 1;

        }
        // Main
int main(int argc, char *agrv[])
{
    int screen;
    Window root_win;
    XEvent event;

    unsigned int depth;
    XSetWindowAttributes attrs;

    GLint att [] = {GLX_RGBA, GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,None};

    XVisualInfo *visual;
    GLXContext glc;

    dpy = XOpenDisplay(null);

    if ((dpy = XOpenDisplay(NULL)) == NULL) {
        fprintf(stderr,"Can't Open Display\n");
        exit(1);
    }

    screen = DefaultScreen(dpy);
    depth = DefaultDepth(dpy,screen);
    root_win = RootWindow(dpy,screen);

    visual = glXChooseVisual(dpy,screen,att);

    attrs.border_pixel = BlackPixel(dpy,screen);
    attrs.background_pixel = WhitePixel(dpy,screen);
    attrs.override_redirect = True;
    attrs.colormap = XCreateColormap(dpy,root_win,visual->visual,AllocNone);
    attrs.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root_win, 200, 200, 600, 500, 0,
                        visual->depth, InputOutput,
                        visual->visual,
                        CWBackPixel|CWColormap|CWBorderPixel|CWEventMask,
                        &attrs);

    XMapWindow(dpy,win);
}
