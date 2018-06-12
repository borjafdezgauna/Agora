#include "stdafx.h"
#include "scene-actor.h"
#include "xml-load.h"
#include "../GeometryLib/matrix44.h"



CSceneActor::CSceneActor(tinyxml2::XMLElement* pNode)
{
	XMLElement* pChild;
	pChild= pNode->FirstChildElement(XML_TAG_TRANSFORM);
	if (pChild)
		XML::load(pChild, m_transform);
}

CSceneActor::~CSceneActor()
{
}

void CSceneActor::setTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	double *pMatrix = getTransformMatrix().asArray();
	if (pMatrix)
		glMultMatrixd(pMatrix);
}

void CSceneActor::restoreTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

Matrix44 CSceneActor::getTransformMatrix() const
{
	Matrix44 mat, rot, scale,trans;
	rot.setRotation(m_transform.rotation());
	trans.setTranslation(m_transform.translation());
	scale.setScale(m_transform.scale());
	mat = trans*rot*scale;
	return mat;
}

void CSceneActor::addLocalOffset(Vector3D& offset)
{
	Matrix44 mat = getTransformMatrix();
	Vector3D worldOffset = mat*offset;
	m_transform.setTranslation(m_transform.translation() + worldOffset);
}

void CSceneActor::addWorldOffset(Vector3D& offset)
{
	m_transform.setTranslation(	m_transform.translation() + offset);
}

void CSceneActor::setWorldPosition(Vector3D& position)
{
	m_transform.setTranslation(position);
}

void CSceneActor::addRotation(Quaternion& quat)
{
	m_transform.setRotation(m_transform.rotation() * quat);
}

void CSceneActor::setRotation(double yaw, double pitch, double roll)
{
	m_transform.setRotation(Quaternion(yaw, pitch, roll));
}