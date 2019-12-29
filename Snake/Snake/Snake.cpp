// sebelum test jalanin setting sfmlmnya dulu di release sama jalanin di release
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace sf;

int main() {
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "Snake The Game!!");
	
	//anggap saja supaya pada menu tidak terlalu cepat berpindah
	int clk = 0;

	//gambar yang ditampilkan pada menu
	Texture MBG;
	MBG.loadFromFile("img/Menu.png");
	Sprite mbg(MBG);
	Texture dif1;
	dif1.loadFromFile("img/Easy1.png");
	Sprite easy1(dif1);
	easy1.setPosition(250, 100);
	Texture dif2;
	dif2.loadFromFile("img/Medium1.png");
	Sprite med1(dif2);
	med1.setPosition(250, 250);
	Texture dif3;
	dif3.loadFromFile("img/Hard1.png");
	Sprite hard1(dif3);
	hard1.setPosition(250, 400);
	Texture dif12;
	dif12.loadFromFile("img/Easy2.png");
	Sprite easy2(dif12);
	easy2.setPosition(250, 100);
	Texture dif22;
	dif22.loadFromFile("img/Medium2.png");
	Sprite med2(dif22);
	med2.setPosition(250, 250);
	Texture dif32;
	dif32.loadFromFile("img/Hard2.png");
	Sprite hard2(dif32);
	hard2.setPosition(250, 400);

	int l = 1; //panjang ular
	int x1[1200]; //koordinat tubuh ular di x, panjang maks 1200 (belum tau caranya jadiin 4800 biar beneran maks)
	x1[0] = 0; // koordinat kepala ular di x, awalnya di set ke 0
	int y1[1200]; // koordinat tubuh ular di y
	y1[0] = 0; // koordinat kepala ular di x, awalnya di set ke 0

	int x2 = rand() % 80 * 10; // koordinat makanan di x
	int y2 = rand() % 60 * 10; // koordinat makanan di y

	// gambar yang ditampilkan pada saat game berjalan
	Texture BG;
	BG.loadFromFile("img/putih.png");
	Sprite bg(BG);
	Texture Snake;
	Snake.loadFromFile("img/hitam.png");
	Sprite snake(Snake);
	Texture Food;
	Food.loadFromFile("img/hitam.png");
	Sprite food(Food);
	food.setPosition(x2, y2);

	int dif = 0; // tingkat kesulitan
	int point = 0; // penunjuk pada menu

	int a = 100; // patokan kecepatan
	int v = 0; // kecepatan
	int x = 1; // jarak pindahnya ular di x
	int y = 0; // jarak pindahnya ular di y

	bool lose = false; // kondisi kalah/mati

	// gambar yang ditamilkan setelah kalah/mati
	Texture LBG;
	LBG.loadFromFile("img/Lose.png");
	Sprite lbg(LBG);
	Texture Yes1;
	Yes1.loadFromFile("img/Yes1.png");
	Sprite yes1(Yes1);
	yes1.setPosition(250, 200);
	Texture No1;
	No1.loadFromFile("img/No1.png");
	Sprite no1(No1);
	no1.setPosition(250, 400);
	Texture Yes2;
	Yes2.loadFromFile("img/Yes2.png");
	Sprite yes2(Yes2);
	yes2.setPosition(250, 200);
	Texture No2;
	No2.loadFromFile("img/No2.png");
	Sprite no2(No2);
	no2.setPosition(250, 400);

	// untuk mencatat score
	FILE* score;
	score = fopen("Score.txt", "a");

	while (window.isOpen()) {
		if (dif == 0) { // dif = 0 (tingkat kesulitan belum dipilih) menampilkan menu
			window.draw(mbg); // menampilkan bg menu
			(point == 0) ? window.draw(easy2) : window.draw(easy1); // menampilkan pilihan tingkat kesulitan
			(point == 1) ? window.draw(med2) : window.draw(med1); // menampilkan pilihan tingkat kesulitan
			(point == 2) ? window.draw(hard2) : window.draw(hard1); // menampilkan pilihan tingkat kesulitan

			if (Keyboard::isKeyPressed(Keyboard::Up)) { // bila tombol naik ditekan pilihan akan naik
				clk++;
				if (clk > 75) {
					point--;
					if (point < 0)
						point = 2;
					clk = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) { // bila tombol bawah ditekan pilihan akan turun
				clk++;
				if (clk > 75) {
					point++;
					if (point > 2)
						point = 0;
					clk = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) { // bila tombol enter ditekan akan masuk ke dalam game
				clk++;
				if (clk > 75) {
					dif = pow(2, point); // tingkat kesulitan = 2^pilihan (easy = 0, med = 1, hard = 4) penjelasan lebih lanjut dibawah

					point = 0;
					clk = 0;
				}
			}
				
		}

		else if (!lose) { // bagian saat game dijalankan
			window.draw(bg); // menampilkan bg game
			window.draw(food); // menampilkan makanan
			for (int i = 0; i < l; i++) { // menampilkan ular
				snake.setPosition(x1[i], y1[i]); // set posisi ular pada array x1 dan y1
				window.draw(snake);
			}

			// perubahan pergerakan ular
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				x = 0;
				y = -1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				x = 0;
				y = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				x = -1;
				y = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				x = 1;
				y = 0;
			}

			v++;
			if (v > a / dif) { // apabila kecepatan sudah melebihi a/dif ular akan bergerak
				for (int i = l; i > 0; i--) { // pengaturan posisi ular jadi posisi belakang = posisi depannya
					x1[i] = x1[i - 1];
					y1[i] = y1[i - 1];
				}

				// pengaturan posisi kepala ular
				x1[0] += x * 10;
				y1[0] += y * 10;

				v = 0;
			}

			// biar bisa nembus dan balik
			if (x1[0] < 0)
				x1[0] = 800;
			if (y1[0] < 0)
				y1[0] = 600;
			if (x1[0] > 800)
				x1[0] = 0;
			if (y1[0] > 600)
				y1[0] = 0;

			// ular makan/ posisi kepala ular sama dengan posisi makanan
			if (x1[0] == x2 && y1[0] == y2) {
				l++;

				x2 = rand() % 80 * 10;
				y2 = rand() % 60 * 10;

				food.setPosition(x2, y2);
			}

			// pengecekan kalah/ mati (posisi kepala ular sama dengan salah satu posisi badan ular)
			for (int i = 1; i < l; i++) {
				if (x1[0] == x1[i] && y1[0] == y1[i]) {
					lose = true;
					point = 0;

					fprintf(score, "Your Last Score : %d\n", l); // nyatet score di file Score.txt
				}
			}
		}

		else { // pmenu pada saat kalah
			window.draw(lbg);

			(point == 0) ? window.draw(yes2) : window.draw(yes1);
			(point == 1) ? window.draw(no2) : window.draw(no1);

			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				clk++;
					if (clk > 75) {
						point--;
						if (point < 0)
							point = 1;
						clk = 0;
					}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				clk++;
				if (clk > 75) {
					point++;
					if (point > 1)
						point = 0;
					clk = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				clk++;
				if (clk > 75) {

					if (point == 0) { // kondisi pingin main lagi, set semua ke awal lagi
						dif = 0;

						l = 1;
						x1[0] = 0;
						y1[0] = 0;

						v = 0;
						x = 1;
						y = 0;

						x2 = rand() % 80 * 10;
						y2 = rand() % 60 * 10;
						food.setPosition(x2, y2);

						point = 0;
						clk = 0;

						lose = false;
					}
					else
						window.close(); // kondisi kalau nggak pingin main lagi, nutup window
				}
			}
		}

		// kejadian apabila windows ditutup (klik tombol silang) aplikasi juga nutup
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		window.display();
	}

	fclose(score);

	return 0;
}