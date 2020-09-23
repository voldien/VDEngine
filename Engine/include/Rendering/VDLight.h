/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_LIGHT_H_
#define _VD_LIGHT_H_ 1
#include"../Scene/VDFrustum.h"
#include"../DataStructure/VDVector.h"
#include"../Rendering/VDUniformBuffer.h"

/**
 *	Light gameobject components. Responsible for
 *	adding light and shadow.
 */
class VDDECLSPEC VDLight : public VDFrustum {
public:

	/**
	 *
	 */
	enum LightType {
		Point 		= 0x4,			/*	Point light, aka omni light.	*/
		eSpot 		= 0x8,			/*	Spot light.	*/
		eDirection 	= 0x10,			/*	Direction light.	*/
	};

	enum LightShadow{
		enoShadow 		= 0x80,		/*	*/
		eHardShadow 		= 0x100,	/*	*/
		eSoftShadow 		= 0x200,	/*	*/
		eLowShadowQuality 	= 0x200,	/*	*/
		eMediumShadowQuality 	= 0x400,	/*	*/
		eHighShadowQuality 	= 0x800,	/*	*/
		eUltraShadowQuality 	= 0x1000,	/*	*/
		eSuperShadowQuality 	= 0x2000,	/*	*/
		eShadowEnable 		= 0x4000,	/*	*/
	};

	enum Attenuation{
		None 		= 0x8000,		/*	*/
		eConstant 	= 0x10000,		/*	*/
		eLinear 	= 0x20000,		/*	*/
		eQuadratic 	= 0x40000,		/*	*/
	};

    VDLight(void);
    VDLight(const VDLight& light);
    VDLight(LightType lightType);

private:	/*	Attributes.	*/

	VDColor diffuseColor;			/**/
	float range;					/**/
	float innerCone;				/**/
	float outerCone;				/**/
	float intensity;				/**/
	float shadowStrength;			/**/
	float shadowBias;				/**/

	unsigned int flag;					/**/
	VDRenderTexture* shadowBuffer;		/**/

	float constAtteuation;				/**/
	float linearAtteuation;				/**/
	float quadraticAtteuation;			/**/

	unsigned char type;

public:	/*	Public method.	*/

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *
	 */
	void VDAPIENTRY setAttenuation(VDLight::Attenuation lightAttenuation, float attenuation);

	/**
	 *	@Return
	 */
	float VDAPIENTRY getAtteuation(VDLight::Attenuation lightAttenuation);

	/**
	 *
	 */
	void VDAPIENTRY setType(VDLight::LightType lightType);	/*	TODO rename to setType	*/

	/**
	 *	@Return
     	 */
	inline unsigned int getType(void)const{
		return this->type;
	}


	/**
     *
	*/
	void VDAPIENTRY setIntensity(float intensity); 

	/**
	 *	@Return
     */
	inline float getIntensity(void)const{
		return this->intensity;
	}

	/**
     *
     */
    void VDAPIENTRY setColor(const VDColor& color); 

	/**
	 *	@Return
     */
    inline VDColor VDAPIENTRY getColor(void)const{
		return this->diffuseColor;
	}

    /*
     *
     */
    void VDAPIENTRY setOuterCone(float Cutoff);

    /*
     *
	 *	@Return
     */
    inline float VDAPIENTRY getOuterCone(void)const{
		return this->outerCone;
	} 
  
    /**
     *
     */
    void VDAPIENTRY setInnerCone(float DropOff);

    /*
     *
	 *	@Return
     */
    inline float VDAPIENTRY getInnerCone(void)const{
		return this->innerCone;
	} 
  
    /*
     *
     */
    void VDAPIENTRY setRange(float range); 

    /*
     *
	 *	@Return
     */
    inline float VDAPIENTRY getRange(void)const{
		return this->range;
	}
  

    /*
     *
     */
    void VDAPIENTRY setShadowStrength(float strenght); 

    /*
     *
	 *	@Return
     */
    inline float VDAPIFASTENTRY getShadowStrenght(void)const{
    	return this->shadowStrength;
    }

    /**
     *
     */
    void VDAPIFASTENTRY setShadowBias(float bias);

    /**
	 *	@Return
     */
    inline float VDAPIFASTENTRY getShadowBias(void)const{
    	return this->shadowBias;
    }


    /**
     *
     */
	void VDAPIENTRY enableShadow(bool enabled);


    /**
     *	TODO resolve this ambiguous functions!
     */
    void VDAPIENTRY setShadow(unsigned int lightShadow);

	/*
	 *	Set Size of the
	 */
	void VDAPIENTRY setShadowSize(unsigned int alignSize);

	/**
	 *	@Return align size in pixels.
	 */
	int VDAPIENTRY getShadowSize(void)const;


	/**
	 *	Get Shadow Texture Attach to This Light.
	 *	@Return
	 */
	inline VDRenderTexture* getShadowTexture(void)const{
		return this->shadowBuffer;
	}

	/*
	 *	Set Shadow Texture to Light.
	 */
	void VDAPIENTRY setShadowTexture(VDRenderTexture* renderTexture);

	/**
	 *	Get light matrix.
	 *	@Return
	 */
    VDMatrix4x4 VDAPIENTRY getShadowMatrix(unsigned int pointLightIndex = 0)const;

    /**
     *	Return true if shadow buffer is attached to
     *	light component.
	 *	@Return
     */
	inline bool VDAPIFASTENTRY isShadowBufferAttached(void)const{
		return (this->getShadowTexture() != NULL);
	}


protected:	/*	Internal method.	*/

	/**
	 *	Attach Shadow Buffer Depending on the Shadow Flag and the Light Type
	 *	@Return
	 */
	int VDAPIENTRY attachShadowComponent(unsigned int shadowFlag);

	/**
	 *
	 */
	void VDAPIENTRY detachShadowComponent(void);


public:	/*	Static methods.	*/

	/**
     *	Update all light uniform location to GLSL Shader.
     */
    static void VDAPIENTRY updateLightUniformLocation(VDStackAllocator* allocator = NULL);
  

	/**
	 *	Set Light Uniform Location of Current GameObject Shader.
	 *	This Method will be called if Shader has been changed.
	 */
	static void VDAPIENTRY drawLightAccumulationShadow(VDCamera* camera = NULL);

	/**
	 *	@Return
	 */
	static int VDAPIENTRY lightCount(void);

};

/**
 *
 */
typedef struct vd_engine_light_t{

	/*	*/
	VDVector<int> directIndices;
	/*	*/
	VDVector<int> pointIndices;
	/*	*/
	VDVector<int> spotIndices;
	/*	*/
	VDVector<int> shadowPointIndices;
	VDVector<int> shadowDirectionIndices;
	VDVector<int> shadowSpotIndices;

	/*
	 *	light indices information.
	 */
	VDUniformBuffer lightIndices;

	/*
	 *	light shadow information.
	 */
	VDUniformBuffer shadowbuffer;

	/*
	 *	light information
	 */
	VDUniformBuffer lightbuffer;
}VDEngineLight;

/*
 *
 */
typedef struct vd_engine_light_shadow_t{
	float shadow[4][4];
}VDEngineLightShadow;

/*
 *
 */
typedef struct vd_uniform_light_t{

	/**/
	VDVector3 direction;
	VDColor color;
	VDVector3 position;
	float angle;
	/*	*/
	float intensity;
	float range;
	float shadowStrength;
	float shadowBias;
	int type;

	/*	*/
	int shadowIndex;

}UniformLight;

#endif
