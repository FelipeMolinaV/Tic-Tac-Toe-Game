project('Tic Tac Toe Game', 'cpp', version : '0.1', default_options : ['cpp_std=c++17'])

sdl3_inc = include_directories('C:/libs/SDL3-3.2.26/x86_64-w64-mingw32/include')
sdl3_lib_dir = 'C:/libs/SDL3-3.2.26/x86_64-w64-mingw32/lib'

sources = [
  'main.cpp',
  'Game.h',
  'Game.cpp',
  'SceneManager.h',
  'SceneManager.cpp',
  'Scene.h',
  'SceneType.h',
  'GameScene.h',
  'GameScene.cpp',
  'GameState.h',
]

executable(
  'TicTacToe',
  sources,
  include_directories : [sdl3_inc],
  link_args : ['-L' + sdl3_lib_dir, '-lSDL3']
)

