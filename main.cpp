#include <Novice.h>
#include "Enemy.h"
#include "Player.h"
const char kWindowTitle[] = "GC1C_11_ツカダ_ハルト_タイトル";

int Collision(int obj1_x, int obj1_y, int obj1_r, int obj2_x, int obj2_y, int obj2_r,int isObj1Alive,int isObj2Alive)
{
	///当たり判定を書いて
	int distance = (obj1_x - obj2_x) * (obj1_x - obj2_x) + (obj1_y - obj2_y) * (obj1_y - obj2_y);
	if (isObj1Alive == 1 && isObj2Alive == 1)
	{
		if (((obj1_r + obj2_r) * (obj1_r + obj2_r)) >= distance)
		{
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	enum SCENE {
		TITLE,
		GAME,
		CLEAR,
		GAMEOVER,
		
	};
	int scene = TITLE;
	Enemy* enemy = new Enemy();
	Player* player = new Player();

	int bulletX = 10;
	int bulletY = 10;
	int bulletR = 16;
	int bulletSpeed = 10;
	int isBulletShot = 0;

	int responTimer = 120;
	int responflag = 0;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (scene)
		{
		case TITLE:
			if (keys[DIK_RETURN])
			{
				scene = GAME;
				enemy->Initalize();
				player->Initalize();
			}
			break;
		case GAME:
			enemy->Update();
			player->Update(keys);
  			if (player->GetIsAlive()&&keys[DIK_SPACE]&&isBulletShot==0)
			{
				bulletX = player->GetPosX();
				bulletY = player->GetPosY();
				isBulletShot = 1;
			}
			if (isBulletShot == 1) {
				bulletY -= bulletSpeed;
			}
			if (bulletY <= 0) {
				isBulletShot = 0;
			}
			if (Collision(enemy->GetPosX(), enemy->GetPosY(), enemy->GetR(),player->GetPosX(), player->GetPosY(), player->GetR(),player->GetIsAlive(),enemy->GetIsAlive()))
			{
				player->OnCollision();
				scene = TITLE;
			}
			if (Collision(enemy->GetPosX(), enemy->GetPosY(), enemy->GetR(), bulletX, bulletY, bulletR, enemy->GetIsAlive(),isBulletShot))
			{
				enemy->OnCollision();
				isBulletShot = 0;
				responflag = 1;
			}
			if (responflag == 1) {
				responTimer--;
			}
			if (responTimer == 0) {
				responTimer = 120;
				responflag = 0;
				enemy->SetIsAlive(1);
			}


			if (isBulletShot == 1)
			{
				Novice::DrawEllipse(bulletX, bulletY, bulletR, bulletR, 0.0f, GREEN, kFillModeSolid);
			}
			break;

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		enemy->Draw();//描画処理に書いて
		player->Draw();//描画処理に書いて
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
