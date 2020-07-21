#include <Core/VDConfig.h>
#include <Core/VDDebug.h>
#include <DataStructure/VDSize.h>
#include <libxml/encoding.h>
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include <Misc/VDFile.h>
#include <SDL2/SDL_stdinc.h>
#include <VDSystemInfo.h>
#include <cstdio>
#include <string>

void VDConfigure::defaultConfig(VDConfigure::VDConfig* config) {
	VDSize size;

	/**/
	config->width = size.width();
	config->height = size.height();
	config->resizable = SDL_TRUE;
	config->fullscreen = SDL_FALSE;
	config->debug = SDL_FALSE;

	/**/
	config->ntaskcores = VDSystemInfo::getCPUCoreCount();

	/**/
	config->verbose = SDL_TRUE;
}

int VDConfigure::loadConfigFile(const char* cconfigfilename,
		VDConfigure::VDConfig* config) {
	xmlDoc* document;
	xmlNode* root, *first_child, *node;
	char* buf;

	/*	*/
	if (!cconfigfilename && !config) {
		VDDebug::errorLog("Invalid arguments.\n");
		return SDL_FALSE;
	}

	/*	save a config file if no one exits.	*/
	if (!VDFile::existFile(cconfigfilename)) {
		std::string dir;
		//dir = VDFile::getDirectory(cconfigfilename);
		if (VDFile::isDirectory(dir.c_str()) == SDL_FALSE) {
			VDFile::createDirectory(dir.c_str());
			//File::setFileMode(dir.c_str(), 0b011);
		}
		VDConfigure::saveConfigFile(cconfigfilename, config);
	}

	document = xmlReadFile(cconfigfilename, NULL, 0);
	if (!document) {
		return SDL_FALSE;
	}

	root = xmlDocGetRootElement(document);

	for (node = root; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE) {
			printf((const char*) node->name);
			printf((const char*) node->content);
		}

	}

	error: /**/

	/**/
	xmlFreeDoc(document);
	xmlCleanupParser();
	xmlMemoryDump();
	return SDL_TRUE;
}

int VDConfigure::saveConfigFile(const char* cconfigfilename,
		VDConfigure::VDConfig* config) {
	xmlDoc* doc;
	xmlNode* root, *first_child, *node;
	xmlNode* window, *rendering;
	xmlTextWriterPtr writer;
	xmlChar *xmlbuff;
	int buffersize;
	char buf[1024];
	int status;

	/*	*/
	if (!cconfigfilename && !config) {
		VDDebug::errorLog("Invalid argument.\n");
		return SDL_FALSE;
	}

	doc = xmlNewDoc(BAD_CAST "1.0");
	root = xmlNewNode(NULL, BAD_CAST "enginesettings");
	xmlDocSetRootElement(doc, root);

	/**/
	window = xmlNewChild(root, NULL, BAD_CAST "width", BAD_CAST buf);
	sprintf(buf, "%d", config->width);
	xmlNewChild(window, NULL, BAD_CAST "width", BAD_CAST buf);
	sprintf(buf, "%d", config->height);
	xmlNewChild(window, NULL, BAD_CAST "height", BAD_CAST buf);
	sprintf(buf, "%d", config->fullscreen);
	xmlNewChild(window, NULL, BAD_CAST "fullscreen", BAD_CAST buf);
	sprintf(buf, "%d", config->resizable);
	xmlNewChild(window, NULL, BAD_CAST "resizable", BAD_CAST buf);

	/*	rendering	*/
	rendering = xmlNewChild(root, NULL, BAD_CAST "width", BAD_CAST buf);
	sprintf(buf, "%d", config->glprofile);
	xmlNewChild(rendering, NULL, BAD_CAST "glprofile", BAD_CAST buf);
	sprintf(buf, "%d", config->glversion);
	xmlNewChild(rendering, NULL, BAD_CAST "glversion", BAD_CAST buf);
	sprintf(buf, "%d", config->renderingapi);
	xmlNewChild(rendering, NULL, BAD_CAST "renderingapi", BAD_CAST buf);

	/**/
	status = xmlSaveFormatFileEnc(cconfigfilename, doc, "UTF-8", 1);
	if (status > 0) {
		VDDebug::log("Configuration file %s successfully saved.\n",
				cconfigfilename);
	} else {
		VDDebug::criticalLog("Configuration file %s failed.\n",
				cconfigfilename);
	}

	error: /**/

	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	return SDL_TRUE;
}
