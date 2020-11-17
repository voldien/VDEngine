#include <Asset/VDAssetManager.h>
#include <Asset/VDAssetObject.h>
#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDObject.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>
#include <climits>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>

char* VDAssetManager::rootpath = NULL;
VDAssetManager::RegistryTable VDAssetManager::assetreg;

const char* VDAssetManager::getRootDirectory(void) {
	return VDAssetManager::rootpath;
}

void VDAssetManager::setRootDirectory(const char* cpath) {
	char buffer[PATH_MAX];
	const char* cRootPath = cpath;
	if (!cpath) {
		//SDL_GetBasePath();
		//ExGetAppliationPath(buffer, sizeof(buffer));
		//cRootPath = &buffer[0];
	}

	/*	TODO resolve.
	 if(!ExIsDirectory(cpath)){
	 VDDebug::errorLog("%s is not a directory\n", cRootPath);
	 return;
	 }
	 */

	rootpath = (char*) realloc(rootpath, strlen(cpath) + 1);
	memset(rootpath, '\0', strlen(cpath));
	memcpy(rootpath, cpath, strlen(cpath));
	VDDebug::log("Set root directory : %s\n", cpath);
}

char* VDAssetManager::getAbsolutePath(const char* relativePath, char* buffer,
		int len) {
	if (!buffer) {
		return NULL;
	}
	// if (!VDFile::isRelativePath(relativePath)) {
	// 	return (char*) relativePath;
	// }

	sprintf(buffer, "%s/%s", getRootDirectory(), relativePath);
	//memmove(relativePath + strlen(getRootDirectory()) , relativePath, strlen(getRootDirectory())  );
	return buffer;
}


std::string VDAssetManager::getResourcePath(ResourceType type) {
	char path[PATH_MAX];
	char tmp[PATH_MAX];
	const char* appname;

	const unsigned int len = sizeof(path);
	appname = VDSystemInfo::getAppliationName();
	char* env = NULL;

	if (VDSystemInfo::operatingSystem() & VDSystemInfo::eUnix) {
		switch (type) {
		case ResourceType::eConfig:
			// env = SDL_getenv("USER");
			// sprintf(path, "/home/%s/.vdengine/%s/engine.conf", env, appname);
			break;
		case ResourceType::eConfigInternal:

			break;
		case ResourceType::eShaderPath: {
			if (!VDDebug::isDebugBuild()) {
				const char* shaderpath = "/usr/share/vdengine/shader";
				memcpy(path, shaderpath, strlen(shaderpath) + 1);
			} else {
				sprintf(tmp, "%s/shader",
						VDAssetManager::getResourcePath(eCurrentDir).c_str());
				memcpy(path, tmp, strlen(tmp) + 1);
			}

		}
			break;
		case ResourceType::eCurrentDir:
			getcwd(path, sizeof(path));
			break;
		case ResourceType::eTmpAssetDir:
			/*					*/
			sprintf(path, "/tmp/%s_%d",
					fragcore::SystemInfo::getAppliationName(),
					VDEngine::getBuildVersion(NULL, NULL, NULL));

			break;
		default:
			VDDebug::criticalLog("Invalid argument.\n");
			break;
		}
	} else if (VDSystemInfo::operatingSystem() & VDSystemInfo::eWindow) {
		switch (type) {
		case ResourceType::eConfig:
			break;
		default:
			VDDebug::criticalLog("Invalid argument.\n");
			break;
		}

	} else if (VDSystemInfo::operatingSystem() == VDSystemInfo::eUnknown) {
		VDDebug::criticalLog(
				"Can't determine what operating system application is running under.\n");
		assert(false);
	}

	return std::string(path);
}

std::string VDAssetManager::getResourceAbsolutePath(ResourceType type,
		const char* relativepath) {
	std::string respath = VDAssetManager::getResourcePath(type);
	return respath + "/" + relativepath;
}

void VDAssetManager::releaseAsset(VDAssetObject* asset) {

	VDAssetManager::RegistryTable::iterator it = assetreg.find(
			(VDGUID) asset->getInstanceID());
	if (it != assetreg.end()) {
		if ((*it).second.asset == asset) {
			/*	release asset.	*/
			asset->release();
			VDAssetManager::assetreg.erase(it);
		} else {
			VDDebug::criticalLog(
					"GUID does not make to correct object : %s != %s <==> %d != %d\n",
					asset->getName(), it->second.asset->getName(),
					asset->getInstanceID(), it->second.asset->getInstanceID());
		}
	}
}

void VDAssetManager::assignAsset(VDAssetObject* asset, ...) {
	VDRegistry* pReg = NULL;

	/*	*/
	if (assetreg[(VDGUID) asset->getInstanceID()].asset == asset) {
		pReg = &VDAssetManager::assetreg[(VDGUID) asset->getInstanceID()];

	} else {

		VDRegistry reg;
		reg.asset = asset;
		reg.guid = (VDGUID) ((VDObject*) asset)->getInstanceID();

		VDAssetManager::assetreg[(VDGUID) asset->getInstanceID()] = reg;
		pReg = VDAssetManager::getAsset((VDGUID) asset->getInstanceID()); //)&VDAssetManager::assetreg[(VDGUID)asset->getInstanceID()];
	}

	if (!pReg) {
		VDDebug::warningLog("Registry is null.\n");
		return;
	}
	if (pReg->asset == NULL) {
		VDDebug::criticalLog("Registry asset is null.\n");
		return;
	}

}

VDRegistry* VDAssetManager::getAsset(const VDGUID uid) {
	return &VDAssetManager::assetreg[uid];
}

