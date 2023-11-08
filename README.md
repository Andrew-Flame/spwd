<div align=center style='text-align: center'>
    <img src='https://img.shields.io/github/repo-size/Andrew-Flame/spwd?style=for-the-badge'/>
    <img src='https://img.shields.io/github/v/release/Andrew-Flame/spwd?style=for-the-badge'/>
    <img src='https://img.shields.io/github/license/Andrew-Flame/spwd?color=%230CD94E&style=for-the-badge'/>
</div>

# SPWD
### Description
"spwd" (short for "Short Present Working Directory") is a program for presenting the current working directory within the width of the terminal. This can be used in the shell prompts, like bash, zsh, fish, etc. to maintain their beautiful appearance

### Usage
```BASH
spwd
# This will just output the current working directory within the width of the terminal
# The symbols "/.../" will be used for the cutting the part of the path
```
```BASH
spwd <width>
# Replace <width> with any integer to explicitly specify the maximum allowable output length
```

### Example
##### Two-line zsh prompt
![](https://github.com/Andrew-Flame/spwd/assets/82677442/acb0d654-457c-4950-b388-d5655b06bbeb)
```BASH
get_aviable_width() { expr $(tput cols) - ${#USER} - ${#HOST} - 10 }
PROMPT=$'%F{blue}┌──($USER@$HOST)-[%F{white}$(spwd $(get_aviable_width))%F{blue}]\n└─$suffix%f '
```
##### One-line zsh prompt
![](https://github.com/Andrew-Flame/spwd/assets/82677442/a7af28ac-a7bf-4e06-916b-7029b9c056e4)
```BASH
get_aviable_width() { expr $(expr $(tput cols) - ${#USER} - ${#HOST} - 10) / 2 }
PROMPT=$'%F{blue}($USER@$HOST)-[%F{white}$(spwd $(get_aviable_width))%F{blue}] $suffix%f '
```

### Installation
#### Manual
To install the program, just copy the code and paste it into the terminal
```BASH
git clone https://github.com/Andrew-Flame/spwd.git /tmp/spwd
cd /tmp/spwd && sudo make clean install
```
#### AUR
You can find this package by [link](https://aur.archlinux.org/packages/spwd)
```BASH
pacaur -S spwd
```
