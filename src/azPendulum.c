// Includes
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

// Defines
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define G 9.8
#define PI 3.14159265358979323846
#define OMEGA_0 0
#define THETA_0 PI/4
#define L 200
#define STEP 0.016 //En segundos
#define UNITS_PER_METER 100 //Cuantas unidades corresponden a un metro

void drawCircle(SDL_Renderer *renderer, int x0, int y0, int r)
{
	int x = r -1;
	int y = 0;
	int dx = 1, dy = 1;
	int err = dx - 2*r;

	while (x >= y)
	{
		SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
    	SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
     	SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
    	SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
	    SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
     	SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
    	SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
	    SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);

		if (err <= 0)
		{
			++y;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			--x;
			dx += 2;
			err += dx-2*r;
		}
	}
}

void fillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);


        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void updatePendulum(double *x, double *y, double *theta, double *omega)
{
	//Actualizamos la posición del pendulo acorde a las EDOs
	//OMEGA_I+1 = OMEGA_I -h G/l sin (THETA_I)
	//THETA_I+1 = THETA_I + h * OMEGA_I
	*omega = *omega -(STEP * G * sin(*theta)) / (L/UNITS_PER_METER);
	*theta = *theta + STEP * *omega;

	//Ahora calculamos los nuevos valores de x e y;
	*x = 400 + L*(sin(*theta));
	*y = 300 + L*(cos(*theta));
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool quit = false;
    SDL_Event event;

	double theta = THETA_0;
	double omega = OMEGA_0;

	//Pendulum Vars
	double x = WINDOW_WIDTH/2 + L*sin(theta), y=WINDOW_HEIGHT/2 + L*cos(theta);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow(
        "Péndulo con SDL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    double newTime = SDL_GetTicks(), oldTime;

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
			else if (event.type = SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
                	// Handle up arrow key
                		y -= 5;
                		break;
            		case SDLK_DOWN:
                		// Handle down arrow key
                		y += 5;
                		break;
            		case SDLK_LEFT:
                		// Handle left arrow key
                		x -= 5;
                		break;
            		case SDLK_RIGHT:
                		// Handle right arrow key
                		x += 5;
                		break;
				}
			}
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 252, 250, 238, 255);  // Black background
        SDL_RenderClear(renderer);

		//Referencia de ángulo inicial
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + L);

		//Cuerda
		SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
		SDL_RenderDrawLine(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, x, y);

		updatePendulum(&x, &y, &theta, &omega);

		SDL_SetRenderDrawColor(renderer, 80, 118, 135, 255);
		//Pivot
		drawCircle(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 25);
		fillCircle(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 25);

		//Círculo para ver si el péndulo cumple
		SDL_SetRenderDrawColor(renderer, 184, 0, 31, 255);
		drawCircle(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, L);

		SDL_SetRenderDrawColor(renderer, 56, 75, 112, 255);
		//Pendulum
		drawCircle(renderer, x, y, 35);
		fillCircle(renderer, x, y, 35);

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to reduce CPU usage
        SDL_Delay(16);  // ~60 FPS
		
		//Debug
		//printf("r teorica: %d. r real: %.3f\n", L, sqrt(pow(x- 400, 2) + pow(y - 300, 2)));

        //Cálculo de FPS
        oldTime = newTime;
        newTime = SDL_GetTicks();

        printf("FPS: %.3f\n", 1000/(newTime-oldTime));
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
