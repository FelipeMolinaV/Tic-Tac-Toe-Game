project('Tic Tac Toe Game', 'cpp', version : '0.1', default_options : ['cpp_std=c++17'])

sdl3_inc = include_directories('C:/libs/SDL3-3.2.26/x86_64-w64-mingw32/include')
sdl3_lib_dir = 'C:/libs/SDL3-3.2.26/x86_64-w64-mingw32/lib'

sdl3_img_inc = include_directories('C:/libs/SDL3_image-3.2.4/x86_64-w64-mingw32/include')
sdl3_img_lib = 'C:/libs/SDL3_image-3.2.4/x86_64-w64-mingw32/lib'

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
  'Texture.h',
  'Texture.cpp',
  'Sprite.h',
  'Sprite.cpp'
]

executable(
  'TicTacToe',
  sources,
  include_directories : [sdl3_inc, sdl3_img_inc],
  link_args : [
    '-L' + sdl3_lib_dir, 
    '-L' + sdl3_img_lib,
    '-lSDL3',
    '-lSDL3_image'
  ]
)

