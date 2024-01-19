



<img align="right" width="32%" src="./misc/roc_2.png">

wannabe ros2 command replacer
===
#### robot operations command - roc

[SUPER EARLY STAGE] at the moment it calls ros2 commands externally, but the goal is to have a single binary that can be used to replace the ros2 command line tool. 

## Usage
```
roc <COMMAND> [SUBCOMMAND] [OPTIONS] [ARGS]
```
<hr>



## Installation

```bash
cargo install rocc
```


## Features

- [ ] usual ros2 commands
- [ ] workspace creation and build commands
- [ ] coordinate frame commands
- [ ] bridge commands (foxglove & rosbridge)
- [ ] ros bag utilities
- [ ] daemon tools


## Commands

```
Usage:  roc <COMMAND>

Monotor Commands:
  action      [a]    Various action subcommands
  topic       [t]    Various topic subcommands
  service     [s]    Various service subcommands
  param       [p]    Various param subcommands
  node        [n]    Various node subcommands
  interface   [i]    Various interface subcommands
  frame       [f]    Various transforms subcommands [WIP]

Workspace Commands:
  run         [r]    Run an executable
  launch      [l]    Launch a launch file
  work        [w]    Various workspace subcommands

Utilities Commands:     
  bag         [b]    Various rosbag subcommands
  daemon      [d]    Deamon and bridge subcommands [WIP]
  middleware  [m]    Various middleware subcommands [WIP]
```

## Why?

Why not? Rust is fun and I wanted to learn more how to interact with the ros2 api.

## Roadmap

- [ ] make every command call the ros2 api directly
- [ ] use https://github.com/ros2-rust/ros2_rust as a library
- [ ] add more commands (e.g. ros2 doctor)
- [ ] add more tests
