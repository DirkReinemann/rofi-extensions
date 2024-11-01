# Extensions for Rofi

Extension for [Rofi](https://github.com/davatorium/rofi) written in C.

## Installation

```bash
# Install in default directory $^
make install

# launch rofi with websearch extension
rofi -show drun -modi "drun,websearch:$PWD/websearch.o"

# launch rofi with websearch extension and google search engine
export ="https://www.google.com/search?q=test"
rofi -show drun -modi "drun,websearch:$PWD/websearch.o"
```

## Extensions

| Name              | Description                            | Config                |
| ---               | ---                                    | ---                   |
| rofi-screenlayout | Lists and execute ARandR shell scripts | ROFI_SCREENLAYOUT_DIR |
| rofi-translate    | Uses the web browser to translate      |                       |

## Development

```bash
# install gcc for compilation, valgrind for memcheck 
sudo pacman -S gcc valgrind

# execute tests
make test
```
