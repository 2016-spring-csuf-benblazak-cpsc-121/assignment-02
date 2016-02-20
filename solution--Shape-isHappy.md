`shape.cpp`

```c++
bool Shape::isHappy( const Neighborhood & n,
                     unsigned int pos_x,
                     unsigned int pos_y) const {

    if (n.get(pos_x, pos_y).getType() == "empty")
        return true;

    unsigned int x_min = (pos_x == 0) ? pos_x : pos_x - 1;
    unsigned int y_min = (pos_y == 0) ? pos_y : pos_y - 1;

    unsigned int x_max = (pos_x == n.size_x-1) ? pos_x : pos_x + 1;
    unsigned int y_max = (pos_y == n.size_y-1) ? pos_y : pos_y + 1;

    double alike = 0;
    double different = 0;

    for (int x=x_min; x <= x_max; x++) {
        for (int y=y_min; y <= y_max; y++) {
            if (x == pos_x && y == pos_y)
                continue;
            else if (n.get(x, y).getType() == "empty")
                continue;
            else if (n.get(x, y).getType() == n.get(pos_x, pos_y).getType())
                alike++;
            else 
                different++;
        }
    }

    return    ( different || alike )
           && ( different == 0 || alike / different >= RATIO_ALIKE_HAPPY )
           && ( alike == 0 || different / alike >= RATIO_DIFFERENT_HAPPY );
}
```


-------------------------------------------------------------------------------
[![Creative Commons License](https://i.creativecommons.org/l/by/4.0/88x31.png)]
(http://creativecommons.org/licenses/by/4.0/)  
Copyright &copy; 2016 Ben Blazak <bblazak@fullerton.edu>  
This work is licensed under a [Creative Commons Attribution 4.0 International
License] (http://creativecommons.org/licenses/by/4.0/)  
Project located at <https://github.com/2016-spring-csuf-benblazak-cpsc-121>

