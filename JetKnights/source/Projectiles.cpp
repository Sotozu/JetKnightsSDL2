#include "Projectile.h"

Projectile::Projectile(int x, int y, float angle, SDL_Renderer* renderer, LTexture* texture)
{
	//Set offsets
	mRenderer = renderer;
	mTexture = texture;

	counter = 0;
	mPosX = x;
	mPosY = y;
	speed = 5;
	mAngle = angle;
	isDead = false;
}

//void Projectile::render(SDL_Renderer* gRenderer )
//{
//	//Show image
//	ammoTexture->render(mPosX, mPosY, NULL, gRenderer);
//
//}

void Projectile::update() {
	if (counter > 100) {
		isDead = true;
	}
	if (!isDead) {
		mPosX += speed * cos(mAngle * (3.14 / 180));
		mPosY += speed * sin(mAngle * (3.14 / 180));
		//std::cout << mPosX << std::endl;
		//std::cout << mPosY << std::endl;
		mTexture->render(mPosX, mPosY, NULL, mRenderer, mAngle);
		counter += 1;
	}
}



//bool Projectile::isDead()
//{
//}