ADS Lighting shader
make a linker method (???)

observe deltatime & counter tick count. last check it was
incrementing in microseconds and not seconds, returning
1000x its correct value.

02/12/25
MainGame.cpp 184, 1; linkADSLighting
bind texture and skybox, similarly to the envMapping
sample the texture so it displays the original mesh
mix texture sampling, light colour, and whatever the fuck else
to get the FragColour