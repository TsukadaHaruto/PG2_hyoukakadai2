#pragma once

class Enemy
{
private:
	///メンバ変数ここから
	///
	int x_;
	int y_;
	int speed_;
	int r_;
	int isAlive_;
	int life_;//死ぬまでのカウント
	///
	///メンバ変数ここまで
public:
	///メンバ関数ここから
	///
	
	void Initalize();//初期化関数
	void Update();//更新処理
	void Draw();//描画処理4
	void OnCollision();
	int GetIsAlive() { return isAlive_; }
	void SetIsAlive(int isAlive) { isAlive_ = isAlive; }
	int GetPosX() { return x_; }
	int GetPosY() { return y_; }
	int GetR() { return r_; }

	///
	///メンバ関数ここまで
};
