ADS Lighting shader - done
make a linker method (???)

02/12/25
MainGame.cpp 184, 1; linkADSLighting
bind texture and skybox, similarly to the envMapping
sample the texture so it displays the original mesh
mix texture sampling, light colour, and whatever the fuck else
to get the FragColour

03/12/25
Normals on Caster mesh are potentially backwards.
Change model to be a ball mesh and scale it on Z?
    fixed. alt drawing bool flip 
    in MainGame::UpdateGameObject(GameObject&...)

04/12/25
Culling seems to be broken on the monkey, with the .geom shader.