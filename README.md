# 42sh - Shell Avancé

## 📋 Description

**42sh** est un interpréteur de commandes (shell) avancé. Il implémente de nombreuses fonctionnalités d'un shell moderne, incluant la gestion des commandes intégrées, des redirections, des pipes, de l'historique des commandes, des alias, et bien plus encore.

## 👥 Équipe de Développement

- **Aouadene Amayyas**
- **Aberkane Mathys**  
- **COMBE--BRACCIALE Nielsen**


## ✨ Fonctionnalités

### 🔧 Commandes Intégrées (Built-ins)
- `cd` / `chdir` - Changement de répertoire avec support de `~`, `-`, et chemins relatifs/absolus
- `env` - Affichage des variables d'environnement
- `setenv` - Définition de variables d'environnement
- `unsetenv` - Suppression de variables d'environnement
- `exit` - Sortie du shell avec code de retour optionnel
- `history` - Gestion de l'historique des commandes avec support des nombres
- `alias` - Création et gestion d'alias de commandes
- `set` - Gestion des variables locales
- `setcolor` - Personnalisation des couleurs du prompt

### 🚀 Fonctionnalités Avancées
- **Exécution de commandes externes** avec recherche dans le PATH
- **Pipes** (`|`) - Chaînage de commandes
- **Redirections** :
  - `>` - Redirection de sortie
  - `<` - Redirection d'entrée
  - `<<` - Here document
- **Opérateurs logiques** :
  - `&&` - Exécution conditionnelle (ET)
  - `||` - Exécution conditionnelle (OU)
- **Séparateur** `;` - Exécution séquentielle
- **Parenthèses** `()` - Groupement de commandes
- **Backticks** `` `command` `` - Substitution de commandes
- **Globbing** - Expansion des motifs (`*`, `?`, `[]`, `{}`, `~`)
- **Variables** - Support des variables locales et d'environnement
- **Gestion des signaux** - Ctrl+C, Ctrl+D, etc.

### 🎨 Interface Utilisateur
- **Mode interactif** avec prompt coloré personnalisable
- **Édition de ligne avancée** :
  - Navigation avec les flèches
  - Historique des commandes (↑/↓)
  - Raccourcis clavier (Ctrl+A, Ctrl+W, Ctrl+Y, etc.)
  - Support des touches Suppr, Backspace
- **Autocomplétion** et **navigation dans l'historique**
- **Mode non-interactif** pour l'exécution de scripts

### 📜 Gestion de l'Historique
- **Commande `history`** avec affichage des commandes précédentes
- **Navigation** dans l'historique avec les flèches
- **Commandes Bang** (`!`) :
  - `!n` - Exécute la commande numéro n
  - `!string` - Exécute la dernière commande commençant par string

## 🏗️ Architecture

### Structure du Projet
```
42sh/
├── source/
│   ├── main.c                 # Point d'entrée principal
│   ├── terminal_line.c        # Gestion du prompt
│   ├── binary_tree/           # Arbre syntaxique
│   ├── builtins/             # Commandes intégrées
│   ├── parser/               # Analyseur syntaxique
│   ├── separator/            # Gestion des opérateurs
│   ├── termios/             # Interface terminal
│   └── tools/               # Utilitaires
├── lib/my/                  # Bibliothèque personnelle
├── include/                 # Fichiers d'en-tête
├── tests/                   # Tests et validation
└── Makefile                # Configuration de compilation
```

### Composants Principaux

#### 🌳 Arbre Syntaxique Binaire
Le shell utilise un arbre binaire pour représenter et exécuter les commandes complexes :
- **Feuilles** : Commandes simples
- **Nœuds** : Opérateurs (pipes, redirections, &&, ||, ;)

#### 📊 Structures de Données
- `mysh_t` : Structure principale du shell
- `bin_tree_t` : Nœuds de l'arbre syntaxique
- `history_t` : Gestion de l'historique
- `alias_t` : Gestion des alias
- `variables_t` : Variables locales

## 🛠️ Compilation et Installation

### Prérequis
- GCC ou compilateur C compatible
- Make
- Bibliothèques système standard

### Compilation
```bash
# Compilation du projet
make

# Nettoyage des fichiers objets
make clean

# Nettoyage complet
make fclean

# Recompilation complète
make re
```

### Tests
```bash
# Exécution des tests unitaires
make tests_run

# Test avec le script de validation
./tests/tester.sh
```

## 🚀 Utilisation

### Lancement du Shell
```bash
# Mode interactif
./42sh

# Affichage de l'aide
./42sh -h

# Exécution d'un script (mode non-interactif)
./42sh < script.sh
```

### Exemples d'Utilisation

#### Commandes de Base
```bash
# Navigation
cd /home/user
cd ~          # Répertoire home
cd -          # Répertoire précédent

# Variables d'environnement
setenv PATH /usr/bin:/bin
env
unsetenv TEMP

# Variables locales
set var=value
set           # Affiche toutes les variables
```

#### Pipes et Redirections
```bash
# Pipe simple
ls -la | grep ".txt"

# Redirections
ls > files.txt
cat < input.txt
cat << EOF
Hello World
EOF

# Combinaisons complexes
ls | grep ".c" > sources.txt
```

#### Opérateurs Logiques
```bash
# Exécution conditionnelle
make && ./program
command_fail || echo "Erreur détectée"

# Séquences
cd /tmp; ls; pwd
```

#### Fonctionnalités Avancées
```bash
# Substitution de commandes
echo "Date: `date`"
files=`ls *.c`

# Groupement avec parenthèses
(cd /tmp && ls) ; pwd

# Globbing
ls *.c           # Tous les fichiers .c
cp file?.txt /backup/  # file1.txt, file2.txt, etc.
```

#### Alias
```bash
# Création d'alias
alias ll "ls -la"
alias gcc-debug "gcc -g -Wall -Wextra"

# Utilisation
ll
gcc-debug main.c

# Affichage des alias
alias
```

#### Historique
```bash
# Affichage de l'historique
history
history 10    # 10 dernières commandes

# Exécution depuis l'historique
!42           # Exécute la commande numéro 42
!ls           # Exécute la dernière commande commençant par "ls"
```

#### Personnalisation
```bash
# Couleurs du prompt
setcolor RED
setcolor BLUE
setcolor RESET
```

## 🎯 Fonctionnalités Spéciales

### Interface Termios Avancée
- **Raw mode** pour une saisie caractère par caractère
- **Gestion des séquences d'échappement** pour les flèches
- **Édition de ligne** avec positionnement du curseur
- **Copier/Coller** avec Ctrl+W/Ctrl+Y

### Gestion des Erreurs
- **Codes de retour** conformes aux standards UNIX
- **Messages d'erreur** descriptifs
- **Gestion des signaux** appropriée

### Optimisations
- **Tri des alias** pour un affichage ordonné
- **Gestion mémoire** rigoureuse avec libération automatique
- **Algorithmes efficaces** pour la recherche et le parsing

## 🧪 Tests et Validation

Le projet inclut un système de tests complet :

### Script de Test Principal
```bash
# Test complet
./tests/tester.sh

# Test spécifique
./tests/tester.sh test_id

# Mode debug
./tests/tester.sh -d test_id
```

### Comparaison avec tcsh
Le système de tests compare automatiquement les sorties avec le shell de référence `tcsh` pour garantir la conformité.

## 📝 Notes Techniques

### Gestion de la Mémoire
- **Allocation dynamique** pour toutes les structures
- **Fonctions de libération** dédiées pour chaque type
- **Vérification des fuites** avec les outils de debugging

### Algorithmes Utilisés
- **Tri fusion** pour l'ordonnancement des alias
- **Arbre binaire** pour l'analyse syntaxique
- **Listes chaînées** pour l'historique et les variables

### Conformité Standards
- **POSIX** pour les fonctionnalités de base
- **GNU Bash** pour les extensions avancées
- **Coding Style EPITECH** pour le formatage du code

## 🐛 Limitations Connues

- Pas de support pour les jobs en arrière-plan
- Expansion des accolades limitée
- Pas de support pour les fonctions shell

---