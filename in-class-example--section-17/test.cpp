#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

using std::string;

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
};

class Neighborhood {
    private:
        Shape * data;
        int sizex;
        int sizey;

    public:
        Neighborhood(int sizex, int sizey) : sizex(sizex), sizey(sizey) {
            data = new Shape[sizex * sizey]();
        }

        ~Neighborhood() {
            delete[] data;
        }

        void animate(int frames) {
            Buffer b(sizex*Shape::sizex, sizey*Shape::sizey);

            for (int y = 0; y < sizey; y++) {
                for (int x = 0; x < sizex; x++) {
                    b.set( x*Shape::sizex,
                           y*Shape::sizey,
                           data[ y * sizex + x ].typeart );
                }
                cout << endl;
            }

            b.draw();
        }
};

int main() {
    Neighborhood n(80/Shape::sizex, 25/Shape::sizey);
    n.animate(1);

    return 0;
}

