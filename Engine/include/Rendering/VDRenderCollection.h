/**
    Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _VD_RENDER_COLLECTION_H_
#define _VD_RENDER_COLLECTION_H_ 1
#include "../VDSystem.h"

/**
 *
 */
typedef vector<VDRenderer*> VDRendererArray;
typedef struct render_Collection_index{

	VDMaterial* index;			/*	material	*/
	VDRendererArray renderers;	/*	renderer array.	*/

}MaterialRendererArray;


/*
 *
 */
typedef std::map<VDGUID, MaterialRendererArray> MaterialRendererArrayCollection;
typedef struct render_collection_index_tmp{

	MaterialRendererArrayCollection collec;		/*	*/

}RenderCollectionMaterialHeap;

/*
 *
 */
typedef std::map<unsigned int, RenderCollectionMaterialHeap> LightTransmissionObjectType;
typedef struct render_collection_index2{
	LightTransmissionObjectType materialType;	/**/
}RenderCollectionHeap;

typedef std::map<unsigned int, RenderCollectionHeap> RenderCollection;
extern VDDECLSPEC RenderCollection rendercollection;

/**
 *	Contains rendering data for the
 *	rendering pipline.
 */
class VDDECLSPEC VDRenderCollection{
public:

	/*
	 *
	 */
	enum MaterialProperties{
		eTranslucent = VDShader::eShaderTranslucent,	/*	*/
		eOpaque = VDShader::eShaderOpaque,				/*	*/
	};

	/**
	 *	@Return render collection.
	 */
	inline static RenderCollection& getRenderCollection(void){
		return rendercollection;
	}

	/*
	 *
	 *	@Return
	 */
	inline static RenderCollection::iterator getRenderCollectionIt(void){
		return rendercollection.begin();
	}


	/**
	 *
	 *	@Return
	 */
	inline static RenderCollectionHeap& getRenderType(unsigned int type){
		return rendercollection[type];
	}

	/*
	 *
	 *	@Return
	 */
	inline static LightTransmissionObjectType::iterator getRenderTypeIt(unsigned int type){
		return rendercollection[type].materialType.begin();
	}

	inline static RenderCollectionMaterialHeap& getRenderColorType(unsigned int renderype, MaterialProperties object){
		return rendercollection[renderype].materialType[object];
	}

	inline static MaterialRendererArrayCollection::iterator getRenderColorTypeIt(unsigned int renderype, MaterialProperties object){
		return rendercollection[renderype].materialType[object].collec.begin();
	}


	inline static unsigned int getRenderColorTypeNumRenderers(unsigned int renderType, MaterialProperties object){
		unsigned int num = 0;
		MaterialRendererArrayCollection::iterator it = getRenderColorTypeIt(renderType,object);
		while(it != getRenderColorType(renderType,object).collec.end()){
			num += it->second.renderers.size();
			it++;
		}
		return num;
	}


	/**/
	inline static MaterialRendererArray& getRenderColorType2(unsigned int renderype, MaterialProperties object, unsigned int guid){
		return rendercollection[renderype].materialType[object].collec[(VDGUID)guid];
	}



	/*
	 *
	 */
	static RenderCollectionMaterialHeap& getRenderHeap(unsigned int rendertype, VDMaterial* material);
	static VDRendererArray& getRenderArray(unsigned int rendertype, VDMaterial* material);


	/*
	 *
	 */
	static void addObjectFromCollection(VDRenderer* renderer, VDMaterial* material);
	static void removeObjectFromCollection(VDRenderer* renderer, VDMaterial* material);
	static void removeObjectFromCollection(VDRenderer* renderer, VDMaterial* material, unsigned int renderType);


	/*
	 *
	 */
	static void replace(VDRenderer* renderer, unsigned int oldRenderType, unsigned int newRenderType, VDMaterial* material);


	inline static int numRenderer(void){return 0;}
};
#endif
