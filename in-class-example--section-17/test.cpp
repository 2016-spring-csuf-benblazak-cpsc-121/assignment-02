#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <random>

using std::cout;
using std::cin;
using std::endl;

using std::string;

// ----------------------------------------------------------------------------

unsigned int mtrand(unsigned int low, unsigned int high) {
    static std::random_device rd;
    static std::mt19937 mt(rd());  // engine (mersenne twister)

    return std::uniform_int_distribution<unsigned int>(low, high)(mt);
}

// ----------------------------------------------------------------------------

class Buffer {
    private:
        char * data;
        int sizex;
        int sizey;

    public:
        Buffer(int sizex, int sizey) : sizex(sizex), sizey(sizey) {
            data = new char[sizex * sizey];

            for (int y = 0; y < sizex; y++) {
                for (int x = 0; x < sizex; x++) {
                    data[ y * sizex + x ] = ' ';
                }
            }
        }

        ~Buffer() {
            delete[] data;
        }

        void draw() {
            for (int y = 0; y < sizey; y++) {
                for (int x = 0; x < sizex; x++) {
                    cout << data[ y * sizex + x ];
                }
                cout << endl;
            }
        }

        void set(int x, int y, char c) {
            data[ y * sizex + x ] = c;
        }

        char get(int x, int y) const {
            return data[ y * sizex + x ];
        }

        void set(int x, int y, string s) {
            int xx = x;
            int yy = y;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '\n') {
                    xx = x;
                    yy++;
                } else {
                    set(xx++, yy, s[i]);
                }
            }
        }
};

class Shape {
    public:
        string type;
        string typeart;

        static const int sizex = 5;
        static const int sizey = 3;

        Shape(string type = "empty") : type(type) {
            if (type == "empty")
                typeart = "     \n"
                          "     \n"
                          "     \n";
            else if (type == "triangle")
                typeart = "  .  \n"
                          " . . \n"
                          ".....\n";
            else if (type == "square")
                typeart = ".....\n"
                          ".   .\n"
                          ".....\n";
        }

        bool isHappy() {
            return false;
        }
};

class Neighborhood {
    private:
        Shape * data;
        int sizex;
        int sizey;

    public:
        Neighborhood(int sizex, int sizey) : sizex(sizex), sizey(sizey) {
            data = new Shape[sizex * sizey]();

            int counter = 0;
            double ratiofilled = 0.40;
            while (counter/double(sizex*sizey) < ratiofilled) {
                int x = mtrand(0, sizex-1);
                int y = mtrand(0, sizey-1);

                if (data[ y * sizex + x ].type != "empty")
                    continue;

                if (mtrand(0,1))
                    data[ y * sizex + x ] = Shape("triangle");
                else
                    data[ y * sizex + x ] = Shape("square");

                counter++;
            }
        }

        ~Neighborhood() {
            delete[] data;
        }

        void move(int x, int y) {
            for (;;) {
                int newx = mtrand(0, sizex-1);
                int newy = mtrand(0, sizey-1);

                if ( data[ newy * sizex + newx ].type != "empty" )
                    continue;

                data[ newy * sizex + newx ] = data[ y * sizex + x ];
                data[ y * sizex + x ] = Shape("empty");

                break;
            }
        }

        void animate(int frames) {
            Buffer b(sizex*Shape::sizex, sizey*Shape::sizey);

            for (int f = 0; f < frames; f++) {
                for (int y = 0; y < sizey; y++) {
                    for (int x = 0; x < sizex; x++) {
                        b.set( x*Shape::sizex,
                               y*Shape::sizey,
                               data[ y * sizex + x ].typeart );
                    }
                }

                b.draw();

                for (int y = 0; y < sizey; y++) {
                    for (int x = 0; x < sizex; x++) {
                        if ( ! data[ y * sizex + x ].isHappy() )
                            move(x, y);
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
};

int main() {
    Neighborhood n(80/Shape::sizex, 25/Shape::sizey);
    n.animate(50);

    return 0;
}

