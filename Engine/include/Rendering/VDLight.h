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
		Spot 		= 0x8,			/*	Spot light.	*/
		Direction 	= 0x10,			/*	Direction light.	*/
	};

	enum LightShadow{
		noShadow 		= 0x80,		/*	*/
		HardShadow 		= 0x100,	/*	*/
		SoftShadow 		= 0x200,	/*	*/
		LowShadowQuality 	= 0x200,	/*	*/
		MediumShadowQuality 	= 0x400,	/*	*/
		HighShadowQuality 	= 0x800,	/*	*/
		UltraShadowQuality 	= 0x1000,	/*	*/
		SuperShadowQuality 	= 0x2000,	/*	*/
		ShadowEnable 		= 0x4000,	/*	*/
	};

	enum Attenuation{
		None 		= 0x8000,		/*	*/
		Constant 	= 0x10000,		/*	*/
		Linear 	= 0x20000,		/*	*/
		Quadratic 	= 0x40000,		/*	*/
	};

    VDLight();
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

	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY onDestroy();
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
	inline unsigned int getType()const{
		return this->type;
	}


	/**
     *
	*/
	void VDAPIENTRY setIntensity(float intensity); 

	/**
	 *	@Return
     */
	inline float getIntensity()const{
		return this->intensity;
	}

	/**
     *
     */
    void VDAPIENTRY setColor(const VDColor& color); 

	/**
	 *	@Return
     */
    inline VDColor VDAPIENTRY getColor()const{
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
    inline float VDAPIENTRY getOuterCone()const{
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
    inline float VDAPIENTRY getInnerCone()const{
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
    inline float VDAPIENTRY getRange()const{
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
    inline float VDAPIFASTENTRY getShadowStrenght()const{
    	return this->shadowStrength;
    }

    /**
     *
     */
    void VDAPIFASTENTRY setShadowBias(float bias);

    /**
	 *	@Return
     */
    inline float VDAPIFASTENTRY getShadowBias()const{
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
	int VDAPIENTRY getShadowSize()const;


	/**
	 *	Get Shadow Texture Attach to This Light.
	 *	@Return
	 */
	inline VDRenderTexture* getShadowTexture()const{
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
	inline bool VDAPIFASTENTRY isShadowBufferAttached()const{
		return (this->getShadowTexture() != nullptr);
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
	void VDAPIENTRY detachShadowComponent();


public:	/*	Static methods.	*/

	/**
     *	Update all light uniform location to GLSL Shader.
     */
    static void VDAPIENTRY updateLightUniformLocation(fragcore::StackAllocator* allocator = nullptr);
  

	/**
	 *	Set Light Uniform Location of Current GameObject Shader.
	 *	This Method will be called if Shader has been changed.
	 */
	static void VDAPIENTRY drawLightAccumulationShadow(VDCamera* camera = nullptr);

	/**
	 *	@Return
	 */
	static int VDAPIENTRY lightCount();

};

/**
 *
 */
typedef struct vd_engine_light_t{

	/*	*/
	std::vector<int> directIndices;
	/*	*/
	std::vector<int> pointIndices;
	/*	*/
	std::vector<int> spotIndices;
	/*	*/
	std::vector<int> shadowPointIndices;
	std::vector<int> shadowDirectionIndices;
	std::vector<int> shadowSpotIndices;

	/*
	 *	light indices information.
	 */
	//VDUniformBuffer lightIndices;

	/*
	 *	light shadow information.
	 */
	//VDUniformBuffer shadowbuffer;

	/*
	 *	light information
	 */
	//VDUniformBuffer lightbuffer;
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
