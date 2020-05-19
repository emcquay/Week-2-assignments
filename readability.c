#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters();
int count_words();
int count_sentences();
int coleman_index();

int main(void)
{
    string text = get_string("Text: ");  // gets string from user input
    int textlen = strlen(text);  //gets the total length of the string including spaces
    //determines the reading level of the text provided
    int grade_score = coleman_index(count_sentences(text, textlen), count_words(text, textlen), count_letters(text, textlen)); 
    if (grade_score <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_score >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_score);
    }
}

int coleman_index(int count_sentences, int count_words, int count_letters)
{
    float constant = 100 / (float)count_words; //this used to calculate the average per 100 words later
    float L = constant * count_letters; //calculates the average letters per 100 words
    float s = constant * count_sentences; // calculates the average sentences per 100 words
    float c_index = (0.0588 * L) - (0.296 * s) - 15.8; // this is the float that holds the reading grade value
    return roundf(c_index); //rounds the float away from zero if at .5 and returns the value to be used in the main program
}

int count_sentences(string text, int textlen) // calculates the number of sentences
{
    int sentence_count = 0;
    for (int i = 0; i < textlen; i++)
    {
        char letteri = text[i];
        //it was stipulated that in this assignment '.' always denotes a sentence. Keep in mind this is not always so.
        if (letteri == '.' || letteri == '?' || letteri == '!')
        {
            sentence_count++;
        }
        else
        {
            sentence_count += 0;
        }
    }
    return sentence_count;
}

int count_words(string text, int textlen)
{
    int word_count = 0;
    for (int i = 0; i < textlen; i++) //increases the word count for every space the program incounters 
    {
        char letteri = text[i];
        // we were told to assume that the sentences provided would not start with a space or contain 2 spaces beside each other meaning that a space should signal the end of a word.
        if (letteri == ' ')   
        {
            word_count ++;
        }
        else
        {
            word_count += 0;
        }
    }
    if (word_count > 0) //This ensures that the length of the sentence will be 0 if the user does not provide input
    {   
        //and increases the word count by 1 to account for the first word of the sentence not starting with a space and if the user only inputs one letter
        word_count ++; 
    }
    return word_count;
}

int count_letters(string text, int textlen) // determines the number of alphabetical characters in the text provided.
{
    int letter_count = 0;
    for (int i = 0; i < textlen; i++)
    {
        if (isalpha(text[i]) == 0)
        {
            letter_count += 0;
        }
        else
        {
            letter_count ++;
        }
    }
    return letter_count;
}