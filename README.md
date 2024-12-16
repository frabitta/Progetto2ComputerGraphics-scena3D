# Progetto2-scena3D
Un piccolo e semplice visualizzatore/editor di semplici scene 3D con OpenGL e ImGUI

## features
- creazione di geometrie
- caricamento di file .obj
- applicazione di materiali (Illuminazione Phong/Blinn-Phong)
- 2 luci puntiformi
- applicazione di texture
- trasformazioni geometriche
- animazione "ad onda"

## navigazione della scena
- premere 'N' per attivare la navigazione tramite WASD + mouse
- girare attorno ad un oggetto tenendo premuto il tasto della rotellina
- rotellina per zoom
- 'esc' per uscire dalla navigazione
- selezionare col tasto sinistro i modelli con cui si vuole interagire

# Uso
1. Scaricare la repository
2. Aprire la soluzione in Visual Studio aprendo il file `.sls`
3. Impostare la modalità di compilazione a "release"
4. In 'Project Properties' -> 'Linker' -> 'General' -> 'Additional Library Directories' imposta il percorso della cartella contenente le seguenti librerie dinamiche: `glfw3.lib;opengl32.lib;assimp-vc142-mt.lib;assimp-vc142-mtd.lib;`

Per modificare la scena visualizzata, modificare `initScene()` in `scena.cpp`.
