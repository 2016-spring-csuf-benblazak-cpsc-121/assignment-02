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

        char get(int x, int y) {
            return data[y * sizex + x];
        }

        // TODO: move to Shape (because of "incomplete type")
        void drawShape(int x, int y, const Shape & s) {
            int originalx = x;
            int originaly = y;
            for (int i = 0; i < s.typeart.length(); i++) {
                if (s.typeart[i] == '\n') {
                    y++;
                    x = originalx;
                } else {
                    set(x, y, s.typeart[i]);
                    x++;
                }
            }
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


};

int main() {
    Buffer b(80, 25);
    Shape s("triangle");
    b.drawShape(5, 10, s);
    b.draw();

    return 0;
}

