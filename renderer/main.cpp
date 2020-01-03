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
#include <windows.h>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h> // prevents error for exit on line   18 when compiling with gcc
#include <limits>
#include "integrator.h"
#include "pinhole.h"
#include "arealight.h"
#include "sphere.h"
#include "plane.h"
#include "lambertian.h"
#include <algorithm>
#include <armadillo>


#define WIDTH 100
#define HEIGHT 100

// TODO: change raw pointer to shared_ptr
unsigned char* render(int width, int height, bool alpha = false) {
    PinholeCam cam(fvec3{ 0, 0, -1.f });
    Sphere *sphere = new Sphere(fvec3{ 0, 0, -5.f }, 0.9f);
    Sphere *sphere3 = new Sphere(fvec3{ 1.5f, 1.f, -5.f }, 0.3f);
    Plane *plane = new Plane(fvec3{ 1.f, 0, 0 }, 2.f);
    Material *mat = new Material();
    mat->bsdf = new BSDF();
    mat->bsdf->add(new BXDF(BXDF::Type::DIFFUSE));
    Material *mat2 = new Material();
    mat2->bsdf = new BSDF();
    mat2->bsdf->add(new Lambertian(fvec3{ .25f, .25f, .75f }));
    Primitive *prim = new Primitive(0, mat, sphere);
    Primitive *prim3 = new Primitive(1, mat, sphere3);
    Primitive *prim4 = new Primitive(2, mat2, plane);

    Sphere *sphere2 = new Sphere(fvec3{ 2.f, 2.f, -5.f }, 1.f);
    
    Scene *scene = new Scene();
    scene->lights.push_back(new AreaLight(sphere2));
    scene->add_primitive(prim);
    scene->add_primitive(prim3);
    scene->add_primitive(prim4);
    Integrator *integrator = new Integrator(scene, &cam);

    unsigned char *img = integrator->render(width, height, alpha);
    return img;
}


#if (OS == 2)

static const WORD MAX_CONSOLE_LINES = 500;
void RedirectIOToConsole()
{
    //Create a console for this application
    AllocConsole();

    // Get STDOUT handle
    HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
    FILE *COutputHandle = _fdopen(SystemOutput, "w");

    // Get STDERR handle
    HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
    int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
    FILE *CErrorHandle = _fdopen(SystemError, "w");

    // Get STDIN handle
    HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
    int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
    FILE *CInputHandle = _fdopen(SystemInput, "r");

    //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    ios::sync_with_stdio(true);

    // Redirect the CRT standard input, output, and error handles to the console
    freopen_s(&CInputHandle, "CONIN$", "r", stdin);
    freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
    freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

    //Clear the error state for each of the C++ standard stream objects. We need to do this, as
    //attempts to access the standard streams before they refer to a valid target will cause the
    //iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
    //to always occur during startup regardless of whether anything has been read from or written to
    //the console or not.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd, BITMAPINFO *);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

    RedirectIOToConsole();

    MSG  msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Pixels";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Pixels",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, WIDTH, HEIGHT + 50, NULL, NULL, hInstance, NULL);


    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void DrawPixels(HWND hwnd, BITMAPINFO *bmi) {

    PAINTSTRUCT ps;
    RECT r;

    GetClientRect(hwnd, &r);

    if (r.bottom == 0) {

        return;
    }

    HDC hdc = BeginPaint(hwnd, &ps);

    auto image = render(WIDTH, HEIGHT);

    SetDIBitsToDevice(hdc, 0, 0, WIDTH, HEIGHT, 0, 0, 0, WIDTH, image, bmi, DIB_RGB_COLORS);

    EndPaint(hwnd, &ps);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biWidth = WIDTH;
    bmi.bmiHeader.biHeight = HEIGHT;

    switch (msg) {

    case WM_CREATE:
        break;

    case WM_PAINT:
        DrawPixels(hwnd, &bmi);
        break;

    case WM_TIMER:
        InvalidateRect(hwnd, NULL, FALSE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}



#elif (OS == 1)

void updown_img(unsigned char *img) {
    for (size_t i = 0; i < HEIGHT / 2; i++) {
        std::swap_ranges(&img[i * WIDTH * 4], &img[(i + 1) * WIDTH * 4], &img[(HEIGHT - 1 - i) * WIDTH * 4]);
    }
}

int main() {
    auto img = render(WIDTH, HEIGHT, true);
    updown_img(img);
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
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, WIDTH, HEIGHT, 1,
                     BlackPixel(d, s), WhitePixel(d, s));


    // Process Window Close Event through event handler so      XNextEvent does Not fail
    Atom delWindow = XInternAtom( d, "WM_DELETE_WINDOW", 0 );
    XSetWMProtocols(d , w, &delWindow, 1);

                    /* select kind of events we are interested in */
    XSelectInput(d, w, ExposureMask | KeyPressMask);

                    /* map (show) the window */
    XMapWindow(d, w);
                    /* event loop */
    XImage *ximage = XCreateImage(d, visual, 24, ZPixmap, 0, (char *)img, WIDTH, HEIGHT, 32, 0);
    while(1) {
        XNextEvent(d, &e);
                        /* draw or redraw the window */
        if(e.type == Expose) {
          // XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
        }
                        /* exit on key press */
        if(e.type == KeyPress) {
            
        }

        // Handle Windows Close Event
        if(e.type == ClientMessage)
          break;
        XPutImage(d, w, DefaultGC(d, 0), ximage, 0, 0, 0, 0, WIDTH, HEIGHT);
    }

                    /* destroy our window */
    XDestroyWindow(d, w);

                    /* close connection to server */
    XCloseDisplay(d);

    return 0;
}

#endif
