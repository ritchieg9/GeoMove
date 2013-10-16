
// Copyright 2013 Isaac Farías.
// Copyright 2013 Ricardo Valtierra.
// Copyright 2013 Luis Martínez.

/*
                    GNU LESSER GENERAL PUBLIC LICENSE
                       Version 2.1, February 1999

 Copyright (C) 1991, 1999 Free Software Foundation, Inc.
 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

[This is the first released version of the Lesser GPL.  It also counts
 as the successor of the GNU Library Public License, version 2, hence
 the version number 2.1.]

                            Preamble
                            

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
Licenses are intended to guarantee your freedom to share and change
free software--to make sure the software is free for all its users.

  This license, the Lesser General Public License, applies to some
specially designated software packages--typically libraries--of the
Free Software Foundation and other authors who decide to use it.  You
can use it too, but we suggest you first think carefully about whether
this license or the ordinary General Public License is the better
strategy to use in any particular case, based on the explanations below.

  When we speak of free software, we are referring to freedom of use,
not price.  Our General Public Licenses are designed to make sure that
you have the freedom to distribute copies of free software (and charge
for this service if you wish); that you receive source code or can get
it if you want it; that you can change the software and use pieces of
it in new free programs; and that you are informed that you can do
these things.

  To protect your rights, we need to make restrictions that forbid
distributors to deny you these rights or to ask you to surrender these
rights.  These restrictions translate to certain responsibilities for
you if you distribute copies of the library or if you modify it.

  For example, if you distribute copies of the library, whether gratis
or for a fee, you must give the recipients all the rights that we gave
you.  You must make sure that they, too, receive or can get the source
code.  If you link other code with the library, you must provide
complete object files to the recipients, so that they can relink them
with the library after making changes to the library and recompiling
it.  And you must show them these terms so they know their rights.

  We protect your rights with a two-step method: (1) we copyright the
library, and (2) we offer you this license, which gives you legal
permission to copy, distribute and/or modify the library.

  To protect each distributor, we want to make it very clear that
there is no warranty for the free library.  Also, if the library is
modified by someone else and passed on, the recipients should know
that what they have is not the original version, so that the original
author's reputation will not be affected by problems that might be
introduced by others.

  Finally, software patents pose a constant threat to the existence of
any free program.  We wish to make sure that a company cannot
effectively restrict the users of a free program by obtaining a
restrictive license from a patent holder.  Therefore, we insist that
any patent license obtained for a version of the library must be
consistent with the full freedom of use specified in this license.

  Most GNU software, including some libraries, is covered by the
ordinary GNU General Public License.  This license, the GNU Lesser
General Public License, applies to certain designated libraries, and
is quite different from the ordinary General Public License.  We use
this license for certain libraries in order to permit linking those
libraries into non-free programs.

  When a program is linked with a library, whether statically or using
a shared library, the combination of the two is legally speaking a
combined work, a derivative of the original library.  The ordinary
General Public License therefore permits such linking only if the
entire combination fits its criteria of freedom.  The Lesser General
Public License permits more lax criteria for linking other code with
the library.

  We call this license the "Lesser" General Public License because it
does Less to protect the user's freedom than the ordinary General
Public License.  It also provides other free software developers Less
of an advantage over competing non-free programs.  These disadvantages
are the reason we use the ordinary General Public License for many
libraries.  However, the Lesser license provides advantages in certain
special circumstances.

  For example, on rare occasions, there may be a special need to
encourage the widest possible use of a certain library, so that it becomes
a de-facto standard.  To achieve this, non-free programs must be
allowed to use the library.  A more frequent case is that a free
library does the same job as widely used non-free libraries.  In this
case, there is little to gain by limiting the free library to free
software only, so we use the Lesser General Public License.

  In other cases, permission to use a particular library in non-free
programs enables a greater number of people to use a large body of
free software.  For example, permission to use the GNU C Library in
non-free programs enables many more people to use the whole GNU
operating system, as well as its variant, the GNU/Linux operating
system.

  Although the Lesser General Public License is Less protective of the
users' freedom, it does ensure that the user of a program that is
linked with the Library has the freedom and the wherewithal to run
that program using a modified version of the Library.

  The precise terms and conditions for copying, distribution and
modification follow.  Pay close attention to the difference between a
"work based on the library" and a "work that uses the library".  The
former contains code derived from the library, whereas the latter must
be combined with the library in order to run.

*/

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
