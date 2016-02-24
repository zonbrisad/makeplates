# Makeplates

Makefile templates is a set of example makefiles.


### Makefile 

#### Links

- [Panda fruits](http://pandafruits.com/stm32_primer/stm32_primer_minimal.php)


### Color encoding

#### Links
- [Colormake](https://github.com/renatosilva/colormake/blob/master/colormake.sh)
- [highlight-and-filter-gcc-compiler-messages](http://stackoverflow.com/questions/1032237/highlight-and-filter-gcc-compiler-messages)


##### Some leftovers
```bash
while read x ; do echo $x ; done \
| sed -e "s/.*error:.*/\x1b[1;36m&\x1b[0m/" \
-e "s/.*warning:.*/\x1b[1;36m&\x1b[0m/" \
-e "s/^\(.*\)\(required from\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
-e "s/^\(.*\)\(In instantiation of\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
-e "s/^\(.*\)\(In member\)/\x1b[1;36m\1\x1b[0mnote: \2/" \
| sed -e "s/error:/\x1b[1;31m&\x1b[1;36m/" \
-e "s/warning:/\x1b[1;35m&\x1b[1;36m/" \
-e "s/note:/\x1b[1;30m&\x1b[0m/"
```
