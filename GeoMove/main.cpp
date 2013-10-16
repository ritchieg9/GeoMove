//incluir GPL3
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <SDL_image.h>
int desplazamiento = 10;
int largo = 640,ancho=480;

void dibujar(SDL_Surface *pantalla,SDL_Surface *figura,SDL_Rect *rectangulo)
{
    int dx = (rectangulo->x+rectangulo->w)-largo;
    int dy = (rectangulo->y+rectangulo->h)-ancho;

    if(dx>0)
    {
        SDL_Rect rx;
        rx.x=100-dx;
        rx.y=0;
        rx.h = 100;
        rx.w =dx;
        SDL_Rect rdestino;
        rdestino.x = 0;
        rdestino.y = rectangulo->y;
        SDL_BlitSurface(figura, &rx, pantalla,&rdestino);
    }

    if(dy>0)
    {
        SDL_Rect rx;
        rx.x=0;
        rx.y=100-dy;
        rx.h = dy;
        rx.w =100;
        SDL_Rect rdestino;
        rdestino.x = rectangulo->x;
        rdestino.y = 0;
        SDL_BlitSurface(figura, &rx, pantalla,&rdestino);
    }

    if(dy > 0 && dx > 0)
    {
        SDL_Rect rxy;
        rxy.x=100-dx;
        rxy.y=100-dy;
        rxy.h = dy;
        rxy.w = dx;
        SDL_Rect rdestino;
        rdestino.x = 0;
        rdestino.y = 0;
        SDL_BlitSurface(figura, &rxy, pantalla,&rdestino);

    }

    SDL_Rect rect_aux;
    rect_aux.x = rectangulo->x;
    rect_aux.y = rectangulo->y;
    rect_aux.h = rectangulo->h;
    rect_aux.w = rectangulo->w;
    SDL_BlitSurface(figura, 0, pantalla,&rect_aux);
}

void moverX(Sint16 *x,int desp)
{
    (*x) = ((*x+desp)+largo) %largo;
}
void moverY(Sint16 *y,int desp)
{
    (*y) = ((*y+desp)+ancho) %ancho;
}

int main ( int argc, char** argv )
{
    //Seleccion de la figura
    int seleccion = 1;
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    //Crea una ventana nueva
    SDL_Surface* screen = SDL_SetVideoMode(largo,ancho, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
    // carga de imagenes y cuadros para las imagenes
    SDL_Surface* cuadro = IMG_Load("rect.png");
    SDL_Surface* Scuadro = IMG_Load("selectedrect.png");
    if (!cuadro)
    {
        printf("Unable to load cuadro: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectCuadro;
    rectCuadro.h = 100;
    rectCuadro.w = 100;
    rectCuadro.x = 100;
    rectCuadro.y = 300;


    SDL_Surface* circulo = IMG_Load("circle.png");
    SDL_Surface* Scirculo = IMG_Load("selectedcircle.png");
    if (!cuadro)
    {
        printf("Unable to load circulo: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectCirculo;
    rectCirculo.x = 320-50 ;
    rectCirculo.y = 50;

    SDL_Surface* triangulo = IMG_Load("triangle.png");
    SDL_Surface* Striangulo = IMG_Load("selectedtriangle.png");
    if (!cuadro)
    {
        printf("Unable to load triangulo: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectTriangulo;
    rectTriangulo.x = 400 ;
    rectTriangulo.y = 300;
    SDL_Rect *RectTurno = &rectCuadro;
    SDL_Surface *SurfaceTurno = Scuadro;
    SDL_Surface *dos = circulo;
    SDL_Rect rdos =rectCirculo;
    SDL_Surface *tres = triangulo;
    SDL_Rect rtres = rectTriangulo;
    //Bucle principal
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // Verificacion de eventos
            switch (event.type)
            {
                //Sale si la vetana se cierra, de lo contrario no hara caso
            case SDL_QUIT:
                done = true;
                break;
                // Eventos del teclado
            case SDL_KEYDOWN:
                {
                    //Sale si la tecla scape es presionada
                    switch(event.key.keysym.sym)
                    {
                            case SDLK_ESCAPE:
                                done = true;
                            break;
                            case SDLK_UP:
                                moverY(&(RectTurno->y),-desplazamiento);
                            break;
                            case SDLK_DOWN:
                                moverY(&(RectTurno->y),+desplazamiento);
                            break;
                            case SDLK_LEFT:
                                moverX(&(RectTurno->x),-desplazamiento);
                            break;
                            case SDLK_RIGHT:
                                moverX(&(RectTurno->x),+desplazamiento);
                            break;
                            case SDLK_TAB:

                                seleccion = ((seleccion+1) % 3)+1;
                                switch(seleccion)
                                    {
                                        case 1:
                                            RectTurno = &rectCuadro;
                                            SurfaceTurno = Scuadro;
                                            dos = circulo;
                                            rdos = rectCirculo;
                                            tres = triangulo;
                                            rtres = rectTriangulo;
                                        break;
                                        case 2:
                                            RectTurno = &rectCirculo;
                                            SurfaceTurno = Scirculo;
                                            dos = triangulo;
                                            rdos = rectTriangulo;
                                            tres = cuadro;
                                            rtres = rectCuadro;
                                        break;
                                        case 3:
                                            RectTurno = &rectTriangulo;
                                            SurfaceTurno = Striangulo;
                                            dos = cuadro;
                                            rdos = rectCuadro;
                                            tres = circulo;
                                            rtres = rectCirculo;
                                        break;
                                    }
                                dibujar(screen,SurfaceTurno,RectTurno);
                                SDL_Flip(screen);
                            break;
                            default:
                            break;
                    }

                }//Fin delSDL_Keydown
            } // Fin el switch

        } //Fin del procesamiento de mensajes
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        dibujar(screen,tres,&rtres);
        dibujar(screen,dos,&rdos);
        RectTurno->w = RectTurno->h =100;//El blit surface corta el cuadro.

        dibujar(screen,SurfaceTurno,RectTurno);
        SDL_Flip(screen);
    } // end main loop
    return 0;
}
