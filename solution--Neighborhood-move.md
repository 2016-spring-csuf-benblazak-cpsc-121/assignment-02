`neighborhood.cpp`

```c++
void Neighborhood::move(unsigned int old_x, unsigned int old_y) {
    for (;;) {
        unsigned int x = mtrand(0, size_x-1);
        unsigned int y = mtrand(0, size_y-1);

        if (get(x, y).getType() == "empty") {
            set(x, y, get(old_x, old_y));
            set(old_x, old_y, Shape("empty"));

            break;
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

