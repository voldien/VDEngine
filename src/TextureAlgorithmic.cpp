#include <GL/glew.h>
#include <Rendering/VDColor32.h>
#include <SDL2/SDL_stdinc.h>
#include <VDSimpleType.h>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <Utility/VDTextureAlgorithmic.h>



int VDIntGenRandomTexture(unsigned char** pixelResult, unsigned int Width,
		unsigned int Height, unsigned int TextureFormat) {

	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureFormat);

	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, TextureFormat)){
		return SDL_FALSE;
	}


	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 1:
				pixelResult[0][y * Height + x] = rand() % 255;
				break;
			case 3:
				pixelResult[0][y * Height * 3 + x * 3] = rand() % 255;
				pixelResult[0][y * Height * 3 + x * 3 + 1] = rand() % 255;
				pixelResult[0][y * Height * 3 + x * 3 + 2] = rand() % 255;
				break;
			case 4:
				pixelResult[0][y * Height * 4 + x * 4] = rand() % 255;
				pixelResult[0][y * Height * 4 + x * 4 + 1] = rand() % 255;
				pixelResult[0][y * Height * 4 + x * 4 + 2] = rand() % 255;
				pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				break;
			default:
				break;
			}
			continue;
		}
		srand(time(NULL) * time(NULL) * y / x);
		continue;
	}
	return SDL_TRUE;
}

int VDIntGenColorTexture(unsigned char** pixelResult, unsigned int Width,
		unsigned int Height, unsigned int TextureFormat,
		unsigned char* colors) {
	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, TextureFormat))
		return SDL_FALSE;

	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureFormat);
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 1:
				pixelResult[0][y * Height + x] = colors[0];
				break;
			case 3:
				pixelResult[0][y * Height * 3 + x * 3] = colors[0];
				pixelResult[0][y * Height * 3 + x * 3 + 1] = colors[1];
				pixelResult[0][y * Height * 3 + x * 3 + 2] = colors[2];
				break;
			case 4:
				pixelResult[0][y * Height * 4 + x * 4] = colors[0];
				pixelResult[0][y * Height * 4 + x * 4 + 1] = colors[1];
				pixelResult[0][y * Height * 4 + x * 4 + 2] = colors[2];
				pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				break;
			default:
				break;
			}
		}
	}
	return SDL_TRUE;
}
int VDIntGenLinearTexture(unsigned char** pixelResult, unsigned int Width,
		unsigned int Height, unsigned int TextureType, unsigned char * colours,
		unsigned int from, unsigned int to, int vertical) {
	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, TextureType))
		return SDL_FALSE;
	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureType);
	float colorProcent = 0.0f;
	for (y = 0; y < Height; y++) {
		unsigned int linearColor = (Height - y);
		for (x = 0; x < Width; x++) {
			if (vertical == 0)
				colorProcent = ((float) y / (float) Height);

			unsigned int colorLerp =
					(unsigned char) (((float) to - (float) from)
							* (float) colorProcent) + from;
			switch (bpp) {
			case 1: // 8 bits per pixel
				pixelResult[0][y * Height + x] = colorLerp;
				continue;
			case 3:
				pixelResult[0][y * Height * 3 + x * 3 + 0] = colorLerp;
				pixelResult[0][y * Height * 3 + x * 3 + 1] = colorLerp;
				pixelResult[0][y * Height * 3 + x * 3 + 2] = colorLerp;
				continue;
			case 4:
				pixelResult[0][y * Height * 4 + x * 4 + 0] = colorLerp;
				pixelResult[0][y * Height * 4 + x * 4 + 1] = colorLerp;
				pixelResult[0][y * Height * 4 + x * 4 + 2] = colorLerp;
				pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				continue;
			default:
				break;
			}
		}
	}
	return SDL_TRUE;
}

int VDIntGenChecker(unsigned char** pixelsResult, unsigned int Width,
		unsigned int Height, int CheckerXDimension, int CheckerYDimension,
		unsigned int TextureType, unsigned int TextureFlag) {
	if (!VDIntMallocTexture((void**) pixelsResult, Width, Height, TextureType))
		return SDL_FALSE;
	unsigned int x, y, Xpatter, Ypatter, bpp = VDIntGetTextureBpp(TextureType);
	Xpatter = (Width / CheckerXDimension);	// pattern count in X
	Ypatter = (Height / CheckerYDimension);	// pattern count in Y
	for (x = 0; x < Width; x++) {
		for (y = 0; y < Height; y++) {

			float patternIndexX = (float) x / (float) CheckerXDimension;
			float patternIndexY = (float) y / (float) CheckerYDimension;

			switch (bpp) {
			case 1:
				if ((int) patternIndexX % 2 == 0) {	// black
					pixelsResult[0][x * Height * 1 + y * 1] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
				} else {	//white
					pixelsResult[0][x * Height * 1 + y * 1] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
				}

				continue;
			case 3:
				if ((int) patternIndexX % 2 == 0) {
					pixelsResult[0][x * Height * 3 + y * 3] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
					pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
					pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
				} else {
					pixelsResult[0][x * Height * 3 + y * 3] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
					pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
					pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
				}

				continue;
			case 4:
				if ((int) patternIndexX % 2 == 0) {
					pixelsResult[0][x * Height * 4 + y * 4] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
					pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
					pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
							((int) patternIndexY % 2 == 0) ? 0 : 255);
					pixelsResult[0][x * Height * 4 + y * 4 + 3] = 255;
				} else {
					pixelsResult[0][x * Height * 4 + y * 4] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
					pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
					pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
							((int) patternIndexY % 2 == 0) ? 255 : 0);
					pixelsResult[0][x * Height * 4 + y * 4 + 3] = 255;
				}
				continue;
			}	// iteration of bpp
			continue;
		}	// iteration of X
		continue;
	}	// iteration of Y
	return SDL_TRUE;
}

int VDIntGenChecker2(unsigned char** pixelsResult, unsigned int Width,
		unsigned int Height, int CheckerXDimension, int CheckerYDimension,
		const VDColor32& firstCheckerColor, const VDColor32& secondCheckerColor,
		unsigned int TextureType, unsigned int TextureFlag) {
	if (!VDIntMallocTexture((void**) pixelsResult, Width, Height, TextureType))
		return SDL_FALSE;
	unsigned int x = 0, y = 0, bpp = VDIntGetTextureBpp(TextureType);
	unsigned int Xpatter, Ypatter;
	Xpatter = (Width / CheckerXDimension);	// pattern count in X
	Ypatter = (Height / CheckerYDimension);	// pattern count in Y

	for (x = 0; x < Width; x++) {
		for (y = 0; y < Height; y++) {

			float patternIndexX = (float) x / (float) CheckerXDimension;
			float patternIndexY = (float) y / (float) CheckerYDimension;

			switch (bpp) {
			case 1:
				if (((unsigned int) patternIndexX) % 2 == 0) {	// black
					pixelsResult[0][x * Height * 1 + y * 1] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.r() :
									secondCheckerColor.r());
				} else {	//white
					pixelsResult[0][x * Height * 1 + y * 1] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.r() :
									firstCheckerColor.r());
				}

				continue;
			case 3:
				if (((unsigned int) patternIndexX) % 2 == 0) {
					pixelsResult[0][x * Height * 3 + y * 3] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.r() :
									secondCheckerColor.r());
					pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.g() :
									secondCheckerColor.g());
					pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.b() :
									secondCheckerColor.b());
				} else {
					pixelsResult[0][x * Height * 3 + y * 3] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.r() :
									firstCheckerColor.r());
					pixelsResult[0][x * Height * 3 + y * 3 + 1] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.g() :
									firstCheckerColor.g());
					pixelsResult[0][x * Height * 3 + y * 3 + 2] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.b() :
									firstCheckerColor.b());
				}

				continue;
			case 4:
				if (((unsigned int) patternIndexX) % 2 == 0) {
					pixelsResult[0][x * Height * 4 + y * 4] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.r() :
									secondCheckerColor.r());
					pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.g() :
									secondCheckerColor.g());
					pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
							((int) patternIndexY % 2 == 0) ?
									firstCheckerColor.b() :
									secondCheckerColor.b());
					pixelsResult[0][x * Height * 4 + y * 4 + 3] = 255;
				} else {
					pixelsResult[0][x * Height * 4 + y * 4] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.r() :
									firstCheckerColor.r());
					pixelsResult[0][x * Height * 4 + y * 4 + 1] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.g() :
									firstCheckerColor.g());
					pixelsResult[0][x * Height * 4 + y * 4 + 2] = (
							((int) patternIndexY % 2 == 0) ?
									secondCheckerColor.b() :
									firstCheckerColor.b());
					pixelsResult[0][x * Height * 4 + y * 4 + 2] = 255;
				}
				continue;
			}	// iteration of bpp
			continue;
		}	// iteration of X
		continue;
	}	// iteration of Y
	return SDL_TRUE;

	return SDL_TRUE;
}

int VDIntGenGridTexture(unsigned char** pixelResult, unsigned int Width,
		unsigned int Height, unsigned int gridX, unsigned int gridY,
		unsigned int thickness, const unsigned char * backcolours,
		const unsigned char* foreColours, unsigned int TextureFormat) {
	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, TextureFormat))
		return SDL_FALSE;
	unsigned int x = 0, y = 0, bpp = VDIntGetTextureBpp(TextureFormat);
	unsigned int XPatt = gridX;	// pattern count in X
	unsigned int YPatt = gridY;	// pattern count in Y

	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 1: {
				if ((x % XPatt) <= (thickness - 1)
						|| (y % YPatt) <= (thickness - 1))	// line
					pixelResult[0][y * Height + x] = foreColours[0];
				else
					pixelResult[0][y * Height + x] = backcolours[0];
			}
			break;
			case 3: {
				if ((x % XPatt) <= (thickness - 1)
						|| (y % YPatt) <= (thickness - 1)) {	// line
					pixelResult[0][y * Height * 3 + x * 3] = foreColours[0];
					pixelResult[0][y * Height * 3 + x * 3 + 1] = foreColours[1];
					pixelResult[0][y * Height * 3 + x * 3 + 2] = foreColours[2];
				} else {	// line
					pixelResult[0][y * Height * 3 + x * 3] = backcolours[0];
					pixelResult[0][y * Height * 3 + x * 3 + 1] = backcolours[1];
					pixelResult[0][y * Height * 3 + x * 3 + 2] = backcolours[2];
				}
			}
			break;
			case 4: {
				if ((x % XPatt) <= (thickness - 1)
						|| (y % YPatt) <= (thickness - 1)) {	// line
					pixelResult[0][y * Height * 4 + x * 4] = foreColours[0];
					pixelResult[0][y * Height * 4 + x * 4 + 1] = foreColours[1];
					pixelResult[0][y * Height * 4 + x * 4 + 2] = foreColours[2];
					pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				} else {	// line
					pixelResult[0][y * Height * 4 + x * 4] = backcolours[0];
					pixelResult[0][y * Height * 4 + x * 4 + 1] = backcolours[1];
					pixelResult[0][y * Height * 4 + x * 4 + 2] = backcolours[2];
					pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				}
			}
			break;
			}
			continue;
		}
		continue;
	}

	return SDL_TRUE;
}


int ProcAlphaIntensity(unsigned char** pixelResult, unsigned int Width,
		unsigned int Height, unsigned char Alpha, unsigned int TextureFormat) {
	if (pixelResult == nullptr)
		return SDL_FALSE;
	unsigned int x, y, bpp;
	bpp = VDIntGetTextureBpp(TextureFormat);
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 4:
				pixelResult[0][(y * Height * 4) + (4 * x) + 3] = Alpha;
				break;
			}
		}
		continue;
	}
	return SDL_TRUE;
}

int VDIntConvertToAlphaMap(unsigned char** pixelResult,
		const unsigned char* templateTexture, unsigned int Width,
		unsigned int Height, unsigned int TextureType) {
	if (templateTexture == nullptr && pixelResult == nullptr)
		return 0;
	pixelResult[0] = (unsigned char*) malloc(
			sizeof(unsigned char) * Width * Height);

	unsigned int x, y;
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			float rgb[3];
			switch (VDIntGetTextureBpp(TextureType)) {
			case 1:
				rgb[0] = templateTexture[y * Height + x];
				rgb[1] = templateTexture[y * Height + x];
				rgb[2] = templateTexture[y * Height + x];
				break;
			case 3:
				rgb[0] = templateTexture[y * Height * 3 + x * 3];
				rgb[1] = templateTexture[y * Height * 3 + x * 3 + 1];
				rgb[2] = templateTexture[y * Height * 3 + x * 3 + 2];
				break;
			case 4:
				rgb[0] = templateTexture[y * Height * 4 + x * 4];
				rgb[1] = templateTexture[y * Height * 4 + x * 4 + 1];
				rgb[2] = templateTexture[y * Height * 4 + x * 4 + 2];
				break;
			default:
				break;
			}

			unsigned char alphaColor = (unsigned char) (255.0f
					* ((rgb[0] * 0.19f) + (rgb[1] * 0.52f) + (rgb[2] * 0.29f)));
			pixelResult[0][y * Height + y] = 0;

			continue;
		}
		continue;
	}

	return SDL_TRUE;
}

int VDIntConvertToNormalMap(unsigned char** pixelResult,
		const unsigned char* templateTexture, unsigned int Width,
		unsigned int Height, unsigned int TextureType, float Slope,
		float bumpiness) {
	if (templateTexture == NULL)
		return SDL_FALSE; // error,no pointer to pixel data!

	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, GL_RGB))
		return SDL_FALSE;

	unsigned char prePixelColor[3];	//allocate previous Pixel Buffer
	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureType);
	unsigned int isGrayScale = false; //ExIsTexture(templateTexture, Width, Height, TextureType, IS_LUMINANCE);
	VDVector3 S, T;

	VDVector3 final;

	for (y = 0; y < Height; y++) {			//	// Calculate Y Direction.
		for (x = 0; x < Width; x++) {
			if (x == 0 && y == 0) {
				switch (bpp) { // capture the first pixel of the template Texture
				case 1:
					//S[0] = 1.0f;
					//S[1] = 0.0f;
					//S[2] = templateTexture[Width * x + Width + y] - templateTexture[Width * x - Width + y];
					prePixelColor[0] = 128;
					templateTexture[Width * x + y];
					prePixelColor[1] = 128;
					templateTexture[Width * x + y];
					prePixelColor[2] = 128;
					templateTexture[Width * x + y];
					break;
				case 3:
					prePixelColor[0] = 128;
					templateTexture[Height * y * 3 + x * 3 + 0];
					prePixelColor[1] = 128;
					templateTexture[Height * y * 3 + x * 3 + 1];
					prePixelColor[2] = 128;
					templateTexture[Height * y * 3 + x * 3 + 2];
					break;
				case 4:
					prePixelColor[0] = 128;
					templateTexture[Height * y * 4 + x * 4 + 0];
					prePixelColor[1] = 128;
					templateTexture[Height * y * 4 + x * 4 + 1];
					prePixelColor[2] = 128;
					templateTexture[Height * y * 4 + x * 4 + 2];
					break;
				}
			}

			float Delta[] = { prePixelColor[0], prePixelColor[1],
					prePixelColor[2] };
			switch (bpp) {
			break;
			case 1:
				Delta[0] -= templateTexture[Height * y + x];
				Delta[1] -= templateTexture[Height * y + x];
				Delta[2] -= templateTexture[Height * y + x];
				//allocate position;
				prePixelColor[0] = templateTexture[Height * y + x];
				prePixelColor[1] = templateTexture[Height * y + x];
				prePixelColor[2] = templateTexture[Height * y + x];
				break;
			case 2:
				break;
			case 3:
				Delta[0] -= templateTexture[Height * y * 3 + x * 3 + 0];
				Delta[1] -= templateTexture[Height * y * 3 + x * 3 + 1];
				Delta[2] -= templateTexture[Height * y * 3 + x * 3 + 2];

				//allocate position;
				prePixelColor[0] = templateTexture[Height * y * 3 + x * 3 + 0];
				prePixelColor[1] = templateTexture[Height * y * 3 + x * 3 + 1];
				prePixelColor[2] = templateTexture[Height * y * 3 + x * 3 + 2];
				break;
			case 4:
				Delta[0] -= templateTexture[Height * y * 4 + x * 4 + 0];
				Delta[1] -= templateTexture[Height * y * 4 + x * 4 + 1];
				Delta[2] -= templateTexture[Height * y * 4 + x * 4 + 2];

				//allocate position;
				prePixelColor[0] = templateTexture[Height * y * 4 + x * 4 + 0];
				prePixelColor[1] = templateTexture[Height * y * 4 + x * 4 + 1];
				prePixelColor[2] = templateTexture[Height * y * 4 + x * 4 + 2];

				break;
			}
			if (!isGrayScale)
				Delta[1] *= 0.59f;
			unsigned char color = (unsigned char) (((float) (2.0f
					* ((float) Delta[1] / (float) 512.0f)) + 1.0f) * 128.0f);//Convert Delta to Direction
			//color *= (unsigned char)(Delta[1] * bumpiness);

			Delta[1] *= Slope;
			//pixelResult[0][y * Height * 3 + x * 3 + 0] = 0; // Red
			pixelResult[0][y * Height * 3 + x * 3 + 1] = color; // calcuate method Green
			pixelResult[0][y * Height * 3 + x * 3 + 2] = 255; // Blue

			continue;
		}
		continue;
	}

	for (x = 0; x < Width; x++) {
		for (y = 0; y < Height; y++) {
			if (x == 0 && y == 0) {
				switch (bpp) { // capture the first pixel of the template Texture
				case 1:
					prePixelColor[0] = templateTexture[Width * x + y];
					prePixelColor[1] = templateTexture[Width * x + y];
					prePixelColor[2] = templateTexture[Width * x + y];
					break;
					break;
				case 3:
					prePixelColor[0] = templateTexture[Height * y * 3 + x * 3
													   + 0];
					prePixelColor[1] = templateTexture[Height * y * 3 + x * 3
													   + 1];
					prePixelColor[2] = templateTexture[Height * y * 3 + x * 3
													   + 2];
					break;
				case 4:
					prePixelColor[0] = templateTexture[Height * y * 4 + x * 4
													   + 0];
					prePixelColor[1] = templateTexture[Height * y * 4 + x * 4
													   + 1];
					prePixelColor[2] = templateTexture[Height * y * 4 + x * 4
													   + 2];
					break;
				}
			}
			float Delta[] = { prePixelColor[0], prePixelColor[1],
					prePixelColor[2] };
			switch (bpp) {
			break;
			case 1:
				Delta[0] -= templateTexture[Width * x + y];
				Delta[1] -= templateTexture[Width * x + y];
				Delta[2] -= templateTexture[Width * x + y];
				//allocate position;
				prePixelColor[0] = templateTexture[Width * x + y];
				prePixelColor[1] = templateTexture[Width * x + y];
				prePixelColor[2] = templateTexture[Width * x + y];
				break;
			case 2:
				break;
			case 3:
				Delta[0] -= templateTexture[Height * y * 3 + x * 3 + 0];
				Delta[1] -= templateTexture[Height * y * 3 + x * 3 + 1];
				Delta[2] -= templateTexture[Height * y * 3 + x * 3 + 2];

				//allocate position;
				prePixelColor[0] = templateTexture[Height * y * 3 + x * 3 + 0];
				prePixelColor[1] = templateTexture[Height * y * 3 + x * 3 + 1];
				prePixelColor[2] = templateTexture[Height * y * 3 + x * 3 + 2];
				break;
			case 4:
				Delta[0] -= templateTexture[Height * y * 4 + x * 4 + 0];
				Delta[1] -= templateTexture[Height * y * 4 + x * 4 + 1];
				Delta[2] -= templateTexture[Height * y * 4 + x * 4 + 2];

				//allocate position;
				prePixelColor[0] = templateTexture[Height * y * 4 + x * 4 + 0];
				prePixelColor[1] = templateTexture[Height * y * 4 + x * 4 + 1];
				prePixelColor[2] = templateTexture[Height * y * 4 + x * 4 + 2];

				break;
			}
			if (!isGrayScale)
				Delta[0] *= 0.29f;
			unsigned char color = (unsigned char) (((float) (2.0f
					* ((float) Delta[0] / (float) 512.0f)) + 1.0f) * 128.0f); //Convert Delta to Direction
			Delta[0] *= Slope;
			pixelResult[0][y * Height * 3 + x * 3] = color; // apply color

			continue;
		}
		continue;
	}
	return 1;
}

int VDIntConvertToDisplaceMap(unsigned char** pixelResult,
		const unsigned char* templateTexture, unsigned int Width,
		unsigned int Height, unsigned int TextureType) {
	if (templateTexture == NULL || pixelResult == NULL)
		return SDL_FALSE;

	pixelResult[0] = (unsigned char*) malloc(
			VDIntGetTextureBpp(TextureType) * Width * Height);

	unsigned int x, y, bpp, isGray;
	unsigned char colours[4];
	bpp = VDIntGetTextureBpp(TextureType);
	isGray = false; // ExIsTexture(templateTexture, Width,Height, TextureType,GL_LUMINANCE);
	for (x = 0; x < Width; x++) {
		for (y = 0; y < Height; y++) {
			switch (bpp) {
			// get Data
			case 1:
				colours[0] = templateTexture[y * Height + x];
				break;
			case 3:
				colours[0] = templateTexture[y * Height * 3 + x * 3];
				colours[1] = templateTexture[y * Height * 3 + x * 3 + 1];
				colours[2] = templateTexture[y * Height * 3 + x * 3 + 2];
				break;
			case 4:
				colours[0] = templateTexture[y * Height * 4 + x * 4];
				colours[1] = templateTexture[y * Height * 4 + x * 4 + 1];
				colours[2] = templateTexture[y * Height * 4 + x * 4 + 2];
				break;
			}
			if (!isGray)
				pixelResult[0][y * Height + x] = 0;
			else
				pixelResult[0][y * Height + x] = 0;
			continue;
		}
		continue;
	}
	return SDL_TRUE;
}

int VDIntConvertToInvert(unsigned char** PixelResult,
		const unsigned char* templateTexture, unsigned int Width,
		unsigned int Height, unsigned int TextureType) {
	if (!VDIntMallocTexture((void**) PixelResult, Width, Height, TextureType))
		return SDL_FALSE;
	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureType);
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 1:
				PixelResult[0][y * Height + x] = UCHAR_MAX
				- templateTexture[y * Height + x];
				break;
			case 3:
				PixelResult[0][y * Height * 3 + x * 3] = UCHAR_MAX
				- templateTexture[y * Height * 3 + x * 3];
				PixelResult[0][y * Height * 3 + x * 3 + 1] = UCHAR_MAX
						- templateTexture[y * Height * 3 + x * 3 + 1];
				PixelResult[0][y * Height * 3 + x * 3 + 2] = UCHAR_MAX
						- templateTexture[y * Height * 3 + x * 3 + 2];
				break;
			case 4:
				PixelResult[0][y * Height * 4 + x * 4] = UCHAR_MAX
				- templateTexture[y * Height * 4 + x * 4];
				PixelResult[0][y * Height * 4 + x * 4 + 1] = UCHAR_MAX
						- templateTexture[y * Height * 4 + x * 4 + 1];
				PixelResult[0][y * Height * 4 + x * 4 + 2] = UCHAR_MAX
						- templateTexture[y * Height * 4 + x * 4 + 2];
				PixelResult[0][y * Height * 4 + x * 4 + 3] = UCHAR_MAX;
				break;
			default:
				break;
			}
			continue;
		}
		continue;
	}
	return SDL_TRUE;
}

unsigned int ConvertToGrayScale(unsigned char** pixelResult,
		unsigned char*templateTexture, unsigned int Width, unsigned int Height,
		unsigned int TextureType) {
	if (!VDIntMallocTexture((void**) pixelResult, Width, Height, TextureType))
		return SDL_FALSE;

	unsigned int x, y, bpp = VDIntGetTextureBpp(TextureType);

	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			switch (bpp) {
			case 1:
				pixelResult[0][y * Height + x] = 255
				- templateTexture[y * Height + x];
				break;
			case 3:
				unsigned char raWPix[3];
				raWPix[0] = templateTexture[y * Height * 3 + x * 3];
				raWPix[1] = templateTexture[y * Height * 3 + x * 3 + 1];
				raWPix[2] = templateTexture[y * Height * 3 + x * 3 + 2];
				raWPix[0] = ((float) raWPix[0] * 0.29f);
				raWPix[1] = ((float) raWPix[1] * 0.59f);
				raWPix[2] = ((float) raWPix[2] * 0.12f);
				unsigned char Gray;
				Gray = raWPix[0] + raWPix[1] + raWPix[2];

				pixelResult[0][y * Height * 3 + x * 3 + 0] = Gray;
				pixelResult[0][y * Height * 3 + x * 3 + 1] = Gray;
				pixelResult[0][y * Height * 3 + x * 3 + 2] = Gray;
				break;
			case 4:
				unsigned char rawPix[3];
				rawPix[0] = templateTexture[y * Height * 4 + x * 4];
				rawPix[1] = templateTexture[y * Height * 4 + x * 4 + 1];
				rawPix[2] = templateTexture[y * Height * 4 + x * 4 + 2];
				rawPix[0] = ((float) rawPix[0] * 0.29f);
				rawPix[1] = ((float) rawPix[1] * 0.59f);
				rawPix[2] = ((float) rawPix[2] * 0.12f);
				unsigned char gray;
				gray = rawPix[0] + rawPix[1] + rawPix[2];
				pixelResult[0][y * Height * 4 + x * 4] = gray;
				pixelResult[0][y * Height * 4 + x * 4 + 1] = gray;
				pixelResult[0][y * Height * 4 + x * 4 + 2] = gray;
				pixelResult[0][y * Height * 4 + x * 4 + 3] = 255;
				break;
			default:
				break;
			}
			continue;
		}
		continue;
	}

	return 1;
}

unsigned int VDIntGetTextureBpp(const unsigned int TextureFlag) {
	switch (TextureFlag) {
	case 1:
	case GL_ALPHA:
	case GL_LUMINANCE:
	case GL_DEPTH_COMPONENT:
	case GL_RED:
		return 1;
	case 3:
	case GL_RGB:
		return 3;
	case 4:
	case GL_RGBA:
	case GL_DEPTH_COMPONENT32:
		return 4;
	case GL_RGB16:
		return 3 * 2;
	case GL_RGBA16:
		return 4 * 2;
	case GL_LUMINANCE16:
		return 2;
	case GL_RGB32F:
		return sizeof(float) * 3;
	case GL_RGBA32F:
		return sizeof(float) * 4;
	default:
		return 0;
	}
}

unsigned int GetTextureDataSize(unsigned int Width, unsigned int Height,
		unsigned int TextureFormat) {
	return (Width * Height * VDIntGetTextureBpp(TextureFormat));
}

int VDIntMallocTexture(void** data, unsigned int Width, unsigned int Height,
		unsigned int TextureFormat) {
	if (data == NULL)
		return SDL_FALSE;

	if (data[0] == NULL)
		data[0] = malloc(GetTextureDataSize(Width, Height, TextureFormat));
	return SDL_TRUE;
}
