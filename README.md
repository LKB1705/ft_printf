<p align="center">
  <img src="https://img.shields.io/badge/42-Lausanne-black?style=for-the-badge&logo=42&logoColor=white" alt="42 Lausanne"/>
  <img src="https://img.shields.io/badge/langage-C-blue?style=for-the-badge&logo=c" alt="C"/>
  <img src="https://img.shields.io/badge/norminette-OK-success?style=for-the-badge" alt="Norminette"/>
</p>

*Ce projet a été créé dans le cadre du cursus de l'école 42 Lausanne par <obohbot>.*

# ft_printf

## Description

**ft_printf** est une réimplémentation de la fonction `printf` de la bibliothèque standard C (`libc`). L'objectif du projet est de comprendre le fonctionnement des **fonctions variadiques** (`va_list`, `va_start`, `va_arg`, `va_end`) et de structurer un code propre, modulaire et conforme à la Norme de 42.

Le résultat est une bibliothèque statique, `libftprintf.a`, qui expose la fonction :

```c
int ft_printf(const char *format, ...);
```

Comme le `printf` original, elle retourne le **nombre de caractères écrits** sur la sortie standard.

## Conversions gérées

| Spécificateur | Description                                         |
|:-------------:|-----------------------------------------------------|
| `%c`          | Affiche un seul caractère                           |
| `%s`          | Affiche une chaîne de caractères                    |
| `%p`          | Affiche un pointeur (`void *`) en hexadécimal       |
| `%d`          | Affiche un entier décimal signé                     |
| `%i`          | Affiche un entier signé en base 10                  |
| `%u`          | Affiche un entier décimal non signé                 |
| `%x`          | Affiche un nombre hexadécimal en minuscules         |
| `%X`          | Affiche un nombre hexadécimal en majuscules         |
| `%%`          | Affiche le caractère `%`                            |

## Instructions

### Prérequis

- Un compilateur `cc` (gcc ou clang)
- `make`
- `ar`

### Compilation

```bash
# Compiler la bibliothèque
make

# Supprimer les fichiers objets
make clean

# Supprimer les fichiers objets et la bibliothèque
make fclean

# Tout recompiler
make re
```

La compilation utilise les flags `-Wall -Wextra -Werror` et produit `libftprintf.a` à la racine du projet.

### Utilisation

Incluez le header et liez la bibliothèque lors de la compilation de votre programme :

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    len = ft_printf("Bonjour %s ! Nombre : %d, hexa : %x, ptr : %p\n",
                    "42", 42, 255, &len);
    ft_printf("Caractères écrits : %d\n", len);
    return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Structure du projet

```
ft_printf/
├── Makefile
├── ft_printf.h
├── ft_printf.c        # Fonction principale et parsing du format
├── ft_print_char.c    # %c et %%
├── ft_print_str.c     # %s
├── ft_print_nbr.c     # %d, %i, %u
├── ft_print_hex.c     # %x, %X
├── ft_print_ptr.c     # %p
└── README.md
```

> Adaptez cette arborescence aux fichiers réellement présents dans votre dépôt.

## Algorithme et choix techniques

### Principe général

1. `ft_printf` initialise une `va_list` avec `va_start`.
2. Le format est parcouru caractère par caractère :
   - un caractère ordinaire est écrit directement avec `write` ;
   - un `%` déclenche la lecture du spécificateur suivant, puis l'appel de la fonction de conversion adaptée.
3. Chaque fonction de conversion retourne le nombre de caractères écrits, ce qui permet de cumuler la valeur de retour finale.
4. La liste d'arguments est libérée avec `va_end`.

### Choix de conception

- **Dispatch par spécificateur** : une fonction dédiée par conversion (ou famille de conversions), pour garder des fonctions courtes et respecter la limite de 25 lignes imposée par la Norme.
- **Conversions numériques récursives** : les nombres sont écrits chiffre par chiffre de façon récursive, ce qui évite toute allocation dynamique (`malloc`) et donc tout risque de fuite mémoire.
- **Hexadécimal** : conversion en base 16 avec une chaîne de symboles (`"0123456789abcdef"` ou `"0123456789ABCDEF"`) pour gérer `%x` et `%X` avec la même logique.
- **Pointeurs** : `%p` affiche le préfixe `0x` suivi de l'adresse en hexadécimal ; un pointeur `NULL` est géré explicitement (`(nil)` sous Linux, `0x0` sous macOS, selon le comportement de la `libc` de référence).
- **Cas limites** : `%s` avec `NULL` affiche `(null)`, et `INT_MIN` est traité sans dépassement en passant par un type plus large (`long`).
- **Valeur de retour** : alignée sur celle de `printf` (nombre d'octets écrits, ou `-1` en cas d'erreur d'écriture).

### Pourquoi une bibliothèque statique ?

Le sujet impose un rendu sous forme d'archive `libftprintf.a`, créée avec `ar rcs`, afin de pouvoir réutiliser `ft_printf` dans les projets suivants du cursus.

## Tests

Quelques pistes pour valider votre implémentation :

```bash
# Comparer avec le printf système
printf("%d|%i|%u|%x|%X|%s|%c|%p|%%\n", ...);
ft_printf("%d|%i|%u|%x|%X|%s|%c|%p|%%\n", ...);
```

- Tester les valeurs limites : `INT_MIN`, `INT_MAX`, `UINT_MAX`, `0`, `-1`.
- Tester `%s` avec `NULL` et la chaîne vide.
- Tester `%p` avec `NULL` et des adresses variées.
- Vérifier l'absence de fuites mémoire avec `valgrind` (ou `leaks` sous macOS).
- Passer le code à la `norminette`.

Testeurs communautaires utiles : [Tripouille/printfTester](https://github.com/Tripouille/printfTester), [paulo-santana/ft_printf_tester](https://github.com/paulo-santana/ft_printf_tester).

## Ressources

### Documentation

- `man 3 printf`, `man 3 stdarg`, `man 2 write`
- [GNU C Library — Variadic Functions](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html)
- [Norme de 42 (PDF)](https://github.com/42School/norminette)
- [cppreference — `printf`](https://en.cppreference.com/w/c/io/fprintf)
- [cppreference — `va_arg`](https://en.cppreference.com/w/c/variadic/va_arg)

### Utilisation de l'IA

L'IA a été utilisée comme aide à la rédaction de ce README (structure et mise en forme). Le code, la conception et la logique du projet ont été réalisés et compris par l'auteur, conformément aux règles de l'école.

## Auteur

- **<votre_login>** — 42 Lausanne
