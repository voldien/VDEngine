#include <Misc/VDMath.h>
#include <cmath>


const float VDMath::pi = 3.14159265f;
const float VDMath::pi2 = 6.2831853f;
const float VDMath::e = 2.7182818284590452353602874713527f;
const float VDMath::infinity = INFINITY;


void VDMath::guassian1Df(float* guassian, int width, double theta){
	for(int x = 0; x < width; x++){
		guassian[x] =  (1.0f / ( theta * sqrt(2.0 * VDMath::pi))) * powf(VDMath::e, -0.5 * powf( x - (float)width/ 2.0f , 2.0f) );
	}
}

void VDMath::guassian2Df(float* guassian, int height, float theta){
	int x;
	int y;
	for(int x = 0; x < height; x++){
		for(int y = 0; y < height; y++){
			guassian[x] =  (1.0 / ( theta * sqrt(2.0))) * powf(VDMath::e, -0.5 * powf( x - height/ 2 , 2.0) );
		}
	}

}
