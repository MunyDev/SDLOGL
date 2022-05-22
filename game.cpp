#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <ostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_render.h>
#include <SDL2\SDL_opengles2.h>


#include <EGL/egl.h>

#include <emscripten.h>
extern "C" {    
   #include <emscripten/html5.h> // emscripten module
}
#include <emscripten/fetch.h>
using namespace std;
SDL_Window *win;
SDL_Renderer *render;
SDL_GLContext sdlgl;
bool loadShaderCompleted[] = {false, false};

int shcount = 0;//Involve Fetch Batching 
void shaderSuccess(emscripten_fetch_t *fetch){
    if (fetch->readyState == 4){
        loadShaderCompleted[shcount] = true;
        shcount++;
        emscripten_fetch_close(fetch);
        
    }
    
    return;
}

void loadShaders(){
// emscripten_fetch_attr_t attr;
    
//     emscripten_fetch_attr_init(&attr);
//     strcpy(attr.requestMethod, "GET");
//     attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
//     attr.onsuccess = shaderSuccess;
    
//     emscripten_fetch(&attr, "asset/basic.vs");
//     emscripten_fetch(&attr, "asset/basic.fs");
    std::ifstream vStream;
    std::ifstream fStream;
    vStream.exceptions(std::ifstream::badbit|std::ifstream::failbit);
    fStream.exceptions(ifstream::badbit | std::ifstream::failbit);

    string vStrSource;
    string fStrSource;
    const char* glvSource;
    const char* glfSource;
    try {

        vStream.open("assets/basic.vs");
        stringstream ss;
        ss << vStream.rdbuf();
        vStrSource = ss.str();
        stringstream ssf;
        fStream.open("assets/basic.fs");
        ssf << fStream.rdbuf();
        fStrSource = ssf.str();
        vStream.close();
        fStream.close();
        
    } catch (std::ifstream::failure e){
        std::cerr << e.what() << std::endl;
        return;
    }

}
void onShaderLoadingFinished(){
    
}

void glLoop(void){
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(win);
    
}
int mouseclick(int eventType, const EmscriptenMouseEvent *mouseEvent, void * userData){
    emscripten_request_pointerlock("#canvas", 0);
    
    return true;
}
int mousemove(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData){
    std::cout << mouseEvent->movementY << ", " << mouseEvent->movementY << std::endl;
    
    return true;
}
int main(int argc, char const *argv[])
{   
    
    int err = SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL|SDL_RENDERER_PRESENTVSYNC, &win, &render);

    sdlgl = SDL_GL_CreateContext(win);
    
    emscripten_set_mousemove_callback("#canvas", NULL, false, mousemove);
    emscripten_set_click_callback("#canvas", NULL, false, mouseclick);
    emscripten_set_main_loop(glLoop, 60, true);
    
    return 0;
}
