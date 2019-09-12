# Physics Engine
Projet 8INF935 réalisé par Bertrand Gilbert-Collet, Yoann Haffner, Louis Lavarone, Baptiste Rey

## Installation
TODO

## Prise en main du projet avec Visual Studio
+ Fichier > nouveau > Projet à partir de code existant... *Mis à part le nom (PhysicsEngine) et le dossier de projet, tout est par défaut*
+ NuGet: installer 'sdl2.nuget', 'sdl2_image.nuget' et 'nupengl.core'
+ Projet > propriétés, puis Editeur de liens > entrée. Ajouter si absent "opengl32.lib;" avant le "%(AdditionalDependencies)"
+ Le projet est normalement fonctionnel. Si l'explorateur de projet affiche des filtres (séparant les headers des sources), il est conseillé de cliquer sur 'Afficher tous les fichiers'