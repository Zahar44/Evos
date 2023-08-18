#include "Game.h"

Game::~Game()
{
	PX_RELEASE(scene);
	PX_RELEASE(material);
	PX_RELEASE(dispatcher);
	PX_RELEASE(physics);
	PX_RELEASE(foundation);
}

void Game::initialize()
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true);
	dispatcher = PxDefaultCpuDispatcherCreate(2);

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	scene = physics->createScene(sceneDesc);

	material = physics->createMaterial(0.5f, 0.5f, 0.6f);

	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 0), *material);
	scene->addActor(*groundPlane);

	auto player = createPlayer();
	scene->addActor(*player->getActor());

	world = new World(physics, player, scene);
}

void Game::update(float delta)
{
	world->getSun().update(delta);
	world->getWind().update(delta);
	world->getPlayer().update(delta);
}

Player* Game::createPlayer()
{
	auto actor = physics->createRigidDynamic(PxTransform(PxVec3(0.f, 2.5f, 0.f)));
	PxRigidBodyExt::updateMassAndInertia(*actor, 10.0f);
	auto material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	auto shape = physics->createShape(PxCapsuleGeometry(1.0f, 1.0f), *material);
	actor->attachShape(*shape);

	auto mesh = CylinderMesh::create();
	auto view = new RigidView(actor, Shader::get(), mesh);
	view->setColor({ 0.0f, 0.0f, 1.0f });

	auto player = new Player(view, actor);
	return player;
}

void Game::simulate()
{
	scene->simulate(simulationTime);
	scene->fetchResults(true);
}
