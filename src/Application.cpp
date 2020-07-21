#include <assert.h>
#include <Core/VDApplication.h>
#include <Core/VDBehavior.h>
#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDScreen.h>
#include <DataStructure/VDSize.h>
#include <GL/glew.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Scene/VDGameObject.h>
#include <cstdlib>
#include <list>

using namespace std;


void VDApplication::focus(void){
	/*	*/
	for(VDGameObjectList::iterator it = gSerlizedGameObject.begin(); it != gSerlizedGameObject.end(); it++){
		for(unsigned int x = 0; x < (*it)->getComponentCount(); x++){
			assert((*it)->getComponentByIndex(x));
			(*it)->getComponentByIndex(x)->onApplicationFocus();
		}
	}

}

void VDApplication::unFocus(void){

	/*	*/
	for(VDGameObjectList::iterator it = gSerlizedGameObject.begin(); it != gSerlizedGameObject.end(); it++){
		for(unsigned int x = 0; x < (*it)->getComponentCount(); x++){
			assert((*it)->getComponentByIndex(x));
			(*it)->getComponentByIndex(x)->onApplicationUnFocus();
		}
	}

}

void VDApplication::quit(int status){

	/*	Sending callback to all scripts	*/
	for(VDGameObjectList::iterator it = gSerlizedGameObject.begin(); it != gSerlizedGameObject.end(); it++){
		for(unsigned int x = 0; x < (*it)->getComponentCount(); x++){
			assert((*it)->getComponentByIndex(x));
			(*it)->getComponentByIndex(x)->onApplicationQuit();
		}
	}

	/*	Release resources.	*/
	VDEngine::releaseEngine();

	/*	*/
	VDDebug::debugLog("Application exit with signal : %d.\n", status);
	exit(status);
}

void VDApplication::captureScreenshot(const char* cfilename, float superSize){

	int status;
	VDSize size = VDSize(VDScreen::width(), VDScreen::height());
	unsigned int bpp = 4;
	VDTexture::TextureDataType type = VDTexture::eUnsignedByte;

	unsigned int format = (bpp == 4) ? VDTexture::eRGBA : VDTexture::eRGB;

	unsigned char *pixelData = (unsigned char *)malloc((int)size.width() * (int)size.height() * bpp);

	/*	Read Front Of Screen.	*/
	glReadBuffer(GL_FRONT);

	/*	read Pixel from screen	*/
	glReadPixels(0, 0, size.width(), size.height(), format, type, pixelData);
	status = VDTexture2D::saveTextureContent(cfilename, pixelData, size.width(), size.height(), format, type, 0);
	free(pixelData);
}
