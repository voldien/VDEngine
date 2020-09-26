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
#ifndef _VD_MATRIX_H_
#define _VD_MATRIX_H_ 1
#include"../VDDef.h"
#include"../VDSystem.h"

/**
 *	Responsible for matrices used by
 *	the rendering pipeline.
 */
class VDDECLSPEC VDMatrix{
public:

	enum MatrixSpace{
		Model 			= 0x1,				/*	Model matrix, aka world matrix.	*/
		View 			= 0x2,				/*	View matrix, aka camera matrix.	*/
		ModelView 		= Model | View,	/*	ModelView Matrix,	*/
		Projection 	= 0x4				/*	Projection matrix.	*/
	};

private:	/*	Attributes.	*/

	static std::vector<VDMatrix4x4> viewMatrix;		/*	View space coordinate.	*/
	static std::vector<VDMatrix4x4> modelMatrix;		/*	world space coordinate.	*/
	static std::vector<VDMatrix4x4> projectionMatrix;	/*	projection space coordinate.	*/
	static unsigned int mode;

public:	/*	Public methods.	*/

	/**
	 *	Initialize matrix. Needs to be called
	 *	before the used the class.
	 */
	static void VDAPIENTRY init(void);

	/**
	 *	Push new matrix.
	 */
	static void VDAPIFASTENTRY pushMatrix(void);

	/**
	 *	Pop matrix.
	 */
	static void VDAPIFASTENTRY popMatrix(void);


	/**
	 *	Override current matrix set.
	 */
	static void VDAPIFASTENTRY setMatrix(const VDMatrix4x4& matrix);


	/**
	 *	Set identity matrix to current
	 *	matrix mode.
	 */
	static void VDAPIFASTENTRY identity(void);

	/**
	 *
	 */
	static void VDAPIFASTENTRY identity(unsigned int matrix);

	/**
	 *
	 */
	static void VDAPIENTRY translate(float x, float y, float z);

	/**
	 *
	 */
	static void VDAPIENTRY translate(const VDVector3& translation);

	/*
	 *
	 */
	static void VDAPIENTRY scale(const VDVector3& scale);

	/**
	 *
	 */
	static void VDAPIENTRY scale(float x, float y, float z);

	/**
	 *
	 */
	static void VDAPIENTRY scale(float alingAxis);


	/**
	 *
	 */
	static void VDAPIENTRY rotation(const VDQuaternion& quaterion);

	/**
	 *
	 */
	static void VDAPIENTRY perspective(float angle, float ratio, float near, float far);

	/**
	 *
	 */
	static void VDAPIENTRY ortho(float left, float right, float bottom, float top, float Near, float Far);


	/**
	 *
	 */
	static void VDAPIFASTENTRY matrixMode(unsigned int matrixMode);

	/**
	 *
	 *	@Return
	 */
	static int VDAPIFASTENTRY getIndex(unsigned int mode);

	/**
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getProjectIndex(void);

	/**
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getViewIndex(void);

	/**
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getModelIndex(void);

	/**
	 *	@Return
	 */
	static VDMatrix4x4 VDAPIFASTENTRY getModelView(void);
	static VDMatrix4x4 VDAPIFASTENTRY getView(void);
	static VDMatrix4x4 VDAPIFASTENTRY getModel(void);
	static VDMatrix4x4 VDAPIFASTENTRY getProjection(void);
	static VDMatrix4x4 VDAPIFASTENTRY getViewProjection(void);
	static VDMatrix4x4 VDAPIFASTENTRY getModelViewProjection(void);

	/**
	 *	Update matrix uniform associated with the
	 *	shader object.
	 */
	static void VDAPIENTRY uniformLocation(const VDShader* shader);

};

#endif
