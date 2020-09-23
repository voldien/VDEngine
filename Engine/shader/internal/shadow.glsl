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


/**/
#if __VERSION__ >= 420 && defined(VD_FRAGMENT_SHADER) && defined(VD_ENGINE)
	layout(early_fragment_tests) in;
#endif

/**/
#if __VERSION__ >= 420
	#define VD_BINDING_POINTS
#endif



/*	Extensions	*/
//#extension GPU_shader4 : enable
//#extension GPU_shader5 : enable


/*	*/
uniform sampler2D DepthTexture;


/*
	Shadows	
*/
#if defined(USE_SHADOWS)

#endif

uniform samplerCubeShadow ShadowCube[2];		/*	TODO */
uniform sampler2DShadow ShadowSampler[8];		/**/

/*	*/
//uniform samplerBuffer lightbuffer;			/**/



#if __VERSION__ >= 400
float getCubeShadowSampling(const in int index, const in vec4 projectcoord){
	return texture(ShadowCube[index], projectcoord);
}
#else
float getCubeShadowSampling(const in int index, const in vec4 projectcoord){
	switch(index){
		case 0:
			return texture(ShadowCube[0], projectcoord);
		case 1:
			return texture(ShadowCube[1], projectcoord);
		default:
			return 0.0;
	}
}
#endif



#if __VERSION__ >= 400
float getShadowSampling(const in int index, const in vec4 projectcoord){
	return textureProj(ShadowSampler[index], projectcoord);
}
#else
float getShadowSampling(const in int index, const in vec4 projectcoord){
	switch(index){
		case 0:
			return textureProj(ShadowSampler[0], projectcoord);
		case 1:
			return textureProj(ShadowSampler[1], projectcoord);
		case 2:
			return textureProj(ShadowSampler[2], projectcoord);
		case 3:
			return textureProj(ShadowSampler[3], projectcoord);
		case 4:
			return textureProj(ShadowSampler[4], projectcoord);
		case 5:
			return textureProj(ShadowSampler[5], projectcoord);
		case 6:
			return textureProj(ShadowSampler[6], projectcoord);
		case 7:
			return textureProj(ShadowSampler[7], projectcoord);
		default:
			return 0.0;
	}
}
#endif




/*
=================================================================================================
					Shadow Implementation					
=================================================================================================
*/
#if __VERSION__ >= 400
subroutine float getCubeShadowMap(const in vec4 LightVertexPosition, const in vec3 lightPos, const in int samplerindex, const in float costTheta, const in float Inputbias, const in float strength);
subroutine float getShadowType(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength);
#endif


#if __VERSION__ >= 400
subroutine(getShadowType)
#endif
float getShadowFactor(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){
	
	float visibility = 1.0;
	if(LightVertexPosition.w > 0.0){
		vec4 ProjCoords = LightVertexPosition / LightVertexPosition.w;
		float bias = tan(acos(cosTheta));
		bias = clamp(bias, 0.000, 0.005); /*	Inputbias * */
		ProjCoords.z *= (1 - bias);
		visibility = getShadowSampling(samplerindex, ProjCoords);
		
		/*	determine the final shadow factor.	*/
		return clamp((1 - strength) + visibility, 0.0, 1.0);
	}
	return visibility;
}


const vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

#if __VERSION__ >= 400
subroutine(getShadowType)
#endif
float getShadowFactorPCF(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){

	if(LightVertexPosition.w > 0.0){
		float visibility = 1.0;
		vec4 ProjCoords = LightVertexPosition / LightVertexPosition.w;			
		float bias = Inputbias * tan(acos(cosTheta));
		bias = clamp(bias, 0.0, 0.005);
		float shadowCoef = 0;
				
		for(int i=0; i<16; i++) {
		#ifdef VD_FRAGMENT_SHADER
			float indexA = (random(vec4(gl_FragCoord.xyx, i))*0.25);
			float indexB = (random(vec4(gl_FragCoord.yxy, i))*0.25);
		#else
			float indexA = 0;
			float indexB = 0;
		#endif 
			ProjCoords.z *= (1 - bias);
			shadowCoef += getShadowSampling(samplerindex, ProjCoords + vec4(indexA, indexB,0, 0) * 0.0085 );
		}
		shadowCoef *= (1.0 / 16.0);
	
		return clamp((1 - strength) + shadowCoef, 0.0, 1.0);
	}
	return 1.0f;
}

#if __VERSION__ >= 400
subroutine (getShadowType)
#endif 
float getVarianceShadow(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){	
/*
	if(LightVertexPosition.w > 1.0){
		float visibility = 1.0;
		vec3 uv = LightVertexPosition.xyz / LightVertexPosition.w;
		float depth = uv.z;
		vec4 moments = texture(ShadowMap, uv.xyz).rgba;
		float E_x2 = moments.y;
		float Ex_2 = moments.x;
		float var = E_x2 - Ex_2;
		var = max (var, 0.00002);
		float mD = depth - moments.x;
		float mD_2 = mD * mD;
		float p_ma = var/(var + mD_2);
		
		visibility = max(p_ma, (depth<=moments.x) ? 1.0 : 0.0);
		
		visibility = (1.0 - visibility);
		if(uv.z > 1.0)
			visibility = 1.0;
		 
		return visibility;
	}
*/
	return 1.0;
}

#if __VERSION__ >= 400
subroutine (getShadowType)
#endif 
float getNoneShadow(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){
	return 1.0;
}

#if __VERSION__ >= 300 && __VERSION__ < 400
#define eSimple 0x2
#define ePCF 0x4
#define eVariance 0x8

float getShadow(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){

	switch(info.shadow){
		case eSimple:
			return getShadowFactor(LightVertexPosition, samplerindex, cosTheta, Inputbias, strength);		
		case ePCF:
			return getShadowFactorPCF(LightVertexPosition, samplerindex, cosTheta, Inputbias, strength);
		case eVariance:
			return getVarianceShadow(LightVertexPosition, samplerindex, cosTheta, Inputbias, strength);
		default:
			return getNoneShadow(LightVertexPosition, samplerindex, cosTheta, Inputbias, strength);
	}
}
#elif __VERSION__ < 300
float getShadow(const in vec4 LightVertexPosition, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){
	return 1.0;
}
#endif


float VectorToDepthValue(vec3 Vec){
    vec3 AbsVec = abs(Vec);
    float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));

    float f = 80;
    float n = 0.5;
    float NormZComp = (f+n) / (f-n) - (2*f*n)/(f-n)/LocalZcomp;
    return (NormZComp + 1.0) * 0.5;
}


/**
 *	Cube shadow mapping.
 */
#if __VERSION__ >= 400
subroutine (getCubeShadowMap)
#endif 
float getShadowCubeFactor(const in vec4 LightVertexPosition, const in vec3 lightPos, const in int samplerindex, const in float costTheta, const in float Inputbias, const in float strength){
	float visibility = 1.0;
	 
	if(LightVertexPosition.w > 0.0){
	
		vec4 ProjCoords = LightVertexPosition / LightVertexPosition.w;
	
		float mdepth = VectorToDepthValue(ProjCoords.xyz - lightPos);
			
		visibility = getCubeShadowSampling(samplerindex, vec4(ProjCoords.xyz,1.0));
		
		
		if(visibility < mdepth){
			visibility = 0;
			//visibility = (1.0 - strength);
		}else{
			visibility = 1.0;
		}
		
		if(ProjCoords.z > 1.0)
			visibility = 1.0;
			
		return visibility;
	}
	return visibility;
}

#if __VERSION__ >= 400
subroutine (getCubeShadowMap)
#endif 
float getShadowCubeFactorPCF(const in vec4 LightVertexPosition, const in vec3 lightPos, const in int samplerindex, const in float costTheta, const in float Inputbias, const in float strength){
	return 1.0;
}

#if __VERSION__ >= 400
subroutine (getCubeShadowMap)
#endif 
float getShadowCubeFactorVariance(const in vec4 LightVertexPosition, const in vec3 lightPos, const in int samplerindex, const in float costTheta, const in float Inputbias, const in float strength){
	return 1.0;
}



#if __VERSION__ >= 300 && __VERSION__ < 400

float getCubeShadow(const in vec4 LightVertexPosition, const in vec3 lightPos, const in int samplerindex, const in float cosTheta, const in float Inputbias, const in float strength){
	
	switch(info.shadow){
		case eSimple:
			return getShadowCubeFactor(LightVertexPosition, lightPos, samplerindex, cosTheta, Inputbias, strength);		
		case ePCF:
			return getShadowCubeFactorPCF(LightVertexPosition, lightPos, samplerindex, cosTheta, Inputbias, strength);
		case eVariance:
			return getShadowCubeFactorVariance(LightVertexPosition, lightPos, samplerindex, cosTheta, Inputbias, strength);
		default:
			return 1.0;
	}

}
#endif

#if __VERSION__ > 400
subroutine uniform getShadowType getShadow;
subroutine uniform getCubeShadowMap getCubeShadow; 
#endif

