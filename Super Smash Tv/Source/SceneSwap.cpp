#include "SceneSwap.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

SceneSwap::SceneSwap(bool startEnabled) : Module(startEnabled)
{

}

SceneSwap::~SceneSwap()
{

}

// Load assets
bool SceneSwap::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/SpritesSSTV/Score_screen_2.png");
	//App->audio->PlayMusic("Assets/Audio/SFX/End point count.wav", 1.0f);
	App->audio->PlayMusic("Assets/Music/06-_Super_Smash_TV_-_Win_Game.ogg", 1.0f);
	Win = App->audio->LoadFx("Assets/Audio/SFX/End point count 2.wav");


	App->audio->PlayFx(Win);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->CleanUp();
	App->collisions->CleanUp();
	App->particles->CleanUp();
	App->enemies->CleanUp();

	App->enemies->Disable();

	return ret;
}

UpdateResult SceneSwap::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 20);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneSwap::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}