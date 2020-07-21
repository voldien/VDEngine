#include <DataStructure/VDBoundVolume.h>
#include <DataStructure/VDPlane.h>
#include <Misc/VDMath.h>
#include <Scene/VDFrustum.h>
#include <VDSimpleType.h>
#include <cmath>
#include <cstring>

VDFrustum::VDFrustum(void){
	memset(planes, 0, sizeof(*planes));
	this->nh = 0.0f;
	this->nw = 0.0f;
	this->fh = 0.0f;
	this->fov = 0.0f;
	this->fh = 0.0f;
	this->nh = 0.0f;
	this->nw = 0.0f;
	this->Zfar = 0.0f;
	this->Znear = 0.0f;
	this->ratio = 0.0f;
	this->tang = 0.0f;

}

VDFrustum::VDFrustum(const VDFrustum& frustum){
	*this = frustum;
}

VDFrustum::VDFrustum(float fov, float aspect, float nearD, float farD){
	this->setPerspective(fov, aspect, nearD, farD);
	this->calcFrustumPlanes(VDVector3(0.0f), VDVector3::up(),VDVector3::right());
}

VDFrustum::VDFrustum(float right, float left, float bottom, float top, float near, float far){
	this->setOrth(left, right, bottom, top, near, far);
	this->calcFrustumPlanes(VDVector3(0.0f), VDVector3::up(),VDVector3::right());
}

void VDFrustum::setFov(float fov) {
	this->fov = fov;
}

void VDFrustum::setNear(float near) {
	this->Znear = near;
}

void VDFrustum::setFar(float far) {
	this->Zfar = far;
}

void VDFrustum::setRatio(float ratio) {
	this->ratio = ratio;
}
float VDFrustum::getFov(void) const {
	return this->fov;
}

float VDFrustum::getNear(void) const {
	return this->Znear;
}

float VDFrustum::getFar(void) const {
	return this->Zfar;
}

float VDFrustum::getRatio(void) const {
	return this->ratio;
}

const VDMatrix4x4& VDFrustum::getProjectionMatrix(void)const{
	return this->projectionMatrix;
}

void VDFrustum::setPerspective(float fov, float aspect, float near, float far){

	this->setFov(fov);
	this->setRatio(aspect);
	this->setNear(near);
	this->setFar(far);

	this->tang = (float)tanf(fov * 0.5f);	/*	Radians	*/
	this->nh = this->Znear * this->tang;
	this->nw = this->nh * this->ratio;
	this->fh = this->Zfar * this->tang;
	this->fw = this->fh * this->ratio;

}

void VDFrustum::setOrth(float left, float right, float bottom, float top, float near, float far){
	this->nh = right / 2.0;
	this->nw = left / 2.0;
	this->fh = bottom / 2.0;
	this->fw = top / 2.0;

	this->Znear = near;
	this->Zfar = far;
	this->ratio = (-left + right) / (bottom + -top);
	if(this->ratio == NAN || this->ratio == -NAN){
		this->ratio = 1.0;
	}
	this->fov = VDMath::pi * 0.5;
}

void VDFrustum::calcFrustumPlanes(const VDVector3& position, const VDVector3& look, const VDVector3& up, const VDVector3& right){

	/**/
	//VDVector3 farPts[4];
	//VDVector3 nearPts[4];

	/**/
	//VDVector3 cN = position + look * this->getNear();
	//VDVector3 cF = position + look * this->getFar();

	/*	fov shall be radian!	S*/
	/*
	float Hnear = 2.0f * tan(this->getFov() * 0.5f ) * Znear;
	float Wnear = Hnear * this->getRatio();
	float Hfar = 2.0f * tan( this->getFov() * 0.5f) * Zfar;
	float Wfar = Hfar * this->getRatio();
	float hHnear = Hnear * 0.5f;
	float hWnear = Wnear * 0.5f;
	float hHfar = Hfar * 0.5f;
	float hWfar = Wfar * 0.5f;

	farPts[0] = cF + up * hHfar - right * hWfar;
	farPts[1] = cF + up * hHfar + right * hWfar;
	farPts[2] = cF - up *  hHfar - right * hWfar;
	farPts[3] = cF - up * hHfar + right* hWfar;

	nearPts[0] = cN + up * hHnear - right * hWnear;
	nearPts[1] = cN + up * hHnear + right * hWnear;
	nearPts[2] = cN - up * hHnear - right * hWnear;
	nearPts[3] = cN - up * hHnear + right * hWnear;

	planes[eTOP] = VDFrustumPlane::fromPoints(nearPts[3],	nearPts[0],	farPts[0]);
	planes[eBOTTOM] = VDFrustumPlane::fromPoints(nearPts[1],nearPts[2],	farPts[2]);
	planes[eLEFT] = VDFrustumPlane::fromPoints(nearPts[0],	nearPts[1],	farPts[1]);
	planes[eRIGHT] = VDFrustumPlane::fromPoints(nearPts[2],	nearPts[3],	farPts[2]);
	planes[eNEARP] = VDFrustumPlane::fromPoints(nearPts[0],	nearPts[3],	nearPts[2]);
	planes[eFARP] = VDFrustumPlane::fromPoints(farPts[3],	farPts[0] ,	farPts[1]);
	*/


	VDVector3 dir,nc,fc,X,Y,Z;

	planes[eNEARP].setNormalAndPoint(-Z,nc);
	planes[eFARP].setNormalAndPoint(Z,fc);

	VDVector3 aux,normal;

	aux = (nc + Y*nh) - position;
	aux.normalize();
	normal = aux * X;
	planes[eTOP].setNormalAndPoint(normal,nc+Y*nh);

	aux = (nc - Y*nh) - position;
	aux.normalize();
	normal = X * aux;
	planes[eBOTTOM].setNormalAndPoint(normal,nc-Y*nh);

	aux = (nc - X*nw) - position;
	aux.normalize();
	normal = aux * Y;
	planes[eLEFT].setNormalAndPoint(normal,nc-X*nw);

	aux = (nc + X*nw) - position;
	aux.normalize();
	normal = Y * aux;
	planes[eRIGHT].setNormalAndPoint(normal,nc+X*nw);


}

void VDFrustum::calcFrustumPlanes(const VDVector3& position, const VDVector3& up, const VDVector3& right){
	this->calcFrustumPlanes(position, cross(up, right), up, right);
}


VDFrustum::Intersection VDFrustum::checkPoint(const VDVector3& pos)const{
	unsigned int x;
	for(x = 0; x < 6; x++){
		if(this->planes[x].distance(pos) < 0)
			return eOut;
	}
	return eIn;
}


VDFrustum::Intersection VDFrustum::intersectionAABB(const VDVector3& min, const VDVector3& max){
	VDFrustum::Intersection result = VDFrustum::eIn;
	int i;

	for(i = 0; i < 6; i++){

		VDVector3 p = min;
		VDVector3 n = max;
		VDVector3 N = planes[i].getNormal();

		if(N.x() >= 0) {
			p[0] = max.x();
			n[0] = min.x();
		}
		if(N.y() >=  0) {
			p[1] = max.y();
			n[1] = min.y();
		}
		if(N.z() >= 0 ) {
			p[2] = max.z();
			n[2] = min.z();
		}

		if (planes[i].distance(p) < 0.0f ) {
			return eOut;
		}
		else if (planes[i].distance(n) < 0.0f ) {
			result = Intersection::eIntersect;
		}
	}

	return result;
}

VDFrustum::Intersection VDFrustum::intersectionAABB(const VDAABB& bounds){
	return this->intersectionAABB(bounds.min(), bounds.max());
}

VDFrustum::Intersection VDFrustum::intersectionOBB(const VDVector3& x, const VDVector3& y, const VDVector3& z){
	VDFrustum::Intersection result;
	for(int x = 0; x < 6; x++){


	}
	return eIn;
}

VDFrustum::Intersection VDFrustum::intersectionOBB(const VDOBB& obb){
	for(int x = 0; x < 6; x++){


	}
	return eIn;
}


VDFrustum::Intersection VDFrustum::intersectPlane(const VDPlane& plane)const{
	unsigned int status = 0;
	for(int x = 0; x < sizeof(planes) / sizeof(planes[0]); x++){
		float det = cross(planes[x].getNormal(), plane.getNormal()).squaredLength();

		if(fabs(det) > 1E-20){
			status++;
		}
		/*
		if(det < 0.01 && det > -0.01){

		}
		*/
	}
	return status >= 5 ? eIn : eOut;
}


VDFrustum::Intersection VDFrustum::intersectBoundingVolume(const VDBound& bounds, VDBound::BoundType type, const VDVector3& position){
	switch(type){
	case VDBound::eAABB:{
		VDAABB aabb = bounds.aabb;
		aabb.setCenter(aabb.getCenter() + position);
		return this->intersectionAABB(aabb);
	}
	case VDBound::eOBB:
		return this->intersectionOBB(bounds.obb);
	default:
		return VDFrustum::eIn;
	}
}

VDFrustum::Intersection VDFrustum::intersectionFrustum(const VDFrustum& frustum)const{
	int i;
	int j;

	for(i = 0; i < sizeof(frustum.planes) / sizeof(frustum.planes[0]); i++){
			if(!this->intersectPlane(frustum.planes[i])){
				return eOut;
			}
	}/**/
	return eIn;
}
