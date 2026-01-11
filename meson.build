project('Tic Tac Toe Game', 'cpp', version : '0.1', default_options : ['cpp_std=c++20'])

sdl3_inc = include_directories('C:/libs/SDL3-3.4.0/x86_64-w64-mingw32/include')
sdl3_lib_dir = 'C:/libs/SDL3-3.4.0/x86_64-w64-mingw32/lib'

sdl3_img_inc = include_directories('C:/libs/SDL3_image-3.2.4/x86_64-w64-mingw32/include')
sdl3_img_lib = 'C:/libs/SDL3_image-3.2.4/x86_64-w64-mingw32/lib'

sdl3_ttf_inc =  include_directories('C:/libs/SDL3_ttf-3.2.2/x86_64-w64-mingw32/include')
sdl3_ttf_lib = 'C:/libs/SDL3_ttf-3.2.2/x86_64-w64-mingw32/lib'

sdl3_mix_inc = include_directories('C:/libs/SDL3_mixer_compiled/include')
sdl3_mix_lib = 'C:/libs/SDL3_mixer_compiled/lib'

json_dep = dependency('nlohmann_json')

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
  'Sprite.cpp',
  'AssetManager.h',
  'AssetManager.cpp',
  'Asset.h',
  'AssetFactory.h',
  'AssetFactory.cpp',
  'AssetID.h',
  'GameObject.h',
  'GameObject.cpp',
  'CollisionSystem.h',
  'Timer.h',
  'Timer.cpp',
  'AIController.h',
  'AIController.cpp',
  'GameLogic.h',
  'GameLogic.cpp',
  'Utils.h',
  'GameObjectFactory.h',
  'GameObjectFactory.cpp',
  'Scene.cpp',
  'Renderable.h',
  'CharacterTexture.h',
  'CharacterTexture.cpp',
  'FontAtlas.h',
  'FontAtlas.cpp',
  'Text.h',
  'Text.cpp',
  'Audio.h',
  'Audio.cpp',
  'AudioSource.h',
  'AudioSource.cpp',
  'TestScene.h',
  'TestScene.cpp',
  'RectLayout.h',
  'RectLayout.cpp'
]

executable(
  'TicTacToe',
  sources,
  include_directories : [sdl3_inc, sdl3_img_inc, sdl3_ttf_inc, sdl3_mix_inc],
  link_args : [
    '-L' + sdl3_lib_dir, 
    '-L' + sdl3_img_lib,
    '-L' + sdl3_ttf_lib,
    '-L' + sdl3_mix_lib,
    '-lSDL3',
    '-lSDL3_image',
    '-lSDL3_ttf',
    '-lSDL3_mixer'
  ],
  dependencies: [json_dep]
)
