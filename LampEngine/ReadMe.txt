========================================================================
    LampEngine Project Overview
========================================================================

Basically just a simple hobby 3D Engine using techniques I've learned so far.
If you want to build / or try it, I suggest you send me an e-mail ( steffene92@gmail.com ).

Planned features:
* Lua Embedding
* Realtime resource editing ( eg, edit shaders/models/textures realtime ).
	This will be done by using the OS onFileChanged events, and then the engine will just reload the asset.
	There will be an asset manager that tracks all assets, making this feature a possibility.
* Shadows
	I will be trying to implement the Variance Shadow Mapping technique
	thebennybox has some nice information describing the technique and it's implementation
	https://www.youtube.com/user/thebennybox (I will be using some tips and tricks learned here)

* Defered Rendering
	I plan to implement this rendering technique and to play with it's capabilities.
	Not sure if I am going to add a second renderer for Forward Rendering, I don't think that should 
	be to hard since most of the actions that Defered Rendering does is just shaders.

* Screen Space Ambient Occlusion ( SSAO )
	I really like how SSAO can change the feel of a scene, so I will be having a go at this.
	To be honest, I haven't really looked much at how AO in general works, but I'll find that out!

I will be adding/removing information here as time progresses.
I might be posting some progress videos on youtube or something, I don't know just yet.

Dependencies:

freetype-2.4.0
SDL2
glew-1.10.0
glm
lua-5.2.3

