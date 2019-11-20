# Physics Engine
Projet 8INF935 réalisé par Bertrand Gilbert-Collet, Yoann Haffner, Louis Iavarone, Baptiste Rey

## Prise en main du projet avec Visual Studio
+ Fichier > nouveau > Projet à partir de code existant... *Mis à part le nom (PhysicsEngine) et le dossier de projet, tout est par défaut*
+ NuGet: installer 'sdl2.nuget', 'sdl2_image.nuget' et 'nupengl.core'
+ Projet > propriétés, puis Editeur de liens > entrée. Ajouter si absent "opengl32.lib;" avant le "%(AdditionalDependencies)"
+ Le projet est normalement fonctionnel. Si l'explorateur de projet affiche des filtres (séparant les headers des sources), il est conseillé de cliquer sur 'Afficher tous les fichiers'
+ Si tu veux éditer des fichiers GLSL (shader), je te conseille le plugin d'intégration suivant: https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

## Commandes du jeu
+ a : Créer un cube avec une force qui provoque translation et rotation.
+ b : Créer un cube avec une force qui provoque translation et rotation.
+ g : Créer deux voitures qui se déplacent l'une vers l'autre et se frappent.
