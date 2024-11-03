#include "Object.h"

Object::Object(Shader shaderWhichRenderObject, glm::quat *orientationQuat, float* degreToRotateX, float* degreToRotateY, float* degreToRotateZ, float* positionX, float* positionY, float* positionZ) /**/
{
	Object::OrientationX_ = *degreToRotateX;
	Object::OrientationY_ = *degreToRotateY;
	Object::OrientationZ_ = *degreToRotateZ;

	Object::PositionX_ = *positionX;
	Object::PositionY_ = *positionY;
	Object::PositionZ_ = *positionZ;

	Object::orientationQuat = *orientationQuat;

	shaderWhichRenderObject_ID = shaderWhichRenderObject.ID;
}
void Object::setPosition(glm::vec3 newPosition)
{
	glm::mat4 modelPos = glm::mat4(1.0f);
	modelPos = glm::translate(modelPos, Object::Position + newPosition);

	Object::modelPos = glm::mat4(1.0f);
	Object::modelPos = modelPos;

	// We setting up position insde Object class 
	Object::Position = newPosition;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelPos"), 1, GL_FALSE, glm::value_ptr(Object::modelPos));  // Pošalji model matricu u shader
};
void Object::rotateObject(float axisX, float axisY, float axisZ)
{
	Object::OrientationX_ = axisX;
	Object::OrientationY_ = axisY;
	Object::OrientationZ_ = axisZ;

	glm::mat4 matrixPos = glm::mat4(1.0f);
	matrixPos = glm::translate(matrixPos, -Object::Position);

	// Apply rotations around each axis (in the order X, Y, Z)
	glm::mat3 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(axisX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(axisY), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(axisZ), glm::vec3(0.0f, 0.0f, 1.0f));

	matrixPos = glm::translate(matrixPos, Object::Position);
	Object::modelRotate = Object::modelRotate * glm::mat4(rotationZ * rotationY * rotationX);

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));
};
void Object::scaleObject(glm::vec3 scaleFactor)
{
	Object::Scale = scaleFactor;

	glm::mat4 matrixScale = glm::mat4(1.0f);
	matrixScale = glm::scale(matrixScale, scaleFactor);

	Object::modelScale = Object::modelScale * matrixScale;

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelScale"), 1, GL_FALSE, glm::value_ptr(Object::modelScale));
};
void Object::rotateQuat(float componentW, float pitchX, float yawY, float rollZ) // This type of rotation solve gimbal lock
{
	glm::vec3 axis(1.0f, 1.0f, 1.0f);
	glm::quat quatRot_local_rotation;
	glm::quat quatRot_total(1.0f, 0.0f, 0.0f, 0.0f);

 	quatRot_local_rotation.w = cosf(componentW / 2);
	quatRot_local_rotation.x = axis.x * sinf(glm::radians(pitchX) / 2);
	quatRot_local_rotation.y = axis.y * sinf(glm::radians(yawY) / 2 );
	quatRot_local_rotation.z = axis.z * sinf(glm::radians(rollZ) / 2);

	quatRot_local_rotation = glm::normalize(quatRot_local_rotation);

	quatRot_total = quatRot_local_rotation * quatRot_total;
	Object::modelRotate = glm::mat4_cast(quatRot_total);

	glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));
};
void Object::setOrientationDegre(Rotation axlToRotate, float *degreToRotate) // To redundad mayby delete
{
	glm::vec3 aroudTheAxle;
	if (axlToRotate == Object::Rotation::X) {
		aroudTheAxle = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::mat4 matrixRot = glm::mat4(1.0f);
		glm::mat4 matrixPos = glm::mat4(1.0f);

		matrixPos = glm::translate(modelPos, -Object::Position);
		matrixRot = glm::rotate(matrixRot, glm::radians(*degreToRotate), aroudTheAxle);
		matrixPos = glm::translate(modelPos, Object::Position);

		Object::modelRotate = Object::modelRotate * matrixRot;
		Object::OrientationX_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Object::Rotation::Y){
		aroudTheAxle = glm::vec3(0.0f, 1.0f, 0.0f);
		
		glm::mat4 matrixRot = glm::mat4(1.0f);
		glm::mat4 matrixPos = glm::mat4(1.0f);

		matrixPos = glm::translate(modelPos, -Object::Position);
		matrixRot = glm::rotate(matrixRot, glm::radians(*degreToRotate), aroudTheAxle);
		matrixPos = glm::translate(modelPos, Object::Position);

		Object::modelRotate = Object::modelRotate * matrixRot;
		OrientationY_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));  // Pošalji model matricu u shader
	}
	else if (axlToRotate == Object::Rotation::Z) {
		aroudTheAxle = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::mat4 matrixRot = glm::mat4(1.0f);
		glm::mat4 matrixPos = glm::mat4(1.0f);

		matrixPos = glm::translate(modelPos, -Object::Position);
		matrixRot = glm::rotate(matrixRot, glm::radians(*degreToRotate), aroudTheAxle);
		matrixPos = glm::translate(modelPos, Object::Position);

		Object::modelRotate = Object::modelRotate * matrixRot;
		OrientationZ_ = *degreToRotate;

		glUniformMatrix4fv(glGetUniformLocation(Object::shaderWhichRenderObject_ID, "modelRotate"), 1, GL_FALSE, glm::value_ptr(Object::modelRotate));  // Pošalji model matricu u shader
	}
};
float Object::getOritation(Object::Rotation rotationAxl) // Make new implementation TODO
{
	if (rotationAxl == Object::Rotation::X) {
		return Object::OrientationX_;
	}
	else if(rotationAxl == Object::Rotation::Y)
	{
		return Object::OrientationY_;
	}
	else if(rotationAxl == Object::Rotation::Z)
	{
		return Object::OrientationZ_;
	}
};
/*//------------Normalizing Quaterion-----------------------------//
	float magnitude = sqrt(componentW + pitchX + yawY + rollZ);

	componentW = componentW / magnitude;
	pitchX = pitchX / magnitude;
	yawY = yawY / magnitude;
	rollZ = rollZ / magnitude;
//-----------Multiply of Quaterion----------------------------------// vazi pravilo komutativnosti
	glm::quat Quat1;
	glm::quat Quat2;
	
	(Quat1 * Quat2).w = (Quat1.w * Quat2.w - Quat1.x * Quat2.x - Quat1.y * Quat2.y - Quat1.z * Quat2.z);	 //            (Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
	(Quat1 * Quat2).x = (Quat1.w * Quat2.x + Quat1.x * Quat2.w + Quat1.y * Quat2.z - Quat1.z * Quat2.y);	 //			   (Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
	(Quat1 * Quat2).y = (Quat1.w * Quat2.y - Quat1.x * Quat2.z + Quat1.y * Quat2.w + Quat1.z * Quat2.x);	 //			   (Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
	(Quat1 * Quat2).z = (Quat1.w * Quat2.z + Quat1.x * Quat2.y - Quat1.y * Quat2.x + Quat1.z * Quat2.w);	 //			   (Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2)
//---------------------------------------------------------------------	               
	glm::quat local_rotation;              // tempoary Quaterion which will simply represent how you're changing the rotationIf you're changing the current rotation by rotating backwards over the X-axis a little bit, this temporary quaternion will represent that.
	
	glm::quat total(0, 0, 0, 1);                      // permanent quaternion

	total = local_rotation * total; //multiplication order matters on this line

	//axis is a unit vector
	local_rotation.w = cosf(fAngle / 2);
	local_rotation.x = glm::vec3(1.0f,0.0f,0.0f) * sinf(glm::radians(pitchX) / 2);                                  //  local_rotation.w = cosf(fAngle / 2)
	local_rotation.y = glm::vec3(0,1,0) * sinf(glm::radians(yawY) / 2);                                    //  local_rotation.x = axis.x * sinf(fAngle / 2) 
	local_rotation.z = glm::vec3(0,0,1) * sinf(glm::radians(rollZ) / 2);								   //  local_rotation.y = axis.y * sinf(fAngle / 2) 
																										   //  local_rotation.z = axis.z * sinf(fAngle / 2)


*/