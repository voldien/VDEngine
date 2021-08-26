#line 1
/**
    VDEngine common built-in shader functions.
    Copyright (C) 2015  Valdemar Lindberg

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

/*	*/
#ifdef GL_ES
	precision mediump float;
	precision mediump int;
#endif

/*	Translate fragment location decleration based on what version.	*/
#if __VERSION__ > 130
	#define FRAGLOCATION(x, vtype, name) layout(location = x) out vtype name
#elif __VERSION__ == 130
	#define FRAGLOCATION(x, vtype, name) out vtype name
#else
	#define FRAGLOCATION(x)
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 130
	#define ATTRIBUTE_IN(x) layout(location = x) in
	#define ATTRIBUTE_OUT(x) layout(location = x) out
#else
	#define ATTRIBUTE_IN(x) attribute
	#define ATTRIBUTE_OUT(x) attribute
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 120
	#define OUT out
	#define SMOOTH_OUT smooth out
	#define FLAT_OUT flat out
	#define IN in
	#define SMOOTH_IN smooth in
	#define FLAT_IN flat in
#else
	#define OUT varying
	#define SMOOTH_OUT smooth varying
	#define FLAT_IN flat varying
	#define IN varying
	#define SMOOTH_IN smooth varying
	#define FLAT_IN flat varying
#endif

/*	*/
#ifndef VD_ENGINE
	#define VD_ENGINE 1

	#ifdef GL_ES
	precision mediump float;
	#endif
#endif

struct shareinfo{
	vec4 ambientColor;
	vec4 cameraPos;
	vec4 cameraDir;
	float cameraNear;
	float cameraFar;
	vec2 screenRes;
	float timescale;
	float time;
	float deltaTime;
	int numLights;
	int maxLights;
	int xpos;
	int ypos;
	int numShadows;
	int shadow;
	mat4 projection;
	mat4 viewMatrix;
	mat4 viewProjection;
	int numDirection;
	int numSpot;
	int numPoint;
	int numShadowDirection;
	int numShadowSpot;
	int numShadowPoint;
	int ambientType;
	float ambientIntensity;
	vec4 fogColor;
	float fogStart;
	float fogEnd;
	float fogHeight;
	int fogType;
	float fogDensity;
};

#if __VERSION__ > 130
	layout(std140, shared) uniform enginestate {
		shareinfo info;
	};
#else
	uniform global_uniform global;
#endif

/**
 *	Get exp function to linear.
 */
float getExpToLinear(const in float start, const in float end, const in float expValue){
	return ((2.0f * start) / (end + start  - expValue * (end - start)));
}

/**
 *	Invert color.
 */
vec3 invertColor(const in sampler2D texture,const in vec2 UV){
	return invertColor(texture2D(texture,UV).rgba));
}

vec4 invertColor(const in vec4 c1){
	return 1.0 - c1;
}

/**
 *	Convert color to gray scal .
 */
float grayScaleColor(const in sampler2D texture, const in vec2 uv){
	return dot(texture2D(texture, uv).xyz, vec3(0.29f, 0.59f, 0.12f));
}

#if GL_compatibility_profile == 1
	#if __VERSION__ >= 420
	sampler2D getTextureArraySampler(const in sampler2D[64] textureArray, const in int index){
		return textureArray[index];
	}
	#else
	sampler2D getTextureArraySampler(const in sampler2D[64] textureArray, const in int index){
		switch(index){
		case 0:return textureArray[0];
		case 1:return textureArray[1];
		case 2:return textureArray[2];
		case 3:return textureArray[3];
		case 4:return textureArray[4];
		case 5:return textureArray[5];
		case 6:return textureArray[6];
		case 7:return textureArray[7];
		default:return textureArray[0];
		}
	}
	#endif
#endif

/*'
 *	Compute chromatic reflection.
 */
vec4 getChromaticReflection(const in samplerCube ReflectionTexture, const in vec3 CameraEye,const in vec3 Reflection,const in vec3 TRed,const in vec3 TGreen,const in vec3 TBlue,const in float refFactor){
	vec4 reflectedColor = texture(ReflectionTexture,Reflection);
	vec4 refractedColor;
	refractedColor.r = texture(ReflectionTexture, TRed).r;
	refractedColor.g = texture(ReflectionTexture, TGreen).g;
	refractedColor.b = texture(ReflectionTexture, TBlue).b;
	refractedColor.a = 1.0f;
	return mix(refractedColor,reflectedColor,refFactor);
}

/*
|=======================================|
|										|
|=======================================|
*/

uniform samplerCube ambientCube;		/*	Image based ambient lightning*/

#define eAmbientConstant	0x1			/**/
#define eAmbientImageBased 	0x2			/**/

/**
 *	Get ambient color.
 */
vec4 getAmbientColor(void){
	return info.ambientColor;
}

/**
 *	Get ambient cubemap color.
 */
vec4 getAmbientCubeMapColor(const in vec3 inputNormal){
	return texture(ambientCube, inputNormal) * getAmbientColor() * vec4(info.ambientIntensity);
}

/**
 *	Get ambient constant color.
 */
vec4 getAmbientConstantColor(const in vec3 inputNormal){
	return getAmbientColor();
}

/**
 *	Compute ambient color.
 */
vec4 getAmbient(const in vec3 inputNormal){
	switch(info.ambientType){
		case eAmbientConstant:
			return getAmbientColor();
		case eAmbientImageBased:
			return getAmbientCubeMapColor(inputNormal);
		default:
			return vec4(0.0);
	}
}


/**
 *	Get current time.
 */
float getTime(void){
	return info.time;
}

/**
 *	Get delta time.
 */
float getDeltaTime(void){
	return info.deltaTime;
}

/**
 *	Get screen resolution in
 *	pixels.
 */
vec2 getScreen(void){
	return info.screenRes;
}

/**
 *	Get UV coordinate of
 *	the screen.
 */
vec2 getScreenUV(void){
#if VD_FRAGMENT_SHADER
	return gl_FragCoord.xy / getScreen();
#else
	return vec2(0);
#endif
}

/**
 * Get current camera position
 * in world space.
 */
vec3 getCameraPosition(void){
	return info.cameraPos.xyz;
}

/**
 *	Get current camera forward direction.
 */
vec3 getCameraDirection(void){
	return info.cameraDir.xyz;
}

/**
 *	Get current camera's
 *	near distance.
 */
float getCameraNear(void){
	return info.cameraNear;
}

/**
 *	Get current camera's
 *	far distance.
 */
float getCameraFar(void){
	return info.cameraFar;
}

/**
 *
 */
mat4 getViewMatrix(void){
	return info.viewMatrix;
}

/**
 *
 */
mat4 getProjectionMatrix(void){
	return info.projection;
}

/**
 *
 */
mat4 getViewProjectionMatrix(void){
	return info.viewProjection;
}


#define FOGLINEAR	0x1	/*	*/
#define FOGEXP		0x2	/*	*/
#define FOGEXP2		0x3	/*	*/
#define FOGHEIGHT	0x4	/*	*/

float getFogFactor(void){

	float near = getCameraNear();
	float far = getCameraFar();
	int fogtype = info.fogType;
	float endFog = info.fogEnd / (far - near);
	float startFog = info.fogStart  / (far - near);
	float densityFog =  info.fogDensity;
	/*	z normalized.	*/
	#ifdef VD_FRAGMENT_SHADER
	float z = getExpToLinear(near, far, gl_FragCoord.z );
	#else
	float z = 1.0;
	#endif

	switch(fogtype){
	case 1:
		return 1.0 - clamp( (endFog - z) / (endFog - startFog), 0.0, 1.0 );
	case 2:
		return 1.0 - clamp( exp( -(densityFog * z) ), 0.0, 1.0);
	case 3:
		return 1.0 - clamp( exp( - ( densityFog * z * densityFog * z) ) , 0.0, 1.0);
	case 4:
		float dist = z * (far - near);
		float b = 0.5;
		float c = 0.9;
	 	return clamp( c*exp(-getCameraPosition().y*b)*(1.0-exp(-dist*getCameraDirection().y*b))/getCameraDirection().y, 0.0, 1.0);
	default:
		return 0.0;
	}
}

/**
 *	Compute fog.
 */
vec4 internalFog(const in vec4 initColor){
	vec4 fogColor = info.fogColor;
	return  mix(initColor, fogColor, getFogFactor() ).rgba;
}
