# 3/28/24 - Iniital Commit

I am an American. We do our dates this way. Get over it.

This is the initial commit. I have a window that renders some text, as well as many "helper" files for drawing / playing assets.

These are found in `render/` for graphics and `utils/` for everything else. I know naming a folder "utils" is probably not a good thing, but it works for me.

# 3/29/24 - Volume + Consistency Fix

Added little descriptions to the changelog, like `- Initial Commit`.

Updated consistency between header files...

- method names are camelCase
- parameters are prefixed `p_` and have no spaces or capitalization
- slight grammar update to `render/RenderWindow.hpp/cleanup` method.
  - Apparently, the verb form of this word is actually two seperate words. (all I did was change the U to capital lmao)

This consistency fix applies to: `render/DrawnTexture.hpp`, `render/Font.hpp`, `render/RenderWindow.hpp`, and `utils/Sound.hpp`

`utils/Sound.hpp` got another update, adding the ability to get and set volume of a sound.

# 3/29/24 - More Sound Fixes

`utils/Sound.hpp` got yet another update:

- Put every sound-related function in a namespace.
- Added `open`, `openDevice`, `changeDevice`, `listDevices`, and `close` methods

`main.cpp`:

- Removed the extremely stupid variant from `textures` vector in `main.hpp`

# 3/29/24 - Forgot some things from last commit

`utils/main.cpp`:

- Forgot to replace some name changes from `utils/Sound.hpp` onto the actual `main` file
- Forgot to close the audio once the window cleans up