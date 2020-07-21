#include <Core/VDDebug.h>
#include <Core/VDScreen.h>
#include <DataStructure/VDSize.h>
#include <GL/glew.h>
#include <Misc/VDMath.h>
#include <Rendering/Texture/VDRenderTexture.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDRenderBuffer.h>
#include <Rendering/VDRenderingAPICache.h>
#include <VDSystemInfo.h>
#include <cmath>
#include <cstring>

using namespace std;


VDRenderTexture::VDRenderTexture(void) : VDTexture2D(){
	glGenFramebuffers(1, &this->framebuffer);
	this->bind();
	this->unBind();
}

VDRenderTexture::VDRenderTexture(const VDRenderTexture& renderTexture) : VDTexture2D(){
	*this = renderTexture;
}

VDRenderTexture::VDRenderTexture(unsigned int width, unsigned int height, unsigned int surfaceFormat, unsigned int surfaceinternalFormat, unsigned int surfaceType,  unsigned int mipMap)
	: VDTexture2D(width, height, surfaceinternalFormat, surfaceFormat, surfaceType, mipMap){

	glGenFramebuffers(1, &this->framebuffer);
	this->bind();
	this->flag |= (mipMap & VDTexture::eMipMapping) != 0 ? VDTexture::eMipMapping : 0;

	this->setTextureAttachment(surfaceFormat != VDTexture::eDepthComponent ? VDRenderTexture::eColorAttachment0 : VDRenderTexture::Attachment::eDepthAttachment, (VDTexture2D*)this);
}

VDRenderTexture::~VDRenderTexture(void){

}

void VDRenderTexture::release(void){
	if(this->isValid()){
		unsigned int numAttach = this->getNumOfAttachment();
		unsigned int numRend = this->getNumOfRenderBuffer();

		/*	TODO check all tecture attachment and renderrer attachment and find the refernce object and deicrement the pointer.*/
		glDeleteFramebuffers(1, &this->framebuffer);
	}

	this->framebuffer = 0;
	VDTexture::release();
}

bool VDRenderTexture::isValid(void)const{
	return ( glIsFramebuffer(this->framebuffer) == GL_TRUE );
}

void VDRenderTexture::init(VDRenderTexture::Attachment attachment, VDTexture::TextureFormat format, const VDSize& size){
	if(!isValid())
		glGenFramebuffers(1, &this->framebuffer);
	this->bind();

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, this->target, this->texture, 0);


	this->mWidth = size.width();
	this->mHeight = size.height();
}

void VDRenderTexture::resize(unsigned int width, unsigned int height, unsigned int layer){

	if(!this->isValid()){
		return;
	}

	int maxAttachment = 16;
	const int attachemntsize = VDSystemInfo::getCompatibility()->sMaxFrameBufferAttachment;
	int attachmentIndices[attachemntsize];
	memset(attachmentIndices, GL_NONE, attachemntsize * sizeof(attachmentIndices[0]));
	/*	TODO fix issues when requesting to resize texture for attachements.	*/


	this->getAttachemtIndices(eColorAttachment0, attachmentIndices);
	this->write();

	if(this->isVolume()){
		for(int x = 0; x < layer; x++){

		}
	}
	if(this->isCubemap()){
		for(int x = 0; x < 6; x++){
			glTexImage2D(VDTexture::eCubeMapPositiveX + x, 0, this->internalFormat, width, height, 0, this->format, this->type, NULL);
		}
	}
	else{
		VDTexture texture;
		VDRenderBuffer renderbuffer;

		/*	attachment0.	*/
		for(int x = 0; x < maxAttachment; x++){
			if(attachmentIndices[x] == GL_NONE || !glIsTexture(attachmentIndices[x])){
				continue;
			}
			texture = getTextureAttachment(x, VDRenderTexture::eColorAttachment0);
			if(texture.isValid()){
				glBindTexture(texture.getTarget(), this->getTexture());
				glTexImage2D(texture.getTarget(), 0, texture.getInternalFormat(), width, height, 0, texture.getInternalFormat(), VDTexture::eUnsignedByte, NULL);
			}
		}

		/*	depth buffer.	*/
		texture = getTextureAttachment(0, VDRenderTexture::eDepthAttachment);
		if(texture.isValid()){
			glBindTexture(texture.getTarget(), this->getTexture());
			glTexImage2D(texture.getTarget(), 0, texture.getInternalFormat(), width, height, 0, texture.getInternalFormat(), VDTexture::eUnsignedByte, NULL);
			//this->setAttachment(VDRenderTexture::eDepthAttachment, &texture);
		}

		/*	stencilbuffer.	*/
		texture = getTextureAttachment(0, VDRenderTexture::eStencilAttachment);
		if(texture.isValid()){
			glBindTexture(texture.getTarget(), this->getTexture());
			glTexImage2D(texture.getTarget(), 0, texture.getInternalFormat(), width, height, 0, texture.getInternalFormat(), VDTexture::eUnsignedByte, NULL);

		}


		/*	renderbuffer0.	*/
		for(int x = 0; x < maxAttachment; x++){
			if( ( attachmentIndices[x] == GL_NONE ) || !glIsRenderbuffer(attachmentIndices[x])){
				continue;
			}
			renderbuffer = getRenderBuffer(x, VDRenderTexture::eColorAttachment0);
			if(renderbuffer.isValid())
				renderbuffer.setStorage(width, height, renderbuffer.getInternalFormat());
		}


		/*	renderubffer depth buffer attachment.	*/
		renderbuffer = getRenderBuffer(0, VDRenderTexture::eDepthAttachment);
		if(renderbuffer.isValid()){
			renderbuffer.setStorage(width, height, renderbuffer.getInternalFormat());
		}

		/*	renderbuffer stencil attachment.	 */
		renderbuffer = getRenderBuffer(0, VDRenderTexture::eStencilAttachment);
		if(renderbuffer.isValid())
			renderbuffer.setStorage(width, height, renderbuffer.getInternalFormat());

	}

	VDRenderTexture::checkError();
	/**/
	this->mWidth = width;
	this->mHeight = height;
}

void VDRenderTexture::setTextureAttachment(Attachment attachment, VDTexture* texture){
	if(!this->isValid()){
		glGenFramebuffers(1, &this->framebuffer);
	}


	this->write();

	/*	*/
	if(texture != NULL){
		if(texture != this){
			texture->increment();
		}

		/*	check what type of texture target */
		switch(texture->getTarget()){
		case VDTexture::eTexture2D:
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment, texture->getTarget(), texture->getTexture(), 0);
			break;
		case VDTexture::eCubeMap:
			glFramebufferTexture(GL_DRAW_FRAMEBUFFER, attachment, texture->getTexture(), 0);
			break;
		}

		/**/
		if(attachment >= eColorAttachment0 && attachment <= GL_COLOR_ATTACHMENT15){
			int indices[16] = {0};
			GLenum buffers[16] = {0};
			unsigned int num = this->getAttachemtIndices(VDRenderTexture::eColorAttachment0, &indices[0]);
			int index = 0;
			for(int x = 0; x < 16; x++){
				if(glIsTexture( indices[x] )){
					buffers[index] = GL_COLOR_ATTACHMENT0 + x;
					index++;
				}
			}
			glDrawBuffers(num, &buffers[0]);
		}
		else{
			glReadBuffer(GL_NONE);
		}
	}
	else{
		glFramebufferTexture(GL_DRAW_FRAMEBUFFER, attachment, 0, 0);
	}

	/*	*/
	if(this->checkError() != GL_FRAMEBUFFER_COMPLETE){
		//texture->reference.deincreemnt();
	}
}

void VDRenderTexture::setAttachment(VDRenderTexture::Attachment attachment, VDRenderBuffer* renderbuffer){
	if(!renderbuffer){
		return;
	}
	if(!isValid()){
		glGenFramebuffers(1, &this->framebuffer);
	}

	renderbuffer->increment();
	this->bind();

	renderbuffer->bind();
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer->getRendererID());

	/*	*/
	if(checkError() != GL_FRAMEBUFFER_COMPLETE){
		//texture->reference.deincreemnt();
	}
}

VDTexture VDRenderTexture::getTextureAttachment(int index, VDRenderTexture::Attachment attachment){
	VDTexture frameTexture;
	int type;
	int name;
	int cube;

	type = cube = name = 0;
	this->bind();

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_TEXTURE){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &name);
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, &cube);
		/*	find texture with the references!	*/
	}

	switch(cube){
	case 0:
		glBindTexture(GL_TEXTURE_2D, name);
		frameTexture.setTextureTarget(VDTexture::eTexture2D);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, (GLint*)&frameTexture.mWidth);
		//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, (GLint*)&((VDTexture2D*)&frameTexture)->mHeight);
		break;
	default:
		glBindTexture(GL_TEXTURE_CUBE_MAP, name);
		frameTexture.setTextureTarget(VDTexture::eCubeMap);
		break;
	}
	/*	extract information about texture.*/
	frameTexture.setTextureID(name);
	//glGetTexParameteriv()

	glBindTexture(frameTexture.getTarget(), 0);

	/*	increment*/
	frameTexture.increment();
	return frameTexture;
}

unsigned int VDRenderTexture::getAttachmentNative(int index, unsigned int attachment){
	int type;
	int name;
	this->bind();

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_TEXTURE){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &name);
		/*	find texture with the references!	*/
	}

	return name;
}

VDRenderBuffer VDRenderTexture::getRenderBuffer(int index, Attachment attachment){
	VDRenderBuffer renderbuffer;
	int type = 0;
	int name = 0;
	int cube = 0;
	this->bind();

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_RENDERBUFFER){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &name);
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + index, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, &cube);
		/*	find texture with the references!	*/
	}

	/*	extract information about texture.*/
	renderbuffer.setRenderId(name);
	/*	increment*/
	renderbuffer.increment();
	renderbuffer.increment();
	return renderbuffer;
}

void VDRenderTexture::setSamples(unsigned int sample){
	/*	check if power of two.	*/
	if(VDMath::modf( log2(sample) )  == 0){
		this->bind();
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, sample);
		/*	go through all components.	*/
	}
}

int VDRenderTexture::getSamples(void){
	int samples;
	this->bind();
	glGetFramebufferParameteriv(GL_FRAMEBUFFER, GL_SAMPLES, &samples);
	return samples;
}

VDRenderBuffer VDRenderTexture::colorBuffer(void){
	VDRenderBuffer buffer;
	int type;
	this->bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_RENDERBUFFER){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&buffer.renderer);
	}

	return buffer;
}

VDRenderBuffer VDRenderTexture::depth(void){
	VDRenderBuffer buffer;
	int type;
	this->bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_RENDERBUFFER){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&buffer.renderer);
	}

	return buffer;
}

VDRenderBuffer VDRenderTexture::stencil(void){
	VDRenderBuffer buffer;
	int type;
	this->bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	if(type == GL_RENDERBUFFER){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&buffer.renderer);
	}

	return buffer;
}


void VDRenderTexture::bind(void){
	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
}

void VDRenderTexture::unBind(void){
	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, 0);
}

void VDRenderTexture::bindTextures(unsigned int startActive){
	unsigned int numMaxAttachment = (getMaxColorAttachment() - GL_COLOR_ATTACHMENT0);
	int tex;
	unsigned int num = 0;
	int type;
	this->bind();
	for(int x = 0; x < numMaxAttachment; x++){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, VDRenderTexture::eColorAttachment0 + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, (GLint*)&type);
		if(type == GL_TEXTURE){
			glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, VDRenderTexture::eColorAttachment0 + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&tex);
			VDRenderingAPICache::bindTexture(VDTexture::eTexture2D, tex, startActive + num);
			num++;
		}
	}
}

void VDRenderTexture::blitTo(VDRenderTexture* framebuffer){
	this->read();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, this->width(), this->height(),
				0,0,VDScreen::width(), VDScreen::height(),
				GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void VDRenderTexture::read(void){
	VDRenderingAPICache::bindFramebuffer(GL_READ_FRAMEBUFFER, this->framebuffer);
}

void VDRenderTexture::write(void){
	VDRenderingAPICache::bindFramebuffer(GL_DRAW_FRAMEBUFFER, this->framebuffer);
}

void VDRenderTexture::clear(void){
	this->write();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool VDRenderTexture::isCubemap(void){
	return this->getTarget() == VDTexture::eCubeMap;
}

bool VDRenderTexture::isVolume(void){
	return 	this->getTarget() == VDTexture::eTexture2DArray ||
			this->getTarget() == VDTexture::eTexture3D ||
			this->getTarget() == VDTexture::eTexture2DArrayMultiSample ||
			this->getTarget() == VDTexture::eTexture1DArray;
}

unsigned int VDRenderTexture::getAttachemtIndices(Attachment attachment, int* indices){
	int type;
	int num = 0;

	VDRenderTexture::bind();
	/*TODO	get max number of attachment.	*/
	unsigned int numMaxAttachment = (getMaxColorAttachment() - GL_COLOR_ATTACHMENT0);
	for(int x = 0; x < numMaxAttachment; x++){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
		if(type != GL_NONE){
			glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GLint*)&indices[x]);
			num++;
		}
	}

	return num;
}

unsigned int VDRenderTexture::getNumOfAttachment(void){
	int type;
	int num = 0;

	VDRenderTexture::bind();
	/*TODO	get max number of attachment.	*/
	unsigned int numAttachment = (getMaxColorAttachment() - GL_COLOR_ATTACHMENT0);
	for(int x = 0; x < numAttachment; x++){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
		if(type == GL_TEXTURE)
			num++;
	}

	return num;
}

bool VDRenderTexture::isColorAttached(Attachment attachment){
	int type;
	VDRenderTexture::bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attachment , GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	return ( type == GL_RENDERBUFFER || type == GL_TEXTURE );
}

bool VDRenderTexture::isDepthAttached(void){
	int type;
	VDRenderTexture::bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, VDRenderTexture::eDepthAttachment , GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	return ( type == GL_RENDERBUFFER || type == GL_TEXTURE );
}

bool VDRenderTexture::isStencilAttached(void){
	int type;
	VDRenderTexture::bind();
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, VDRenderTexture::eStencilAttachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
	return ( type == GL_RENDERBUFFER || type == GL_TEXTURE );
}


unsigned int VDRenderTexture::getNumOfRenderBuffer(void){
	int type;
	int num = 0;

	this->bind();
	for(int x = 0; x < (GL_COLOR_ATTACHMENT15 - GL_COLOR_ATTACHMENT0); x++){
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + x, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &type);
		if(type == GL_RENDERBUFFER)
			num++;
	}

	return num;
}

unsigned int VDRenderTexture::checkError(void){
	unsigned int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch(status){
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		VDDebug::errorLog("Framebuffer incomplete attachment.\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		VDDebug::errorLog("Framebuffer incomplete dimensions.\n");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		VDDebug::errorLog("Framebuffer incomplete missing attachment.\n");
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		VDDebug::errorLog("Framebuffer unsporrted.\n");
		break;
	case GL_FRAMEBUFFER_COMPLETE:
		VDDebug::log("Successful framebuffer.\n");
		break;
	default:
		VDDebug::errorLog("Framebuffer error, status: 0x%x\n", status);
		break;
	}
	return status;
}


VDRenderTexture* VDRenderTexture::colorTexture(unsigned int width, unsigned int height, unsigned int SurfaceFormat, unsigned int SurfaceinternalFormat, unsigned int SurfaceType,  unsigned int mipMap){
	VDRenderTexture* render = new VDRenderTexture(width, height, SurfaceFormat, SurfaceinternalFormat, SurfaceType, mipMap);
	unsigned int state;
	render->bind();

	render->isTexture()->bind();
	glTexParameteri(render->getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(render->getTarget(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	render->setWrapMode(VDTexture::eClampEdge);

	/**/
	if(mipMap & VDTexture::eMipMapping){
		render->updateMipMap();
	}

	/*
	VDRenderBuffer buffer = VDRenderBuffer();
	buffer.bind();
	buffer.setStorage(width, height, VDTexture::TextureFormat::eDepthComponent32);
	render->setAttachment(VDRenderTexture::eDepthAttachment, (VDRenderBuffer*)&buffer);
	render->setAttachment(VDRenderTexture::eColorAttachment0, (VDTexture*)render);
*/


	if(VDRenderTexture::checkError() != GL_FRAMEBUFFER_COMPLETE){
		VDDebug::errorLog("Failed to create color RenderTexture!\n");
	}

	render->unBind();
	return render;
}

VDRenderTexture* VDRenderTexture::LuminanceTexture(unsigned int width, unsigned int height, unsigned int SurfaceType, unsigned int SurfaceFormat, unsigned int SurfaceinternalFormat, unsigned int mipMap){
	VDRenderTexture* lumiTex = new VDRenderTexture(width, height, SurfaceFormat, SurfaceinternalFormat, SurfaceType, mipMap );

	lumiTex->bind();
	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER,lumiTex->framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,lumiTex->texture,0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	unsigned int state = VDRenderTexture::checkError();
	if(state != GL_FRAMEBUFFER_COMPLETE){
		VDDebug::errorLog("Failed to Initilize Luminance FrameBuffer!\n");
	}

	lumiTex->unBind();
	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, 0);
	return lumiTex;
}

VDRenderTexture* VDRenderTexture::StencilTexture(unsigned int width, unsigned int height, unsigned int SurfaceType, unsigned int SurfaceFormat, unsigned int SurfaceinternalFormat, unsigned int MipMap){
	VDRenderTexture* stencilTex = new VDRenderTexture(width, height,SurfaceType, SurfaceFormat,SurfaceinternalFormat,MipMap );
	stencilTex->bind();


	stencilTex->unBind();
	return stencilTex;
}



VDRenderTexture* VDRenderTexture::colorCubeMap(unsigned int width, unsigned int height, unsigned int surfaceType, unsigned int surfaceFormat, unsigned int surfaceInternalFormat , unsigned int mipmap){
	unsigned int tex;
	VDRenderTexture* rendTex = new VDRenderTexture();
	rendTex->setTextureTarget(VDTexture::TextureTarget::eCubeMap);
	rendTex->mWidth = width;
	rendTex->mHeight = height;


	glGenTextures(1, &tex);
	glBindTexture(rendTex->getTarget(), tex);
	glTexParameteri(rendTex->getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(rendTex->getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(rendTex->getTarget(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	glTexParameteri(rendTex->getTarget(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(rendTex->getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/**/
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, surfaceInternalFormat , rendTex->width(), rendTex->height(), 0, surfaceFormat, surfaceType, NULL);

	/**/
	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, rendTex->getTexture(), 0);

	unsigned int state = VDRenderTexture::checkError();
	if(state != GL_FRAMEBUFFER_COMPLETE){
		VDDebug::errorLog("Failed to create color cubemap!\n");
		rendTex->release();
	}

	rendTex->unBind();
	return rendTex;
}


VDRenderTexture* VDRenderTexture::ShadowMap(unsigned int width, unsigned int height, unsigned int SurfaceFormat, unsigned int SurfaceinternalFormat, unsigned int SurfaceType,  unsigned int MipMap){
	VDRenderTexture* render = new VDRenderTexture(width, height, SurfaceFormat, SurfaceinternalFormat, SurfaceType, MipMap);

	render->setTextureTarget(VDTexture::eTexture2D);
	render->bind();
	render->setFilterMode(VDTexture::FilterMode::eNearest);
	render->setWrapMode(VDTexture::WrapMode::eClampBorder);


	GLfloat border[4]={1,0,0,0};
	glTexParameterfv(render->getTarget(), GL_TEXTURE_BORDER_COLOR, border);

	glTexParameteri(render->getTarget(), GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(render->getTarget(), GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);


	render->setTextureAttachment(VDRenderTexture::eDepthAttachment, render);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	unsigned int state = VDRenderTexture::checkError();
	if(state != GL_FRAMEBUFFER_COMPLETE){
		VDDebug::errorLog("Failed to create shadowmap framebuffer!\n");
		render->release();
	}
	render->unBind();
	return render;
}

VDRenderTexture* VDRenderTexture::ShadowCubeMap(unsigned int Width, unsigned int Height, unsigned int SurfaceFormat , unsigned int SurfaceinternalFormat,  unsigned int surfaceType, unsigned int MipMap){
	VDRenderTexture* render = new VDRenderTexture();
	render->setTextureTarget(VDTexture::eCubeMap);
	render->bind();
	render->mWidth = Width;
	render->mHeight = Height;

	glGenTextures(1, &render->texture);
	glBindTexture(render->getTarget(), render->getTexture());
	render->setWrapMode(VDTexture::eClampBorder);

	glTexParameteri(render->getTarget(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(render->getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, SurfaceinternalFormat , render->width(), render->height(), 0, SurfaceFormat, surfaceType, NULL);

	float bordercolor[] = {1.0, 1.0, 1.0, 1.0};
	glTexParameterfv(render->getTarget(), GL_TEXTURE_BORDER_COLOR, bordercolor);

	glTexParameteri(render->getTarget(), GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(render->getTarget(), GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, render->getTexture(), 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	unsigned int state = VDRenderTexture::checkError();
	if(state != GL_FRAMEBUFFER_COMPLETE){
		VDDebug::errorLog("Failed to create shadowmap framebuffer!\n");
		render->release();
	}

	render->unBind();
	return render;
}

VDRenderTexture* VDRenderTexture::createRenderTexture(const VDSize& size, unsigned int templateType){
	switch(templateType){
		case eColor: return VDRenderTexture::colorTexture(size.width(), size.height());
		case eLuminance: return VDRenderTexture::LuminanceTexture(size.width(), size.height());
		case eStencil: return VDRenderTexture::StencilTexture(size.width(), size.height());
		case eShadowMapping: return VDRenderTexture::ShadowMap(size.width(), size.height());
		default: return NULL;
	}
}



void VDRenderTexture::blit(VDRenderTexture* read, VDRenderTexture* write){
	unsigned int swidth;
	unsigned int sheight;
	unsigned int dwidth;
	unsigned int dheight;
	if(read){
		read->read();
		swidth = read->width();
		sheight = read->height();
	}else{
		VDRenderingAPICache::bindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}
	if(write){
		write->write();
	}else{
		VDRenderingAPICache::bindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		dheight = sheight;
		dwidth = swidth;
	}

	glBlitFramebuffer(0,0, swidth, sheight, 0, 0, dwidth, dheight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}


