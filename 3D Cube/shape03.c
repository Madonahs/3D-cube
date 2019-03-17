/*
 * shape03.c
 *
 *  Created on: April 1, 2018
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

void drawTriangle(void){

    static int angle;
    static float pos = 0.0;
    XGetWindowAttributes(dpy,win, &winattr);
    glViewport(0,0,winattr.width,winattr.height);

    glClearColor(0.7f,0.7f,0.7f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f,0.9f,1.0f);

    glPushMatrix();

    glScalef(pos,pos,0.0);

       glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,-0.2f,0.5f);
        glVertex3f(-0.5f,0.3f,0.5f);
        glVertex3f(0.5f,0.6f,0.5f);
glEnd();

glPopMatrix();


 glXSwapBuffers(dpy,win);
        usleep(5000);
        angle += 1;

        if(angle == 360)
           angle = 0;

   pos +=0.001;
         if(pos >= 1.0)
            pos = 0.0;
}
