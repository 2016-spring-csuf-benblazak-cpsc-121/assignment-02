`neighborhood.cpp`

```c++
Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y)
    : size_x(size_x), size_y(size_y) {

    // initialize `neighborhood_` and fill with "empty" `Shape`s
    neighborhood_ = new Shape[ size_x * size_y ]();

    // fill with non-empty shapes so that the ratio of non-empty to empty
    // shapes is `RATIO_FILLED` (from `constants.h`)
    for (int filled=0; filled < size_x*size_y*RATIO_FILLED; ) {
        unsigned int x = mtrand(0, size_x-1);
        unsigned int y = mtrand(0, size_y-1);

        if (this->get(x, y).getType() == "empty") {
            this->set( x, y, mtrand(0, 1) ? Shape("triangle")
                                          : Shape("square") );
            filled++;
        }
    }
}
```


-------------------------------------------------------------------------------
[![Creative Commons License](https://i.creativecommons.org/l/by/4.0/88x31.png)]
(http://creativecommons.org/licenses/by/4.0/)  
Copyright &copy; 2016 Ben Blazak <bblazak@fullerton.edu>  
This work is licensed under a [Creative Commons Attribution 4.0 International
License] (http://creativecommons.org/licenses/by/4.0/)  
Project located at <https://github.com/2016-spring-csuf-benblazak-cpsc-121>

