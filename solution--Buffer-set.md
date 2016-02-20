`buffer.cpp`

```c++
void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s) {
    for (int i=0, x=pos_x, y=pos_y; i < s.length(); i++) {
        if (s[i] == '\n') {
            y++;
            x=pos_x;
        } else {
            set(x++, y, s[i]);
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

