// Grade the reading levels of a text using Coleman-Liau index
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);

int count_words(string text);

int count_sentences(string text);

float get_grade(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    // Calculate the Coleman-Liau index of the text
    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sentences = count_sentences(text);
    int index = round(get_grade(num_letters, num_words, num_sentences));

    // Final grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Count number of letters in the text
int count_letters(string text)
{
    int num_letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            num_letters++;
        }
    }
    return num_letters;
}

// Count number of words in the text
int count_words(string text)
{
    int num_words = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ' || i == n - 1)
        {
            num_words++;
        }
    }
    return num_words;
}

// Count number of sentences in the text
int count_sentences(string text)
{
    int num_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            num_sentences++;
        }
    }
    return num_sentences;
}

// Coleman-Liau index
// index = 0.0588 * L - 0.296 * S - 15.8
float get_grade(int num_letters, int num_words, int num_sentences)
{
    // L = avg num of letters per 100 words
    float avg_letters = (float) num_letters / num_words * 100;
    // S = avg num of sentences per 100 words
    float avg_sentences = (float) num_sentences / num_words * 100;
    float grade = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
    return grade;
}