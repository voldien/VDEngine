#include <Core/VDDebug.h>
#include <Core/VDGUID.h>
#include <Core/VDObject.h>
#include <DataStructure/VDVector.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderCollection.h>
#include <map>

RenderCollectionMaterialHeap& VDRenderCollection::getRenderHeap(unsigned int rendertype, VDMaterial* material){
	if(material->isOpaque())
		return VDRenderCollection::getRenderColorType(rendertype, VDRenderCollection::eOpaque);
	else
		return VDRenderCollection::getRenderColorType(rendertype, VDRenderCollection::eTranslucent );
}

VDRendererArray& VDRenderCollection::getRenderArray(unsigned int rendertype, VDMaterial* material){
	RenderCollectionMaterialHeap* heap;
	if(material->isOpaque())
		heap = &VDRenderCollection::getRenderColorType(rendertype, VDRenderCollection::eOpaque);
	else
		heap = &VDRenderCollection::getRenderColorType(rendertype, VDRenderCollection::eTranslucent );

	return heap->collec[(VDGUID)material->getInstanceID()].renderers;
}

void VDRenderCollection::removeObjectFromCollection(VDRenderer* renderer, VDMaterial* material){
	VDRenderCollection::removeObjectFromCollection(renderer, material, renderer->getRenderType());
}

void VDRenderCollection::removeObjectFromCollection(VDRenderer* renderer, VDMaterial* material, unsigned int renderType){
	VDRendererArray* array = &getRenderArray(renderType, material);
	RenderCollectionMaterialHeap& heap = getRenderHeap(renderType, material);

	if(array && array->isValid()){
		/*	find the renderer in the vector class.	*/
		for(int x = 0; x < array->size(); x++){
			if( (*array)[x] == renderer)
				array->remove(x);
		}
		if(array->size() == 0){
			MaterialRendererArrayCollection::iterator it = heap.collec.find((VDGUID)material->getInstanceID());
			heap.collec.erase(it);
		}

	}
	else{
		VDDebug::errorLog("Failed to find material by name : %s. \n", material->getName());
	}
}

void VDRenderCollection::replace(VDRenderer* renderer, unsigned int oldRenderType, unsigned int newRenderType, VDMaterial* material){
	VDRendererArray* array = &VDRenderCollection::getRenderArray(oldRenderType, material);
	if(array){
		VDRenderCollection::removeObjectFromCollection(renderer, material, oldRenderType);


		if(material->isOpaque())
			getRenderColorType(newRenderType, VDRenderCollection::eOpaque).collec[(VDGUID)material->getInstanceID()].renderers.push(renderer);
		else
			getRenderColorType(newRenderType, VDRenderCollection::eTranslucent).collec[(VDGUID)material->getInstanceID()].renderers.push(renderer);
	}
	else{
		VDDebug::errorLog("Failed to find material by name : %s. \n", material->getName());
	}

}
