

#include <HAPI_lib.h>
#include <random>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

constexpr int kNumStars{1000};
const int width{ 1024 };
const int height{ 768 };
int kEyeDistance{ 100 };
struct Star{

	float x, y, z, speed;
	
};

void playTunes(std::string songName)
{
	int InstanceID = 1;
	HAPI_TSoundOptions options(1.0f, false);
	
	/*if (!HAPI.LoadSound("Audio/magic-mallet.wav")) {
		std::cout << "This shit didn't load out ong" << std::endl;
	}*/
	if (!HAPI.PlaySound("Audio/" + songName, options, InstanceID))
	{
		std::cout << "This shit didn't play out ong" << std::endl;

	}
}

void blitting() {

}

void clr_scrn_to_colour(int width,int height, BYTE* screen) {
	BYTE* copyPointer = &screen[(width * height * 4) / 2];
	for (int i = 0; i < (width*height*4)/2; i+=4) {
		screen[i] = 242;
		screen[(i) + 1]= 39;
		screen[(i) + 2] = 76;
	}
	memcpy(copyPointer,screen,(height*width*4)/2);

}

void plotLineHigh(int x0,int y0,int x1,int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	
	if (dx < 0) 
	{
		xi = -1;
		dx = -dx;
	}

	int D = (2 * dx) - dy;
	int x = x0;

	for (size_t i = y0; i < y1; i++)
	{
		//plot();
		if (D>0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else 
		{
			D = D + 2 * dx;
		}
	}
}

void plotLineLow(int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;

	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	int D = (2 * dy) - dx;
	int y = y0;

	for (size_t i = x0; i < x1; i++)
	{
		//plot();
		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
		{
			D = D + 2 * dy;
		}
	}
}
//void plot(BYTE* screen, int width, int height) {
//
//}

void plotLine(int x0,int x1, int y0,int y1) {
	if (abs(y1-y0)< abs(x1-x0))
	{
		if (x0 > x1) 
		{
			plotLineLow(x1,y1,x0,y0);
		}else
		{
			plotLineLow(x0,y0,x1,y1);
		}
	}
	else 
	{
		if (y0>y1)
		{
			plotLineHigh(x1,y1,x0,y0);
		}
		else 
		{
			plotLineHigh (x0, y0,x1,y1);
		}
	}
}

void StarShow() {
	Star stars[kNumStars];
	BYTE* screen{ HAPI.GetScreenPointer() };
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	
	



	for (int i = 0; i < kNumStars; i++)
	{
		stars[i].x = rand() % 1000;
		stars[i].y = rand() % 1000;
		stars[i].z = rand() % 100;
		stars[i].speed = (rand() %100)/100 + 0.05;
	}


	float cx{ width / 2.0f };
	float cy{ height / 2.0f };


	HAPI.SetShowFPS(true);


	while (HAPI.Update()) {

		//clr_scrn_to_colour(width, height, screen);
		memset(screen,0,width*height*4);

		if (keyData.scanCode[HK_DOWN])
		{
			playTunes(("magic-mallet.wav"));
			if (kEyeDistance < 2)
			{
				kEyeDistance = 2;
			}
			else
			{
				kEyeDistance--;
			}
		}

		if (keyData.scanCode[HK_UP])
		{
			playTunes("magic-mallet.wav");
			if (kEyeDistance > 100)
			{
				kEyeDistance = 100;
			}
			else
			{
				kEyeDistance++;
			}
		}


		for (int i = 0; i <kNumStars; i++)
		{


			stars[i].z=stars[i].z-stars[i].speed;
			if (stars[i].z <= 0) {

				stars[i].z = 100;
			}
		}

		for (int i = 0; i < kNumStars; i++)
		{
			float eyePlusPz = kEyeDistance + stars[i].z;

			float sX = ((kEyeDistance * (stars[i].x - cx)) / (eyePlusPz)) + cx;
			float sY = ((kEyeDistance * (stars[i].y - cy)) / (eyePlusPz)) + cy;

			int offset=((int)sX +(int)sY * width) * 4;

			if (sX< width && sX>0 && sY>0 && sY< height)
			{
				screen [offset] = 242;
				screen [offset + 1]=255;
				screen [offset + 2] =255;
				

			}

		}


	
	//HAPI.RenderText(50,50,HAPI_TColour(200,30,10),"HAPI is cool", 64);
	//HAPI.SetControllerRumble(0, 65000,65000);
	//memcpy(screen + offset, &fillColour,4);

	}

}
void HAPI_Main()
{
	
	int screenWidth = 1024;
	int sceenHeight = 768;
	
	//HAPI_TColour fillColour(242, 39, 76);
	if (!HAPI.Initialise(screenWidth, sceenHeight, "David Soremekun, HAPI HOUR "))
		return;
	StarShow();

	



}





