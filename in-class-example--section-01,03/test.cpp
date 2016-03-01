#include <iostream>
#include <string>
#include <thread>
#include <chrono>
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

    public:
        const int sizex;
        const int sizey;

        Buffer(int sx, int sy) : sizex(sx), sizey(sy) {
            data = new char[sx * sy];

            for(int y = 0; y < sizey; y++) {
                for(int x = 0; x < sizex; x++) {
                    data[y * sizex + x] = ' ';
                }
            }
        }

        ~Buffer() {
            delete[] data;
        }

        void draw() const {
            for(int y = 0; y < sizey; y++) {
                for(int x = 0; x < sizex; x++) {
                    cout << data[y * sizex + x];
                }
                cout << endl;
            }
        }

        void set(int x, int y, char c) {
            data[y * sizex + x] = c;
        }

        char get(int x, int y) const {
            return data[y * sizex + x];
        }
};

class Shape {
    private:
    public:
        static const int sizex = 5;
        static const int sizey = 3;
        string type;
        string typeart;

        Shape(string t = "empty") {
            type = t;
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

        void drawToBuffer(Buffer & b, int x, int y) const {
            int originalx = x;
            int originaly = y;
            for (int i = 0; i < typeart.length(); i++) {
                if (typeart[i] == '\n') {
                    y++;
                    x = originalx;
                } else {
                    b.set(x, y, typeart[i]);
                    x++;
                }
            }
        }

        bool isHappy() const {
            return false;
        }
};

class Neighborhood {
    private:
        const int sizex;
        const int sizey;
        Shape * data;

    public:
        Neighborhood(int x, int y) : sizex(x), sizey(y) {
            data = new Shape[ sizex * sizey ]();

            int counter = 0;
            while (counter/double(sizex*sizey) < 0.40) {
                int x = mtrand(0, sizex-1);
                int y = mtrand(0, sizey-1);

                if ( data[ y * sizex + x ].type != "empty" )
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

        void move(int oldx, int oldy) {
            for(;;) {
                int x = mtrand(0, sizex-1);
                int y = mtrand(0, sizey-1);

                if ( data[ y * sizex + x ].type != "empty" )
                    continue;

                data[ y * sizex + x ] = data[ oldy * sizex + oldx ];
                data[ oldy * sizex + oldx ] = Shape("empty");

                break;
            }
        }

        void animate(int frames) {
            Buffer b(sizex * Shape::sizex, sizey * Shape::sizey);

            for (int i = 0; i < frames; i++) {
                for(int y = 0; y < sizey; y++) {
                    for(int x = 0; x < sizex; x++) {
                        data[ y * sizex + x ].drawToBuffer( b,
                                                            x*Shape::sizex,
                                                            y*Shape::sizey );
                    }
                }

                b.draw();

                for(int y = 0; y < sizey; y++) {
                    for(int x = 0; x < sizex; x++) {
                        if (! data[ y * sizex + x ].isHappy())
                            move(x,y);
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
};

int main() {
    Neighborhood n(80/Shape::sizex, 25/Shape::sizey);
    n.animate(100);

    return 0;
}

