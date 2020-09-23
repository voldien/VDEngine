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
#ifndef _VD_MATERIAL_H_
#define _VD_MATERIAL_H_ 1
#include"Texture/VDTexture2D.h"
#include"VDShader.h"

/**
 *
 */
class VDDECLSPEC VDMaterial : public VDAssetObject{
protected:

	VDMaterial(void);
	VDMaterial(const VDMaterial& material);
	VDMaterial(VDShader* shader);
public:
	~VDMaterial(void);

	VDMaterial& operator=(const VDMaterial& material);

	/**
	 *	release Reference of Resource assoication with
	 *	this Material.
	 */
	virtual void VDAPIENTRY release(void);

private:	/*	Attributes.	*/

	VDShader* shader;		/*	Shader associated with material.	*/
	VDTexture* textures[16];	/*	Textures.	*/

public:	/*	*/

	/**
	 *
	 */
	void VDAPIFASTENTRY setShader(VDShader* shader);

	/**
	 *
	 */
	VDShader* VDAPIFASTENTRY getShader(void)const;

	/**
	 *	bind Material Properties Association with this
	 *	Material. Shader Program won't be binded.
	 */
	void VDAPIFASTENTRY bindProperties(void);

	/**
	 *	Bind shader with properties associated with material
	 */
	void VDAPIFASTENTRY bind(void);

	/**
	 *
	 */
	void VDAPIENTRY setTexture(int index, VDTexture* texture);

	/**
	 *
	 *	@Return
	 */
	VDTexture2D* VDAPIFASTENTRY getTexture(const char* samplename);

	/**
	 *
	 *	@Return
	 */
	VDTexture2D* VDAPIFASTENTRY getTexture(int IndexSampler);

	/**
	 *
	 *	Set Texture Sampler Offset.
	 */
	void VDAPIENTRY setTextureOffset(const char* sample,const VDVector2& offset);

	/**
	 *	Set Texture Sampler Tile.
	 */
	void VDAPIENTRY setTextureTile(const char* sample,const VDVector2& tile);


	/**
	 *	Get Texture Sampler Offset.
	 *
	 *	@Return
	 */
	VDVector2 VDAPIENTRY getTextureOffset(const char* sample);

	/**
	 *	Get Texture Sampler Tile.
	 *
	 *	@Return
	 */
	VDVector2 VDAPIENTRY getTextureTile(const char* sample);


	/**
	 *
	 */
	void VDAPIENTRY setVec2(const char* uniformName, const VDVector2& vec2);

	/*
	 *
	 */
	void VDAPIENTRY setVec2(const char* uniformName, float x, float y);

	/*
	 *
	 */
	void VDAPIENTRY setVec2v(const char* uniformName, unsigned int count, const VDVector2* vector);

	/**
	 *
	 *	@Return
	 */
	VDVector2 VDAPIENTRY getVec2(const char* uniformName);

	/**
	 *
	 *	@Return
	 */
	VDVector2* VDAPIENTRY getVec2v(const char* uniformName, unsigned int  IndexOffset, unsigned int  Count);


	/**
	 *
	 */
	void VDAPIENTRY setVec3(const char* uniformName, const VDVector3& vec3);

	/**
	 *
	 */
	void VDAPIENTRY setVec3(const char* uniformName, float x, float y, float z);

	/*
	 *
	 */
	void VDAPIENTRY SetVec3v(const char* uniformName, unsigned int count, const VDVector3* vector);

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getVec3(const char* uniformName);

	/*
	 *
	 *	@Return
	 */
	VDVector3* VDAPIENTRY getVec3v(const char* uniformName, unsigned int indexOffset, unsigned int Count);


	/*
	 *
	 */
	void VDAPIENTRY setVec4(const char* uniformName, const VDVector4& vec4);

	/*
	 *
	 */
	void VDAPIENTRY setVec4(const char* uniformName, float x, float y, float z, float w);

	/*
	 *
	 */
	void VDAPIENTRY SetVec4v(const char* uniformName, unsigned int count, const VDVector4* vector);

	/*
	 *
	 */
	VDVector4 VDAPIENTRY getVec4(const char* uniformName);

	/*
	 *
	 */
	VDVector4* VDAPIENTRY getVec4v(const char* uniformName, unsigned int IndexOffset, unsigned int Count);


	/**
	 *
	 */
	void VDAPIENTRY setColor(const char* uniformName,const VDColor& color);
	void VDAPIENTRY setColor(const char* uniformName, float red, float green, float blue, float alpha);
	inline void VDAPIENTRY setColorv(const char* uniformName,unsigned int  count, const VDColor* vector){this->SetVec4v(uniformName, count, (VDVector4*)vector);}
	VDColor VDAPIENTRY getColor(const char* uniformName);
	inline VDColor* VDAPIENTRY getColorv(const char* uniformName, unsigned int  IndexOffset, unsigned int  Count){return (VDColor*)this->getVec4v(uniformName, IndexOffset,Count);}


	/**
	 *
	 */
	void VDAPIENTRY setDouble(const char* uniformName, double value);
	void VDAPIENTRY setDoublev(const char* uniformName, unsigned int  count, const double* pValue);
	double VDAPIENTRY getDouble(const char* uniformName);
	double* VDAPIENTRY getDoublev(const char* uniformName, unsigned int  indexOffset, unsigned int  count);
	void VDAPIENTRY getDoublev(const char* uniformName, unsigned int  indexOffset, unsigned int  count,double *pValue);


	/**
	 *	int
	 */
	void VDAPIENTRY setBool(const char* uniformName, int value);
	void VDAPIENTRY SetBoolv(const char* uniformName, unsigned int count, const int* pValue);
	int VDAPIENTRY getBool(const char* uniformName);
	int* VDAPIENTRY getBoolv(const char* uniformName, unsigned int indexOffset, unsigned int count);
	void VDAPIENTRY getBoolv(const char* uniformName, unsigned int indexOffset, unsigned int count,int *pValue);


	/**
	 *
	 */
	void VDAPIENTRY setfloat(const char* cuniformName, float value);
	void VDAPIENTRY setfloatv(const char* cuniformName, unsigned int count, float* pValue);
	float VDAPIENTRY getfloat(const char* cuniformName);
	float* VDAPIENTRY getfloatv(const char* uniformName, unsigned int indexOffset, unsigned int count);
	void VDAPIENTRY getfloatv(const char* uniformName, unsigned int indexOffset, unsigned int count,float *pValue);

	/**
	 *
	 */
	void VDAPIENTRY setInt(const char* uniformName, int value);
	void VDAPIENTRY setInt(const char* uniformName, unsigned int index, int Value);
	void VDAPIENTRY setIntv(const char* uniformName, unsigned int count, const int* pValue);
	int VDAPIENTRY getInt(const char* uniformName);
	int* VDAPIENTRY getInt(const char* uniformName, unsigned int indexOffset, unsigned int count);
	void VDAPIENTRY getInt(const char* uniformName, unsigned int indexOffset, unsigned int count,int *pValue);

	/*  */
	void VDAPIENTRY setMatrix4(const char* uniformName, const VDMatrix4x4& matrix);
	void VDAPIENTRY setMatrix4v(const char* uniformName, float*matrixs, unsigned int Count);


	/*  Matrix Of double as Sub Component.
	 */
	void VDAPIENTRY SetDMatrix4(const char* uniformName, const VDMatrix4x4& matrix);
	void VDAPIENTRY SetDMatrix4v(const char* uniformName,float*matrixs, unsigned int Count);
	
	
	/**
	 *
	 */
	VDMatrix4x4 VDAPIENTRY getMatrix4(const char* uniformName);

	/**
	 *
	 */
	std::vector<VDMatrix4x4> VDAPIENTRY getMatrix4v(const char* uniformName, unsigned int count);


	/*
	 *	Sets the material as an opaque material.
	 */
	void VDAPIFASTENTRY setOpaque(void);

	/**
	 *
	 *
	 */
	void VDAPIFASTENTRY setTranslucent(void);



public:	/*	*/

	/**
	 *	@Return
	 */
	inline bool isTranslucent(void)const{return this->getShader()->isFlagSet(VDShader::eShaderTranslucent); }

	/**
	 *
	 *	@Return
	 */
	inline bool isOpaque(void)const{return this->getShader()->isFlagSet(VDShader::eShaderOpaque); }

	/*
	 *
	 */
	inline bool isTessellation(void)const{return this->getShader()->isFlagSet( VDShader::eTessellationEvaulation | VDShader::eTessellationControl );}


	/*
	 *
	 */
	inline bool useStencil(void)const{
		return getShader()->isFlagSet(0x01);
	}

	/*
	 *
	 */
	inline bool isFrontCulling(void)const{
		return this->getShader()->isFlagSet(VDShader::eFrontCulling);;
	}

	/*
	 *
	 */
	inline bool isBackCulling(void)const{
		return this->getShader()->isFlagSet(VDShader::eBackCulling);
	}

	/*
	 *
	 */
	inline bool isFrontBackCulling(void)const{
		return this->getShader()->isFlagSet( VDShader::eBothCulling);
	}


	/*
	 *
	 */
	void VDAPIFASTENTRY setCullingSupport(unsigned long int cullingMode){
		this->getShader()->setFlag( (this->getShader()->getFlagSet() & ~(VDShader::eBothCulling | VDShader::eBackCulling | VDShader::eFrontCulling) ) | cullingMode );
	}

public :	/*	Static methods.	*/

	/**
	 *	Create material object.
	 *
	 *	@Return non null if succesfully.
	 */
	static VDMaterial* VDAPIENTRY createMaterial(void);

	/**
	 *
	 *	@Return
	 */
	static VDMaterial* VDAPIENTRY createMaterial(VDShader* shader);

	/**
	 *	Create a defualt Material. Defualt Material use
	 *	preset [High Quality Default Material || Low Quality Default Material]
	 *	@Return
	 */
	static VDMaterial* VDAPIENTRY createDefaultMaterial(unsigned int preset = 0);

	/**
	 *
	 */
	static VDMaterial VDAPIENTRY findMaterial(const char* cname);

	/**
	 *	get Default Material
	 *	@Return non-null material object.
	 */
	static VDMaterial* VDAPIFASTENTRY getDefaultMaterial(void);

	/**
	 *	Get Defualt Material texture.
	 *	@Return non-null texture object.
	 */
	static VDTexture2D* VDAPIFASTENTRY getDefaultTexture(void);

};

/*	TODO relocate to somewhere else.*/
extern VDDECLSPEC VDMaterial* gDefaulMaterial;
extern VDDECLSPEC VDTexture2D* resourceErrorTexture;
extern VDDECLSPEC VDTexture2D debugTexture;

#endif
