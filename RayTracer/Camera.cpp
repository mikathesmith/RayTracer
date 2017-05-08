

#include "Camera.h"
 /*
  An image is rendered  by a virtual camers (pinhole) 
  centered at origin looking along positive Z-axis) 
  
  */


Camera::Camera() : transform() {

}

Camera::Camera(const Camera& camera) : transform(camera.transform) {

}

Camera::~Camera() {

}

const Camera& Camera::operator=(const Camera& camera) {
	if (this != &camera) {
		transform = camera.transform;
	}

	return *this;
}
