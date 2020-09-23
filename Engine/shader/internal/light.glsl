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

/**
 *
 */
int getNumDirectionLight(void){
	return info.numDirection;
}

/**
 *
 */
int getNumShadowDirectionLight(void){
	return info.numShadowDirection;
}

/**
 *
 */
int getNumSpotLight(void){
	return info.numSpot;
}

/**
 *
 */
int getNumShadowSpotLight(void){
	return info.numShadowSpot;
}

/**
 *
 */
int getNumPointLight(void){
	return info.numPoint;
}

/**
 *
 */
int getNumShadowPointLight(void){
	return info.numShadowPoint;
}



/**
 *
 */
vec4 getDirectionLight(const in vec3 Normal, const in vec3 LightDirection){
	float contribution = max(0.0, dot(Normal, LightDirection) );
	return vec4(contribution);
}



struct light_index{
	ivec4 shadowLight[32];
	ivec4 shadowDirectionLight[32];
	ivec4 shadowSpotLight[32];
	ivec4 shadowPointLight[32];
	ivec4 direction[256];
	ivec4 pointLight[256];
	ivec4 spotLight[256];
};


struct light_shadow{
	mat4 shadowMatrix;
};

struct list_item{
	vec4 direction;
	vec4 color;
	vec4 position;
	float angle;
	float intensity;
	float range;
	float shadowStrength;
	float shadowBias;
	int type;
	int shadowIndex;
	
};


/*	*/
#define eLightDisable 0x2
#define ePointLight 0x4
#define eSpotLight 0x8
#define eDirectionLight 0x10


layout(std140, shared) uniform lightuniform{
	list_item light[64];
};


layout(std140, shared) uniform shadowstructure{
	light_shadow lightShadow[64];
};

layout( std140, shared) uniform lightIndices{
	light_index lightIndex;
};



int getShadowDirectionIndex(const in int index){
	return lightIndex.shadowDirectionLight[index / 4][index % 4];
}
int getShadowPointIndex(const in int index){
	return lightIndex.shadowPointLight[index / 4][index % 4];
}
int getShadowSpotIndex(const in int index){
	return lightIndex.shadowSpotLight[index / 4][index % 4];
}


int getDirectionIndex(const in int index){
	return lightIndex.direction[index / 4][index % 4];
}
int getPointIndex(const in int index){
	return lightIndex.pointLight[index / 4][index % 4];
}
int getSpotIndex(const in int index){
	return lightIndex.spotLight[index / 4][index % 4];
}


float getLightContributionFactor(const in list_item light, in vec3 normalInput){
	float contribution = max(0.0, dot(-normalInput, light.direction.xyz) );
	return contribution;
}


float getSpotLightContributionFactor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
	vec3 deltaSpace = (light.position.xyz - vertexInput);	//TODO resolve this later in the!
	float SpotFactor = dot( normalize(deltaSpace), -normalize(light.direction.xyz) );
	float SpotEffect;
	if(SpotFactor > light.angle ){
		float dist = length(deltaSpace);
		float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
		float contribution = max(0.0, dot(normalInput, normalize(deltaSpace))) * SpotFactor;
		SpotEffect = 1.0;//smoothstep(0.1 , 0.0f, 1.0f - SpotFactor);
		return contribution * SpotEffect * attenuation;
	}
	return 0.0f;
}

vec4 getDirectionLightColor(const in list_item light, const in vec3 normalInput){
	float contribution = getLightContributionFactor(light, normalInput);
	return (contribution * light.color * light.intensity);
}

vec4 getPointLightColor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
	vec3 deltaSpace = (light.position.xyz - vertexInput);
	float dist = length(deltaSpace);
	float contribution = max(0.0, dot(normalInput, normalize(deltaSpace) ) ) ;		
	float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
	attenuation *= attenuation;
	return light.color * contribution  * attenuation * light.intensity;
}

float getPointLightFactor(const in list_item light, const in vec3 normalInput, const in vec3 vertexInput){
	vec3 deltaSpace = (light.position.xyz - vertexInput);
	float dist = length(deltaSpace);
	float contribution = max(0.0, dot(normalInput, normalize(deltaSpace) ) ) ;		
	float attenuation = clamp(1.0 - (dist*dist)/(light.range*light.range), 0.0, 1.0);
	attenuation *= attenuation;
	return contribution  * attenuation * light.intensity;
}


float getIsotropicFactor(in list_item light, const in vec3 normalInput, const in vec3 vertexInput, const float shininessInput){
	float contri;
	contri = dot(reflect(-light.direction.xyz, normalInput) , normalize(vertexInput - getCameraPosition().xyz) );
	contri = max(0.0, contri);
	contri = pow( contri , shininessInput);
	return contri;
}

float getAnsistropicFactor(list_item light, const in vec3 normalInput){
	return 1.0;
}


vec4 getLight(const in vec3 normalInput, const in vec3 vertexInput){
	int x;
	vec4 color = vec4(0);
	float contribution;
	vec3 deltaSpace;
	float dist;
	float attenuation;
	float demon;
	float contri;
	float sha;
	vec4 shadowPos;
	
	for(x = 0; x < info.numShadows; x++){
		int shadowIndex = 0;
		switch(light[shadowIndex].type){
			/*	Direction Light.	*/
			case eDirectionLight:
			/*	shadow factor.	*/
			shadowPos = lightShadow[shadowIndex].shadowMatrix * vec4(vertexInput, 1.0);
			sha = getShadowFactor(shadowPos, shadowIndex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
			/*	final color.	*/
			color += (getDirectionLightColor(light[shadowIndex], normalInput).xyzw * sha);
			break;
		}	
	}
	
	
	
	return color;	
}


vec4 getLightIsotropicSpecular(const in vec3 normalInput, const in vec3 vertexInput, const in float InputShininess, const in vec3 InputSpecularColor){
	int x;
	vec4 color = vec4(0);
	float contribution;
	float contri;
	float sha;
	vec4 shadowPos;
	int matrixindex = 0;
	
	/*	Compute light sources with shadow attached to them.*/
	for(x = 0; x < getNumShadowDirectionLight(); x++){
		int shadowIndex = getShadowDirectionIndex(x);
		
		contri = getIsotropicFactor(light[shadowIndex], normalInput, vertexInput,  InputShininess);
		
		/*	shadow factor.	*/
		matrixindex = light[shadowIndex].shadowIndex;
		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
		sha = getShadow(shadowPos, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
		
		/*	final color.	*/
		color += (getDirectionLightColor(light[shadowIndex], normalInput).xyzw * sha)  + (vec4(InputSpecularColor.rgb  * contri, 0.0) * sha);		
		
	}
	
	
	for(x = 0; x < getNumShadowSpotLight(); x++){
		int shadowIndex = getShadowSpotIndex(x);
		contribution = getSpotLightContributionFactor(light[shadowIndex], normalInput, vertexInput);
		
		matrixindex = light[shadowIndex].shadowIndex;
		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
		sha = getShadow(shadowPos, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
		
		color += sha * contribution * (light[shadowIndex].color);
	}
	
	for(x = 0; x < getNumShadowPointLight(); x++){
		int shadowIndex = getShadowPointIndex(x);
		
		shadowPos = lightShadow[matrixindex].shadowMatrix * vec4(vertexInput, 1.0);
		sha = getCubeShadow(shadowPos, light[shadowIndex].position.xyz, matrixindex, dot(normalInput, -light[shadowIndex].direction.xyz), light[shadowIndex].shadowBias, light[shadowIndex].shadowStrength );
		
		contribution = getPointLightFactor(light[shadowIndex], normalInput, vertexInput);
		contri = getIsotropicFactor(light[shadowIndex], normalInput, vertexInput,  InputShininess);
		
		color += contribution * sha * ( light[shadowIndex].color + vec4(InputSpecularColor * contri, 0.0) );
	}
		
	
	
	/*	*/
	for(x = 0; x < getNumDirectionLight(); x++){
		int ind = getDirectionIndex(x);
		/*	specular.	*/
		contri = getIsotropicFactor(light[ind], normalInput, vertexInput,  InputShininess);
		/*	final color.	*/
		color += (getDirectionLightColor(light[ind], normalInput).xyzw)  + (vec4(InputSpecularColor.rgb  * contri, 0.0));
	}
	
	for(x = 0; x < getNumPointLight(); x++){
		int ind = getPointIndex(x);
		contribution = getPointLightFactor(light[ind], normalInput, vertexInput);
		contri = getIsotropicFactor(light[ind], normalInput, vertexInput,  InputShininess);
		color += contribution * ( light[ind].color + vec4(InputSpecularColor * contri, 0.0) );
	}
	
	for(x = 0; x < getNumSpotLight(); x++){
		int ind = getSpotIndex(x);
		
		contribution = getSpotLightContributionFactor(light[ind], normalInput, vertexInput);
		
		color += contribution * light[ind].color;

		/*
		deltaSpace = (light[ind].position.xyz - vertexInput);	//TODO resolve this later in the!
		float SpotFactor = dot( normalize(deltaSpace), -normalize(light[x].direction.xyz) );
		float SpotEffect;

		if(SpotFactor > light[ind].angle ){
			dist = length(deltaSpace);
			demon = (dist / light[ind].range) + 0.05;
			attenuation = 1.0 / (demon * demon);
			attenuation = max((attenuation - 0.05) / (1 - 0.05),0.0);
			contribution = max(0.0, dot(normalInput, normalize(deltaSpace))) * SpotFactor;
			contri = dot(reflect(-light[ind].direction.xyz, normalInput) , normalize(vertexInput - info.cameraPos.xyz) );
			contri = clamp(contri, 0.0, 1.0);
			contri = pow( contri , InputShininess);
			SpotEffect = smoothstep(0.1 , 0.0f, 1.0f - SpotFactor);
			color += contribution * light[ind].intensity * light[ind].color * SpotEffect * sha + (vec4(InputSpecularColor.rgb  * contri, 0.0) * sha * SpotEffect);
		}
	*/
	}
	return color;
}



/*	ansistropic specular	*/
float getAnsistropicSpecular(in vec3 normalIn, vec3 tangentIN, in vec3 ViewIn, in vec3 LightDirection, in float shininess){

/*
			"	vec3 biNormal = cross(normalize(tangent), Mnormal);\n"
			"	vec3 halfVector = normalize((VertexPosition - CameraPos) + HDirectionLight[x].Direction);\n"
			"	float dotHN = dot(halfVector, HDirectionLight[x].Direction);\n"
			"	float dotVN = dot(normalize(VertexPosition - CameraPos), Mnormal);\n"
			"	float dotHTalphaX = dot(halfVector, normalize(tangent)) / AlphaX;\n"
			"	float dotHTalphaY = dot(halfVector, Mnormal) / AlphaY;	\n";
			switch(lightFunctioName){	// refered to the type of light function.
				case LightFunctioName::eLightSpecularMapped:lightSource += "	EndColor += SpecularColor * sqrt(max(0.0, contribution / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) /(1.0 + dotHN)) * texture2D(SpecularMap, UV).r;\n";break;
				default:lightSource += "	EndColor += SpecularColor * sqrt(max(0.0, contribution / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) /(1.0 + dotHN));\n";break;
			}

*/


/*
	vec3 biNormal = cross(normalIn, tangentIN);
	vec3 halfVector = normalize(ViewIn + LightDirection);
	float dotHN = dot(halfVector, LightDirection);
	float dotVN = dot(ViewIn, normalIn);
	float dotLN = dot(LightDirection, normalIn);
	float dotHTalphaX = dot(halfVector, tangentIn) / AlphaX;
	float dotHTalphaY = dot(halfVector, biNormal) / AlphaY;	
	return (sqrt(max(0.0, dotLN / dotVN)) * exp(-2.0 *(dotHTalphaX * dotHTalphaX + dotHTalphaY *dotHTalphaY) ) ) /(1.0 + dotHN);
	*/
	return 0.0f;
}

vec4 getLightSubSurface(const in vec3 normalInput, const in vec3 vertexInput, const in float InputShininess, const in vec3 InputSpecularColor){
	return vec4(1.0);
}
