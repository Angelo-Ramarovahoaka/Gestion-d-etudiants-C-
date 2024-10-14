## Gestionnaire d'Étudiants en C++

Le **Gestionnaire d'Étudiants** est une application C++ qui permet de gérer efficacement des informations sur des étudiants via une interface CGI (Common Gateway Interface). Le projet est conçu pour faciliter l'ajout, la modification, la suppression et l'affichage des données des étudiants, tout en offrant une interface web simple et interactive.

### Fonctionnalités principales :
- **Ajout d'étudiants** : Permet l'insertion des informations des étudiants dans un fichier `students.txt`. Chaque étudiant possède les champs suivants :
  - Prénom
  - Nom
  - Parcours
  - Date de naissance
  - Adresse
  - Sexe
- **Affichage des étudiants** : Les données des étudiants sont affichées sous forme de tableau HTML. Chaque ligne comprend des actions permettant de consulter les détails ou de supprimer un étudiant.
- **Modification des données** : Chaque étudiant peut être modifié via un formulaire dédié.
- **Suppression d'un étudiant** : Supprime définitivement un étudiant de la liste et du fichier.
- **Validation des données** : Les informations telles que l'adresse e-mail et le numéro de téléphone sont validées avec des expressions régulières, garantissant des entrées correctes.

### Architecture :
L'application repose sur une architecture orientée objet, avec une classe principale `StudentManager` qui gère toutes les opérations liées aux étudiants, telles que :
- `addStudent()` : Ajoute un nouvel étudiant dans le fichier.
- `displayStudents()` : Affiche tous les étudiants sous forme de tableau HTML.
- `deleteStudent()` : Supprime un étudiant en fonction de son identifiant.
- `updateStudent()` : Permet de modifier les informations d'un étudiant.
- `validateEmail()` : Valide l'adresse e-mail selon des critères définis (par exemple, uniquement les adresses se terminant par `@gmail.com`).

### Technologies utilisées :
- **C++** : Pour la gestion du backend et les opérations de traitement des fichiers.
- **CGI** : Pour permettre l'interaction entre le serveur web et le programme C++, facilitant l'affichage dynamique des données.
- **HTML/CSS** : Pour la création d'une interface utilisateur simple et intuitive.
- **Expressions régulières** : Pour la validation des données utilisateurs, comme les e-mails et les numéros de téléphone.

### Cas d'utilisation :
Le projet est conçu pour des établissements académiques ou toute organisation nécessitant la gestion des données d'étudiants, où les administrateurs peuvent ajouter, consulter et modifier les informations des étudiants de manière intuitive via une interface web.

### Objectifs :
- Offrir une solution légère et portable pour la gestion des étudiants.
- Utiliser des technologies standards comme CGI et C++ pour assurer la compatibilité sur plusieurs plateformes.
- Faciliter l'apprentissage de concepts avancés en C++, tels que la manipulation des fichiers, l'orientation objet, et l'interfaçage avec le web.
