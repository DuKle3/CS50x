#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

//declartion
int count_letter(string t);
int count_words(string t);
int count_sentences(string t);
void cal_grade(float index);

int main(void)
{
    //get input text
    string text = get_string("Text: ");

    //letter
    int letter = count_letter(text);

    //word
    int words = count_words(text);

    //sentences
    int sentences = count_sentences(text);

    //letters per 100 words
    float L = (float)letter / words * 100;

    //sentences per 100 words
    float S = (float)sentences / words * 100;

    //index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    cal_grade(index);
}

int count_letter(string t)
{
    int count = 0;
    int i = 0;
    while (t[i])
    {
        if (isalpha(t[i]))
        {
            count++;
        }
        i++;
    }
    return count;
}

int count_words(string t)
{
    int i = 0;
    int count = 0;
    while (t[i])
    {
        if (t[i] == ' ')
        {
            count++;
        }
        i++;
    }
    return count + 1;
}

int count_sentences(string t)
{
    int i = 0;
    int count = 0;
    while (t[i])
    {
        if (t[i] == '!' || t[i] == '.' || t[i] == '?')
        {
            count++;
        }
        i++;
    }
    return count;
}

void cal_grade(float index)
{
    int grade = 0;
    int i = 0;
    while (1)
    {
        if (index - i < 1)
        {
            if (index - i < (i + 1) - index)
            {
                grade = i;
                break;
            }
            else
            {
                grade = i + 1;
                break;
            }
        }
        i++;
    }
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}