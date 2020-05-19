#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encryption();

int main(int argc, string argv[])
{
    //checks to see if user provided a value in for the subsitution k if not the program will terminate
    if (argc < 2) 
    {
        printf("please provide a substitution key that is 26 unique alpha characters long\n");
        return 1;
    }
    // if the user put spaces between characters at any point it will ask them for a single line of text instead and terminate
    else if (argc > 2) 
    {
        printf("please provide your key as a single line of text\n");
    }
    //if the key the user provides is not 26 characters long it will remined them that it must be and terminat
    else if (strlen(argv[1]) != 26) 
    {
        printf("substitution key must be 26 characters long\n");
        return 1;
    }
    else
    {
        //this steps through the key provided and checks if there are any non alphabetic values or if there are duplicate values in the string
        for (int i = 0; i < 25; i++) 
        {
            //if there are non alpha digits in the key it will send a message and terminate
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Substitution key must only contain alphabetical values\n");
                return 1;
            }
            for (int j = i + 1; j < 26; j++)
            {
                // if there are duplicate alpha values (upper or lowercase) it will send a message and terminate
                if (argv[1][i] == argv[1][j] || toupper(argv[1][i] == argv[1][j])) 
                {
                    printf("Substitution key must contain only one of each character\n");
                    return 1;
                }
            }
        }
        string cipher = argv[1];
        string plaintext = get_string("plaintext: "); //get plain text from user
        printf("ciphertext: %s\n", encryption(cipher, plaintext));
        return 0;
    }
}

string encryption(string cipher, string plaintext)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz"; //the alphabet string that will be used to substitue with the key
    string ciphertext = plaintext;
    // searches through the plain text provided by the user and substitutes values from the alphabet string with the cipher string and saves them to ciphertext string
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char plainchar = plaintext [i];
        for (int j = 0; j < 26; j++)
        {
            //looks to see if the letter in location i in the plain text is equal to the letter in location j of the alphabet (upper or lower case)
            if (plainchar == alphabet[j] || plainchar == toupper(alphabet[j]))
            {
                //if the plaintext is uppercaes this preserves the case in the ciphertext
                if (isupper(plainchar) != 0)
                {
                    ciphertext[i] = toupper(cipher[j]);
                }
                //likewise for lowercase if the subsitution key is given in uppper case
                else 
                {
                    ciphertext[i] = tolower(cipher[j]);
                }
            }
            //if a non alpha char is in the plain text it will just save that in the ciphertext as is
            if (isalpha(plainchar) == 0)
            {
                ciphertext[i] = plaintext[i];
            }
        }
    }
    return ciphertext;
}