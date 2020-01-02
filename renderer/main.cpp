#if defined(unix)        || defined(__unix)      || defined(__unix__) \
 || defined(linux)       || defined(__linux)     || defined(__linux__) \
 || defined(sun)         || defined(__sun) \
 || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
 || defined(__FreeBSD__) || defined (__DragonFly__) \
 || defined(sgi)         || defined(__sgi) \
 || defined(__MACOSX__)  || defined(__APPLE__) \
 || defined(__CYGWIN__)
#define OS 1
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
   || defined(WIN64)    || defined(_WIN64) || defined(__WIN64__)
#define OS 2
#else
#define OS 0
#endif

#if (OS == 1)
#include <X11/Xlib.h>
#elif (OS == 2)
#include <windowsx.h>
#endif

#include <stdio.h>
#include <stdlib.h> // prevents error for exit on line   18 when compiling with gcc
#include <limits>
#include "integrator.h"
#include "pinhole.h"
#include "sphere.h"
#include <armadillo>


// TODO: change raw pointer to shared_ptr
int main() {
    PinholeCam cam;
    Sphere *sphere = new Sphere(fvec3{0, 0, 5.f}, 1.f);
    Material *mat = new Material();
    mat->bsdf = new BSDF();
    mat->bsdf->add(new BXDF(BXDF::Type::DIFFUSE));
    Primitive *prim = new Primitive(0, mat, sphere);
    Scene *scene = new Scene();
    scene->add_primitive(prim);
    Integrator *integrator = new Integrator(scene, &cam);


    int width = 400;
    int height = 300;

    unsigned char *img = integrator->render(width, height);

    Display *d;
    
    Window w;
    XEvent e;
                    /* open connection with the server */
    d = XOpenDisplay(NULL);
    Visual* visual = DefaultVisual(d, 0);
    if(d == NULL) {
        printf("Cannot open display\n");
        exit(1);
    }
    int s = DefaultScreen(d);

                    /* create window */
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                     BlackPixel(d, s), WhitePixel(d, s));


    // Process Window Close Event through event handler so      XNextEvent does Not fail
    Atom delWindow = XInternAtom( d, "WM_DELETE_WINDOW", 0 );
    XSetWMProtocols(d , w, &delWindow, 1);

                    /* select kind of events we are interested in */
    XSelectInput(d, w, ExposureMask | KeyPressMask);

                    /* map (show) the window */
    XMapWindow(d, w);
                    /* event loop */
    XImage *ximage = XCreateImage(d, visual, 24, ZPixmap, 0, (char *)img, width, height, 32, 0);
    while(1) {
    XNextEvent(d, &e);
                    /* draw or redraw the window */
    if(e.type == Expose) {
      // XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
    }
                    /* exit on key press */
    if(e.type == KeyPress) {
       for (size_t i = 0; i < height; i++)
       {
         for (size_t j = 0; j < width; j++)
         {
           img[(i * width + j) * 4] = 0;
           img[(i * width + j) * 4 + 1] = 0;
           img[(i * width + j) * 4 + 2] = 255;
           img[(i * width + j) * 4 + 3] = 255;
         }
       }
    }

    // Handle Windows Close Event
    if(e.type == ClientMessage)
      break;
    XPutImage(d, w, DefaultGC(d, 0), ximage, 0, 0, 0, 0, width, height);
    }

                    /* destroy our window */
    XDestroyWindow(d, w);

                    /* close connection to server */
    XCloseDisplay(d);

    return 0;
}
