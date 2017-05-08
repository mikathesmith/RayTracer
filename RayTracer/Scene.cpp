#include "Scene.h"

#include "Colour.h"
#include "Display.h"
#include "utility.h"

/*This is the scene to be ray traced. It collects Object, LightSource and Camera data together for rendering.
#It also includes basic info about the environment (backgroundColour, ambientLight), the image to be produced
#(renderWidth, renderHeight, filename) and the max number of reflections allowed (maxRayDepth)

#It provides methods required to render an image - intersecting a Ray with the objects in the Scene, and 
#computing the Colour from a Ray
*/

Scene::Scene() : backgroundColour(0,0,0), ambientLight(0,0,0), diffuseLight(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
	Display display("Render", renderWidth, renderHeight, Colour(128,128,128));
	
	std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;

	double halfPixel = 2.0/(2*renderWidth);

	for (unsigned int y = 0; y < renderHeight; ++y) {
		for (unsigned int x = 0; x < renderWidth; ++x) {
			double cx = (x - 0.5*renderWidth)*2.0/renderWidth + halfPixel;
			double cy = (y - 0.5*renderHeight)*2.0/renderWidth + halfPixel;
			Ray ray = camera_->castRay(cx,cy);
			display.set(x, y, computeColour(ray, maxRayDepth));
		}
		display.refresh();
	}
	display.save(filename);
	display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
	RayIntersection firstHit;
	firstHit.distance = infinity;	
	for (auto& obj : objects_) {
		std::vector<RayIntersection> hits = obj->intersect(ray);
		for (auto& hit : hits) {
			if (hit.distance > epsilon && hit.distance < firstHit.distance) {
				firstHit = hit;
			}
		}
	}
	for (auto& obj: objects_) {
	  auto hits = obj->intersect(ray);
	}
	return firstHit;
}

//The Colour seen by a  Ray depends on the lighting, the first Object that it hits, and the
//Material properties of that Object. This method performs these computations and computes the
//observed Colour. For some objects it may be necessary to cast other Rays to deal with
//reflections. This can recurse forever so is limited by a max number of reflections. 
Colour Scene::computeColour(const Ray& viewRay, unsigned int rayDepth) const {
	RayIntersection hitPoint = intersect(viewRay);
	
	//If ray does not hit any object, then the scene's background colour should be returned
	if (hitPoint.distance == infinity) {
		return backgroundColour;
	}
	
    //*diffuseLight * specular
	//Colour hitColour = ambientLight * hitPoint.material.ambientColour;
	Colour hitColour = diffuseLight * hitPoint.material.diffuseColour; 
		
	// Code to do better lighting, shadows, and reflections goes here.
    for (auto light: lights_) {
        // Compute the influence of this light on the appearance of the hit object.
        
    }
    
	return hitColour;
}

bool Scene::hasCamera() const {
	return bool(camera_);
}
