#include <Asset/VDAssetManager.h>
#include <Asset/VDAssetURLFetch.h>
#include <Asset/VDResources.h>
#include <Audio/VDAudioClip.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDMesh.h>
#include <stddef.h>
#include <climits>
#include <cstdio>
#include <cstring>
#include <string>

/**/
static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

VDAssetURLFetch::VDAssetURLFetch(void)
{
	this->ramDisk = NULL;
	memset(this->tmpPath, 0, sizeof(this->tmpPath));
}

VDAssetURLFetch::VDAssetURLFetch(const char *url)
{
	this->ramDisk = NULL;
	this->load(url);
}

VDAssetURLFetch::VDAssetURLFetch(const VDAssetURLFetch &assetfetchurl)
{
	*this = assetfetchurl;
}

VDAssetURLFetch::~VDAssetURLFetch(void)
{
	//VDFile::removeFile(tmpPath);
	if (this->ramDisk != NULL)
	{
		fclose(this->ramDisk);
	}
}

bool VDAssetURLFetch::load(const char *url)
{
	CURL *curl;
	CURLcode res;
	std::string tmpDirectory;
	char tmpAppName[PATH_MAX];

	curl = curl_easy_init();
	tmpDirectory = VDAssetManager::getResourcePath(VDAssetManager::eTmpAssetDir);

	// if(curl){
	// 	VDFile::createDirectory(tmpDirectory.c_str());

	// 	sprintf(this->tmpPath, "%s/%s", tmpDirectory.c_str(), basename((char*)url));
	// 	this->ramDisk = VDFile::safeOpenWrite(tmpPath);
	// 	if(ramDisk != NULL){
	// 		res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	// 		res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, this->ramDisk);
	// 		res = curl_easy_setopt(curl, CURLOPT_URL, url);
	// 		res = curl_easy_perform(curl);
	// 		curl_easy_cleanup(curl);

	// 		fclose(this->ramDisk);
	// 		this->ramDisk = NULL;

	// 		return true;
	// 	}
	// }/**/
	return false;
}

VDTexture2D *VDAssetURLFetch::getTexture(void)
{
	return VDResources::load<VDTexture2D>(this->getAbsolutePath());
}

VDAudioClip *VDAssetURLFetch::getAudioClip(void)
{
	return VDResources::load<VDAudioClip>(this->getAbsolutePath());
}

VDMesh *VDAssetURLFetch::getMesh(void)
{
	return VDResources::load<VDMesh>(this->getAbsolutePath());
}

char *VDAssetURLFetch::getText(void)
{
	return VDResources::load<char>(this->getAbsolutePath());
}

const char *VDAssetURLFetch::getAbsolutePath(void) const
{
	return this->tmpPath;
}

const char *VDAssetURLFetch::getCacheDirectory(void)
{
	return VDAssetManager::getResourcePath(VDAssetManager::eTmpAssetDir).c_str();
}
