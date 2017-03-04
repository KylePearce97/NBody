#include "ThreeBody.h"



void ThreeBody::render(Renderer * r)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-2000, 2000, -2000, 2000, 0.0f, 1.0f); // Reference system of our simulation
	glColor3f(0.5, 1.0, 1.0);

	for (int i = 0; i < bodies.size(); i++) {
		glm::dvec2 p = this->bodies[i].getP0();
		this->bodies[i].render(r);
		//r->renderCircle(dvec3(p.x, p.y, 0),this->bodies[i].getRadius(), 30, this->bodies[i].getColor());
	}

	r->swap();
}

void ThreeBody::update()
{
	for (int i = 0; i < bodies.size(); i++) {
		Body &iB = this->bodies[i];
		for (int j = 0; j < bodies.size(); j++) {
			Body &jB = this->bodies[j];
			if(i != j)
				iB.calculateForce(jB);
		}
		iB.update(dt);
		iB.resetForce();
	}
}

bool ThreeBody::pollEvents(SDL_Event e)
{
	if (e.type == SDL_QUIT)
		return false;
	if (e.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		default:
			break;
		}
	}

	return true;
}

ThreeBody::ThreeBody()
{
}


ThreeBody::~ThreeBody()
{
}

void ThreeBody::init()
{
	dt = 1e4;
	bodies.push_back(Body(dvec2(500,0), dvec2(0,0), dvec2(0), 1, 10, vec3(1.0,1.0,1.0)));
	bodies.push_back(Body(dvec2(500, -500), dvec2(-0,0), dvec2(0), 1, 10, vec3(0.0, 1.0, 1.0)));
	bodies.push_back(Body(dvec2(-500, 500), dvec2(0), dvec2(0), 1, 10, vec3(1.0, 0.0, 0.0)));
}

void ThreeBody::run(Renderer * r)
{
	SDL_Event e;
	this->init();
	bool running = true;
	while (running) {
		SDL_PollEvent(&e);
		running = this->pollEvents(e);
		this->update();
		this->render(r);
	}
}