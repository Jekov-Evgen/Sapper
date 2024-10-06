#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(400, 400), "sapper");

	int width = 32;
	int gridLogic[12][12];
	int drawView[12][12];

	Texture squares;
	squares.loadFromFile("image/tiles.jpg");
	Sprite s(squares);

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			drawView[i][j] = 10;
			if (rand() % 5 == 0) {
				gridLogic[i][j] = 9;
			}
			else 
			{
				gridLogic[i][j] = 0;
			}
		}

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) {
				continue;
			}

			if (gridLogic[i + 1][j] == 9) {
				n++;
			}

			if (gridLogic[i][j + 1] == 9) {
				n++;
			}

			if (gridLogic[i - 1][j] == 9) {
				n++;
			}

			if (gridLogic[i][j - 1] == 9) {
				n++;
			}

			if (gridLogic[i + 1][j + 1] == 9) {
				n++;
			}

			if (gridLogic[i - 1][j - 1] == 9) {
				n++;
			}

			if (gridLogic[i - 1][j + 1] == 9) {
				n++;
			}

			if (gridLogic[i + 1][j - 1] == 9) {
				n++;
			}

			gridLogic[i][j] = n;
		}

	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / width;
		int y = pos.y / width;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Left) {
					drawView[x][y] = gridLogic[x][y];
				}
				else if (event.key.code == Mouse::Right) {
					drawView[x][y] = 11;
				}
			}
		}

		window.clear(Color::White);

		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++) {
				if (drawView[x][y] == 9) {
					drawView[i][j] = gridLogic[i][j];
				}

				s.setTextureRect(IntRect(drawView[i][j] * width, 0, width, width));

				s.setPosition(i * width, j * width);

				window.draw(s);
			}
		}

		window.display();
	}

	return 0;
}