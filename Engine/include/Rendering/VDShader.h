/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_SHADER_H_
#define _VD_SHADER_H_ 1
#include "../Asset/VDAssetObject.h"
#include <map>
#include <string>

/**
 *
 */
class VDDECLSPEC VDShader : public VDAssetObject {
	friend class VDMatrix;
	friend class VDSkyBox;
	friend class VDRenderer;

  public:
	/*	TODO change the value to opengl const variables*/
	enum ShaderType : unsigned long int {
		eVertex = (unsigned long int)0x100000000000ULL,
		eFragment = (unsigned long int)0x200000000000ULL,
		eGeometry = (unsigned long int)0x400000000000ULL,
		eProgram = (unsigned long int)0x800000000000ULL,
		eTessellationControl = (unsigned long int)0x1000000000000ULL,
		eTessellationEvaulation = (unsigned long int)0x2000000000000ULL,

		eShaderAll = (eVertex | eFragment | eGeometry | eTessellationControl | eTessellationEvaulation),

		eVertexShader = 0x8B31,
		eFragmentShader = 0x8B30,
	};

	enum Flags : unsigned long int {
		eShaderDiffuseColor = (1 << 0),
		eShaderSpecularColor = (1 << 1),
		eShaderCubeMapColor = (1 << 2),

		eShaderDiffuseTexture = (1 << 4),
		eShaderNormalTexture = (1 << 5),
		eShaderCubeMapTexture = (1 << 6),
		eShaderIllusion = (1 << 7),
		eShaderDepthTexture = (1 << 8),
		eShaderSpecularTexture = (1 << 9),
		eShaderDisplacementTexture = (1 << 10),

		/**/
		eShaderLight = (1 << 11),

		eShaderProjection = (1 << 13),
		eShaderModelMatrix = (1 << 14),
		eShaderViewMatrix = (1 << 15),
		eShaderModelViewMatrix = (1 << 16),
		eShaderModelViewProjection = (1 << 17),
		eShaderViewProjectionMatrix = (1 << 18),

		eShaderDeformMatrix = (1 << 20),
		eShaderLightMatrix = (1 << 21),

		eShaderScreenSpace = (1 << 22),
		eShaderWorldSpace = (1 << 23),

		/**/
		eShaderOpaque = (1 << 24),
		/**/
		eShaderTranslucent = (1 << 25),
		/**/
		eFrontCulling = (1 << 26),
		/**/
		eBackCulling = (1 << 27),
		/**/
		eBothCulling = (1 << 28),

		/**/
		eSubRoutines = (1 << 29),

	};

  public:
	struct common_uniform_location_t {
		int diffuseTexture0;
		int diffuseTexture1;
		int diffuseTexture2;
		int diffuseTexture3;

		int normalTexture;
		int specularTexture;
		int cubeTexture;

		int diffuseColor;
		int specularColor;

		int shininess;
		int heights;
		int refraction;
	};

	struct matrixInfo {
		int modelMatrix;			   /* World Space Matrix.	*/
		int viewMatrix;				   /* Camera Space Matrix.	*/
		int projectionMatrix;		   /* Projection Matrix.	*/
		int modelViewMatrix;		   /* CameraWorld Space Matrix.	*/
		int modelViewProjectionMatrix; /* ProjectionCameraWorld.	*/
		int viewprojection;			   /*	*/
		int normalMatrix;			   /* World Space Normal Matrix.	*/
		int deformMatrix;			   /* bone.	*/
	};

  private:
	VDShader();
	VDShader(const VDShader &shader);
	VDShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath, const char *Name,
			 const char *tessC = nullptr, const char *tessE = nullptr, unsigned int flag = 1);

  public:
	~VDShader();

  private:							  /*	Attributes.	*/
	unsigned int program;			  /*	*/
	matrixInfo matrixInfo;			  /*	*/
	common_uniform_location_t common; /*	*/
	unsigned long int flag;			  /*	*/
	struct sub_routine {			  /*	*/
		int numActive;				  /*	*/
		unsigned int indices[32];	  /*	*/
	} subroutines;

  public:
	/**
	 *	Get shader program unique identifier.
	 */
	unsigned int getProgram() const;

	/**
	 *	Release resource.
	 */
	virtual void VDAPIENTRY release() override;

	/**
	 *	release Shader From GPU. Data Associating With Shader Will Be
	 *	Remove & Shader Allocation Reference will be cleaned as well.
	 */
	void VDAPIENTRY release(unsigned int flag = (eVertex | eFragment | eGeometry | eProgram | eTessellationControl |
												 eTessellationEvaulation));

	/**
	 *	bind Shader Program. All Shader Component will be enabled
	 */
	inline void bind() {}

	/**
	 *	Get if Flag is Set
	 *	@Return
	 */
	inline bool isFlagSet(unsigned long int flag) const { return (this->flag & flag) != 1; }

	/**
	 *
	 */
	inline unsigned long int getFlagSet() const { return this->flag; }
	inline void setFlagSet(unsigned long int flag) { this->flag = flag; }

	const struct VDShader::matrixInfo *getMatrinxInfo() const { return &this->matrixInfo; }

	/**
	 *	Get version of the binary shader.
	 *	@Return
	 */
	unsigned int VDAPIENTRY getVersion() const;

	/**
	 *	Get if shader is valid.
	 *
	 *	@Return true if shader program is valid.
	 */
	bool VDAPIENTRY isValid() const;

  public: /*	Set shader states.	*/
	/**
	 *	Get Shader Uniform Location.
	 *
	 *	@Return uniform index.
	 */
	int VDAPIFASTENTRY getUniformLocation(const char *cuniformName) const;

	/**
	 *	Set Get Uniform Location Of Array Object. Get Location of all Object
	 *
	 *	In GLSL.
	 *	[FrontText] Defined as "Object[".
	 *	[Index] Index Location.
	 *	[EndText] Defined as "].Value".
	 *
	 *	@Return
	 */
	int VDAPIENTRY getUniformLocationArray(const char *frontText, unsigned int index, const char *endText);

	/**
	 *	Get shader attribute Location.
	 *
	 *	@Return attribute index.
	 */
	int VDAPIFASTENTRY getAttributeLocation(const char *attributeName) const;

	/**
	 *	Set vertex attribute location index.
	 */
	void VDAPIFASTENTRY setAttributeLocation(const char *attributeName, unsigned int index);

	/**
	 * 	Get fragment location index.
	 *
	 *	@Return index as a whole number if successfully.
	 */
	int VDAPIFASTENTRY getFragDataLocation(const char *name) const;

	/**
	 *	Set fragmenation location.
	 */
	void VDAPIFASTENTRY setFragDataLocation(const char *name, unsigned int colorNumber);

	/**
	 *	Set varyings
	 *
	 */
	void VDAPIENTRY setVaryings(int count, const char **varyings, unsigned int mode);

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getUniformBlockIndex(const char *uniformBlockName) const;

	/**
	 *
	 *
	 *	@Return
	 */
	int VDAPIFASTENTRY getUniformSize(const char *cuniformName) const;

	/**
	 *	Get uniform block size.
	 *
	 *	@Return
	 */
	int VDAPIFASTENTRY getUniformBlockSize(const char *uniformBlockName) const;

	/**
	 *
	 */
	void VDAPIFASTENTRY setUniformBlockBind(int uniformBlockIndex, unsigned int uniformBlockBinding);

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getStorageBlockIndex(const char *cStorageBlockName);

	/**
	 *	@Return
	 */
	int VDAPIFASTENTRY getStorageBlockSize(const char *cStorageBlockName);

	/**
	 *
	 */
	void VDAPIFASTENTRY setStorageBlockBind(unsigned int uniformBlockIndex, unsigned int uniformBlockBinding);

	/**
	 * 	subroutine
	 *
	 *	@Return
	 */
	unsigned int VDAPIENTRY getSubRoutineIndex(ShaderType shadertype, const char *cfunctionName);

	/**
	 *	Set routines.
	 *
	 *	subroutine
	 */
	void VDAPIENTRY setSubRoutine(ShaderType shadertype, unsigned int num, const unsigned int *indices);

	/*	TODO rename and such.*/
	void VDAPIENTRY setSubRoutineTmp(ShaderType shaderType, const char *funcname, const char *routineName);

	/**
	 *	TODO rename to getNumActiveSubRoutines();
	 *
	 *	@Return
	 */
	unsigned int VDAPIENTRY getNumSubRoutines() const;

	/**
	 *
	 *	@Return
	 */
	const unsigned int *getActiveRoutinesIndices() const;

  public:
	/**
	 *
	 *	@Return
	 */
	int VDAPIENTRY compileShader(const char *vertex, const char *fragment, const char *geomtry, const char *control,
								 const char *evolution);

	/*
	 *	Read Shader Source and Flag Shader Component.
	 *	[Flag] What Shader Source to be flagged.
	 *
	 */
	void VDAPIENTRY flagReference(const char *cVertexFileName, const char *fragmentPath, const char *geometryPath,
								  const char *tessC, const char *tessE);

	/**
	 *	Initialization of Shader Flag.
	 */
	void VDAPIENTRY initFlagData();

	VDShader &operator=(const VDShader &shader);

  public:
	/*
	 *	Defined few Default Shader.
	 */
	static void VDAPIENTRY getUniformMatrixLocation(VDShader *shader);

	/*
	 *	Get Uniform Data Type Size.
	 *	@Return
	 */
	static unsigned int VDAPIFASTENTRY getUniformTypeSize(unsigned int uniformFlag);

	/*  Shader Map Generic Array. Containts all kind of Shader.
	 *  Not Instance. Type by Given Name.
	 */

	static VDShader *VDAPIENTRY findShader(const char *name);
	static inline VDShader *VDAPIENTRY findShader(std::string &name) { return VDShader::findShader(name.c_str()); }
	std::multimap<const char *, VDShader *> VDAPIENTRY getShaderCollection();

  private: /*	*/
	/**
	 *	Get Shader Version Of Shader Source input.
	 */
	int VDAPIENTRY getVersion(const char *shaderSource) const;

	/*
	 *	Get shader source shader languager version
	 */
	unsigned int VDAPIENTRY getFileShaderVersion(const std::string &source) const;

  public: /*	Static methods.	*/
	/**
	 *	Validate Shader. Shader Will be Validateed if Shader if
	 *	Compatible. Error Log Will Be Shown on Failure with Description!
	 *	[Return] 0 Equal Failure. 1 Equal to Success.
	 *
	 *	@Return
	 */
	static unsigned int VDAPIENTRY validateShader(const VDShader *shader);

	/**
	 *	Get Compiler Log. Compiler Log Will Be Displayed on Debug
	 *	Console GameWindow.
	 */
	static void VDAPIENTRY compilerLog(int shader, unsigned int shaderType);

	/**
	 *	Get Compiler Log By Given Shader & Shader Type.
	 *
	 *	\infolog
	 */
	static void VDAPIENTRY getCompileLog(int shader, unsigned int shaderType, char *infoLog);

	/**
	 *
	 *	@Return
	 */
	static char *VDAPIENTRY getShaderSource(VDShader *shader, unsigned int shaderType);

	/**
	 * Assign Shader to Shader FrameWork.
	 */
	static void VDAPIFASTENTRY setShader(VDShader *shader);

	/*
	 *
	 */
	// static VDShader* VDAPIFASTENTRY getShader(const VDGUID guid);

  public: /*	Factory methods.	*/
	/**
	 *	Create em
	 *	@Return
	 */
	static VDShader *VDAPIENTRY createShader();

	/**
	 *
	 *	@Return
	 */
	static VDShader *VDAPIENTRY createShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath,
											 const char *Name, const char *tessC = nullptr, const char *tessE = nullptr,
											 unsigned int flag = 1);
};

typedef std::map<unsigned int, VDShader *> ShaderCollection;
extern VDDECLSPEC ShaderCollection shaderCollection;

#define VD_SHADER_C_PROC_ID "#define SHADER_PROC_ID "
#define VD_SHADER_C_PROC_ENGINE_ID "#define VDENGINE_ID"

/**
 *	Global uniform data struct.
 */
typedef struct vd_uniform_data_t {
	struct vd_engine_uniform_state_t {
		VDColor ambientColor;
		VDVector3 cameraPosition;
		VDVector3 cameraDir;
		float cameraNear;
		float cameraFar;
		float width;
		float height;
		float timescale;
		float time;
		float deltaTime;
		int numLights;
		int maxLights;
		int xpos;
		int ypos;
		unsigned int numShadows;
		unsigned int shadow;
		VDMatrix4x4 projection;
		VDMatrix4x4 viewMatrix;
		VDMatrix4x4 viewProjection;
		int numDirection;
		int numSpot;
		int numPoint;
		int numShadowDirection;
		int numShadowSpot;
		int numShadowPoint;
		int ambientType;
		float ambientIntensity;
		VDColor fogColor;
		float fogStart;
		float fogEnd;
		float fogHeight;
		int fogType;
		float fogDensity;
	} engineState;

	// unsigned int ubo;
	// unsigned int ubo_index;
	// VDUniformBuffer enginestate;
} VDSceneUniform;

#endif
