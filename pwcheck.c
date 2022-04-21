#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PW_LENGTH 101 //maximalni délka hesla

//struktura obsahujici statistiky testovanych hesel
typedef struct
{
    bool stats;
    bool nchars[128];
    int min;
    int total_len;
    int password_count;
} Stats;

//funkce pro zjištění délky řetězce
//vstup - str je řetězec kterého delku chceme zjistit
//výstup - číslo které představuje délku řetězce
int my_strlen(char str[]) 
{
    int result = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        result++;
    }

    return result;
}

//funkce pro porovnání délek řetězců
//vstupy - dva řetězce které budeme porovnávat
//výstupy - 0 pokud se jejich délky nerovnají, 1 pokud jsou řetězce stejné délky
int my_strcmp(char str1[], char str2[])
{
    if (my_strlen(str1) != my_strlen(str2))
    {
        return 0;
    }

    for (int i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    
    return 1;
}
//funkce pro odstranění odřádkování za hesly
//vstup - str je řetězec kterému chceme odstanit znak nového řádku z poslední pozice
//výstup - funkce nemá vratnou hodnotu, výsledek se projeví upravou řetězce str
void remove_newline(char* str)
{
    if(str[my_strlen(str) - 1] == '\n')
    {
        str[my_strlen(str) - 1] = '\0';
    }
}
//funkce pro získání podřetězce z jiného řetězce
/* vstupy - str řetězec z kterého chceme získat podřetězec
          - start číslo představuje pozici na kterém začíná podřetězec v řetězci str
          - lenght číslo představuje délku podřetězce který chceme získat
          - result řetězec do kterého se uloží výsledný podřetězec
  výstupy - funkce nemá vratnou hodnotu, vysledný podřetězec je uložený do parametru result */
void get_substring(char* str, int start, int length, char* result)
{
    for(int i = start; i < start + length; i++)
    {
        result[i-start] = str[i];
    }
    result[length] = '\0';
}

//funkce pro zjištění zda se v řetězci nachází malé písmeno (a-z)
//vstup - řetězec password který představuje heslo které chceme zkontrolovat
//výstupy - true pokud male pismeno obsahuje, false pokud male pismeno neobsahuje 
bool contains_lowercase(char* password)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= 'a' && password[i] <= 'z')
        {
            return true;
        }
    }

    return false;
}

//funkce pro zjištění zda se v řetězci nachází velké písmeno (A-Z)
//vstup - řetězec password který představuje heslo které chceme zkontrolovat
//výstupy - true pokud velké písmeno obsahuje, false pokud velké písmeno neobsahuje
bool contains_uppercase(char* password)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= 'A' && password[i] <= 'Z')
        {
            return true;
        }
    }

    return false;
}

//funkce pro zjištění zda řetězec obsahuje číslo (0-9)
//vstup - řetězec password který představuje heslo které chceme zkontrolovat
//výstupy - true pokud řetězec obsahuje číslo, false pokud neobsahuje číslo 
bool contains_number(char* password)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= '0' && password[i] <= '9')
        {
            return true;
        }
    }

    return false;
}

//funkce pro zjištění zda řetězec obsahuje speciální znak (ASCII 32-126)
//vstup - řetězec password který představuje heslo které chceme zkontrolovat
//výstupy - true pokud obsahuje speciální znak, false pokus speciální znak neobsahuje
bool contains_special_character(char* password)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= 32 && password[i] < '0')
        {
            return true;
        }
        if(password[i] > '9' && password[i] < 'A')
        {
            return true;
        }
        if(password[i] > 'Z' && password[i] < 'a')
        {
            return true;
        }
        if(password[i] > 'z' && password[i] <= 126)
        {
            return true;
        }
    }

    return false;
}

//funkce pro kontrolu prvního pravidla 
//vstup - řetězec password který představuje heslo které chceme zkontrolovat
//výstup - true pokud heslo splňuje pravidlo, false pokud heslo pravidlo nesplňuje
bool check_first_rule(char* password)
{
    return (contains_lowercase(password) && contains_uppercase(password));
}

//funkce pro kontrolu druhého pravidla - Heslo obsahuje znaky z alespoň X skupin
//vstupy - řetězec password který představuje heslo které chceme zkontrolovat, parametr
//výstup - true pokud heslo splňuje pravidlo, false pokud heslo pravidlo nesplňuje
bool check_second_rule(char* password, int param)
{
    int checked = 0;

    if(contains_lowercase(password)) //heslo obsahuje malé písmeno (a-z)
    {
        checked++;
    }
    if(contains_uppercase(password)) //heslo obsahuje velké písmeno (A-Z)
    {
        checked++;
    }
    if(contains_number(password)) //heslo obsahuje číslo (0-9)
    {
        checked++;
    }
    if(contains_special_character(password)) //heslo obsahuje speciální znak 
    {
        checked++;
    }

    return (checked >= param || checked == 4);
}

//funkce pro kontrolu třetího pravidla - Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
//vstup - řetězec password který představuje heslo které chceme zkontrolovat, parametr
//výstupy - true pokud heslo pravidlo splňuje, false pokud heslo pravidlo nesplňuje
bool check_third_rule(char* password, int param)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        char c = password[i];
        int count = 0;
        for(int j = i; password[j] != '\0'; j++)
        {
            if(password[j] == c)
            {
                count++;
            }
            else
            {
                i = j - 1;
                break;
            }
        }

        if(count >= param)
        {
            return false;
        }
    }

    return true;
}

//funkce pro kontrolu čtvrtého pravidla - Heslo neobsahuje dva stejné podřetězce délky alespoň X.
//vstupy - řetězec password který představuje heslo které chceme zkontrolovat, parametr
//výstupy - true pokud heslo pravidlo splňuje, false pokud heslo pravidlo nesplňuje
bool check_fourth_rule(char* password, int param)
{
    for(int i = 0; password[i] != '\0'; i++)
    {
        for(int j = i; j - i <= param; j++)
        {
            if(password[j] == '\0')
            {
                return true;
            }
        }

        char substring[param];
        get_substring(password, i, param, substring);

        for(int j = i+1; password[j+param-1] != '\0'; j++)
        {
            char comparison[param];
            get_substring(password, j, param, comparison);
            if(my_strcmp(substring, comparison))
            {
                return false;
            }
        }
    }

    return true;
}

//funkce pro výpis statistik testovaných hesel
//vstup - ????
//výstupy - Statistiky testovaných hesel
void print_stats(Stats stats)
{
    int nchars = 0;
    for (int i = 0; i < 128; i++)
    {
        if(stats.nchars[i])
        {
            nchars++;
        }
    }

    if(stats.total_len == 0)
    {
        stats.password_count = 1;
    }

    printf("Statistika:\n");
    printf("Ruznych znaku: %d\n", nchars); //vypíše počet různých znaků v heslech
    printf("Minimalni delka: %d\n", stats.min); //vypíše délku nejkratšího hesla
    printf("Prumerna delka: %.1f\n", stats.total_len / (float) stats.password_count); //vypíše průměrnou délku testovaných hesel
}

//funkce pro ????
//vstupy - 
//výstupy - 
int pwcheck(int level, int param, Stats stats)
{
    char password[MAX_PW_LENGTH];
    int result = 0;

    while(fgets(password, MAX_PW_LENGTH+1, stdin) != NULL)
    {
        if(my_strlen(password) == MAX_PW_LENGTH && password[MAX_PW_LENGTH-1] != '\n')
        {
            return 2;
        }
        remove_newline(password);
        if(password[my_strlen(password) - 1] == '\0')
        {
            continue;
        }

        if (stats.stats)
        {
            int password_length = my_strlen(password);

            stats.password_count++;
            if(password_length < stats.min || stats.min == 0)
            {
                stats.min = password_length;
            }
            stats.total_len += password_length;

            for (int i = 0; password[i] != '\0'; i++)
            {
                stats.nchars[(int) password[i]] = true;
            }
        }

        if(level >= 1)
        {
            if(!check_first_rule(password))
            {
                continue;
            }
        }
        
        if(level >= 2)
        {
            if(!check_second_rule(password, param))
            {
                continue;
            }
        }

        if(level >= 3)
        {
            if(!check_third_rule(password, param))
            {
                continue;
            }
        }

        if(level == 4)
        {
            if(!check_fourth_rule(password, param))
            {
                continue;
            }
        }

        printf("%s\n", password);
    }

    if(stats.stats)
    {
        print_stats(stats);
    }

    return result;
}

//funkce
//vstupy - 
//výstupy - 
void init_stats(Stats* stats)
{
    stats->min = 0;
    stats->password_count = 0;
    stats->total_len = 0;
    stats->stats = false;
    for (int i = 0; i < 128; i++)
    {
        stats->nchars[i] = false;
    }
    
}

int main(int argc, char* argv[])
{
    int level, param;
    Stats stats;

    init_stats(&stats);

    if (argc == 3 || (argc == 4 && my_strcmp(argv[3], "--stats")))
    {
        if (argc == 4)
        {
            stats.stats = true;
        }

        char* endptr = NULL;
        level = strtol(argv[1], &endptr, 10);

        if (endptr[0] != '\0' || (level < 1 || level > 4))
        {
            fprintf(stderr, "Error: Argument LEVEL contained incorrect value\n");
            return 1;
        }

        param = strtol(argv[2], &endptr, 10);
        
        if (endptr[0] != '\0' || param < 1)
        {
            fprintf(stderr, "Error: Argument PARAM contained incorrect value\n");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }

    int result = pwcheck(level, param, stats);

    if(result == 2)
    {
        fprintf(stderr, "Error: Input exceeded 100 characters\n");
    }

    return result;
}