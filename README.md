# Physics Engine
Projet 8INF935 réalisé par Bertrand Gilbert-Collet, Yoann Haffner, Louis Iavarone, Baptiste Rey

### Compilation
Le dossier du projet comprend les fichiers nécessaires à la compilation via CMake, qu'il est donc nécessaire d'installer.

## Prise en main du projet avec Visual Studio
+ Fichier > nouveau > Projet à partir de code existant... *Mis à part le nom (PhysicsEngine) et le dossier de projet, tout est par défaut*
+ NuGet: installer 'sdl2.nuget', 'sdl2_image.nuget' et 'nupengl.core'
+ Projet > propriétés, puis Editeur de liens > entrée. Ajouter si absent "opengl32.lib;" avant le "%(AdditionalDependencies)"
+ Le projet est normalement fonctionnel. Si l'explorateur de projet affiche des filtres (séparant les headers des sources), il est conseillé de cliquer sur 'Afficher tous les fichiers'

## Commandes du jeu
+ a : Envoie une balle simple
+ z : Fait apparaitre une balle tombante
+ e : Envoie une balle simple
+ r : Fait apparaitre deux balles, dont une retenue grace à un ressort
+ q : Fait apparaitre une balle avec un effet de flottaison, ainsi qu'une balle repère pour la surface de l'eau
+ d : Fait apparaitre deux balles, reliées par une tige solide

+ Flèches directionnelles : Permet de controller la particule au centre du Blob
+ Espace : Assemble et désassemble le Blob